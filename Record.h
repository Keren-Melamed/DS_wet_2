#ifndef RECORD_H_
#define RECORD_H_

#include <iostream>
#include "exception.h"

class Record{
private:
    int m_id;
    int m_number_of_buys;
    int m_copies;
    int m_height;

public:

    Record();
    Record(int id, int number_of_buys, int copies);

    Record(const Record& other) = default;
    Record& operator=(const Record& other) = default;
    ~Record() = default;

    void print(std::ostream& os);

    int getId() const;

    int getNumOfCopies() const;

    int getNumberOfBuys() const;

    int getHeight() const;

    int getPrice() const;

    void setNumberOfCopies(int copies);


    void setNumberOfBuys(int number_of_buys);

    void UpdateHeight(int height);
    void updateNumberOfBuys();
    

    void updateNumberOfBuys();
    
    void setNumberOfBuys(int number_of_buys);

    void UpdateHeight(int height);
};
#endif
