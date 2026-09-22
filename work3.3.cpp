#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct node
{
    char inf[256];
    struct node* next;
};

struct node* head = NULL;

struct node* get_struct(void)
{
    struct node* p;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf_s("%255s", p->inf, (unsigned)_countof(p->inf));

    p->next = NULL;

    return p;
}

void push(void)
{
    struct node* p = get_struct();

    p->next = head;
    head = p;

    printf("Элемент добавлен в стек\n");
}

void review(void)
{
    struct node* cur = head;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("\nСтек:\n");

    while (cur != NULL)
    {
        printf("Объект: %s\n", cur->inf);
        cur = cur->next;
    }
}

void pop(void)
{
    struct node* temp;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    temp = head;
    head = head->next;

    printf("Удален объект: %s\n", temp->inf);

    free(temp);
}

int main(void)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int choice;

    do
    {
        printf("\n--- СТЕК ---\n");
        printf("1 - Добавить элемент\n");
        printf("2 - Просмотреть стек\n");
        printf("3 - Удалить верхний элемент\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;

        case 2:
            review();
            break;

        case 3:
            pop();
            break;

        case 0:
            printf("Выход\n");
            break;

        default:
            printf("Неверный выбор\n");
        }

    } while (choice != 0);

    return 0;
}