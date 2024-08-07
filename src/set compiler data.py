# 10, Jul, 24
# This file generates the compiler data.h and compiler data.c files
import sys


#Print a newline every newLineConstant lines in the .c and .h files
newLineConstant = 5;


defineNameNumberOfTokens = "NUMBER_OF_TOKENS";
defineNameMaxTokenLength = "MAX_TOKEN_LENGTH";
tokenStruct = """

typedef struct Token {

    VALID_TOKEN_ENUM tokenEnum;

    //Immediates and variables
    union {
        DynamicString userString;  //User string (func name, variable, etc - parser must determine based on context)

        char charImmediate;        //Used if immediate char 'f'
        int intImmediate;          //Used for immediate int '3'
        float floatImmediate;      //Used for immediate float '3.32'
    };

} Token;
""";


outputFolder = "./src/";

hFile = "compiler data.h";
cFile = "compiler data.c";
headerGuardName = "COMPILE_H";


#Tokens to pre-append (Appear in .h but not .c file)
tokensPreappend = [

    "EOF_TOKEN",
    "INT_IMMEDIATE",
    "FLOAT_IMMEDIATE",
    "CHAR_IMMEDIATE",
    "USER_STRING",

];


#Tokens to append to the files
tokens = {

    #Internal types
    "invalid" : "INVALID_TOKEN",

    #Datatypes
    "int" : "TOK_INT", "flt" : "TOK_FLT", "chr" : "TOK_CHR", "@" : "TOK_PTR", "=" : "TOK_EQUALS_ASSIGNMENT",

    #Operators
    "+" : "TOK_ADD", "-" : "TOK_SUB", "*" : "TOK_MUL", "/" : "TOK_DIV","\%" : "TOK_MOD","||" : "TOK_OR", "&&" : "TOK_AND",
    "==" : "TOK_EQUAL_TO", "!=" : "TOK_NOT_EQUAL_TO", ">=" : "TOK_GREATER_EQUAL_TO", "<=" : "TOK_LESS_EQUAL_TO", ">>" : "TOK_GREATER_TO", "<<" : "TOK_LESS_TO", 


    #Control flow
    "if" : "TOK_IF", "gto" : "TOK_GTO", "lbl" : "TOK_LBL",

    #Functions
    "fn" : "TOK_FN", "ret" : "TOK_RET",

    #Inbuilt functions
    "allocate" : "TOK_ALLOCATE", "free" : "TOK_FREE", "sizeof" : "TOK_SIZEOF",

    #Organisation
    "//" : "TOK_COMMENT",

    #Misc
    "<" : "TOK_OPEN_ANGLE", ">" : "TOK_CLOSE_ANGLE", "[" : "TOK_OPEN_SQUAER", "]" : "TOK_CLOSE_SQUARE", 
    "(" : "TOK_OPEN_PAREN", ")" : "TOK_CLOSE_PAREN", "{" : "TOK_OPEN_CURLEY", "}" : "TOK_CLOSE_CURLEY", 
    "," : "TOK_COMMA", "." : "TOK_DOT", ";" : "TOK_SEMICOLEN", "\'" :"TOK_SINGLE_QUOTE",
};

numberOfTokens = 0;
maxTokenSize = 0;




librariesToInclude = [

    "<stdlib.h>",
    "<stdio.h>",
    "<stdbool.h>",
    "<string.h>",
    "<stdint.h>",
    "\"../libraries/vector.h\"",
    "\"../libraries/datastructures.h\"",
    "\"../libraries/static hashmap.h\"",
    "\"../libraries/dynamic string.h\"",
];



#Write to the .h file
def write_h_file():

    try:
        
        with open(str(outputFolder + hFile), 'w') as file:
        
            #Write header guards
            file.write("#ifndef " + str(headerGuardName) + "\n");
            file.write("#define " + str(headerGuardName) + "\n\n\n");

            #Define constants
            file.write("#define " + str(defineNameNumberOfTokens) + " " + str(numberOfTokens) + "\n");
            file.write("#define " + str(defineNameMaxTokenLength) + " " + str(maxTokenSize) + "\n\n\n");


            #Include libraries
            for library in librariesToInclude:
                file.write("#include " + str(library) + "\n");

            file.write("extern const char validTokens[" + str(defineNameNumberOfTokens) + "][" + str(defineNameMaxTokenLength) + "];\n" ) 

            file.write("\n\ntypedef enum VALID_TOKEN_ENUM {\n\n");


            counter = -1;
            for token in tokensPreappend:
                
                if (-1 * counter) % newLineConstant == 0:
                    file.write("\n\n");
                file.write("    " + str(token) + " = " + str(counter) + ",\n");
                counter -= 1;

            counter = 0;
            for value in tokens.values():

                if counter % newLineConstant == 0:
                    file.write("\n\n");

                file.write("    " + str(value) + " = " + str(counter) + ",\n");
                counter += 1;

            file.write("\n\n} VALID_TOKEN_ENUM;\n");


            file.write("\n\n" + str(tokenStruct) + "\n\n");




            file.write("\n\n#endif //" + str(headerGuardName) + "\n\n");
            file.write("//NOTE: Generated by python script\n\n\n\n");






        return True; 
    
    
    except:
        return False;




#Write to the .c file
def write_c_file():

    global numberOfTokens;
    global maxTokenSize;

    numberOfTokens = len(tokens);
    maxTokenSize = 0;
    for token in tokens:
        if len(token) > maxTokenSize:
            maxTokenSize = len(token);

    maxTokenSize += 1; #Make space for NULL terminator

    try:
        with open(str(outputFolder + cFile), 'w') as file:
            file.write("#include " + "\"" + str(hFile) + "\"\n\n\n");


            file.write("const char validTokens[" + str(defineNameNumberOfTokens) + "][" + str(defineNameMaxTokenLength) + "] = {\n");

            counter = 0;
            for key in tokens.keys():

                if counter % newLineConstant == 0:
                    file.write("\n\n\n\n    ");

                file.write("\"" + key + "\",");
            
                counter += 1;

            file.write("\n\n};\n\n");
        
            file.write("//NOTE: Generated by python script\n\n\n\n");
        return True; 
    
    
    except:
        return False;



#Main function
def main():
    
    if(write_c_file() == False):
        print("Failed to write data to .c file: " + str(cFile));
        return -1;


    if(write_h_file() == False):
        print("Failed to write data to .c file: " + str(hFile));
        return -2;


    return 0;







if __name__ == "__main__":
    sys.exit(main());




