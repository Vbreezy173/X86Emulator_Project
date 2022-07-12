This program is a X86 8/16-bit emulator written in C++. x86 is a family of complex instruction set computer (CISC) instruction set architectures initially 
developed by Intel based on the Intel 8086 microprocessor and its 8088 variant. The goal of this project was to emulate some features of the X86.\
The program implements the following features-
1. General-Purpose Registers (GPR).
<p align="center">
  <img src="https://user-images.githubusercontent.com/89701605/178577684-dca14655-1221-4a07-a66a-ea02edf5221e.png" />
</p>
2. Memory. <br/>
3. Instruction Pointer (IP register).
<p align="center">
  <img src="https://user-images.githubusercontent.com/89701605/178578594-39c42ca2-d27d-4e4d-b1aa-805aaab8aa63.png" />
</p>

The program takes a x86 assembly code file compiled to machine code (.com) and exuctues the commands.
The program can execuate the following X86 instructions-
1. XCHG
2. ADD
3. SUB
4. MOV
5. INC
6. DEC
7. INT 21h

Each instruction moves data to and from the registers and depending on the data in the register certain operation can be done. An example is displaying "Hello World".
I have provided 3 .com files as examples that can be used in this program to be run. 
