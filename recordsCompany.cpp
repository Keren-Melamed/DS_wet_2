
#include "recordsCompany.h"
using namespace std;


RecordsCompany::RecordsCompany() : m_numberOfRecords(0)
{}

RecordsCompany::~RecordsCompany()
{
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

    m_UFRecords.resetRecords(records_stocks, number_of_records);

    m_numberOfRecords = number_of_records;

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

    Node<Costumer>* newNode = m_costumers.getCostumer(c_id);
    if(newNode != nullptr)
    {
        //cout << "costumer already exists" << endl;
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
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Costumer newCostumer(c_id, 0);
    Node<Costumer>* newNode = m_costumers.getCostumer(c_id);
    if(newNode == nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }
    else
    {
        int phone = newNode->getValue()->getPhoneNumber();
        Output_t<int> result(phone);
        return result;
    }
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id < 0)
    {
        return StatusType ::INVALID_INPUT;
    }

    Node<Costumer>* newCostumerNode = m_costumers.getCostumer(c_id);


    if(newCostumerNode == nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }

    Costumer* theCostumer = newCostumerNode->getValue();
    if(m_members.findObject(m_members.getRoot(), theCostumer) != nullptr)
    {
        return StatusType::ALREADY_EXISTS;
    }

    newCostumerNode->getValue()->setMember(true);

    try
    {
        /*Costumer* newMember = new Costumer(theCostumer->getId(), theCostumer->getPhoneNumber(),
                                           theCostumer->getExpenses(), theCostumer->getIsMember());
        m_members.insertValue(newMember);*/
        m_members.insertValue(theCostumer);
        return StatusType::SUCCESS;
    }


    catch(BadAllocation& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    //if member is added after prizes were distributed than we need to adjust his expenses, can be done by subtracting
// the accumulated ranks from his expenses ************* happens in tree.insertValue
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
        //cout << "the costumer: " << newNode->getValue()->getId() << endl;
        bool isMember = newNode->getValue()->getIsMember();
        Output_t<bool> result(isMember);
        return result;
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(((c_id < 0) || (r_id < 0))) //maybe only >
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
    
    Costumer* tmpMember = new Costumer(c_id, 0);
    RankedNode<Costumer>* tmpMemberNode = m_members.findObject(m_members.getRoot(), tmpMember);

    if(tmpMemberNode != nullptr) // else do nothing
    {
        tmpMemberNode->getValue()->updateExpenses(m_UFRecords.getRecordPrice(r_id));
    }
    delete tmpMember;
    m_UFRecords.updateRecordSales(r_id);
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if(c_id1 < 0 || c_id2 < c_id1)
    {
        return StatusType::INVALID_INPUT;
    }
    if(c_id1 == c_id2)// don't actually need this but why even call addPrizeHelper and risk a problem?
    {
        return StatusType::SUCCESS;
    }
    addPrizeHelper(c_id1, c_id2 - 1, amount, m_members.getRoot()); //upper limit shouldn't get the bonus,
    // so instead of changing the function just make it one smaller
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

    if(m_members.getRoot() == nullptr){
        delete tmpCostumer;
        return StatusType::DOESNT_EXISTS;
    }

    RankedNode<Costumer>* costumerNode = m_members.findObject(m_members.getRoot(), tmpCostumer);
    if(costumerNode == nullptr){
        delete tmpCostumer;
        return StatusType::DOESNT_EXISTS;
    }


    double extras = getExpensesHelper(m_members.getRoot(), tmpCostumer, 0);
    double totalExpenses = costumerNode->getValue()->getExpenses() - extras;
    //extras += costumerNode->getExtraRank();
    delete tmpCostumer;
    Output_t<double> result(totalExpenses);
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
        return counter + node->getRank();
        //return counter + node->getValue()->getExpenses();
    }
    else if(*tmpCostumer < *(node->getValue()))
    {
        counter += node->getRank();
        //counter += node->getValue()->getExpenses();
        return getExpensesHelper(node->getLeftNode(), tmpCostumer, counter);
    }
    else if(*tmpCostumer > *(node->getValue()))
    {
        counter += node->getRank();
        //counter += node->getValue()->getExpenses();
        return getExpensesHelper(node->getRightNode(), tmpCostumer, counter);
    }
    cout << "somehow no condition was entered in getExpensesHelper" << endl;
    return counter;

}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if((r_id1 < 0) || (r_id2 < 0))
    {
        return StatusType::INVALID_INPUT;
    }

    if((r_id1 >= m_numberOfRecords) || (r_id2 >= m_numberOfRecords))
    {
        return StatusType::DOESNT_EXISTS;
    } 
    
    if(m_UFRecords.sameStackRoot(r_id1, r_id2))
    {
        return StatusType::FAILURE; 
    }
    
    m_UFRecords.unify(r_id2, r_id1);
    return StatusType::SUCCESS;
    
 


    /*try{
        m_UFRecords.Union(r_id1, r_id2);
        return StatusType::SUCCESS;
    }
    catch(InTheSameGroup& a){
        return StatusType::FAILURE;
    }*/


}

StatusType RecordsCompany::getPlace(int r_id, int* column, int* height)
{
    if((r_id < 0) || (column == nullptr) || (height == nullptr))
    {
        return StatusType::INVALID_INPUT;
    }

    if(r_id >= m_numberOfRecords)
    {
        return StatusType::DOESNT_EXISTS;
    }

    *column = m_UFRecords.getRecordColumn(r_id);

    *height = m_UFRecords.getRecordHeight(r_id);

    return StatusType::SUCCESS;

}
