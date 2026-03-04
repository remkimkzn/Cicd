TARGET = s21_cat
CC = gcc
# WAY =../build/
CFLAGS = -c -Wall -Wextra -Werror 
 		

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(WAY)$(TARGET)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(WAY)$(TARGET) *.o

