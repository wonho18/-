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
    printf("[%d회차]\n\n", trial + 1);

    printf("숫자 %d개를 입력하세요(1 ~ 9까지의 숫자를 입력 숫자는 1칸씩 띄고 합니다.) :", level);

    for (i = 0; i < level; i++)
    {
        printf("\n%d번째 숫자 : ", i + 1);
        scanf("%d", &player[i]);
    }

    printf("\n");

    for (int i = 0; i < level; i++)
    {
        for (int k = i + 1; k < level; k++)
        {
            if (player[i] == player[k])
            {
                printf("중복된 숫자를 받을 수 없습니다.\n");
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
            printf("1에서 9까지의 입력만 받아올 수 있습니다.\n");
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

    printf("게임 불러오기 / 새로시작 (y/n) : ");
    scanf(" %c", &a);

    if (a == 'y')
    {
        fgets(d, 10, rfp);
        w_score = atoi(d);
        fgets(d, 10 ,rfp);
        l_score = atoi(d);
        printf("%d승 %d패", w_score, l_score);
    }

    else if (a == 'n')
    {
        printf("새롭게 게임을 시작합니다.\n");
    }

    else
    {
        printf("y,n 중에 하나 선택하세요.");
    }

    fclose(rfp);
    printf("\n");

    printf("========== 반갑습니다 여러분! 야구 게임을 시작해보겠습니다. ==========\n");

    while (1)
    {
        printf("========== 야구 게임을 시작합니다. ==========\n");
        printf("========== 난이도를 선택한 후 9회까지 게임을 진행합니다. ==========\n");
        printf("난이도 선택 -> 몇 개의 숫자를 생성하나요? (2-4) 입력 : ");
        scanf("%d", &level);

        initiliaze();

        if (level >= 2 && level <= 4)
        {
            printf("참고용 정답 출력: ");

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
                    printf("승리 했습니다!\n\n");
                    w_score++;
                    break;
                }

                if (ct == 8)
                {
                    printf("9회가 마무리 되었습니다. You lose!\n");
                    l_score++;
                    break;
                }
            }
        }
        else
            printf("난이도는 2-4 까지 입니다.\n\n");

        while (1)
        {
            printf("1.계속하기/ 2.저장하고 계속하기/ 3.저장 후 종료하기/ 4.저장하지 않고 종료하기\n");
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
                printf("1-4까지의 숫자만 입력할 수 있습니다.\n");
                continue;
            }
            break;
        }

        fclose(wfp);
        free(player);
        free(answer);
    }
}