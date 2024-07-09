#ifndef COMPILE_H
#define COMPILE_H


#define NUMBER_OF_TOKENS 39
#define MAX_TOKEN_LENGTH 9


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "datastructures.h"
#include "static hashmap.h"
extern const char validTokens[NUMBER_OF_TOKENS][MAX_TOKEN_LENGTH];


typedef enum VALID_TOKEN_ENUM {


    USER_STRING = 0,
    INVALID_TOKEN = 1,
    TOK_INT = 2,
    TOK_FLT = 3,
    TOK_CHR = 4,


    TOK_PTR = 5,
    TOK_ADD = 6,
    TOK_SUB = 7,
    TOK_MUL = 8,
    TOK_DIV = 9,


    TOK_MOD = 10,
    TOK_OR = 11,
    TOK_AND = 12,
    TOK_EQUAL_TO = 13,
    TOK_NOT_EQUAL_TO = 14,


    TOK_GREATER_EQUAL_TO = 15,
    TOK_LESS_EQUAL_TO = 16,
    TOK_GREATER_TO = 17,
    TOK_LESS_TO = 18,
    TOK_IF = 19,


    TOK_GTO = 20,
    TOK_LBL = 21,
    TOK_FN = 22,
    TOK_RET = 23,
    TOK_ALLOCATE = 24,


    TOK_FREE = 25,
    TOK_SIZEOF = 26,
    TOK_COMMENT = 27,
    TOK_OPEN_ANGLE = 28,
    TOK_CLOSE_ANGLE = 29,


    TOK_OPEN_SQUAER = 30,
    TOK_CLOSE_SQUARE = 31,
    TOK_OPEN_PAREN = 32,
    TOK_CLOSE_PAREN = 33,
    TOK_OPEN_CURLEY = 34,


    TOK_CLOSE_CURLEY = 35,
    TOK_COMMA = 36,
    TOK_DOT = 37,
    TOK_SEMICOLEN = 38,


} VALID_TOKEN_ENUM;




typedef struct Token {

    VALID_TOKEN_ENUM tokenEnum;

    //Immediates and variables
    union {
        char *userString;       //User string (func name, variable, etc - parser must determine based on context)

        char charImmediate;     //Used if immediate char 'f'
        int intImmediate;       //Used for immediate int '3'
        float floatImmediate;   //Used for immediate float '3.32'
    };

} Token;




#endif //COMPILE_H

//NOTE: Generated by python script



