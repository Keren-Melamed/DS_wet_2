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
    std::cout << "is  "<< c_id <<" a member " << endl;
    Output_t<double> res = obj->getExpenses(c_id);
    if(res.status() != INVALID_INPUT){
        std::cout << res.ans() << std::endl;
    }
    else{
        status_aux(res.status());
    }
}

void put_on_top_aux(RecordsCompany *obj, int r_id1, int r_id2)
{
    std::cout << "putting record " << r_id1 << " on top of  " << r_id2 << endl;
    status_aux(obj->putOnTop(r_id1, r_id2));
}

void get_place_aux(RecordsCompany *obj, int r_id){
    std::cout << " getting place of record  "<< r_id << endl;
    int column = 0;
    int height = 0;
    status_aux(obj->getPlace(r_id, &column, &height));

    std::cout << "column: " << column << " height: " << height << endl;
}

void test() {
    RecordsCompany *obj = new RecordsCompany();
    int* stocks = new int[18]{18, 18, 13, 17, 18, 4, 18, 9, 11, 16, 8, 13, 8, 10, 20, 13, 4, 5};
    new_month_aux(obj, 18, stocks);
    
    
    put_on_top_aux(obj, -1, 15);
    
    get_place_aux(obj, 12);
    
    put_on_top_aux(obj, 3, 11);
    get_place_aux(obj, 3);

/*
    get_expenses_aux(obj, 206);
    is_member_aux(obj, 217);
    is_member_aux(obj, 72);
    get_phone_aux(obj, 206);
    get_phone_aux(obj, 163);
    add_prize_aux(obj, 145, 190, 21);
    add_costumer_aux(obj, 101, 216);
    buy_record_aux(obj, 245, 10);
    get_place_aux(obj, 15);
    add_prize_aux(obj, 231, 82, 73);
    put_on_top_aux(obj, 6, 17);
    buy_record_aux(obj, 245, 0);
    buy_record_aux(obj, 206, 12);
    make_member_aux(obj, 245);
    get_place_aux(obj, 19);
    get_expenses_aux(obj, 72);
    get_phone_aux(obj, 127);
    buy_record_aux(obj, 206, 5);
    buy_record_aux(obj, 72, 12);
    get_place_aux(obj, 13);
    get_phone_aux(obj, 222);
    add_prize_aux(obj, 48, 214, 6);
    make_member_aux(obj, 245);
    get_expenses_aux(obj, 72);
    add_costumer_aux(obj, 160, 206);
    get_expenses_aux(obj, 101);
    get_phone_aux(obj, 127);
    put_on_top_aux(obj, 13, -1);
    get_place_aux(obj, 12);
    buy_record_aux(obj, 101, 15);
    get_place_aux(obj, 7);
    get_expenses_aux(obj, 206);
    make_member_aux(obj, 101);
    buy_record_aux(obj, 163, 10);
    get_place_aux(obj, 7);
    get_place_aux(obj, 11);
    add_prize_aux(obj, 246, 49, 54);
    get_expenses_aux(obj, -21);
    make_member_aux(obj, 72);
    add_prize_aux(obj, 59, 319, 87);
    get_place_aux(obj, -1);
    get_place_aux(obj, -2);
    get_expenses_aux(obj, 72);
    add_prize_aux(obj, 235, 202, 2);
    add_costumer_aux(obj, 168, 227);
    make_member_aux(obj, 101);
    is_member_aux(obj, -5);
    get_phone_aux(obj, 163);
    get_phone_aux(obj, 206);
    buy_record_aux(obj, 168, 2);
    is_member_aux(obj, 245);
    buy_record_aux(obj, 101, 16);
    buy_record_aux(obj, 127, -9);
    is_member_aux(obj, 206);
    add_costumer_aux(obj, 238, 148);
    put_on_top_aux(obj, 5, 10);
    make_member_aux(obj, 238);
    make_member_aux(obj, 168);
    is_member_aux(obj, 72);
    get_place_aux(obj, 22);
    put_on_top_aux(obj, 12, 20);
    get_phone_aux(obj, 72);
    get_phone_aux(obj, 72);
    make_member_aux(obj, 72);
    is_member_aux(obj, 238);
    get_place_aux(obj, 22);
    buy_record_aux(obj, 163, 12);
    add_prize_aux(obj, 55, 108, 95);
    put_on_top_aux(obj, 1, 20);
    make_member_aux(obj, -14);
    make_member_aux(obj, 245);
    make_member_aux(obj, 245);
    buy_record_aux(obj, 168, 2);
    get_phone_aux(obj, 168);
    add_prize_aux(obj, 120, 199, 88);
    is_member_aux(obj, 160);
    get_phone_aux(obj, 127);
    add_prize_aux(obj, 170, 258, 92);
    buy_record_aux(obj, 160, 2);
    add_costumer_aux(obj, 67, 79);
    buy_record_aux(obj, 101, 1);
    add_prize_aux(obj, 0, 35, 82);
    get_expenses_aux(obj, -25);
    get_phone_aux(obj, 160);
    get_expenses_aux(obj, 160);
    add_costumer_aux(obj, 80, 75);
*/


    delete obj;

}


int main() {

    test();
    return 0;
}
