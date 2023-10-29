all:fcc
fcc:	fcc.c
	rm -rf account
	mkdir account
	gcc fcc.c -o fcc -DLOGFILE="\"$(PWD)/account/login\""
clean:
	rm -rf account
	rm fcc
	
