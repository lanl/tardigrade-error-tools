/*!
===============================================================================
|                                error_tools.h                                |
===============================================================================
| A collection of tools for error handling in C++ code. This is a lightweight |
| library intended to cause minimal extra burden but can use very useful for  |
| when code goes bad.                                                         |
===============================================================================
*/

#include<memory>
#include<string>
#include<iostream>

namespace errorTools{

    void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
                 str.replace(start_pos, from.length(), to);
                 start_pos += to.length(); // ...
        }
    }

    struct Node{
        /*!
         * A single node in the linked list chain. Contains three pieces of information:
         * 
         * functionName: The function name that the error occurred in.
         * error: A string describing the error that occurred.
         * node: A pointer to the next node in the list.
         */
        std::string functionName;
        std::string error;
        bool errorReplace = false;
        std::unique_ptr<Node> next = NULL;

        Node(std::string functionName):functionName(functionName){
            /*!
             * Create a node in the error string
             * 
             * :param std::string functionName: The function name within which the error was created
             */
        }

        Node(std::string functionName, std::string error):functionName(functionName), error(error){
            /*!
             * Create a node in the error string
             * 
             * :param std::string functionName: The function name within which the error was created
             * :param std::string error: The string discribing the error.
             */
        }

        void addNext(Node *newNode){
            /*!
             * Add another layer to the errors
             * 
             * :param Node &newNode: The new node to be added
             */
            this->next.reset(newNode);
            return;
        }

        void print(){
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
    };
}
