
 /* scanner for C language */

%{
/* need this for the call to atof() below */
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
%}


DIGIT    [0-9]
LETTER   [A-Za-z]
ID       {LETTER}({LETTER}|{DIGIT}|_)*
L        [\n]
S        []
QUOTE    ["]
STRING   {QUOTE}({LETTER}|{S})*{QUOTE}
KEYWORD  [int|float|do|finish|then|if|else|void|double|char|return|while|for|switch|auto|extren|volatile|]


%%

{STRING}  {
            printf("A String : %s\n",yytext);
            }

{DIGIT}+(\.{DIGIT}+)?(\Ee[+-]?{DIGIT}+)? {
             printf("Real number: %s\n",yytext);
            }
{ID}        printf( "An identifier: %s\n", yytext );

{KEYWORD}   printf("A Keyword: %s\n",yytext);


"+"|"-"|"*"|"/"   printf( "An operator: %s\n", yytext );

"{"[^}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

main( argc, argv )
int argc;
char **argv;
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    }
