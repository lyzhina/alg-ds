#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "LabA.h"

//�������, ������ ����� ��� �����
list* PutWord(list* old, list* newWord) {
    if (strlen(newWord->string) < strlen(old->string) || (strlen(newWord->string) == strlen(old->string) && strcmp(newWord->string, old->string) <= 0)) {
        newWord->previous = old;
        return newWord;
    }
    else if (old->previous == NULL) {
        newWord->previous = NULL;
        old->previous = newWord;
        return old;
    }
    else {
        old->previous = PutWord(old->previous, newWord);
        return old;
    }
}

//�������, ����������� ������
void MakeList(list* mylist, FILE* F) {
    while (feof(F) == 0) {
        list* new = (list*)calloc(1, sizeof(list));
        if (new != NULL) {
            fscanf(F, "%s", &new->string);
            WordToList(mylist, new);
        }
        else printf("Error: no memory");
    }
}

//�������, ������������ ����� � ������ �����
void WordToList(list* mylist, list* newWord) {
    if (mylist->previous == NULL) {
        newWord->previous = NULL;
        mylist->previous = newWord;
    }
    else {
        mylist->previous = PutWord(mylist->previous, newWord);
    }
}

//�������, ���������� ������
void ListPrint(list* word) {
    printf("%s\n", word->string);
    if (word->previous != NULL)
        ListPrint(word->previous);
}
//�������, ������������ ����� �����
int NumberOfLetters(void) {
    int number;
    printf("Enter the number of letters:\n");
    scanf("%d", &number);
    flagSameLength = 0;
    return number;
}
//�������, ���������� �����, ������� ��������� N
void ListCountMore(list* word) {
    if(strlen(word->string) > N)
    printf("%s\n", word->string);
    if (word->previous != NULL)
        ListCountMore(word->previous);
}
//�������, ���������� �����, ������ ��������� �����
void ListCountSame(list* word, int number) {
    if (strlen(word->string) == number) {
        flagSameLength++;
        if (flagSameLength == 1)//��� ���������� ������� ����� ����� �����
            printf("Words of the same length:\n");
        printf("%s\n", word->string);
    }
    if (word->previous != NULL)
        ListCountSame(word->previous, number);
    else  if (flagSameLength == 0)
        printf("No words of the same length.");
}

