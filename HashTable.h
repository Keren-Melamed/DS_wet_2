#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "AVLTree.h"
#include "Costumer.h"
#include "exception.h"

const int DEFAULT_TABLE_SIZE = 2;

class HashTable
{
private:
    int size;
    int maxCurrentSize;
    int currentSize;

    void resize();

    int hashFunc(int num) const {return num % size;}

    void addTreeToTable(Node<Costumer>* node);

public:

    AVLTree<Costumer>** data;

    explicit HashTable(int size = DEFAULT_TABLE_SIZE);
    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    ~HashTable();

    void insert(int c_id, int phone, double expenses = 0, bool isMember = false);
    Node<Costumer>* getCostumer(int c_id);

    ostream& print(ostream& os) const;

};

#endif // HASHTABLE_H_