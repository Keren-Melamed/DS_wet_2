#include "HashTable.h"

int main2(){

    HashTable<Costumer>* obj = new HashTable<Costumer>(2);

    obj->insert(Costumer(123, 123465));
    obj->insert(Costumer(456, 123465));
    obj->insert(Costumer(789, 123465));

    obj->print(cout);

    return 0;
}