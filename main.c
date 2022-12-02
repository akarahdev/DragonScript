#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dragon.h"

char tokens[1000][50]; // token list
int enableDebug = 1; // is debug logs enabled? | 0 = false | 1 = true

char fileContent[50000];

void lexer(FILE* readerFile);
void compile();
void savefile();


int FILE_SIZE_M = 50000;
int ARG_SIZE_M = 100;
int FILE_SIZE = 50000;
int ARG_SIZE = 100;

char variableList[1000][50];
int variableListIndex = 0;

int main(int argc, int *argv[]) {
    if(argc != 2) {
        printf("You supplied bad arguments, sorry.\n");
        printf("Please specify a file name without a space.");
        return 1;
    }
    // output c file to exportedscript.c
    // export exe file to ds.exe
    FILE* readerFile;
    char buf[100];

    snprintf(buf, 90, "%s", argv[1]);
    readerFile = fopen(buf, "r");
    if(readerFile == NULL) {
        printf("File is null, sorry.");
        return 1;
    }
    printf("Reading file %s\n", argv[1]);

    lexer(readerFile);
    

    fclose(readerFile);

    return 0;
}

void lexer(FILE* readerFile) {
    char ch;
    int tokenAmountCount = 0; // the amount of tokens
    int tokenCharCount = 0; // the character index of token
    int inComment = 0; // if you are in comment | 0 = false | 1 = true
    int inWhitespace = 0; // if you are in whitespace before an token. | 0 = false | 1 = true
    int inString = 0; // if you are in a string. | 0 = false | 1 = true

    char tokenList[30][256] = {
        "int\0",
        "print\0",
        "set\0",
        "if\0",
        "else\0",
        "setstr\0",
        "str\0",
        "query\0"
    };

    char operands[30][256] = {
        "==\0",
        ">=\0",
        "<=\0",
        "!=\0",
        "=\0",
        "+\0",
        "-\0",
        "*\0",
        "/\0",
        "^\0"
    };

    char* currentToken = calloc(256, sizeof(char));
    char* regenToken = calloc(256, sizeof(char));
    while (ch != EOF) {
        ch = fgetc(readerFile);
        // if the current character is a space, check to make a new command
        // if the token matches one of the tokenList's indexes, make a new command
        if(ch == ' ') {
            // if we are not in a string or a comment...
            if(inString == 0) {
                if(inComment == 0) {
                    // check for new commands using tokenList
                    for(int i = 0; i<30; i++) {
                        if(strcmp(currentToken, tokenList[i]) == 0) {
                            snprintf(regenToken, 256, "COMMAND:%s", currentToken);
                            strcpy(tokens[tokenAmountCount], regenToken);
                            if(enableDebug == 1) { printf("%s! (inString %d)\n", tokens[tokenAmountCount], inString); }
                            tokenCharCount = 0;
                            inComment = 0;
                            tokenAmountCount += 1;
                            inWhitespace = 1;
                        }
                    }
                    // check for operands via operands list
                    for(int i = 0; i<30; i++) {
                        if(strcmp(currentToken, operands[i]) == 0) {
                            snprintf(regenToken, 256, "OPERAND:%s", currentToken);
                            strcpy(tokens[tokenAmountCount], regenToken);
                            if(enableDebug == 1) { printf("%s! (inString %d)\n", tokens[tokenAmountCount], inString); }
                            tokenCharCount = 0;
                            inComment = 0;
                            tokenAmountCount += 1;
                            inWhitespace = 1;
                        }
                    }
                }
            }
            
        }
        // set the current token's current character to the current character of the file
        if(ch >= 32 && ch <= 125) {
            currentToken[tokenCharCount] = ch; 
            tokenCharCount += 1; // go to the next character
        }
    }
    free(currentToken);
    free(regenToken);
    compile();
        /* if(ch == '\n') {
            snprintf(tokens[tokenAmountCount], 256, "COMMAND:%s", tokens[tokenAmountCount]);
            if(enableDebug == 1) { printf("%s! (inString %d)\n", tokens[tokenAmountCount], inString); }
            tokenCharCount = 0;
            inComment = 0;
            tokenAmountCount += 1;
            inWhitespace = 1;
        } else if (ch == '(' || ch == ')' || ch == ',') {
            snprintf(tokens[tokenAmountCount], 256, "ARG:%s", tokens[tokenAmountCount]);
            if(enableDebug == 1) { printf("%s! (inString %d)\n", tokens[tokenAmountCount], inString); }
            tokenCharCount = 0;
            inComment = 0;
            tokenAmountCount += 1;
            inWhitespace = 1;

            tokens[tokenAmountCount][tokenCharCount] = ch;
            tokenCharCount += 1;

            tokenCharCount = 0;
            inComment = 0;
            tokenAmountCount += 1;
            inWhitespace = 1;

        } else {
            switch(ch) {
                case '"':
                    if(inString == 0) {
                        inString = 1;
                    } else {
                        inString = 0;
                    }
                    break;
                case ';':
                    tokenCharCount = 0;
                    inComment = 1;        
                    break; 
                case ' ':
                    if(inWhitespace == 0) {
                        if(inString == 0) {
                            if(inComment == 0) {
                                snprintf(tokens[tokenAmountCount], 256, "STRING:%s", tokens[tokenAmountCount]);
                                if(enableDebug == 1) { printf("%s! (inString %d)\n", tokens[tokenAmountCount], inString); }
                                tokenCharCount = 0;
                                inComment = 0;
                                tokenAmountCount += 1;
                                inWhitespace = 1;
                            }
                        } else {
                            inWhitespace = 0;
                            tokens[tokenAmountCount][tokenCharCount] = ch;
                            tokenCharCount += 1;
                        }
                        
                    }
                    break;
                default:
                    if(inComment == 0) {
                        inWhitespace = 0;
                        tokens[tokenAmountCount][tokenCharCount] = ch;
                        tokenCharCount += 1;
                    }
                    break;          
            }
        } */ 
    
}

