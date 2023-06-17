#ifndef UFRECORDS_H_
#define UFRECORDS_H_

#include "Record.h"
#include "exception.h"


class UFRecords{
private:

        Record* m_records;
        int* m_parents;
        int MAX_SIZE = 0;
        
    public:

        UFRecords();
        UFRecords(int *record_stocks, int num_of_records);
        UFRecords(const UFRecords& other);
        UFRecords& operator=(const UFRecords& other);
        ~UFRecords();

    void addRecords(int *record_stocks);

    void Union(int below, int above);

    int Find(int r_id);

    int FindToStack(int r_id1);

    bool isInSameGroup(int r_id1, int r_id2);

    void printParents(std::ostream& os, int r_id);
    void printAllParents(std::ostream& os);

    int getRecordHeight(int r_id) const;
    Record* getRecord(int r_id) const;

    void printAllRecords(std::ostream& os);

    void deleteHelper(Record* records, int* parents);
};

#endif