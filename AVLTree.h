#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include "Node.h"
#include <iostream>
#include "exception.h"


using namespace std;

template<class T>
class AVLTree
{
public:

    /**** c'tors amd d'tors ****/

    /*
    *c'tor of the AVLTree class
    *
    * @result
    *       an instance of AVLTree
    */
    AVLTree();

    explicit AVLTree(Node<T> root);
    /*
    * copy c'tor
    */
    AVLTree(const AVLTree& originalTree) = default;

    /*
    * d'tor
    */
    ~AVLTree();

    Node<T>* getRoot();

    void setRoot(Node<T>* root);

    /**** Methods ****/

    /*
    * calculates the height difference between the right and left nodes
    * @param node - the nodes whose son's heights need to be compared
    * @return
    *       height difference between left and right nodes
    */
    int balanceFactor(Node<T>* node);

    /*
    * calculates the height of a given node
    * @param node - the nodes whose height needs ot be calculated
    * @return
    *       the node's height
    */
    int calculateHeight(Node<T>* node) const;

    /*
    * removes the node from the tree and rebalances it via recursion
    * @param node - the node that needs to be removed
    * @return
    *       a pointer to the node that is to be put in the appropriate spot
    */
    void removeValue(T* value);

    Node<T>* removeValueHelper(Node<T>* node, T* value);

    /*
    * inserts node into the tree with the corresponding value and rebalances it via recursion
    * @param node - the node that needs to be added
    *        value - the value of the added node
    * @return
    *       a pointer to the node that is to be put in the appropriate spot
    */
    void insertValue(T *value);

    Node<T>* insertValueHelper(Node<T>* node, T* value);

    /*
    * balances the tree from this root downwards
    * @param node - the root that is to be balanced
    * @return
    *       a pointer to the node that is to be put in the appropriate spot
    */
    Node<T>* balance(Node<T>* node);

    Node<T>* findObject(Node<T>* node, T* value);

    Node<T>* getMaximumValue();

    void setMaximumValue(Node<T>* node);

    ostream& inOrder(ostream& os, Node<T>* node) const;

    ostream& postOrder(ostream& os, Node<T>* node) const;

    ostream& preOrder(ostream& os, Node<T>* node) const;

    void treeToArrayInOrderRight(Node<T>* node, T** array, int sizeOfArray, int* counter);

    void deleteNodes(Node<T>* node);

    void setAllToNullptr(Node<T> *node);

private:

    static int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node<T>* findFather(T* value);
    Node<T>* findFatherHelper(T* value, Node<T>* node);

    Node<T>* getNextMinValue(Node<T>* node);

    Node<T>* findObjectHelper(Node<T>* node, T* value);

    Node<T> *findMaximumValue(Node<T> *node);


    void numOfNodes(Node<T>* node, int* counter);

    /*
    * different methods for balancing an AVLTree
    */
    Node<T>* rotateLeft(Node<T>* parent);
    Node<T>* rotateRight(Node<T>* parent);

    Node<T>* m_root;
    Node<T>* m_maximumValue;

};


/***********************AVLTree C'tors and D'tors************************/


template<class T>
AVLTree<T>::AVLTree() : m_root(NULL){}

template<class T>
AVLTree<T>::AVLTree(Node<T> root) : m_root(&root){}

template<class T>
AVLTree<T>::~AVLTree()
{
    int* nodeCounter = new int(0);
    int* counter = new int(0);

    deleteNodes(getRoot());
    delete nodeCounter;
    delete counter;
}

template<class T>
void AVLTree<T>::deleteNodes(Node<T> *node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteNodes(node->getLeftNode());
    deleteNodes(node->getRightNode());
    delete node->getValue();
    delete node;
}


/**************************AVLTree Functions*****************************/


template<class T>
Node<T>* AVLTree<T>::getNextMinValue(Node<T>* node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(node->getRightNode() == nullptr)
    {
        return node;
    }
    else
    {
        Node<T>* current = node->getRightNode();
        while(current->getLeftNode() != nullptr)
        {
            current = current->getLeftNode();
        }
        return current;
    }
}

