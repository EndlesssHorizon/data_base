#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

#define DEFAULT_FILENAME "books.txt"

void display_menu() 
{
    printf("\n=== Book Database Menu ===\n");
    printf("1. Add a book\n");
    printf("2. Remove a book\n");
    printf("3. Display all books\n");
    printf("4. Save database to file\n");
    printf("5. Load database from file\n");
    printf("6. Sort books\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void display_sort_options() 
{
    printf("\n=== Sort Options ===\n");
    printf("1. By title (A-Z)\n");
    printf("2. By title (Z-A)\n");
    printf("3. By year (ascending)\n");
    printf("4. By year (descending)\n");
    printf("5. By price (low to high)\n");
    printf("6. By price (high to low)\n");
    printf("Enter sorting option: ");
}

void clear_input_buffer() 
{
    while (getchar() != '\n');
}

int main(int argc, char *argv[]) 
{
    int capacity = INITIAL_CAPACITY;
    int count = 0;
    Book* database = malloc(capacity * sizeof(Book));
    char filename[MAX_FILENAME_LEN] = DEFAULT_FILENAME;
    
    if (argc > 1) 
    {
        strncpy(filename, argv[1], MAX_FILENAME_LEN - 1);
        load_from_file(&database, &count, &capacity);
    }

    int choice;
    do {
        display_menu();
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) 
        {
            case 1:
                database = add_book(database, &count, &capacity);
                break;
                
            case 2:
                if (count == 0) 
                {
                    printf("Database is empty!\n");
                    break;
                }
                printf("Enter book number to remove (1-%d): ", count);
                int index;
                if (scanf("%d", &index) == 1 && index >= 1 && index <= count) 
                {
                    remove_book(database, &count, index - 1);
                } 
                else 
                {
                    printf("Invalid book number!\n");
                }
                clear_input_buffer();
                break;
                
            case 3:
                print_books(database, count);
                break;
                
            case 4:
                printf("Enter filename (default: %s): ", filename);
                char new_filename[MAX_FILENAME_LEN];
                fgets(new_filename, MAX_FILENAME_LEN, stdin);
                new_filename[strcspn(new_filename, "\n")] = '\0';
                if (strlen(new_filename) > 0) 
                {
                    strncpy(filename, new_filename, MAX_FILENAME_LEN - 1);
                }
                save_to_file(database, count);
                break;
                
            case 5:
                printf("Enter filename (default: %s): ", filename);
                fgets(new_filename, MAX_FILENAME_LEN, stdin);
                new_filename[strcspn(new_filename, "\n")] = '\0';
                if (strlen(new_filename) > 0) 
                {
                    strncpy(filename, new_filename, MAX_FILENAME_LEN - 1);
                }
                load_from_file(&database, &count, &capacity);
                break;
                
            case 6:
                if (count == 0) 
                {
                    printf("Database is empty!\n");
                    break;
                }
                display_sort_options();
                int sort_choice;
                if (scanf("%d", &sort_choice) == 1 && sort_choice >= 1 && sort_choice <= 6) 
                {
                    int field = (sort_choice + 1) / 2;
                    bool ascending = (sort_choice % 2) == 1;
                    sortBooks(database, count, field, ascending);
                    printf("Books sorted successfully.\n");
                } 
                else 
                {
                    printf("Invalid sort option!\n");
                }
                clear_input_buffer();
                break;
                
            case 0:
                printf("Saving to %s and exiting...\n", filename);
                save_to_file(database, count);
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    free(database);
    return 0;
}