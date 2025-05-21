BUILD: 
		gcc main.c -Wall -Werror -Ideps -lkrpc_cnano -o telem

FREE_BUILD:
	gcc main.c -Wall -Ideps -lkrpc_cnano -o telem


RUN:
		./telem
