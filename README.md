# EDLine-py
Forked from [this](https://github.com/HanjieLuo/EDLine_parallel)

![test image](./data/result.png)

## Update
- added python binding
- added web [api](api/readme.md)
- install with *cmake*

## Requirements ##
The code is tested on Debian GNU/Linux 10. It requires the following tools and libraries: *python3.8*, *pybind11*, *Numpy*, *OpenCV 3.4.13*.

## Installation ##
in the project root, execute the following command in your terminal
```bash
pip install .
```

## Usage ##
```python
import cv2
import edline
# args: kernel:int
#       sigma:float
#       gradient_threshold:float
#       anchor_threshold:float
#       scan_interval:int
#       min_line_len:int
#       line_fit_err_threshold:float
ed = edline.EDLine(5, 1.0, 30, 5, 2, 25, 1.8)
lines = edline.LineList()
img = cv2.imread(SOME_IMAGE, 0)  # 0: gray scale
ed.detect(img, lines, False)
for l in lines:
    print(l.endpoint)  # [x1, y1, x2, y2]
```

Test:

```bash
PYTHONPATH=. python test/demo.py
```

## Known issues ##
*OpenCV* that is installed with `pip` may not work with this repo.
install with *CMake* instead:
```
# assuming numpy has been installed
git clone -b 3.4.13 https://github.com/opencv/opencv.git
cd opencv
mkdir build
cd build
cmake .. -DPYTHON3_EXECUTABLE=`which python`
make -j`nproc`
make install
```
