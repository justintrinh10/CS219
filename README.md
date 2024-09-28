# CS219-PA1

Instructions:

A makefile is included. To run the code, execute the following commands:
1) make
2) ./main.exe


Code Working Process:

1) A vector of type CommandLine of type uint32_t is created.
2) The .txt file is read into the file.
3) Each line in the .txt file is saved in an object of CommandLine and stored in the vector in a seperate index value.
   The CommandLine class has an attribute for the operation as a string and both operands as a seperate attribute of type uint32_t.
   When getting the hex values from the .txt file it is first grabbed as a string and directly convered into a decimal number.
4) The program outputs every CommandLine object. This is done using an operator overload.
   This outputs each attribute of the CommandLine object and then outputs the result of the operation. This is done by calling the alu() method which performs the operation and returns the result (Only ADD operation is implemented, others can be implemented later).
   It then outputs whether an overflow has occured. This is done by checking if the result is smaller that either of the original operands.


Result:

1) 0X1 + 0X1 = 0X2
   The result is correct, therefore no overflow occured.
2) 0XAAA5555 + 0X555AAAA = 0XFFFFFFF 
   The result is correct, therefore no overflow occured.
3) 0XFFFFFFFF + 0X1 = 0X0
   The result is incorrect, therefore an overflow occured. This is beacause the result exceeds the bounds of an unsigned 32 bit number.
4) 0X1234 + 0X8765 = 0X9999
   The result is correct, therefore no overflow occured.
5) 0X72DF9901 + 0X2E0B484A = 0XA0EAE14B
   The result is correct, therefore no overflow occured.


