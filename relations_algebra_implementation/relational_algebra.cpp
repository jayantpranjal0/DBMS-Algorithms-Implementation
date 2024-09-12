#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include<chrono>

using namespace __gnu_pbds;
using namespace std;
using namespace chrono;
using namespace tr1;

#define ll long long
#define rep(i,n) for(int i=0;i<n;i++)
#define inar(a,n) for(int inputarrayunique1234=0;inputarrayunique1234<n;inputarrayunique1234++){cin>>a[inputarrayunique1234];}
#define tolower(a) ((char)tolower(a))
#define toupper(a) ((char)toupper(a))
#define yes cout<<"YES";
#define no cout<<"NO";
#define rall(a) a.rbegin(),a.rend()
#define sz(a) (int)a.size()
#define pb push_back
#define mp make_pair





int precedence(const string& op) {
    if (op == "||") return 1;
    if (op == "&&") return 2;
    if (op == "!") return 3;
    if (op == ">" || op == "<" || op == "=") return 4;
    return 0; 
}

bool isOperator(const string& token) {
    return (token == "&&" || token == "||" || token == "!");
}

bool isComparisonOperator(const string& token) {
    return (token == ">" || token == "<" || token == "=");
}

bool isInteger(const string& token) {
    for (char c : token) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

int evaluateComparison(string lefts, const string& op, string rights) {
	if(isInteger(lefts) && isInteger(rights)){
		int left=stoi(lefts),right=stoi(rights);
		if (op == ">") {
			return left > right;
		} else if (op == "<") {
			return left < right;
		} else if (op == "=") {
			return left == right;
		}
	}
	else{
		if (op == ">") {
			return lefts > rights;
		} else if (op == "<") {
			return lefts < rights;
		} else if (op == "=") {
			return lefts == rights;
		}
	}
    
    throw runtime_error("Invalid comparison operator");
}

bool evaluateExpression(const vector<string>& expression) {
    stack<string> operatorStack;
    stack<string> valueStack;

    for (const string& token : expression) {
        if (token == "true" || token == "false") {
			valueStack.push(token);
        } else if (isInteger(token)) {
			valueStack.push(token);
        } else if (token == "(") {
            operatorStack.push(token);
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                string op = operatorStack.top();
                operatorStack.pop();
                if (op == "||" || op == "&&" || op == "!") {
                    if (valueStack.size() < 2) {
                        throw runtime_error("Invalid expression");
                    }
					string right = valueStack.top();
                    valueStack.pop();
                    string left = valueStack.top();
                    valueStack.pop();
                    if (op == "||") {
                        valueStack.push((left=="true" || right=="true")?"true":"false");
                    } else if (op == "&&") {
                        valueStack.push((left=="true" && right=="true")?"true":"false");
                    } else if (op == "!") {
                        valueStack.push(right=="true"?"false":"true");
                    }
                } else if (isComparisonOperator(op)) {
                    if (valueStack.size() < 2) {
                        throw runtime_error("Invalid expression");
                    }
                    string rightOperand = valueStack.top();
                    valueStack.pop();
                    string leftOperand = valueStack.top();
                    valueStack.pop();
                    valueStack.push(evaluateComparison(leftOperand, op, rightOperand)? "true":"false");
                }
            }
            if (!operatorStack.empty() && operatorStack.top() == "(") {
                operatorStack.pop(); 
            } else {
                throw runtime_error("Unbalanced parentheses");
            }
        } else if (isOperator(token) || isComparisonOperator(token)) {
            while (!operatorStack.empty() && operatorStack.top() != "(" && 
                precedence(token) <= precedence(operatorStack.top())) {
                string op = operatorStack.top();
                operatorStack.pop();
                if (op == "||" || op == "&&" || op == "!") {
                    if (valueStack.size() < 2) {
                        throw runtime_error("Invalid expression");
                    }
                    string right = valueStack.top();
                    valueStack.pop();
                    string left = valueStack.top();
                    valueStack.pop();
                    if (op == "||") {
                        valueStack.push((left=="true" || right=="true")?"true":"false");
                    } else if (op == "&&") {
                        valueStack.push((left=="true" && right=="true")?"true":"false");
                    } else if (op == "!") {
                        valueStack.push(right=="true"?"false":"true");
                    }
                } else if (isComparisonOperator(op)) {
                    if (valueStack.size() < 2) {
                        throw runtime_error("Invalid expression");
                    }
                    string rightOperand = valueStack.top();
                    valueStack.pop();
                    string leftOperand = valueStack.top();
                    valueStack.pop();
                    valueStack.push(evaluateComparison(leftOperand, op, rightOperand)?"true":"false");
                }
            }
            operatorStack.push(token);
        }
		else{
			valueStack.push(token);
		}
    }

    while (!operatorStack.empty()) {
        string op = operatorStack.top();
        operatorStack.pop();
        if (op == "(") {
            throw runtime_error("Unbalanced parentheses");
        }
        if (op == "||" || op == "&&" || op == "!") {
            if (valueStack.size() < 2) {
                throw runtime_error("Invalid expression");
            }
            string right = valueStack.top();
            valueStack.pop();
            string left = valueStack.top();
            valueStack.pop();
            if (op == "||") {
                valueStack.push((left=="true" || right=="true")?"true":"false");
            } else if (op == "&&") {
                valueStack.push((left=="true" && right=="true")?"true":"false");
            } else if (op == "!") {
                valueStack.push(right=="true"?"false":"true");
            }
        } else if (isComparisonOperator(op)) {
            if (valueStack.size() < 2) {
                throw runtime_error("Invalid expression");
            }
            string rightOperand = valueStack.top();
            valueStack.pop();
            string leftOperand = valueStack.top();
            valueStack.pop();
            valueStack.push(evaluateComparison(leftOperand, op, rightOperand)? "true":"false");
        }
    }

    if (valueStack.size() != 1) {
        throw runtime_error("Invalid expression");
    }

    return valueStack.top()=="true";
}
vector<string> split(string input, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(input);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
string inputString(){
	string s;
	cin>>s;
	return s;
}
bool isalphanum(char c){
	return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0'&&c<='9');
}
string ltrim(string s){
	int i=0;
	while(s[i]==' '){
		i++;
	}
	return s.substr(i);
}
string rtrim(string s){
	int i=s.size()-1;
	while(s[i]==' '){
		i--;
	}
	return s.substr(0,i+1);
}
string trim(string s){
	return ltrim(rtrim(s));
}

enum operation{
	SELECT ,
	PROJECT,
	CARTESIAN_PRODUCT,
	SET_DIFFERENCE,
	SET_UNION,
	DEFAULT,
	EXIT,
    RENAME,
    CREATE_TABLE
};

string toLower(string s){
	for(int i=0;i<s.size();i++){
		s[i]=tolower(s[i]);
	}
	return s;
}


operation stringToOperation(string operation){
	if(toLower(operation)=="select"){
		return SELECT;
	}
	else if(toLower(operation)=="project"){
		return PROJECT;
	}
	else if(toLower(operation)=="cartesian_product"){
		return CARTESIAN_PRODUCT;
	}
	else if(toLower(operation)=="set_difference"){
		return SET_DIFFERENCE;
	}
	else if(toLower(operation)=="rename"){
		return RENAME;
	}
	else if(toLower(operation)=="exit"){
		return EXIT;
	}
	else if(toLower(operation)=="set_union"){
		return SET_UNION;
	}
    else if(toLower(operation)=="create_table"){
        return CREATE_TABLE;
    }
	else{
		return DEFAULT;
	}
}
int inputInt(){
	int n;
	cin>>n;
	return n;
}

class Table{
public:
	string table_name;
	vector<vector<string>> table;
	vector<string> col_names;
	map<string,int> col_index;
	// map<string,int> col_type;
// public:
	Table(){

	}
	Table(string table_name,vector<vector<string>> table,vector<string> col_names){
		this->table_name=table_name;
		this->table=table;
		this->col_names=col_names;
		for(int i=0;i<col_names.size();i++){
			col_index[col_names[i]]=i;
		}
	}
	Table(string table_name,string filename){
		this->table_name=table_name;
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Error: Could not open file " << filename << endl;
		}
		string line;
		getline(file, line);
		stringstream ss(line);
		string col_name;
		while (getline(ss, col_name, ',')) {
			col_names.push_back(col_name);
		}
		while (getline(file, line)) {
			vector<string> row;
			stringstream ss(line);
			string cell;
			while (getline(ss, cell, ',')) {
				row.push_back(cell);
			}
			if(row.size()==col_names.size())
				table.push_back(row);
			else {
				cerr << "Error: Row has wrong number of cells" << endl;
				exit(1);
			}
		}
		for(int i=0;i<col_names.size();i++){
			col_index[col_names[i]]=i;
		}
	}
	void print(){
		cout<<"Table Name: "<<table_name<<endl;
		int n = table.size();
		int m = col_names.size();
		int max_col_width = 20;
		vector<int> col_widths(m, 0);
		for(int i = 0; i < m; i++){
			col_widths[i] = min((int)col_names[i].size(), max_col_width);
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				col_widths[j] = max(col_widths[j], min((int)table[i][j].size(), max_col_width));
			}
		}
		int total_width = accumulate(col_widths.begin(), col_widths.end(), 0) + 3 * m + 1;
		cout << string(total_width, '-') << endl;
		cout << "| ";
		for(int j = 0; j < m; j++){
			cout << setw(col_widths[j]) << left << col_names[j] << " | ";
		}
		cout << endl;
		cout << string(total_width, '-') << endl;
		for(int i = 0; i < n; i++){
			cout << "| ";
			for(int j = 0; j < m; j++){
				cout << setw(col_widths[j]) << left << table[i][j] << " | ";
			}
			cout << endl;
		}
		cout << string(total_width, '-') << endl;
	}
	static bool isCompatible(Table* table1,Table* table2){
		return table1->col_names==table2->col_names;
	}
};
class Database{
	map<string,Table*> tables;
	public:
		Database(){

		}
		Database(map<string,Table*> tables){
			this->tables=tables;
		}
		Table* createTable(string table_name,string filename){
			if(tables.find(table_name)!=tables.end()){
                Table* tableAlreadyExistsTable=new Table("Table already exists",{{"Table already exists"}},{"Table already exists"});
                return tableAlreadyExistsTable;
			}
            cout<<"Creating table "<<table_name<<" from file "<<filename<<endl;
			this->tables[table_name]=new Table(table_name,filename);
            return tables[table_name];
		}

