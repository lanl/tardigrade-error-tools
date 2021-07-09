############
error\_tools
############

*******************
Project Description 
*******************

A collection of tools used for error handling. These tools provide a linked
list class which can help a user both understand where an error happened
and also help the developer to correct for the errors.

Information
===========

* Documentation: https://aea.re-pages.lanl.gov/material-models/error_tools
* Wiki: https://re-git.lanl.gov/aea/material-models/error_tools/-/wikis/home

Developers
==========

* Nathan Miller nathanm@lanl.gov
* Kyle Brindley kbrindley@lanl.gov

************
Dependencies
************

Executables
===========

* CMake >= 3.14
* Doxygen >= 1.8.5

Python Modules (for documentation)
==================================

* Sphinx >= 3.0.4
* Breathe >= 4.30.0
* sphinx\_rtd\_theme >= 0.4.3

For convenience, the minimal Python environment requirements for the
documentation build are included in ``environment.yaml`` and
``requirements.txt``. A minimal anaconda environment for building the
documentation can be created from an existing anaconda installation with the
following commands.
 
.. code-block:: bash

   $ conda env create --file environment.yaml

**************************
Building the documentation
**************************

.. warning::

   **API Health Note**: The Sphinx API docs are a work-in-progress. The doxygen
   API is much more useful

A build script has been created for convenience, ``new_build.sh``. It will build
everything including the library binary, the test binary, and the documentation.
This is the same build script used by ``jenkins_build.sh`` for CI builds and
testing.

sstelmo
=======

1) Activate a [W-13 Python Environment](https://xcp-confluence.lanl.gov/display/PYT/The+W-13+Python+3+environment)

   .. code-block:: bash

      $ sv3r

2) Create the build directory and move there

   .. code-block:: bash

      $ cd build/

3) Run cmake3 configuration
 
   .. code-block:: bash

      $ cmake3 ..

4) Build the docs

   .. code-block:: bash

      $ cmake3 --build docs

5) Sphinx HTML Documentation builds to:

   .. code-block:: bash

      error_tools/build/docs/sphinx/html/index.html

6) Display docs

   .. code-block:: bash

      $ firefox docs/sphinx/html/index.html &

7) While the Sphinx API is still a WIP, try the doxygen API

   .. code-block:: bash

      $ firefox docs/doxygen/html/index.html &

*****************
Build the library
*****************

Follow the steps for building the documentation and pick up below.

4) Build just the library

   .. code-block:: bash

      $ pwd
      /path/to/error_tools/build
      $ cmake3 --build src/cpp

*******************
Install the library
*******************

Build the entire before performing the installation.

4) Build the entire project

   .. code-block:: bash

      $ pwd
      /path/to/error_tools/build
      $ cmake3 --build .

5) Install the library

   .. code-block:: bash

      $ pwd
      /path/to/error_tools/build
      $ cmake --install . --prefix path/to/root/install

      # Example local user (non-admin) Linux install
      $ cmake --install . --prefix /home/$USER/.local

      # Example install to conda environment
      $ cmake --install . --prefix path/to/conda/environment/

      # Example install to W-13 CI/CD conda environment performed by CI/CD institutional account
      $ cmake --install . --prefix /projects/python/release

*****************************
Building the python interface
*****************************

A python interface to the ``error_tools`` C++ routines is provided. After the
libraries have been built, they can be linked so that they can be called with
python.

sstelmo
=======

1) Build the libraries

   .. code-block:: bash

      $ ./new_build.sh None

2) Activate a [W-13 Python Environment](https://xcp-confluence.lanl.gov/display/PYT/The+W-13+Python+3+environment)

   .. code-block:: bash

      $ sv3r

3) in the ``src/python`` directory build the interface using ``cython``

   .. code-block:: bash

      $ python setup.py build_ext --inplace
