/**
  ******************************************************************************
  * \file error_tools.cpp
  ******************************************************************************
  * A collection of tools for error handling in C++ code. This is a lightweight
  * library intended to cause minimal extra burden but can use very useful for
  * when code goes bad.
  ******************************************************************************
  */

#include<error_tools.h>

namespace errorTools{

    void replaceAll( std::string& str, const std::string& from, const std::string& to ) {
        size_t start_pos = 0;
        while ( ( start_pos = str.find( from, start_pos ) ) != std::string::npos ) {
            str.replace( start_pos, from.length( ), to );
            start_pos += to.length( ); // ...
        }
    }

    /**
      * Add another layer to the errors
      *
      * Will be depreciated because it encourages unsafe coding practices
      *
      * \param Node &newNode: The new node to be added
      */
    void Node::addNext( Node *newNode ){
        this->next.reset( newNode );
        return;
    }

    /**
      * Add another layer to the errors
      *
      * \param Node &newNode: The new node to be added
      */
    void Node::addNext( std::unique_ptr< Node > &newNode ){
        this->next = std::move( newNode );
        return;
    }

    /**
      * Print the errors in a list of nodes.
      *
      * \param header const bool Flag which indicates if the header
      *     should be printed
      *
      */
    void Node::print( const bool header ){
        if ( header ){
            std::cerr << "\n***************\n";
            std::cerr <<   "*    ERROR    *\n";
            std::cerr <<   "***************\n\n";
        }

        std::cerr << "In function " << functionName << "\n";

        if ( !errorReplace ){
            replaceAll( error, "\n", "\n\t" );
            errorReplace = true;
        }

        std::cerr << "\t" << error << "\n";

        if ( next != NULL ){
            next->print( false );
        }

        if ( header ){
            std::cerr << "\n***************************\n";
            std::cerr <<   "*    END ERROR MESSAGE    *\n";
            std::cerr <<   "***************************\n";
        }

        return;
    }
}
