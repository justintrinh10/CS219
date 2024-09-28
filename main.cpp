//Programmer: Justin Trinh
//Date: 9/27/24
//Purpose: PA1

#include "commandLine.h"

template<typename T>
CommandLine<T> getCommandLine(fstream& f);

int main(){
    vector<CommandLine<uint32_t>> commands = {};
    fstream f;
    f.open(INPUTFILE, ios_base::in);
    if(f.is_open()){
        while(f.good()){
            commands.push_back(getCommandLine<uint32_t>(f));
        }
        f.close();
        for(int i = 0; i < commands.size(); i ++){
            cout << commands[i] << endl;
        }
    }
    else{
        cout << "Cannot Open File" << endl;
    }
    return 0;
}

template<typename T>
CommandLine<T> getCommandLine(fstream& f){
    string op, tempo1, tempo2;
    T o1, o2;
    f >> op;
    f >> tempo1;
    getline(f, tempo2);
    o1 = stoul(tempo1, nullptr, 16);
    o2 = stoul(tempo2, nullptr, 16);
    CommandLine<T> out(op, o1, o2);
    return out;
}

template<class T>
ostream& operator << (ostream& out, CommandLine<T>& rhs){
    out << rhs.operation;
    out << right << setw(13) << hex << showbase << uppercase << rhs.operand1;
    out << right << setw(13) << hex << showbase << uppercase << rhs.operand2;
    out << ":";
    out << right << setw(13) << hex << showbase << uppercase << rhs.getResult() << endl;
    out << "Overflow: ";
    rhs.displayOverflow();
    out << endl;
    return out;
}