# elsh

## Motivation 
In a word, I want to build my own script language that can be written in `C` or a simplied version of `C`. And here are some basic rules: 
- All the code would be written in C++ and C++ only, using c++11 standard. No more than that.
- The code should be able to be built anywhere there is a C++ compiler. so, we will use `Makefile` to build this project. No `cmake` or `bazel`.

## Goal
For example, you have a `elsh` script `example.sh` like this: 
```
int a = 0;
int b = 10;
do {
  a += 1;
  print(a);
} while ( a < b );
```
and you have already install the `elsh` in the system, then you can use: 
```
elsh example.sh
```
to run this script.