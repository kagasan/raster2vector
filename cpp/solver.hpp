#pragma once

#include <random>
#include <fstream>
#include <algorithm>

#include "image.hpp"
#include "svg.hpp"
#include "ring.hpp"
#include "median_color.hpp"
#include "viewer.hpp"

class Solver{
    public:
    Image goal, canvas;
    std::vector<Stroke>strokes;
    Ring ring;

    Solver(std::string file_name) {
        mt = std::mt19937_64(rd());
        goal.read(file_name);
        canvas = Image(goal.size);
    }
    void solve(std::string viewer_file_name, bool auto_reload = true, int iterate_num = 1000, int max_r = 100, int quality = 10) {
        ring = Ring(max_r);
        int last_r = max_r;
        for (int iterate = 0; iterate < iterate_num; iterate++) {
            Stroke stroke = search_best_circle(std::max(std::min(max_r, last_r * 2), 50), quality);
            last_r = stroke.r;
            extend_stroke(stroke);
            canvas.paint(stroke);
            strokes.push_back(stroke.light_stroke());
            if(iterate % 10 == 0)write_viewer(viewer_file_name, auto_reload);
            // canvas.write_png("canvas.png");
        }
    }
    void write_svg(std::string file_name) {
        SVG svg(canvas.size);
        svg.bind(strokes);
        std::ofstream ofs(file_name);
        ofs << svg << std::endl;
    }
    void write_viewer(std::string file_name, bool auto_reload = false) {
        SVG svg(canvas.size);
        svg.bind(strokes);
        Viewer viewer;
        viewer.write(file_name, svg, auto_reload);
    }
    
    private:
    std::random_device rd;
    std::mt19937_64 mt;

    Point random_point() {
        return Point(mt() % canvas.size.width, mt() % canvas.size.height);
    }

    Point near_point(Point point, int r) {
        r = r * (0.5 + (mt() % 100) * 0.01);
        int x = point.x + r * std::cos(mt() * 0.001);
        int y = point.y + r * std::sin(mt() * 0.001);
        return Point(x, y);
    }

    Stroke optimize_circle_by_center(int max_r, Point center) {
        Stroke best_circle(0, Color(0, 0, 0), canvas.size, {}, -1);
        MedianColor median_color;
        long long r_diff_sum = 0, g_diff_sum = 0, b_diff_sum = 0;
        std::vector<int>r_count(1050, 0), g_count(1050, 0), b_count(1050, 0);
        for (int r = 0; r <= max_r; r++) {
            for (auto d: ring.points[r]) {
                Point p = center + d;
                if (! canvas.has(p))continue;
                r_diff_sum += abs(goal[p].r - canvas[p].r);
                g_diff_sum += abs(goal[p].g - canvas[p].g);
                b_diff_sum += abs(goal[p].b - canvas[p].b);
                median_color.push(2 * goal[p].r - canvas[p].r, 2 * goal[p].g - canvas[p].g, 2 * goal[p].b - canvas[p].b);
                r_count[520 + 2 * goal[p].r - canvas[p].r]++;
                g_count[520 + 2 * goal[p].g - canvas[p].g]++;
                b_count[520 + 2 * goal[p].b - canvas[p].b]++;
            }
            Stroke tmp_circle(r, median_color.get(), canvas.size, {});
            for (int i = 0; i < 1050; i++) {
                int double_src_dst = i - 520;
                tmp_circle.score += r_count[i] * abs(double_src_dst - tmp_circle.color.r);
                tmp_circle.score += g_count[i] * abs(double_src_dst - tmp_circle.color.g);
                tmp_circle.score += b_count[i] * abs(double_src_dst - tmp_circle.color.b);
            }
            tmp_circle.score /= -2;
            tmp_circle.score += r_diff_sum;
            tmp_circle.score += g_diff_sum;
            tmp_circle.score += b_diff_sum;
            if (tmp_circle.score > best_circle.score) {
                best_circle = tmp_circle;
            }
        }
        best_circle.push_back(center);
        return best_circle;
    }

    Stroke search_best_circle(int max_r, int iterate_num) {
        Stroke best_circle = optimize_circle_by_center(max_r, random_point());
        for (int iterate = 1; iterate < iterate_num; iterate++) {
            Stroke tmp_circle = optimize_circle_by_center(max_r, random_point());
            if (tmp_circle.score > best_circle.score) {
                best_circle = tmp_circle;
            }
        }
        return best_circle;
    }

    long long calculate_update_score(const std::vector<Point> & points, Color color) {
        long long score = 0;
        for (auto point : points) {
            long long before_diff = goal[point] - canvas[point];
            long long after_diff = goal[point] - (canvas[point] + color);
            score += before_diff - after_diff;
        }
        return score;
    }

    void extend_stroke(Stroke &stroke) {
        for (int failed_count = 0; failed_count < 3; failed_count++) {
            long long best_extend_score = 0;
            Point best_extend_point;
            bool best_front_flag = true;
            for (int iterate = 0; iterate < 50; iterate++) {
                bool front_flag = mt() % 2 > 0;
                Point p = front_flag ? stroke.get_front() : stroke.get_back();
                Point q = near_point(p, stroke.r);
                if (! canvas.has(q))continue;
                std::vector<Point>points;
                if (front_flag) points = stroke.push_front(q, true);
                else points = stroke.push_back(q, true);
                long long update_score = calculate_update_score(points, stroke.color);
                if (update_score > best_extend_score) {
                    best_extend_score = update_score;
                    best_extend_point = q;
                    best_front_flag = front_flag;
                }
            }
            if (best_extend_score > 0) {
                stroke.score += best_extend_score;
                if (best_front_flag) stroke.push_front(best_extend_point);
                else stroke.push_back(best_extend_point); 
                failed_count = 0;
            }
        }
    }

    void fit_color(Stroke &stroke) {
        if (stroke.point_set.empty())return;
        std::vector<int>r, g, b;
        for (auto p: stroke.point_set) {
            r.push_back(2 * goal[p].r - canvas[p].r);
            g.push_back(2 * goal[p].g - canvas[p].g);
            b.push_back(2 * goal[p].b - canvas[p].b);
        }
        std::sort(r.begin(), r.end());
        std::sort(g.begin(), g.end());
        std::sort(b.begin(), b.end());
        stroke.color.r = r[r.size() / 2];
        stroke.color.g = g[g.size() / 2];
        stroke.color.b = b[b.size() / 2];
    }
};