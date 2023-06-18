# include "UFRecords.h"
#include <iostream>




UFRecords::UFRecords() : m_records(nullptr), m_numOfRecords(0)
{}

UFRecords::~UFRecords() 
{
    clearRecords();
}

UFRecords::UFRecords(const UFRecords &other) {

    m_numOfRecords = other.m_numOfRecords;

    if (other.m_records == nullptr)
    {
        m_records = nullptr;
        return;
    }

    m_records = new Record*[m_numOfRecords];

    for (int i = 0; i < m_numOfRecords; ++i)
    {
        m_records[i] = new Record(*other.m_records[i]);
    }

}

UFRecords &UFRecords::operator=(const UFRecords &other)
        {

    if (this == &other) {
        return *this;
    }

    clearRecords();

    m_numOfRecords = other.m_numOfRecords;

    if (other.m_records == nullptr) {
        m_records = nullptr;
        return *this;
    }

    m_records = new Record*[m_numOfRecords];

    for (int i = 0; i < m_numOfRecords; ++i) {
        m_records[i] = new Record(*other.m_records[i]);
    }

    return *this;
}

int UFRecords::getRecordColumn(int recordId)
{
    return getRoot(recordId)->getColumn();
}

int UFRecords::getRecordHeight(int recordId)
{
    int extrasExcludingRoot = getExtrasExcludingRoot(m_records[recordId]);
    int recordHeight = extrasExcludingRoot + getRoot(recordId)->getExtra();
    return recordHeight;
}

int UFRecords::getRecordPrice(int recordId)
{
    return m_records[recordId]->getPrice();
}

int UFRecords::getExtrasExcludingRoot(Record *record)
{

    int extrasExcludingRoot = 0;

    while (record->getIsParent() == false)
    {
        extrasExcludingRoot += record->getExtra();
        record = m_records[record->getStackParentId()];
    }
    return extrasExcludingRoot;
}

void UFRecords::resetRecords(int *recordsStocks, int numOfRecords)
{
    if (m_records != nullptr)
    {
        clearRecords();
    }

    m_numOfRecords = numOfRecords;
    m_records = new Record*[numOfRecords];

    for(int i = 0 ; i < numOfRecords; ++i)
    {
        m_records[i] = new Record(i, recordsStocks[i]);
    }
}

void UFRecords::unify(int recordA , int recordB)
{
    Record* rootA = getRoot(recordA);
    int sizeA = rootA->getStackSize();
    Record* rootB = getRoot(recordB);
    int sizeB = rootB->getStackSize();

    int heightRecordA = rootA->getStackHeight();
    int oldExtraStockB = rootB->getExtra();
    int oldExtraStockA = rootA->getExtra();

    if (sizeB <= sizeA)
    {
        rootB->setExtra(oldExtraStockB + heightRecordA - oldExtraStockA);
        rootA->increaseStack(rootB->getStackSize(), rootB->getStackHeight());
        rootB->setStackParent(rootA->getStackParentId());

        rootB->resetRecord();
    }

    else
    {
        rootB->setExtra(oldExtraStockB + heightRecordA);
        int newExtraStockB = rootB->getExtra();
        rootA->setExtra(oldExtraStockA - newExtraStockB);

        rootB->increaseStack(rootA->getStackSize(), rootA->getStackHeight());
        rootB->setColumn(rootA->getColumn());
        rootA->setStackParent(rootB->getStackParentId());
        rootA->resetRecord();
    }
}

void UFRecords::clearRecords()
{
    for (int i = 0; i < m_numOfRecords; ++i)
    {
        delete m_records[i];
    }
    delete[] m_records;
    m_numOfRecords = 0;
}

void UFRecords::updateRecordSales(int recordId)
{
    m_records[recordId]->updateNumberOfBuys();
}

void UFRecords::compressPath(Record* record, Record* rootRecord)
{
    Record* currentRecord = record;
    int heightWithoutRoot = getExtrasExcludingRoot(record);
    int ExtraToReduce = 0;

    while (currentRecord != rootRecord)
    {
        int tmpExtra = currentRecord->getExtra();
        currentRecord->setExtra(heightWithoutRoot - ExtraToReduce);
        ExtraToReduce += tmpExtra;
        currentRecord->setStackParent(rootRecord->getStackParentId());
        currentRecord = m_records[currentRecord->getStackParentId()];
    }
}

bool UFRecords::sameStackRoot(int recordId1, int recordId2)
{
    return getRoot(recordId1)->getColumn() == getRoot(recordId2)->getColumn();
}

Record* UFRecords::getRoot(int recordId)
{
//    assert(recordId < m_numOfRecords);
    Record* currRecord = m_records[recordId];
    while (currRecord->getIsParent() == false)
    {
        currRecord = m_records[currRecord->getStackParentId()];
    }
    compressPath(m_records[recordId], currRecord);
    return currRecord;
}
