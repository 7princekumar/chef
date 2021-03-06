/*//////////////////////////PROGRAM DETAILS///////////////////////
                     OOP OPEN ENDED PROJECT, 2017
              SIDDAGANGA INSTITUTE OF TECHNOLOGY, TUMKUR
                
          NAME OF THE PROJECT :::: Job/Time management of Chefs.
                
                      PROJECT SUBMITTED BY: 
                  1. Prince Kumar - 1SI15CS080
                  2. Puru Jaiswal - 1SI15CS081
                
             PROJECT SUBMITTED TO ::: Prof. H.D. Kallinatha
///////////////////////////HEADER FILES//////////////////////////*/
#include<iostream>
#include<cctype>
#include<vector>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#define NO_OF_CHEF 5
using namespace std;



///////////////////////////////NODE////////////////////////////////
struct node{
    string food;
    int cost;
    int time;
    int customer_num;
};
typedef struct node NODE;



/////////////////////////////classes///////////////////////////////
class ORDER{
    public:
    vector<NODE>order_node;
};

class CUSTOMER:public ORDER{
     int static count;
     int c_num; //customer_number
     int total_cost;
     public:
     int min_time;
     int order_count;
     static int get_customer_num(){
       return count;
     }
     CUSTOMER(){
         c_num = count++;
     }
     int return_total_cost(){
         total_cost = 0;
         for(int i =0; i<order_node.size(); i++)
            total_cost += order_node[i].cost;
         return total_cost;
     }
};

class CHEF:public CUSTOMER{
     public:
     vector<NODE>job;
     int work_time;
};



//////////////////////functions prototypes/////////////////////////
string string_to_upper(string&);
string string_to_lower(string&);
string string_1_upper(string&);
int menu_cost(string);
int menu_time(string);
void show_menu();
bool compare(NODE,NODE);
CHEF& chef_with_min_work_time(vector<CHEF>& , NODE); 
CHEF& chef_with_min_work_time(vector<CHEF>&, int, NODE);

int CUSTOMER::count; //static count



/////////////////////////////main/////////////////////////////////
int main(){
    int i,j;
    string name;
    NODE item;
    vector<NODE> order_array;

    //get the no of customers, say 'n'
    int no_of_customers;
    cout<<"Number of customers: ";
    cin>>no_of_customers;
    
    //create 'n' number of customer objects
    vector<CUSTOMER> c;
    c.resize(no_of_customers);

    ///////////INPUT - get orders from all customers /////////////////
    show_menu();
    cout<<"\n\nENTER THE NAMES OF THE FOOD ITEMS AND ENTER 'done' IF NO MORE\n";
    for(i=0; i<no_of_customers; i++){
        //reset item and order_array as we need to reuse it
        name = "";
        order_array.clear();
        
        cout<<"\n           CUSTOMER : ["<<i<<"]\n";
        while(1){
            cout<<"           : ";
            cin>>name;
            name = string_to_lower(name);
            if(name == "done") break;
            item.food = name;
            item.cost = menu_cost(name);
            item.time = menu_time(name);
            item.customer_num = i;
            order_array.push_back(item);
        }
        //put the values inside each customer data
        c[i].order_node = order_array;
    }


    //create instance of chefs
    vector<CHEF> chef;
    chef.resize(NO_OF_CHEF); 
    for(i=0; i<NO_OF_CHEF; i++)
        chef[i].work_time = 0;
    

/////////////...........PROCESSING - ALGORITHM............///////////////
    //1. SORT THE NODE ARRAY in decreasing order
    for(i = 0; i<no_of_customers; i++){
        sort(c[i].order_node.begin(), c[i].order_node.end(), compare);
        // for(j=0; j<c[i].order_node.size(); j++)
        //     cout<<c[i].order_node[j].time <<" -> ";
        // cout<<endl;
    }

    //2. Push it to chef accordingly
    int spare_max = 0;
    for(i=0; i<no_of_customers; i++){
         order_array = c[i].order_node; 
         //order_array is sorted list of orders of customer[i]
         //iterate over this array & assign its order to chefs accordingly
         for(j=0; j<order_array.size(); j++){ 
             spare_max = order_array[0].time; //since sorted in decreasing order
             
             //for first order
             chef_with_min_work_time(chef,order_array[j]).job.push_back(order_array[j]);
             j++;
             
             //for other orders
             while(j<= (order_array.size())){
                 if(j+1 > order_array.size()) break;
                 chef_with_min_work_time
                      (chef, spare_max, order_array[j]).job.push_back(order_array[j]);
                 if(j == order_array.size()) break;
                 j++;
             }
         }
    }
    
    
    //find min time for customers' order to finish
    for(i=0; i<no_of_customers; i++){
        int final_max_time = 0;
        for(j=0; j<chef.size(); j++){
            int max_loc  = 0;
            int max_time = 0;
            if(chef[j].job.empty()) break;
            
            for(int k= (int(chef[j].job.size()) - 1); k>= -1; k--){
                if(chef[j].job[k].customer_num == i){
                    max_loc = k; //else 0
                    break;
                }
            }

            if(chef[j].job[max_loc].customer_num == i)
                for(int k =0; k<= max_loc; k++){
                    max_time += chef[j].job[k].time;
                }
            if(max_time > final_max_time)
                final_max_time = max_time;
        }
        c[i].min_time = final_max_time;
    }




///////......... OUTPUT - LISTS OF CUSTOMERS and THEIR ORDERS .........///////// 
    cout<<"======================================================================\n";
    int flag = no_of_customers - 1;
    for(i=0; i<no_of_customers; i++){
        cout<<"\n\t                 CUSTOMER : ["<<i<<"]\n";
        cout<<"\t\t  "<<setw(9)<<"Name "<<setw(8)<<" Time"<<setw(9)<<"Cost\n";
        cout<<"\t\t  "<<setw(9)<<"____ "<<setw(8)<<" ____"<<setw(9)<<"____\n";
        for(j=0; j<c[i].order_node.size(); j++){
            cout<<"\t\t"<<setw(10)<<string_to_upper(c[i].order_node[j].food)<<
            setw(8)<<c[i].order_node[j].time<<setw(8)<<c[i].order_node[j].cost<<endl;
        }
        cout<<endl;
        if(no_of_customers > 1 && i < flag)
            cout<<"\t\t________________________________\n";
    }
    cout<<"______________________________________________________________________\n";
    
    
    
    cout<<"\n\tMinimum time required to complete orders of customers and bill.\n";
    cout<<"\t\t                   Time           Cost\n";
    for(i=0; i<no_of_customers; i++){
        cout<<"\t\tCustomer ["<<i<<"] : "<<setw(4)<<c[i].min_time<<" minutes";
        cout<<"       Rs."<<setw(3)<<c[i].return_total_cost()<<endl;
    }
    cout<<"______________________________________________________________________\n\n";
    



/////....... OUTPUT - LISTS OF CHEF and THEIR WORK DISTRIBUTION ......./////// 
    for(i=0; i<chef.size(); i++){
        cout<<"\n             CHEF["<<i<<"] :  ";
        //cout<<"Name \t\tTime \tCost\n";
        for(j=0; j<chef[i].job.size(); j++){
            cout<<"c"<<chef[i].job[j].customer_num<<"_"<<
            string_1_upper(chef[i].job[j].food)<<
            "("<<chef[i].job[j].time<<")"<<" -> ";
        }
        cout<<endl;
    }
    cout<<"\n\n======================================================================\n";

    return 0;
}






