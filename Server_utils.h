#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "OAuth.h"

typedef struct ClientsDB {
  size_t size;
  char **clients;
} ClientsDB;

typedef struct ClientInfo {
  char permissions[50];
  char access_token[16];
  char refresh[2];
  char refresh_token[16];
  char id[16];
  int valability;
} ClientInfo;

typedef struct Resources {
  size_t size;
  char **resources;
} Resources;

typedef struct Permissions {
  size_t size;
  char **permissions;
  size_t current;
} Permissions;

void get_clients(char *path);
void get_resources(char *path);
void read_permissions(char *path);
ClientInfo *init_client_info();

// Allocates memory for the approval result.
int prepare_approve_request_token_result(approve_response *result);

// If the user already exists, then modify just the information.
int modify_client_info(access input, access_response output);

// Adds a new client in the information about clients list.
void add_client_info(access input, access_response output);

// Server validates the operation and returns the correct status.
int generate_operation_status(char *result, action action);

// Allocates memory for the refresh operation
int prepare_new_token_result(refresh_output *result);

extern ClientsDB *clients;
extern Resources *resources;
extern Permissions *permissions;
extern int valability;
extern ClientInfo *cl_info;
extern int size_cl_info;