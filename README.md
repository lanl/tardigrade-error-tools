# error\_tools

A collection of tools used for error handling. These tools provide a linked 
list class which can help a user both understand where an error happened 
and also help the developer to correct for the errors.

Note: In order to use the Intel compiler one must run the following command in a
bash prompt: source /apps/intel2016/bin/ifortvars.sh -arch intel64 -platform
linux

This is the same command that the abaqus command issues. It may be that 
this command will change on different platforms.

---

---

## Dependencies: 

* CMake
* Doxygen
* Sphinx
* Breathe
* sphinx\_rtd\_theme

---

---

Building the documentation:

1) Create the build directory

```
mkdir build0/
cd build0/
```

2) Set the environment CXX variable

```
export CXX=g++
```

3) Run cmake3

```
cmake3 ..
```

4) Run make

```
make
```

5) Documentation builds to: 

```
.../error_tools/build0/docs/sphinx/index.html
```
