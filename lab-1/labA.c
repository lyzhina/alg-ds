#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "LabA.h"

//�������, ����������� ����� �� ����� � ������
int ReadList(list* mylist, FILE* F) {

    list* WordBase = (list*)calloc(1, sizeof(list));

    fscanf(F, "%s", &WordBase->string);

    WordBase->previous = mylist->previous;
    mylist->previous = WordBase;

    if (feof(F) != 0 )  
        return 0;
    else
        ReadList(mylist, F);
}
//�������, �������� 2 ����� ������� ��� ������������� � ������������ ��������� �� �������������� ��������� ������
list* SortSubstitution(list* word) {
    //���� ����� ����� � ������ �������
    if (strlen(word->string) < strlen(word->previous->string)  || (strlen(word->string) == strlen(word->previous->string) && strcmp(word->string, word->previous->string) <= 0)) {
        if (word->previous->previous != NULL)
            word->previous = SortSubstitution(word->previous);
        return word;
    }
    //���� ����� ����� �������� �������
    else if (strlen(word->string) > strlen(word->previous->string) || (strlen(word->string) == strlen(word->previous->string) && strcmp(word->string, word->previous->string)>0)) {
        list intermediate;
        list* sortedStart;
        sortedStart = word->previous;
        intermediate.previous = word->previous->previous;
        word->previous->previous = word;
        word->previous = intermediate.previous;
        flagSort++; //������� ���������� ������
        if (sortedStart->previous->previous != NULL)
            sortedStart->previous = SortSubstitution(sortedStart->previous);
        return sortedStart;
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
//�������, ����������� ������ �������
void SortList(list* mylist) {
    flagSort = 0;
    mylist->previous = SortSubstitution(mylist->previous);
    if (flagSort != 0) //���� �� ������� �� ����� �������, ������, ������ ������������
        SortList(mylist);
}
