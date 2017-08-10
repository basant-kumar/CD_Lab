#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cctype>
 
using namespace std;
 
char operators[] = "+-*/%="
char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};

int isKeyword(char buffer[]){
    
    int i, flag = 0;
    
    for(i = 0; i < 32; ++i){
        if(strcmp(keywords[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    
    return flag;
}

bool isOperator(char ch){
    for(int i = 0; i < 6; ++i){
      if(ch == operators[i])
        return true;    
    }
    return false;
}
 
int main(){
    char ch, buffer[15];
    ifstream fp("input.c");
    int i,j=0,quote=0;
    
    if(!fp.is_open()){
        cout<<"error while opening the file\n";
        exit(0);
    }
    
    while(!fp.eof()){
      ch = fp.get();

      if(isOperator()){
        cout<<ch<<" is operator"<<endl;
      }
      else if(ch=='"'){
        while(1){
          ch=fp.get();
          if(ch=='"')
            break;
          cout<<ch;
        }cout<<" is string"<<endl;

      }
      else if(isalpha(ch)){
         buffer[j++] = ch;
      }
      else if(isdigit(ch)){
         cout<<ch<<" is constant\n";
      }
      else if((ch == ' ' || ch == '\n' || ch== '(' || ch== ')') && (j != 0)){
             x[j] = '\0';
             j = 0;
                                
             if(isKeyword(buffer) == 1)
                 cout<<buffer<<" is keyword\n";
             else
                 cout<<buffer<<" is indentifier\n";
      }
       
    }
    
    fp.close();
    
    return 0;
}