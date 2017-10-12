#include<bits/stdc++.h>
#include<cstdio>
using namespace std;

int main(){
	//unordered_map<string, int> stack;

	// open a file in read mode.
	char data[1024];
	ifstream infile; 
	infile.open("input.txt"); 
	infile >> data; 
	cout << data << endl;
	infile >> data; 
	cout << data << endl; 
	infile.close();


	return 0;
}