#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {

    pbook b1 = creat_book("Book1", 111);
    pbook b2 = creat_book("Football", 222);
    pbook b3 = creat_book("Football2", 333);
    PAdptArray nullptr = CreateAdptArray(NULL, NULL, NULL);
    assert(nullptr == NULL);
    assert(GetAdptArraySize(nullptr) == -1);

    PAdptArray mybooks = CreateAdptArray(copy_book, delete_book, print_book);
    SetAdptArrayAt(mybooks, 3, b1);
    SetAdptArrayAt(mybooks, 5, b2);
    assert(GetAdptArraySize(mybooks) == 6);
    SetAdptArrayAt(mybooks, 2, b3);
    assert(GetAdptArraySize(mybooks) == 6);
    printf("the size is %d\n", GetAdptArraySize(mybooks));
    pbook b = GetAdptArrayAt(mybooks, 7);
    assert(b == NULL); // doesn't fail
    PrintDB(mybooks);
    b = GetAdptArrayAt(mybooks, 3);
    printf("the book is %s\n", b->name);
    assert(strcmp(b->name, "Book1") == 0);

    PrintDB(mybooks);
    pperson p1 = creat_person("Amit", "Kabalo", 314993247);
    pperson p2 = creat_person("Nadav", "Kabalo", 123456789);
    pperson p3 = creat_person("Sigal", "Kabalo", 1);
    pperson p4 = NULL;

    PAdptArray persons = CreateAdptArray(copy_person, delete_person, print_person);
    SetAdptArrayAt(persons, 2, p1);
    SetAdptArrayAt(persons, 8, p2);
    SetAdptArrayAt(persons, 1, p3);
    assert(SetAdptArrayAt(persons, 9, p4) == FAIL);
    assert(GetAdptArrayAt(persons, 10) == NULL);
    printf("the size is %d\n", GetAdptArraySize(persons)); // prints 9
    PrintDB(persons); // prints:
    DeleteAdptArray(mybooks);
    DeleteAdptArray(persons);
    delete_book(b1);
    delete_book(b2);
    delete_book(b);
    delete_person(p1);
    delete_person(p2);

    return 0;
}