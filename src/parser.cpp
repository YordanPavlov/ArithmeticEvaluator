#include <iostream>
#include <cstring>
#include <sstream>

#include "parser.h"

namespace parser
{

void Parser::parseInputRec(const std::string& input,
                        unsigned& index,
                        ComplexOperand &parentOperand)
{
    for(; index<input.size(); ++index)
    {
        if('(' == input[index])
        {
            BaseNode* newOperand = parentOperand.addMemberNode(BaseNodePtr(new ComplexOperand()));
            parseInputRec(input,
                          ++index,
                          *(static_cast<ComplexOperand*>(newOperand)));
        }
        else if(')' == input[index])
        {
            parentOperand.endBracketParsed();
            return;
        }
        else if('+' == input[index])
        {
            parentOperand.addMemberNode(BaseNodePtr(new BaseNode(NodeType::ADD)));
        }
        else if('*' == input[index])
        {
            parentOperand.addMemberNode(BaseNodePtr(new BaseNode(NodeType::MUL)));
        }
        else if('-' == input[index])
        {
            parentOperand.addMemberNode(BaseNodePtr(new BaseNode(NodeType::SUB)));
        }
        else if('/' == input[index])
        {
            parentOperand.addMemberNode(BaseNodePtr(new BaseNode(NodeType::DIV)));
        }
        else if(' ' == input[index])
        {
            // SKIP SPACE
        }
        else if(input[index] >= '0' && input[index] <= '9')
        {
            // Depend on the ascii table ordering of symbols
            double number = input[index] - '0';

            BaseNode* newOperand = parentOperand.addMemberNode(BaseNodePtr(new BaseNode(NodeType::SIMPLE)));
            newOperand->simpleData = number;
        }
        else
        {   std::stringstream errorMsg;
            errorMsg << "Unexpected character " << input[index];
            throw std::runtime_error( errorMsg.str() );
        }
    }
}

void Parser::parseInput(const std::string& input)
{
      result.reset(new ComplexOperand());

      unsigned index = 0;

      parseInputRec(input,
                    index,
                    *(static_cast<ComplexOperand*>(result.get())));

      if(index < input.size())
      {
           throw std::runtime_error("Misplaced closing parentheses");
      }
}

BaseNodePtr& Parser::getResult()
{
    return result;
}

} // namespace parser
