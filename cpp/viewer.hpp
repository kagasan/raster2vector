#pragma once
#include <fstream>

#include "svg.hpp"

class Viewer{
    public:
    void write(std::string file_name, SVG svg, bool auto_reload = false) {
        std::ofstream ofs(file_name);
        ofs << R"(
        <html>
        <head>
        <meta charset='utf-8'>
        <title>viewer</title>
        <script>
        window.onload = () => {
        )" << std::endl;
        ofs << "const info = '" << (auto_reload ? " (auto reload mode)" : "") << "';" << std::endl;
        ofs << R"(
            const svg = document.getElementsByTagName('svg')[0];
            const path = svg.children;
            const step_input = document.getElementById('step');
            const speed_input = document.getElementById('speed');
            const step_label = document.getElementById('step_label');
            const speed_label = document.getElementById('speed_label');
            svg.setAttribute('height', '95%');
            svg.removeAttribute('width');
            step_input.max = path.length - 1;
            step_input.value = path.length - 1;
            setInterval(()=>{
            const step = (parseInt(step_input.value) + parseInt(speed_input.value)) % path.length;
            step_input.value = step;
            step_label.innerText = `Step:${step+1}/${path.length}`;
            speed_label.innerText = `Speed:${speed_input.value}`;
            document.title = `${step+1}/${path.length}` + info;
            for (let i = 0; i < path.length; i++) {
            path[i].style.visibility = i <= step ? 'visible' : 'hidden';
            }
            }, 100);
        )" << std::endl;
        if (auto_reload) {
            ofs << "window.setTimeout(function(){location.reload()},5000);" << std::endl;
        }
        ofs << R"(
        }
        </script>
        <style>
        body {
        margin: 0;
        text-align: center;
        }
        </style>
        </head>
        <body>
        <div style='height:5%'>
        <input type='range' id='step' name='step' min='0' max='1' value='0'><label for='step' id ='step_label'>Step</label>
        <input type='range' id='speed' name='speed' min='0' max='10' value='0'><label for='speed' id = 'speed_label'>Speed</label>
        </div>
        )" << std::endl;
        ofs << svg << std::endl;
        ofs << R"(
        </body>
        </html>
        )" << std::endl;
    }
};