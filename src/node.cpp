#include <iostream>
#include <cstring>

#include "node.h"
#include "utils.h"

namespace parser
{

BaseNode::BaseNode(NodeType _type)
:
type(_type),
leftNode(nullptr),
rightNode(nullptr),
simpleData(0)
{
}

/**
 * @brief BaseNode::getWeight
 *
 * Depending on the type of the node return its order of operation. Lower weights will
 * pop-up higher in the AST
 */
unsigned BaseNode::getWeight() const
{
    switch(type)
    {
        case NodeType::SUB:
            return 1;
        case NodeType::ADD:
            return 2;
        case NodeType::MUL:
            return 3;
        case NodeType::DIV:
            return 4;
        case NodeType::SIMPLE:
            return 5;
        case NodeType::COMPLEX:
            return 6;
    }
    throw std::runtime_error( "Internal Error. Unhandled case.");
}

BaseNode* BaseNode::getNodeWithLowestWeight()
{
    if(!rightNode)
    {
        throw std::runtime_error( "Internal Error. Lowest order search on empty list.");
    }

    BaseNode* rootNode = this;
    for  (BaseNode* iter = rootNode->rightNode;
          iter != nullptr;
          iter = iter->rightNode)
    {
        if (iter->getWeight() < rootNode->getWeight())
        {
            rootNode = iter;
        }
    }

    return rootNode;
}

BaseNode* BaseNode::getHead()
{
    if (leftNode)
    {
        return leftNode->getHead();
    }
    else
    {
        return this;
    }
}

BaseNode* BaseNode::getTail()
{
    if (rightNode)
    {
        return rightNode->getTail();
    }
    else
    {
        return this;
    }
}

void BaseNode::makeHead()
{
    leftNode = nullptr;
}

void BaseNode::makeTail()
{
    rightNode = nullptr;
}

BaseNode* BaseNode::treeify()
{
    // Should be called on head nodes only
    if(leftNode)
    {
        throw std::runtime_error( "Internal Error. Treeify invoked on non-head node");
    }

    // The last node
    if (!rightNode)
    {
        if(NodeType::COMPLEX == type)
        {
            return static_cast<ComplexOperand*>(this)->treeifyComplex();
        }
        else
        {
            return this;
        }
    }

    BaseNode* rootNode = getNodeWithLowestWeight();

    if(!rootNode->leftNode || !rootNode->rightNode)
    {
        // The case of a single node in this list is handled above.
        // Here we expect at least 3 nodes and the operator node should be picked.
        // It should be a 'middle' node so we expect it to have both left and right nodes.
        throw std::runtime_error( "Internal error. Could not pick root node.");
    }

    // At this point we break up the list into two separate lists
    // The right node becomes the head of a new list. While the left node becomes
    // the tail of another list.
    rootNode->rightNode->makeHead();
    rootNode->leftNode->makeTail();

    // Starting from the heads of the both new lists, treeify them and attach them to the
    // root node we built at this step. This is the recursive step.
    rootNode->leftNode = rootNode->leftNode->getHead()->treeify();
    rootNode->rightNode = rootNode->rightNode->treeify();

    // Upon completion of the recursion we are done
    return rootNode;
}

double BaseNode::solve()
{
    if( NodeType::SIMPLE == type)
    {
        return simpleData;
    }
    else if( NodeType::COMPLEX == type)
    {
        throw std::runtime_error( "Internal error. No complex operands should have remained after treeify.");
    }
    else
    {
        if(!leftNode || !rightNode)
        {
            throw std::runtime_error( "Internal error. Both left and right nodes expected.");
        }

        double leftValue = leftNode->solve();
        double rightValue = rightNode->solve();

        switch(type)
        {
            case NodeType::SUB:
                return safeSubtract(leftValue, rightValue);
            case NodeType::ADD:
                return safeAdd(leftValue, rightValue);
            case NodeType::MUL:
                return safeMul(leftValue, rightValue);
            case NodeType::DIV:
            {
                if(0 == rightValue)
                {
                    throw std::runtime_error( "Division by zero.");
                }
                return leftValue / rightValue;
            }
            default:
                throw std::runtime_error( "Internal error. Unknown operation.");
        }
    }
}

bool BaseNode::isOperand() const
{
    return (NodeType::SIMPLE == type || NodeType::COMPLEX == type);
}

///// ComplexOperand /////

ComplexOperand::ComplexOperand()
:
BaseNode(NodeType::COMPLEX)
{
}

bool typesMatchOrder(const BaseNode* nodeLeft, const BaseNode* nodeRight)
{
    // The order is for operator to follow operand to follow operator
    return nodeLeft->isOperand() != nodeRight->isOperand();
}

BaseNode* ComplexOperand::addMemberNode(BaseNodePtr&& operand)
{
    if(!innerNodes.empty())
    {
        innerNodes.back()->rightNode = operand.get();
        operand->leftNode = innerNodes.back().get();
    }

    if(innerNodes.empty())
    {
        if((NodeType::SIMPLE != operand->type) &&
           (NodeType::COMPLEX != operand->type))
        {
            throw std::runtime_error( "Operator parsed at start of expression.");
        }
    }
    else
    {
        if(!typesMatchOrder(innerNodes.back().get(), operand.get()))
        {
            throw std::runtime_error( "The order or literals is not met.");
        }
    }

    innerNodes.emplace_back(std::move(operand));

    return innerNodes.back().get();
}

void ComplexOperand::endBracketParsed()
{
    if(innerNodes.empty())
    {
        throw std::runtime_error( "Empty brackets are not supported.");
    }
    else if(!innerNodes.back()->isOperand())
    {
        throw std::runtime_error( "Last token in expression is not an operand.");
    }
}

BaseNode* ComplexOperand::treeifyComplex()
{
    if(innerNodes.empty())
    {
        throw std::runtime_error( "Expression is empty.");
    }

    return innerNodes.front()->treeify();
}

} // namespace parser
