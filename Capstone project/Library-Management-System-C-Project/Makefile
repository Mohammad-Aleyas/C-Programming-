CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src/main.c src/storage.c src/books.c src/members.c src/circulation.c src/reports.c
TARGET = library_system

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.dat Library_Audit_Report.txt
