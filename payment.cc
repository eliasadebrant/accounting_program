#include "payment.h"
#include <memory>


Payment::Payment (vector<shared_ptr<Entry>> entries, 
                    int date, 
                    string owner, 
                    string receipt_path, 
                    string description):
    entries {entries},
    date {date},
    owner {owner},
    receipt_path {receipt_path},
    description{description}
{}

bool Payment::is_balanced(){
    double total_sum = 0;
    for (shared_ptr<Entry>& entry : entries){
        total_sum += entry->amount;
    }
    if (total_sum == 0.00){ return true; } else { return false; }
}
int Payment::get_date(){
    return date;
}
vector<shared_ptr<Entry>> Payment::get_entries(){
    return entries;
}
string Payment::get_description(){
    return description;
}
