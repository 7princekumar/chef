///////LINKED LIST//////
#include<iostream>

struct node{
    string food;
    int cost;
    int time;
    struct node* link;
};

typedef struct node NODE;

NODE* start = NULL;
void insert_rear();