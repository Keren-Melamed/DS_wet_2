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
    UFRecords* obj = new UFRecords(4);
    for (int i = 0; i < 4; i++)
    {
        ReversedNode* record = new ReversedNode(new Record(i, 0, records_stocks[i]));
        record->setParent(obj->m_parents[i]);
    }

    obj->print(cout);

    cout << obj->Find(3) << endl;
    cout << obj->Find(2) << endl;

    obj->Union(1 ,2);
    obj->Union(2, 3);
    obj->print(cout);


   return 0;
}