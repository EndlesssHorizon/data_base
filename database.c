#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"

void addBook(Book *books, int *count) {
    if (*count >= MAX_ITEMS) {
        printf("Maximum book limit reached!\n");
        return;
    }
    
    printf("Enter book title: ");
    fgets(books[*count].title, MAX_NAME_LENGTH, stdin);
    books[*count].title[strcspn(books[*count].title, "\n")] = '\0';
    
    printf("Enter publication year: ");
    scanf("%d", &books[*count].year);
    
    printf("Enter price: ");
    scanf("%f", &books[*count].price);
    
    (*count)++;
    printf("Book added successfully!\n");
}

void deleteBook(Book *books, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid index!\n");
        return;
    }
    
    for (int i = index; i < *count - 1; i++) {
        books[i] = books[i + 1];
    }
    
    (*count)--;
    printf("Book deleted successfully!\n");
}

void printBooks(const Book *books, int count) {
    if (count == 0) {
        printf("No books in database!\n");
        return;
    }
    
    printf("\nBook List:\n");
    printf("#  Title%-*sYear  Price\n", MAX_NAME_LENGTH - 5, "");
    for (int i = 0; i < count; i++) {
        printf("%-2d %-*s %-4d $%.2f\n", 
               i + 1, 
               MAX_NAME_LENGTH, 
               books[i].title, 
               books[i].year, 
               books[i].price);
    }
}

void saveToFile(const Book *books, int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%d;%.2f\n", books[i].title, books[i].year, books[i].price);
    }
    
    fclose(file);
    printf("Data saved to '%s' successfully!\n", filename);
}

void loadFromFile(Book *books, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading!\n");
        return;
    }
    
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && *count < MAX_ITEMS) {
        char *token = strtok(line, ";");
        if (token) strcpy(books[*count].title, token);
        
        token = strtok(NULL, ";");
        if (token) books[*count].year = atoi(token);
        
        token = strtok(NULL, ";");
        if (token) books[*count].price = atof(token);
        
        (*count)++;
    }
    
    fclose(file);
    printf("Loaded %d books from '%s'\n", *count, filename);
}

void sortBooks(Book *books, int count, int field, bool ascending) {
    int (*compare)(const void*, const void*) = NULL;
    
    switch (field) {
        case 1: compare = ascending ? compareTitleAsc : compareTitleDesc; break;
        case 2: compare = ascending ? compareYearAsc : compareYearDesc; break;
        case 3: compare = ascending ? comparePriceAsc : comparePriceDesc; break;
        default: printf("Invalid field choice!\n"); return;
    }
    
    qsort(books, count, sizeof(Book), compare);
    printf("Sorting completed!\n");
}

// Sorting functions
int compareTitleAsc(const void *a, const void *b) {
    return strcmp(((Book*)a)->title, ((Book*)b)->title);
}
int compareTitleDesc(const void *a, const void *b) {
    return -strcmp(((Book*)a)->title, ((Book*)b)->title);
}
int compareYearAsc(const void *a, const void *b) {
    return ((Book*)a)->year - ((Book*)b)->year;
}
int compareYearDesc(const void *a, const void *b) {
    return ((Book*)b)->year - ((Book*)a)->year;
}
int comparePriceAsc(const void *a, const void *b) {
    float diff = ((Book*)a)->price - ((Book*)b)->price;
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}
int comparePriceDesc(const void *a, const void *b) {
    float diff = ((Book*)b)->price - ((Book*)a)->price;
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}