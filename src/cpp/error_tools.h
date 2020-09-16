/**
  ******************************************************************************
  * \file error_tools.h
  ******************************************************************************
  * A collection of tools for error handling in C++ code. This is a lightweight
  * library intended to cause minimal extra burden but can use very useful for
  * when code goes bad.
  ******************************************************************************
  */

#ifndef ERROR_TOOLS_H
#define ERROR_TOOLS_H

#include<memory>
#include<string>
#include<iostream>
#include<stdlib.h>

namespace errorTools{

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
}

#endif
