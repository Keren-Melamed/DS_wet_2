#ifndef WET2_RANKEDAVLTREE_H
#define WET2_RANKEDAVLTREE_H

#include "RankedNode.h"
#include <iostream>
#include "exception.h"

using namespace std;

template<class T>
class RankedAVLTree
{
    public:

        /**** c'tors amd d'tors ****/

        /*
        *c'tor of the RankedAVLTree class
        *
        * @result
        *       an instance of RankedAVLTree
        */
        RankedAVLTree();

        explicit RankedAVLTree(RankedNode<T> root);
        /*
        * copy c'tor
        */
        RankedAVLTree(const RankedAVLTree& originalTree) = default;

        /*
        * d'tor
        */
        ~RankedAVLTree();

        RankedNode<T>* getRoot();

        /**** Methods ****/

        /*
        * calculates the height difference between the right and left nodes
        * @param node - the nodes whose son's heights need to be compared
        * @return
        *       height difference between left and right nodes
        */
        int balanceFactor(RankedNode<T>* node);

        /*
        * calculates the height of a given node
        * @param node - the nodes whose height needs ot be calculated
        * @return
        *       the node's height
        */
        int calculateHeight(RankedNode<T>* node) const;

        /*
        * removes the node from the tree and rebalances it via recursion
        * @param node - the node that needs to be removed
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        void removeValue(T* value);

        /*
        * inserts node into the tree with the corresponding value and rebalances it via recursion
        * @param node - the node that needs to be added
        *        value - the value of the added node
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        void insertValue(T *value);

        /*
        * balances the tree from this root downwards
        * @param node - the root that is to be balanced
        * @return
        *       a pointer to the node that is to be put in the appropriate spot
        */
        RankedNode<T>* balance(RankedNode<T>* node);

        RankedNode<T>* findObject(RankedNode<T>* node, T* value);

        void deleteNodes(RankedNode<T>* node);

        void setAllToNullptr(RankedNode<T>* node);

        void resetAllRanks(RankedNode<T>* node);

        ostream& inOrder(ostream& os, RankedNode<T>* node) const;

        ostream& postOrder(ostream& os, RankedNode<T>* node) const;

        ostream& preOrder(ostream& os, RankedNode<T>* node) const;

    private:

        static int max(int a, int b)
        {
            return (a > b) ? a : b;
        }

        RankedNode<T>* findFather(T* value);
        RankedNode<T>* findFatherHelper(T* value, RankedNode<T>* node);

        RankedNode<T>* getNextMinValue(RankedNode<T>* node);

        RankedNode<T>* removeValueHelper(RankedNode<T>* node, T* value);

        RankedNode<T>* insertValueHelper(RankedNode<T>* node, T* value, double counter);

        RankedNode<T>* findObjectHelper(RankedNode<T>* node, T* value);

        void numOfNodes(RankedNode<T>* node, int* counter);

        void setRoot(RankedNode<T>* root);

        /*
        * different methods for balancing an RankedAVLTree
        */
        RankedNode<T>* rotateLeft(RankedNode<T>* parent);
        RankedNode<T>* rotateRight(RankedNode<T>* parent);
        
        RankedNode<T>* m_root;

};


/***********************RankedAVLTree C'tors and D'tors************************/


template<class T>
RankedAVLTree<T>::RankedAVLTree() : m_root(NULL){}

template<class T>
RankedAVLTree<T>::RankedAVLTree(RankedNode<T> root) : m_root(&root){}

template<class T>
RankedAVLTree<T>::~RankedAVLTree()
{
    deleteNodes(getRoot());
}

template<class T>
void RankedAVLTree<T>::deleteNodes(RankedNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteNodes(node->getLeftNode());
    deleteNodes(node->getRightNode());
    delete node->getValue();// might cause -> doesn't delete the tree in group and was somehow causing a seg fault....(double free to be exact)
    delete node;
}


/**************************RankedAVLTree Functions*****************************/


template<class T>
RankedNode<T>* RankedAVLTree<T>::getNextMinValue(RankedNode<T>* node)
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
        RankedNode<T>* current = node->getRightNode();
        while(current->getLeftNode() != nullptr)
        {
            current = current->getLeftNode();
        }
        return current;
    }
}

template<class T>
RankedNode<T>* RankedAVLTree<T>::findFatherHelper(T* value, RankedNode<T>* node)
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
RankedNode<T>* RankedAVLTree<T>::findFather(T* value)
{
    return findFatherHelper(value, m_root);
}

template<class T>
RankedNode<T>* RankedAVLTree<T>::getRoot()
{
    return m_root;
}

template<class T>
void RankedAVLTree<T>::setRoot(RankedNode<T>* root)
{
    m_root = root;
}

