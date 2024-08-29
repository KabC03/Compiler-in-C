//30 Aug 2024
//Includes macros for assembly generation by parser
//Some architectures may require multiple lines to perform the same operations as others

#ifndef ARCHITECTURE_PNEUMONICS_HH
#define ARCHITECTURE_PNEUMONICS_HH

#define NUMBER_OF_REGISTERS 5 //Number of general purpose registers
#define STACK_DATASIZE 4
/*
Note: 
If stack pointer is not available,
should use one of the general purpose registers in macros below (not allow compiler to use it for storage)
*/








//Arithmatic - Assign a destination register to a src register
/*
If in architecture that has accumulator registers only (e.g x86) can do this:

E.g add ebx, ecx into eax

add eax 0   //Zero the destination
add eax ebx //Add first argument
add eax ecx //Add second argument
*/

#define internal_macro_load_immediate(regDest, immediate, destFptr)\
    if(fprintf(destFptr, "LOD R%zu %d\n",regDest, immediate) < 0) {/*printf("HERE");*/ return _INTERNAL_ERROR_;}

#define internal_macro_move(regDest, rSrc, destFptr)\
    if(fprintf(destFptr, "MOV R%zu R%zu\n",regDest, rSrc) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_addition(regDest, rSrc, destFptr)\
    if(fprintf(destFptr, "ADD R%zu R%zu\n",regDest, rSrc) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_subtraction(regDest, rSrc, destFptr)\
    if(fprintf(destFptr, "SUB R%zu R%zu\n",regDest, rSrc) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_multiplication(regDest, rSrc, destFptr)\
    if(fprintf(destFptr, "MUL R%zu R%zu\n",regDest, rSrc) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_division(regDest, rSrc, destFptr)\
    if(fprintf(destFptr, "DIV R%zu R%zu\n",regDest, rSrc) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_modulo(regDest, rSrc, destFptr)\
    if(fprintf(destFptr, "MOD R%zu R%zu\n",regDest, rSrc) < 0) {return _INTERNAL_ERROR_;}




//Conditional logic - Jump to a label if the condition is met
/*
NOTE: If in architecture that requires flags (e.g x86) can do the following:

E.g - compare eax and ebx, if equal jump to my_label

cmp eax ebx
je my_label
*/

#define internal_macro_equal_to(labelToJumpTo, regSrc1, regSrc2, destFptr)\
    if(fprintf(destFptr, "EQA R%zu R%zu %s\n",regSrc1, regSrc2, labelToJumpTo) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_not_equal_to(labelToJumpTo, regSrc1, regSrc2, destFptr)\
    if(fprintf(destFptr, "NEQ R%zu R%zu %s\n",regSrc1, regSrc2, labelToJumpTo) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_less_than(labelToJumpTo, regSrc1, regSrc2, destFptr)\
    if(fprintf(destFptr, "LES R%zu R%zu %s\n",regSrc1, regSrc2, labelToJumpTo) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_greater_than(labelToJumpTo, regSrc1, regSrc2, destFptr)\
    if(fprintf(destFptr, "GRT R%zu R%zu %s\n",regSrc1, regSrc2, labelToJumpTo) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_greater_equal(labelToJumpTo, regSrc1, regSrc2, destFptr)\
    if(fprintf(destFptr, "GRE R%zu R%zu %s\n",regSrc1, regSrc2, labelToJumpTo) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_less_equal(labelToJumpTo, regSrc1, regSrc2, destFptr)\
    if(fprintf(destFptr, "LTE R%zu R%zu %s\n",regSrc1, regSrc2, labelToJumpTo) < 0) {return _INTERNAL_ERROR_;}



//Memory operations - Store and load from memory - offset from a base pointer
#define internal_macro_save(reg, offset, destFptr)\
    if(fprintf(destFptr, "save R%zu RBP %zu\n",reg, offset) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_load(reg, offset, destFptr)\
    if(fprintf(destFptr, "load R%zu RBP %zu\n",reg, offset) < 0) {return _INTERNAL_ERROR_;}



//Functions - Call and return from a function
#define internal_macro_call_function(labelToCall, destFptr)\
    if(fprintf(destFptr, "call %s\n",labelToCall) < 0) {return _INTERNAL_ERROR_;}

#define internal_macro_return_function(destFptr)\
    if(fprintf(destFptr, "ret\n\n") < 0) {return _INTERNAL_ERROR_;}



#endif // ARCHITECTURE_PNEUMONICS_HH






