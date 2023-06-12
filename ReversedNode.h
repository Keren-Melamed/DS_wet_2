template <class T>
class ReversedNode{
    private:
        T* m_value;
        ReversedNode* m_parent;
    public:
        ReversedNode();
        ReversedNode(T* value){
            m_value = value;
            m_parent = nullptr;
        }

        T* getValue(){
            return m_value;
        }

        ReversedNode* getParent(){
            return m_parent;
        }

        void setParent(ReversedNode* newParent){
            m_parent = newParent;
        }

        void print(std::ostream& os){
            os << m_value;
        }
};