template<class T>
int RankedAVLTree<T>::calculateHeight(RankedNode<T>* node) const
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
int RankedAVLTree<T>::balanceFactor(RankedNode<T>* node)
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
RankedNode<T>* RankedAVLTree<T>::removeValueHelper(RankedNode<T>* node, T* value)
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
            RankedNode<T>* child = node->getLeftNode() ? node->getLeftNode() : node->getRightNode();

            if(child == nullptr)
            {
                child = node;
                node = nullptr;
            }
            else
            {
                RankedNode<T>* father = findFather(node->getValue());
                if(father == nullptr)
                {
                    RankedNode<T>* temp = node;
                    node = child;
                    child = temp;
                }
                else
                {
                    RankedNode<T>* temp = child;
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
            RankedNode<T>* minVal = getNextMinValue(node);

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
void RankedAVLTree<T>::removeValue(T* value)
{
    m_root = removeValueHelper(m_root, value);
}

template<class T>
RankedNode<T>* RankedAVLTree<T>::insertValueHelper(RankedNode<T>* node, T* value, double counter)
{
    if(node == nullptr)
    {
        node = new RankedNode<T>(value);
        if(node == nullptr)
        {
            throw BadAllocation();
        }
        node->updateRank(-counter);
        return node;
    }

    else if (*(node->getValue()) > *value )
    {
        counter += node->getRank();
        node->setLeftNode(insertValueHelper(node->getLeftNode(), value, counter));
    }

    else if (*(node->getValue()) < *value)
    {
        counter += node->getRank();
        node->setRightNode(insertValueHelper(node->getRightNode(), value, counter));
    }

    node->setHeight(calculateHeight(node));
    return balance(node);
}

template<class T>
void RankedAVLTree<T>::insertValue(T* value)
{
    m_root = insertValueHelper(m_root, value, 0);
}

template<class T>
RankedNode<T>* RankedAVLTree<T>::balance(RankedNode<T>* node)
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
RankedNode<T>* RankedAVLTree<T>::findObjectHelper(RankedNode<T>* node, T* value)
{
    if(node == nullptr )
    {
        return nullptr;
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
RankedNode<T>* RankedAVLTree<T>::findObject(RankedNode<T>* node, T* value)
{
    return findObjectHelper(node, value);
}

template<class T>
RankedNode<T>* RankedAVLTree<T>::rotateLeft(RankedNode<T>* parent)
{
    if(parent == nullptr || parent->getRightNode() == nullptr)
    {
        return parent;
    }
    RankedNode<T>* parentRight = parent->getRightNode();
    RankedNode<T>* parentRightLeft = parentRight->getLeftNode();

    parentRight->setLeftNode(parent);
    parent->setRightNode(parentRightLeft);

    parent->setHeight(calculateHeight(parent));
    parentRight->setHeight(calculateHeight(parentRight));

    double parentRank = parent->getRank(), parentRightRank = parentRight->getRank();
    parent->updateRank(-parentRank -parentRightRank/*maybe*/);
    parentRight->updateRank(parentRank);
    if(parentRightLeft != nullptr)//also maybe
    {
        parentRightLeft->updateRank(parentRightRank);
    }


    return parentRight;
}

template<class T>
RankedNode<T>* RankedAVLTree<T>::rotateRight(RankedNode<T>* parent)
{
    if(parent == nullptr || parent->getLeftNode() == nullptr)
    {
        return parent;
    }
    RankedNode<T>* parentLeft = parent->getLeftNode();
    RankedNode<T>* parentLeftRight = parentLeft->getRightNode();

    parentLeft->setRightNode(parent);
    parent->setLeftNode((parentLeftRight));

    parent->setHeight(calculateHeight(parent));
    parentLeft->setHeight(calculateHeight(parentLeft));

    double parentRank = parent->getRank(), parentLeftRank = parentLeft->getRank();
    parent->updateRank(-parentRank -parentLeftRank/*maybe*/);
    parentLeft->updateRank(parentRank);
    if(parentLeftRight != nullptr)//also maybe
    {
        parentLeftRight->updateRank(parentLeftRank);
    }

    return parentLeft;
}

template<class T>
void RankedAVLTree<T>::numOfNodes(RankedNode<T> *node, int* counter)
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
void RankedAVLTree<T>::setAllToNullptr(RankedNode<T>* node)
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
void RankedAVLTree<T>::resetAllRanks(RankedNode<T>* node)
{
    if(node == nullptr)
    {
        return;
    }
    resetAllRanks(node->getLeftNode());
    node->updateRank(-(node->getRank()));
    resetAllRanks(node->getRightNode());
}

template<class T>
ostream& RankedAVLTree<T>::inOrder(ostream& os, RankedNode<T>* node) const
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
ostream& RankedAVLTree<T>::postOrder(ostream& os, RankedNode<T>* node) const
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
ostream& RankedAVLTree<T>::preOrder(ostream& os, RankedNode<T>* node) const
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

#endif // WET2_RANKEDAVLTREE_H