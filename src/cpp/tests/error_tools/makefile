# Error handling library
# 
# Author: Nathan A. Miller (LANL / CU Boulder)
# Email:  nathanm@lanl.gov
# Date:   November 25, 2019
#
# This is the makefile for test_error_tools.cpp it tests the error handling tools

include ../../../../config.mk

# List of executables
EXECUTABLE=test_error_tools
TESTOBJECT=test_error_tools.o
TESTSOURCE=test_error_tools.cpp
OBJECT=error_tools.o
HEADER=../../error_tools.h
SOURCE=../../error_tools.cpp
INC+=-I../..
LOCAL_CFLAGS=-ggdb

#Set the mode due to the method variable
DBG =
ifeq ($(METHOD),dbg)
  DBG = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -g
endif
ifeq ($(METHOD),oprof)
  DBG = -pg
endif

# Makefile rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(TESTOBJECT) $(OBJECT)
	$(CXX) $(LOCAL_CFLAGS) $(INC) $(LIB) $(DBG) $^ -o $@ $(CFLAGS) -lstdc++ -std=gnu++11

$(TESTOBJECT): $(TESTSOURCE) $(HEADER)
	$(CXX) $(LOCAL_CFLAGS) $(INC) $(LIB) $(DBG) $< -c -o $@ $(CFLAGS) -lstdc++ -std=gnu++11

$(OBJECT): $(SOURCE) $(HEADER)
	$(CXX) $(LOCAL_CFLAGS) $(INC) $(LIB) $(DBG) $< -c -o $@ $(CFLAGS) -lstdc++ -std=gnu++11

clean:
	rm -f $(EXECUTABLE)
	rm $(TESTOBJECT) $(OBJECT)

.PHONY: all clean
