#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct student
{
    int num;
    char name[10];
    int grade;
};

struct stunode
{
    struct student *data;
    struct stunode *next;
};

int main()
{
    struct student stu[13] =
        {{2, "Lin", 92}, {3, "Zhang", 87}, {4, "Zhao", 72}, {5, "Ma", 91}, {9, "Zhen", 85}, {11, "Wang", 100}, {12, "Li", 86}, {13, "Xu", 83}, {16, "Mao", 78}, {17, "Hao", 95}, {20, "Lu", 82}, {21, "Song", 76}, {22, "Wu", 88}};
    int i, k;
    struct stunode *head1 = NULL, *head2 = NULL, *head3 = NULL, *p1, *p2, *p3, *q1 = NULL, *q2 = NULL, *q3 = NULL;

    for (i = 0; i < 13; i++)
    {
        k = 10 - (int)stu[i].grade / 10;
        switch (k)
        {
        case 0:
        case 1:
            p1 = (struct stunode *)malloc(sizeof(struct stunode));
            if (p1 == NULL)
            {
                printf("cant get memory");
                exit(1);
            }
            p1->data = &stu[i];
            if (head1 == NULL)
                head1 = p1;
            else
                q1->next = p1;
            q1 = p1;
            break;
        case 2:
            p2 = (struct stunode *)malloc(sizeof(struct stunode));
            if (p2 == NULL)
            {
                printf("cant get memory");
                exit(1);
            }
            p2->data = &stu[i];
            if (head2 == NULL)
                head2 = p2;
            else
                q2->next = p2;
            q2 = p2;
            break;
        case 3:
            p3 = (struct stunode *)malloc(sizeof(struct stunode));
            if (p3 == NULL)
            {
                printf("cant get memory");
                exit(1);
            }
            p3->data = &stu[i];
            if (head3 == NULL)
                head3 = p3;
            else
                q3->next = p3;
            q3 = p3;
            break;
        }
    }

    p1 = head1;
    p2 = head2;
    p3 = head3;

    while (p1 != NULL)
    {
        printf("%d %s %d\n", p1->data->num, p1->data->name, p1->data->grade);
        q1 = p1;
        p1 = p1->next;
        free(q1);
    }
    printf("\n");

    while (p2 != NULL)
    {
        printf("%d %s %d\n", p2->data->num, p2->data->name, p2->data->grade);
        q2 = p2;
        p2 = p2->next;
        free(q2);
    }
    printf("\n");

    while (p3 != NULL)
    {
        printf("%d %s %d\n", p3->data->num, p3->data->name, p3->data->grade);
        q3 = p3;
        p3 = p3->next;
        free(q3);
    }

    printf("sb编译器");

    return 0;
}