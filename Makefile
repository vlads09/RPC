build:
	# rpcgen -C -a OAuth.x
	gcc -g -o server OAuth_server.c OAuth_svc.c OAuth_xdr.c OAuth_utils.c -ltirpc -I/usr/include/tirpc -Wall
	gcc -g -o client OAuth_client.c OAuth_clnt.c OAuth_xdr.c OAuth_utils.c -ltirpc -I/usr/include/tirpc -Wall
clean:
	rm -f client server OAuth_server.c OAuth_svc.c OAuth_client.c OAuth_clnt.c Makefile.OAuth OAuth_xdr.c OAuth.h