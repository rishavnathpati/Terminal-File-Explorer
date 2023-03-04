CC = g++
CFLAGS = -Wall 
DEPS = myheader.h 
OBJ = mydirectoryfunction.o main.o navigate.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tfe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	rm -rf *o

clean:
	rm -rf *o tfe

