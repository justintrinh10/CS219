//Programmer: Justin Trinh
//Date: 11/25/24
//Versiono: 3.0
//Purpose: PA3

#include "commandLine.h"

template<typename T>
CommandLine<T> createCommandLine(string s);

template<typename T>
bool isAri(CommandLine<T> c);

template<typename T>
bool isLog(CommandLine<T> c);

template<typename T>
bool isShi(CommandLine<T> c);

template<typename T>
void updateFlags(CommandLine<T> c);

template<typename T>
void updateNFlag(CommandLine<T> c);

template<typename T>
void updateZFlag(CommandLine<T> c);

template<typename T>
void updateCFlag(CommandLine<T> c);

template<typename T>
void updateVFlag(CommandLine<T> c);

template<typename T>
void updateRegisters(CommandLine<T> c);

template<typename T>
void executeCommand(CommandLine<T> c);

vector<string> readFile(fstream& f);
string peekOperand(string s);
void displayFlags();
void displayRegs();

int main(){
    vector<string> stringCommands = {};
    fstream f;

    f.open(INPUTFILE, ios_base::in);
    if(f.is_open()){
        stringCommands = readFile(f);
        f.close();
        for(int i = 0; i < stringCommands.size(); i ++){
            if(peekOperand(stringCommands[i]) == "ASR"){
                CommandLine<int32_t> curCommand(stringCommands[i]);
                cout << stringCommands[i] << endl;
                executeCommand(curCommand);
            }
            else{
                CommandLine<uint32_t> curCommand(stringCommands[i]);
                cout << stringCommands[i] << endl;
                executeCommand(curCommand);
            }
            cout << endl;
        }
    }
    else{
        cout << "Cannot Open File" << endl;
    }
    return 0;
}

vector<string> readFile(fstream& f){
    vector<string> destination = {};
    while(f.good()){
        string temp;
        getline(f, temp);
        destination.push_back(temp);
    }
    return destination;
}

string peekOperand(string s){
    string operand = "";
    for(int i = 0; i < 3; i ++){
        operand += toupper(s[i]);
    }
    return operand;
}

void displayFlags(){
    cout << "N: " << flags[0] << "   Z: " << flags[1] << "   C: " << flags[2] << "   V: " << flags[3] << endl;
}

void displayRegs(){
    for(int i = 0; i < NUM_REG/2; i ++){
        cout << "R" << i << ": 0x" << hex << uppercase << left << setw(12) << registers[i] << nouppercase;
    }
    cout << endl;
    for(int i = NUM_REG/2; i < NUM_REG; i ++){
        cout << "R" << i << ": 0x" << hex << uppercase << left << setw(12) << registers[i] << nouppercase;
    } 
}

template<typename T>
void updateFlags(CommandLine<T> c){
    updateNFlag(c);
    updateZFlag(c);
    updateCFlag(c);
    updateVFlag(c);
}

template<typename T>
void updateNFlag(CommandLine<T> c){
    if(c.getFlag()){
        if((c.getResult() & 0x80000000) == 0){
            flags[0] = 0;
        }
        else{
            flags[0] = 1;
        }
    }
}

template<typename T>
void updateZFlag(CommandLine<T> c){
    if(c.getFlag()){
        if(c.getResult() == 0){
            flags[1] = 1;
        }
        else{
            flags[1] = 0;
        }
    }
}

template<typename T>
void updateCFlag(CommandLine<T> c){
    if((c.getFlag()) && ((isAri(c)) || (isShi(c)))){
        if(isAri(c)){
            //subtraction case
            if((c.getOpCode() == "SUB") || (c.getOpCode() == "CMP")){
                if(registers[c.getRegA()] >= registers[c.getRegB()]){
                    //1 if subtraction results in no borrow
                    flags[2] = 1;
                }
                else{
                    flags[2] = 0;
                }
            }

            //addition case
            if(c.getOpCode() == "ADD"){
                if((c.getResult() < registers[c.getRegA()]) || (c.getResult() < registers[c.getRegB()])){
                    flags[2] = 1;
                }
                else{
                    flags[2] = 0;
                }
            }
        }

        else if(isShi(c)){
            if(c.getOpCode() == "LSL"){
                if((registers[c.getRegA()] << (c.getImmVal() - 1)) > 0x7FFFFFFF){
                    flags[2] = 1;
                }
                else{
                    flags[2] = 0;
                }
            }
            else if((c.getOpCode() == "LSR") || (c.getOpCode() == "ASR")){
                if(((registers[c.getRegA()] >> (c.getImmVal() - 1)) % 2) == 1){
                    flags[2] = 1;
                }
                else{
                    flags[2] = 0;
                }
            }
        }
    }
}

template<typename T>
void updateVFlag(CommandLine<T> c){
    if((c.getFlag()) && isAri(c)){
        //for addition
        if(c.getOpCode() == "ADD"){
            if((registers[c.getRegA()] > 0x7FFFFFFF) && (registers[c.getRegB()] > 0x7FFFFFFF) && (c.getResult() <= 0x7FFFFFFF)){
                flags[3] = 1;
            }
            else if((registers[c.getRegA()] <= 0x7FFFFFFF) && (registers[c.getRegB()] <= 0x7FFFFFFF) && (c.getResult() > 0x7FFFFFFF)){
                flags[3] = 1;
            }
            else{
                flags[3] = 0;
            }
        }

        //for subtraction
        if((c.getOpCode() == "SUB") || (c.getOpCode() == "CMP")){
            if((registers[c.getRegA()] > 0x7FFFFFFF) && ((~registers[c.getRegB()] + 1) > 0x7FFFFFFF) && (c.getResult() <= 0x7FFFFFFF)){
                flags[3] = 1;
            }
            else if((registers[c.getRegA()] <= 0x7FFFFFFF) && ((~registers[c.getRegB()] + 1) <= 0x7FFFFFFF) && (c.getResult() > 0x7FFFFFFF)){
                flags[3] = 1;
            }
            else{
                flags[3] = 0;
            }
        }
    }
}

template<typename T>
void updateRegisters(CommandLine<T> c){
    if(c.getWr()){
        registers[c.getRegWr()] = c.getResult();
    }
}

template<typename T>
void executeCommand(CommandLine<T> c){
    updateFlags(c);
    updateRegisters(c);
    displayRegs();
    cout << endl;
    displayFlags();
}

template<typename T>
bool isAri(CommandLine<T> c){
    if((c.getOpCode() == "ADD") || (c.getOpCode() == "SUB") || (c.getOpCode() == "CMP")){
        return true;
    }
    else{
        return false;
    }
    
}

template<typename T>
bool isLog(CommandLine<T> c){
    if((c.getOpCode() == "AND") || (c.getOpCode() == "ORR") || (c.getOpCode() == "XOR") || (c.getOpCode() == "TST")){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
bool isShi(CommandLine<T> c){
    if((c.getOpCode() == "ASR") || (c.getOpCode() == "LSR") || (c.getOpCode() == "LSL")){
        return true;
    }
    else{
        return false;
    }
}