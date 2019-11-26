/*!
===============================================================================
|                               error_tools.cpp                               |
===============================================================================
| A collection of tools for error handling in C++ code. This is a lightweight |
| library intended to cause minimal extra burden but can use very useful for  |
| when code goes bad.                                                         |
===============================================================================
*/

#include<error_tools.h>

namespace errorTools{

    void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
                 str.replace(start_pos, from.length(), to);
                 start_pos += to.length(); // ...
        }
    }

    void Node::addNext(Node *newNode){
        /*!
         * Add another layer to the errors
         * 
         * :param Node &newNode: The new node to be added
         */
        this->next.reset(newNode);
        return;
    }
 
    void Node::print(){
        /*!
         * Print the errors in a list of nodes.
         * 
         * :param Node* error: A node in the chain
         *
         */
    
        std::cerr << "In function " << functionName << "\n";
 
        if (!errorReplace){
            replaceAll(error, "\n", "\n\t");
            errorReplace = true;
        }
 
        std::cerr << "\t" << error << "\n";
 
        if (next != NULL){
            next->print();
        }
 
        return;
    }
}
