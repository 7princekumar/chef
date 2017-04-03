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

//class constructors definations


//class functions
//normal functions


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
    CUSTOMER c[no_of_customers];
    
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
        //(c[i])(o_count, order_array);//calling the constructor
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