template<class T>
Node<T>* AVLTree<T>::findFatherHelper(T* value, Node<T>* node)
{
    if(node == nullptr || *value == *(node->getValue()))
    {
        return nullptr;
    }
    else if(*value < *(node->getValue()))
    {
        if (node->getLeftNode() != nullptr)
        {
            if (*(node->getLeftNode()->getValue()) == *value)
            {
                return node;
            }
            else
            {
                return findFatherHelper(value, node->getLeftNode());
            }
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        if(node->getRightNode() != nullptr)
        {
            if(*(node->getRightNode()->getValue()) == *value)
            {
                return node;
            }
            else
            {
                return findFatherHelper(value, node->getRightNode());
            }
        }
        else
        {
            return  nullptr;
        }
    }
}

template<class T>
Node<T>* AVLTree<T>::findFather(T* value)
{
    return findFatherHelper(value, m_root);
}

template<class T>
Node<T>* AVLTree<T>::getRoot()
{
    return m_root;
}

template<class T>
void AVLTree<T>::setRoot(Node<T>* root)
{
    m_root = root;
}

template<class T>
int AVLTree<T>::calculateHeight(Node<T>* node) const
{
    if(node->getLeftNode() == nullptr && node->getRightNode() == nullptr)
    {
        return 0;
    }

    else if(node->getLeftNode() == nullptr && node->getRightNode() != nullptr)
    {
        return (node->getRightNode()->getHeight() + 1);
    }
    else if(node->getLeftNode() != nullptr && node->getRightNode() == nullptr)
    {
        return (node->getLeftNode()->getHeight() + 1);
    }
    else
    {
        return (max(node->getLeftNode()->getHeight(), node->getRightNode()->getHeight()) + 1);
    }
}

template<class T>
int AVLTree<T>::balanceFactor(Node<T>* node)
{
    if(node->getLeftNode() == nullptr && node->getRightNode() == nullptr)
    {
        return 0;
    }
    else if(node->getLeftNode() == nullptr && node->getRightNode() != nullptr)
    {
        return (-1 - node->getRightNode()->getHeight());
    }
    else if(node->getLeftNode() != nullptr && node->getRightNode() == nullptr)
    {
        return (node->getLeftNode()->getHeight() + 1);
    }
    else
    {
        return(node->getLeftNode()->getHeight() - node->getRightNode()->getHeight());
    }
}

template<class T>
Node<T>* AVLTree<T>::removeValueHelper(Node<T>* node, T* value)
{
    if(node == nullptr)
    {
        return node;
    }
    if(*value > *(node->getValue()))
    {
        node->setRightNode(removeValueHelper(node->getRightNode(), value));
    }
    else if(*value < *(node->getValue()))
    {
        node->setLeftNode(removeValueHelper(node->getLeftNode(), value));
    }
    else
    {
        if(node->getLeftNode() == nullptr || node->getRightNode() == nullptr)
        {
            Node<T>* child = node->getLeftNode() ? node->getLeftNode() : node->getRightNode();

            if(child == nullptr)
            {
                child = node;
                node = nullptr;
            }
            else
            {
                Node<T>* father = findFather(node->getValue());
                if(father == nullptr)
                {
                    Node<T>* temp = node;
                    node = child;
                    child = temp;
                }
                else
                {
                    Node<T>* temp = child;
                    bool doesRightExist = (father->getRightNode() != nullptr);
                    bool doesLeftExist = (father->getLeftNode() != nullptr);
                    if(doesLeftExist && father->getLeftNode()->getValue() == node->getValue())
                    {
                        father->setLeftNode(temp);
                    }
                    if(doesRightExist && father->getRightNode()->getValue() == node->getValue())
                    {
                        father->setRightNode(temp);
                    }

                    child = node;
                    node = temp;
                }
            }
            delete child;
        }

        else
        {
            Node<T>* minVal = getNextMinValue(node);

            node->setValue(minVal->getValue());
            node->setRightNode(removeValueHelper(node->getRightNode(), minVal->getValue()));
        }
    }

    if(node == nullptr)
    {
        return node;
    }
    node->setHeight(calculateHeight(node));

    node = balance(node);

    return node;
}

template<class T>
void AVLTree<T>::removeValue(T* value)
{
    m_root = removeValueHelper(m_root, value);
    setMaximumValue(findMaximumValue(m_root));
}

template<class T>
Node<T>* AVLTree<T>::insertValueHelper(Node<T>* node, T* value)
{
    if(node == nullptr)
    {
        node = new Node<T>(value);
        if(node == nullptr)
        {
            throw BadAllocation();
        }
        return node;
    }

    else if (*(node->getValue()) > *value )
    {
        node->setLeftNode(insertValueHelper(node->getLeftNode(), value));
    }

    else if (*(node->getValue()) < *value)
    {
        Node<T>* tmp = insertValueHelper(node->getRightNode(), value);
        node->setRightNode(tmp);
    }

    node->setHeight(calculateHeight(node));
    return balance(node);
}

template<class T>
void AVLTree<T>::insertValue(T* value)
{
    m_root = insertValueHelper(m_root, value);
    setMaximumValue(findMaximumValue(m_root));
}

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    int balance = balanceFactor(node);
    if(balance > 1)
    {
        if(balanceFactor(node->getLeftNode()) > -1)
        {
            return (rotateRight(node));
        }
        else if(balanceFactor(node->getLeftNode()) == -1)
        {
            node->setLeftNode(rotateLeft(node->getLeftNode()));
            return rotateRight(node);
        }
        else
        {
            return node;
        }
    }
    else if(balance < -1)
    {
        if(balanceFactor(node->getRightNode()) < 1)
        {
            return rotateLeft(node);
        }
        else if(balanceFactor(node->getRightNode()) == 1)
        {
            node->setRightNode(rotateRight(node->getRightNode()));
            return rotateLeft(node);
        }
        else
        {
            return node;
        }
    }
    else
    {
        return node;
    }
}

