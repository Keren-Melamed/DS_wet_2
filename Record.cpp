#include "Record.h"

Record::Record(int recordId, int Copies) : m_isParent(true), m_stackParent(recordId), m_stackSize(1),
                                           m_stackHeight(Copies), m_column(recordId), m_extra(0), m_numberOfBuys(0)
{}

int Record::getStackParentId() const
{
    return m_stackParent;
}

int Record::getColumn() const
{
    return m_column;
}

int Record::getExtra() const
{
    return m_extra;
}

int Record::getStackHeight() const
{
    return m_stackHeight;
}

void Record::setExtra(int extra) 
{
    m_extra = extra;
}

void Record::setStackParent(int parent)
{
    m_stackParent = parent;
    m_isParent = false;
}

int Record::getStackSize() const
{
    return m_stackSize;
}


void Record::setColumn(int Column)
{
    m_column = Column;
}

void Record::resetRecord()
{
    m_column = INVALID;
    m_stackHeight = INVALID;
    m_stackSize = INVALID;
}

void Record::increaseStack(int additionalSize, int additionalHeight)
{
    m_stackSize += additionalSize;
    m_stackHeight += additionalHeight;
}

void Record::updateNumberOfBuys()
{
    m_numberOfBuys += 1;
}

int Record::getPrice() const
{
    int price = m_numberOfBuys + 100;
    return price;
}

bool Record::getIsParent() const
{
    return m_isParent;
}