# error\_tools

A collection of tools used for error handling. These tools provide a linked
list class which can help a user both understand where an error happened
and also help the developer to correct for the errors.

Note: In order to use the Intel compiler one must run the following command in a
bash prompt:

```
source /path/to/ifortvars.sh -arch intel64 -platform linux
```

This is the same command that the abaqus command issues. It may be that
this command will change on different platforms.

---

---

## Dependencies:

### Executables

* CMake >= 3.14
* Doxygen >= 1.8.5

### Python Modules (for documentation)

* Sphinx >= 3.0.4
* Breathe >= 4.18.1
* sphinx\_rtd\_theme >= 0.4.3

For convenience, the minimal Python environment requirements for the
documentation build are included in ``environment.yaml`` and
``requirements.txt``. A minimal anaconda environment for building the
documentation can be created from an existing anaconda installation with the
following commands.

```
$ conda env create --file environment.yaml
```

---

---

## Building the documentation

> **API Health Note**: The sphinx API docs are a work-in-progress. The doxygen
> API is much more useful

A build script has been created for convenience, ``new_build.sh``. It will build
everything including the library binary, the test binary, and the documentation.
This is the same build script used by ``jenkins_build.sh`` for CI builds and
testing.

### sstelmo

1) Activate the python environment.

```
$ conda activate environment
```

2) Create the build directory and move there

```
$ pwd
/path/to/error_tools/
$ mkdir build/
$ cd build/
```

3) Run cmake3 configuration

```
$ pwd
/path/to/error_tools/build/
$ cmake3 ..
```

4) Build the docs

```
$ cmake3 --build docs
```

5) Documentation builds to:

```
error_tools/build/docs/sphinx/index.html
```

6) Display docs

```
$ pwd
/path/to/error_tools/build/
$ firefox docs/sphinx/index.html &
```

7) While the Sphinx API is still a WIP, try the doxygen API


```
$ pwd
/path/to/error_tools/build/
$ firefox docs/doxygen/html/index.html &
```

---

---

## Building the python interface

A python interface to the ``error_tools`` C++ routines is provided. After the
libraries have been built, they can be linked so that they can be called with
python. 

### sstelmo

1) Build the libraries

```
$ pwd
/path/to/error_tools
$ ./new_build.sh g++
```

2) Activate the python environment

```
$ conda activate environment
```

3) in the ``src/python`` directory build the interface using ``cython``

```
$ pwd
/path/to/src/python
$ python setup.py build_ext --inplace
```
