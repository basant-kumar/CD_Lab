a.out: lex.yy.c
	gcc -o a.out lex.yy.c -ll 

lex.yy.c: bkm.l 
	lex bkm.l

clean:
	rm a.out lex.yy.c