#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include<chrono>
#pragma GCC optimize("Ofast")
#pragma GCC optimization ("unroll-loops")
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_pair tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_mult tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_pair_mult tree<pair<int,int>, null_type,less_equal<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_sum tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_pair_sum tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_mult_sum tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_pair_mult_sum tree<pair<int,int>, null_type,less_equal<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;
using namespace std;
using namespace chrono;
using namespace tr1;

#define ll long long
#define ld long double
#define endl "\n"
#define int long long int
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

using namespace std;

void voidFunction(){};
void printError(string s){
	cout<<"\033[1;31m"+s;
}
void printSuccess(string s){
	cout<<"\033[1;32m"+s;
}
void printWarning(string s){
	cout<<"\033[1;33m"+s;
}
void printInfo(string s){
	cout<<"\033[1;34m"+s;
}
class Node{
public:
	bool isLeaf;
	vector<ll> Keys;
	Node *Parent;
};

class NonLeafNode : public Node{
public:
	vector<Node *> Children;
	NonLeafNode(){
		isLeaf = false;
		Parent = NULL;
	}
};

class LeafNode : public Node{
public:
	Node *Next;
	vector<string> Value;
	LeafNode(){
		Parent = NULL;
		isLeaf = true;
		Next = NULL;
	}
};
class BpTree{
public:
	map<int,string> m;
	Node *head;
	int n;
	BpTree(int degree){
		n = degree;
		head = new LeafNode();
	}
	LeafNode* getCorrespodingLeaf(int key){
		Node *t = this->head;
		while (!t->isLeaf){
			int i=upper_bound(t->Keys.begin(),t->Keys.end(),key)-t->Keys.begin();
			t=((NonLeafNode *)t)->Children[i];
		}
		return (LeafNode *)t;
	}
	void remove(int key){
		if(find(key)=="This key does not exist in this B+ tree!"){
			printError("Key does not exist!");
			return;
		}
		m.erase(key);
		head=new LeafNode();
		for(auto i:m)this->insert(i.first,i.second);

	}
	void insertInParent(int key,NonLeafNode*t, Node *newnode){
		if(t == nullptr) return;
		if (key>t->Keys.back()){
			t->Keys.push_back(key);
			((NonLeafNode *)t)->Children.push_back(newnode);
		}
		else{
			for(int i=0;i<t->Keys.size();i++){
				if(t->Keys[i] > key){
					t->Keys.insert(t->Keys.begin() + i, key);
					((NonLeafNode *)t)->Children.insert(((NonLeafNode *)t)->Children.begin() + i + 1, newnode);
					break;
				}
			}
		}
		if (t->Keys.size() >n){
			Node *nright = new NonLeafNode();
			nright->Parent = t->Parent;
			nright->Keys.insert(nright->Keys.begin(),t->Keys.begin() + floor((n + 2) / 2),t->Keys.end());
			((NonLeafNode *)nright)->Children.insert(((NonLeafNode *)nright)->Children.begin(),((NonLeafNode *)t)->Children.begin() +floor((n + 2) / 2),((NonLeafNode *)t)->Children.end());
			for (int i = (n + 2)/2;i<((NonLeafNode *)t)->Children.size();++i){
				((NonLeafNode *)t)->Children[i]->Parent = nright;
			}
			key = t->Keys[(n+2)/2-1];
			t->Keys.erase(t->Keys.begin()+(n+2)/2-1,t->Keys.end());
			((NonLeafNode *)t)->Children.erase(((NonLeafNode *)t)->Children.begin()+floor((n + 2) / 2),((NonLeafNode *)t)->Children.end());
			newnode = nright;
			newnode->Parent = t;
			if(t->Parent==NULL){
				t->Parent=new NonLeafNode();
				((NonLeafNode *)t->Parent)->Children.push_back(t);
				((NonLeafNode *)t->Parent)->Children.push_back(newnode);
				((NonLeafNode *)t->Parent)->Keys.push_back(key);
				newnode->Parent=t->Parent;
				head=t->Parent;
				return;
			}
			insertInParent(key,(NonLeafNode*)t->Parent,newnode);
		}
	}
	void insert(int key, string value){
		if(find(key)!="This key does not exist in this B+ tree!"){
			printError("Key already exists!");
			return;
		}
		Node *t=head;
		while (!t->isLeaf) {
			bool flag=false;
			for (int i=0;i<t->Keys.size();i++)(t->Keys[i] > key )?({t=((NonLeafNode *)t)->Children[i]; flag=true; break;}):voidFunction();
			((!flag) && (t=((NonLeafNode *)t)->Children[t->Keys.size()]));
		}
		if (t->Keys.size()==0 || key>t->Keys.back()) {
			t->Keys.push_back(key);
			((LeafNode *)t)->Value.push_back(value);
		} 
		else{
			for (int i = 0; i < t->Keys.size(); ++i) { 
				if(t->Keys[i]>key){
					t->Keys.insert(t->Keys.begin() + i, key);
					((LeafNode *)t)->Value.insert(((LeafNode *)t)->Value.begin() + i, value);
					break;
				}
			}
		}
		if (t->Keys.size()+1>n+1){
			Node *newnode=new LeafNode();
			newnode->Parent=t->Parent;
			for(int i=0;i<=(n+1)/2;i++){
				newnode->Keys.push_back(t->Keys.back());
				t->Keys.pop_back();
				((LeafNode *)newnode)->Value.push_back(((LeafNode *)t)->Value.back());
				((LeafNode *)t)->Value.pop_back();
			}
			reverse(newnode->Keys.begin(),newnode->Keys.end());
			((LeafNode *)newnode)->Next = ((LeafNode *)t)->Next;
			((LeafNode *)t)->Next = newnode;
			key = newnode->Keys[0];
			if(t->Parent==NULL){
				t->Parent=new NonLeafNode();
				((NonLeafNode *)t->Parent)->Children.push_back(t);
				((NonLeafNode *)t->Parent)->Children.push_back(newnode);
				((NonLeafNode *)t->Parent)->Keys.push_back(key);
				newnode->Parent=t->Parent;
				head=t->Parent;
				return;
			}
			insertInParent(key,(NonLeafNode*)t->Parent, newnode);
		}
		m[key]=value;
	}
	void printKeys(){
		if (head->Keys.size() == 0){
			printInfo("No keys to print!");
			return;
		}
		queue<pair<NonLeafNode *,int>> q;
		int lastlevel = 0;
		q.push({(NonLeafNode *)head,0});
		while(!q.empty()){
			int size = q.size();
			if(!q.front().first->isLeaf)for(auto j:((q.front().first)->Children))q.push({(NonLeafNode*)j,q.front().second+1});
			printSuccess("[");
			for(auto j:q.front().first->Keys)printSuccess(to_string(j) + ",");
			printSuccess("\b]");
			q.pop();
			cout<<(lastlevel==q.front().second?"":"\n");
			lastlevel=q.front().second;
		}
	}
	void printValues(){
		Node *t = this->head;
		while(!t->isLeaf)t=((NonLeafNode*)t)->Children[0];
		while (t!=NULL){
			for(auto i:t->Keys)printSuccess(((LeafNode *)t)->Value[i]+"\n");
			t=((LeafNode *)t)->Next;
		}
	}
	string find(int key){
		Node *t = this->head;
		while (!t->isLeaf){
			int i=upper_bound(t->Keys.begin(),t->Keys.end(),key)-t->Keys.begin();
			t=((NonLeafNode *)t)->Children[i];
		}
		int x=lower_bound(t->Keys.begin(),t->Keys.end(),key)-t->Keys.begin();
		return binary_search(t->Keys.begin(),t->Keys.end(),key)?((LeafNode *)t)->Value[x]:"This key does not exist in this B+ tree!";
	}
	~BpTree(){
		head?delete(head):voidFunction();
	}
};


