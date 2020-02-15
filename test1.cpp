#include<iostream>
using namespace std;

class bnode 
{
    int * keys;
    int t, n;
    bnode **c;
    bool leaf;

public:
    bnode(int _t, bool _leaf)
    {
        t = t1;
        leaf = leaf1;
        keys = new int[2*t-1];
        c = new bnode *[2*t];
        n = 0;
    }
    void insert(int key);
    void split(int i, bnode *child);
    void traverse();
    bnode *search(int key);

friend class btree;
};

class btree{
    bnode *root;
    int t;

public:
    btree(int _t)
    {
        root = NULL;
        t = _t;
    }
    
    void traverse()
    {
        if(root != NULL)
            root -> traverse();
    }

    bnode * search(int key)
    {
        if(!root)
            return NULL;
        else
            return(root->search(key));
    }

    void insertToTree(int key);
};

// bnode::bnode(int t1, bool leaf1)
// {
//     t = t1;
//     leaf = leaf1;
//     keys = new int[2*t-1];
//     c = new bnode *[2*t];
//     n = 0;
// }

void bnode::traverse()
{
    for(int i=0; i<n; i++)
    {
        if (!leaf)
            c[i]->traverse();
        printf("%d ", keys[i]);
    }

    if(!leaf)
        c[i]->traverse();
}

bnode *bnode::search(int s)
{
    int i=0;
    while(i<n && s>keys[i])
        i++;

    if (keys[i] == s)
        return this;

    if(leaf)
        return NULL;
    
    return c[i]->search(s);
}

void btree::insertToTree(int key)
{
    if(!root)
    {
        root = new bnode(t, true);
        root->keys[0] = key;
        root->n = 1;
    }
    else{
        if(root->n == 2*t-1)
        {
            bnode *cb = new bnode(t, false);
            cb->c[0] = root;
            cb->split(0, root);
            
            int i = 0;
            if(cb->keys[0] < key)
                i++;
            cb->c[i]->insert(key);
            root = cb;
        }
        else
            root->insert(key);
    }
}

void bnode::insert(int key)
{
    int i = n-1;
    if(leaf)
    {
        while(i>=0 && keys[i] > key)
        {
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = key;
        n = n+1;
    }
    else{
        while(i>=0 && keys[i] > key)
        {
            i--;
        }

        if(c[i+1]->n == 2*t-1)
        {
            split(i+1, c[i+1]);
            if(keys[i+1] < key)
                i++;
        }
        c[i+1]->insert(key);
    }
}

void bnode::split(int i, bnode *y)
{
    bnode * nd = new bnode (y->t, y->leaf);
    nd->n = t-1;

    for(int j=0; j<t-1; j++)
        nd->keys[j] = y->keys[j+t]

    if(!(y->leaf))
        for(int j=0; j<t; j++)
            nd->c[j] = y->c[j+t];

    y->n = t-1;

    for(int j=n; j >= i+1; j--)
        c[j+1] = c[j];
    
    c[i+1] = nd;

    for(int j=n-1; j>= i; j--)
        keys[j+1] = keys[j];
    
    keys[i] = y->keys[t-1];

    n += 1;
}

