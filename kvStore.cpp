#include<bits/stdc++.h>
enum Color {RED, BLACK, DOUBLE_BLACK};

struct Slice{
    uint8_t size;
    char *data;
};
class node
{
    public:
        Slice *key;
        Slice *value;
        node *parent;
        int color;
        node *left;
        node *right;
        int lsize;
        int rsize;
    public:
        node(){
            key = new Slice;
            value = new Slice;
            key->size = 64;
            key->data = (char *)malloc(sizeof(char)*(65));
            value->size = 255;
            value->data = (char *)malloc(sizeof(char)*(257));
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
            p->rsize=0;
            if(y->left!=NULL)
            {
                p->right=y->left;
                p->rsize+=p->right->lsize + p->right->rsize;
                y->lsize=0;
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
            y->lsize+=p->lsize + p->rsize + 1;
            p->parent=y;
        }
    }
    void rightrotate(node *p)
    {
        if(p->left==NULL)
            return ;
        else
        {
            node *y=p->left;
            p->lsize=0;
            if(y->right!=NULL)
            {
                p->left=y->right;
                p->lsize+=(p->left->lsize+p->left->rsize);
                y->rsize=0;
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
            y->rsize+=(p->lsize+p->rsize) + 1;
            p->parent=y;
        }
    }
    int getColor(node *&lode)
    {
        if (lode == nullptr)
            return BLACK;

        return lode->color;
    }

    void setColor(node *&lode, int color)
    {
        if (lode == nullptr)
            return;

        lode->color = color;
    }

    void fixInsertRBTree(node *&ptr) {
        node *parent = nullptr;
        node *grandparent = nullptr;
        while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED)
        {
            parent = ptr->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                node *uncle = grandparent->right;
                if (getColor(uncle) == RED)
                {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    ptr = grandparent;
                }
                else
                {
                    if (ptr == parent->right)
                    {
                        leftrotate(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    rightrotate(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
            else
            {
                node *uncle = grandparent->left;
                if (getColor(uncle) == RED)
                {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    ptr = grandparent;
                }
                else
                {
                    if (ptr == parent->left)
                    {
                        rightrotate(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    leftrotate(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
        }
        setColor(root, BLACK);
    }

    node* deleteBST(node *&root,  char *data)
    {
        if (root == nullptr)
            return root;

        if (strcmp(root->key->data,data) < 0)
            return deleteBST(root->left, data);

        if (strcmp(root->key->data,data) > 0)
            return deleteBST(root->right, data);

        if (root->left == nullptr || root->right == nullptr)
            return root;

        node *temp = minValueNode(root->right);
        root->key->data = temp->key->data;
        root->value->data = temp->value->data;
        return deleteBST(root->right, temp->key->data);
    }

    node *minValueNode(node *&lode)
    {
        node *ptr = lode;

        while (ptr->left != nullptr)
            ptr = ptr->left;

        return ptr;
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
                                 s->left->color=='b';
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
                            if(s && s->left && s->left->color=='b')
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
        }
    }
    node* successor(node *p)
    {
        node *y=NULL;
        if(p->left!=NULL)
        {
            p->lsize--;
            y=p->left;
            while(y->right!=NULL)
            {
              y->rsize--;
              y=y->right;
            }
        }
        else
        {
            p->rsize--;
            y=p->right;
            while(y->left!=NULL)
            {
              y->lsize--;
              y=y->left;
            }
        }
        return y;
    }

    bool put(Slice *key, Slice *value)
    {
        //Your Code Here
        node *p, *q, *par;
        node *t = new node;

        strcpy(t->key->data,key->data);
        t->key->size = key->size;
        strcpy(t->value->data,value->data);
        t->value->size = value->size;
        t->left = NULL;
        t->right = NULL;
        t->color = 'r';
        if(!root)
        {
            root = t;
            t->parent = NULL;
        }
        else{
            p = root;
            q = NULL;
            register int cmp;
            while(p)
            {
                q = p;
                cmp = strcmp(p->key->data,t->key->data);
                if(!cmp)
                {
                    // p->value->data = value;
                    par=p;
                    while(par!=root)
                    {
                        if(par->parent->left == par)
                            par->parent->lsize--;
                        else
                            par->parent->rsize--;
                        par = par->parent;
                    }
                    return true;
                }
                else if(cmp<0)
                {
                    p->rsize++;
                    p = p->right;
                }
                else
                {
                    p->lsize++;
                    p = p->left;
                }
            }
            t->parent = q;
            if(strcmp(q->key->data,t->key->data)<0)
                q->right = t;
            else
                q->left = t;
        }
        fixInsertRBTree(t);
        return false;
    }

    bool del(Slice *key){

        // node *node = deleteBST(root, key);
        //     fixDeleteRBTree(node);
        if(root==NULL)
        return false;
        node *p;
        p=root;
        node *y=NULL;
        node *q=NULL;
        int found=0;
        while(p!=NULL&&found==0)
        {
            if(!strcmp(p->key->data,key->data))
                found=1;
            if(found==0)
            {
                if(strcmp(p->key->data,key->data)<0)
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
            while(par!=root)
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
                strcpy(p->key->data,y->key->data);
                strcpy(p->value->data,y->value->data);
            }
            if(y->color=='b')
            delfix(q);

        }
        return false;
    }
    //
    bool get(Slice *key,Slice *value){
        node *p;
        p=root;
        node *y=NULL;
        node *q=NULL;
        int found=0;
        while(p!=NULL&&found==0)
        {
            if(strcmp(p->key->data,key->data)==0)
                found=1;
                strcpy(value->data,p->value->data);
            if(found==0)
            {
                if(strcmp(p->key->data,key->data)<0)
                    p=p->right;
                else
                    p=p->left;
            }
        }
        if(found == 0)
            return false;
        return true;
    }

    bool get(int N, Slice *key, Slice *value){
        N++;
        node *p;
        p=root;
        if(p->lsize+p->rsize + 1< N)
            return false;
        int curr = 0;
        while(p->lsize + curr + 1 != N)
        {
            if(curr + p->lsize + 1> N)
            {
                if(p->left != NULL)
                    p = p->left;
                else
                    break;
            }
            else if(curr + p->lsize + 1< N)
            {
                if(p->right != NULL)
                {
                    curr+=p->lsize + 1;
                    p=p->right;
                }
                else
                  break;
            }
            // printf("N = %d,curr + lisze = %d ,",N,curr+p->lsize + 1);
            // std::cout<<p->left<<" "<<p->right<<endl;
        }
        strcpy(key->data,p->key->data);
        strcpy(value->data,p->value->data);
        return true;
    }

    bool del(int N){
        N++;
        node *p;
        p=root;
        if(p->lsize+p->rsize + 1 < N)
            return false;
        int curr = 0;
        while(p->lsize + curr + 1 != N)
        {
            if(curr + p->lsize + 1> N)
            {
                if(p->left != NULL)
                    p = p->left;
                else
                    break;
            }
            else if(curr + p->lsize + 1< N)
            {
                if(p->right != NULL)
                {
                    curr+=p->lsize + 1;
                    p=p->right;
                }
                else
                  break;
            }
      }
        del(p->key);
        return true; //not sure
  }

};
