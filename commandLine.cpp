template<typename T>
bool CommandLine<T>::isAri(){
    if((opCode == "ADD") || (opCode == "SUB") || (opCode == "CMP")){
        return true;
    }
    else{
        return false;
    }
    
}

template<typename T>
bool CommandLine<T>::isLog(){
    if((opCode == "AND") || (opCode == "TST") || (opCode == "ORR") || (opCode == "XOR") || (opCode == "NOT")){
        return true;
    }
    else{
        return false;
    }
}

template<typename T>
bool CommandLine<T>::isShi(){
    if((opCode == "ASR") || (opCode == "LSR") || (opCode == "LSL")){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
T CommandLine<T>::alu(){
    T operand1 = registers[regA];
    T operand2;
    if(imm){
        operand2 = immVal;
    }
    else{
        operand2 = registers[regB];
    }

    if(opCode == "ADD"){
        return operand1 + operand2;
    }
    else if((opCode == "AND") || (opCode == "TST")){
        return operand1 & operand2;
    }
    else if((opCode == "LSR") || (opCode == "ASR")){
        return operand1 >> operand2;
    }
    else if(opCode == "LSL"){
        return operand1 << operand2;
    }
    else if(opCode == "NOT"){
        return ~operand1;
    }
    else if(opCode == "ORR"){
        return operand1 | operand2;
    }
    else if((opCode == "SUB") || (opCode == "CMP")){
        return operand1 - operand2;
    }
    else if(opCode == "XOR"){
        return operand1 ^ operand2;
    }
    else if(opCode == "MOV"){
        return immVal;
    }
    else{
        return 0;
    }
}

template<class T>
CommandLine<T>::CommandLine(){
    opCode = "N/A";
    regA = -1;
    regB = -1;
    imm = false;
    immVal = -1;
    wr = false;
    regWr = -1;
    flag = false;
}

template<class T>
CommandLine<T>::CommandLine(string op, int rA, int rB, bool im, T imV, bool w, bool rW, bool f){
    opCode = op;
    regA = rA;
    regB = rB;
    imm = im;
    immVal = imV;
    wr = w;
    regWr = rW;
    flag = f;
}

template<class T>
CommandLine<T>::CommandLine(const CommandLine<T>& rhs){
    opCode = rhs.opCode;
    regA = rhs.regA;
    regB = rhs.regB;
    imm = rhs.imm;
    immVal = rhs.immVal;
    wr = rhs.wr;
    regWr = rhs.regWr;
    flag = rhs.flag;
}

template<class T>
CommandLine<T>::CommandLine(string rawCommandLine):CommandLine(){
    //getting opCode
    opCode = "";
    int i = 0;
    do{
        opCode += toupper(rawCommandLine[i]);
        i++;
    }
    while(rawCommandLine[i] != ' ' && rawCommandLine[i] != '\t');
    if(opCode[3] == 'S'){
        opCode.pop_back();
        flag = true;
    }
    if((opCode == "CMP") || (opCode == "TST")){
        flag = true;
    }

    if(isAri() || isLog() || isShi() || (opCode == "MOV")){
        //getting wr and regWr
        if((opCode != "CMP") && (opCode != "TST")){
            //getting junk
            do{
                i++;
            }
            while(rawCommandLine[i] == ' ' || rawCommandLine[i] == '\t');

            i++;
            string temp = "";
            do{
                temp += rawCommandLine[i];
                i++;
            }
            while(rawCommandLine[i] != ' ' && rawCommandLine[i] != '\0' && rawCommandLine[i] != '\t');
            wr = true;
            regWr = stoi(temp);
        }

        //getRegA
        if(opCode != "MOV"){
            //getting junk
            do{
                i++;
            }
            while(rawCommandLine[i] == ' ' || rawCommandLine[i] == '\t');

            i++;
            string temp = "";
            do{
                temp += rawCommandLine[i];
                i++;
            }
            while(rawCommandLine[i] != ' ' && rawCommandLine[i] != '\0' && rawCommandLine[i] != '\t');
            regA = stoi(temp);
        }

        //getRegB
        if(opCode != "NOT"){
            //getting junk
            do{
                i++;
            }
            while(rawCommandLine[i] == ' ' || rawCommandLine[i] == '\t');
            i++;
            
            //immediate
            if(rawCommandLine[i - 1] == '#'){
                imm = true;
            }

            string temp = "";
            do{
                temp += rawCommandLine[i];
                i++;
            }
            while(rawCommandLine[i] != ' '&& rawCommandLine[i] != '\0' && rawCommandLine[i] != '\t');

            if(imm){
                if(isShi()){
                    immVal = stoul(temp);
                }
                else{
                    immVal = stoul(temp, nullptr, 16);
                }
            }
            else{
                regB = stoi(temp);
            }
        }
    }
    else{
        cout << "CommandLine Reading Error" << endl;
    }
}

template<class T>
string CommandLine<T>::getOpCode(){
    return opCode;
}

template<class T>
int CommandLine<T>::getRegA(){
    return regA;
}

template<class T>
int CommandLine<T>::getRegB(){
    return regB;
}

template<class T>
bool CommandLine<T>::getImm(){
    return imm;
}

template<class T>
T CommandLine<T>::getImmVal(){
    return immVal;
}

template<class T>
bool CommandLine<T>::getWr(){
    return wr;
}

template<class T>
int CommandLine<T>::getRegWr(){
    return regWr;
}

template<class T>
bool CommandLine<T>::getFlag(){
    return flag;
}

template<class T>
T CommandLine<T>::getResult(){
    return alu();
}

template<class T>
void CommandLine<T>::setOpCode(string op){
    opCode = op;
}

template<class T>
void CommandLine<T>::setRegA(int rA){
    regA = rA;
}

template<class T>
void CommandLine<T>::setRegB(int rB){
    regB = rB;
}

template<class T>
void CommandLine<T>::setImm(bool im){
    imm = im;
}

template<class T>
void CommandLine<T>::setImmVal(T imV){
    immVal = imV;
}

template<class T>
void CommandLine<T>::setWr(bool w){
    wr = w;
}

template<class T>
void CommandLine<T>::setRegWr(int rW){
    regWr = rW;
}

template<class T>
void CommandLine<T>::setFlag(bool f){
    flag = f;
}