#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_IDENTIFIER,
    TOKEN_END,
    TOKEN_INVALID
} TokenType;


typedef struct {
    TokenType type;
    char value[64];
} Token;


Token getNextToken(const char **input) {
    Token token;
    while (isspace(**input)) (*input)++; 

    if (isdigit(**input)) { 
        token.type = TOKEN_NUMBER;
        int i = 0;
        while (isdigit(**input) && i < 63) {
            token.value[i++] = *(*input)++;
        }
        token.value[i] = '\0'; 
    } else if (isalpha(**input)) { 
        token.type = TOKEN_IDENTIFIER;
        int i = 0;
        while (isalnum(**input) && i < 63) {
            token.value[i++] = *(*input)++;
        }
        token.value[i] = '\0'; 
    } else if (**input == '+' || **input == '-') { 
        token.type = TOKEN_OPERATOR;
        token.value[0] = *(*input)++;
        token.value[1] = '\0'; 
    } else if (**input == '\0') { 
        token.type = TOKEN_END;
        token.value[0] = '\0'; 
    } else { 
        token.type = TOKEN_INVALID;
        token.value[0] = *(*input)++;
        token.value[1] = '\0'; 
    }
    return token;
}


int main() {
    const char *input = "x + 42 - y"; 
    const char *p = input; 
    Token token;

   
    while ((token = getNextToken(&p)).type != TOKEN_END) {
        printf("Token: Type=%d, Value='%s'\n", token.type, token.value);
    }

    return 0; 
}