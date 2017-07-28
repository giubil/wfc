# Wave Function Collapse in C++
This code is a refactor from https://github.com/emilk/wfc, which is a C++ port of https://github.com/mxgmn/WaveFunctionCollapse.

All sample images come from https://github.com/mxgmn/WaveFunctionCollapse

# License
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.

The sample images are from https://github.com/mxgmn/WaveFunctionCollapse, so they are NOT covered by the above license.

# How to get started

    git clone git@github.com:giubil/wfc.git
    cd wfc
    make run

`make run` starts downloads dependencies, build, links, and finally runs the program.

This works on Mac and Linux.

When running the sfml code, please be advised that it is a WIP. Several things are not handled. Window dimension are written in the code, and do not adapt to the dimension of the samples being shown.

To show frames you need to pass the argument `--gif`. The final gif will also not be created (even if the file will be created, it will only have the final frame into it).

# Requirements

C++14. 

This release integrates a video output with SFML. It also totally breaks Windows support, because of the introduction of threads.

All required third-party libraries are included or downloaded by running `make` (except for SFML). These are:

* https://github.com/emilk/configuru (`.cfg` loading)
* https://github.com/emilk/emilib (small helpers for looping and string formating)
* https://github.com/emilk/loguru (logging and asserts)
* https://github.com/nothings/stb (image read/write)
* http://www.jonolick.com/home/gif-writer (write gif files)

# Performance
The sample configuration finishes **25% faster** than the original version (50 vs 40 seconds).

Tested on a Linux VM, speed may be better on an installed distribution.

# Limitations
This port supports everything in https://github.com/mxgmn/WaveFunctionCollapse (as of October 2016),
though with slightly different input ([.cfg files](https://github.com/emilk/Configuru) over .xml, for instance).

The code is not optimized nor well-documented. It could also do with some further cleanup.
