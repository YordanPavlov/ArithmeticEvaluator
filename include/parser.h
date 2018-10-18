#pragma once

#include <string>
#include "node.h"

namespace parser
{

/**
 * @brief
 * The Parser class used to read a line of input
 */
class Parser
{
private:
    BaseNodePtr result;
    char variableUsed = ' ';

    void parseInputRec(const std::string& input,
                            unsigned& index,
                            ComplexOperand& parentOperand);
public:
    // Parse a single line of equation to be calculated as read on the console
    void parseInput(const std::string& input);

    // Return the result of the parsing a complex operand (equation).
    BaseNodePtr& getResult();
};


} // namespace parser
