#ifndef DS_WET_2_COSTUMER_H
#define DS_WET_2_COSTUMER_H

#include "utilesWet2.h"
#include <iostream>

class Costumer
{
    private:
        int m_id;
        int m_phoneNumber;
        double m_expenses;
        bool m_isMember;

    public:
        Costumer(int id, int phoneNumber, double expenses = 0, bool isMember = false);
        Costumer(const Costumer& other) = delete;//no need for a copy c'tor;
        ~Costumer() = default;


        /*** Getters ***/
        int getId() const;
        int getPhoneNumber() const;
        double getExpenses() const;
        bool getIsMember() const;

        /*** Methods ***/
        void buyRecord(double price);
        void updateExpenses(double expense);
        void setMember(bool isMember);

        /*** Operators ***/
        friend bool operator==(const Costumer& a, const Costumer& b);
        bool operator<(const Costumer& other) const;
        bool operator>(const Costumer& other) const;

        bool operator<(const int& num) const;
        bool operator>(const int& num) const;
        bool operator<=(const int& num) const;
        bool operator>=(const int& num) const;
        friend bool operator==(const Costumer& a, const int& b);
        friend bool operator==(const int& a, const Costumer& b);

        void print(std::ostream& os) const;

};


#endif //DS_WET_2_COSTUMER_H
