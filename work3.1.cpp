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

int name_exists(const char* name)
{
    struct node* cur = head;

    while (cur != NULL)
    {
        if (strcmp(cur->inf, name) == 0)
        {
            return 1;
        }
        cur = cur->next;
    }

    return 0;
}

struct node* get_struct(void)
{
    struct node* p;

    p = (struct node*)malloc(sizeof(struct node));

    if (p == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    int ok = 0;

    while (!ok)
    {
        printf("Введите название объекта: ");
        scanf_s("%255s", p->inf, (unsigned)_countof(p->inf));

        if (name_exists(p->inf))
        {
            printf("Ошибка: объект с таким именем уже существует. Введите другое имя.\n");
        }
        else
        {
            ok = 1;
        }
    }

    p->priority = 0;

    while (p->priority <= 0)
    {
        printf("Введите приоритет (целое число > 0): ");
        scanf_s("%d", &p->priority);

        if (p->priority <= 0)
        {
            printf("Ошибка: приоритет не может быть отрицательным или равным нулю. Повторите ввод.\n");
        }
    }

    p->next = NULL;

    return p;
}

void insert_sorted(struct node* p)
{
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

void add_priority(void)
{
    struct node* p = get_struct();

    insert_sorted(p);
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

void change_priority(void)
{
    char name[256];
    struct node* cur = head;
    struct node* target = NULL;
    int new_priority = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    printf("Введите имя объекта, у которого нужно изменить приоритет: ");
    scanf_s("%255s", name, (unsigned)_countof(name));

    while (cur != NULL)
    {
        if (strcmp(cur->inf, name) == 0)
        {
            target = cur;
            break;
        }
        cur = cur->next;
    }

    if (target == NULL)
    {
        printf("Объект с именем \"%s\" не найден.\n", name);
        return;
    }

    printf("Текущий приоритет объекта \"%s\": %d\n",
        target->inf, target->priority);

    while (new_priority <= 0)
    {
        printf("Введите новый приоритет (целое число > 0): ");
        scanf_s("%d", &new_priority);

        if (new_priority <= 0)
        {
            printf("Ошибка: приоритет не может быть отрицательным или равным нулю. Повторите ввод.\n");
        }
    }

    if (new_priority == target->priority)
    {
        printf("Приоритет не изменился.\n");
        return;
    }

    if (target == head)
    {
        head = target->next;
    }
    else
    {
        cur = head;
        while (cur->next != target)
        {
            cur = cur->next;
        }
        cur->next = target->next;
    }

    target->priority = new_priority;
    target->next = NULL;

    insert_sorted(target);

    printf("Приоритет объекта \"%s\" успешно изменён на %d.\n",
        target->inf, target->priority);
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice = -1;

    while (choice != 0)
    {
        printf("\n--- МЕНЮ ---\n");
        printf("1 - Добавить элемент\n");
        printf("2 - Просмотреть очередь\n");
        printf("3 - Удалить первый элемент\n");
        printf("4 - Изменить приоритет по имени\n");
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

        case 4:
            change_priority();
            break;

        case 0:
            printf("Выход\n");
            break;

        default:
            printf("Неверный выбор\n");
        }
    }

    return 0;
}
