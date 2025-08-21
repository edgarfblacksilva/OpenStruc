# OpenStruc:
OpenStruc: Static Analysis of Two- and Three-dimensional Structures
Version 1.0
August 21, 2025

![my OpenStruc logo](https://github.com/edgarfblacksilva/OpenStruc/blob/main/src/OpenStrucLogo.jpg)

**OpenStruc** is a computer program for the static analysis of two- and three-dimensional structures. **OpenStruc** can be used to analyze five types of structures: plane trusses and plane frames, space trusses and space frames, and plane structures with loads applied orthogonally to their plane (grids). 

**OpenStruc** is written entirely in C++. At its core, **OpenStruc** uses a direct solver algorithm based on Gauss Elimination, including a variation of the *Active Column Solution* method.

**OpenStruc** includes a plotting subsystem that utilizes a slightly modified version of the header file "matplotlibcpp.h" from the **matplotlib-cpp** project (See https://github.com/lava/matplotlib-cpp). **matplotlib-cpp** resembles the plotting API used by Matlab and matplotlib. Therefore, please be sure that your computer has a working **Python** system with the numpy and matplotlib libraries installed.

**OpenStruc** has been compiled and testsed in Linux (Linux Mint 22.1) and the following C++ compilers:
  - g++ 13.3.0-6ubuntu2~24.04
  - icpx Intel(R) oneAPI DPC++/C++ Compiler 2025.1.1 (2025.1.1.20250418)
  - Nvidia nvc++ 25.5-0 64-bit target on x86-64 Linux -tp haswell

**OpenStruc** has also compiled and tested in Mac OSX using the clang++ compiler. Thank to Brock Angelo for his assistant with the OSX implementation.

Please, take a look at the `user_Guide_OpenStruc.pdf` document for a quick overview of basic commands that will allow you to start analyzing structures quickly.

Welcome to **OpenStruc**. Thank you for using it! 

# Requirements

- `C++ compiler`
- `cmake`
- `python, numpy, matplotlib`

# Build Instructions

1. Make a build directory

```bash
mkdir build 
```

2. move to the build directory
```bash
cd build 
```

3. Build OpenStruc
```bash
cmake ..
```

4. Make OpenStruc
```bash
make 
```

# Run an example

The most common mode of running OpenStruc is by reading its commands from an input
script file. For example, you can instruct **OpenStruc** to execute one of the examples included in the `Examples` directory:

```
$ OpenStruc Examples/spaceFrame.dat [outputFileName]
```

For extended instruction on how to run **OpenStruc**, take a look at the *user_Guide_OpenStruc.pdf* included in this distribution.


# Check your solution
In the `Solutions` directory, you will find an output file for each of the input files located in the `Examples` directory.


