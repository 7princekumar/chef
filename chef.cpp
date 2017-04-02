//header files
#include<iostream>
#include<ctype>
#include<algorithm>

//classes
class ORDER{
    public:
    int order_count;
    char* food[order_count];
    int cost[order_count];
    int time[order_count];
};


class CUSTOMER:public ORDER{
     int static count;
     int c_num; //customer_number
     ORDER order;
     public:
     CUSTOMER(){
         c_num = count++;
     }
     CUSTOMER(int/*count of orders*/,char*[]/*array of orders*/);
};


//class constructors definations
CUSTOMER::CUSTOMER(int order_count, char* order_array[order_count]){
    c_num = count++;
    
}

//class functions
//normal functions


//main
int main(){
    int i;
    char* food;
    int order_count;
    char* order_array[];
    
    //get the no of customers, say 'n'
    int no_of_customers;
    cout<<"Number of customers: ";
    cin>>no_of_customers;
    
    //create 'n' number of customer objects
    for(int i=0; i<no_of_customers; i++){
        CUSTOMERS c[i];
    }
    
    //get the food items for each customer and add it to their order_array
    for(int j=0; i<no_of_customers; j++){
        cout<<"Enter the names of the food items and enter 'DONE' if no more\n";
        i = 0;
        while(tolower(food) != 'done'){
            c[j]order_array[i] = tolower(food);
            i++;
        }
    }
    
}