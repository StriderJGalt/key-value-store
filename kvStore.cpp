#include<bits/stdc++.h>
using namespace std;

struct Slice{
        uint8_t size;
        char* data;
};
class node
{
public:
       Slice *key;
       Slice *value;
       node *parent;
       char color;
       node *left;
       node *right;
       int lsize;
       int rsize;
public:
       node(){
        key->size = 63;
        key->data = (char *)malloc(sizeof(char)*(key->size));
        value->size = 255;
        value->data = (char *)malloc(sizeof(char)*(value->size));
        lsize = 0;
        rsize = 0;
      }
};

class kvstore{
      node *root;
      node *q;
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
