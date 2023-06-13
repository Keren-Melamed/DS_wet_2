#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "recordsCompany.h"

using namespace std;

RecordsCompany::RecordsCompany()
{

}

RecordsCompany::~RecordsCompany()
{

}

StatusType RecordsCompany::newMonth(int* records_stocks, int number_of_records)
{
    return FAILURE;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    return FAILURE;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    return Output_t<int>();
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id < 0)
    {
        return StatusType ::INVALID_INPUT;
    }

    //add the same method used to check if a member already exists as in add costumer

    Costumer* tmp = new Costumer(c_id, 0);
    if(m_members.findObject(m_members.getRoot(), tmp) != nullptr)
    {
        return StatusType::ALREADY_EXISTS;
    }
    //find the costumer in the hash and add him to the tree
    //also change his member flag to true

    //if member is added after prizes were distributed than we need to adjust his expenses, can be done by subtracting the accumelated ranks from his expenses

    return StatusType ::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    return Output_t<bool>();
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id < 0 || r_id < 0)
    {
        return StatusType ::INVALID_INPUT;
    }
    if(r_id >= number_of_records)
    {
        return StatusType::DOESNT_EXISTS;
    }

    //c_id part check if not member
    try
    {
            Costumer* tmpCostumer = new Costumer(c_id, 0);
            RankedNode<Costumer>* tmpNode = m_members.findObject(m_members.getRoot(), tmpCostumer);
            tmpNode->getValue()->buyRecord(/* record.getPrice() */);
    }
    catch(NodeDoesntExist& e)
    {
        return StatusType::DOESNT_EXISTS;
    }

    //r_id part

    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if(c_id1 < 0 || c_id2 < c_id1)
    {
        return StatusType::INVALID_INPUT;
    }
    addPrizeHelper(c_id1, c_id2, amount, m_members.getRoot());
    return StatusType::SUCCESS;
}

void RecordsCompany::addPrizeHelper(int c_id1, int c_id2, double amount, RankedNode<Costumer>* node)
{
    if(node == nullptr)
    {
        return;
    }

    if(*node->getValue() < c_id1)
    {
        if(node->getRightNode() != nullptr)
        {
            addPrizeHelper(c_id1, c_id2, amount, node->getRightNode());
        }
    }

    else if(*node->getValue() > c_id2)
    {
        if(node->getLeftNode() != nullptr)
        {
            addPrizeHelper(c_id1, c_id2, amount, node->getLeftNode());
        }
    }

    else
    {
        node->updateRank(amount);
        //if 2 in a row adds too much ..........................................................
        if(node->getLeftNode() != nullptr)
        {
            addPrizeHelperLeft(c_id1, c_id2, amount, node->getLeftNode());
        }
        if(node->getRightNode() != nullptr)
        {
            addPrizeHelperRight(c_id1, c_id2, amount, node->getRightNode());
        }
    }
}

void RecordsCompany::addPrizeHelperLeft(int c_id1, int c_id2, double amount, RankedNode<Costumer> *node)
{
    if (*node->getValue() > c_id1)
    {
        if (node->getLeftNode() != nullptr)
        {
            addPrizeHelperLeft(c_id1, c_id2, amount, node->getLeftNode());
            //everyone to the right is in the range
        }
    }
    else if(*node->getValue() == c_id1)
    {
        if(node->getLeftNode() != nullptr)
        {
            node->getLeftNode()->updateRank(-amount);
        }
        return;
        //everyone to the right is in the range
    }
    else //value is smaller than c_id1 and therefore is out of range
    {
        node->updateRank(-amount);
        if(node->getRightNode() != nullptr)
        {
            addPrizeHelper(c_id1, c_id2, amount, node->getRightNode());//going back to addPrizeHelper because we don't know what's in range anymore
        }
    }
}

void RecordsCompany::addPrizeHelperRight(int c_id1, int c_id2, double amount, RankedNode<Costumer> *node)
{
    if(*node->getValue() < c_id2)
    {
        if(node->getRightNode() != nullptr)
        {
            addPrizeHelperRight(c_id1, c_id2, amount, node->getRightNode());
            //everyone to the left is in range
        }
    }
    else if(*node->getValue() == c_id2)
    {
        if(node->getRightNode() != nullptr)
        {
            node->getRightNode()->updateRank(-amount);
        }
        return;
        //everyone to the left is in range
    }
    else //value is greater than c_id2 and therefore is out of range
    {
        //maybe reduce amount from this node?
        node->updateRank(-amount);
        if(node->getLeftNode() != nullptr)
        {
            addPrizeHelper(c_id1, c_id2, amount, node->getLeftNode());//going back to addPrizeHelper because we don't know what's in range anymore
            //should change to an additional func that doesn't continue to check the right to save time complexity even though its only logn
        }
    }
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id < 0)
    {
        return Output_t<double>(StatusType::INVALID_INPUT);
    }
    Costumer* tmpCostumer = new Costumer(c_id, 0);
    double extras = getExpensesHelper(m_members.getRoot(), tmpCostumer, 0);
    delete tmpCostumer;
    Output_t<double> result(extras);
    return result;
}

double RecordsCompany::getExpensesHelper(RankedNode<Costumer>* node, Costumer* tmpCostumer, double counter)
{
    if(node == nullptr )
    {
        cout << "getExpensesHelper didnt find the id it was given" << endl;
        return counter;
    }
    else if(*(node->getValue()) == *tmpCostumer)
    {
        return counter + node->getValue()->getExpenses();
    }
    else if(*tmpCostumer < *(node->getValue()))
    {
        counter += node->getValue()->getExpenses();
        return getExpensesHelper(node->getLeftNode(), tmpCostumer, counter);
    }
    else if(*tmpCostumer > *(node->getValue()))
    {
        counter += node->getValue()->getExpenses();
        return getExpensesHelper(node->getRightNode(), tmpCostumer, counter);
    }
    cout << "somehow no condition was entered in getExpensesHelper" << endl;
    return counter;

}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    return FAILURE;
}

StatusType RecordsCompany::getPlace(int r_id, int* column, int* height)
{
    return FAILURE;
}





#pragma clang diagnostic pop