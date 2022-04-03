#include <iostream>
#include <string>

#include "solver.hpp"

int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        std::cout << "./raster2vector.out SRC_FILE_NAME SVG_FILE_NAME VIEWER_FILE_NAME" << std::endl;
        return 0;
    }
    std::string src_file_name = std::string(argv[1]);
    std::string svg_file_name = std::string(argv[2]);
    std::string viewer_file_name = std::string(argv[3]);

    bool viewer_auto_reload = true;
    int iterate_num = 1000;
    int max_r = 100;
    int quality = 10;

    Solver solver(src_file_name);
    solver.solve(viewer_file_name, viewer_auto_reload, iterate_num, max_r, quality);
    solver.write_svg(svg_file_name);
    solver.write_viewer(viewer_file_name);

    return 0;
}