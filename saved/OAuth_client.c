/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "OAuth.h"
#include "OAuth_utils.h"

void
grade_prog_1(char *host, char *id, char *refresh)
{
	CLIENT *clnt;
	char * *result_1;
	authorization  request_authorization_token_1_arg;
	approve_response  *result_2;
	approve  approve_request_token_1_arg;
	access_response  *result_3;
	access  request_access_token_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, GRADE_PROG, GRADE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	request_authorization_token_1_arg.id = calloc(16, sizeof(char));
	strcpy(request_authorization_token_1_arg.id, id);

	result_1 = request_authorization_token_1(&request_authorization_token_1_arg, clnt);

	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if (strcmp(*result_1, "USER_NOT_FOUND") != 0) {
		approve_request_token_1_arg.authorization_token = calloc(16, sizeof(char));
		strcpy(approve_request_token_1_arg.authorization_token, *result_1);

		result_2 = approve_request_token_1(&approve_request_token_1_arg, clnt);
		if (result_2 == (approve_response *) NULL) {
			clnt_perror (clnt, "call failed");
		}

		if (result_2->verify == 2) {
			printf("%s\n", result_2->permissions);
		} else {
			request_access_token_1_arg.authorization_token.authorization_token = calloc(16, sizeof(char));
			request_access_token_1_arg.authorization_token.permissions = calloc(50, sizeof(char));
			request_access_token_1_arg.id = calloc(16, sizeof(char));
			request_access_token_1_arg.refresh = calloc(2, sizeof(char));

			strcpy(request_access_token_1_arg.authorization_token.authorization_token, *result_1);
			strcpy(request_access_token_1_arg.authorization_token.permissions, result_2->permissions);
			strcpy(request_access_token_1_arg.id, id);
			request_access_token_1_arg.authorization_token.verify = result_2->verify;

			result_3 = request_access_token_1(&request_access_token_1_arg, clnt);
			if (result_3 == (access_response *) NULL) {
				clnt_perror (clnt, "call failed");
			} else {
				printf("%s -> %s\n", result_2->authorization_token, result_3->access_token);
			}
		}
	} else {
		printf("%s\n", *result_1);
	}
	

	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	char *path;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	path = argv[2];

	int size_orders = 0;
	ClientOrder* orders = get_orders(path, &size_orders);

	for (int i = 0; i< size_orders; i++) {
		char *id = orders[i].id;
		char *action = orders[i].action;
		char *details = orders[i].details;

		if (strcmp(action, "REQUEST") == 0) {
			grade_prog_1(host, id, details);
		}
	}

exit (0);
}
