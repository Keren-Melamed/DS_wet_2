<<<<<<< HEAD
#ifndef DS_WET_2_REVERSENODE_H
#define DS_WET_2_REVERSENODE_H

#include <iostream>
#include "Record.h"

class ReversedNode{
private:
    Record* m_value;
    ReversedNode* m_parent;

public:
    ReversedNode(){
        m_value = nullptr;
        m_parent = nullptr;
    }
    ~ReversedNode() = default;

    ReversedNode(Record* value){
        m_value = value;
        m_parent = nullptr;
    }

    Record* getValue(){
        return m_value;
    }

    ReversedNode* getParent(){
        return m_parent;
    }

    void setParent(ReversedNode* newParent){
        m_parent = newParent;
    }

    void print(std::ostream& os){
        os << this->m_value->getId();
    }
};
#endif //DS_WET_2_REVERSENODE_H
=======
#ifndef DS_WET_2_REVERSENODE_H
#define DS_WET_2_REVERSENODE_H

#include <iostream>
#include "Record.h"

class ReversedNode{
private:
    Record* m_value;
    ReversedNode* m_parent;

public:
    ReversedNode(){
        m_value = nullptr;
        m_parent = nullptr;
    }
    ~ReversedNode() = default;

    ReversedNode(Record* value){
        m_value = value;
        m_parent = nullptr;
    }

    Record* getValue(){
        return m_value;
    }

    ReversedNode* getParent(){
        return m_parent;
    }

    void setParent(ReversedNode* newParent){
        m_parent = newParent;
    }

    void print(std::ostream& os){
        os << this->m_value->getId();
    }
};
#endif //DS_WET_2_REVERSENODE_H
>>>>>>> daf3e761afbadea9901bfadc004643151e57fd8b
