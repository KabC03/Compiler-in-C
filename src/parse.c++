//30 Aug 2024
#include "parse.h++"
#define APPEND_INPUT_LABEL_STR "USR"
#define OPERAND_RESERVE 10
#define LABEL_RESERVE 10
#define IF_STACK_RESERVE 10
#define internal_macro_parser_print_invalid_token(stringToPrint, tokenToPrint)  cout << stringToPrint;\
    debug_tokenise_singular_token_print(tokenToPrint);\
    cout << "" << endl;






/**
 * parser_initialise
 * ===============================================
 * Brief: Initialise register vector with empty values and set the global file pointer
 * 
 * Param: 
 *         &outputFile - Output file that will be written to
 * 
 * Return: ParserStructures 
 * 
 */
ParserStructures parser_initialise(ofstream &outputFileSet) {

    //outputFile = outputFileSet;
    ParserStructures parserStructures;
    
    
    Operand operand;
    operand.isVar = false; //Indicates position can be overwritten
    operand.memoryOffset = -1;
    operand.varName = "\0";
    parserStructures.registerStates.resize(NUMBER_OF_REGISTERS, operand); //Fill with operand

    parserStructures.operandMap.reserve(OPERAND_RESERVE);
    parserStructures.knownLabels.reserve(LABEL_RESERVE);

    return parserStructures;
}


//Parse an endif statement
bool internal_parse_endif(vector<Token> &tokens, size_t numberOfTokens, ParserStructures &parserStructures) {

    if(numberOfTokens != 1) {
        cout << "ERROR: Expected endif" << endl;
        return false;
    } else {
        if(parserStructures.ifStack.size() == 0) {
            cout << "ERROR: Expected an if statement" << endl;
            return false;
        }

        //macro_pneumonic_print_label(ifStack.top(), outputFile);
        parserStructures.ifStack.pop();
    }

    return true;
}



//Parse a label  statement
bool internal_parse_label_dec(vector<Token> &tokens, size_t numberOfTokens, ParserStructures &parserStructures) {

    //goto label
    if(numberOfTokens != 2) {
        cout << "ERROR: Expected label" << endl;
        return false;

    } else {

        //Preappend string to garuntee it will not collide with compiler labels
        tokens[1].string += APPEND_INPUT_LABEL_STR;
        auto labelMapIterator = parserStructures.knownLabels.find(tokens[1].string);

        if(labelMapIterator != parserStructures.knownLabels.end()) { //Label found
            cout << "Redefinition of '" << tokens[1].string << "'" << endl;

        } else {
            
            //macro_pneumonic_print_label(tokens[1].string, outputFile);
            parserStructures.knownLabels.insert(tokens[1].string);
            return false;
        }
    }

    return true;
}


//Parse a goto  statement
bool internal_parse_goto(vector<Token> &tokens, size_t numberOfTokens, ParserStructures &parserStructures) {

    //goto label
    if(numberOfTokens != 2) {
        cout << "ERROR: Expected label" << endl;
        return false;

    } else {

        auto labelMapIterator = parserStructures.knownLabels.find(tokens[1].string);
        if(labelMapIterator != parserStructures.knownLabels.end()) { //Label found

            //macro_pneumonic_unconditional_jump(tokens[1].string, outputFile);
        } else {

            internal_macro_parser_print_invalid_token("ERROR: Unrecognised label:", tokens[1]);
            return false;
        }

    }

    return true;
}




/**
 * parser_parse 
 * ===============================================
 * Brief: Parse a stream of tokens
 * 
 * Param: 
 *        &tokens - Tokens to be parsed
 * 
 * Return: bool - Indicating if parsing was successful
 * 
 */
bool parser_parse(vector<Token> &tokens, ParserStructures &parserStructures) {


    size_t numberOfTokens = tokens.size();
    if(numberOfTokens < 1) {
        cout << "ERROR: Insufficient tokens" << endl;
        return false;
    }

    switch(tokens[0].tokenType) {

    case TOK_DEC: {

        break;
    } case TOK_SET: {

        break;
    } case TOK_IF: {

        break;
    } case TOK_ENDIF: {
        if(internal_parse_endif(tokens, numberOfTokens, parserStructures) == false) {
            return false;
        }
        break;
    } case TOK_LABEL: {
        if(internal_parse_label_dec(tokens, numberOfTokens, parserStructures) == false) {
            return false;
        }
        break;
    } case TOK_GOTO: {
        if(internal_parse_goto(tokens, numberOfTokens, parserStructures) == false) {
            return false;
        }
        break;
    } default: {
        internal_macro_parser_print_invalid_token("ERROR: Unrecognised instruction:", tokens[0]);
        return false;
        break;
    }
    }




    return true;
}



































