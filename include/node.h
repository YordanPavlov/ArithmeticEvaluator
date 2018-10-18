#pragma once

#include <deque>
#include <memory>

namespace parser
{

enum class NodeType
{
    ADD, SUB, MUL, DIV, SIMPLE, COMPLEX
};

/**
 * @brief The BaseNode struct
 * A base class to represent both operators and operands.
 */
struct BaseNode
{
    NodeType type;

    // A link to the left and right neighbour nodes. This is useful when building a tree.
    BaseNode* leftNode;
    BaseNode* rightNode;

    // If this node is a simple operand (numeric values from 0 to 9), the data will be stored here
    int simpleData;

    BaseNode(NodeType type);

    // When building an AST we need to assign each token a weight.
    // Returns the weight for this type of node
    unsigned getWeight() const;
    // Starting from this node iterate the linked list and find the node with the lowest weight
    BaseNode* getNodeWithLowestWeight();

    // Break the linked list this node is part of and make it the head of a new list
    void makeHead();
    // Break the linked list this node is part of and make it the tail of a new list
    void makeTail();
    // Get the head of the linked list that this node is part of
    BaseNode* getHead();
    // Get the tail of the linked list that this node is part of
    BaseNode* getTail();

    // Make an AST tree out of the linked list that this node is part of
    BaseNode* treeify();
    // Solve the AST that this node is part of
    double solve();

    // Is this node an operand (number from 0 to 9 or complex operand () )
    bool isOperand() const;

};

using BaseNodePtr = std::unique_ptr<BaseNode>;

/**
 * @brief The ComplexOperand struct
 * Represents a complex operand. Example: in the equation '(1 + 2) + 3', (1 + 2) would be handled
 * as complex operand.
 */
struct ComplexOperand : public BaseNode
{
    // A storage of the member tokens
    std::deque<BaseNodePtr> innerNodes;

    ComplexOperand();

    // Upon parsing, add a new member node
    BaseNode* addMemberNode(BaseNodePtr&& operand);
    // Signal that the end bracket has been parsed. Used to validate logic.
    void endBracketParsed();

    // Treeify this complex node
    BaseNode* treeifyComplex();

};

} // namespace parser
