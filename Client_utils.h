#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "OAuth.h"

typedef struct ClientSideInfo
{
    char id[16];
    char access_token[16];
    int valability;
    int refresh;
    char refresh_token[16];
} ClientSideInfo;

typedef struct ClientOrder
{
    char id[16];
    char action[20]; // any operation a user can do and the REQUEST action
    char details[20]; // resource that the user want to access 
                    // or if the refresh mode is activated (REQUEST)
} ClientOrder;

ClientSideInfo *init_clients_info();

// Reads the client input and saves the information needed when operating.
ClientOrder* get_orders(char* path, int* i);

// Copies the id into the authorization structure.
int prepare_request_token_args(authorization *authorization, char *id);

// Copies the authorization token into the approve structure.
int prepare_approve_request_token_args(approve *approve, char *authorization);

// Copies the necessary information for the access token request.
int prepare_request_access_token_args(access *access, char *authorization, char *permissions, char *id, char *refresh, int verify);

// Prints the user's tokens from the server response.
void print_tokens(char *refresh, char *authorization, access_response tokens);

// Adds or modify a client that has a new access token.
void add_or_modify_client(ClientSideInfo *clients_info, int *current_clients_info, char *id, char *refresh, access_response tokens);

// Copies the information about the user's incoming operation.
int prepare_validate_delegated_action(action *action, char *access_token, char *op, char *source);

// If the user's refresh mode is activated, then this copies the id and the refresh token for getting a new access token.
int prepare_get_new_token(refresh_input *input, char *id, char *refresh_token);

// Modifies the current access token with a new one (as well as the refresh token).
void modify_access_token(ClientSideInfo *clients_info, int current_clients_info, char *id, refresh_output tokens);
