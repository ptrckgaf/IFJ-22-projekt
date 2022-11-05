#ifndef IFJ_22_PROJEKT_UTILS_H
#define IFJ_22_PROJEKT_UTILS_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * error codes definition
 */
#define LEX_ERR 1;
#define SYN_ERR 2;
#define UNDEF_FUNC_ERR 3;
#define PARAMS_ERR 4;
#define UNDEF_VAR_ERR 5;
#define TERM_ERR 6;
#define TYPE_ERR 7;
#define SEM_ERR 8;
#define INT_ERR 99;

extern int ERROR_CODE;

/*
 *  token types definition
 */
typedef enum{
    TOKEN_ID,
    TOKEN_FUN_ID,
    TOKEN_VAR_ID,
    TOKEN_TYPE_ID,

    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_FLOAT,
    TOKEN_KEYWORD_FUNCTION,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_NULL,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_STRING,
    TOKEN_KEYWORD_VOID,
    TOKEN_KEYWORD_WHILE,

    TOKEN_DECLARE,
    TOKEN_STRICT_TYPES,

    TOKEN_L_PAR,
    TOKEN_R_PAR,
    TOKEN_L_BRACKET,
    TOKEN_R_BRACKET,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_COLON,

    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_GREATER,
    TOKEN_GREATER_EQ,
    TOKEN_LESS,
    TOKEN_LESS_EQ,
    TOKEN_ASSIGN,
    TOKEN_COMPARE,
    TOKEN_NEG_COMPARE,

    TOKEN_INT,
    TOKEN_DOUBLE,
    TOKEN_STRING,

    TOKEN_PROLOG,
    TOKEN_END,
}TokenType;

/*
 * token metadata, helps to store token value
 */
typedef enum{
    VALUE_INT,
    VALUE_STRING,
    VALUE_DOUBLE,
    VALUE_NULL
}TokenValueType;

typedef struct DynamicString{
    char *value;
    unsigned int length;
    unsigned int capacity;  //memory allocated
}DynamicString;

typedef struct{
    TokenType type;
    TokenValueType valueType;

    union{
        int integer;
        double decimal;
        DynamicString *stringPtr;
    }value;

}Token;

typedef struct{
    Token **value;
    int top;
    int size;
}Stack;

// struktura pre AST
typedef struct ASTstruct
{
    int type;
    char *value;

    struct ASTstruct *leftNode;
    struct ASTstruct *rightNode;
} ASTstruct;


// typy uzlov v AST
typedef enum{
    SEQ,
    PROLOG,
    NODE_DEF_FUNC,
    NODE_PARAMS_RETURNTYPE,
    RETURN_TYPE_INT,
    RETURN_TYPE_FLOAT,
    RETURN_TYPE_STRING,
    NODE_PARAM_ID_INT,
    NODE_PARAM_ID_FLOAT,
    NODE_PARAM_ID_STRING,
    NODE_RETURN,

} Nodes;

/**
 * Dynamic string initialization
 * @param string
 */
DynamicString* DynamicStringInit();

/**
 * Increases string's capacity
 * @param string
 */
void DynamicStringResize(DynamicString *string, unsigned int new_capacity);

/**
 * Creates deep copy of string
 * @param string
 */
void DynamicStringCopy(DynamicString *src, DynamicString *dst);

/**
 * Frees memory occupied by string
 * @param string
 */
void DynamicStringFree(DynamicString *string);

/**
 * Adds character to string
 * @param string
 * @param ch
 */
void DynamicStringAddChar(DynamicString *string, char ch);

/**
 * Removes last character from string
 * Does nothing if string is empty
 * @param string
 */
void DynamicStringRemoveChar(DynamicString *string);

/**
 * Cleans dynamic string value
 * @param string
 */


void DynamicStringClean(DynamicString *string);

/**
 * Compares dynamic string with static string
 * @param string dynamic
 * @param string1 static
 * @return
 */
bool DynamicStringCompare(DynamicString *string, const char *string2);

/**
 * Initializes token with given arguments
 *
 * @param tokenType
 * @param valueType
 * @param value
 * @return
 */
Token * TokenInit(TokenType tokenType, DynamicString *value);

/**
 * Deep copies token
 * @param src
 * @return
 */
Token *TokenCopy(Token *src);

/**
 * Prints token value to stdout
 * @param token
 */
void TokenPrint(Token *token);

/**
 * Frees memory occupied by token
 * @param token
 */
void TokenFree(Token *token);

/**
 * Initializes stack
 * @param stack
 */
Stack *StackInit();
/**
 * Checks if stack is empty
 * @param stack
 * @return
 */
bool StackIsEmpty(Stack *stack);

/**
 * Adds token on top of the stack
 * @param stack
 * @param token
 */
void StackPush(Stack *stack, Token *token);

/**
 * Removes top element from stack and returns its value
 * @param stack
 * @return
 */
Token* StackPop(Stack *stack);

/**
 * Removes top element from stack
 * @param stack
 */
void StackRemoveTop(Stack *stack);

/**
 * Returns top element
 * @param stack
 * @return
 */
Token* StackTop(Stack *stack);

/**
 * Returns amount of elements in stack
 * @param stack
 * @return
 */
unsigned int StackSize(Stack *stack);

/**
 * Prints stack elements to stdout in {value, type} format
 * @param stack
 */
void StackPrint(Stack *stack);

/**
 * Frees memory occupied by stack
 * @param stack
 */
void StackFree(Stack *stack);

/**
 * Returns flipped stack
 * @param stack
 * @return
 */
void StackFlip(Stack *stack);

/**
 * returns type of token value(str, int, null)
 * @return
 */
TokenValueType getValueType(TokenType tokenType);



int parser();
ASTstruct *parse();
ASTstruct *prolog();
ASTstruct *program();

// vytvori uzol v AST
ASTstruct *createNode(int type, DynamicString *value, ASTstruct *leftNode, ASTstruct *rightNode);
void expectToken(int type, Stack *stack);
Token *loadToken(Stack *stack);
void unloadToken(Stack *stack);
ASTstruct *rt(Stack *stack);
ASTstruct *getRT(Stack *stack);
ASTstruct *params(Stack *stack);
ASTstruct *stmt(Stack *stack);


#endif //IFJ_22_PROJEKT_UTILS_H
