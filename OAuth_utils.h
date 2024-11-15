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

typedef struct ClientInfo
{
    char permissions[50];
    char access_token[16];
    char refresh[2];
    char refresh_token[16];
    char id[16];
    int valability;
} ClientInfo;

typedef struct Resources
{
    size_t size;
    char **resources;
} Resources;

typedef struct Permissions
{
    size_t size;
    char **permissions;
    size_t current;
} Permissions;

void get_clients(char *path);
void get_resources(char *path);
ClientOrder* get_orders(char *path, int *i);
void read_permissions(char *path);
ClientInfo *init_client_info();

extern ClientsDB *clients;
extern Resources *resources;
extern Permissions *permissions;
extern int valability;
extern ClientInfo *cl_info;
extern int size_cl_info;