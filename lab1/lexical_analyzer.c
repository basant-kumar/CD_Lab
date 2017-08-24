#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8 // max length of each word string
#define LIMIT 200 // max number of word strings in an input file

//global variables 
char *keywords[15] = {"start", "finish", "then", "if", "repeat", "var", 
	"int", "float", "do",
	"read", "print", "void", "return", "dummy", "program"};	

char *relationalOperators[] = {"==", "<", ">", "=>", "=<"};

char otherOperators[6] = {':', '+', '-', '*', '/', '%'};
char delimiters[9] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};

char words[LIMIT][MAX]; 
int wordi = 0, wordj = 0;
int wordLineNums[LIMIT];

char keys[LIMIT][MAX]; 
int keyi = 0;
int keyLineNums[LIMIT];
   
char idens[LIMIT][MAX]; 
int ideni = 0;
int idenLineNums[LIMIT];

char nums[LIMIT][MAX];  
int numi = 0, numj = 0;
int numLineNums[LIMIT];

char delims[LIMIT]; 
int delimi = 0;
int delimLineNums[LIMIT];

char otherOps[LIMIT]; 
int otherOpi = 0;
int otherOpLineNums[LIMIT];

char relOps[LIMIT][MAX]; 
int relOpi = 0, relOpj = 0;
int relOpLineNums[LIMIT];

int isExAcceptableChar(char);

int isDelimiter(char);
int isOtherOperators(char);
int isStartRelationalOperator(char);

void splitWords();
void printWords();
void printKeywords();
void printNumbers();
void printIdentifiers();
void printDelimiters();
void printOtherOperators();
void printRelationalOperators();
void printSummary();


void getTokenType(FILE *filePtr) {
	int lineNum = 1;	
	char ch;
	
	while ((ch = fgetc(filePtr)) != EOF) {
		if (ch == '\n') {
			lineNum++;
		}

		// Ignore comment starting with // to the end of line
		if (ch == '/') {
			if (fgetc(filePtr) == '/') {
				while ((ch = fgetc(filePtr)) != '\n') {}
				lineNum++;
			} else
				fseek(filePtr, -1, SEEK_CUR);
		}

		if (isalpha(ch)) {
			words[wordi][wordj++] = ch;	
			while (isalpha(ch = fgetc(filePtr))) {
				words[wordi][wordj++] = ch;	
			}
			words[wordi][wordj] = '\0';	
			wordLineNums[wordi] = lineNum;
			wordi++; wordj = 0;	
			fseek(filePtr, -1, SEEK_CUR);
		} 

		else if (isdigit(ch)) {
			nums[numi][numj++] = ch;
			while (isdigit(ch = fgetc(filePtr))) {
				nums[numi][numj++] = ch;
			}
			nums[numi][numj] = '\0';
			numLineNums[numi] = lineNum;
			numi++; numj = 0;
			fseek(filePtr, -1, SEEK_CUR);
		}

		else if (ispunct(ch)) {
			if (isDelimiter(ch)) {
				delims[delimi] = ch;
				delimLineNums[delimi] = lineNum;
				delimi++;
			} 
			else if (isOtherOperators(ch)) {
				otherOps[otherOpi] = ch;
				otherOpLineNums[otherOpi] = lineNum;
				otherOpi++;
			}
			else if (isStartRelationalOperator(ch)) {
				if (ch == '<' || ch == '>') {
					relOps[relOpi][relOpj++] = ch;
					relOps[relOpi][relOpj] = '\0';
					relOpLineNums[relOpi] = lineNum;
					relOpi++; relOpj = 0;
				}
				else if (ch == '=') {
					if ((ch = fgetc(filePtr)) == '=' || ch == '>' || ch == '<') {
						relOps[relOpi][relOpj++] = '=';	
						relOps[relOpi][relOpj++] = ch;	
						relOps[relOpi][relOpj] = '\0';
						relOpLineNums[relOpi] = lineNum;
						relOpi++; relOpj = 0;
					} else if (ch == '!') {
						if ((ch = fgetc(filePtr)) == '=') {
							relOps[relOpi][relOpj++] = '=';
							relOps[relOpi][relOpj++] = '!';
							relOps[relOpi][relOpj++] = ch;	
							relOps[relOpi][relOpj] = '\0';
							relOpLineNums[relOpi] = lineNum;
							relOpi++; relOpj = 0;
						} else {
							fseek(filePtr, -1, SEEK_CUR);
						}
					} else {
						fseek(filePtr, -1, SEEK_CUR);
					}
			
				}
			}
		}
	} // end while

	splitWords();	

	printSummary();
	
	
}

void printSummary() {
	printf("----------BEGIN SUMMARY---------- \n");

	printf("Total %d KEYWORDS found are: \n", keyi);
	printKeywords();
	printf("***/END KEYWORD SUMMARY*** \n");

	printf("\nTotal %d IDENTIFIERS found are: \n", ideni);
	printIdentifiers();	
	printf("***/END IDENTIFIER SUMMARY*** \n");

	printf("\nTotal %d NUMBERS found are: \n", numi);
	printNumbers();	
	printf("***/END NUMBER SUMMARY*** \n");

	printf("\nTotal %d DELIMITERS found are: \n", delimi);
	printDelimiters();	
	printf("***/END DELIMITER SUMMARY*** \n");

	printf("\nTotal %d RELATIONAL OPERATORS found are: \n", relOpi);
	printRelationalOperators();	
	printf("***/END RELATIONAL OPERATOR SUMMARY*** \n");

	printf("\nTotal %d OTHER OPERATORS found are: \n", relOpi);
	printOtherOperators();	
	printf("***/END OTHER OPERATOR SUMMARY*** \n");

	printf("\n----------/END SUMMARY----------- \n");
}

