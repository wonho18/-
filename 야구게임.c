#include <stdio.h>
#include <stdlib.h>  
#include <time.h>

int strike = 0, ball = 0;
int* player;
int* answer;
int level, i, k;
int trial = 0;

void initiliaze()
{
    int i, k, num;
    char dup = 'N';

    srand((unsigned)time(NULL));

    player = (int*)malloc(sizeof(int) * level);
    answer = (int*)malloc(sizeof(int) * level);

    for (i = 0; i < level;)
    {
        num = rand() % 9 + 1;

        for (k = 0; k < level; k++)

            if (answer[k] == num)
                dup = 'Y';

        if (dup == 'N')
            answer[i++] = num;
        else
            dup = 'N';
    }
}
void get_input(int* player)
{
    printf("[%dȸ��]\n\n", trial + 1);

    printf("���� %d���� �Է��ϼ���(1 ~ 9������ ���ڸ� �Է� ���ڴ� 1ĭ�� ��� �մϴ�.) :", level);

    for (i = 0; i < level; i++)
    {
        printf("\n%d��° ���� : ", i + 1);
        scanf("%d", &player[i]);
    }

    printf("\n");

    for (int i = 0; i < level; i++)
    {
        for (int k = i + 1; k < level; k++)
        {
            if (player[i] == player[k])
            {
                printf("�ߺ��� ���ڸ� ���� �� �����ϴ�.\n");
                break;
            }
        }
        break;
    }
}

int check(int* player)
{
    for (int i = 0; i < level; i++)
    {
        if ((0 >= player[i]) || (player[i] > 9))
        {
            printf("1���� 9������ �Է¸� �޾ƿ� �� �ֽ��ϴ�.\n");
            return 1;
        }
    }
    return 0;
}

void compare_answer_player(int* answer, int* player)
{
    strike = 0;
    ball = 0;

    for (i = 0; i < level; i++)
    {
        if (answer[i] == player[i])

            strike += 1;

        else
         for (k = 0; k < level; k++)
         {
            if (answer[i] == player[k])
                ball += 1;
         }
    }
}

int print_and_check_result() 
{
    printf("strike: %d  ball %d\n\n", strike, ball);
    if (strike == level)
        return 1;
    else
        return 0;
}

void main()
{
    FILE* rfp;
    FILE* wfp;
    char a,c,d[10];
    int b;
    int w_score = 0, l_score = 0;

    rfp = fopen("c:\\temp\\save.txt", "r");

    printf("���� �ҷ����� / ���ν��� (y/n) : ");
    scanf(" %c", &a);

    if (a == 'y')
    {
        fgets(d, 10, rfp);
        w_score = atoi(d);
        fgets(d, 10 ,rfp);
        l_score = atoi(d);
        printf("%d�� %d��", w_score, l_score);
    }

    else if (a == 'n')
    {
        printf("���Ӱ� ������ �����մϴ�.\n");
    }

    else
    {
        printf("y,n �߿� �ϳ� �����ϼ���.");
    }

    fclose(rfp);
    printf("\n");

    printf("========== �ݰ����ϴ� ������! �߱� ������ �����غ��ڽ��ϴ�. ==========\n");

    while (1)
    {
        printf("========== �߱� ������ �����մϴ�. ==========\n");
        printf("========== ���̵��� ������ �� 9ȸ���� ������ �����մϴ�. ==========\n");
        printf("���̵� ���� -> �� ���� ���ڸ� �����ϳ���? (2-4) �Է� : ");
        scanf("%d", &level);

        initiliaze();

        if (level >= 2 && level <= 4)
        {
            printf("����� ���� ���: ");

            for (i = 0; i < level; i++)
            {
                printf("%d ", answer[i]);
            }

            printf("\n\n");

            for (int ct = 0; ct < 9; ++ct)
            {
                get_input(player);

                compare_answer_player(answer, player);

                check(player);

                trial++;

                int victory = print_and_check_result();

                if (victory)
                {
                    printf("�¸� �߽��ϴ�!\n\n");
                    w_score++;
                    break;
                }

                if (ct == 8)
                {
                    printf("9ȸ�� ������ �Ǿ����ϴ�. You lose!\n");
                    l_score++;
                    break;
                }
            }
        }
        else
            printf("���̵��� 2-4 ���� �Դϴ�.\n\n");

        while (1)
        {
            printf("1.����ϱ�/ 2.�����ϰ� ����ϱ�/ 3.���� �� �����ϱ�/ 4.�������� �ʰ� �����ϱ�\n");
            scanf("%d", &b);

            wfp = fopen("c:\\temp\\save.txt", "w");

            switch (b)
            {
            case 1:
                break;

            case 2:
                wfp;
                fprintf(wfp, "%d\n", w_score);
                fprintf(wfp, "%d", l_score);
                fclose(wfp);
                break;

            case 3:
                wfp;
                fprintf(wfp, "%d\n", w_score);
                fprintf(wfp, "%d", l_score);
                fclose(wfp);
                return 0;

            case 4:
                return 0;

            default:
                printf("1-4������ ���ڸ� �Է��� �� �ֽ��ϴ�.\n");
                continue;
            }
            break;
        }

        fclose(wfp);
        free(player);
        free(answer);
    }
}