
     extern printf                  ;tell nasm that we want to call printf in this asm
     global main                    ;make main available to operating system(os)
main:
     ;create the stack frame
     push ebp
     push mov ebp, esp

     ;create local variables by reserving space on the stack
     sub esp, 0x10  ;reserve space of 16 bytes-- maybe 4 integers(4bytes*8bit=32bits)



     ;we use increment of 4 because check push is 4 bytes in length
     ;because the stack is structured to hold 32 bit(4byte) values
     ;notably address, which are 4 bytes in length
     mov DWORD [ebp-4], 0xf ;store 15 into first variable 
     mov DWORD [ebp-8], 0xff  ;255
     mov DWORD [ebp-12],0xfff ;etc

     push DWORD [ebp-4]   ;push the value stored at ebp -4 onto stack
     push DWORD msg       ;push the address of msg onto the stack
     call printf          ;call the extern, c standard library

     push DWORD [ebp-8]   ;push the value 
     push DWORD msg       ;push the address of msg onto the stack
     call printf          ;call the extern, c standard library

     push DWORD [ebp-12]   ;push the value 
     push DWORD msg       ;push the address of msg onto the stack
     call printf          ;call the extern, c standard library

     push DWORD [ebp-16]   ;push the value 
     push DWORD msg       ;push the address of msg onto the stack all printf
     call printf


     ;destroy the stack frame
     mov esp, ebp
     pop ebp
     ret 