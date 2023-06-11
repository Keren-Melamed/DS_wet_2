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

        void insert(Costumer& item);
        Node<Costumer> getCostumer(Costumer& item);
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
    int newSize = this->size * 2;
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
        if(currTree != nullptr){
            int currIndex = hashFunc(currTree->getRoot()->getValue()->getId());

            if(data[i] != nullptr){
                addTo(newData[currIndex], currTree->getRoot());
            }
        }
    }

    maxCurrentSize = newSize;
    delete[] data;
    this->data = newData;
}

template<class Costumer>
void HashTable<Costumer>::insert(Costumer& costumer){

    int index = hashFunc(costumer.getId());

    AVLTree<Costumer>* tree = data[index];//the tree we need to add to

    Node<Costumer>* newCostumer = new Node<Costumer>(&costumer);

    if(newCostumer == nullptr){
        throw BadAllocation();
    }

    if(tree == NULL){
        data[index] = new AVLTree<Costumer>();
        data[index]->setRoot(newCostumer);
        currentSize++;
    }

    else{
        Node<Costumer>* temp = tree->findObject(tree->getRoot(), newCostumer->getValue());

        if(temp == nullptr){
            tree->insertValue(newCostumer->getValue());
            currentSize++;
        }

        else{
            throw NodeAlreadyExists();
        }
    }

    if(currentSize == maxCurrentSize){
        resize();
    }
}

template<class Costumer>
Node<Costumer> HashTable<Costumer>::getCostumer(Costumer& costumer){
    int index = hashFunc(costumer.getId());
    AVLTree<Costumer>* tree = data[index];
    if(tree != nullptr){
        tree->findObject(tree->getRoot(), &costumer);
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
    }
    return os;
    
}










#endif