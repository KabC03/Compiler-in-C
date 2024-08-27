
//Parser - generates IR

#ifndef PARSE_H 
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "../libraries/return codes.h"
#include "../libraries/datastructures.h"
#include "compiler data.h"
#include "../libraries/string hashmap.h"
#include "architecture pneumonics.h"
#include "tokenise.h"
#include "register.h"

typedef struct VariableData { //Could definitely optimise the 'inUse' member but make it more readable for now
    //Held within the variableStorage string hashmap
    size_t baseOffset;     //Where the variable is stored on the stack
    size_t registerNumber; //Which register the variable is stoed in (-1 if not stored in register)
    size_t timesRequested; //Times this variable has been used (higher usage means it will stay in registers longer)
    bool inUse;            //If this register space is in use (to specify empty space in register state vector)

} VariableData;

RETURN_CODE parse_initialise(void);
RETURN_CODE parse(Vector *tokens, FILE *irOut);


#endif //PARSE_H



