//Includes a bunch of defines for IR generation (just to make the parser cleaner)

#ifndef IR_GRAMMER_H
#define IR_GRAMMER_H

#define IR_MAIN_FUNC_NAME "main"

//Arithmatic - Format: ADD A1 A2 (Add A1 to A2)
#define IR_ADD "ADD "
#define IR_SUB "SUB "
#define IR_MUL "MUL "
#define IR_DIV "DIV "
#define IR_MOD "MOD"
#define IR_DEREFERENCE "LEA" //Load effective address


//Jumps - Format: JEQ A1 A2 label
#define IR_JUMP_EQUAL "JEQ"
#define IR_JUMP_NOT_EQUAL "JNE"
#define IR_JUMP_GREATER "JGT "
#define IR_JUMP_LESS "JLT"
#define IR_JUMP_GREATER_EQUAL "JGE "
#define IR_JUMP_LESS_EQUAL "JLE "
#define IR_JUMP_UNCONDITIONAL "JUM"

//Stack - Format: STK_STR A1 offset_base_ptr 
#define IR_STACK_STORE "STK_STR "
#define IR_STACK_RETRIEVE "STK_RET "
#define IR_STACK_PUSH "STK_PUSH " //Simple push operation (like in x86) 
#define IR_STACK_POP "STK_POP" 

//Labels
#define IR_LABEL "LABEL: " 

//Functions (push PC onto stack)
#define IR_JUMP_AND_LINK "JAL " //JAL label
#define IR_JUMP_RETURN "JRT " //JRT (no args)

#endif // IR_GRAMMER_H 


