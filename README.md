# CS219-PA3

Instructions:

A makefile is included. To run the code, execute the following commands:
1) make
2) ./main.exe


Code Working Process:

1) A vector of type string is created to hold the commands in their raw string form.
2) A global array of type int is created to store the flags. It is initalize to all 0. The [0] index is for the N flag while the [1] index is for the zero flag. The [2] index is for the C flag. The [3] index is for the V flag.
3) A global array of type uint32_t is created to store the values in the registers 0-7.
4) The .txt file is read into the file.
5) Each line in the .txt file is saved into the vector.
6) The following will iterate through all elements in the vector
7) If the operation is ASR then a CommandLine object of type signed int32_t is created. Otherwise a CommandLine object of type unsigned uint32_t is created.
8) This is done by entering the raw string into a special constructor that will make its parameters match what is requested of it in the raw string. 
8.1) First it calls the default constructor too initalize every parameter to 0 or false. 
8.2) Next it will get the 3 character operation and set the opCode parameter equal to it. Then if the next character is an 'S' then it will set the flag parameter to true.
8.3) If the opCode is not TST or CMP, it will grab the write back register and set the corresponding parameter equal to it. Then the write enable is set to true.
8.4) If the opCode is not MOV, it will grab the register A and set the corresponding parameter equal to it.
8.5) If the opCode is not NOT, it will grab register B.
8.5.1) If it starts with a '#', it is an immdiate value and the value collected will put into the immediate value parameter while the immediate value bool is set to true. 
8.5.2) If it starts with a 'R', then it will be put into the register B parameter.
9) Next the raw string is displayed to the console.
10) Then the flags are updated by calling the updateFlags() function that calls all of the corresponding flag functions if the flag bool is true.
10.1) For N flag, if the result of the alu() for the assembly line bitwise AND with 0x80000000 is 0, that means the MSB is 0 so the N flag is set to 0, else it is set to 1.
10.2) For Z flag, if the result of the alu() is 0, the Z flag is set to 1, else it is set to 0.
10.3) For C flag
10.3.1) If it is an "ADD" opCode, if the result of the alu() is smaller than both the values stored in register A and register B, the flag is set to 1, else 0.
10.3.2) If it is a "SUB" or "CMP" opCode, if the value in register A is greater than or equal to the value in register B, the flag is set to 1, else 0.
10.3.3) If it is "LSL", if the MSB before the final shift is 1, the flag is set to 1, otherwise 0.
10.3.4) If it is "LSR" or "ASR", if the LSB before the final shift is 1, the flag is set to 1, otherwise 0.
10.4) For V flag
10.4.1) If it is "ADD", if the two values of registers A and B have the same MSB but the MSB of the result of the alu() is different, the V flag is set to 1, otherwise 0.
10.4.2) If it is "SUB" or "CMP", do the same as with "ADD", but use the 2's compliment of register B instead (not of register B + 1).
11) If the write bool is true, the write back register is updated to the result of the alu().
12) The updated flags and registers are displayed to the console.

Result:

1) MOV R1, #0x72DF9901
set R1 to 0x72DF9901
does not affect flags

2) MOV R2, #0x2E0B484A
set R2 to 0x2E0B484A
does not affect flags

3) ADDS R3, R1, R2
set R3 to R1 + R2 = 0xA0EAE14B
N: 1   Z: 0   C: 0   V: 1

4) SUBS R4, R3, R2
set R4 to R3 - R2 = 0x72DF9901
N: 0   Z: 0   C: 1   V: 1

5) mov r0, #0xAAA5555
set R0 to 0xAAA5555
does not affect flags

6) ands r0, r0, r4
set R0 to bitwise and of R0 and R4 = 0x28A1101
N: 0   Z: 0

7) orr r0, r2, r3
set R0 to bitwise or of R2 and R3 = 0xAEEBE94B
does not affect flags

8) xor r5, r3, r4
set R5 to bitwise xor of R3 and R4 = 0xD235784A
does not affect flags

9) MOV R6, #0xFFFFFFFF
set R6 to 0xFFFFFFFF
does not affect flags

10) lsrs R7, R6, #2
set R7 to R6 logical right shift by 2 bits = 0x3FFFFFFF
N: 0   Z: 0   C: 1

11) LSLS R6, R7, #1
set R6 to R7 logical left shift by 1 bit = 0x7FFFFFFE
N: 0   Z: 0   C: 0

12) CMP R6, R7
does not change registers, changes flags based on R6 - R7
N: 0   Z: 0   C: 1   V: 0

13) tst R3, R4
does not change registers, changes flags based on bitwise and of R3 and R4
N: 0   Z: 0


