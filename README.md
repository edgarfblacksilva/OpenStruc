# OpenStruc:
OpenStruc: Static Analysis of Two- and Three-dimensional Structures
Version 1.0
August 04, 2025

![my OpenStruc logo](https://github.com/edgarfblacksilva/OpenStruc/blob/main/src/OpenStrucLogo.jpg)

**OpenStruc** is a computer program for the static analysis of two- and three-dimensional structures. **OpenStruc** can be used to analyze several types of structures: plane trusses and frames, space trusses and frames, and grids -- plane structures with loads applied orthogonally to their plane. 

**OpenStruc** is written entirely in C++. At its core, **OpenStruc** uses a direct solver algorithm based on Gauss Elimination, including a variation of the *Active Column Solution* method.

Welcome to **OpenStruc**. Thank you for using it! 


# Requirements

- `C++ compiler`
- `cmake`
- `python, numpy, matplotlib `
- `matplotlibcpp.h`

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
In the Solutions directory, you will find an output file for each of the input files located in the Examples directory.


