Simion George-Vlad
342C5
                Client/Server Application for OAuth authorization
                                    using RPC

Disclaimer: Application was made on Ubuntu 24.04.1 LTS.
            There will not be any rpcgen to be made.

Tests passed: 7/7

        This is a simulation of an OAuth authorization system of a client/server application
using the Remote Procedure Call (RPC).

        The interface has been explained in the OAuth.x for further more details.

        How does it work?

    Using the functions and the structures I declared in Server_utils.h, firstly, in OAuth_svc.c
it has been saved information from the database, such as the userIDs, server's resources and
the upcoming approvals which are related with the receiving access token process.
    After that, for the client side, I declared helpful functions and structures in Client_utils.h.
In OAuth_client.c, it has been saved the details about the client input in a list of orders, each 
element being a ClientOrder type. ClientOrder saves info about the ID, the action which will be
given to the server to process and the necessary details, according to the action made. It goes
through each order and by the action type, there are three functions made from the OAuth.x:

  1. grade_prog_1 represents the process where an user wants to have access to the resources of
the server. As input, the ID and the refresh type (activated or deactivated) were given. First step 
is to get the authorization token from the server. The client only needs to give the ID and the server
will check if the user is in the database. If so, then an authorization token will be given back, else,
an error message will be displayed saying that the user has not been found. After that, before getting 
the access token using the authorization token, the latter should be signed by the server. My take
here for the server logic was to have an integer that suggests whether the signing process went well
or not and then I attached the resources with the permissions by accessing the approvals' database
which made easier for the future explainations. If the signing was a success, then the process of
generating the access token starts. From the authorization token, it will be given the access token
and if the refresh mode was activated by the user, then a refresh token will be generated too, using
the access token. From the server side, all the information throughout this process will be saved
on a list of ClientInfo type and from the client side, the ID, the access token, the valability and
the refresh token (if the user opted for one) will be saved.

  2. grade_prog_2 represents the part where server will take care of the client's order which will
be about the actions made by the user. As input, the userID, the action, the resource and the access 
token are important. In order to validate the action, the server needs to check first if the user ID
is on the list which has all the information. If there is no user to be found, then the request will
be denied. If the user exists and the access token is associated with it, then it will check first
the valability. If the access token expired, then a message about it will be displayed to the client.
After that, the resource will be checked if it exists in the database. If not, the operation will
not be permitted by the server. If it was a success, then it will check if the operation is in
user's permission. If not, then the operation will not be permitted by the server. In the end, if
the operation of the user is available, then the server will give access granted to it.

  3. grade_prog_3 represents the case if the access_token is going to expire and the user
activated the refresh option. For this, the input needed was the user ID and the refresh token.
First the server checks if the user ID and the refresh token corresponds with the server's info.
Then, the procedure is a shorter version of grade_prog_1, this time it will only generate the tokens
needed: the access and the refresh ones. Both the client side and server side will be updated with
the new information and the process goes on with the remaining orders.
