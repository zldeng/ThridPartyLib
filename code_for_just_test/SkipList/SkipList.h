#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include <iostream>
#include <fstream>
#include "SkipNode.h"
#include "RandomHeight.h"

using namespace std;

template<class Key,class Obj>
class SkipList
{
private:
    SkipNode<Key,Obj>* head;
    SkipNode<Key,Obj>* tail;

    float probability;
    int maxHeight;
    int curHeight;
    RandomHeight* randGen;

public:
    SkipList(float prob,int maxH,Key* key);
    ~SkipList();

    bool insert(Key* k,Obj* o);
    bool remove(Key* k);
    Obj* retrive(Key* k);
    void dump(ofstream& of);
};


template<class Key,class Obj>
SkipList<Key,Obj>::SkipList(float prob,int maxH,Key* max_key)
{
    curHeight = 1;
    maxHeight = maxH;
    probability = prob;
    randGen = new RandomHeight(maxH,prob);

    head = new SkipNode<Key,Obj>(maxH);
    tail = new SkipNode<Key,Obj>(max_key,(Obj*)nullptr,maxH);

    for(int k = 1;k <= maxH;k++)
    {
        head->fwdNodes[k] = tail;
    }
}

template<class Key,class Obj>
SkipList<Key,Obj>::~SkipList()
{
    SkipList<Key,Obj>* tmp;
    SkipList<Key,Obj>* nxt;

    tmp = head;

    while (tmp)
    {
        nxt = tmp->fwdNodes[1];
        delete tmp;
        tmp = nxt;
    }
}


template<class Key,class Obj>
bool SkipList<Key,Obj>::insert(Key* k,Obj* o)
{
    int lvl = 0,h = 0;

    // all pre-node needed to update
    SkipNode<Key,Obj>** updateVec = new SkipNode<Key,Obj>* [maxHeight+1];

    SkipNode<Key,Obj>* tmp = head;
    Key* cmpKey;

    for(h = curHeight;h >= 1;--h)
    {
        cmpKey = tmp->fwdNodes[h]->getKey();

        while (*cmpKey < *k)
        {
            tmp = tmp->fwdNodes[h];
            cmpKey = tmp->fwdNodes[h]->getKey();
        }

        updateVec[h] = tmp;
    }

    tmp = tmp->fwdNodes[1];
    cmpKey = tmp->getKey();

    if (*k == *cmpKey)
    {
        return false;
    }

    lvl = randGen->newLevel();

    if (lvl > curHeight)
    {
        for(int i = curHeight + 1;i <= lvl;i++)
        {
            updateVec[i] = head;
        }

        curHeight = lvl;
    }

    tmp = new SkipNode<Key,Obj>(k,o,lvl);

    for(int i = 1;i <= lvl;i++)
    {
        tmp->fwdNodes[i] = updateVec[i]->fwdNodes[i];
        updateVec[i]->fwdNodes[i] = tmp;
    }

    return true;
}


template<class Key,class Obj>
bool SkipList<Key,Obj>::remove(Key* key)
{
    SkipNode<Key,Obj>** updateVec = new SkipList<Key,Obj>* [maxHeight];

    SkipNode<Key,Obj>* tmp = head;
    Key* cmpKey;

    for(int h = curHeight;  h > 0;--h)
    {
        cmpKey = tmp->fwdNodes[h]->getKey();

        while (*cmpKey < *key)
        {
            tmp = tmp->fwdNodes[h];
            cmpKey = tmp->fwdNodes[h]->getKey();
        }

        updateVec[h] = tmp;
    }

    tmp = tmp->fwdNodes[1];
    cmpKey = tmp->getKey();

    if (*cmpKey == *key)
    {
        for(int i = 1;i <= curHeight;i++)
        {
            if (updateVec[i]->fwdNodes[i] != tmp)
                break;

            updateVec[i]->fwdNodes[i] = tmp->fwdNodes[i];
        }

        delete tmp;

        while (curHeight > 1 && head->fwdNodes[curHeight]->getKey() == tail->getKey())
            curHeight--;

        return true;
    }

    return false;
}

template<class Key,class Obj>
Obj* SkipList<Key,Obj>::retrive(Key* key)
{
    int h = 0;
    SkipNode<Key,Obj>** updateVec = new SkipNode<Key,Obj>*[maxHeight + 1];

    SkipNode<Key,Obj>* tmp = head;
    Key* cmpKey;

    for (h = curHeight;h >= 1;h--)
    {
        cmpKey = tmp->fwdNodes[h]->getKey();

        while(*cmpKey < *key){
            tmp = tmp->fwdNodes[h];
            cmpKey = tmp->fwdNodes[h]->getKey();
        }

        updateVec[h] = tmp;
    }

    tmp = tmp->fwdNodes[1];
    cmpKey = tmp->getKey();

    if (*cmpKey == *key)
    {
        return tmp->getObj();
    }
    else
    {
        return (Obj*)nullptr;
    }
    
}

template<class Key,class Obj>
void SkipList<Key,Obj>::dump(ofstream& of)
{
    SkipNode<Key,Obj>* tmp = head;

    while (tmp != tail)
    {
        if (tmp == head)
        {
            of << "head node!\n";
        }
        else
        {
            of << "next key: " << tmp->getKey() << endl;
            tmp = tmp->fwdNodes[1]; 
        }
    }

    of << "tail node!\n";
}


#endif
