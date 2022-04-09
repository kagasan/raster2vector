set -eu

sh build.sh

echo run start
VIEWER_FILE=index.html
cp waiting.html ${VIEWER_FILE}
open ${VIEWER_FILE}
./raster2vector.out sample.png result.svg ${VIEWER_FILE}

echo run finish
