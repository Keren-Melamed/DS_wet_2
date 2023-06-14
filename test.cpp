/*
#include "HashTable.h"
#include "UFRecords.h"

void union_aux(UFRecords* records, int child, int parent){
    cout << parent << " is becoming a parent of "<< child << endl;
    cout << "(" << parent << " is above " << child << ")" <<endl;
    records->Union(child, parent);
}

void find_aux(UFRecords* records, int r_id){

    cout << " record " << r_id << " is in heap " << records->Find(r_id) << endl;
}

void size_aux(UFRecords* records, int group){
    cout << "group " << group << " is of size " << records->getSize(group) << endl;
}

void height_aux(UFRecords* records, int r_id){
    cout << "the height of record " << r_id << " is " << records->getRecordHeight(r_id) << endl;
}


int main()
{

    int records_stocks[5] = {10, 20, 30, 40, 50};
    int len = sizeof(records_stocks)/sizeof(records_stocks[0]);

    UFRecords* obj = new UFRecords(records_stocks, len);

    UFRecords* new_obj = new UFRecords(*obj);
    cout << "new_obj: \n" << endl;
    new_obj->printAllParents(cout);

    delete new_obj;

    cout << "obj: \n" <<endl;
    obj->printAllParents(cout);

    union_aux(obj, 1, 2);
    union_aux(obj, 1, 3);

    find_aux(obj, 1);

    obj->printParents(cout, 1);

    height_aux(obj, 3);

    size_aux(obj, 1);


   return 0;
}
*/