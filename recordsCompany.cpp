#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "recordsCompany.h"

RecordsCompany::RecordsCompany()
{

RecordsCompany::RecordsCompany() : m_numberOfRecords(0)
{}

RecordsCompany::~RecordsCompany()
{
    m_members.setAllToNullptr(m_members.getRoot());
    m_members.setAllToNullptr(m_members.getRoot());
}

StatusType RecordsCompany::newMonth(int* records_stocks, int number_of_records)
{
    if(number_of_records < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    m_members.resetAllRanks(m_members.getRoot());
    resetAllExpenses(m_members.getRoot());

    // something with the records.......................................

    return StatusType::SUCCESS;
}

void RecordsCompany::resetAllExpenses(RankedNode<Costumer> *node)
{
    if(node == nullptr)
    {
        return;
    }
    resetAllExpenses(node->getLeftNode());
    node->getValue()->updateExpenses(-(node->getValue()->getExpenses()));
    resetAllExpenses(node->getRightNode());
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id < 0 || phone < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Costumer newCostumer(c_id, phone);
    Node<Costumer>* newNode = m_costumers.getCostumer(c_id);
    if(newNode != nullptr)
    {
        cout << "costumer already exists" << endl;
        return StatusType::ALREADY_EXISTS;
    }
    else
    {
        try
        {
            m_costumers.insert(c_id, phone);
            return StatusType::SUCCESS;
        }
        catch (BadAllocation &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }

}

void RecordsCompany::resetAllExpenses(RankedNode<Costumer> *node)
{
    if(node == nullptr)
    {
        return;
    }
    resetAllExpenses(node->getLeftNode());
    node->getValue()->updateExpenses(-(node->getValue()->getExpenses()));
    resetAllExpenses(node->getRightNode());
    if(c_id < 0 || phone < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Node<Costumer>* newNode = m_costumers.getCostumer(c_id);
    if(newNode != nullptr)
    {
        cout << "costumer already exists" << endl;
        return StatusType::ALREADY_EXISTS;
    }
    else
    {
        try
        {
            m_costumers.insert(c_id, phone);
            return StatusType::SUCCESS;
        }
        catch (BadAllocation &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }

}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    return Output_t<int>();
}

StatusType RecordsCompany::makeMember(int c_id)
{
    return FAILURE;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Costumer>* newNode = m_costumers.getCostumer(c_id);
    if(newNode == nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }
    else
    {
        bool isMember = newNode->getValue()->getIsMember();
        Output_t<bool> result(isMember);
        return result;
    }
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Costumer>* newNode = m_costumers.getCostumer(c_id);
    if(newNode == nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }
    else
    {
        bool isMember = newNode->getValue()->getIsMember();
        Output_t<bool> result(isMember);
        return result;
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id < 0 || r_id < 0)
    {
        return StatusType ::INVALID_INPUT;
    }
    if(r_id >= m_numberOfRecords)
    {
        return StatusType::DOESNT_EXISTS;
    }

    Node<Costumer>* newCostumerNode = m_costumers.getCostumer(c_id);
    if(newCostumerNode == nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }

    Record* record = m_UFrecords.getRecord(r_id);
    record->updateNumberOfBuys();

    Costumer* tmpMember = new Costumer(c_id, 0);
    RankedNode<Costumer>* tmpMemberNode = m_members.findObject(m_members.getRoot(), tmpMember);
    delete tmpMember;
    if(tmpMemberNode != nullptr) // else do nothing
    {
        tmpMemberNode->getValue()->updateExpenses(record->getPrice());
    }

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
    if((r_id1 > m_numberOfRecords) || (r_id2 > m_numberOfRecords)){
        return StatusType::INVALID_INPUT;
    }
    m_UFrecords.Union(r_id2, r_id1);
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int* column, int* height)
{
    if(r_id > m_numberOfRecords){
        return StatusType::INVALID_INPUT;
    }
    
    int tempColumn = m_UFrecords.Find(r_id);
    column = &tempColumn;

    int tempHeight = (m_UFrecords.getRecordHeight(r_id));
    height = &tempHeight;

    return StatusType::SUCCESS;
    
}

#pragma clang diagnostic pop