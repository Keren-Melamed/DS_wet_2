#include "HashTable.h"

int main(){

    HashTable<Costumer>* obj = new HashTable<Costumer>(2);

    Costumer a(123, 123465);
    Costumer b(456, 123465);
    Costumer c(789, 123465);

    obj->insert(a);
    obj->insert(b);
    obj->insert(c);

    obj->print(cout);

    return 0;
}