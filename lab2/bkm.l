 /* scanner for C/C++ language */

%{
/* need this for the call to atof() below */
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
static int IdCount,NumCount;

int installNum();
int installID();
%}

delim	[ \t\n]
nl      [\n]
digit   [0-9]
ws		{delim}+
letter  [A-Za-z]
id      {letter}({letter}|{digit})*
number  {digit}+(\.{digit}+)?(\Ee[+-]?{digit}+)?
relop   [<|<=|=|<>|>|>=]
op      [+|-|*|/|%]
comment [//]

%%

{ws}	{}



{number} {	int yylval=installNum();
			printf("A Real Number: %s\n", yytext);
		}
{id}	 {	int yylval=installID();
			printf("A Identifier: %s\n",yytext);
		}


{op}	 {	
			printf("A Operator: %s\n",yytext);
		}

{relop}	 {	
			printf("A Relational Operator: %s\n",yytext);
		}
{comment}+.+{nl}
		{
			printf("A Comment: %s\n",yytext);
		}



.           printf( "Unrecognized character: %s\n", yytext );


%%

int installID(){
	IdCount++;
	return IdCount;
}

int installNum(){
	NumCount++;
	return NumCount;
}

int main(int argc, char **argv){
	IdCount=0;
	NumCount=0;
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    return 0;
}