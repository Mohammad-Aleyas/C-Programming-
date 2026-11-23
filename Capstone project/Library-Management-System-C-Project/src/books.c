#include <stdio.h>
#include <string.h>
#include "library.h"

extern Book books[MAX_BOOKS];
extern int book_count;

void addBook(void) {
    if (book_count >= MAX_BOOKS) {
        printf("[Error] Book inventory capacity reached.\n");
        return;
    }

    Book b;
    printf("Enter Book ID (e.g., B105): ");
    scanf("%19s", b.id);
    clearInputBuffer();

    if (findBookIndex(b.id) != -1) {
        printf("[Error] Book ID '%s' already exists!\n", b.id);
        return;
    }

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Category (Computer Science / Mathematics / Electronics / Management / Literature): ");
    fgets(b.category, sizeof(b.category), stdin);
    b.category[strcspn(b.category, "\n")] = '\0';

    printf("Enter Total Quantity: ");
    if (scanf("%d", &b.total_qty) != 1 || b.total_qty < 1) {
        clearInputBuffer();
        printf("[Error] Quantity must be at least 1.\n");
        return;
    }
    b.available_qty = b.total_qty;

    books[book_count++] = b;
    saveAllData();
    printf("[Success] Book '%s' added to catalog.\n", b.title);
}

void displayBooks(void) {
    if (book_count == 0) {
        printf("No books found in inventory.\n");
        return;
    }

    printf("\n%-8s | %-28s | %-18s | %-18s | %-5s | %-5s\n",
           "ID", "Title", "Author", "Category", "Total", "Avail");
    printf("-----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < book_count; i++) {
        printf("%-8s | %-28s | %-18s | %-18s | %-5d | %-5d\n",
               books[i].id, books[i].title, books[i].author,
               books[i].category, books[i].total_qty, books[i].available_qty);
    }
}

void editBook(void) {
    char id[20];
    printf("Enter Book ID to edit: ");
    scanf("%19s", id);
    clearInputBuffer();

    int idx = findBookIndex(id);
    if (idx == -1) {
        printf("[Error] Book ID '%s' not found.\n", id);
        return;
    }

    Book *b = &books[idx]; /* Pointer pass-by-reference update */
    int new_qty;

    printf("Editing '%s' (Current Author: %s, Total Qty: %d)\n", b->title, b->author, b->total_qty);

    printf("Enter New Title: ");
    fgets(b->title, sizeof(b->title), stdin);
    b->title[strcspn(b->title, "\n")] = '\0';

    printf("Enter New Author: ");
    fgets(b->author, sizeof(b->author), stdin);
    b->author[strcspn(b->author, "\n")] = '\0';

    printf("Enter New Category: ");
    fgets(b->category, sizeof(b->category), stdin);
    b->category[strcspn(b->category, "\n")] = '\0';

    printf("Enter New Total Quantity: ");
    if (scanf("%d", &new_qty) == 1 && new_qty >= 1) {
        int diff = new_qty - b->total_qty;
        b->total_qty = new_qty;
        b->available_qty = (b->available_qty + diff < 0) ? 0 : (b->available_qty + diff);
    }

    saveAllData();
    printf("[Success] Book '%s' updated.\n", b->id);
}

void deleteBook(void) {
    char id[20];
    printf("Enter Book ID to delete: ");
    scanf("%19s", id);

    int idx = findBookIndex(id);
    if (idx == -1) {
        printf("[Error] Book ID '%s' not found.\n", id);
        return;
    }

    for (int i = idx; i < book_count - 1; i++) {
        books[i] = books[i + 1];
    }
    book_count--;
    saveAllData();
    printf("[Success] Book '%s' deleted from catalog.\n", id);
}

void searchAndFilterBooks(void) {
    int mode;
    char keyword[100];
    printf("Search by: [1] Title/Author/ID Keyword  [2] Category Filter : ");
    scanf("%d", &mode);
    clearInputBuffer();

    printf("Enter search keyword or category: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    printf("\nMatching Books:\n");
    for (int i = 0; i < book_count; i++) {
        int match = 0;
        if (mode == 2) {
            if (strstr(books[i].category, keyword) != NULL) match = 1;
        } else {
            if (strcmp(books[i].id, keyword) == 0 ||
                strstr(books[i].title, keyword) != NULL ||
                strstr(books[i].author, keyword) != NULL) {
                match = 1;
            }
        }

        if (match) {
            printf(" -> [%s] %s by %s (%s) | Available: %d/%d\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].category, books[i].available_qty, books[i].total_qty);
            found = 1;
        }
    }

    if (!found) {
        printf("No books matched '%s'.\n", keyword);
    }
}
