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
struct node* tail = NULL;

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

void add_queue(void)
{
    struct node* p = get_struct();

    if (head == NULL)
    {
        head = p;
        tail = p;
    }
    else
    {
        tail->next = p;
        tail = p;
    }

    printf("Элемент добавлен в очередь\n");
}

void review(void)
{
    struct node* cur = head;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    printf("\nОчередь:\n");

    while (cur != NULL)
    {
        printf("Объект: %s\n", cur->inf);
        cur = cur->next;
    }
}

void delete_first(void)
{
    struct node* temp;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    temp = head;
    head = head->next;

    if (head == NULL)
    {
        tail = NULL;
    }

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
        printf("\n--- ОЧЕРЕДЬ ---\n");
        printf("1 - Добавить элемент\n");
        printf("2 - Просмотреть очередь\n");
        printf("3 - Удалить первый элемент\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_queue();
            break;

        case 2:
            review();
            break;

        case 3:
            delete_first();
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