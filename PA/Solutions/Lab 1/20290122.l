%{
#include "y.tab.h"
void yyerror (char *s);
int yylex();
%}
%%
"let"                             {return begin;}
"show"                            {return print;}
"done"                            {return exit_command;}
"loop"                            {return WHILE;}
"whether"                         {return IF;}
"dec"							  {return dec;}
"rat"							  {return rat;}
"=="                              {return EQ;}
">="                              {return GE;}
"<="                              {return LE;}
"!="                              {return NE;}
"&&"                              {return AND;}
"||"                              {return OR;}
"!"                               {return NOT;}
[_a-zA-Z][a-zA-Z0-9]*             {yylval.var = yytext[0]; return variable;}
[0-9]+                            {yylval.num = atoi(yytext); return decimal;}
[0-9]+[.][0-9]+				      {yylval.ind = atof(yytext); return rational;}
[ \t\n]                           ;
[-+/*=()<>;:]                      {return yytext[0];}

%%
int yywrap (void) {return 1;}
