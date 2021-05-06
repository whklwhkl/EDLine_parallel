c++ -O3 -Wall -shared -std=c++11 \
  $(python3 -m pybind11 --includes) \
  src/*.cpp \
  -o edline$(python3-config --extension-suffix) \
  -I`python -c"import numpy;print(numpy.get_include())"` \
  -Iinclude/ -fPIC \
  -L/usr/local/lib \
  `pkg-config --cflags --libs opencv`
