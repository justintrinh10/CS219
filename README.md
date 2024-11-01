# CS219-PA2

Instructions:

A makefile is included. To run the code, execute the following commands:
1) make
2) ./main.exe


Code Working Process:

1) A vector of type string is createdto hold the commands in their raw string form.
2) An array of type int is created to store the flags. It is initalize to all 0. The [0] index is for the N flag while the [2] index is for the zero flag.
3) The .txt file is read into the file.
4) Each line in the .txt file is saved into the vector.
5) The following will iterate through all elements in the vector
6) If the operation is ASR then a CommandLine object of type signed int32_t is created. Otherwise a CommandLine object of type unsigned uint32_t is created.
7) This is done by splitting up the raw string and entering them into the correct parameters. First it will get the 3 character operation and set the operation parameter equal to it. Then if the next character is an 'S' then it will set the flag parameter to true. Next it will convert the string of the first hex operand into the correct data type and enter it in. Then if it is a shifting operation the next operand is grabbed as a decimal value. If the operation is not "NOT" then it will grab the next operand as a hex value of the corresponding data type.
8) Next it will compute the result using the alu() function which has else if statements to return the result of the corresponding operation.
9) From this result the updateFlags() function is called which will update the flags accordingly. If the flag parameter is true, then it will check for updates on the flag. If the result is 0, the zero flag is set to 1, otherwise 0. If the result bitwise AND with 0x8000000 is 0, then the MSB is 1 signifying the negative flag to be set to 1, otherwise 0.
10) The result is displayed to the console.
 in an object of CommandLine and stored in the vector in a seperate index value.

Result:

1) ADD - add the two operands together using +
2) AND - bitwise AND of the two operands together using &
3) ASR - second operand value right shift of the first operand. It is a signed int32_t value so it does aritmetic right shift >>.
4) LSR - second operand value right shift of the first operand. It is an unsigned uint32_t value so it does logical right shift using >>.
5) LSL - second operand value left shift of the first operand. It is an unsigned uint32_t value so it does logical left shift using <<.
6) NOT - does bitwise NOT of first operand using !.
7) ORR - does bitwise OR between first and second operand using |.
8) SUB - does first operand - second operand.
9) XOR - does bitwise XOR between first and second operand using ^.
10) Flags - if the flag bool parameter is true then flags will updated based on the result of the operation, otherwise the flags are not affected. 
10.1) N flag - If the result bitwise AND with 0x8000000 is 0, then the MSB is 1 signifying the negative flag to be set to 1, otherwise 0.
10.2) Z flag - If the result is equal to 0, then z flag is set to 1, otherwise 0.


