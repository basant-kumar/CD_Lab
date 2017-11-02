#include<bits/stdc++.h>
#include<cstdio>
using namespace std;

int main(){
	//unordered_map<string, int> stack;

	// open a file in read mode.
	char data[1024];
	ifstream file("input.txt");
	string str; 
    while (getline(file, str))
    {
        cout<<str<<endl;
    }
	file.close();


	return 0;
}