int isStartRelationalOperator(char c) {
	int i;
	int result = 0; // false
	if (c == '=' || c == '<' || c == '>') {
		result = 1;
	}
	return result;	
}

int isOtherOperators(char c) {
	 int i;
	 int result = 0; // false
	 for (i = 0; i < 6; i++) {
		if (otherOperators[i] == c) 
			result = 1;
	 }
	 return result;
}

int isDelimiter(char c) {
	 int i;
	 int result = 0; // false
	 for (i = 0; i < 9; i++) {
		if (delimiters[i] == c) 
			result = 1;
	 }
	 return result;
}

int isKeyword(char *str) {
	int i;
	int result = 0; // false
	for (i = 0; i < 15; i++) {
		if (!strcasecmp(keywords[i], str))
			result = 1;
	}
	return result;
}

void printOtherOperators() {
	int i;
	for (i = 0; i < otherOpi; i++) {
		printf("%c \t (line #%d) \n", otherOps[i], otherOpLineNums[i]);
	}
}

void printDelimiters() {
	int i;
	for (i = 0; i < delimi; i++) {
		printf("%c \t (line #%d) \n", delims[i], delimLineNums[i]);
	}
}

void printRelationalOperators() {
	int i;
	for (i = 0; i < relOpi; i++) {
		printf("%s \t (line #%d) \n", relOps[i], relOpLineNums[i]);
	}
}

void printWords() {
	// printf("Num of words = %d \n", wordi);
	int i;
	for (i = 0; i < wordi; i++) {
		printf("%s \t (line #%d) \n", words[i], wordLineNums[i]);
	}
}

void printKeywords() {
	int i;
	for (i = 0; i < keyi; i++) {
		printf("%s \t (line #%d) \n", keys[i], keyLineNums[i]);
	}
}

void printNumbers() {
	int i;
	for (i = 0; i < numi; i++) {
		printf("%s \t (line #%d) \n", nums[i], numLineNums[i]);
	}
}

void printIdentifiers() {
	int i;
	for (i = 0; i < ideni; i++) {
		printf("%s \t (line #%d) \n", idens[i], idenLineNums[i]);
	}
}

void splitWords() {
	int i;
	for (i = 0; i < wordi; i++) {
		if (isKeyword(words[i])) {
			strcpy(keys[keyi], words[i]);
			keyLineNums[keyi] =  wordLineNums[i];
			keyi++;
		} else {
			strcpy(idens[ideni], words[i]);
			idenLineNums[ideni] = wordLineNums[i];
			ideni++;

		}
	}
}



// Besides English letters, and digits, these are extra acceptable characters
int isExAcceptableChar(char c) {
	if (c == '.' || c == '(' || c == ')' || c == ',' || c =='{' || c == '}' ||
		c == ';' || c == '[' || c == ']' || 
		c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || 
		c == '=' || c == '<' || c == '>' || c == '!' 
		 || c == '#' || c=='"' ) {

		return 1;
	} else 
		return 0;
}



int main(int argc, char *argv[])
{
	FILE *filePtr;
	if(argc<2){
		printf("Plese give input file name: e.g. ./a.out input.c\n");
		exit(1);
	}
	if( (filePtr = fopen(argv[1], "r")) == NULL ) {
		printf("Cannot open input file.\n");
		exit(1);
	}

	fseek(filePtr, 0, SEEK_END);
	if (ftell(filePtr) == 0) {
		printf("File is empty.\n");
		exit(1);
	} else {
		rewind(filePtr);
	}

	char c;
	int numLine = 1;

	int charCount = 0;
	char tempStr[MAX]; 
	int i;

	int isValid = 1; // true 
	while ((c = fgetc(filePtr)) != EOF) {
		if (c == '\n')
			numLine++;

		// Exclude comment line starting with '//' and ending with new line
		if (c == '/') {
			if (fgetc(filePtr) == '/') {
				while ((c = fgetc(filePtr)) != '\n') {}
				numLine++;
			}			
		}

		if (isalnum(c)) {
			tempStr[charCount] = c; 
			charCount++;
			if (charCount > MAX) {
				printf("Word '%s' on line number %d is too long. \n", tempStr, numLine);
				exit(1);	
			}
		} else if (isspace(c) || isExAcceptableChar(c)) { 
			charCount = 0;
		} else {
			printf("Invalid character '%c' at line %d. \n", c, numLine);
			isValid = 0; // false
		}

	}

	if (isValid == 0) { 
		printf("Something wrong with the input file. \n");
		exit(1);
	}

	rewind(filePtr);
	
	getTokenType(filePtr);
	

	fclose(filePtr);
	return 0;
}
