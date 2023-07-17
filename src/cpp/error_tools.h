/**
  ******************************************************************************
  * \file error_tools.h
  ******************************************************************************
  * A collection of tools for error handling in C++ code. This is a lightweight
  * library intended to cause minimal extra burden but can use very useful for
  * when code goes bad.
  ******************************************************************************
  */

#ifndef TARDIGRADE_ERROR_TOOLS_H
#define TARDIGRADE_ERROR_TOOLS_H

#include<memory>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<sstream>
#include<stdexcept>


/*!
    \brief Formatting of each line of the stacktrace
    \param message: The std::string message to be appended to
    \param func: A standard string or char function name
    \param line: The integer filename
    \param file: A standard string or char filename
*/
#define STACKTRACE_FORMAT(message, func, line, file)                               \
        message += file;                                                           \
        message += " ( ";                                                          \
        message += std::to_string( line );                                         \
        message += " ): ";                                                         \
        message += func;                                                           \

/*!
    \brief An internal macro to catch exceptions and add additional information
           Not intended to be used in user code 
    \param expr: The expression to be evaluated
    \param func: A standard string or char function name
    \param line: The integer filename
    \param file: A standard string or char filename
*/
#define TARDIGRADE_ERROR_TOOLS_CATCH_INTERNAL(expr, func, line, file)                         \
    try{                                                                           \
        expr;                                                                      \
    }                                                                              \
    catch(const std::exception &e){                                                \
        std::string message;                                                       \
        STACKTRACE_FORMAT(message, func, line, file)                               \
        std::throw_with_nested(std::runtime_error( message ));                     \
    }                                                                              \
    catch(...){                                                                    \
        std::string message;                                                       \
        STACKTRACE_FORMAT(message, func, line, file)                               \
        std::throw_with_nested(std::runtime_error( message ));                     \
    }                                                                              \


/*!
    \brief A macro to catch exceptions and add additional information
    \param expr: The expression to be evaluated
*/
#define TARDIGRADE_ERROR_TOOLS_CATCH(expr) TARDIGRADE_ERROR_TOOLS_CATCH_INTERNAL(expr, __func__, __LINE__, __FILE__)

/*!
    \brief An internal macro to catch tardigradeErrorTools::Node pointers and convert them to exceptions
           Not intended to be used in user code 
    \param expr: The expression to be evaluated that returns a pointer
        to an tardigradeErrorTools::Node object
    \param func: A standard string or char function name
    \param line: The integer filename
    \param file: A standard string or char filename
*/
#define TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER_INTERNAL(expr, func, line, file)            \
    if ( expr ){                                                                   \
        std::stringstream buffer;                                                  \
        std::streambuf * old = std::cerr.rdbuf( buffer.rdbuf( ) );                 \
        expr->print( );                                                            \
        std::string message = buffer.str( );                                       \
        std::cerr.rdbuf( old );                                                    \
        STACKTRACE_FORMAT(message, func, line, file)                               \
        throw std::runtime_error( message );                                       \
    }                                                                              \

/*!
    \brief A macro to catch tardigradeErrorTools::Node pointers and convert them to exceptions
    \param expr: The expression to be evaluated
*/
#define TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER(expr) TARDIGRADE_ERROR_TOOLS_CATCH_NODE_POINTER_INTERNAL(expr, __func__, __LINE__, __FILE__)


namespace tardigradeErrorTools{

    void replaceAll(std::string& str, const std::string& from, const std::string& to);

    /**
      * A single node in the linked list chain. Contains three pieces of information:
      *
      * \param functionName: The function name that the error occurred in.
      * \param error: A string describing the error that occurred.
      * \param node: A pointer to the next node in the list.
      */
    class Node{

        private:

            std::string functionName;
            std::string error;
            bool errorReplace = false;
            std::unique_ptr<Node> next;

        public:

            /**
              * The default constructor
              */
            Node(){
            }
            /**
              * Create a node in the error string
              *
              * \param functionName std::string The function name within which the error was created
              */
            Node(std::string functionName):functionName(functionName){
            }

            /**
              * Create a node in the error string
              *
              * \param functionName std::string The function name within which the error was created
              * \param error std::string The string discribing the error.
              */
            Node(std::string functionName, std::string error):functionName(functionName), error(error){
            }

            void addNext(Node *newNode);

            void addNext( std::unique_ptr< Node > &newNode );

            void print( const bool header = true );
    };

    void printNestedExceptions( const std::exception &e, std::size_t depth = 0, std::string message = "");

}


#endif
