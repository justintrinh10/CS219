#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include<iostream>
#include<string>
#include <iomanip>
#include<fstream>
#include<vector>
#include<cstdint>
using namespace std;

#define INPUTFILE "Programming-Project-3.txt"
#define NUM_REG 8

//Global Variables
int flags[4] = {}; //[0] = N flag; [1] = Z flag; [2] = C flag; [3] = V flag
uint32_t registers[NUM_REG] = {}; //r0-rNUM_REG registers

template<class T>
class CommandLine{
    string opCode;
    int regA;
    int regB;

    bool imm;
    T immVal;

    bool wr;
    int regWr;

    bool flag;

    bool isAri();
    bool isLog();
    bool isShi();

    T alu();

    public:
        CommandLine();
        CommandLine(string op, int rA, int rB, bool im, T imV, bool w, bool rW, bool f);
        CommandLine(const CommandLine<T>& rhs);
        CommandLine(string rawCommandLine);

        string getOpCode();
        int getRegA();
        int getRegB();
        bool getImm();
        T getImmVal();
        bool getWr();
        int getRegWr();
        bool getFlag();
        T getResult();

        void setOpCode(string op);
        void setRegA(int rA);
        void setRegB(int rB);
        void setImm(bool im);
        void setImmVal(T imV);
        void setWr(bool w);
        void setRegWr(int rW);
        void setFlag(bool f);
};

#include "commandLine.cpp"

#endif