COMPILER = g++
OPTS = --std=c++20 -Wall -Werror -pedantic -g
LIBS = -lgmp
HEADERS = rsa.hpp
OBJECTS = rsa.o main.o
PROGRAM = rsa

all: $(PROGRAM)

%.o: %.cpp $(HEADERS)
	$(COMPILER) $(OPTS) -c $^

$(PROGRAM): $(OBJECTS)
	$(COMPILER) $(OPTS) -o $@ $^ $(LIBS)

run: $(PROGRAM)
	./$<

clean:
	rm -f *.o *.hpp.gch $(PROGRAM)