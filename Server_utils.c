#include "Server_utils.h"

ClientsDB *clients;
Resources *resources;
Permissions *permissions;
ClientInfo *cl_info;
int size_cl_info;
int valability;

ClientInfo *init_client_info() {
  ClientInfo *c = calloc(50, sizeof(ClientInfo));
  if (c == NULL) {
    printf("Error while allocating memory for the users' info!\n");
    free(c);
    return NULL;
  }
  return c;
}

void get_clients(char *path) {
  clients = calloc(1, sizeof(ClientsDB));
  FILE *fptr;
  size_t client_size = 16;
  // Open a file in read mode
  fptr = fopen(path, "r");

  char *string_size = calloc(3, sizeof(char));
  fgets(string_size, 3, fptr);

  clients->size = atoi(string_size);

  clients->clients = calloc(clients->size, sizeof(char *));

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

void get_resources(char *path) {
  resources = calloc(1, sizeof(Resources));
  FILE *fptr;

  fptr = fopen(path, "r");

  char *resources_size = calloc(3, sizeof(char));
  fgets(resources_size, 3, fptr);

  resources->size = atoi(resources_size);

  resources->resources = calloc(resources->size, sizeof(char *));
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
  FILE *fptr;
  // Open a file in read mode
  fptr = fopen(path, "r");
  permissions->permissions = calloc(100, sizeof(char *));

  size_t permission_size = 50;
  int i;
  for (i = 0; i < 100; i++) {
    if (feof(fptr)) {
      break;
    }
    getline(&(permissions->permissions[i]), &permission_size, fptr);

    if (permissions->permissions[i][strlen(permissions->permissions[i]) - 1] ==
        '\n') {
      permissions->permissions[i][strlen(permissions->permissions[i]) - 1] =
          '\0';
    }
  }
  permissions->size = i;
  fclose(fptr);
}

int prepare_approve_request_token_result(approve_response *result) {
  result->authorization_token = calloc(16, sizeof(char));
  if (result->authorization_token == NULL) {
    printf("Error while allocating memory for the approve result\n");
    free(result->authorization_token);
    fflush(stdout);
    return 0;
  }

  result->permissions = calloc(50, sizeof(char));
  if (result->permissions == NULL) {
    printf("Error while allocating memory for the approve result!\n");
    free(result->authorization_token);
    free(result->permissions);
    fflush(stdout);
    return 0;
  }

  return 1;
}

int modify_client_info(access input, access_response output) {
  for (int i = 0; i < size_cl_info; i++) {
    if (!strcmp(input.id, cl_info[i].id)) {
      strcpy(cl_info[i].permissions, input.authorization_token.permissions);
      strcpy(cl_info[i].access_token, output.access_token);
      if (atoi(input.refresh)) {
        strcpy(cl_info[i].refresh_token, output.refresh_token);
        printf("  RefreshToken = %s\n", output.refresh_token);
        fflush(stdout);
      }
      strcpy(cl_info[i].refresh, input.refresh);
      cl_info[i].valability = valability;

      return 1;
    }
  }

  return 0;
}

void add_client_info(access input, access_response output) {
  strcpy(cl_info[size_cl_info].id, input.id);
  strcpy(cl_info[size_cl_info].permissions,
         input.authorization_token.permissions);
  strcpy(cl_info[size_cl_info].access_token, output.access_token);

  if (atoi(input.refresh)) {
    strcpy(cl_info[size_cl_info].refresh_token, output.refresh_token);
    printf("  RefreshToken = %s\n", output.refresh_token);
    fflush(stdout);
  }
  strcpy(cl_info[size_cl_info].refresh, input.refresh);
  cl_info[size_cl_info++].valability = valability;
}

int generate_operation_status(char *result, action action) {
  for (int i = 0; i < size_cl_info; i++) {
    // if the access token corresponds with the one on the list
    if (!strcmp(action.access_token, cl_info[i].access_token)) {
      // check if the access token is still active
      if (cl_info[i].valability > 0) {
        (cl_info[i].valability)--;

        // check if the resource exists
        int found_resource = 0;
        for (int j = 0; j < resources->size; j++) {
          if (!strcmp(action.source, resources->resources[j])) {
            found_resource = 1;
            break;
          }
        }

        if (!found_resource) {
          strcpy(result, "RESOURCE_NOT_FOUND");
          printf("DENY (%s,%s,%s,%d)\n", action.operation, action.source,
                 action.access_token, cl_info[i].valability);
          fflush(stdout);
          return 1;
        }

        // check if the resource exists in the permissions
        // and the operation given will be granted by the server
        // by checking the user's permission on the resource
        char *resources_aux = calloc(50, sizeof(char));
        strcpy(resources_aux, cl_info[i].permissions);

        char *token;
        token = strtok(resources_aux, ",");

        int count = 0;
        while (token != NULL) {
          if (count % 2 == 0) {
            if (strcmp(action.source, token) == 0) {
              token = strtok(NULL, ",");

              for (int j = 0; j < strlen(token); j++) {
                // Operation is EXECUTE and X is used commonly for this
                if (token[j] == 'X') {
                  token[j] = 'E';
                }
                if (action.operation[0] == token[j]) {
                  strcpy(result, "PERMISSION_GRANTED");
                  printf("PERMIT (%s,%s,%s,%d)\n", action.operation,
                         action.source, action.access_token,
                         cl_info[i].valability);
                  fflush(stdout);
                  return 1;
                }
              }

              // resource exists, but the user cannot use the operation given
              strcpy(result, "OPERATION_NOT_PERMITTED");
              printf("DENY (%s,%s,%s,%d)\n", action.operation, action.source,
                     action.access_token, cl_info[i].valability);
              fflush(stdout);
              return 1;
            }
          }

          token = strtok(NULL, ",");
          count++;
        }

        // resource does not exist in the user's permissions
        strcpy(result, "OPERATION_NOT_PERMITTED");
        printf("DENY (%s,%s,%s,%d)\n", action.operation, action.source,
               action.access_token, cl_info[i].valability);
        fflush(stdout);
        return 1;
      }

      // valability is no longer available, so the token is expired
      // user should do another request
      strcpy(result, "TOKEN_EXPIRED");
      printf("DENY (%s,%s,,%d)\n", action.operation, action.source,
             cl_info[i].valability);
      fflush(stdout);
      return 1;
    }
  }

  return 0;
}

int prepare_new_token_result(refresh_output *result) {
  result->access_token = calloc(16, sizeof(char));
  if (result->access_token == NULL) {
    printf("Error while allocating memory for the new token result!\n");
    free(result->access_token);
    fflush(stdout);
    return 0;
  }

  result->refresh_token = calloc(16, sizeof(char));
  if (result->refresh_token == NULL) {
    printf("Error while allocating memory for the new token result!\n");
    free(result->access_token);
    free(result->refresh_token);
    fflush(stdout);
    return 0;
  }

  return 1;
}

