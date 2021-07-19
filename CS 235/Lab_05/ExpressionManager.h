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
    std::vector<std::string> expVector;

    int getPrecedence(const char &myChar);

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

int ExpressionManager::getPrecedence(const char &myChar)
{
    switch (myChar)
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
    /* std::string postfix = "";
    stack<char> operatorStack;

    std::string::const_iterator iter = exp.cbegin();
    while (iter != exp.cend())
    {
        char myChar = *iter++;
        std::cout << " " << myChar;

        switch (myChar)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        {
            while (!operatorStack.empty() &&
                   this->getPrecedence(myChar) <= getPrecedence(operatorStack.top()))
            {
                postfix += operatorStack.top();
                postfix += " ";
                operatorStack.pop();
            }
            operatorStack.push(myChar);
            break;
        }

        case '(':
        case '{':
        case '[':
        {
            operatorStack.push(myChar);
            break;
        }

        case ')':
        case '}':
        case ']':
        {
            while (operatorStack.top() != '(')
            {
                postfix += operatorStack.top();
                postfix += " ";
                operatorStack.pop();
            }
            operatorStack.pop(); // Remove open paren
            break;
        }

        case ' ':
            break;
        default: // operands
            postfix += myChar;
            postfix += " ";
            break;
        }
    }

    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        postfix += " ";
        operatorStack.pop();
    }

    return postfix; */
    return "";
}

#endif