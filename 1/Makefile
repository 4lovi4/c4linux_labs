all : libsolution

libsolution : solution.c
	gcc -shared solution.c -fPIC -o libsolution.so 	

clean :
	-rm *.so *.o 2>/dev/null 
