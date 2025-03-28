#pragma once

#define MAX_NAME_LENGTH 50
#define MAX_ITEMS 100

typedef struct 
{
    char title[MAX_NAME_LENGTH];
    int year;
    float price;
} Book;

// Добавить книгу
void addBook(Book *books, int *count);
// Удалить книгу
void deleteBook(Book *books, int *count, int index);
// Вывести список книг
void printBooks(const Book *books, int count);
// Сохранить в файл
void saveToFile(const Book *books, int count, const char *filename);
// Загрузить из файла
void loadFromFile(Book *books, int *count, const char *filename);
// Сортировать книги
void sortBooks(Book *books, int count, int field, bool ascending);


// Сортировка по названию книг в порядке возрастания
int compareTitleAsc(const void *a, const void *b);
// Сортировка по названию книг в порядке убывания
int compareTitleDesc(const void *a, const void *b);
// Сортировка по годам публикации в порядке возрастания
int compareYearAsc(const void *a, const void *b);
// Сортировка по годам публикации в порядке убывания
int compareYearDesc(const void *a, const void *b);
// Сортировка цены в порядке возрастания
int comparePriceAsc(const void *a, const void *b);
// Сортировка цены в порядке убывания
int comparePriceDesc(const void *a, const void *b);