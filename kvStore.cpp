#include<bits/stdc++.h>
using namespace std;
enum Color {RED, BLACK, DOUBLE_BLACK};

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
        int color;
        node *left;
        node *right;
        int lsize;
        int rsize;
    public:
        node(){
            key = new Slice;
            value = new Slice;
            key->size = 63;
            /* key->data = (char *)malloc(sizeof(char)*(key->size)); */
            value->size = 255;
            /* value->data = (char *)malloc(sizeof(char)*(value->size)); */
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
    int getColor(node *&node) {
        if (node == nullptr)
            return BLACK;

        return node->color;
    }

    void setColor(node *&node, int color) {
        if (node == nullptr)
            return;

        node->color = color;
    }

    void fixInsertRBTree(node *&ptr) {
        node *parent = nullptr;
        node *grandparent = nullptr;
        while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
            parent = ptr->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                node *uncle = grandparent->right;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    ptr = grandparent;
                } else {
                    if (ptr == parent->right) {
                        leftrotate(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    rightrotate(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            } else {
                node *uncle = grandparent->left;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    ptr = grandparent;
                } else {
                    if (ptr == parent->left) {
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

    node* deleteBST(node *&root,  string data) {
        if (root == nullptr)
            return root;

        if (data.compare(root->key->data) < 0)
            return deleteBST(root->left, data);

        if (data.compare(root->key->data) > 0)
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
    void fixDeleteRBTree(node *&lode) {
        if (lode == nullptr)
            return;

        if (lode == root) {
            root = nullptr;
            return;
        }

        if (getColor(lode) == RED || getColor(lode->left) == RED || getColor(lode->right) == RED) {
            node* child = lode->left != nullptr ? lode->left : lode->right;

            if (lode == lode->parent->left) {
                lode->parent->left = child;
                if (child != nullptr)
                    child->parent = lode->parent;
                setColor(child, BLACK);
                delete (lode);
            } else {
                lode->parent->right = child;
                if (child != nullptr)
                    child->parent = lode->parent;
                setColor(child, BLACK);
                delete (lode);
            }
        } else {
            node *sibling = nullptr;
            node *parent = nullptr;
            node *ptr = lode;
            setColor(ptr, DOUBLE_BLACK);
            while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
                parent = ptr->parent;
                if (ptr == parent->left) {
                    sibling = parent->right;
                    if (getColor(sibling) == RED) {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        leftrotate(parent);
                    } else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            setColor(sibling, RED);
                            if(getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        } else {
                            if (getColor(sibling->right) == BLACK) {
                                setColor(sibling->left, BLACK);
                                setColor(sibling, RED);
                                rightrotate(sibling);
                                sibling = parent->right;
                            }
                            setColor(sibling, parent->color);
                            setColor(parent, BLACK);
                            setColor(sibling->right, BLACK);
                            leftrotate(parent);
                            break;
                        }
                    }
                } else {
                    sibling = parent->left;
                    if (getColor(sibling) == RED) {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rightrotate(parent);
                    } else {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                            setColor(sibling, RED);
                            if (getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        } else {
                            if (getColor(sibling->left) == BLACK) {
                                setColor(sibling->right, BLACK);
                                setColor(sibling, RED);
                                leftrotate(sibling);
                                sibling = parent->left;
                            }
                            setColor(sibling, parent->color);
                            setColor(parent, BLACK);
                            setColor(sibling->left, BLACK);
                            rightrotate(parent);
                            break;
                        }
                    }
                }
            }
            if (lode == lode->parent->left)
                lode->parent->left = nullptr;
            else
                lode->parent->right = nullptr;
            delete(lode);
            setColor(root, BLACK);
        }
    }


    void disp()
    {
         display(root);
    }
    void display(node *p)
    {
         if(root==NULL)
         {
              cout<<"\nEmpty Tree.";
              return ;
         }
         if(p!=NULL)
         {
                    cout<<"\n\t NODE: ";
                    cout<<"\n Key: "<<p->key->data;
                    cout<<"\n lsize: "<<p->lsize;
                    cout<<"\n rsize: "<<p->rsize;
                    cout<<"\n Colour: ";
        if(p->color==BLACK)
         cout<<"Black";
        else
         cout<<"Red";
                    if(p->parent!=NULL)
                           cout<<"\n Parent: "<<p->parent->key->data;
                    else
                           cout<<"\n There is no parent of the node.  ";
                    if(p->right!=NULL)
                           cout<<"\n Right Child: "<<p->right->key->data;
                    else
                           cout<<"\n There is no right child of the node.  ";
                    if(p->left!=NULL)
                           cout<<"\n Left Child: "<<p->left->key->data;
                    else
                           cout<<"\n There is no left child of the node.  ";
                    cout<<endl;
        if(p->left)
        {
                     cout<<"\n\nLeft:\n";
         display(p->left);
        }
        if(p->right)
        {
         cout<<"\n\nRight:\n";
                     display(p->right);
        }
        /*else
         cout<<"\nNo Right Child.\n"*/
         }
    }




    bool put(string key, string value)
    {
        //Your Code Here
        register node *p, *q;
        register node *t = new node;

        t->key->data = key;
        t->key->size = key.length();
        t->value->data = value;
        t->value->size = value.length();
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
            while(p)
            {
                q = p;
                if(!p->key->data.compare(t->key->data))
                {
                    // p->value->data = value;
                    node *par=p;
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
                else if(p->key->data.compare(t->key->data)<0)
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
            if(q->key->data.compare(t->key->data)<0)
                q->right = t;
            else
                q->left = t;
        }
        fixInsertRBTree(t);
        return false;
    }

    bool del(string key){
        node *node = deleteBST(root, key);
            fixDeleteRBTree(node);
        // if(root==NULL)
        // return false;
        // node *p;
        // p=root;
        // node *y=NULL;
        // node *q=NULL;
        // int found=0;
        // while(p!=NULL&&found==0)
        // {
        //     if(!p->key->data.compare(key))
        //         found=1;
        //     if(found==0)
        //     {
        //         if(p->key->data.compare(key)<0)
        //             p=p->right;
        //         else
        //             p=p->left;
        //     }
        // }
        // if(found==0)
        // {
        //     return false;
        // }
        // else
        // {
        //     node *par=p;
        //     while(par!=root)
        //     {
        //         if(par->parent->left == par)
        //             par->parent->lsize--;
        //         else
        //             par->parent->rsize--;
        //         par = par->parent;
        //     }
        //     if(p->left==NULL||p->right==NULL)
        //         y=p;
        //     else
        //         y=successor(p);
        //     if(y->left!=NULL)
        //         q=y->left;
        //     else
        //     {
        //         if(y->right!=NULL)
        //             q=y->right;
        //         else
        //             q=NULL;
        //     }
        //     if(q!=NULL)
        //         q->parent=y->parent;
        //     if(y->parent==NULL)
        //         root=q;
        //     else
        //     {
        //         if(y==y->parent->left)
        //             y->parent->left=q;
        //         else
        //             y->parent->right=q;
        //     }
        //     if(y!=p)
        //     {
        //         p->color=y->color;
        //         p->key->data=y->key->data;
        //         p->value->data=y->value->data;
        //     }
        //     if(y->color=='b')
        //     delfix(q);
        // }
        return false;
    }
    //
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

    pair<string,string> get(int N){
        N++;
        node *p;
        p=root;
        if(p->lsize+p->rsize + 1< N)
            return make_pair("None","None");
        int curr = 0;
        while(p->lsize + curr + 1 != N)
        {
            if(curr + p->lsize + 1> N)
            {
                if(p->left != NULL)
                p = p->left;
                else
                {
                    std::cout<<"Left is NULL"<<endl;
                    break;
                }
            }
            else if(curr + p->lsize + 1< N)
            {
                if(p->right != NULL)
                {
                curr+=p->lsize + 1;
                p=p->right;
                }
                else{
                    std::cout<<"Right is NULL"<<endl;
                    break;
                }
            }
            // printf("N = %d,curr + lisze = %d ,",N,curr+p->lsize + 1);
            // std::cout<<p->left<<" "<<p->right<<endl;
       }
        return make_pair(p->key->data,p->value->data);
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
            if(curr + p->lsize + 1> N && p->left != NULL)
                p = p->left;
            else if(curr + p->lsize + 1< N && p->right != NULL)
            {
                curr+=p->lsize + 1;
                p = p->right;
            }
        }
        return del(p->key->data);
    }

};
