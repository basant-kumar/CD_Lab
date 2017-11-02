#include<bits/stdc++.h>
using namespace std;
int Rz=0;
class runtime_stack{
	public:
		string func;
		map<string,int> vars;
		int ret_addr;
		runtime_stack(string f,int x=0,int y=0){
			func = f;
			vars["Rx"] = x;
			vars["Ry"] = y;
		}
};
bool is_label(char *str){
	return str[strlen(str)-1]==':';
}
void parse_file(char *file,map<string,vector<string> > &code){
	FILE *fp = fopen(file,"r");
	char buff[20];
	string label;
	while(!feof(fp)){
		fscanf(fp,"%[^\n]\n",buff);
		if(is_label(buff)){
			buff[strlen(buff)-1] = '\0';
			label = string(buff);
			code.insert(make_pair(label,vector<string> (0)));
		}
		else{
			code[label].push_back(string(buff));
		}
	}
}
void print(pair<string ,vector<string> > vec){
	cout<<vec.first<<endl;
	for(auto a:vec.second){
		cout<<a<<endl;
	}
}
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
	        return !std::isspace(ch);
	}));
}

				// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
bool is_int(string str){
	for(int i=0;i<str.length();++i)
		if(str[i]<'0' or str[i]>'9')
			return false;
	return true;
}
int evaluate(string s,map<string,int> &mp,int &Rx,int &Ry,int &Rz){
	int e = s.find("=");
	s = s.substr(e+1);
	trim(s);
	int p = s.find("+");
	int n = s.find("-");
	if(p==string::npos and n==string::npos){
		if(is_int(s))
			return stoi(s);
		else if(s.compare("Rz")==0)
			return Rz;
		else if(mp.find(s)==mp.end()){
			cout<<"Undefined variable..."<<s<<endl;
			exit(1);
		}
		else{
			return mp[s];
		}
	}
	int f,sec;
	if(p==string::npos){
		string str = s.substr(0,n);
		trim(str);
		if(is_int(str)){
			f = stoi(str);
		}
		else{
			if(mp.find(str)==mp.end()){
				cout<<"undefined reference to 1"<<str<<endl;
				exit(1);
			}
			else if(str.compare("Rz")==0)
				f = Rz;
			else{
				f = mp[str];
			}
		}
			

		str = s.substr(n+1);
		trim(str);
		if(is_int(str)){
			sec = stoi(str);
		}
		else{
			if(mp.find(str)==mp.end()){
				cout<<"undefined reference to 2"<<str<<endl;
				exit(1);
			}
			else if(str.compare("Rz")==0)
				sec = Rz;
			else
				sec = mp[str];

		}
		return f-sec;
	}
	else{
		string str = s.substr(0,p);
		trim(str);
		if(is_int(str)){
			f = stoi(str);
		}
		else{
			if(str.compare("Rz")==0)
				f = Rz;
			else if(mp.find(str)==mp.end()){
				cout<<"undefined reference to 3"<<str<<endl;
				exit(1);
			}
			else{
				f = mp[str];
			}
		}
			

		str = s.substr(p+1);
		trim(str);
		if(is_int(str)){
			sec = stoi(str);
		}
		else{
			if(mp.find(str)==mp.end()){
				cout<<"undefined reference to 4"<<str<<endl;
				exit(1);
			}
			else if(str.compare("Rz")==0)
				sec = Rz;
			else
				sec = mp[str];

		}
		return f+sec;
	}
}
pair<string,string> parse_instruction(string s){
	int l = s.find(' ');
	if (l==string::npos){
		trim(s);
		return make_pair(s,string (""));
	}
	string l1 = s.substr(0,l);
	string l2 = s.substr(l+1,s.length()-l);
	return make_pair(l1,l2);
}
void execute_code(map<string,vector<string> > &code){
		runtime_stack rs(string("Main"));
		int pc = 0;
		rs.ret_addr = 0;
		stack<runtime_stack> st;
		st.push(rs);
		while(!st.empty()){
			vector<string> &v = code[st.top().func];
			map<string,int> mp = st.top().vars;
			if(mp.find("Rx")==mp.end()){
				mp["Rx"]=0;
				mp["Ry"]=0;
			}
			pc = st.top().ret_addr;
			for(;pc<v.size();){
				pair<string,string> p = parse_instruction(v[pc]);
				pc++;
				if(p.first.compare("Call")==0){
					st.top().vars = mp;
					st.top().ret_addr = pc;
					runtime_stack obj1(p.second,mp["Rx"],mp["Ry"]);
					obj1.ret_addr = 0;
					st.push(obj1);
					break;
				}
				else if(p.first.compare("STOP")==0){
					return;	
				}
				else if(p.first.compare("JMLT")==0){
					st.top().ret_addr=pc;
					st.top().vars = mp;
					runtime_stack obj1(p.second,mp["Rx"],mp["Ry"]);
					obj1.ret_addr = 0;
					st.push(obj1);
					st.top().vars = mp;
					break;
				}
				else if(p.first.compare("RET")==0){
					st.pop();
					break;
				}
				else if(p.first.compare("print")==0){
					if(p.second.compare("Rz")==0)
						cout<<Rz<<endl;
					else if(mp.find(p.second)==mp.end()){
						cerr<<"Undefined referece to variable...5"<<p.second<<endl;
				//		exit(1);
					}
					else{
						cout<<mp[p.second]<<endl;
					}
				}
				else{
					if(p.first.compare("Rz")==0){
						Rz = evaluate(p.second,mp,mp["Rx"],mp["Ry"],Rz);
						continue;
					}
					else if(mp.find(p.first)==mp.end())
						mp[p.first] = 0;
					mp[p.first] = evaluate(p.second,mp,mp["Rx"],mp["Ry"],Rz);
				}
			}
		}
}
int main(int argc, char *argv[]){
	map<string,vector<string> > code;

	
	parse_file(argv[1],code);
	execute_code(code);

return 0;
}
