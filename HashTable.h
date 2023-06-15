#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "AVLTree.h"
#include "Costumer.h"
#include "exception.h"

const int DEFAULT_TABLE_SIZE = 5;

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

    void addTreeToTable(Node<Costumer>* node);

public:
    HashTable(int size = DEFAULT_TABLE_SIZE);

    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    ~HashTable();

    void insert(int c_id, int phone, double expenses = 0, bool isMember = false);
    Node<Costumer>* getCostumer(int c_id);
    void addTo(AVLTree<Costumer>* tree, Node<Costumer>* node);

    ostream& print(ostream& os);

};

template<class Costumer>
HashTable<Costumer>::HashTable(int size){
    this->size = size;
    currentSize = 0;
    maxCurrentSize = DEFAULT_TABLE_SIZE;
    data = new AVLTree<Costumer>*[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = nullptr;
    }
    
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
void HashTable<Costumer>::resize(){
    int newSize = this->size * 2;//don't add the plus 1, breaks it for some reason.....
    int oldSize = this->size;
    this->size = newSize;
    AVLTree<Costumer>** oldData = data;

    data = new AVLTree<Costumer>*[newSize]();
    for (int i = 0; i < size; i++)
    {
        data[i] = nullptr;
    }

    for(int i = 0; i < oldSize; i++)
    {
        if(oldData[i] != nullptr){
            addTreeToTable(oldData[i]->getRoot());
        }
    }

    maxCurrentSize = newSize;

    for(int i = 0; i < oldSize; i++)
    {
        if(oldData[i] != nullptr){
            oldData[i]->setAllToNullptr(data[i]->getRoot());
            delete oldData[i];
        }
    }
    delete[] oldData;
}
template<class Costumer>
void HashTable<Costumer>::addTreeToTable(Node<Costumer>* node)
{
    if(node == nullptr)
    {
        return;
    }
    addTreeToTable(node->getLeftNode());
    Costumer* costumer = node->getValue();
    insert(costumer->getId(), costumer->getPhoneNumber(), costumer->getExpenses(), costumer->getIsMember());
    addTreeToTable(node->getRightNode());
}

template<class Costumer>
void HashTable<Costumer>::insert(int c_id, int phone, double expenses, bool isMember){

    int index = hashFunc(c_id);
    cout << "insert index: " << index << endl;

    Costumer* newCostumer = new Costumer(c_id, phone);
    if(newCostumer == nullptr)
    {
        throw BadAllocation();
    }

    if(data[index] == nullptr)
    {
        data[index] = new AVLTree<Costumer>();
        data[index]->insertValue(newCostumer);
        currentSize++;
        cout << "data[index] in insert " << data[index]->getRoot()->getValue()->getId();
    }

    else
    {
        Node<Costumer>* newCostumerNode = data[index]->findObject(data[index]->getRoot(), newCostumer);

        if(newCostumerNode == nullptr)
        {
            data[index]->insertValue(newCostumer);
            currentSize++;
        }

        else
        {
            delete newCostumer;
            throw NodeAlreadyExists();
        }
    }

    if(currentSize == maxCurrentSize)
    {
        resize();
    }
}

template<class Costumer>
Node<Costumer>* HashTable<Costumer>::getCostumer(int c_id){
    
    int index = hashFunc(c_id);
    cout << "get costumer index: " << index << endl;
    AVLTree<Costumer>* tree = data[index];

    if(tree != nullptr)
    {
        cout << "the tree isn't nullptr" << endl;
        Costumer* tmpCostumer = new Costumer(c_id, 0);
        Node<Costumer>* tmpNode = tree->findObject(tree->getRoot(), tmpCostumer);
        //cout << "in getCostumer find object has finished" << endl;
        delete tmpCostumer;
        if(tmpNode == nullptr)
        {
            cout << "the tmpNode in getCostumer was null" << endl;
            return nullptr;
        }
        return tmpNode;
    }
    else
    {
        cout << "the tree was nullptr" << endl;
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