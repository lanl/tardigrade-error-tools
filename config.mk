# Micromorphic filter, a variationally based filter for DNS
#
# Author: Nathan A. Miller (LANL / CU Boulder)
# Email:  nathanm@lanl.gov
# Date:   July 13, 2018
#
# This is the common configuration file for all of the included makefiles

# C++ compiler
CXX=icc

# Flags for the C++ compiler
CFLAGS=-std=c++11 -Wall -ansi -pedantic -O3 -I. -fmax-errors=5

# Location of the Eigen library
EIGEN=-I$(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))/../eigen)

# The python command
PYTHON=/apps/anaconda3/bin/python
