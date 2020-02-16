#include<bits/stdc++.h>
using namespace std;

struct Slice{
    uint8_t size;
    string data;
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
            key->data = (char *)malloc(sizeof(string)*(key->size));
            value->size = 255;
            value->data = (char *)malloc(sizeof(string)*(value->size));
            lsize = 0;
            rsize = 0;
        }
};

class kvstore{
    node *root;
    node *q;
    public:
    void leftrotate(node *p)
    {
         if(p->right==NULL)
               return ;
         else
         {
               node *y=p->right;
               p->rsize-=(y->lsize + y->rsize);
               if(y->left!=NULL)
               {
                      p->right=y->left;
                      p->rsize+=p->right->lsize + p->right->rsize;
                      y->lsize-=p->right->lsize + p->right->rsize;
                      y->left->parent=p;
               }
               else
                      p->right=NULL;
               if(p->parent!=NULL)
                    y->parent=p->parent;
               if(p->parent==NULL)
                    root=y;
               else
               {
                   if(p==p->parent->left)
                           p->parent->left=y;
                   else
                           p->parent->right=y;
               }
               y->left=p;
               y->lsize+=p->lsize + p->rsize;
               p->parent=y;
         }
    }
    node* successor(node *p)
    {
         node *y=NULL;
         if(p->left!=NULL)
         {
             y=p->left;
             while(y->right!=NULL)
                  y=y->right;
         }
         else
         {
             y=p->right;
             while(y->left!=NULL)
                  y=y->left;
         }
         return y;
    }

    void rightrotate(node *p)
    {
         if(p->left==NULL)
              return ;
         else
         {
             node *y=p->left;
             p->lsize-=(p->left->lsize+p->left->rsize);
             if(y->right!=NULL)
             {
                      p->left=y->right;
                      p->lsize+=(p->left->lsize+p->left->rsize);
                      y->rsize-=(p->left->lsize+p->left->rsize);
                      y->right->parent=p;
             }
             else
                     p->left=NULL;
             if(p->parent!=NULL)
                     y->parent=p->parent;
             if(p->parent==NULL)
                   root=y;
             else
             {
                 if(p==p->parent->left)
                       p->parent->left=y;
                 else
                       p->parent->right=y;
             }
             y->right=p;
             y->rsize+=(p->lsize+p->rsize);
             p->parent=y;
         }
    }


    void delfix(node *p)
    {
        node *s;
        while(p!=root&&p->color=='b')
        {
            if(p->parent->left==p)
            {
                s=p->parent->right;
                if(s->color=='r')
                {
                    s->color='b';
                    p->parent->color='r';
                    leftrotate(p->parent);
                    s=p->parent->right;
                }
                if(s->right->color=='b'&&s->left->color=='b')
                {
                    s->color='r';
                    p=p->parent;
                }
                else
                {
                    if(s->right->color=='b')
                    {
                        s->left->color='b'; //==
                        s->color='r';
                        rightrotate(s);
                        s=p->parent->right;
                    }
                    s->color=p->parent->color;
                    p->parent->color='b';
                    s->right->color='b';
                    leftrotate(p->parent);
                    p=root;
                }
            }
            else
            {
                s=p->parent->left;
                if(s->color=='r')
                {
                    s->color='b';
                    p->parent->color='r';
                    rightrotate(p->parent);
                    s=p->parent->left;
                }
                if(s->left->color=='b'&&s->right->color=='b')
                {
                    s->color='r';
                    p=p->parent;
                }
                else
                {
                    if(s->left->color=='b')
                    {
                        s->right->color='b';
                        s->color='r';
                        leftrotate(s);
                        s=p->parent->left;
                    }
                    s->color=p->parent->color;
                    p->parent->color='b';
                    s->left->color='b';
                    rightrotate(p->parent);
                    p=root;
                }
            }
            p->color='b';
            root->color='b';
        }
    }


    bool del(string key){
        node *p;
        p=root;
        node *y=NULL;
        node *q=NULL;
        int found=0;
        while(p!=NULL&&found==0)
        {
            if(p->key->data.compare(key)==0)
                found=1;
            if(found==0)
            {
                if(p->key->data.compare(key)<0)
                    p=p->right;
                else
                    p=p->left;
            }
        }
        if(found==0)
        {
            return false;
        }
        else
        {
          node *par=p;
          while(par->parent!=NULL)
          {
            if(par->parent->left == par)
            par->parent->lsize--;
            else
            par->parent->rsize--;
            par = par->parent;
          }
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
                p->key->data=y->key->data;
            }
            // if(y->color=='b')
                // delfix(q);
        }
        return false;
    }

    bool get(string key){
        node *p;
        p=root;
        node *y=NULL;
        node *q=NULL;
        int found=0;
        while(p!=NULL&&found==0)
        {
            if(p->key->data.compare(key)==0)
                found=1;
            if(found==0)
            {
                if(p->key->data.compare(key)<0)
                    p=p->right;
                else
                    p=p->left;
            }
        }
        if(found == 0)
        return false;
        return true;
    }

    bool put(string key, string value){
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
