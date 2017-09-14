%option noyywrap

%{

#include<stdio.h>

#include "calc.tab.h"
	
%}

%%

[ \t] ; //ignore all whitespace
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+ { yylval.ival = atoi(yytext); return INT; }
\n { return NEWLINE; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULTIPLY; }
"/" { return DIVIDE; }
"(" { return LEFT; }
")" { return RIGHT; }
'+' { return EQUAL; }
"exit" { return QUIT; }
"quit" { return QUIT; }

%%