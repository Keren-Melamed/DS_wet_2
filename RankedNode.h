#ifndef WET1_RANKEDNODE_H
#define WET1_RANKEDNODE_H

template <class T>
class RankedNode {
    public:
        
        /**** c'tors and d'tors ****/

        /*
        * c'tor of the RankedNode class with a set value
        *
        * @param value - the value to be saved in the node
        * @result
        *       an instance of RankedNode with a saved value
        */
        RankedNode(T* value);
        //do we need this?

        /*
        * c'tor of the RankedNode class with a set const value
        *
        * @param value - the value to be saved in the node
        * @result
        *       an instance of RankedNode with a saved value
        */
        //RankedNode(const T& value);
        

        /*
        * copy c'tor
        */
        RankedNode(const RankedNode& originalRankedNode);

        /*
        * d'tor
        */
        ~RankedNode() = default;

        /**** Getters and Setters ****/

        /*
        * returns the pointer to the left node
        *
        * @return
        *       m_leftNode
        */
        RankedNode* getLeftNode() const;

        /*
        * returns the pointer to the right node
        *
        * @return
        *       m_rightNode
        */
        RankedNode* getRightNode() const;

        /*
        * returns the value saved in the node
        *
        * @return
        *       m_value
        */
        T* getValue();

        /*
        * returns the height of the node
        * @return
        *       m_height
        */
        int getHeight() const;

        double getRank() const;

        /*
        * setter for left node's pointer
        *
        * @param leftNode - pointer for the new left node
        * @result
        *       void
        */
        void setLeftNode(RankedNode* leftNode);

        /*
        * setter for right node's pointer
        *
        * @param rightNode - pointer for the new right node
        * @result
        *       void
        */
        void setRightNode(RankedNode* rightNode);

        /*
        * setter for the current value saved in the node
        *
        * @param value - the RankedNode's new value
        * @result
        *       void
        */
        void setValue(T* value);

        /*
        * setter for the current height of the node
        *
        * @param height - the RankedNode's new height
        * @result
        *       void
        */
        void setHeight(int height);

        void updateRank(double rank);

    private:

        RankedNode* m_leftNode;
        RankedNode* m_rightNode;

        T* m_value;

        int m_height;
        double m_rank;

};


/*************************RankedNode c'tors & d'tor****************************/


template<class T>
RankedNode<T>::RankedNode(T* value) :
    m_leftNode(nullptr), m_rightNode(nullptr), m_value(value), m_height(0), m_rank(0)
{}

template<class T>
RankedNode<T>::RankedNode(const RankedNode& originalRankedNode) :
    m_leftNode(originalRankedNode.getLeftNode()), m_rightNode(originalRankedNode.getRightNode()), m_value(originalRankedNode.getValue()),
    m_height(originalRankedNode.getHeight()), m_rank(originalRankedNode.getRank())
{}


/*******************************RankedNode Functions***************************/


template<class T>
RankedNode<T>* RankedNode<T>::getLeftNode() const
{
    return m_leftNode;
}

template<class T>
RankedNode<T>* RankedNode<T>::getRightNode() const
{
    return m_rightNode;
}

template<class T>
void RankedNode<T>::setLeftNode(RankedNode* leftNode)
{
    m_leftNode = leftNode;
}

template<class T>
void RankedNode<T>::setRightNode(RankedNode* rightNode)
{
    m_rightNode = rightNode;
}

template<class T>
T* RankedNode<T>::getValue()
{
    return m_value;
}

template<class T>
void RankedNode<T>::setValue(T* value)
{
    m_value = value;
}

template<class T>
int RankedNode<T>::getHeight() const
{
    return m_height;
}

template<class T>
void RankedNode<T>::setHeight(int height)
{
    m_height = height;
}

template<class T>
double RankedNode<T>::getRank() const
{
    return m_rank;
}

template<class T>
void RankedNode<T>::updateRank(double rank)
{
    m_rank += rank;
}

#endif // RANKEDNODE_H