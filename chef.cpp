//header files
#include<iostream>
#include<cctype>
#include<vector>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#define NO_OF_CHEF 5
using namespace std;

struct node{
    string food;
    int cost;
    int time;
};
typedef struct node NODE;


//functions prototypes
int menu_cost(string);
int menu_time(string);
int max_of_vector(vector<NODE>);
bool compare(NODE,NODE);




//classes
class ORDER{
    public:
    vector<NODE>order_node;
};


class CUSTOMER:public ORDER{
     int static count;
     int c_num; //customer_number
     public:
     int order_count;
     static int get_customer_num(){
       return count;
     }
     CUSTOMER(){
         c_num = count++;
     }
};


class CHEF:public CUSTOMER{
     public:
     vector<NODE>job;
     int work_time;
};


CHEF& chef_with_min_work_time(vector<CHEF>& , NODE); //return by reference concept//fucntion prototype
CHEF& chef_with_min_work_time(vector<CHEF>& , int, int, NODE);
int CUSTOMER::count; //static count



//main
int main(){
    int i,j;
    string name;
    NODE item;
    vector<NODE> order_array;

    //get the no of customers, say 'n'
    int no_of_customers;
    cout<<"Number of customers: ";
    cin>>no_of_customers;

    //create 'n' number of customer objects and initialise em
    vector<CUSTOMER> c;
    c.resize(no_of_customers); //resolves the variable length array problem

    for(i=0; i<no_of_customers; i++){
        //reset item and order_array as we need to reuse it
        name = "";
        order_array.clear();

        cout<<"CUSTOMER: ["<<i<<"] ::\n";
        cout<<"Enter the names of the food items and enter 'done' if no more\n";
        while(1){
            cin>>name;
            if(name == "done") break;
            item.food = name;
            item.cost = menu_cost(name);
            item.time = menu_time(name);

            order_array.push_back(item); /////
        }

        //put the values inside each customer data
        c[i].order_node = order_array;
    }


    //create instance of chefs
    vector<CHEF> chef;
    chef.resize(NO_OF_CHEF); ////////FIX IT IN FUTURE, let there be any chef for now
    for(i=0; i<NO_OF_CHEF; i++)
        chef[i].work_time = 0;
    

    //NEW ALGO
    //1. SORT THE NODE ARRAY in decreasing order
    for(i = 0; i<no_of_customers; i++){
        sort(c[i].order_node.begin(), c[i].order_node.end(), compare);  //order_node is now sorted
        for(j=0; j<c[i].order_node.size(); j++)
            cout<<c[i].order_node[j].time <<" -> ";
        cout<<endl;
    }


    //2. Push it to chef accordingly
    // int k = -1; //for chefs
    // int spare = 0;
    // for(i=0; i<no_of_customers; i++){
    //      k++;
    //      order_array = c[i].order_node; //order_array is sorted list of orders of customer[i]
    //      for(j=0; j<order_array.size(); j++){ //iterate over this array and assign its order to chefs accordingly
    //          spare = order_array[0].time; //since sorted in decreasing order

    //          if(chef[k].job.empty()){
    //             //assign the first order of new customer to an empty chef
    //             if(k+1 >= NO_OF_CHEF) break;
    //             if(j+1 >= order_array.size()) break;
    //             chef[k++].job.push_back(order_array[j++]); //k++ since after insertion, go to next chef
    //          }
    //          else{
    //              if(k+1 >= NO_OF_CHEF) break;
    //              if(j+1 >= order_array.size()) break;
    //              chef[++k].job.push_back(order_array[j++]); //++k since go to next insertion and then insert
    //          }

    //          while(spare>0){
    //              spare -= order_array[j].time;
    //              chef[k].job.push_back(order_array[j++]);  //j++ since after insertion, point to next order of customer [i]
    //              if(j+1 > order_array.size()) break;
    //          }
    //      }
    // }


    //VERSION 3 algo
    //2. Push it to chef accordingly
    int k = 0; //for chefs
    int spare = 0;
    int spare_max = 0;
    for(i=0; i<no_of_customers; i++){
         order_array = c[i].order_node; //order_array is sorted list of orders of customer[i]
         for(j=0; j<order_array.size(); j++){ //iterate over this array and assign its order to chefs accordingly
             spare_max = order_array[0].time; //since sorted in decreasing order
             spare = spare_max;
             
             //for first order
             if(j+1 >= order_array.size()) break;
             chef_with_min_work_time(chef,order_array[j]).job.push_back(order_array[j]);
             j++;
             
             //for other orders
             while(spare>0 && j<= (order_array.size()) ){
                 if(j+1 > order_array.size()) break;
                 chef_with_min_work_time(chef, spare, spare_max, order_array[j]).job.push_back(order_array[j]);
                 spare -= order_array[j].time;
                 j++;
             }
        
         }
    }









    //testing the order's list of customers by printing
    for(i=0; i<no_of_customers; i++){
        cout<<"Customer ["<<i<<"] :\n";
        cout<<setw(20)<<"Name "<<setw(20)<<"  Time"<<setw(20)<<"Cost\n";
        for(j=0; j<c[i].order_node.size(); j++){
            cout<<setw(20)<<c[i].order_node[j].food<<setw(20)<<c[i].order_node[j].time<<setw(20)<<c[i].order_node[j].cost<<endl;
        }
        cout<<endl;
    }

    //testing the job list of chef by printing
    for(i=0; i<chef.size(); i++){
        cout<<"CHEF ["<<i<<"] :  ";
        //cout<<"Name \t\tTime \tCost\n";
        for(j=0; j<chef[i].job.size(); j++){
            cout<<chef[i].job[j].time<<" -> ";
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

int max_of_vector(vector<NODE> V){
    int i;
    int max_ = V[0].time;
    for(i=1; i<V.size(); i++){
        if ( V[i].time > max_ ) max_ = V[i].time;
    }
    return max_;
}


bool compare(NODE a,NODE b){
    return (a.time > b.time);
}



CHEF& chef_with_min_work_time(vector<CHEF> &a, NODE order_to_be_pushed){
    int min_pos = 0;
    for(int i=0; i<a.size(); i++){
        if(a[i].work_time < a[min_pos].work_time)
            min_pos = i;
    }
    cout<<"MIN POS : "<<min_pos<<endl;
    a[min_pos].work_time += order_to_be_pushed.time;
    return a[min_pos];
}
 
 
 
CHEF& chef_with_min_work_time(vector<CHEF> &a, int spare, int spare_max, NODE order_to_be_pushed){
     int min_pos = 0;
     for(int i=0; i<a.size(); i++){
         if((a[i].work_time < spare) && ((a[i].work_time + order_to_be_pushed.time) <= spare_max)){
              min_pos = i; 
              break;
         }
     }
     //cout<<"MIN POS 2 : "<<min_pos<<endl; //REMOVE
     if(min_pos == 0) //i.e, no chef that satisfies this condition, so return chef with min worktime only
         chef_with_min_work_time(a,order_to_be_pushed);
     else{
         a[min_pos].work_time += order_to_be_pushed.time;
         return a[min_pos];
    }
}