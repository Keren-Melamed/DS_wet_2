#include "HashTable.h"


HashTable::HashTable(int size){
    this->size = size;
    currentSize = 0;
    maxCurrentSize = DEFAULT_TABLE_SIZE;
    data = new AVLTree<Costumer>*[size];
    for (int i = 0; i < size; i++)
    {
        data[i] = nullptr;
    }

}

HashTable::~HashTable(){
    for (int i = 0; i < size; i++)
    {
        delete data[i];
    }
    delete[] this->data;

}

void HashTable::resize(){
    int newSize = this->size * 2;//don't add the plus 1, breaks it for some reason.....
    int oldSize = this->size;
    this->size = newSize;
    AVLTree<Costumer>** oldData = data;

    data = new AVLTree<Costumer>*[newSize]();
    //cout << "first for is about to be entered" <<endl;
    for (int i = 0; i < size; i++)
    {
        data[i] = nullptr;
    }

    //cout << "second for is about to be entered" <<endl;
    for(int i = 0; i < oldSize; i++)
    {
        if(oldData[i] != nullptr)
        {
            addTreeToTable(oldData[i]->getRoot());
        }
    }

    maxCurrentSize = newSize;

    //cout << "third for is about to be entered" <<endl;
    for(int i = 0; i < oldSize; i++)
    {
        if(oldData[i] != nullptr)
        {
            //cout << "i is: " << i << endl;
            oldData[i]->setAllToNullptr(oldData[i]->getRoot());
        }
        delete oldData[i];//might delete nullptr but that shouldn't be a problem
    }
    delete[] oldData;
    //cout << "finishing resize" << endl;
}

void HashTable::addTreeToTable(Node<Costumer>* node)
{
    if(node == nullptr)
    {
        return;
    }
    addTreeToTable(node->getLeftNode());
    Costumer* costumer = node->getValue();
    insertOldCostumer(costumer);
    addTreeToTable(node->getRightNode());
}

void HashTable::insertOldCostumer(Costumer *costumer)
{
    int index = hashFunc(costumer->getId());

    if(data[index] == nullptr)
    {
        data[index] = new AVLTree<Costumer>();
        data[index]->insertValue(costumer);
        currentSize++;
    }

    else
    {
        Node<Costumer>* newCostumerNode = data[index]->findObject(data[index]->getRoot(), costumer);

        if(newCostumerNode == nullptr)//will always be true
        {
            data[index]->insertValue(costumer);
            currentSize++;
        }
    }
}

void HashTable::insert(int c_id, int phone, double expenses, bool isMember){

    int index = hashFunc(c_id);

    //AVLTree<Costumer>* tree = data[index];//the tree we need to add to

    Costumer* newCostumer = new Costumer(c_id, phone, expenses, isMember);
    if(newCostumer == nullptr)
    {
        delete newCostumer;
        throw BadAllocation();
    }

    if(data[index] == nullptr)
    {
        //cout << "a new tree was made in hashTable insert" << endl;
        data[index] = new AVLTree<Costumer>();
        data[index]->insertValue(newCostumer);
        currentSize++;
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
        //cout << "resizing the hashTable" << endl;
        resize();
    }
}

Node<Costumer>* HashTable::getCostumer(int c_id){
    //cout << "getCostumer was entered" << endl;
    int index = hashFunc(c_id);
    //AVLTree<Costumer>* tree = data[index];
    //cout << "the if statement is about to be entered" << endl;
    if(data[index] != nullptr)
    {
        //cout << "the tree isn't nullptr" << endl;
        Costumer* tmpCostumer = new Costumer(c_id, 0);
        Node<Costumer>* tmpNode = data[index]->findObject(data[index]->getRoot(), tmpCostumer);
        //cout << "in getCostumer find object has finished" << endl;
        delete tmpCostumer;
        if(tmpNode == nullptr)
        {
            //cout << "the tmpNode in getCostumer was null" << endl;
            return nullptr;
        }
        return tmpNode;
    }
    else
    {
        //cout << "the tree was nullptr" << endl;
        return nullptr;
    }

}

ostream& HashTable::print(ostream& os) const
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