void compile() {
    strcpy(fileContent, "#include<stdio.h>\n#include<string.h>\n#include<stdlib.h>\n\n int main() {\n");
    for(int i = 0; i<999; i++) {
        int* pI = &i;
        // TODO switch statement
        char input[100];
        strncpy(input, tokens[i], ARG_SIZE_M);
        if(strcmp(input, "int") == 0) { dragonscript_int(pI); } 
        else if(strcmp(input, "COMMAND:str") == 0) { dragonscript_str(pI);} 
        else if(strcmp(input, "COMMAND:set") == 0) { dragonscript_set(pI); } 
        else if(strcmp(input, "COMMAND:setstr") == 0) { dragonscript_setstr(pI); } 
        else if(strcmp(input, "COMMAND:print") == 0) { dragonscript_print(pI); } 
        else if(strcmp(input, "COMMAND:query") == 0) { dragonscript_query(pI); }
        else if(strcmp(input, "COMMAND:free") == 0) { dragonscript_free(pI); }
        else if(strcmp(input, "COMMAND:if") == 0) { dragonscript_if(pI); }
        else if(strcmp(input, "COMMAND:}") == 0) { snprintf(fileContent, FILE_SIZE_M, "%s}", fileContent); }
    }
    snprintf(fileContent, FILE_SIZE_M, "%s \nprintf(\"\\nPress ENTER to exit.\"); \ngetchar(); \nreturn 0;\n }", fileContent);
    printf("%s", fileContent);
    printf("\nlen: %d", strlen(fileContent));
    savefile();
}

void savefile() {
    FILE* writeFile;
    writeFile = fopen("dragonsave.c", "w");
    fputs(fileContent, writeFile);
    fclose(writeFile);
    system("gcc dragonsave.c -o mydragonscript.exe");
}


























void dragonscript_int(int* i) {
    char var[ARG_SIZE];
    strncpy(var, tokens[*i+1], ARG_SIZE);
    printf("INT STATEMENT: var: %s\n", var);
    snprintf(fileContent, FILE_SIZE, "%s int* %s = malloc(sizeof(int));\n", fileContent, var);
}
void dragonscript_str(int* i) {
    char var[ARG_SIZE];
    strncpy(var, tokens[*i+1], ARG_SIZE);
    printf("STR STATEMENT: var: %s\n", var);
    snprintf(fileContent, FILE_SIZE, "%s char* %s = calloc(2048, sizeof(char));\n", fileContent, var);
}

void dragonscript_set(int* i) {
    char* var = malloc(sizeof(char) * ARG_SIZE);
    strncpy(var, tokens[*i+1], ARG_SIZE);
    char* operator = malloc(sizeof(char) * ARG_SIZE);;
    strncpy(operator, tokens[*i+2], ARG_SIZE);
    char* value = malloc(sizeof(char) * ARG_SIZE);;
    strncpy(value, tokens[*i+3], ARG_SIZE);
    printf("SETINT STATEMENT: var: %s | operator: %s | value: %s\n", var, operator, value);
    snprintf(fileContent, FILE_SIZE, "%s %s %s %s;\n", fileContent, var, operator, value);
    free(var);
    free(operator);
    free(value);
}

void dragonscript_setstr(int* i) {
    char* var = malloc(sizeof(char) * ARG_SIZE);
    strncpy(var, tokens[*i+1], ARG_SIZE);
    char* operator = malloc(sizeof(char) * ARG_SIZE);
    strncpy(operator, tokens[*i+2], ARG_SIZE);
    char* value = malloc(sizeof(char) * ARG_SIZE);
    strncpy(value, tokens[*i+3], ARG_SIZE);
    printf("SETSTR STATEMENT: var: %s | operator: %s | value: \"%s\"\n", var, operator, value);
    snprintf(fileContent, FILE_SIZE, "%s strncpy(%s, \"%s\", 2048);\n", fileContent, var, value);
    free(var);
    free(operator);
    free(value);
}

