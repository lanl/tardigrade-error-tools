from libcpp.string cimport string

cimport error_tools


cdef class PyNode:
    cdef Node* c_node

    def __cinit__(self, function_name = "", error_message = ""):
        cdef string c_function_name = bytearray(function_name, 'utf-8')
        cdef string c_error_message = bytearray(error_message, 'utf-8')

        if (function_name == "") or (error_message == ""):
            self.c_node = new error_tools.Node()
        else:
            self.c_node = new error_tools.Node(c_function_name, c_error_message)

    def __dealloc__(self):
        del self.c_node

    def print_error(self):

        try:
            if self.c_node:
                self.c_node.c_print(True)
        except:
            raise ValueError("Error not defined")
