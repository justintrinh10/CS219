template<class T>
T CommandLine<T>::alu(){
    if(operation == "ADD"){
        return operand1 + operand2;
    }
    else{
        return 0;
    }
}

template<class T>
bool CommandLine<T>::calcOverflow(){
    if((operand1 > alu()) || (operand2 > alu())){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
CommandLine<T>::CommandLine(){
    operation = "N/A";
    operand1 = 0;
    operand2 = 0;
}

template<class T>
CommandLine<T>::CommandLine(string op, T o1, T o2){
    operation = op;
    operand1 = o1;
    operand2 = o2;
}

template<class T>
CommandLine<T>::CommandLine(const CommandLine<T>& rhs){
    operation = rhs.operation;
    operand1 = rhs.operand1;
    operand2 = rhs.operand2;
}

template<class T>
string CommandLine<T>::getOperation(){
    return operation;
}

template<class T>
T CommandLine<T>::getOperand1(){
    return operand1;
}

template<class T>
T CommandLine<T>::getOperand2(){
    return operand2;
}

template<class T>
T CommandLine<T>::getResult(){
    return alu();
}

template<class T>
void CommandLine<T>::setOperation(string op){
    operation = op;
}

template<class T>
void CommandLine<T>::setOperand1(T o1){
    operand1 = o1;
}

template<class T>
void CommandLine<T>::setOperand2(T o2){
    operand2 = o2;
}

template<class T>
void CommandLine<T>::displayOverflow(){
    if(calcOverflow()){
        cout << "yes";
    }
    else{
        cout << "no";
    }
}