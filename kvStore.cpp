#include<bits/stdc++.h>
using namespace std;

struct Slice{
        uint8_t size;
        char* data;
};
struct node
{
       Slice *key;
       key->size = 64;
       key->data = malloc(sizeof(char)*(key->size));
       Slice *value;
       value->size = 256;
       value->data = malloc(sizeof(char)*(value->size));
       node *parent;
       char color;
       node *left;
       node *right;
};
class kvstore{
public:
	pair<string,string> get(string key){
		//Your Code Here
    pair<string,string> temp = make_pair("key","value");
    return temp;
	}

	bool put(string key, string value){
		//Your Code Here
		return false;
	}

	bool del(string key){
		//Your Code Here
		return false;
	}

	pair<string,string> get(int N){
		// Your Code Here
		pair<string,string> temp = make_pair("key","value");
		return temp;
	}

	bool del(int N){
		// Your Code Here
		return true;
	}
};
