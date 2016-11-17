CC=gcc
N=solution

$(N) : $(N).o
	$(CC) $^ -o $@

$(N).o : $(N).c
	$(CC) -c $^ 

clean : 
	rm -rf *.o $(N) $(N1)

