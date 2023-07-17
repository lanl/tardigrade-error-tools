. _user_manual:

###########
User Manual
###########

***********
Quick Start
***********

Two methods currently exist for error handling within the error_tools library. The first is the
construction of linked lists which can be used to unwind errors to the root cause and the second,
which is the path going forward, are macros which enable systematic catching of exceptions such
that a stack trace can be generated. This second method is believed to be more general than the
linked list approach and also requires less custom software to implement.

Exception Handling
------------------

`error_tools.h` contains macros which will be used by the pre-processor to substitute in code at
compile time. The two macros of importance here are `TARDIGRADE_ERROR_TOOLS_CATCH` and
`TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER`. The first macro can be used to wrap exceptions or function calls
that may cause exceptions to provide stack information on error. The second macro can be used to
convert the old, linked-list, style method to the exception format. By way of example, we present
a simple block of code which demonstrates the utility.::

    void badFunction( ){
        TARDIGRADE_ERROR_TOOLS_CATCH( throw std::logic_error( "oops" ) ); //LN1
    }
    
    void containsBadFunction( ){
        TARDIGRADE_ERROR_TOOLS_CATCH( badFunction( ) ); // LN2
    }
    
    void goodFunction( ){
        return;
    }

    void test_form_stacktrace( ){

        try{
            TARDIGRADE_ERROR_TOOLS_CATCH( containsBadFunction( ) ); //LN3
        }
        catch( std::exception &e ){
            errorTools::printNestedExceptions( e );
        }

    }

On execution of `test_form_stacktrace` the output would be similar to::

    3 : oops
    2 : myfile.cpp ( LN1 ): badFunction
    1 : myfile.cpp ( LN2 ): containsBadFunction
    0 : myfile.cpp ( LN3 ): test_form_stacktrace

where `myfile.cpp` is the name of the file which was compiled and `LN#` represents the function's
line number. The first line is the message thrown by the original error which should help in
debugging.

Node interface
--------------

In addition to the more modern, and recommended, method presented above we also provide a macro
`TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER` to enable interface with the older `error_tools` utility.
Historically errors were handled by returning pointers to the last member of a linked list of
`errorTools::Node` objects i.e.,::

    errorTools::Node *error = myFunction( ... )
    
    if ( error ){ //Checks if the pointer is not NULL
        
        errorTools::Node *result = new errorTools::Node( __func__, "My error message" ); //Func is a macro that gives the current funtion name
    
        result->addNext( error );
    
        return result;
    
    }

This is effective but requires development and maintinence of a class. For functions which use the
old `errorTools::Node` based system one can do the following::

    TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER( myFunction( ... ) );

which will convert the `errorTools::Node*` to an exception. We will provide this utility until all
of the node-based approaches have been removed from the libraries.