void dragonscript_print(int* i) {
    char* out = malloc(sizeof(char) * 1000);
    strncpy(out, tokens[*i+1], 1000);
    
    int* inBrace;
    inBrace = (int *)malloc(sizeof(int));
    inBrace[0] = 0;
    int* varCount;
    varCount = (int *)malloc(sizeof(int));
    varCount[0] = 0;
    int* varCharCount;
    varCharCount = (int *)malloc(sizeof(int));
    varCharCount[0] = 0;
    // varRangeStart and varRangeEnd delete the ${} from each out, replacing them with %s/%d
    int* newOutRange; // character index counter for newOut
    newOutRange = (int *) malloc(sizeof(int));
    newOutRange[0] = 0;
    printf("PRINT STATEMENT: out: %s strlen: %d\n", out, strlen(out));
    char varSave[10][100];
    printf("strlen %d", strlen(out));
    char* newOut = calloc(1000, sizeof(char));
    // search for the variables, and replace them
    for(int i2 = 0; i2<strlen(out); i2++) {
        // start searching when $str{ for string
        if(out[i2] == '$' &&
            out[i2+1] == 's' &&
            out[i2+2] == 't' &&
            out[i2+3] == 'r' &&
            out[i2+4] == '{') {
            i2 += 4;
            if(inBrace[0] == 0) {
                inBrace[0] = 1;
            }
            newOut[newOutRange[0]] = '%';
            newOut[newOutRange[0]+1] = 's';
            newOutRange[0] += 2;
        // start searching when $int{ for integer
        } else if(out[i2] == '$' && 
            out[i2+1] == 'i' && 
            out[i2+2] == 'n' && 
            out[i2+3] == 't' && 
            out[i2+4] == '{') {
            i2 += 4;
            if(inBrace[0] == 0) {
                inBrace[0] = 1;
            }
            newOut[newOutRange[0]] = '%';
            newOut[newOutRange[0]+1] = 'd';
            newOutRange[0] += 2;
        // end searching when }
        } else if(out[i2] == '}') {
            if(inBrace[0] == 1) {
                inBrace[0] = 0;
                varSave[varCount[0]][varCharCount[0]] = '\0';
                printf("my thingy is: %s", varSave[varCount[0]]);
                varCount[0] += 1;
            }
        // when searching, add each char to varSave
        } else {
            if(inBrace[0] == 1) {
                printf("int: %d\n", out[i2]);
                if(out[i2] >= 65 && out[i2] <= 122) {
                    varSave[varCount[0]][varCharCount[0]] = out[i2]; //name
                    varCharCount[0] += 1;
                }
            } else {
                newOut[newOutRange[0]] = out[i2];
                newOutRange[0] += 1;
            }
        }
    }
    strncpy(out, newOut, 1000);
    free(newOut); // free newOut
    char* append = calloc(1024, sizeof(char)); // the string to append to the end of the printf statement
    // prepare append variable, adding ", %s" of each varSave index
    if(varCount[0] > 0) {
        for(int i3=0; i3<varCount[0]; i3++) {
            if(i3 == 0) {
                snprintf(append, 1024, "%s", varSave[i3]);
                printf("\nvarsave is %s", varSave[i3]);
            } else {
                snprintf(append, 1024, "%s , %s", append, varSave[i3]);
                
                printf("\nvarsave is %s", varSave[i3]);
            }
            
            printf("\n\n\nAppend is %s\n\n\n", append);
        }
        snprintf(fileContent, FILE_SIZE, "%s\nprintf(\"%s\", %s);", fileContent, out, append);
    } else {
        snprintf(fileContent, FILE_SIZE, "%s\nprintf(\"%s\");", fileContent, out);
    }
    
    
    // free variables
    free(varCount);
    free(varCharCount);
    free(inBrace);
    free(append);
    free(out);
}

void dragonscript_query(int* i) {
    char* var = malloc(sizeof(char) * ARG_SIZE_M);
    strncpy(var, tokens[*i+1], ARG_SIZE_M);
    snprintf(fileContent, FILE_SIZE_M, "%s\nfgets(%s, 2048, stdin);", fileContent, var);
}

void dragonscript_free(int* i) {
    char* var = malloc(sizeof(char) * ARG_SIZE_M);
    strncpy(var, tokens[*i+1], ARG_SIZE_M);
    var[strlen(var)-1] = '\0';
    snprintf(fileContent, FILE_SIZE_M, "%s\nfree(%s);", fileContent, var);
}

void dragonscript_if(int* i) {
    char* condition = malloc(sizeof(char) * ARG_SIZE_M);
    strncpy(condition, tokens[*i+1], ARG_SIZE_M);
    char* operand = malloc(sizeof(char) * ARG_SIZE_M);
    strncpy(operand, tokens[*i+2], ARG_SIZE_M);
    char* comparison = malloc(sizeof(char) * ARG_SIZE_M);
    strncpy(comparison, tokens[*i+3], ARG_SIZE_M);
    // var[strlen(var)-1] = '\0';
    printf("IF STATEMENT: condition: %s | operand: %s | comparison: %s", condition, operand, comparison);
    snprintf(fileContent, FILE_SIZE_M, "%s\nfree(%s);", fileContent, condition);
}