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
        node *p;
        p=root;
        node *y=NULL;
        node *q=NULL;
        int found=0;
        while(p!=NULL&&found==0)
        {
            if(p->key->data.compare(x)==0)
                found=1;
            if(found==0)
            {
                if(p->key->data.compare(x)<0)
                    p=p->right;
                else
                    p=p->left;
            }
        }
        if(found==0)
        {
            cout<<"\nElement Not Found.";
            return ;
        }
        else
        {
            cout<<"\nDeleted Element: "<<p->key;
            cout<<"\nColour: ";
            if(p->color=='b')
                cout<<"Black\n";
            else
                cout<<"Red\n";

            if(p->parent!=NULL)
                cout<<"\nParent: "<<p->parent->key;
            else
                cout<<"\nThere is no parent of the node.  ";
            if(p->right!=NULL)
                cout<<"\nRight Child: "<<p->right->key;
            else
                cout<<"\nThere is no right child of the node.  ";
            if(p->left!=NULL)
                cout<<"\nLeft Child: "<<p->left->key;
            else
                cout<<"\nThere is no left child of the node.  ";
            cout<<"\nNode Deleted.";
            if(p->left==NULL||p->right==NULL)
                y=p;
            else
                y=successor(p);
            if(y->left!=NULL)
                q=y->left;
            else
            {
                if(y->right!=NULL)
                    q=y->right;
                else
                    q=NULL;
            }
            if(q!=NULL)
                q->parent=y->parent;
            if(y->parent==NULL)
                root=q;
            else
            {
                if(y==y->parent->left)
                    y->parent->left=q;
                else
                    y->parent->right=q;
            }
            if(y!=p)
            {
                p->color=y->color;
                p->key=y->key;
            }
            if(y->color=='b')
                delfix(q);
        }
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
