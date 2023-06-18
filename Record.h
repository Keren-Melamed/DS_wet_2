#ifndef RECORD_H_
#define RECORD_H_

#include <iostream>
#include "exception.h"

class Record {

    public:

        Record(int recordId, int Copies);

        int getStackParentId() const;
        int getColumn() const;
        int getStackHeight() const;
        int getExtra() const;
        int getStackSize() const;
        int getPrice() const;
        bool getIsParent() const;

        void setExtra(int extra);
        void setStackParent(int Parent);
        void setColumn(int Column);
        void updateNumberOfBuys();

        void increaseStack(int additionalSize, int additionalHeight);

        void resetRecord();

        static const int INVALID = -2;

    private:

        bool m_isParent;
        int m_stackParent;
        int m_stackSize;
        int m_stackHeight;
        int m_column;
        int m_extra;
        int m_numberOfBuys;
};

#endif//RECORD_H_
