# raster2vector
ラスタ画像をベクタ画像に変換します。

## build
```
sh build.sh
```

## run
```
./raster2vector.out sample.jpg result.svg index.html
# 実行中はブラウザでindex.htmlを開いて過程を確認できます。
```

## result

## ○○したい
### 一部領域（人間の顔など）だけ高解像にしたい
```
solver.hppのPoint random_point()で偏りを持たせる
Point random_point() {
    if(mt() % 5 == 0)return Point(mt() % canvas.size.width, mt() % canvas.size.height);
    return Point(200 + mt() % 60, 85 + mt() % 60);
}
```

### 動画にしたい
```
solver.hppのvoid solve()のループ内でcanvas.write_png()
ffmpeg等で複数の画像から動画にする
```

## 利用ライブラリ
https://github.com/nothings/stb
```
MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
