#pragma once

#include <stdbool.h>

#define MAX_TITLE_LEN 100
#define MAX_FILENAME_LEN 50
#define INITIAL_CAPACITY 5

typedef struct 
{
    char title[MAX_TITLE_LEN];
    int year;
    float price;
} Book;

// Основные функции работы с базой данных
Book* add_book(Book* database, int* count, int* capacity);
void remove_book(Book* database, int* count, int index);
void print_books(const Book* database, int count);
void save_to_file(const Book* database, int count);
void load_from_file(Book** database, int* count, int* capacity);

// Функции сортировки
void sortBooks(Book *books, int count, int field, bool ascending);

// Вспомогательные функции для сортировки
int compareTitleAsc(const void *a, const void *b);
int compareTitleDesc(const void *a, const void *b);
int compareYearAsc(const void *a, const void *b);
int compareYearDesc(const void *a, const void *b);
int comparePriceAsc(const void *a, const void *b);
int comparePriceDesc(const void *a, const void *b);
