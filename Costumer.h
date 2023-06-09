#ifndef DS_WET_2_COSTUMER_H
#define DS_WET_2_COSTUMER_H

#include "utilesWet2.h"

class Costumer
{
    private:
        int m_id;
        int m_phoneNumber;
        double m_expenses;
        bool m_isMember;

    public:
        Costumer(int id, int phoneNumber);
        Costumer(const Costumer& other) = delete;//no need for a copy c'tor;
        ~Costumer() = default;


        /*** Getters ***/
        int getId() const;
        int getPhoneNumber() const;
        double getExpenses() const;
        bool getIsMember() const;

        /*** Methods ***/
        void buyRecord(double price);
        StatusType_t setMember();

        /*** Operators ***/
        friend bool operator==(const Costumer& a, const Costumer& b);
        bool operator<(const Costumer& other) const;
        bool operator>(const Costumer& other) const;

};


#endif //DS_WET_2_COSTUMER_H
