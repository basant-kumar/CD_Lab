from __future__ import print_function

grammer=[]
nonterminal=set([])

print("Enter the production rules:")
#Taking input
while True:
    line = input()
    if line:
        grammer.append(line)
        nonterminal.add(line[0])
    else:
        break

#Non terminals in grammer, print(nonterminal)

#Finding left recursions and terminals
for rule in grammer:
	recursion=[]
	terminal=[]
	for i in range(1,len(rule)):
		if(rule[0]==rule[i] and (rule[i-1]=='>' or rule[i-1]=='|')):
			recursion.append(i)
		if((rule[i-1]=="|" or rule[i-1]==">") and (i==len(rule)-1 or rule[i+1]=="|")):
			terminal.append(rule[i])
	if(len(recursion)>0):
		print(rule+" is left recursive and will be replaced by the following,")
		#Removing left recursion for any non terminal A
		print(rule[0]+"->",end="")
		for j in range(len(terminal)):
			print(terminal[j]+rule[0]+"\'",end="")
			if j<len(terminal)-1:
				print("|",end="")
		print("")
		#Adding grammer for A'
		print(rule[0]+"\'->",)
		for k in range(len(recursion)):
			x = recursion[k]
			while True:
				if(not(rule[x+1]=="|" or x==len(rule)-1)):
					print(rule[x+1],end="")
					x+=1
				else:
					print(rule[0]+"\'",end="")
					break
			if(k<len(recursion)-1):
				print("|",end="")
			else:
				print("|epsilon\n")
	
