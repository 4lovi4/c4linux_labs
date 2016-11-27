CC=gcc
N=solution
HELP=help

$(N) : $(N).o
	$(CC) $^ -o $@

$(N).o : $(N).c
	$(CC) -c $^ 

$(HELP) : $(HELP).c
	$(CC) $^ -o $@

clean : 
	rm -rf *.o $(N)

