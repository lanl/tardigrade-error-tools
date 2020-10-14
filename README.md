# error\_tools

A collection of tools used for error handling. These tools provide a linked
list class which can help a user both understand where an error happened
and also help the developer to correct for the errors.

Note: In order to use the Intel compiler one must run the following command in a
bash prompt:

```
source /apps/intel2016/bin/ifortvars.sh -arch intel64 -platform linux
```

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

## Building the documentation

> **API Health Note**: The sphinx API docs are a work-in-progress. The doxygen
> API is much more useful

A build script has been created for convenience, ``new_build.sh``. It will build
everything including the library binary, the test binary, and the documentation.
This is the same build script used by ``jenkins_build.sh`` for CI builds and
testing.

### sstelmo

1) Activate a [W-13 Python Environment](https://xcp-confluence.lanl.gov/display/PYT/The+W-13+Python+3+environment)

```
$ module load python/2019.10-python-3.7
$ sv3r
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
