#include "OAuth_utils.h"

ClientsDB *clients;
Resources *resources;
Permissions *permissions;
ClientInfo *cl_info;
int size_cl_info;
int valability;

ClientInfo *init_client_info() {
  ClientInfo *c = calloc(50, sizeof(ClientInfo));
  return c;
}

void get_clients(char* path) {
  clients = calloc(1, sizeof(ClientsDB));
  FILE* fptr;
  size_t client_size = 16;
  // Open a file in read mode
  fptr = fopen(path, "r");

  char* string_size = calloc(3, sizeof(char));
  fgets(string_size, 3, fptr);

  clients->size = atoi(string_size);

  clients->clients = calloc(clients->size, sizeof(char*));

  for (int i = 0; i < clients->size; i++) {
    if (feof(fptr)) {
        break;
    }
    clients->clients[i] = calloc(client_size, sizeof(char));
    getline(&(clients->clients[i]), &client_size, fptr);
    if (clients->clients[i][strlen(clients->clients[i]) - 1] == '\n') {
      clients->clients[i][strlen(clients->clients[i]) - 1] = '\0';
    }
  }

  fclose(fptr);
}

ClientOrder* get_orders(char* path, int* i) {
  FILE* fptr;
  size_t line_size = 100;
  // Open a file in read mode
  fptr = fopen(path, "r");
  ClientOrder* orders = calloc(100, sizeof(ClientOrder));
  char* line = NULL;
  while (getline(&line, &line_size, fptr) != -1) {
    char* token;
    token = strtok(line, ",");
    int count = 0;
    while (token != NULL) {
      switch (count) {
        case 0:
          /* code */
          strcpy(orders[*i].id, token);
          break;
        case 1:
          strcpy(orders[*i].action, token);
          break;
        case 2:
          strcpy(orders[*i].details, token);
          if (orders[*i].details[strlen(orders[*i].details) - 1] == '\n') {
            orders[*i].details[strlen(orders[*i].details) - 1] = '\0';
          }
          break;
        default:
          break;
      }
      count++;
      token = strtok(NULL, ",");
    }
    (*i)++;
  }

  fclose(fptr);
  return orders;
}

void get_resources(char* path) {
  
  resources = calloc(1, sizeof(Resources));
  FILE* fptr;
  // Open a file in read mode
  fptr = fopen(path, "r");

    char* resources_size = calloc(3, sizeof(char));
    fgets(resources_size, 3, fptr);

    resources->size = atoi(resources_size);

    resources->resources = calloc(resources->size, sizeof(char*));
    size_t resource_size = 20;
    for (int i = 0; i < resources->size; i++) {
        getline(&(resources->resources[i]), &resource_size, fptr);

        if (resources->resources[i][strlen(resources->resources[i]) - 1] == '\n') {
            resources->resources[i][strlen(resources->resources[i]) - 1] = '\0';
        }
    }

    fclose(fptr); 
}

void read_permissions(char *path) {
  permissions = calloc(1, sizeof(Permissions));
  permissions->current = 0;
  FILE* fptr;
  // Open a file in read mode
  fptr = fopen(path, "r");
    permissions->permissions = calloc(100, sizeof(char*));

    size_t permission_size = 50;
    int i;
    for (i = 0; i < 100; i++) {
        if (feof(fptr)) {
            break;
        }
        getline(&(permissions->permissions[i]), &permission_size, fptr);

        if (permissions->permissions[i][strlen(permissions->permissions[i]) - 1] == '\n') {
            permissions->permissions[i][strlen(permissions->permissions[i]) - 1] = '\0';
        }
    }
    permissions->size = i;
    fclose(fptr);
}