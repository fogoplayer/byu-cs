#ifndef EXPRESSIONMANAGER_H_
#define EXPRESSIONMANAGER_H_

#include <vector>
#include <stack>
#include <iostream>
#include <sstream>

#include "ExpressionManagerInterface.h"

class ExpressionManager : public ExpressionManagerInterface
{
private:
    std::string expression;
    std::vector<string> expVector;
    std::vector<string> postfixVector;
    int operatorCount;
    int operandCount;

    int
    getPrecedence(const std::string &tokenChar);
    void balanceCheck();
    void otherChecks();
    int aOperatorB(std::string a, std::string b, std::string operatorString);

public:
    ExpressionManager(std::string expression) : ExpressionManagerInterface(), expression(expression)
    {
    }
    ~ExpressionManager() {}

    virtual int value();

    /** Return the infix items from the expression
		Throw an error if not a valid infix expression as follows:
		First check to see if the expression is balanced ("Unbalanced"),
		then throw the appropriate error immediately when an error is found
		(ie., "Missing Operand", "Illegal Operator", "Missing Operator") */
    virtual std::string infix()
    {
        // Push to Vector
        std::istringstream expStream(expression);
        std::string token;
        while (expStream >> token)
        {
            expVector.push_back(token);
        }

        //Error checking
        // this->balanceCheck();
        // this->otherChecks();

        return this->toString();
    }

    /** Return a postfix representation of the infix expression */
    virtual std::string postfix();

    /** Return a prefix representation of the infix expression */
    virtual std::string prefix();

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

void ExpressionManager::balanceCheck()
{
    std::stack<char> grouperStack;
    for (size_t i = 0; i < expVector.size(); ++i)
    {
        std::string token = expVector[i];
        if (token.compare("(") == 0 ||
            token.compare("{") == 0 ||
            token.compare("[") == 0)
        {
            grouperStack.push(token[0]); // convert token to char
        }
        else if (token.compare(")") == 0 ||
                 token.compare("}") == 0 ||
                 token.compare("]") == 0)
        {
            if ((token[0] - 1) == grouperStack.top()) // open always has the char code 1 lower than close
            {
                grouperStack.pop(); // If they match, pop it
            }
            else
            {
                throw std::string("Unbalanced");
            }
        }
    }
    if (grouperStack.size() > 0) // Check if all open operators are accounted for
    {
        throw std::string("Unbalanced");
    }
}

void ExpressionManager::otherChecks()
{
    for (size_t i = 0; i < expVector.size(); ++i)
    {
        string token = expVector[i];

        // Missing Operand
        if (token.compare("+") == 0 ||
            token.compare("-") == 0 ||
            token.compare("*") == 0 ||
            token.compare("/") == 0 ||
            token.compare("%") == 0)
        {
            size_t charBeforeIsAnOperand = string("1234567890(){}[]").find(expVector[i - 1]);
            size_t charAfterIsAnOperand = string("1234567890(){}[]").find(expVector[i + 1]);
            if (charBeforeIsAnOperand == string::npos || charAfterIsAnOperand == string::npos)
            {
                throw std::string("Missing Operand");
            }
        }

        // Illegal Operator
        if (string("+-*/%(){}[]123457890").find(token[0]) == string::npos)
        {
            throw std::string("Illegal Operator");
        }

        //Missing Operator
        if (string("1234567890").find(token[0]) != string::npos)
        {
            // Check token before unless first token
            size_t charBeforeIsAnOperand = i == 0 ? 0 : string("+-*/%(){}[]").find(expVector[i - 1]);
            // Check token after unless last token
            size_t charAfterIsAnOperand = i == expVector.size() - 1 ? 0 : string("+-*/%(){}[]").find(expVector[i + 1]);

            if (charBeforeIsAnOperand == string::npos || charAfterIsAnOperand == string::npos)
            {
                throw std::string("Missing Operand");
            }
        }
    }
}

int ExpressionManager::aOperatorB(std::string a, std::string b, std::string operatorString)
{
    int aInt, bInt;
    std::istringstream args(a + " " + b);
    args >> aInt >> bInt;

    if (operatorString == "+")
    {
        return aInt + bInt;
    }
    if (operatorString == "-")
    {
        return aInt - bInt;
    }
    if (operatorString == "*")
    {
        return aInt * bInt;
    }
    if (operatorString == "/")
    {
        return aInt / bInt;
    }
    if (operatorString == "%")
    {
        return aInt % bInt;
    }

    return 0;
}

int ExpressionManager::value()
{
    std::stack<std::string> operandStack;
    for (size_t i = 0; i < postfixVector.size(); i++)
    {
        if (string("+-*/%").find(postfixVector[i]) != std::string::npos)
        {
            std::string operand = postfixVector[i];
            std::string b = operandStack.top();
            operandStack.pop();
            std::string a = operandStack.top();
            operandStack.pop();
            operandStack.push(std::to_string(aOperatorB(a, b, postfixVector[i])));
        }
        else
        {
            operandStack.push(postfixVector[i]);
        }
    }
    std::istringstream is(operandStack.top());
    int finalVal;
    is >> finalVal;
    return finalVal;
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
                postfixVector.push_back(operatorStack.top());
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
            while (operatorStack.top()[0] != token[0] - 1 && operatorStack.top()[0] != token[0] - 2)
            {
                postfixVector.push_back(operatorStack.top());
                postfix += operatorStack.top();
                postfix += " ";
                operatorStack.pop();
            }
            operatorStack.pop(); // Remove open paren
        }

        // Operands
        else
        {
            postfixVector.push_back(token);
            postfix += token;
            postfix += " ";
        }
    }

    while (!operatorStack.empty())
    {
        postfixVector.push_back(operatorStack.top());
        postfix += operatorStack.top();
        postfix += " ";
        operatorStack.pop();
    }

    return postfix;
}

std::string ExpressionManager::prefix()
{
    std::string prefix = "";
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
            prefix = " " + token + prefix;
        }

        // Operands
        if (string("1234567890").find(token[0]) != string::npos)
        {
            prefix += " " + token;
        }

        // Open braces
        if (token.compare("(") == 0 ||
            token.compare("{") == 0 ||
            token.compare("[") == 0)
        {
            //snip out parenthetical
            std::ostringstream os;
            for (i = i + 1; i < expVector.size(); i++)
            {
                if (expVector[i][0] - 1 == token[0] || expVector[i][0] - 1 == token[0])
                {
                    break;
                }

                os << " " << expVector[i];
            }

            ExpressionManager tempExpManager(os.str());
            tempExpManager.infix();
            prefix += tempExpManager.prefix();
        }
    }

    return prefix;
}
#endif