#define FILE_EXTENSION ".txt"
#include <bits/stdc++.h>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

struct node{
	node(char c){
		str = 0;
		id = c;
		// len = 0;
		//for(int i = 0; i < 26; i++) next[i] = NULL;
	}
	bool str;
	char id;
	// int len;
	node *next[26] = {NULL}, *prev = NULL;
};
vector<node *> leaf[10005];
vector<node *> tree;
// vector<int> max_depth;

bool find_same(string s, node *r){
	node *ptr = r;
	//bool ok = 1;
	for(int i = 1; i < s.length() - 1; i++){
		//int nxt = s[i] - 'a';
		if(ptr -> next[s[i] - 'a'] == NULL){
			// ok = 0;
			// break;
			return 0;
		} 
		ptr = ptr -> next[s[i] - 'a'];
		
	}
	//if(ptr != NULL && !ptr -> str) return 0;
	if(!ptr -> str) return 0;
	//ok = 0;
	//return ok;
	return 1;
}
bool find_pre(string s, node *r){
	node *ptr = r;
	//bool ok = 1;
	//int len = s.length();
	for(int i = 0; i < s.length(); i++){
		// int nxt = s[i] - 'a';
		//cout << nxt << ' ';
		if(ptr -> next[s[i] - 'a'] == NULL){
			// ok = 0;
			// break;
			return 0;
		} 
		ptr = ptr -> next[s[i] - 'a'];
		
	}
	return 1;
}
bool find_suf(string s, int e_num){
	
	//bool ok = 0;
	//int sz = leaf[e_num].size();
	//int len = s.length();
	for(int i = 0; i < leaf[e_num].size(); i++){
		if(leaf[e_num][i] -> id != s[s.length() - 2]) continue;
		if(s.length() == 3) return 1; 
		//if(ok) break;
		//if(leaf[e_num][i] -> len < s.length() - 2) continue;
		// if(leaf[e_num][i] -> id == s[s.length() - 2]){
			node *ptr = leaf[e_num][i];
			for(int j = s.length() - 3; j >= 1; j--){
				if(ptr -> prev == NULL || ptr -> prev -> id != s[j]) break;
				if(j == 1) return 1;
				ptr = ptr -> prev;
			}
		// }
	}
	
	return 0;
}
bool find_star(string s, int s_pos, node *r){
	//if(s.length() - 1 - s_pos - star > max_depth[e_num] - depth) return 0;
	//int len = s.length();
	
	//if(r == NULL) return 0;
	if(s_pos == s.length() - 1){
		if(r -> str) return 1;
		return 0;
	}
	//if(s[s_pos] == '*' && s_pos == s.length() - 2) return 1;
	if(s[s_pos] != '*'){
		if(r -> next[s[s_pos] - 'a'] == NULL) return 0;
		return find_star(s, s_pos + 1, r -> next[s[s_pos] - 'a']);
	} 
	if(s_pos == s.length() - 2) return 1;
	
	bool ok = 0;
	for(int i = 0; i < 26; i++){
		//if(ok) break;
		if(r -> next[i] == NULL) continue;
		if(i == s[s_pos + 1] - 'a') ok = find_star(s, s_pos + 2, r -> next[i]);
		if(ok) return 1;
		ok = find_star(s, s_pos, r -> next[i]);
		if(ok) return 1;
	}
	return 0;

	// if(r == NULL) return 0;
	// if(s[s_pos] == '*'){
	// 	if(s_pos == 1) return 1;
	// 	return (find_star(s, s_pos - 1, r) || find_star(s, s_pos, r -> prev));
	// }
	// if(r -> id != s[s_pos]) return 0;	
	// if(s_pos == 1 && r -> prev == NULL) return 1;
	// return find_star(s, s_pos - 1, r -> prev);
	
}

void build_tree(string s, int e_num){
	if(tree[e_num] == NULL) tree[e_num] = new node('\0');
	node *last = tree[e_num], *ptr = tree[e_num];
	//int len = s.length();
	for(int i = 0; i < s.length(); i++){
		if(ptr -> next[s[i] - 'a'] == NULL) ptr -> next[s[i] - 'a'] = new node(s[i]);
		ptr = ptr -> next[s[i] - 'a'];
		//if(!e_num) cout << "tree: " << ptr -> id << '\n';
		if(i) ptr -> prev = last;
		last = ptr;
	}
	if(!ptr -> str){
		leaf[e_num].push_back(ptr);
		ptr -> str = 1;
	}
	
	//ptr -> len = s.length();
	
	return;
}
// Utility Func

