set -eu

echo download libraries
curl https://raw.githubusercontent.com/nothings/stb/master/stb_image.h -o ./cpp/stb_image.h
curl https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h -o ./cpp/stb_image_write.h

echo build start
g++ -std=c++11 ./cpp/main.cpp -O3 -o raster2vector.out -Wall

echo build finish
