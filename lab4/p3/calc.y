%{

	#include<stdio.h>
	#include<stdlib.h>

	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;
	
	void yyerror(const char *s);
	
%}

%union{
	int ival;
	float fval;
}

%token<ival> INT
%token<fval> FLOAT
%token PLUS MINUS MULTIPLY DIVIDE LEFT RIGHT
%token NEWLINE QUIT
%left PLUS MINUS
%left MULTIPLY DIVIDE
%nonassoc UMINUS
%left AND XOR OR 
%right NOT


%type<ival> expr
%type<fval> mixed_expr

%start calculation

%%

calculation: 
			| calculation line
			;

line: 	NEWLINE
		| expr NEWLINE { printf("Result: %i\n",$1); }
		| mixed_expr NEWLINE { printf("Result: %f\n",$1); }
		| QUIT 	NEWLINE { printf("Bye! Have Fun!\n"); exit(0); }
		;

expr: 	|INT {$$ = $1; }
		| expr PLUS expr { $$ = $1 + $3; }
		| expr MINUS expr { $$ = $1 - $3; }
		| expr MULTIPLY expr { $$ = $1 * $3; }
		| MINUS expr %prec UMINUS { $$ = -$2; }
		| expr AND expr { $$ = $1 & $3; }
		| expr OR expr { $$ = $1 | $3; }
		| expr XOR expr { $$ = $1 ^ $3; }
		| NOT expr { $$ = ~$2; }
		| LEFT expr RIGHT  { $$ = $2; }
		;

mixed_expr: FLOAT { $$ = $1; }
			| mixed_expr PLUS mixed_expr { $$ = $1 + $3; }
			| mixed_expr MINUS mixed_expr { $$ = $1 - $3; }
			| mixed_expr MULTIPLY mixed_expr { $$ = $1 * $3; }
			| mixed_expr DIVIDE mixed_expr { $$ = $1 / $3; }
			| LEFT mixed_expr RIGHT { $$ = $2; }
			| expr PLUS mixed_expr { $$ = $1 + $3; }
			| expr MINUS mixed_expr { $$ = $1 - $3; }
			| expr MULTIPLY mixed_expr { $$ = $1 * $3; }
			| expr DIVIDE mixed_expr { 
										if($3==0.0 ||$3==0)
											yyerror("divide by zero");
										else
											$$ = $1 / $3; 
									}
			| mixed_expr PLUS expr { $$ = $1 + $3; }
			| mixed_expr MINUS expr { $$ = $1 - $3; }
			| mixed_expr MULTIPLY expr { $$ = $1 * $3; }
			| mixed_expr DIVIDE expr { $$ = $1 / $3; }
			| expr DIVIDE expr { 
									if($3==0.0 ||$3==0)
										yyerror("divide by zero");
									else
										$$ = $1 / (float)$3; 
									}
			;
%%

int main(){
	yyin = stdin;
	fprintf(stdout, "supported operations: AND, OR, XOR, NOT, +, - , *, / etc.....\n");
	do{
		yyparse();
	}while(!feof(yyin));
	return 0;
}

void yyerror(const char *s){
	fprintf(stderr, "Parse Error: %s\n",s);
	exit(1);
}