/////////////////////////function definations///////////////////////////

string string_to_upper(string &s){
    for(int i=0;i< s.length();i++)
        s[i]=toupper(s[i]);
    return s;
}

string string_to_lower(string &s){
    for(int i=0;i< s.length();i++)
        s[i]=tolower(s[i]);
    return s;
}

string string_1_upper(string &s){
    for(int i=0; i< 1; i++)
        s[i]=toupper(s[i]);
    return s;
}


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
     return 0;
     //more to be added
}

int menu_cost(string sample){
    //input:  one order name as string
    //output: cost of that order as integer
     if (sample == "idli")   return 7;
     if (sample == "dosa")   return 30;
     if (sample == "tea")    return 8;
     if (sample == "samosa") return 12;
     if (sample == "coffee") return 8;
     if (sample == "noodle") return 60;
     if (sample == "friedrice") return 30;
     return 0;
     //more to be added
}




bool compare(NODE a,NODE b){
    //input:  two order structures of type NODE
    //output: returns boolean, True: if NODE a order time is greater
    //        otherwise false
    return (a.time > b.time);
}



CHEF& chef_with_min_work_time(vector<CHEF> &a, NODE order_to_be_pushed){
    //input:  vector of chefs, struct of an order
    //output: reference to a chef with min work_time
    int min_pos = 0;
    for(int i=0; i<a.size(); i++){
        if(a[i].work_time < a[min_pos].work_time)
            min_pos = i;
    }
    a[min_pos].work_time += order_to_be_pushed.time;
    return a[min_pos];
}
 
 
 
CHEF& chef_with_min_work_time(vector<CHEF> &a, int spare_max, NODE order_to_be_pushed){
    //input:  vector of chefs, maxTimeTaking order, struct of an order
    //output: reference to a chef which satifies certain conditions
     int min_pos = 0;
     for(int i=0; i<a.size(); i++){
         if((a[i].work_time + order_to_be_pushed.time) <= spare_max){
              min_pos = i; 
              break;
         }
     }
     if(min_pos == 0) //i.e, no chef that satisfies this condition, so return chef with min worktime only
         return chef_with_min_work_time(a,order_to_be_pushed);
     else
         a[min_pos].work_time += order_to_be_pushed.time;
    return a[min_pos];
}



void show_menu(){
    cout<<"\n\n";
    cout<<"   ----------------------------------------------\n";
    cout<<"   |     NAME        COST(Rupees)     TIME(min) |\n";
    cout<<"   |--------------------------------------------|\n";
    cout<<"   |     Idli    "<<setw(9)<<menu_cost("idli")     
                          <<setw(18)<<menu_time("idli")     <<setw(6)<<"|\n";
    cout<<"   |     Dosa    "<<setw(9)<<menu_cost("dosa")
                          <<setw(18)<<menu_time("dosa")     <<setw(6)<<"|\n";
    cout<<"   |     Tea     "<<setw(9)<<menu_cost("tea")
                          <<setw(18)<<menu_time("tea")      <<setw(6)<<"|\n";
    cout<<"   |    Samosa   "<<setw(9)<<menu_cost("samosa")
                          <<setw(18)<<menu_time("samosa")   <<setw(6)<<"|\n";
    cout<<"   |    Coffee   "<<setw(9)<<menu_cost("coffee")
                          <<setw(18)<<menu_time("coffee")   <<setw(6)<<"|\n";
    cout<<"   |    Noodle   "<<setw(9)<<menu_cost("noodle")
                          <<setw(18)<<menu_time("noodle")   <<setw(6)<<"|\n";
    cout<<"   |  Fried Rice "<<setw(9)<<menu_cost("friedrice")
                          <<setw(18)<<menu_time("friedrice")<<setw(6)<<"|\n";
    cout<<"   ----------------------------------------------\n";
    cout<<"\n";
}


