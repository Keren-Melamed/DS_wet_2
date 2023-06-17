# include "UFRecords.h"
#include <iostream>

UFRecords::UFRecords(){
    m_records = nullptr;
    m_parents = nullptr;
}

UFRecords::UFRecords(int *record_stocks, int num_of_records){


    Record* records = new Record[num_of_records];
    m_records = records;

    int* parents = new int[num_of_records];
    m_parents = parents;

    for (int i = 0; i < num_of_records; i++)
    {
        m_records[i] = Record(i, 0, record_stocks[i]);
        m_parents[i] = -1;
    }

    MAX_SIZE = num_of_records;

}

UFRecords::UFRecords(const UFRecords& other){

    this->MAX_SIZE = other.MAX_SIZE;

    Record* records = new Record[MAX_SIZE];
    m_records = records;
    
    int* parents = new int[MAX_SIZE];
    m_parents = parents;
    
    for (int i = 0; i < MAX_SIZE; i++)
    {
        this->m_records[i] = other.m_records[i];
        this->m_parents[i] = other.m_parents[i];
    }
}

UFRecords& UFRecords::operator=(const UFRecords& other){
    if (this == &other) {
        return *this;
    }

    Record* tempRecords = new Record[other.MAX_SIZE];
    int* tempParents = new int[other.MAX_SIZE];

    try {
        for(int i=0; i < other.MAX_SIZE; i++) {
            tempRecords[i] = other.m_records[i];
            tempParents[i] = other.m_parents[i];
        }
    }

    catch(...) {
        deleteHelper(tempRecords, tempParents);
        throw;
    }
    deleteHelper(m_records, m_parents);
    MAX_SIZE = other.MAX_SIZE;
    this->m_records = tempRecords;
    this->m_parents = tempParents;

    return *this;
}

UFRecords::~UFRecords(){
    deleteHelper(m_records, m_parents);
}

void UFRecords::Union(int r_id1, int r_id2){
    if(r_id2 == r_id1){
        return;
    }
    if(isInSameGroup(r_id1, r_id2)){
        throw InTheSameGroup();
    }

    m_parents[r_id1] = r_id2;

    m_records[r_id1].UpdateHeight(m_records[r_id2].getHeight());
}

int UFRecords::Find(int r_id){
    if (m_parents[r_id] == -1){
        return r_id;
    }
    return m_parents[r_id] = Find(m_parents[r_id]);

}

bool UFRecords::isInSameGroup(int r_id1, int r_id2){
    if(Find(r_id1) == Find(r_id2)){
        return true;
    }
    return false;
}

void UFRecords::printParents(std::ostream& os, int r_id){

    while(m_parents[r_id] != -1){
        m_records[r_id].print(os);
        os << "\n";
        r_id = m_parents[r_id];
    }
    if(m_parents[r_id] == -1){
        os << "no parents, printing only the record: \n";
        m_records[r_id].print(os);
        os << "\n \n";

    }
}

void UFRecords::printAllParents(std::ostream& os){
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printParents(os, i);
    }
}

int UFRecords::getRecordHeight(int r_id) const{
    return m_records[r_id].getHeight();
}
    
void UFRecords::deleteHelper(Record* records, int* parents){
    delete[] records;
    delete[] parents;
}

Record* UFRecords::getRecord(int r_id) const
{
    return &m_records[r_id];
}
    
void UFRecords::printAllRecords(std::ostream& os){
    os << "printing all records:\n" ;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        m_records[i].print(os);
        os << "\n";
    }
}