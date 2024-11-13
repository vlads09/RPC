#include "OAuth_utils.h"

ClientsDB* clients;

void get_clients(char* path) {

    clients = calloc(1, sizeof(ClientsDB));
    FILE *fptr;
    size_t client_size = 16;
    // Open a file in read mode
    fptr = fopen(path, "r");

    char* string_size = calloc(3, sizeof(char)); 
    fgets(string_size, 3, fptr);

    clients->size = atoi(string_size);

    clients->clients = calloc(clients->size, sizeof(char*));

    for (int i = 0; i < clients->size; i++) {
        clients->clients[i] = calloc(client_size, sizeof(char));
        getline(&(clients->clients[i]), &client_size, fptr);
        if (clients->clients[i][strlen(clients->clients[i]) - 1] == '\n') {
            clients->clients[i][strlen(clients->clients[i]) - 1] = '\0';    
        }
    }

    fclose(fptr);
}

ClientOrder* get_orders(char* path, int* i) {
    FILE *fptr;
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
            switch (count)
            {
            case 0:
                /* code */
                strcpy(orders[*i].id, token);
                break;
            case 1:
                strcpy(orders[*i].action, token);
                break;
            case 2:
                strcpy(orders[*i].details, token);
                if (orders[*i].details[strlen(orders[*i].details) - 1] == '\n'){
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
