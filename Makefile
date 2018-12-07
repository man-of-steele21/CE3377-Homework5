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
LDLIBS := -lm -lgsl -lgslcblas
RM := @rm
INCLUDE := -I $(GSL_DIR)

# Rules
all: dealer hand
dealer: dealer.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
hand: hand.o
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

