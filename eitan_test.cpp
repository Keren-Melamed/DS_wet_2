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
    int* stocks = new int[14]{3, 12, 4, 2, 4, 11, 8, 18, 10, 2, 11, 15, 6, 8};

    new_month_aux(obj, 14, stocks);
    add_costumer_aux(obj, 242, 94);
    add_costumer_aux(obj, 105, 2);
    add_costumer_aux(obj, 212, 155);
    get_place_aux(obj, 12);
    is_member_aux(obj, 212);
    get_place_aux(obj, -1);
    is_member_aux(obj, 212);
    put_on_top_aux(obj, 5, 2);
    put_on_top_aux(obj, 6, 3);
    make_member_aux(obj, 242);
    get_expenses_aux(obj, 242);
    get_place_aux(obj, 14);
    get_expenses_aux(obj, 242);
    put_on_top_aux(obj, 1, 14);
    put_on_top_aux(obj, 2, 9);
    add_prize_aux(obj, -19, 19, 72);
    is_member_aux(obj, 105);
    get_phone_aux(obj, 212);
    add_prize_aux(obj, 13, 180, 44);
    get_phone_aux(obj, -73);
    get_phone_aux(obj, 105);
    put_on_top_aux(obj, 4, 0);
    add_prize_aux(obj, 188, 157, 9);
    buy_record_aux(obj, 242, 7);
    add_costumer_aux(obj, 179, 175);
    put_on_top_aux(obj, 4, 2);
    get_expenses_aux(obj, 242);
    make_member_aux(obj, 105);
    get_place_aux(obj, 15);
    add_prize_aux(obj, 145, 260, 3);
    is_member_aux(obj, 105);
    is_member_aux(obj, 242);
    put_on_top_aux(obj, 12, 4);
    add_costumer_aux(obj, 182, 67);
    buy_record_aux(obj, 105, 12);
    is_member_aux(obj, 105);
    put_on_top_aux(obj, 10, 2);
    is_member_aux(obj, -85);
    add_prize_aux(obj, 184, 281, 45);
    make_member_aux(obj, -100);
    is_member_aux(obj, 212);
    put_on_top_aux(obj, 4, 8);
    get_expenses_aux(obj, 182);
    add_costumer_aux(obj, 242, 216);
    get_expenses_aux(obj, 249);
    get_place_aux(obj, 2);
    get_place_aux(obj, -1);
    put_on_top_aux(obj, -1, -1);
    add_prize_aux(obj, 128, 341, 97);
    get_expenses_aux(obj, 242);
    put_on_top_aux(obj, 6, 12);
    put_on_top_aux(obj, 13, -1);
    get_place_aux(obj, 18);
    get_expenses_aux(obj, 242);
    put_on_top_aux(obj, 7, 10);
    make_member_aux(obj, 179);
    get_expenses_aux(obj, -17);
    put_on_top_aux(obj, 9, 14);
    get_expenses_aux(obj, 242);
    add_costumer_aux(obj, 96, 106);
    get_expenses_aux(obj, 96);
    is_member_aux(obj, 179);
    buy_record_aux(obj, 182, 11);
    is_member_aux(obj, 211);
    add_prize_aux(obj, 187, 29, 90);
    add_costumer_aux(obj, 115, 7);
    get_place_aux(obj, 10);
    get_expenses_aux(obj, 212);
    buy_record_aux(obj, 179, 11);
    make_member_aux(obj, 212);
    is_member_aux(obj, -100);
    is_member_aux(obj, 105);
    make_member_aux(obj, 212);
    get_expenses_aux(obj, 96);
    add_costumer_aux(obj, 33, 243);
    put_on_top_aux(obj, 14, 9);
    add_prize_aux(obj, 234, 91, 64);
    make_member_aux(obj, 119);
    get_phone_aux(obj, 105);
    add_costumer_aux(obj, 68, 157);
    buy_record_aux(obj, 182, 13);
    put_on_top_aux(obj, 12, 5);
    get_expenses_aux(obj, 105);
    add_costumer_aux(obj, 0, 137);
    get_expenses_aux(obj, 212);
    add_costumer_aux(obj, 147, 249);
    add_costumer_aux(obj, 193, 142);
    buy_record_aux(obj, 105, 5);
    make_member_aux(obj, 179);
    put_on_top_aux(obj, 0, 9);
    get_phone_aux(obj, 179);
    get_expenses_aux(obj, 105);
    get_expenses_aux(obj, 0);
    get_phone_aux(obj, 193);
    make_member_aux(obj, -48);
    get_expenses_aux(obj, 17);
    get_expenses_aux(obj, 179);
    make_member_aux(obj, 136);
    get_expenses_aux(obj, 182);
    make_member_aux(obj, 115);
    put_on_top_aux(obj, 9, 3);
    add_costumer_aux(obj, 241, 214);



    delete obj;

}


int main() {

    test();
    return 0;
}
