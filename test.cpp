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
    

   int records_stocks[4] = {1, 2, 3, 4};
   UFRecords* obj = new UFRecords(records_stocks, 10);

    obj->print(cout);

    cout << obj->Find(3) << endl;
    cout << obj->Find(2) << endl;

    obj->Union(1 ,2);
    obj->print(cout);
*/

    Record* tempRecord = new Record(1, 0, 3);
    ReversedNode* tempNode = new ReversedNode(tempRecord);

    tempNode->print(cout);


   return 0;
}