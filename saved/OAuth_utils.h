#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ClientsDB 
{
    size_t size;
    char** clients;
} ClientsDB;

typedef struct ClientOrder
{
    char id[16];
    char action[20];
    char details[20];
} ClientOrder;

void get_clients(char* path);
ClientOrder* get_orders(char* path, int *i);

extern ClientsDB* clients;