// string parser : output vector of strings (words) after parsing
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(tolower(ch));
		}
		parse_string.emplace_back(new_str);
		
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;

	char * strs = new char[str.length() + 1] ; 
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; 
		res.push_back(s); 
		p = strtok(NULL, d);
	}

	return res;
}

vector<string> q_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		//cout << "parse " << word << '\n';
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch)) new_str.push_back(tolower(ch));
			else if(ch == '"' || ch == '<' || ch == '>' || ch == '*'){
				new_str.push_back(ch);
			} 
		}
		//cout << "newstring " << new_str << '\n';
		if(new_str.length()) parse_string.emplace_back(new_str);
	}
	return parse_string;
}


int main(int argc, char *argv[])
{
	auto start_time = std::chrono::high_resolution_clock::now();
    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);

	// Read File & Parser Example

	string file, tmp;
	fstream fi;
	vector<string> tmp_string;
	vector<string> ans_title;


	ofstream output_stream(output, ios::out);
	// from data_dir get file ....
	// eg : use 0.txt in data directory
	//fi.open(data_dir + "data/0.txt", ios::in);
	int i = 0;
    while(1){

        //string s = to_string(i);
        fi.open(data_dir + to_string(i) + FILE_EXTENSION, ios::in);
		if(!fi.is_open()) break;
        
		string title_name;
		getline(fi, title_name);
		
		ans_title.push_back(title_name);
		//if(title_name == "Aspects of Electron-Phonon Self-Energy Revealed from Angle-Resolved") cout << "i = " << i << '\n';
        // GET TITLENAME WORD ARRAY
        tmp_string = split(title_name, " ");
        vector<string> title = word_parse(tmp_string);

		tree.push_back(NULL);
		vector<int> tmp_ans;
		
		int maxx = 0;

		for(int j = 0; j < title.size(); j++){
			
			build_tree(title[j], i);
		}
		

        // GET CONTENT LINE BY LINE
        while(getline(fi, tmp)){

            // GET CONTENT WORD VECTOR
            tmp_string = split(tmp, " ");

            // PARSE CONTENT
            vector<string> content = word_parse(tmp_string);
			for(int j = 0; j < content.size(); j++){
				
				build_tree(content[j], i);
			}
        }

        // CLOSE FILE
        fi.close();

		i++;
    }
	int n = i;

	fi.open(query, ios :: in);
	string _query;
	
	while(getline(fi, _query)){
		tmp_string = split(_query, " ");
		
		//cout << _query << '\n';
		//output_stream << _query << '\n';
		vector<string> v_query = q_parse(tmp_string);
		bool flag = 0, any = 1;
		for(int k = 0; k < n; k++){
			flag = 0;
			int cnt = 0, op = 2;
			for(auto &word : v_query){
			
				if(cnt == 0){
					cnt++;
				}else if(tmp_string[cnt] == "+"){
					op = 0;
					cnt += 2;
				} 
				else if(tmp_string[cnt] == "-"){
					op = 1;
					cnt += 2;
				} 
				else if(tmp_string[cnt] == "/"){
					op = 2;
					cnt += 2;
				} 
				

				if(!flag && (op != 2)){
					continue;
				}
				int type = 0;
				
				bool result = 0;
				if(word[0] == '"'){
					// if(max_depth[k] < word.length() - 2) result = 0;
					result = find_same(word, tree[k]);
				} 
				else if(word[0] == '*'){
					//if(max_depth[k] < word.length() - 2) result = 0;
					result = find_suf(word, k);
				} 
				else if(word[0] >= 'a' && word[0] <= 'z'){
					//if(max_depth[k] < word.length()) result = 0;
					result = find_pre(word, tree[k]);
				} 
				else if(word[0] == '<'){
					result = find_star(word, 1, tree[k]);
					// result = 0;
					// if(word == "<*>") result = 1;
					// for(int i = 0; i < leaf[k].size(); i++){
					// 	node *ptr = leaf[k][i];
					// 	if(word[word.length() - 2] != '*' && ptr -> id != word[word.length() - 2]) continue;
					// 	if(word.length() == 3){
					// 		result = 1;
					// 		break;
					// 	} 
					// 	result = find_star(word, word.length() - 2, ptr);
					// 	if(result) break;
					// }
				}

				if(op == 0) flag = result;
				else if(op == 1) flag = 1 - result;
				else if(op == 2 && !flag) flag = result;
			}
			if(flag == 1){
				output_stream << ans_title[k] << '\n';
				any = 0;
			} 
		}
		if(any) output_stream << "Not Found!\n";
	}

	// CLOSE FILE
	fi.close();
    output_stream.close();

	auto end_time = std::chrono::high_resolution_clock::now();

    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // 输出执行时间
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}


// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