        Table* project(string query,Table* data){
            Table* out;
            vector<string> tokens= split(query,',');
			vector<string> resultColumnNames;
			vector<vector<string>> resultTable;
            for(int i=0; i<tokens.size(); i++)
            {
                if(data->col_index.count(tokens[i])==0)
                {
                    cout<<"Column doesn't exits"<<endl;
                    Table* incompatibleTablesTable=new Table("Incompatible Tables",{{"Incompatible Tables"}},{"Incompatible Tables"});
                    return incompatibleTablesTable;
                }
                resultColumnNames.push_back(tokens[i]);
            }
            for(int i=0; i<data->table.size(); i++)
            {
                vector<string> temp;
                for(int j=0; j<tokens.size(); j++)
                {
                    temp.push_back(data->table[i][data->col_index[tokens[j]]]);
                }
                resultTable.push_back(temp);
            }
            Table* resultTablePointer=new Table("result",resultTable,resultColumnNames);
			return resultTablePointer;
        }
		Table* cartesianProduct(Table* table1,Table* table2){
			vector<vector<string>> resultTable;
			vector<string> resultColNames(table1->col_names.size()+table2->col_names.size());
			resultTable.resize(table1->table.size()*table2->table.size(),vector<string>(table1->col_names.size()+table2->col_names.size()));
			map<string,int> count;
			for(int i=0;i<table1->col_names.size();i++){
				count[table1->col_names[i]]++;
			}
			for(int i=0;i<table2->col_names.size();i++){
				count[table2->col_names[i]]++;
			}
			for(int i=0;i<table1->col_names.size();i++){
				resultColNames[i]=((count[table1->col_names[i]]==2)?(table1->table_name+((table1->table_name==table2->table_name)?"1":"")+"."):"")+table1->col_names[i];
			}
			for(int i=0;i<table2->col_names.size();i++){
				resultColNames[i+table1->col_names.size()]=((count[table2->col_names[i]]==2)?(table2->table_name+((table1->table_name==table2->table_name)?"2":"")+"."):"")+table2->col_names[i];
			}
            for(int i=0;i<table1->table.size();i++){
                for(int j=0;j<table2->table.size();j++){
					for(int k=0;k<table1->col_names.size();k++){
						resultTable[i*table2->table.size()+j][k]=table1->table[i][k];
					}
					for(int k=0;k<table2->col_names.size();k++){
						resultTable[i*table2->table.size()+j][k+table1->col_names.size()]=table2->table[j][k];
					}
                }
            }
            Table* resultTablePointer=new Table(table1->table_name+"X"+table2->table_name,resultTable,resultColNames);
            return resultTablePointer;
		}
		Table* setDifference(Table* table1,Table* table2){
			vector<vector<string>> resultTable;
			vector<string> resultColNames;
            if(!Table::isCompatible(table1,table2)){
                Table* incompatibleTablesTable=new Table("Incompatible Tables",{{"Incompatible Tables"}},{"Incompatible Tables"});
                return incompatibleTablesTable;
            }
            set<vector<string>> s(table2->table.begin(),table2->table.end());
            for(auto x:table1->table){
                if(s.find(x)==s.end()){
                    resultTable.push_back(x);
                }
            }
            Table* resultTablePointer=new Table("result",resultTable,table1->col_names);
            return resultTablePointer;
		};
		Table* setUnion(Table* table1,Table* table2){
			vector<vector<string>> resultTable;
			if(!Table::isCompatible(table1,table2)){
                Table* incompatibleTablesTable=new Table("Incompatible Tables",{{"Incompatible Tables"}},{"Incompatible Tables"});
                return incompatibleTablesTable;
            }
            set<vector<string>> s(table1->table.begin(),table1->table.end());
            for(auto x:table2->table){
                s.insert(x);
            }
            for(auto x:s){
                resultTable.push_back(x);
            }
            Table* resultTablePointer=new Table("result",resultTable,table1->col_names);
            return resultTablePointer;
		}
		Table* rename(string table_name,Table* table){
			if(tables.find(table_name)!=tables.end()){
                Table* tableAlreadyExistsTable=new Table("Table already exists",{{"Table already exists"}},{"Table already exists"});
                return tableAlreadyExistsTable;
			}
            else{
                Table* newTable=new Table(table_name,table->table,table->col_names);
				tables[table_name]=newTable;
                return newTable;
            }
		}
		bool satisfiesCondition(int i,string s,Table* table){
			vector<string> vals;
			s.push_back('-');
			string temp="";
			for(int i=0;i<s.length();i++){
				if(isalphanum(s[i])){
					temp.push_back(s[i]);
				}
				else if(temp!=""){
					vals.push_back(temp);
					temp="";
				}
				if(s[i]=='='){
					vals.push_back("=");
				}
				else if(s[i]=='<'){
					if(s[i+1]=='='){
						vals.push_back("<=");
						i++;
					}
					else{
						vals.push_back("<");
					}
				}
				else if(s[i]=='('){
					vals.push_back("(");
				}
				else if(s[i]==')'){
					vals.push_back(")");
				}
				else if(s[i]==' '){
					continue;
				}
				else if(s[i]=='>'){
					if(s[i+1]=='='){
						vals.push_back(">=");
						i++;
					}
					else{
						vals.push_back(">");
					}
				}
				else if(s[i]=='!'){
					if(s[i+1]=='='){
						vals.push_back("!=");
						i++;
					}
				}
				else if(s[i]=='&' && s[i+1]=='&'){
					vals.push_back("&&");
					i++;
				}
				else if(s[i]=='|' && s[i+1]=='|'){
					vals.push_back("||");
					i++;
				}
				else if(s[i]=='"'){
					temp="";
					i++;
					temp.push_back('"');
					while(s[i]!='"'){
						temp.push_back(s[i]);
						i++;
					}
					vals.push_back(temp);
					temp="";
				}
			}
			for(auto &x:vals){
				x=isalphanum(x[0])?table->table[i][table->col_index[x]]:x;
				x=(x[0]=='"')?x.substr(1,x.length()):x;
			}
			return evaluateExpression(vals);
		}
		Table* select(string s,Table* table){
			s=trim(s);
			vector<vector<string>> resultTable;
			for(int i=0;i<table->table.size();i++){
				if(satisfiesCondition(i,s,table)){
					resultTable.push_back(table->table[i]);
				}
			}
			Table* resultTablePointer=new Table("result",resultTable,table->col_names);
			return resultTablePointer;
		}
        Table* parseAndOutput(string s){
			s=trim(s);
            operation op;
            string s1,s2;
            if(s.find('[')==string::npos || s.find(']')==string::npos || s.find('{')==string::npos || s.find('}')==string::npos){
                if(tables.find(s)==tables.end()){
                    Table* invalidInputTable=new Table("Invalid Input",{{"Invalid Input"}},{"Invalid Input"});
                    return invalidInputTable;
                }
                else{
                    return tables[s];
                }
            }
			Table* tableAlreadyExistsTable=new Table("Table already exists",{{"Table already exists"}},{"Table already exists"});
			s1="";
			int i=0;
			for(;i<s.length();i++){
				if(s[i]=='{')break;
				s1.push_back(s[i]);
			}
			op=stringToOperation(trim(s1));
			int count=1;
			s1="";
			for(i+=2;i<s.length() && count!=0;i++){
				s1.push_back(s[i-1]);
				if(s[i]=='{')count++;
				else if(s[i]=='}') count--;
			}
			while(s[i]!='[' && i<s.length())i++;
			count=1;
			s2="";
			for(i+=2;i<s.length() && count!=0;i++){
				s2.push_back(s[i-1]);
				if(s[i]=='[')count++;
				else if(s[i]==']')count--;
			}
            switch(op){
                case CREATE_TABLE:
                    return createTable(s1,s2);
                    break;
                case SELECT:
                    return select(s1,parseAndOutput(s2));
                    break;
                case PROJECT:
                    return project(s1,parseAndOutput(s2));
                    break;
                case CARTESIAN_PRODUCT:
                    return cartesianProduct(parseAndOutput(s1),parseAndOutput(s2));
                    break;
                case SET_DIFFERENCE:
                    return setDifference(parseAndOutput(s1),parseAndOutput(s2));
                    break;
                case SET_UNION:
                    return setUnion(parseAndOutput(s1),parseAndOutput(s2));
                    break;
                case RENAME:
                    return rename(s1,parseAndOutput(s2));
                    break;
                case EXIT:
                    cout<<"Exiting...\n";   
                    exit(0);
                    break;
                default:
                    Table* invalidInputTable=new Table("Invalid Input",{{"Invalid Input"}},{"Invalid Input"});
                    return invalidInputTable;
            }
        }
};

signed main(){
	Database* db;
    db=new Database();
	db->createTable("table1","table1.csv");
	db->createTable("table2","table2.csv");
    while(true){
        cout<<">>> ";
        string s;
        getline(cin,s);
        s=trim(s);
        db->parseAndOutput(s)->print();
    }
	return 0;
}