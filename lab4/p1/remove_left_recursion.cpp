#include<stdio.h>
#include<string.h>    
#define SIZE 10    
		int main () {         
		char non_terminal;         
		char beta,alpha[10];         
		int num;         
		char production[10][SIZE];         
		int index=3; /* starting of the string following "->" */  
       printf("Enter Number of Production : ");  
       scanf("%d",&num);  
       printf("Enter the grammar as E->E-A :\n");  
       for(int i=0;i<num;i++){  
            scanf("%s",production[i]);  
       }  
       for(int i=0;i<num;i++){  
            printf("\nGRAMMAR : : : %s",production[i]);  
            non_terminal=production[i][0];  
            if(non_terminal==production[i][index]) { 
            int t=0; 
                //alpha[t]=production[i][index+1]; 
                //t++; 
                 printf(" is left recursive.\n");  
                 while(production[i][index]!=0 && production[i][index]!='|'){  
                    index++; 
                    alpha[t++]=production[i][index];
                  }
                  alpha[t-1]='\0';
                 if(production[i][index]!=0) {  
                      beta=production[i][index+1];  
                      printf("Grammar without left recursion:\n");  
                      printf("%c->%c%c\'",non_terminal,beta,non_terminal);  
                      printf("\n%c\'->%s%c\'|Z\n",non_terminal,alpha,non_terminal);  
                }  
                 else  
                     printf(" can't be reduced\n");  
            }  
            else  
                 printf(" is not left recursive.\n");  
            index=3;  
       }  
  }   