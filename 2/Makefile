all:	solution.c
	gcc solution.c -o solution -ldl -Wl,-rpath .  

lib:	lib_sol.c
	gcc -shared -fPIC lib_sol.c -o libShared.so 

clean:	
	- rm *.o *.so solution
