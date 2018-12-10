# Exercise5.0 Makefile
# Jackson Steele

# Files
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

# Options
CC := g++
CFLAGS := -O3
GSL_DIR := ~/local/gsl-2.5
LDFLAGS := -L/usr/lib -L $(GSL_DIR)/cblas/.libs -L $(GSL_DIR)/.libs
GETPOT_DIR := ~/local/getpot-c++/c++
LDLIBS := -lm -lgsl -lgslcblas
RM := @rm
INCLUDE := -I $(GSL_DIR) -I $(GETPOT_DIR)

# Rules
all: dealer dealerbonus0 dealerbonus1 dealerbonus2 hand handbonus1 handbonus2
dealer: dealer.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
dealerbonus0: dealerbonus0.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
dealerbonus1: dealerbonus1.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
dealerbonus2: dealerbonus2.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
hand: hand.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
handbonus1: handbonus1.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
handbonus2: handbonus2.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $<
clean:
	$(RM) $(OBJ) $(EXEC)

# Debugging:
test:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(INCLUDE)

