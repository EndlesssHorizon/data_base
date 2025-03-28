#pragma once

#define MAX_NAME_LENGTH 50
#define MAX_ITEMS 100

typedef struct 
{
    char title[MAX_NAME_LENGTH];
    int year;
    float price;
} Book;

// �������� �����
void addBook(Book *books, int *count);
// ������� �����
void deleteBook(Book *books, int *count, int index);
// ������� ������ ����
void printBooks(const Book *books, int count);
// ��������� � ����
void saveToFile(const Book *books, int count, const char *filename);
// ��������� �� �����
void loadFromFile(Book *books, int *count, const char *filename);
// ����������� �����
void sortBooks(Book *books, int count, int field, bool ascending);


// ���������� �� �������� ���� � ������� �����������
int compareTitleAsc(const void *a, const void *b);
// ���������� �� �������� ���� � ������� ��������
int compareTitleDesc(const void *a, const void *b);
// ���������� �� ����� ���������� � ������� �����������
int compareYearAsc(const void *a, const void *b);
// ���������� �� ����� ���������� � ������� ��������
int compareYearDesc(const void *a, const void *b);
// ���������� ���� � ������� �����������
int comparePriceAsc(const void *a, const void *b);
// ���������� ���� � ������� ��������
int comparePriceDesc(const void *a, const void *b);