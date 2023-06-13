#include "HashTable.h"
#include "UFRecords.h"

int main()
{
/*
    HashTable<Costumer>* obj = new HashTable<Costumer>(2);

    Costumer a(123, 123465);
    Costumer b(456, 123465);
    Costumer c(789, 123465);

    obj->insert(a);
    obj->insert(b);
    obj->insert(c);

    obj->print(cout);
    
*/
    int records_stocks[4] = {1, 2, 3, 4};
    UFRecords* obj = new UFRecords(records_stocks, 4);


    obj->print(cout);

    cout << "\n 3 is in: " << obj->Find(3) << endl;
    cout << "\n 2 is in: " << obj->Find(2) << endl;

    obj->Union(1 ,2);
    obj->Union(2, 3);
    cout << "\n 1 is in: " << obj->Find(1) << endl;
    obj->print(cout);


   return 0;
}