template<class T>
Node<T>* AVLTree<T>::findObjectHelper(Node<T>* node, T* value)
{
    if(node == nullptr )
    {
        throw NodeDoesntExist();
    }
    else if(*(node->getValue()) == *value)
    {
        return node;
    }
    else if(*value < *(node->getValue()))
    {
        return findObjectHelper(node->getLeftNode(), value);
    }
    else if(*value > *(node->getValue()))
    {
        return findObjectHelper(node->getRightNode(), value);
    }
    return nullptr;
}

template<class T>
Node<T>* AVLTree<T>::findObject(Node<T>* node, T* value)
{
    return findObjectHelper(node, value);
}

template<class T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* parent)
{
    if(parent == nullptr || parent->getRightNode() == nullptr)
    {
        return parent;
    }
    Node<T>* parentRight = parent->getRightNode();
    Node<T>* parentRightLeft = parentRight->getLeftNode();

    parentRight->setLeftNode(parent);
    parent->setRightNode(parentRightLeft);

    parent->setHeight(calculateHeight(parent));
    parentRight->setHeight(calculateHeight(parentRight));

    return parentRight;

}

template<class T>
Node<T>* AVLTree<T>::rotateRight(Node<T>* parent)
{
    if(parent == nullptr || parent->getLeftNode() == nullptr)
    {
        return parent;
    }
    Node<T>* parentLeft = parent->getLeftNode();
    Node<T>* parentLeftRight = parentLeft->getRightNode();

    parentLeft->setRightNode(parent);
    parent->setLeftNode((parentLeftRight));

    parent->setHeight(calculateHeight(parent));
    parentLeft->setHeight(calculateHeight(parentLeft));

    return parentLeft;

}

template<class T>
void AVLTree<T>::treeToArrayInOrderRight(Node<T>* node, T **array, int sizeOfArray, int* counter)
{
    if (node == NULL || *counter >= sizeOfArray)
    {
        return;
    }
    else
    {
        if(node->getRightNode() != nullptr)
        {
            treeToArrayInOrderRight(node->getRightNode(), array, sizeOfArray, counter);
        }
        array[*counter] = node->getValue();
        *counter += 1;
        if (node->getLeftNode() != nullptr)
        {
            treeToArrayInOrderRight(node->getLeftNode(), array, sizeOfArray, counter);
        }
    }
}

template<class T>
void AVLTree<T>::numOfNodes(Node<T> *node, int* counter)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        numOfNodes(node->getLeftNode(), counter);
        *counter += 1;
        numOfNodes(node->getRightNode(), counter);
    }
}

template<class T>
void AVLTree<T>::setAllToNullptr(Node<T>* node)
{
    if(node == nullptr)
    {
        return;
    }
    if(node->getLeftNode() != nullptr)
    {
        setAllToNullptr(node->getLeftNode());
    }
    if(node->getRightNode() != nullptr)
    {
        setAllToNullptr(node->getRightNode());
    }
    node->setValue(nullptr);
}

template<class T>
Node<T>* AVLTree<T>::findMaximumValue(Node<T>* node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(node->getRightNode() == nullptr)
    {
        return node;
    }
    return (findMaximumValue(node->getRightNode()));
}

template<class T>
Node<T>* AVLTree<T>::getMaximumValue()
{
    return m_maximumValue;
}

template<class T>
void AVLTree<T>::setMaximumValue(Node<T>* node)
{
    m_maximumValue = node;
}

/************************AVLTree Print Functions*************************/


template<class T>
ostream& AVLTree<T>::inOrder(ostream& os, Node<T>* node) const
{
    if (node == NULL)
    {
        return os;
    }
    else
    {
        inOrder(os, node->getLeftNode());
        node->getValue()->print(os);
        inOrder(os, node->getRightNode());
        return os;
    }
}

template<class T>
ostream& AVLTree<T>::postOrder(ostream& os, Node<T>* node) const
{
    if (node == NULL)
    {
        return os;
    }
    else
    {
        postOrder(os, node->getLeftNode());
        postOrder(os, node->getRightNode());
        node->getValue()->print(os);
        return os;
    }
}

template<class T>
ostream& AVLTree<T>::preOrder(ostream& os, Node<T>* node) const
{
    if(node == NULL)
    {
        return os;
    }
    else
    {
        node->getValue()->print(os);
        preOrder(os, node->getLeftNode());
        preOrder(os, node->getRightNode());
        return os;
    }
}



#endif // WET1_AVLTREE_H