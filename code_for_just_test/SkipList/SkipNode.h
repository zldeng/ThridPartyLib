#ifndef _SKIPNODE_H_
#define _SKIPNODE_H_

struct  productData
{
    float cost;
    int quantity;
    int location;
};


template <class Key,class Obj>
class SkipList;

template <class Key,class Obj>
class SkipNode
{
private:
    int nodeHeight;
    Key* key;
    Obj* obj;

public:
    SkipNode(Key* k,Obj* o,int h);
    SkipNode(int h);
    ~SkipNode();

    Key* getKey()
    {
        return key;
    }

    Obj* getObj()
    {
        return obj;
    }

    int getHgt()
    {
        return nodeHeight;
    }

    SkipNode** fwdNodes;
};

template<class Key,class Obj>
SkipNode<Key,Obj>::~SkipNode()
{
    delete key;
    delete value;
    delete[] fwdNodes;
}


template<class Key,class Obj>
SkipNode<Key,Obj>::SkipNode(Key* k,Obj* o,int h)
{
    nodeHeight = h;
    key = k;
    obj = o;

    fwdNodes = new SkipNode<Key,Obj>*[h+1];
    for(int i = 1;i <= h;i++)
    {
        fwdNodes[i] = (SkipNode<Key,Obj>*) nullptr;
    }
}

template<class Key,class Obj>
SkipNode<Key,Obj>::SkipNode(int h)
{
    nodeHeight = h;
    key = nullptr;
    obj = nullptr;
    fwdNodes = new SkipNode<Key,Obj>*[h+1];

    for(int k = 1;k < h+1;++k)
    {
        fwdNodes[k] = nullptr;
    }
}

#endif