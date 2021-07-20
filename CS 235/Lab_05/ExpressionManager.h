#ifndef EXPRESSIONMANAGER_H_
#define EXPRESSIONMANAGER_H_

#include <vector>
#include <iostream>
#include <sstream>

#include "ExpressionManagerInterface.h"

class ExpressionManager : public ExpressionManagerInterface
{
private:
    std::string expression;
    std::vector<string> expVector;

    int getPrecedence(const std::string &tokenChar);

public:
    ExpressionManager(std::string expression) : ExpressionManagerInterface(), expression(expression) {}
    ~ExpressionManager() {}

    virtual int value() { return 1; }

    /** Return the infix items from the expression
		Throw an error if not a valid infix expression as follows:
		First check to see if the expression is balanced ("Unbalanced"),
		then throw the appropriate error immediately when an error is found
		(ie., "Missing Operand", "Illegal Operator", "Missing Operator") */
    virtual std::string
    infix()
    {
        std::istringstream expStream(expression);
        std::string token;
        while (expStream >> token)
        {
            expVector.push_back(token);
        }

        return this->toString();
    }

    /** Return a postfix representation of the infix expression */
    virtual std::string postfix();

    /** Return a prefix representation of the infix expression */
    virtual std::string prefix()
    {
        return "";
    }

    /** Return the infix vector'd expression items */
    virtual std::string toString() const
    {
        std::ostringstream os;
        for (size_t i = 0; i < expVector.size(); ++i)
        {
            os << " " << expVector[i];
        };
        return os.str();
    }

    /**
     * @return an ostream with the contents of the infix vector
     */
    friend std::ostream &
    operator<<(std::ostream &os, ExpressionManager &obj)
    {
        os << obj.toString();
        return os;
    }
};

int ExpressionManager::getPrecedence(const std::string &token)
{
    char tokenChar = token[0]; // func is only called when token is 1 character

    switch (tokenChar)
    {
    case '+':
    case '-':
        return 1;
        break;

    case '*':
    case '/':
    case '%':
        return 2;
        break;

    default: // (, [, { etc.
        return 0;
        break;
    }
}

std::string ExpressionManager::postfix()
{
    std::string postfix = "";
    std::stack<std::string> operatorStack;

    for (size_t i = 0; i < expVector.size(); ++i)
    {
        string token = expVector[i];

        // Arithmetic operators
        if (token.compare("+") == 0 ||
            token.compare("-") == 0 ||
            token.compare("*") == 0 ||
            token.compare("/") == 0 ||
            token.compare("%") == 0)
        {
            while (!operatorStack.empty() &&
                   this->getPrecedence(token) <= getPrecedence(operatorStack.top()))
            {
                postfix += operatorStack.top();
                postfix += " ";
                operatorStack.pop();
            }
            operatorStack.push(token);
        }

        // Open braces
        else if (token.compare("(") == 0 ||
                 token.compare("{") == 0 ||
                 token.compare("[") == 0)
        {
            operatorStack.push(token);
        }

        // Close braces
        else if (token.compare(")") == 0 ||
                 token.compare("}") == 0 ||
                 token.compare("]") == 0)
        {
            while (!operatorStack.top().compare("("))
            {
                postfix += operatorStack.top();
                postfix += " ";
                operatorStack.pop();
            }
            operatorStack.pop(); // Remove open paren
        }

        // Operands
        else
        {
            postfix += token;
            postfix += " ";
        }
    }

    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        postfix += " ";
        operatorStack.pop();
    }

    return postfix;
}

#endif