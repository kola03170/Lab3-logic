#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct node
{
    char inf[256];
    int priority;
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

    do
    {
        printf("Введите приоритет (целое число > 0): ");
        scanf_s("%d", &p->priority);

        if (p->priority <= 0)
        {
            printf("Ошибка: приоритет не может быть отрицательным или равным нулю. Повторите ввод.\n");
        }

    } while (p->priority <= 0);

    p->next = NULL;

    return p;
}

void add_priority(void)
{
    struct node* p = get_struct();
    struct node* cur;

    if (head == NULL)
    {
        head = p;
        return;
    }


    if (p->priority < head->priority)
    {
        p->next = head;
        head = p;
        return;
    }

    cur = head;

    while (cur->next != NULL &&
        cur->next->priority <= p->priority)
    {
        cur = cur->next;
    }

    p->next = cur->next;
    cur->next = p;
}

void review(void)
{
    struct node* cur = head;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    printf("\nПриоритетная очередь:\n");

    while (cur != NULL)
    {
        printf("Объект: %s, приоритет: %d\n",
            cur->inf, cur->priority);

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

    printf("Удален объект: %s\n", temp->inf);

    free(temp);
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do
    {
        printf("\n--- МЕНЮ ---\n");
        printf("1 - Добавить элемент\n");
        printf("2 - Просмотреть очередь\n");
        printf("3 - Удалить первый элемент\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_priority();
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
