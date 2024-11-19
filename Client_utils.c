#include "Client_utils.h"

ClientSideInfo *init_clients_info() {
    ClientSideInfo *clients_info = calloc(50, sizeof(ClientSideInfo));

    if (clients_info == NULL) {
        printf("Error while allocating memory for clients' info!\n");
        free(clients_info);
        return NULL;
    }
    return clients_info;
}

ClientOrder* get_orders(char* path, int* i) {
  FILE* fptr;
  size_t line_size = 100;
  // Open a file in read mode
  fptr = fopen(path, "r");
  ClientOrder* orders = calloc(100, sizeof(ClientOrder));
  char* line = NULL;
    // reading the CSV file
  while (getline(&line, &line_size, fptr) != -1) {
    char* token;
    token = strtok(line, ",");
    int count = 0; // counter used to determine where the cursor is (ID,ACTION,DETAILS)
    while (token != NULL) {
      switch (count) {
        case 0:
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

int prepare_request_token_args(authorization *authorization, char *id) {
    authorization->id = calloc(strlen(id), sizeof(char));
    if (authorization->id == NULL) {
        printf("Error while allocating memory for authorization!\n");
        free(authorization->id);
        return 0;
    }

    strcpy(authorization->id, id);

    return 1;
}

int prepare_approve_request_token_args(approve *approve, char *authorization) {
    approve->authorization_token = calloc(strlen(authorization), sizeof(char));
    if (approve->authorization_token == NULL) {
        printf("Error while allocating memory for approval!\n");
        free(approve->authorization_token);
        return 0;
    }

    strcpy(approve->authorization_token, authorization);

    return 1;
}

int prepare_request_access_token_args(access *access, char *authorization, char *permissions, char *id, char *refresh, int verify) {
    access->authorization_token.authorization_token = calloc(16, sizeof(char));
    if (access->authorization_token.authorization_token == NULL) {
        printf("Error while allocating memory for access request!\n");
        free(access->authorization_token.authorization_token);
        return 0;
    }

    access->authorization_token.permissions = calloc(50, sizeof(char));
    if (access->authorization_token.authorization_token == NULL) {
        printf("Error while allocating memory for access request!\n");
        free(access->authorization_token.authorization_token);
        free(access->authorization_token.permissions);
        return 0;
    }

    access->id = calloc(16, sizeof(char));
    if (access->id == NULL) {
        printf("Error while allocating memory for access request!\n");
        free(access->authorization_token.authorization_token);
        free(access->authorization_token.permissions);
        free(access->id);
        return 0;
    }

    access->refresh = calloc(2, sizeof(char));
    if (access->refresh == NULL) {
        printf("Error while allocating memory for access request!\n");
        free(access->authorization_token.authorization_token);
        free(access->authorization_token.permissions);
        free(access->id);
        free(access->refresh);
        return 0;
    }

    strcpy(access->authorization_token.authorization_token, authorization);
    strcpy(access->authorization_token.permissions, permissions);
    strcpy(access->id, id);
    strcpy(access->refresh, refresh);
    access->authorization_token.verify = verify;

    return 1;
}

void print_tokens(char *refresh, char *authorization, access_response tokens) {
    if (atoi(refresh) == 0) {
        printf("%s -> %s\n", authorization, tokens.access_token);	
    } else if (atoi(refresh) == 1) {
        printf("%s -> %s,%s\n", authorization, tokens.access_token, tokens.refresh_token);
    }
}

void add_or_modify_client(ClientSideInfo *clients_info, int *current_clients_info, char *id, char *refresh, access_response tokens) {
    int already_exists = 0;

    // modify the client that requests again
    for (int i = 0; i < *current_clients_info; i++) {
        if (!strcmp(id, clients_info[i].id)) {
            already_exists = 1;
            strcpy(clients_info[i].access_token, tokens.access_token);
            strcpy(clients_info[i].refresh_token, tokens.refresh_token);
            clients_info[i].refresh = atoi(refresh);
            clients_info[i].valability = tokens.valability;
        }
    }

    if (!already_exists) {
        // adding a new client
        strcpy(clients_info[*current_clients_info].id, id);
        strcpy(clients_info[*current_clients_info].access_token, tokens.access_token);

        if (!atoi(refresh)) {
            memset(clients_info[*current_clients_info].refresh_token, 0, strlen(clients_info[*current_clients_info].refresh_token));
            strcpy(clients_info[*current_clients_info].refresh_token, "");    
        } else {
            strcpy(clients_info[*current_clients_info].refresh_token, tokens.refresh_token);
        }
        clients_info[*current_clients_info].refresh = atoi(refresh);
        clients_info[(*current_clients_info)++].valability = tokens.valability;
    }
}

int prepare_validate_delegated_action(action *action, char *access_token, char *op, char *source) {
    action->access_token = calloc(16, sizeof(char));
    if (action->access_token == NULL) {
        printf("Error while allocating memory for the validation!\n");
        free(action->access_token);
        return 0;
    }

	action->operation = calloc(10, sizeof(char));
    if (action->operation == NULL) {
        printf("Error while allocating memory for the validation!\n");
        free(action->access_token);
        free(action->operation);
        return 0;
    }

	action->source = calloc(15, sizeof(char));
    if (action->source == NULL) {
        printf("Error while allocating memory for the validation!\n");
        free(action->access_token);
        free(action->operation);
        free(action->source);
        return 0;
    }

    strcpy(action->access_token, access_token);
	strcpy(action->operation, op);
	strcpy(action->source, source);

    return 1;
}

int prepare_get_new_token(refresh_input *input, char *id, char *refresh_token) {
    input->id = calloc(16, sizeof(char));
    if (input->id == NULL) {
        printf("Error while allocating memory for the refresh input!\n");
        free(input->id);
        return 0;
    }

	input->refresh = calloc(16, sizeof(char));
    if (input->refresh == NULL) {
        printf("Error while allocating mmemory for the refresh input!\n");
        free(input->id);
        free(input->refresh);
        return 0;
    }

    strcpy(input->id, id);
	strcpy(input->refresh, refresh_token);

    return 1;
}

void modify_access_token(ClientSideInfo *clients_info, int current_clients_info, char *id, refresh_output tokens) {
    for (int i = 0; i < current_clients_info; i++) {
		if (!strcmp(id, clients_info[i].id)) {
			strcpy(clients_info[i].access_token, tokens.access_token);
			strcpy(clients_info[i].refresh_token, tokens.refresh_token);
			clients_info[i].valability = tokens.valability;
		}
	}
}
