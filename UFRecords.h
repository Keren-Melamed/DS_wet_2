#ifndef UFRECORDS_H_
#define UFRECORDS_H_

#include "Record.h"
#include "exception.h"

class UFRecords {

    public:

        UFRecords();
        ~UFRecords();
        UFRecords(const UFRecords& other);

        UFRecords& operator=(const UFRecords& other);

        int getRecordColumn(int recordId);
        int getRecordHeight(int recordId);
        int getRecordPrice(int recordId);

        int getExtrasExcludingRoot(Record* record);

        void resetRecords(int *recordsStocks, int numOfRecords);

        void unify(int recordA , int recordB);

        void clearRecords();

        void updateRecordSales(int recordId);

        void compressPath(Record* record, Record* rootRecord);

        bool sameStackRoot(int recordId1, int recordId2);

        Record* getRoot(int recordId);

    private:

        Record** m_records;
        int m_numOfRecords;
};




/*class UFRecords{
private:

    Record** m_records;
    int m_numOfRecords;

public:

    UFRecords();
    UFRecords(const UFRecords& other);
    ~UFRecords();

    void clearRecords();

    void resetRecords(int *records, int numOfRecords);

    void unify(int recordA, int recordB);

    void compressPath(Record* record, Record* rootRecord);

    void updateRecordSells(int recordId);

    int getExtrasExcludeRoot(Record* record);

    int getRecordColumn(int recordId);

    int getRecordHeight(int recordId);

    int getRecordPrice(int recordId);

    bool sameStackRoots(int recordIdA, int recordIdB);

    Record* getRoot(int recordId);

    UFRecords& operator=(const UFRecords &other);

};*/

#endif //UFRECORDS_H_