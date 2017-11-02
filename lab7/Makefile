all: a.out

y.tab.c y.tab.h : l.y
	yacc -d l.y

lex.yy.c: lex.l y.tab.h
	lex lex.l

a.out: lex.yy.c y.tab.c y.tab.h
	gcc y.tab.c lex.yy.c -o a.out -lm -ll

clean:
	rm a.out lex.yy.c y.tab.c y.tab.h
