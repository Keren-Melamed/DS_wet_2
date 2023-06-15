#include <iostream>
#include "recordsCompany.h"
#include "utilesWet2.h"
using namespace std;

void status_aux(StatusType status) {
    switch (status)
    {
        case StatusType::SUCCESS:
            cout<<"SUCCESS"<<endl;
            break;
        case StatusType::FAILURE:
            cout<<"FAILURE"<<endl;
            break;
        case StatusType::ALLOCATION_ERROR:
            cout<<"ALLOCATION_ERROR"<<endl;
            break;
        case StatusType::INVALID_INPUT:
            cout<<"INVALID_INPUT"<<endl;
            break;
        case StatusType::ALREADY_EXISTS:
            cout<<"ALREADY_EXISTS" << endl;
    
        case StatusType::DOESNT_EXISTS:
            cout << "DOESNT_EXIST" << endl;

        }

}

void new_month_aux(RecordsCompany *obj, int number_of_records, int *records_stocks) {
    std::cout << "create new month "<< endl;
    status_aux(obj->newMonth(records_stocks, number_of_records));
}

void add_costumer_aux(RecordsCompany *obj, int c_id, int phone) {
    std::cout<<"add costumer "<< c_id << endl;
    status_aux(obj->addCostumer(c_id, phone));
}

void get_phone_aux(RecordsCompany *obj, int c_id) {
    std::cout<<"get phone number of client  "<< c_id << endl;
    Output_t<int> phone = obj->getPhone(c_id);
    status_aux(phone.status());
    std::cout << phone.ans() << std::endl;   
}

void make_member_aux(RecordsCompany *obj, int c_id) {
    std::cout <<"make member out of costumer "<< c_id <<" " << endl;
    status_aux(obj->makeMember(c_id));
}

void is_member_aux(RecordsCompany *obj, int c_id) {
    std::cout<<"is  "<< c_id <<" a member " << endl;
    Output_t<bool> res = obj->isMember(c_id);
    if(res.ans() == true){
        std::cout << "true" << std::endl;  
    }
     if(res.ans() == false){
        std::cout << "false" << std::endl;  
    }
    else{
        status_aux(res.status());
    }
}

void buy_record_aux(RecordsCompany *obj, int c_id, int r_id)
{
    std::cout << "costumer " << c_id << " buying record " << r_id << endl;
    status_aux(obj->buyRecord(c_id, r_id));
}

void add_prize_aux(RecordsCompany *obj, int c_id1, int c_id2, double amount)
{
    std::cout << "adding prize of " << amount << " to clients  " << c_id1 << " till " << c_id2 << endl;;
    status_aux(obj->addPrize(c_id1, c_id2, amount));
}

void get_expenses_aux(RecordsCompany *obj, int c_id) {
    std::cout << "get expenses of member  "<< c_id << endl;
    Output_t<double> res = obj->getExpenses(c_id);
    if(res.ans() == 0){
        status_aux(res.status());
    }
    else{
        std::cout << res.ans() << std::endl;
    }
}

void put_on_top_aux(RecordsCompany *obj, int r_id1, int r_id2)
{
    std::cout << "putting record " << r_id1 << " on top of  " << r_id2 << endl;
    status_aux(obj->putOnTop(r_id1, r_id2));
}

void get_place_aux(RecordsCompany *obj, int r_id){
    std::cout << " getting place of record  "<< r_id << endl;
    int temp = 0;
    int* column = &temp;
    int* height = &temp;
    status_aux(obj->getPlace(r_id, column, height));
    if((column != nullptr) && (height != nullptr)){
        std::cout << "column: " << *column << " height: " << *height << endl;
    }
}

void test() {
    RecordsCompany *obj = new RecordsCompany();
    int* stock = new int[18]{18, 18, 13, 17, 18, 4, 18, 9, 11, 16, 8, 13, 8, 10, 20, 13, 4, 5};
    

    new_month_aux(obj, 18, stock);
    obj->getAllRecords(cout);

    add_costumer_aux(obj, 206, 246);


    add_costumer_aux(obj, 184, -4);


    add_costumer_aux(obj, 245, 175);


    buy_record_aux(obj, 206, 10);


    get_expenses_aux(obj, 245);


    put_on_top_aux(obj, -1, 15);
    add_prize_aux(obj, 7, 2, 72);
    add_costumer_aux(obj, 1000000, 214);
    add_costumer_aux(obj, 127, 42);

    obj->m_UFrecords.printParents(cout, 12);
    get_place_aux(obj, 12);



    delete obj;

}


int main() {

    test();
    return 0;
}
