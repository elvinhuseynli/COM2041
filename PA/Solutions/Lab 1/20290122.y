%{
void yyerror (char *s);
int yylex();
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int symbols[52];
int symbolVal(char symbol);
void updateSymbolVal(char symbol, int val);
%}

%union {
    int num; 
    char var;
    float ind;
    }

%start line
%token begin print exit_command IF WHILE GE NE LE EQ AND OR NOT dec rat
%token <num> decimal
%token <var> variable
%token <ind> rational
%type <num> exp line statement statements TYPE
%nonassoc IFX

%left '<' '>' GE NE LE EQ
%left '+' '-'
%left '*' '/'
%left '(' ')'
%nonassoc AND OR NOT
%nonassoc NEG

%%

line        : begin ';' statements ';'                  {;}
            | exit_command ';'                          {printf("OK\n");exit(EXIT_SUCCESS);}
            | line exit_command ';'                     {printf("OK\n");exit(EXIT_SUCCESS);}
            ;

statements  : statement                                 {$$ = $1;}
            | statements ';' statement                  {;}
            ;

statement   : exp                                       {$$ = $1;}
            | TYPE variable '=' exp                     {updateSymbolVal($2,$4);}
            | print exp                                 {;}
            | IF '(' exp ')' statement                  {if ($3) $$ = $5;else $$ = 0;}
            | WHILE '(' exp ')' statement               {;}
            ;

TYPE        : dec                                       {;}
            | rat                                       {;}

exp         : decimal                                   {$$ = $1;}
            | variable                                  {$$ = symbolVal($1);}
            | rational                                  {$$ = symbolVal($1);}
            | '-' exp %prec NEG                         {$$ = -$2;}
            | exp '+' exp                               {$$ = $1 + $3;}
            | exp '-' exp                               {$$ = $1 - $3;}
            | exp '*' exp                               {$$ = $1 * $3;}
            | exp '/' exp                               {$$ = $1 / $3;}
            | exp '>' exp                               {$$ = $1 > $3;}
            | exp '<' exp                               {$$ = $1 < $3;}
            | exp GE  exp                               {$$ = $1 >= $3;}
            | exp LE  exp                               {$$ = $1 <= $3;}
            | exp EQ  exp                               {$$ = $1 == $3;}
            | exp NE  exp                               {$$ = $1 != $3;}
            | NOT exp                                   {$$ = !$2;}
            | exp AND exp                               {$$ = $1 && $3;}
            | exp OR exp                                {$$ = $1 || $3;}
            | '(' exp ')'                               {$$ = $2;}
            ;

%%   

int computeSymbolIndex(char token)
{
    int idx = -1;
    if(islower(token)) {
        idx = token - 'a' + 26;
    } else if(isupper(token)) {
        idx = token - 'A';
    }
    return idx;
} 

int symbolVal(char symbol)
{
    int bucket = computeSymbolIndex(symbol);
    return symbols[bucket];
}

void updateSymbolVal(char symbol, int val)
{
    int bucket = computeSymbolIndex(symbol);
    symbols[bucket] = val;
}

int main (void) {
    int i;
    for(i=0; i<52; i++) {
        symbols[i] = 0;
    }

    return yyparse ();
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);} 
