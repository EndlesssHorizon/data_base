#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add book\n");
    printf("2. Delete book\n");
    printf("3. Show all books\n");
    printf("4. Save to file\n");
    printf("5. Load from file\n");
    printf("6. Sort books\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main(int argc, char *argv[]) {
    Book books[MAX_ITEMS];
    int count = 0;
    char filename[100] = "books.txt";
    
    if (argc > 1) {
        strcpy(filename, argv[1]);
        loadFromFile(books, &count, filename);
    }

    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        switch (choice) {
            case 1: addBook(books, &count); break;
            case 2: {
                int index;
                printf("Enter book number to delete: ");
                if (scanf("%d", &index) == 1) deleteBook(books, &count, index - 1);
                while (getchar() != '\n');
                break;
            }
            case 3: printBooks(books, count); break;
            case 4: {
                printf("Enter filename (default %s): ", filename);
                char newFilename[100];
                fgets(newFilename, sizeof(newFilename), stdin);
                newFilename[strcspn(newFilename, "\n")] = '\0';
                if (strlen(newFilename) > 0) strcpy(filename, newFilename);
                saveToFile(books, count, filename);
                break;
            }
            case 5: {
                printf("Enter filename (default %s): ", filename);
                char newFilename[100];
                fgets(newFilename, sizeof(newFilename), stdin);
                newFilename[strcspn(newFilename, "\n")] = '\0';
                if (strlen(newFilename) > 0) strcpy(filename, newFilename);
                loadFromFile(books, &count, newFilename);
                break;
            }
            case 6: {
                int field, order;
                printf("Sort by:\n1. Title\n2. Year\n3. Price\nChoose field: ");
                if (scanf("%d", &field) == 1 && field >= 1 && field <= 3) {
                    printf("Order:\n1. Ascending\n2. Descending\nChoose order: ");
                    if (scanf("%d", &order) == 1 && (order == 1 || order == 2)) {
                        sortBooks(books, count, field, order == 1);
                    }
                }
                while (getchar() != '\n');
                break;
            }
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}