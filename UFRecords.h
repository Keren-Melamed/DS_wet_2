#ifndef UFRECORDS_H_
#define UFRECORDS_H_

#include "Record.h"
#include "ReversedNode.h"
#include "exception.h"


class UFRecords{
    private:

        int MAX_SIZE = 0;

    public:

        ReversedNode** m_parents;
        int* m_sizes;

        UFRecords(int num_of_records);
        UFRecords(const UFRecords& other) = delete;
        UFRecords& operator=(const UFRecords& other) = delete;
        ~UFRecords();

        void addRecords(int *record_stocks);

        int getSize(int index);

        void updateSize(int index, int size);

        void Union(int below, int above);

        int Find(int r_id);

        bool isDisjoint(int r_id1, int r_id2);

        void print(std::ostream& os);

        
};

#endif