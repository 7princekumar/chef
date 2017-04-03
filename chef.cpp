//header files
#include<iostream>
#include<cctype>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//classes
class ORDER{
    public:
    int order_count;
    vector <string> food;
    vector <int> cost;
    vector <int> time;
};


class CUSTOMER:public ORDER{
     int static count;
     int c_num; //customer_number
     public:
     int order_count;
     CUSTOMER(){
         c_num = count++;
         order_count = 0;
     }
};



int CUSTOMER::count; //static count


//functions prototypes
int menu_cost(string);
int menu_time(string);



//main
int main(){
    int i,j;
    string item = "";
    int o_count; //order count
    vector<string> order_array;
    
    //get the no of customers, say 'n'
    int no_of_customers;
    cout<<"Number of customers: ";
    cin>>no_of_customers;
    
    //create 'n' number of customer objects and initialise em
    //CUSTOMER c[no_of_customers];
    vector<CUSTOMER> c;
    c.resize(no_of_customers);
    
    for(int i=0; i<no_of_customers; i++){
        //reset item and order_array as we need to reuse it
        item = "";
        order_array.clear();
        o_count = 0;
        
        cout<<"CUSTOMER: ["<<i<<"] ::\n";
        cout<<"Enter the names of the food items and enter 'DONE' if no more\n";
        while(1){
            cin>>item;
            if(item == "done") break;
            o_count++;
            order_array.push_back(item);
        }
        
        //put the values inside each customer data
        (c[i]).order_count = o_count;
        for(j=0; j<o_count; j++){
            (c[i]).food.push_back(order_array[j]);
        }
    }
    
    
    
    //testing the order's list of customers by printing
    for(i=0; i<no_of_customers; i++){
        cout<<"Customer ["<<i<<"] :\n";
        for(j=0; j<c[i].order_count; j++){
            cout<<c[i].food[j]<<endl;
        }
        cout<<endl;
    }
    return 0;
}






//normal functions
int menu_time(string sample){
    //input: one order name as string
    //output: time taken to complete that order as integer(mins)
     if (sample == "idli")   return 10;
     if (sample == "dosa")   return 30;
     if (sample == "tea")    return 5;
     if (sample == "samosa") return 7;
     if (sample == "coffee") return 5;
     if (sample == "noodle") return 20;
     if (sample == "fried rice") return 25;
     //more to be added
}

int menu_cost(string sample){
    //input: one order name as string
    //output: cost of that order as integer
     if (sample == "idli")   return 7;
     if (sample == "dosa")   return 30;
     if (sample == "tea")    return 8;
     if (sample == "samosa") return 12;
     if (sample == "coffee") return 8;
     if (sample == "noodle") return 60;
     if (sample == "fried rice") return 30;
     //more to be added
}