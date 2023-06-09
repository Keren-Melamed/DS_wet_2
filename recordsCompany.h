#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "Costumer.h"
#include "RankedAVLTree.h"
#include "HashTable.h"
#include "UFRecords.h"
#include <memory>

using namespace std;

class RecordsCompany {
private:

    int m_numberOfRecords;

    void addPrizeHelper(int c_id1, int c_id2, double amount, RankedNode<Costumer>* node);
    void addPrizeHelperLeft(int c_id1, int c_id2, double amount, RankedNode<Costumer>* node);
    void addPrizeHelperRight(int c_id1, int c_id2, double amount, RankedNode<Costumer>* node);

    void resetAllExpenses(RankedNode<Costumer>* node);

    double getExpensesHelper(RankedNode<Costumer>* node, Costumer* tmpCostumer, double counter);

public:

    HashTable m_costumers;
    RankedAVLTree<Costumer> m_members;
    UFRecords m_UFRecords;

    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int* records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int* column, int* height);

};

#endif