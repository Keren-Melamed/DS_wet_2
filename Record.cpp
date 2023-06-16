#include "Record.h"

Record::Record() : m_id(-1), m_number_of_buys(0), m_copies(0), m_height(0)
{}

Record::Record(int id, int number_of_buys, int copies) : m_id(id), m_number_of_buys(number_of_buys), m_copies(copies),
                                                        m_height(0)
{}

int Record::getId() const{
    return m_id;
}

int Record::getNumOfCopies() const{
    return m_copies;
}

int Record::getNumberOfBuys() const{
    return m_number_of_buys;
}

int Record::getHeight() const{
    return m_height;
}

void Record::setNumberOfCopies(int copies){
    m_copies = copies;
}

void Record::setNumberOfBuys(int number_of_buys){
    m_number_of_buys = number_of_buys;
}

void Record::UpdateHeight(int height){
    m_height += height;
}

void Record::print(std::ostream& os){
    os << "record id: " << m_id;
    os << " copies: " << m_copies;
    os << " buys: " << m_number_of_buys;
}

void Record::updateNumberOfBuys(){
    m_number_of_buys += 1;
}

int Record::getPrice() const
{
    return (100 + getNumberOfBuys());
}






