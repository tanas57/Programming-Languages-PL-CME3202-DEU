#include <stdio.h>
#include <ctype.h>

// lexical analyzer code started
#define LETTER 0
#define DIGIT 1
#define OPERATOR 2
#define INT_LIT 3
#define IDENT 4
#define UNKNOWN -1
#define FINISHED -2

char input[100];
int inputIndex=0;

int charClass;
char lexeme[10];
char nextChar;
int lexLen;
// lexical analyzer code finished

// syntax analyzer code started
int nextToken=0;
#define PLUS_CODE 5
#define MINUS_CODE 6
#define AST_CODE 7
#define SLASH_CODE 8
#define ID_CODE 9
#define LEFT_PAREN_CODE 10
#define RIGHT_PAREN_CODE 11

void expr();
void term();
void factor();

int exprId=0;
int termId=0;
int factorId=0;
int i=0;
int error=0;
// syntax analyzer code finished

// lexical analyzer code started
void addChar()
{
    if (lexLen<=9)
    {
        lexeme[lexLen++] =nextChar;
    }
    else
    {
        printf("Error - lexeme too long\n");
    }
}

char getNextChar()
{
    if (input[inputIndex] != '\0')
    {
        return input[inputIndex++];
    }
    else
        return NULL;
}
void getChar()
{
    if((nextChar=getNextChar())!=NULL)
    {

        if (nextChar=='(' )
            charClass = LEFT_PAREN_CODE;
        else if (nextChar==')' )
            charClass = RIGHT_PAREN_CODE;
        else if (nextChar=='+' )
            charClass = PLUS_CODE;
        else if (nextChar=='-')
            charClass = MINUS_CODE;
        else if (nextChar=='*' )
            charClass = AST_CODE;
        else if (nextChar=='/' )
            charClass = SLASH_CODE;
        else
        {
            if (isalpha(nextChar))
            {
                charClass=LETTER;
            }
            else
            {
                if (isdigit(nextChar))
                    charClass = DIGIT;
                else
                    charClass = UNKNOWN;
            }
        }
    }
    else
        charClass = FINISHED;
}

void getNonBlank()
{
    while (isspace(nextChar))
        getChar();
}

int lex2()
{
    int i;
    for (i=0; i<lexLen; i++)
        lexeme[i]='\0';
    lexLen=0;
    static int first = 1;
    if (first)
    {
        getChar();
        first=0;
    }
    getNonBlank();
    switch(charClass)
    {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT)
            {
                addChar();
                getChar();
            }
            return IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT)
            {
                addChar();
                getChar();
            }
            return INT_LIT;
            break;
        case LEFT_PAREN_CODE:
            addChar();
            getChar();
            return LEFT_PAREN_CODE;
            break;
        case RIGHT_PAREN_CODE:
            addChar();
            getChar();
            return RIGHT_PAREN_CODE;
            break;
        case PLUS_CODE:
            addChar();
            getChar();
            return PLUS_CODE;
            break;
        case MINUS_CODE:
            addChar();
            getChar();
            return MINUS_CODE;
            break;
        case AST_CODE:
            addChar();
            getChar();
            return AST_CODE;
            break;
        case SLASH_CODE:
            addChar();
            getChar();
            return SLASH_CODE;
            break;
        case FINISHED:
            return FINISHED;
            break;
        case UNKNOWN:
            addChar();
            getChar();
            return UNKNOWN;
            break;

    }
    return UNKNOWN;
}

int lex()
{
    nextToken =lex2();
    return nextToken;
}

void expr()
{
    int myExprId =exprId;
    exprId++;
    printf("expr starting %d\n",myExprId);

    term();
    while (nextToken == PLUS_CODE || nextToken == MINUS_CODE)
    {
        printf("lexeme %s\n",lexeme);
        lex();
        term();
    }
    printf("expr ended %d\n",myExprId);
}

void term()
{
    int myTermId =termId;
    termId++;
    printf("<term>\n");
    printf("  factor starting %d\n",myTermId);
    factor();
    while (nextToken == AST_CODE || nextToken == SLASH_CODE)
    {
    	printf("lexeme %s\n", lexeme);
        lex();
        factor();
    }
	printf("factor ended %d\n",myTermId);
	printf("<term>\n");
}

void factor()
{
    int myFactorId =factorId;
    factorId++;
    printf("  factor starting %d\n",myFactorId);
    if (nextToken== IDENT || nextToken== INT_LIT)
    {
        printf("  lexeme %s\n",lexeme);
        lex();
    }
    else if (nextToken == LEFT_PAREN_CODE)
    {
           printf("lexeme %s\n",lexeme);
		lex();
		expr();
		if (nextToken == RIGHT_PAREN_CODE)
		{
			printf("lexeme %s\n",lexeme);
			lex();
		}
		else
		{
			error=1;
			printf("No right parenthesis\n");
		}
    }
    else
    {
        error=1;
        printf("  Syntax error\n");
    }
    printf("  factor ended %d\n",myFactorId);

}
// syntax analyzer code finished

int main()
{
    printf("Input your string: \n");
    scanf("%s", input);

    error=0;

    lex();
    expr();

    if (nextToken!= FINISHED || error)
        printf("error");
    else
        printf("success");
    scanf("%s");
    return 0;

}


