from libcpp.string cimport string
from libcpp cimport bool


cdef extern from "tardigrade_error_tools.h" namespace "tardigradeErrorTools":
    cdef cppclass Node:
        Node() except +
        Node(string&, string&) except +
        void c_print "print"(const bool)
