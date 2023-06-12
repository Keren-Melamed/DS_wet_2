#ifndef UFRECORDS_H_
#define UFRECORDS_H_

#include "Record.h"
#include "ReversedNode.h"
#include "exception.h"


class UFRecords{
    private:
        ReversedNode<Record>** m_parents;
        int* m_sizes;

    public:
        UFRecords(int *records_stocks, int num_of_records);
        UFRecords(const UFRecords& other) = delete;
        UFRecords& operator=(const UFRecords& other) = delete;
        ~UFRecords();

        int getSize(int index);

        void updateSize(int index, int size);

        void Union(int below, int above);

        int Find(int r_id);

        bool isDisjoint(int r_id1, int r_id2);

        void print(std::ostream& os);
};

#endif