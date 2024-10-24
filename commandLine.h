#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include<iostream>
#include<string>
#include <iomanip>
#include<fstream>
#include<vector>
#include<cstdint>
using namespace std;

#define INPUTFILE "Programming-Project-1.txt"

template<class T>
class CommandLine{
    string operation;
    T operand1;
    T operand2;
    bool flag;

    T alu();
    bool calcOverflow();

    public:
        CommandLine();
        CommandLine(string op, T o1, T o2, bool f);
        CommandLine(const CommandLine<T>& rhs);

        string getOperation();
        T getOperand1();
        T getOperand2();
        bool getFlag();
        T getResult();

        void setOperation(string op);
        void setOperand1(T o1);
        void setOperand2(T o2);

        void displayOverflow();
        template<class U>
        friend ostream& operator << (ostream& out, CommandLine<U>& rhs);
};

#include "commandLine.cpp"

#endif