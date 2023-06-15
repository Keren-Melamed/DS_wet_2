# include "UFRecords.h"
#include <iostream>

UFRecords::UFRecords(){
    m_records = nullptr;
    m_parents = nullptr;
    m_sizes = nullptr;
}

UFRecords::UFRecords(int *record_stocks, int num_of_records){
    
    int* sizes = new int[num_of_records];
    m_sizes = sizes;

    Record** records = new Record*[num_of_records];
    m_records = records;

    int* parents = new int[num_of_records];
    m_parents = parents;

    for (int i = 0; i < num_of_records; i++)
    {
        m_records[i] = new Record(i, 0, record_stocks[i]);
        m_parents[i] = -1;
        m_sizes[i] = record_stocks[i];
    }

    MAX_SIZE = num_of_records;
   
}

UFRecords::UFRecords(const UFRecords& other){
    
    this->MAX_SIZE = other.MAX_SIZE;
    std::cout << "MAX_SIZE: " << this->MAX_SIZE << std::endl;
    int* sizes = new int[MAX_SIZE];
    this->m_sizes = sizes;

    Record** records = new Record*[MAX_SIZE];
    this->m_records = records;

    int* parents = new int[MAX_SIZE];
    this->m_parents = parents;
    
    for (int i = 0; i < MAX_SIZE; i++)
    {
        std::cout << "record in place: " << i << " " << other.m_records[i] << std::endl;
        this->m_records[i] = other.m_records[i];
        std::cout << "parent in place: " << i << " " << other.m_parents[i] << std::endl;
        this->m_parents[i] = other.m_parents[i];
        std::cout << "size in place: " << i << " " << other.m_sizes[i] << std::endl;
        this->m_sizes[i] = other.m_sizes[i];
    }
    
}

UFRecords& UFRecords::operator=(const UFRecords& other){
    if (this == &other) {
        return *this;
    }

    Record** tempRecords = new Record*[other.MAX_SIZE];
    int* tempSizes = new int[other.MAX_SIZE];
    int* tempParents = new int[other.MAX_SIZE];

    try {
        for(int i=0; i < other.MAX_SIZE; i++) {
            tempRecords[i] = other.m_records[i];
            tempParents[i] = other.m_parents[i];
            tempSizes[i] = other.m_sizes[i];
        }
    } 
    
    catch(...) {
        deleteHelper(tempRecords, tempParents, tempSizes);
        throw;
    }
    deleteHelper(m_records, m_parents, m_sizes);
    MAX_SIZE = other.MAX_SIZE;
    this->m_records = tempRecords;
    this->m_parents = tempParents;
    this->m_sizes = tempSizes;

    return *this;
}

UFRecords::~UFRecords(){
    deleteHelper(m_records, m_parents, m_sizes);
}

int UFRecords::getSize(int index) const{
    return m_sizes[index];
}

void UFRecords::updateSize(int index, int size){
    m_sizes[index] += size;
}

void UFRecords::Union(int child, int parent){
    if(child == parent){
        return;
    }

    m_parents[child] = parent;

    m_records[parent]->UpdateHeight(m_sizes[child]);

    m_sizes[child] += m_sizes[parent];
    m_sizes[parent] = 0;
}

int UFRecords::Find(int r_id){
    if (m_parents[r_id] == -1){
        return r_id;
    }
    return m_parents[r_id] = Find(m_parents[r_id]);
    
}

bool UFRecords::isDisjoint(int r_id1, int r_id2){
    if(Find(r_id1) == Find(r_id2)){
        return true;
    }
    return false;
}

void UFRecords::printParents(std::ostream& os, int r_id){

    while(m_parents[r_id] != -1){
        m_records[r_id]->print(os);
        os << "\n";
        r_id = m_parents[r_id];
    }
    if(m_parents[r_id] == -1){
        os << "no parents, printing only the record: \n";
        m_records[r_id]->print(os);
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
    return m_records[r_id]->getHeight();
}
    
void UFRecords::deleteHelper(Record** records, int* parents, int* sizes){
    for (int i = 0; i < MAX_SIZE; i++)
    {
        delete records[i];
    }
    delete[] parents;
    delete[] sizes;
}

Record* UFRecords::getRecord(int r_id) const
{
    return m_records[r_id];
}
    
