#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

Book* add_book(Book* database, int* count, int* capacity) 
{
    if (*count >= *capacity) 
    {
        *capacity *= 2;
        Book* new_db = realloc(database, *capacity * sizeof(Book));
        if (!new_db) 
        {
            printf("Memory allocation error!\n");
            return database;
        }
        database = new_db;
    }

    printf("Enter the name of the book: ");
    fgets(database[*count].title, MAX_TITLE_LEN, stdin);
    database[*count].title[strcspn(database[*count].title, "\n")] = '\0';

    printf("Enter the year of publication: ");
    scanf("%d", &database[*count].year);
    getchar();

    printf("Enter the price: ");
    scanf("%f", &database[*count].price);
    getchar();

    (*count)++;
    return database;
}

void remove_book(Book* database, int* count, int index) 
{
    if (index < 0 || index >= *count) 
    {
        printf("Invalid index!\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) 
    {
        database[i] = database[i + 1];
    }
    (*count)--;
}

void print_books(const Book* database, int count) 
{
    if (count == 0) 
    {
        printf("The database is empty!\n");
        return;
    }

    printf("\n%-5s %-40s %-10s %-10s\n", "¹", "Title", "Year", "Price");
    for (int i = 0; i < count; i++) 
    {
        printf("%-5d %-40s %-10d $%-10.2f\n", 
               i + 1, 
               database[i].title, 
               database[i].year, 
               database[i].price);
    }
}

void save_to_file(const Book* database, int count) 
{
    char filename[MAX_FILENAME_LEN];
    printf("Enter the file name to save: ");
    fgets(filename, MAX_FILENAME_LEN, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "w");
    if (!file) 
    {
        printf("File creation error!\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "%s;%d;%.2f\n", database[i].title, database[i].year, database[i].price);
    }

    fclose(file);
    printf("The data is saved to a file '%s'\n", filename);
}

void load_from_file(Book** database, int* count, int* capacity) 
{
    char filename[MAX_FILENAME_LEN];
    printf("Enter the file name to download: ");
    fgets(filename, MAX_FILENAME_LEN, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "r");
    if (!file) 
    {
        printf("File opening error!\n");
        return;
    }

    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) 
    {
        if (*count >= *capacity) 
        {
            *capacity *= 2;
            Book* new_db = realloc(*database, *capacity * sizeof(Book));
            if (!new_db) 
            {
                printf("Memory allocation error!\n");
                break;
            }
            *database = new_db;
        }

        char* token = strtok(line, ";");
        if (token) strncpy((*database)[*count].title, token, MAX_TITLE_LEN - 1);

        token = strtok(NULL, ";");
        if (token) (*database)[*count].year = atoi(token);

        token = strtok(NULL, ";");
        if (token) (*database)[*count].price = atof(token);

        (*count)++;
    }

    fclose(file);
    printf("Uploaded %d books from the file '%s'\n", *count, filename);
}
void sortBooks(Book *books, int count, int field, bool ascending) 
{
    int (*compare)(const void*, const void*) = NULL;
    
    switch (field) 
    {
        case 1: compare = ascending ? compareTitleAsc : compareTitleDesc; break;
        case 2: compare = ascending ? compareYearAsc : compareYearDesc; break;
        case 3: compare = ascending ? comparePriceAsc : comparePriceDesc; break;
        default: printf("Invalid field choice!\n"); return;
    }
    
    qsort(books, count, sizeof(Book), compare);
    printf("Sorting completed!\n");
}

int compareTitleAsc(const void *a, const void *b) 
{
    return strcmp(((Book*)a)->title, ((Book*)b)->title);
}
int compareTitleDesc(const void *a, const void *b) 
{
    return -strcmp(((Book*)a)->title, ((Book*)b)->title);
}
int compareYearAsc(const void *a, const void *b) 
{
    return ((Book*)a)->year - ((Book*)b)->year;
}
int compareYearDesc(const void *a, const void *b) 
{
    return ((Book*)b)->year - ((Book*)a)->year;
}
int comparePriceAsc(const void *a, const void *b) 
{
    float diff = ((Book*)a)->price - ((Book*)b)->price;
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}
int comparePriceDesc(const void *a, const void *b) 
{
    float diff = ((Book*)b)->price - ((Book*)a)->price;
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}