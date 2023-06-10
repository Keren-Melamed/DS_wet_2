#ifndef WET1_NODE_H
#define WET1_NODE_H

template <class T>
class Node {
    public:
        
        /**** c'tors and d'tors ****/

        /*
        * c'tor of the Node class with a set value
        *
        * @param value - the value to be saved in the node
        * @result
        *       an instance of Node with a saved value
        */
        Node(T* value);
        //do we need this?

        /*
        * c'tor of the Node class with a set const value
        *
        * @param value - the value to be saved in the node
        * @result
        *       an instance of Node with a saved value
        */
        //Node(const T& value);
        

        /*
        * copy c'tor
        */
        Node(const Node& originalNode);

        /*
        * d'tor
        */
        ~Node() = default;

        /**** Getters and Setters ****/

        /*
        * returns the pointer to the left node
        *
        * @return
        *       m_leftNode
        */
        Node* getLeftNode() const;

        /*
        * returns the pointer to the right node
        *
        * @return
        *       m_rightNode
        */
        Node* getRightNode() const;

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

        /*
        * setter for left node's pointer
        *
        * @param leftNode - pointer for the new left node
        * @result
        *       void
        */
        void setLeftNode(Node* leftNode);

        /*
        * setter for right node's pointer
        *
        * @param rightNode - pointer for the new right node
        * @result
        *       void
        */
        void setRightNode(Node* rightNode);

        /*
        * setter for the current value saved in the node
        *
        * @param value - the Node's new value
        * @result
        *       void
        */
        void setValue(T* value);

        /*
        * setter for the current height of the node
        *
        * @param height - the Node's new height
        * @result
        *       void
        */
        void setHeight(int height);

    private:

        Node* m_leftNode;
        Node* m_rightNode;

        T* m_value;

        int m_height;

};


/*************************Node c'tors & d'tor****************************/


template<class T>
Node<T>::Node(T* value) :
    m_leftNode(nullptr), m_rightNode(nullptr), m_value(value), m_height(0)
{}

template<class T>
Node<T>::Node(const Node& originalNode) :
    m_leftNode(originalNode.getLeftNode()), m_rightNode(originalNode.getRightNode()), m_value(originalNode.getValue()),
    m_height(originalNode.getHeight())
{}


/*******************************Node Functions***************************/


template<class T>
Node<T>* Node<T>::getLeftNode() const
{
    return m_leftNode;
}

template<class T>
Node<T>* Node<T>::getRightNode() const
{
    return m_rightNode;
}

template<class T>
void Node<T>::setLeftNode(Node* leftNode)
{
    m_leftNode = leftNode;
}

template<class T>
void Node<T>::setRightNode(Node* rightNode)
{
    m_rightNode = rightNode;
}

template<class T>
T* Node<T>::getValue()
{
    return m_value;
}

template<class T>
void Node<T>::setValue(T* value)
{
    m_value = value;
}

template<class T>
int Node<T>::getHeight() const
{
    return m_height;
}

template<class T>
void Node<T>::setHeight(int height)
{
    m_height = height;
}




#endif