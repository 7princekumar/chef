cout<<"CUSTOMER: ["<<i<<"] ::\n";
cout<<"Enter the names of the food items and enter 'DONE' if no more\n";
while(1){
    cin>>item;
    if(item == "done") break;
    o_count++;
}


void insert order(char *ordername){
  NODE* neworder;
  neworder=(NODE *)malloc(sizeof(NODE));
  neworder->order_name=ordername;
  neworder->time_in_min=menu_time(ordername);
  neworder->next=start;
  start=neworder;
}
