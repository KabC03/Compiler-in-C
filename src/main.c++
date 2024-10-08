//30 Aug 2024
#include <fstream>
#include "compiler data.h++"
#include "tokenise.h++"
#include "parse.h++"
#define SRC_FILE_PATH "./data/input.txt"
#define OUTPUT_FILE_PATH "./data/output.txt"

using namespace std;


int main(void) {


    //debug_tokenise_map_print(tokenMap);

    //File handling
    string inputString = "\0";
    int returnValue = 0;

    //Initialise structures
    TokeniserData tokenData;
    ParserData parserData;
    if(tokeniser_initialise_map(SRC_FILE_PATH, tokenData) == false) {
        goto A;
    }
    if(parser_initialise(OUTPUT_FILE_PATH, parserData) == false) {
        goto B;
    }





    for(size_t i = 0; getline(tokenData.inputFile, inputString); i++) { //Read line by line
        vector<Token> tokeniserOut = tokeniser_tokenise(inputString, tokenData);
        if(tokeniserOut.size() == 0) {
            cout << "Line: " << i << endl;
            returnValue = 3;
            break; //Error in tokeniser
        }

        //debug_tokenise_tokens_print(tokeniserOut);
        if(parser_parse(tokeniserOut, parserData) == false) {
            cout << "Line: " << i + 1 << endl;
            returnValue = 4;
            break; //Error in parser
        }
    }


    tokenData.inputFile.close();
B:
    parserData.outputFile.close();
A:

    return returnValue;
}
























