#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "AVLTree.h"
#include "Costumer.h"
#include "exception.h"

const int DEFAULT_TABLE_SIZE = 2;

template<class Costumer>
class HashTable
{
private:
    int size;
    int maxCurrentSize;
    int currentSize;
    AVLTree<Costumer>** data;

    void resize();

    int hashFunc(int num) {return num % size;}

public:
    HashTable(int size = DEFAULT_TABLE_SIZE);

    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    ~HashTable();

    void insert(int c_id, int phone);
    Node<Costumer>* getCostumer(int c_id) const;
    void addTo(AVLTree<Costumer>* tree, Node<Costumer>* node);

    ostream& print(ostream& os);

};

template<class Costumer>
HashTable<Costumer>::HashTable(int size){
    this->size = size;
    currentSize = 0;
    maxCurrentSize = DEFAULT_TABLE_SIZE;
    data = new AVLTree<Costumer>*[size];
}

template<class Costumer>
HashTable<Costumer>::~HashTable(){
    for (int i = 0; i < size; i++)
    {
        AVLTree<Costumer>* curr = (this->data)[i];
        if(curr != nullptr){
            delete curr;
        }
    }
    delete[] this->data;

}

template<class Costumer>
void HashTable<Costumer>::addTo(AVLTree<Costumer>* tree, Node<Costumer>* node){
    if(node == nullptr){
        return;
    }
    addTo(tree, node->getLeftNode());
    tree->insertValue(node->getValue());
    addTo(tree, node->getRightNode());
}

template<class Costumer>
void HashTable<Costumer>::resize()
{
    int newSize = this->size * 2;//don't add the plus 1, breaks it for some reason.....
    int oldSize = this->size;
    this->size = newSize;
    AVLTree<Costumer>** newData = new AVLTree<Costumer>*[newSize]();

    for (int i = 0; i < size; i++)
    {
        newData[i] = new AVLTree<Costumer>();
    }


    for (int i = 0; i < oldSize; i++)
    {
        AVLTree<Costumer>* currTree = data[i];
        if(currTree != nullptr)
        {
            int currIndex = hashFunc(currTree->getRoot()->getValue()->getId());

            if(data[i] != nullptr)
            {
                addTo(newData[currIndex], currTree->getRoot());
            }
        }
    }

    maxCurrentSize = newSize;
    delete[] data;
    this->data = newData;
}

template<class Costumer>
void HashTable<Costumer>::insert(int c_id, int phone){

    int index = hashFunc(c_id);

    AVLTree<Costumer>* tree = data[index];//the tree we need to add to

    Costumer* newCostumer = new Costumer(c_id, phone);
    if(newCostumer == nullptr)
    {
        throw BadAllocation();
    }

    if(tree == NULL)
    {
        data[index] = new AVLTree<Costumer>();
        data[index]->insertValue(newCostumer);
        currentSize++;
    }

    else
    {
        Node<Costumer>* newCostumerNode = tree->findObject(tree->getRoot(), newCostumer);

        if(newCostumerNode == nullptr)
        {
            tree->insertValue(newCostumer);
            currentSize++;
        }

        else
        {
            throw NodeAlreadyExists();
        }
    }

    if(currentSize == maxCurrentSize)
    {
        resize();
    }
}

template<class Costumer>
Node<Costumer>* HashTable<Costumer>::getCostumer(int c_id) const{
    int index = hashFunc(c_id);
    AVLTree<Costumer>* tree = data[index];
    if(tree != nullptr)
    {
        Costumer* tmpCostumer = new Costumer(c_id, 0);
        Node<Costumer>* tmpNode = tree->findObject(tree->getRoot(), tmpCostumer);
        delete tmpCostumer;
        if(tmpNode == nullptr)
        {
            return nullptr;
        }
        return tmpNode;
    }
    else
    {
        return nullptr;
    }

}

template<class Costumer>
ostream& HashTable<Costumer>::print(ostream& os)
{
    for (int i = 0; i < size; i++)
    {
        os << " tree number " << i << ": ";
        if(data[i] != nullptr){
            data[i]->inOrder(os, data[i]->getRoot());
        }
        cout << endl;
    }
    return os;
}



#endif // HASHTABLE_H_