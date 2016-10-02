# Wave Function Collapse in C++
This is a C++ port of https://github.com/mxgmn/WaveFunctionCollapse.

All sample images come from https://github.com/mxgmn/WaveFunctionCollapse

# License
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.

The sample images are from https://github.com/mxgmn/WaveFunctionCollapse, so they are NOT covered by the above license.

# How to run
Download third-party libraries by running `./configure.sh`.
To compile and run the program, just run `./main.cpp` (yes, really).
Optionally, just compile `main.cpp` with your favorite compile.
This works on Mac, and maybe Linux.

# Requirements
C++14. Nothing more, really.

All required third-party libraries are downloaded by the `./configure.sh` script. These are:

* https://github.com/emilk/configuru (`.cfg` loading)
* https://github.com/emilk/emilib (small helpers for looping and string formating)
* https://github.com/emilk/loguru (logging and asserts)
* https://github.com/nothings/stb (image read/write)

# Limitations
This port supports everything in https://github.com/mxgmn/WaveFunctionCollapse (as of October 2016),
though with slightly different input ([.cfg files](https://github.com/emilk/Configuru) over .xml, for instance).

The code is not optimized nor well-documented. It could also do with some further cleanup.