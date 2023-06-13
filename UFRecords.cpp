# include "UFRecords.h"

UFRecords::UFRecords(int *record_stocks, int num_of_records){
    
    int* sizes = new int[num_of_records];
    this->m_sizes = sizes;

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

int UFRecords::getSize(int index){
    return m_sizes[index];
}

void UFRecords::updateSize(int index, int size){
    m_sizes[index] += size;
}

void UFRecords::Union(int below, int above){
    if(below == above){
        return;
    }

    m_parents[below] = above;

    m_records[above]->UpdateHeight(m_sizes[below]);

    m_sizes[below] += m_sizes[above];
    m_sizes[above] = 0;
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
        os << m_records[r_id] << "\n";
        r_id = m_parents[r_id];
    }
    if(m_parents[r_id] == -1){
        os << "no parents, printing only the record: \n";
        os << m_records[r_id] << "\n \n ";

    }
}

void UFRecords::printAllParents(std::ostream& os){
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printParents(os, i);
    }
    
}

int UFRecords::getRecordHeight(int r_id){
    return m_records[r_id]->getHeight();
}
    
