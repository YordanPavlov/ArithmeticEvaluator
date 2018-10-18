#include <iostream>

// Readline library for user friendly input console
#include <readline/readline.h>
#include <readline/history.h>

#include "parser.h"

using namespace parser;

int main (int, char *[])
{
    std::cout<<"Pleace provide input or 'q' for exit"<<std::endl;

    char* line;

    while((line = readline("")) != nullptr)
    {
        if (strlen(line) > 0)
        {
          add_history(line);
        }
        else
        {
            continue;
        }

        try
        {
            if(strlen(line) == 1 && 'q' == line[0])
            {
                std::cout<<"Goodbye!"<<std::endl;
                return 0;
            }

            Parser parser;
            parser.parseInput(line);

            const parser::BaseNodePtr& parentOperand = parser.getResult();

            if(NodeType::COMPLEX != parentOperand->type)
            {
                throw std::runtime_error("Internal error. Complex operand expected.");
            }

            BaseNode* rootNode = static_cast<ComplexOperand*>(parentOperand.get())->treeifyComplex();

            if(!rootNode)
            {
                throw std::runtime_error("Internal error.");
            }
            else
            {
                std::cout<<rootNode->solve()<<std::endl;
            }
        }
        catch(std::exception& ex)
        {
            std::cout<<"Error. "<< ex.what() <<std::endl;
        }

       // readline malloc's a new buffer every time.
       free(line);
    }
}
