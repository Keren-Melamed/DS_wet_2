#include "Costumer.h"


Costumer::Costumer(int id, int phoneNumber):
m_id(id), m_phoneNumber(phoneNumber), m_expenses(0), m_isMember(false)
{}

int Costumer::getId() const
{
    return m_id;
}

int Costumer::getPhoneNumber() const
{
    return m_phoneNumber;
}

double Costumer::getExpenses() const
{
    return m_expenses;
}

void Costumer::updateExpenses(double expense)
{
    if(m_isMember == true)
    {
        m_expenses += expense;
    }
}

bool Costumer::getIsMember() const
{
    return m_isMember;
}

void Costumer::buyRecord(double price)
{
    updateExpenses(price);
}

void Costumer::setMember(bool isMember)
{
    m_isMember = isMember;
}

bool operator==(const Costumer &a, const Costumer &b)
{
    if(a.getId() == b.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Costumer::operator<(const Costumer &other) const
{
    if(m_id < other.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Costumer::operator>(const Costumer &other) const
{
    if(m_id > other.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Costumer::operator<(const int& num) const
{
    if(m_id < num)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Costumer::operator>(const int& num) const
{
    if(m_id > num)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Costumer::operator<=(const int &num) const
{
    if(m_id < num || m_id == num)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Costumer::operator>=(const int &num) const
{
    if(m_id > num || m_id == num)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(const Costumer &a, const int &b)
{
    if(a.getId() == b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(const int &a, const Costumer &b)
{
    if(a == b.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Costumer::print(std::ostream &os) const
{
    os << m_id << " ";
}






