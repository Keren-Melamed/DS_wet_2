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
    m_records[above]->UpdateHeight(m_records[below]->getNumOfCopies());
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

void UFRecords::print(std::ostream& os){

    for (int i = 0; i < MAX_SIZE; i++)
    {
        int help = i;
        do{
            os<< " help: " << help << "\n";
            m_records[help]->print(os);
            os << "\n";
            help = m_parents[help];
        }
        while(m_parents[help] != -1);
    }
}
    

    