void printOperations(){
	printInfo("\tOperations: \nfind\ninsert\ndelete\nprintKeys\nprintVals");
}
enum operation{
	find,
	insert,
	deletion,
	printVals,
	printKeys,
	def
};
string toLower(string s){
	for(int i=0;i<s.size();i++){
		s[i]=tolower(s[i]);
	}
	return s;
}
operation stringToOperation(string s){
	s=toLower(s);
	if(s=="find")return operation::find;
	if(s=="insert")return operation::insert;
	if(s=="delete")return deletion;
	if(s=="print")return printVals;
	if(s=="printkeys")return printKeys;
	if(s=="printvals")return printVals;
	return def;
}
void Insert(BpTree*t){
	printInfo("Enter key and value");
	string s;
	cin>>s;
	int k;
	cin>>k;
	t->insert(k,s);
}

void Find(BpTree*t){
	printInfo("Enter key");
	int k;
	cin>>k;
	printSuccess(t->find(k));
}

void Delete(BpTree*t){
	printInfo("Enter key");
	int k;
	cin>>k;
	t->remove(k);
}
void callOnTree(){
	BpTree* t=new BpTree(2);
	char op;
	do{
		cout<<">>> ";
		string s;
		cin>>s;
		operation op=stringToOperation(s);
		switch(op){
			case operation::insert:
				Insert(t);
				break;
			case operation::find:
				Find(t);
				break;
			case printKeys:
				t->printKeys();
				break;
			case printVals:
				t->printValues();
				break;
			case deletion:
				Delete(t);
				break;
			default:
				printError("Invalid operation. Try again!!\n");
				break;
		}
	} while (true);
}


void testingFunction(){
	BpTree*t=new BpTree(3);
}
signed main(){
	printOperations();
	printInfo("Press 1 to test the tree\nPress 2 to call on the tree\n");
	int c=1;
	cin>>c;
	(c==1?testingFunction():callOnTree());
	return 0;
}
