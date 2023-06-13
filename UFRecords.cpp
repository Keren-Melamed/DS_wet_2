# include "UFRecords.h"

UFRecords::UFRecords(int num_of_records){
    
    int* sizes = new int[num_of_records];
    this->m_sizes = sizes;

    ReversedNode** parents = new ReversedNode*[num_of_records];
    m_parents = parents;
    for (int i = 0; i < num_of_records; i++)
    {
        m_parents[i] = new ReversedNode(new Record(i, 0, 0));
    }

    MAX_SIZE = num_of_records;
   
}

void UFRecords::addRecords(int *record_stocks){
    if(abs(sizeof(record_stocks)/sizeof(record_stocks[0])) > MAX_SIZE){
        throw BadAllocation();
    }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        ReversedNode* record = new ReversedNode(new Record(i, 0, record_stocks[i]));
        record->setParent(m_parents[i]);
    }
    
}

int UFRecords::getSize(int index){
    return m_sizes[index];
}

void UFRecords::updateSize(int index, int size){
    m_sizes[index] += size;
}

void UFRecords::Union(int below, int above){
    ReversedNode* A = m_parents[above];
    ReversedNode* B = m_parents[below];

    //updating the parent of above to be the parent pf below
    A->setParent(B);

    //change height of above to be + height of below
    A->getValue()->UpdateHeight(B->getValue()->getHeight());

    //update size of below to be size of both, 
    updateSize(below, getSize(above));

    m_parents[above]->setParent(nullptr);
    updateSize(above, 0);
}

int UFRecords::Find(int r_id){
    while(m_parents[r_id]->getValue()->getId() != r_id){
        m_parents[r_id]->setParent(m_parents[r_id]->getParent());
        r_id = m_parents[r_id]->getValue()->getId();
    }
    return r_id;
}

bool UFRecords::isDisjoint(int r_id1, int r_id2){
    if(Find(r_id1) == Find(r_id2)){
        return true;
    }
    return false;
}

void UFRecords::print(std::ostream& os){
    int i = 0;
    while(m_parents[i]!= NULL){
        os << " group number " << i << "\n";
        ReversedNode* temp = m_parents[i];
        os << " with records ";
        
        while(temp != NULL){
            temp->getValue()->print(os);
            os << "\n";
            temp = temp->getParent();
        }
        os << "\n \n ";
        i++;
    }
}
    
