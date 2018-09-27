#include <stdio.h>
#include <stdlib.h>
struct node
{
    int x, y;
    struct node *next;
};
void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
struct node *insert(struct node *start, int i, int j)
{
    struct node *n = (struct node *)malloc(sizeof(struct node)), *ptr = start;
    n->x = i;
    n->y = j;
    n->next = NULL;
    if (start == NULL)
    {
        start = n;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = n;
    }
    return start;
}
struct node *delete (struct node *start)
{
    struct node *ptr = start;
    start = start->next;
    free(ptr);
    return start;
}
void create_maze(char a[][11])
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 11; j++)
        {
            if (i == 0 || i == 8)
            {
                a[i][j] = '-';
            }
            else if (j == 0 || j == 10)
            {
                a[i][j] = '|';
            }
            else
            {
                a[i][j] = ' ';
            }
            if ((i == 6 && (j == 1 || j == 2 || j == 3)) || (j == 4 && (i == 1 || i == 2)) || (i == 3 && (j == 3 || j == 4 || j == 5)) || (i == 5 && (j == 9 || j == 8 || j == 7)))
            {
                a[i][j] = '1';
            }
        }
    }
    a[1][1] = 'S';
    a[7][1] = 'D';
}
void print(char a[][11])
{
    int i, j;
    printf("\n");
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 11; j++)
        {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}
