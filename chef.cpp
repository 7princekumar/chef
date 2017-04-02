//header files
#include<iostream>
#include<cctype>
#include<string>
#include<algorithm>
using namespace std;

//classes
class ORDER{
    public:
    int order_count;
    string food[];
    int cost[];
    int time[];
};


class CUSTOMER:public ORDER{
     int static count;
     int c_num; //customer_number
     public:
     CUSTOMER(){
         c_num = count++;
         order_count = 0;
     }
     CUSTOMER(int/*count of orders*/,char*/*array of orders*/);
};

int CUSTOMER::count; //static count

//class constructors definations
CUSTOMER::CUSTOMER(int o_count, char* order_array){
    c_num = count++;
    order_count = o_count;
    for(int i = 0; i<order_count; i++){
        food[i] = order_array[i];
    }
    
}

//class functions
//normal functions


//main
int main(){
    int i,j;
    string item = "";
    int o_count; //order count
    string order_array[];
    
    //get the no of customers, say 'n'
    int no_of_customers;
    cout<<"Number of customers: ";
    cin>>no_of_customers;
    
    //create 'n' number of customer objects and initialise em
    for(int i=0; i<no_of_customers; i++){
        CUSTOMER c[i];
    }
    
    for(int i=0; i<no_of_customers; i++){
        cout<<"Enter the names of the food items and enter 'DONE' if no more\n";
        o_count = 0;
        j = 0;
        while(item != "done"){
            cin>>item;
            o_count++;
            order_array[j] = item;
            j++;
        }
        CUSTOMER (c[i])(o_count,order_array);//calling the constructor
    }
    
    /*//get the food items for each customer and add it to their order_array
    for(int j=0; i<no_of_customers; j++){
        cout<<"Enter the names of the food items and enter 'DONE' if no more\n";
        o_count = 0;
        while(tolower(food) != 'done'){
            cin<<food;
            o_count++;
            order_array[i] = tolower(food);
        }
        c[j].order_count = o_count; 
        c[j].food[]
    }
    */
    
    
    //testing the order's list of customers by printing
    for(i=0; i<no_of_customers; i++){
        cout<<"Customer ["<<i<<"] :\n";
        for(j=0; i<c[i].order_count; j++){
            cout<<c[i].food[j]<<endl;
        }
        cout<<endl;
    }
    return 0;
}