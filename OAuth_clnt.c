/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "OAuth.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

char **
request_authorization_token_1(authorization *argp, CLIENT *clnt)
{
	static char *clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, request_authorization_token,
		(xdrproc_t) xdr_authorization, (caddr_t) argp,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

approve_response *
approve_request_token_1(approve *argp, CLIENT *clnt)
{
	static approve_response clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, approve_request_token,
		(xdrproc_t) xdr_approve, (caddr_t) argp,
		(xdrproc_t) xdr_approve_response, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

access_response *
request_access_token_1(access *argp, CLIENT *clnt)
{
	static access_response clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, request_access_token,
		(xdrproc_t) xdr_access, (caddr_t) argp,
		(xdrproc_t) xdr_access_response, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

char **
validate_delegated_action_2(action *argp, CLIENT *clnt)
{
	static char *clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, validate_delegated_action,
		(xdrproc_t) xdr_action, (caddr_t) argp,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

refresh_output *
get_new_token_3(refresh_input *argp, CLIENT *clnt)
{
	static refresh_output clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, get_new_token,
		(xdrproc_t) xdr_refresh_input, (caddr_t) argp,
		(xdrproc_t) xdr_refresh_output, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