void run_queue(char a[][11])
{
    struct node *start = NULL;
    int i = 1, j = 1;
    start = insert(start, i, j);
    //print(a);
    while (a[i][j] != 'D')
    {
        a[i][j] = '@';
        //print(a);
        if (a[i - 1][j] == 'D' || a[i + 1][j] == 'D' || a[i][j - 1] == 'D' || a[i][j + 1] == 'D')
        {
            return;
        }
        if (a[i - 1][j] != '-' && a[i - 1][j] != '|' && a[i - 1][j] != '1' && a[i - 1][j] != '@' && a[i - 1][j] != 'D') //up
        {
            insert(start, i - 1, j);
            a[i - 1][j] = '#';
        }
        if (a[i + 1][j] != '-' && a[i + 1][j] != '|' && a[i + 1][j] != '1' && a[i + 1][j] != '@' && a[i + 1][j] != 'D') //down
        {
            insert(start, i + 1, j);
            a[i + 1][j] = '#';
        }
        if (a[i][j - 1] != '-' && a[i][j - 1] != '|' && a[i][j - 1] != '1' && a[i][j - 1] != '@' && a[i][j - 1] != 'D') //left
        {
            insert(start, i, j - 1);
            a[i][j - 1] = '#';
        }
        if (a[i][j + 1] != '-' && a[i][j + 1] != '|' && a[i][j + 1] != '1' && a[i][j + 1] != '@' && a[i][j + 1] != 'D') //right
        {
            insert(start, i, j + 1);
            a[i][j + 1] = '#';
        }
        start = delete (start);
        i = start->x;
        j = start->y;
    }
}
void copy(char a[][11], char b[][11], char c[][11])
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 11; j++)
        {
            b[i][j] = a[i][j];
            c[i][j] = a[i][j];
        }
    }
}
struct node *pop(struct node *start)
{
    struct node *s = start;
    while (s->next->next != NULL)
    {
        s = s->next;
    }
    struct node *ptr = s->next;
    s->next = NULL;
    free(ptr);
    return start;
}
struct node *top(struct node *start)
{
    while (start->next != NULL)
    {
        start = start->next;
    }
    return start;
}
void printll(struct node *start)
{
    while (start != NULL)
    {
        printf("%d %d\t", start->x, start->y);
        start = start->next;
    }
}
void run_stack(char a[][11])
{
    struct node *start = NULL, *t;
    int i = 1, j = 1, c = 0;
    start = insert(start, i, j);
    //print(a);
    while (a[i][j] != 'D')
    {
        a[i][j] = '@';
        //print(a);
        c++;
        if (a[i - 1][j] == 'D' || a[i + 1][j] == 'D' || a[i][j - 1] == 'D' || a[i][j + 1] == 'D')
        {
            return;
        }
        if (a[i][j + 1] != '-' && a[i][j + 1] != '|' && a[i][j + 1] != '1' && a[i][j + 1] != 'D' && a[i][j + 1] != '@')
        {
            insert(start, i, j + 1);
            a[i][j + 1] = '#';
        }
        if (a[i + 1][j] != '-' && a[i + 1][j] != '|' && a[i + 1][j] != '1' && a[i + 1][j] != 'D' && a[i + 1][j] != '@')
        {
            insert(start, i + 1, j);
            a[i + 1][j] = '#';
        }
        if (a[i - 1][j] != '-' && a[i - 1][j] != '|' && a[i - 1][j] != '1' && a[i - 1][j] != 'D' && a[i - 1][j] != '@')
        {
            insert(start, i - 1, j);
            a[i - 1][j] = '#';
        }
        if (a[i][j - 1] != '-' && a[i][j - 1] != '|' && a[i][j - 1] != '1' && a[i][j - 1] != 'D' && a[i][j - 1] != '@')
        {
            insert(start, i, j - 1);
            a[i][j - 1] = '#';
        }

        //printll(start);
        t = top(start);
        if (t->x == i && t->y == j)
        {
            start = pop(start);
            t = top(start);
        }
        //start=pop(start);
        i = t->x;
        j = t->y;
        //printf("*%d %d*", i, j);
    }
}
void load(char a[][11], char aq[][11], char as[][11])
{
    int f = 1, x = 1, y = 1, i = 1, j = 1, p = 1;
    char a1[9][11], a2[9][11];
    copy(a, a1, a2);
    static int level = 1, score = 0, lifes = 3;
    char move;
    a[1][1] = 'M';
    if (level == 1)
    {
        printf("\n\nBoard with man->(M) enter the moves and take the man to D or press q to exit\n");
        print(a);
        //scanf("%c", &move);
    }
    while (f && move != 'q')
    {
        if (lifes == 0)
        {
            printf("\nGame Over\n");
            break;
        }
        switch (move)
        {
        case 'w':
            x = i - 1;
            y = j;
            break;
        case 's':
            x = i + 1;
            y = j;
            break;
        case 'a':
            x = i;
            y = j - 1;
            break;
        case 'd':
            x = i;
            y = j + 1;
            break;
        }
        if (a[x][y] == 'D')
        {
            if (level == 1)
            {
                system("clear");
                break;
            }
            else
            {
                printf("\nCongratulations\n");
                break;
            }
        }
        if (a[x][y] == '1' || a[x][y] == '-' || a[x][y] == '|')
        {
            lifes--;
            score = 0;
            a[i][j] = 'M';
            x = i;
            y = j;
            p = 0;
        }
        else
        {
            p = 1;
            a[x][y] = 'M';
        }
        if (p == 1)
        {
            if (a[x][y] == '*')
            {
                score--;
            }
            if (aq[i][j] == '@' && level == 1)
            {
                score++;
            }
            if (aq[i][j] == ' ' && level == 1)
            {
                lifes--;
                score = 0;
                a[i][j] = 'M';
                x = i;
                y = j;
                p = 0;
            }
            if (as[x][y] == '@' && level == 2)
            {
                score++;
            }
            if (as[x][y] == ' ' && level == 2)
            {
                lifes--;
                score = 0;
                a[i][j] = 'M';
                x = i;
                y = j;
                p = 0;
            }
        }
        printf("LEVEL = %d\nLIVES LEFT = %d\nSCORE = %d", level, lifes, score);
        print(a);
        scanf("%c", &move);
        clean_stdin();
        system("clear");
    }
    if (level == 1 && lifes > 0 && move != 'q')
    {
        level++;
        load(a1, aq, as);
    }
}
int main()
{
    char a[9][11], aq[9][11], as[9][11];
    create_maze(a);
    printf("\t\t\t\tMAZE GAME\n\n");
    printf("Use A for backward, S for downward, D for forward and W for upward directions respectively\n\n");
    printf("Main board\n");
    print(a);
    copy(a, aq, as);
    run_queue(aq);
    printf("\n\nBackend board for level 1\n");
    print(aq); //for level 1
    run_stack(as);
    printf("\n\nBackend board for level 2\n");
    print(as); //for level 2;
    load(a, aq, as);
    return 0;
}
