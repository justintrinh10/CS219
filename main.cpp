//Programmer: Justin Trinh
//Date: 10/24/24
//Purpose: PA2

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
void updateFlags(int* fls, CommandLine<T> c);

template<typename T>
void updateNFlag(int* fls, CommandLine<T> c);

template<typename T>
void updateZFlag(int* fls, CommandLine<T> c);

vector<string> readFile(fstream& f);
string peekOperand(string s);
void displayFlags(int* fls);

int main(){
    vector<string> stringCommands = {};
    fstream f;
    int flags[4] = {0, 0, 0, 0}; //[0] = N flag; [1] = Z flag
    f.open(INPUTFILE, ios_base::in);
    if(f.is_open()){
        stringCommands = readFile(f);
        f.close();
        for(int i = 0; i < stringCommands.size(); i ++){
            if(peekOperand(stringCommands[i]) == "ASR"){
                CommandLine<int32_t> curCommand;
                curCommand = createCommandLine<int32_t>(stringCommands[i]);
                updateFlags(flags, curCommand);
                cout << curCommand;
                displayFlags(flags);
            }
            else{
                CommandLine<uint32_t> curCommand;
                curCommand = createCommandLine<uint32_t>(stringCommands[i]);
                updateFlags(flags, curCommand);
                cout << curCommand;
                displayFlags(flags);
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
        operand += s[i];
    }
    return operand;
}

template<typename T>
CommandLine<T> createCommandLine(string s){
    CommandLine<T> destination;
    string op = "";
    int i = 0;
    do{
        op += s[i];
        i++;
    }
    while(s[i] != ' ' && s[i] != '\t');
    destination.setOperation(op);
    do{
        i++;
    }
    while(s[i] == ' ' || s[i] == '\t');
    string tempo1 = "";
    do{
        tempo1 += s[i];
        i++;
    }
    while(s[i] != ' ' && s[i] != '\0' && s[i] != '\t');
    destination.setOperand1(stoul(tempo1, nullptr, 16));
    if(isAri(destination) || isLog(destination)){
        do{
            i++;
        }
        while(s[i] == ' ' || s[i] == '\t');
        string tempo2 = "";
        do{
            tempo2 += s[i];
            i++;
        }
        while(s[i] != ' '&& s[i] != '\0' && s[i] != '\t');
        destination.setOperand2(stoul(tempo2, nullptr, 16));
    }
    else if(isShi(destination)){
        do{
            i++;
        }
        while(s[i] == ' ' || s[i] == '\t');
        string tempo2 = "";
        do{
            tempo2 += s[i];
            i++;
        }
        while(s[i] != ' ' && s[i] != '\0' && s[i] != '\t');
        destination.setOperand2(stoul(tempo2));
    }
    else if(destination.getOperation() != "NOT"){
        throw "CommandLine Reading Error";
    }
    return destination;
}

void displayFlags(int* fls){
    cout << "N: " << fls[0] << "   Z: " << fls[1] << endl;
}

template<typename T>
void updateFlags(int* fls, CommandLine<T> c){
    updateNFlag(fls, c);
    updateZFlag(fls, c);
}

template<typename T>
void updateNFlag(int* fls, CommandLine<T> c){
    if(c.getFlag()){
        CommandLine<T> temp("AND", c.getResult(), 0x80000000, false);
        if(temp.getResult() == 0){
            fls[0] = 0;
        }
        else{
            fls[0] = 1;
        }
    }
}

template<typename T>
void updateZFlag(int* fls, CommandLine<T> c){
    if(c.getFlag()){
        if(c.getResult() == 0){
            fls[1] = 1;
        }
        else{
            fls[1] = 0;
        }
    }
}

template<typename T>
bool isAri(CommandLine<T> c){
    if((c.getOperation() == "ADD") || (c.getOperation() == "SUB")){
        return true;
    }
    else{
        return false;
    }
    
}

template<typename T>
bool isLog(CommandLine<T> c){
    if((c.getOperation() == "AND") || (c.getOperation() == "ORR") || (c.getOperation() == "XOR")){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
bool isShi(CommandLine<T> c){
    if((c.getOperation() == "ASR") || (c.getOperation() == "LSR") || (c.getOperation() == "LSL")){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
ostream& operator << (ostream& out, CommandLine<T>& rhs){
    out << rhs.operation;
    if(rhs.getFlag()){
        out << "S";
    }
    out << right << setw(13) << hex << showbase << uppercase << rhs.operand1;
    if(isAri(rhs) || isLog(rhs)){
        out << right << setw(13) << hex << showbase << uppercase << rhs.operand2;
    }
    else if(isShi(rhs)){
        out << right << setw(13) << dec << noshowbase << rhs.operand2;
    }
    out << ":";
    out << right << setw(13) << hex << showbase << uppercase << rhs.getResult() << endl;
    out << dec << noshowbase;
    return out;
}