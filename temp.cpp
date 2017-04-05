//header files
#include<iostream>
#include<cctype>
#include<vector>
#include<string>
#include<algorithm>
#define NO_OF_CHEF 5
using namespace std;


//Linked list to store the orders corresponding time
struct node{
  string order_name;
  int time_in_min;
  struct node* next;
};
typedef struct node NODE;
NODE *order_start=NULL;

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
     friend void insert_order(string ordername);
};


class CHEF:public CUSTOMER{
     public:
     vector <int> job;
};


void insert_order(string ordername){
  NODE* neworder;
  neworder=(NODE *)malloc(sizeof(NODE));
  neworder->order_name=ordername;
  neworder->time_in_min=menu_time(ordername);
  neworder->next=order_start;
  order_start=neworder;
}



int CUSTOMER::count; //static count


//functions prototypes
int menu_cost(string);
int menu_time(string);
int max_of_vector(vector<int>);



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
    vector<CUSTOMER> c;
    c.resize(no_of_customers); //resolves the variable length array problem

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
        //1. count
        (c[i]).order_count = o_count;
        //2. fill food,time,cost vector
        for(j=0; j<o_count; j++){
            (c[i]).food.push_back(order_array[j]);
            (c[i]).time.push_back(menu_time(order_array[j]));
            (c[i]).cost.push_back(menu_cost(order_array[j]));
            (c[i]).insert_order(order_array[j]);
        }
    }

    //create instance of chefs
    vector <CHEF> chef;
    chef.resize(NO_OF_CHEF);

    //ALGORITHM - assignment of jobs
    //1.fetch max of customer1's order and store it in 'c_max' and 'spare'
        //assign it to chef 1
    //2.get the next max of customer1's order
        //assign it to chef 2
        //spare <- spare - next_max
        //repeat till spare>0
    //3.repeat for all customers
    int c_max;
    int spare = 0;
    vector<int>time_array;
    for(i=0; i<no_of_customers; i++){
        time_array = c[i].time; //as we need to mutate time_array
        for(j=0; j<NO_OF_CHEF; j++){
            c_max = max_of_vector(time_array);
            spare = c_max;
            do {
                chef[j].job.push_back(c_max);
                //remove the time used from time_array
                for(int k=0; ; k++){
                    if (c_max == time_array[k]){
                        time_array[k] = 0; //since we can't delete this array location
                        break;
                    }
                }
                c_max = max_of_vector(time_array); //new c_max
                cout<<c_max<<"\t";break; //test
                spare -= c_max;
            }while(spare>0);
        }
        cout<<endl;
    }


    //testing the order's list of customers by printing

    for(i=0; i<no_of_customers; i++){
        cout<<"Customer ["<<i<<"] :\n";
        cout<<"Name \t\tTime \tCost\n";
        for(j=0; j<c[i].order_count; j++){
            cout<<c[i].food[j]<<"\t\t"<<c[i].time[j]<<"\t"<<c[i].cost[j]<<endl;
        }
        cout<<endl;
    }

    //testing the job list of chef by printing
    for(i=0; i<NO_OF_CHEF; i++){
        cout<<"CHEF ["<<i<<"] :  ";
        //cout<<"Name \t\tTime \tCost\n";
        for(j=0; j<chef[i].job.size(); j++){
            cout<<chef[i].job[j]<<" -> ";
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
     if (sample == "friedrice") return 25;
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
     if (sample == "friedrice") return 30;
     //more to be added
}

int max_of_vector(vector<int> V){
    int i;
    int max_ = V[0];
    for(i=1; i<V.size(); i++){
        if ( V[i] > max_ ) max_ = V[i];
    }
    return max_;
}
