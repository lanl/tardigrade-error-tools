import io
import contextlib
import difflib

import pytest

import error_tools


function_string = "some_function"
error_string = "some_error"
answer = "\n***************\n"+\
         "*    ERROR    *\n"+\
         "***************\n"+\
         "\n"+\
         "In function function\n"+\
         "\terror\n"+\
         "\n"+\
         "***************************\n"+\
         "*    END ERROR MESSAGE    *\n"+\
         "***************************\n"

data = [(function_string, error_string, answer)]

@pytest.mark.parametrize("function_string,error_string,answer",data)
def test_PyNode_print(capfd, function_string, error_string, answer):
    """
    A test of the PyNode print functionality.

    :param str function_string: The name of the function
    :param str error_string: The name of the error
    :param str answer: The expected output
    """

    node = error_tools.PyNode("function","error")

    node.print_error()

    output = capfd.readouterr().err

    assert output == answer
