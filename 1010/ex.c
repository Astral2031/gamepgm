#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


void maingame(int low_set, int high_set, int start_set){
    short det_mul, det_minus, temp, f_suggest, sent, e_sent, e_f_suggest;
    short numlist[11] = {0,0,0,0,0,0,0,0,0,0,0}; short enemy_mumlist[11] = {1,1,1,1,1,1,1,1,1,1,1};
    short now = start_set;
    short minus_stack = 3; short enemy_minus_stack = 3;
    short mul_stack = 3; short enemy_mul_stack = 3;
    short first = 0;
    short gaming = 1;           //승패 판결
    short winner = 0;           //승자 판결

    short plus_w, minus_w, sol_w, mul_w, zero_w, user_op_w, normal_w;      //AI판단 가중치
    short p_dist, m_dist, ab_c;                                       //AI판단 기반
    short en_minus, en_mul, en_answer;
    short enemy_used = 0;

    while(gaming){
        system("cls");
        printf("\n\t\t현재 숫자 : %hd\n\n 남은 \'-\' 횟수 : %hd,  남은 \'*\' 횟수 : %hd,   우선순위 : %hd\n\n  ",now, minus_stack, mul_stack, first);
        
        for(int i = 0; i < 11; i++){
            if(numlist[i] == 0){
                printf("%d ", i);
            }
            else{
                printf("  ");
            }
        }

        while(1){                           //유저 숫자 제시
            det_mul = 1;
            char num_sugg[5];
            det_minus = 1;
            en_minus = 1;
            en_mul = 1;
            temp = 0;
            printf("\n\n숫자를 제시해주세요 : ");
            if(scanf("%s",num_sugg) != 1){              //c언어 너무 싫다 진짜
                getchar();
                printf("\n입력이 올바르지 않습니다.\n");
                getchar();
                continue;
            }

            if(num_sugg[0] == '-'){         //잔여횟수 체크
                if(minus_stack == 0){
                    printf("\n-의 잔여횟수가 남아있지 않습니다.\n");
                    getchar();
                    continue;
                }
                det_minus = -1;
            }

            temp = atoi(num_sugg);          //특수문자 지우기

            if(temp < 0){                   //음수 판별
                temp = -1 * temp;
            }

            if(temp > 10){                  //예외처리
                printf("\n입력받은 숫자의 범위가 올바르지 않습니다.\n");
                getchar();
                continue;
            }

            if(num_sugg[0] == '*' || num_sugg[min(det_minus, 0) * (-1) + 2] == '*' || num_sugg[min(det_minus, 0) * (-1) + 2] == '2'){       //잔여 횟수 체크
                if(mul_stack == 0){
                    printf("\n*2의 잔여횟수가 남아있지 않습니다.\n");
                    getchar();
                    continue;
                }
                det_mul = 2;
            }

            if(temp == 0){          //기호만 쓸 것인지 체크
                if(det_mul == 2 || det_minus == -1){
                    mul_stack -= det_mul - 1;
                    minus_stack += min(det_minus, 0);
                    f_suggest = 0;
                    sent = -1;
                    break;
                }
                else if(numlist[0]){
                    printf("\n이미 사용한 숫자입니다\n");
                    getchar();
                    continue;
                }
            }

            if(numlist[temp]){      //사용한 숫자인지 체크
                printf("\n이미 사용한 숫자입니다");
                getchar();
                continue;
            }

            f_suggest = temp * det_minus * det_mul;         //결산
            mul_stack -= det_mul - 1;
            minus_stack += min(det_minus, 0);
            det_mul = 1;
            det_minus = 1;
            numlist[temp] = 1;
            sent = temp;
            break;
        }

        en_minus = 1;
        en_mul = 1;
        p_dist = high_set - now;                            //AI판단 시작
        m_dist = now - low_set;
        ab_c = 0;
        int temp = enemy_minus_stack + enemy_mul_stack;

        for(int i = 0; i < (p_dist + m_dist)/2; i++){
            if(enemy_mumlist[i]){
                ab_c++;
            }
        }

        srand(time(NULL));

        if(rand() % (ab_c + temp) < ab_c){                  //AI행동 판단
            srand(time(NULL));
            if(enemy_mumlist[0] && rand() % 3 == 0){        //0만 내기
                e_sent = 0;
                enemy_mumlist[0] = 1; 
                e_f_suggest = 0;
            }
            else{
                ab_c = 0;                                       //숫자
                minus_w = 2;
                plus_w = 2;
                if(p_dist < m_dist){
                    minus_w++;
                }
                else{
                    plus_w++;
                }

                srand(time(NULL));
                if(rand() % (minus_w + plus_w) < minus_w){      //음수 판별
                    en_minus = -1;
                    enemy_minus_stack -= 1;
                    temp = m_dist;
                }
                else{
                    temp = p_dist;
                }

                ab_c = 0;
                for(int i = 0; i < temp; i++){
                    if(enemy_mumlist[i]){
                        ab_c++;
                    }
                }

                srand(time(NULL));
                ab_c = rand() % ab_c;

                for(int i = 0; i < temp; i++){
                    if(enemy_mumlist[i]){
                        if(ab_c == 0){
                            e_sent = i;
                            enemy_mumlist[i] = 0;
                            break;
                        }
                        ab_c--;
                    }
                }

                e_f_suggest = en_minus * e_sent;
                en_minus = 1;
            }
            
        }
        else{
            en_answer = 0;                                  //기호만
            e_sent = -1;
            short ran;
            minus_w = enemy_minus_stack;
            mul_w = enemy_mul_stack;
            temp = min(minus_w, mul_w);
            
            if(m_dist < p_dist){
                minus_w++;
            }

            srand(time(NULL));
            ran = rand() % (minus_w + mul_w + temp);

            if(ran < minus_w){
                en_minus = -1;
                enemy_minus_stack -= 1;
            }
            else if(ran < minus_w + mul_w){
                en_mul = 2;
                enemy_mul_stack -= 1;
            }
            else{
                en_minus = -1;
                enemy_minus_stack -= 1;
                en_mul = 2;
                enemy_mul_stack -= 1;
            }

        }

        if(first == 0){                                     //중립상황시 우선순위 설정
            if(sent > e_sent){
                first = 1;
            }
            else if(sent < e_sent){
                first = -1;
            }
            else{
                short temp1 = f_suggest * en_mul * en_minus;
                short temp2 = e_f_suggest * det_minus * det_mul;
                if(temp1 > temp2){
                    first = 1;
                }
                else if(temp2 > temp1){
                    first = -1;
                }
                else{
                    first = 0;
                    printf("\n결과값이 같기 때문에 이번 턴은 현재 값이 변화하지 않습니다\n");
                    getchar();
                }
            }
        }

        system("cls");

        if(first == 1){                                      //우선순위 1 최종 판단
            now += f_suggest * en_mul * en_minus;           //유저
            printf("현재 우선순위 : 당신\n");
            printf("\n\t더해지는 값 = %hd * %hd * %hd\n\t현재값 : %hd\n", f_suggest, en_mul, en_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = -1;
                printf("\n\t당신의 패배입니다");
                getchar();
                break;
            }
            getchar();

            now += e_f_suggest * det_minus * det_mul;
            printf("\n\t더해지는 값 = %hd * %hd * %hd\n\t현재값 : %hd", e_f_suggest, det_mul, det_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = 1;
                printf("\n\t당신의 승리입니다");
                getchar();
                break;
            }
        }
        else if(first == -1){                               //우선순위 2 최종 판단
            printf("현재 우선순위 : 상대\n");

            now += e_f_suggest * det_minus * det_mul;
            printf("\n\t더해지는 값 = %hd * %hd * %hd\n\t현재값 : %hd\n", e_f_suggest, det_mul, det_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = 1;
                printf("\n\t당신의 승리입니다");
                getchar();
                break;
            }
            getchar();

            now += f_suggest * en_mul * en_minus;
            printf("\n\t더해지는 값 = %hd * %hd * %hd\n\t현재값 : %hd\n", f_suggest, en_mul, en_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = -1;
                printf("\n\t당신의 패배입니다");
                getchar();
                break;
            }
        }

        if(sent > e_sent){
            first = 1;
        }
        else if(sent < e_sent){
            first = -1;
        }

        getchar();
    }
}

void game_manual(){
    char enter;
    printf("이 게임은 AI와 자신이 현재 값에 0 ~ 10까지의 숫자중 하나를 더하거나 빼서\n 자신이 낸 숫자로 인해 게임의 최댓값이나 최솟값에 도달하게 되면 패배하는 게임입니다\n");
    printf("한번 낸 숫자는 소모되며 숫자를 모두 소모했을 시 모든 숫자와 기호가 재보급 됩니다\n");
    printf("게임은 턴제로 진행되며 1턴에 AI와 유저가 동시에 숫자를 내게 되며 우선순위가 높은 쪽 먼저 판정이 일어나게 됩니다\n");
    printf("우선순위 전 턴에 상대방보다 더 높은 숫자를 낸 쪽이 높은 우선순위를 가지게 됩니다\n");
    printf("게임시작 직후나 전턴에 서로 제시한 숫자의 값이 같다면 이번턴에 낸 숫자가 더 높은 쪽이 우선권을 가지게 됩니다\n");
    printf("우연히 우선권을 결정할 수 없는 상황이라면 랜덤으로 우선권이 주어집니다\n");
    printf("게임에는 특수한 기호가 있으며 이 기호들을 통하여 상대방을 방해하거나 자신에게 유리한 상황을 만들 수 있습니다. 또한 기호는 각각 3번씩 쓸 수 있습니다\n");
    printf("기호는 각각 -, *2가 있으며 자신이 낼 숫자에 적용할 수 있습니다(ex: \"-8\")\n");
    printf("만약 자신이 낼 숫자를 적지 않고 기호만 적는다면 이 기호의 효과는 상대방이 낸 숫자에 적용됩니다\n");
    printf("이번턴에 양쪽이 기호를 동시에 냈다면 아무일도 일어나지 않고 현제 우선권을 유지한 체 다음 턴으로 넘어가게 됩니다\n");
    printf("만약 한쪽이 기호만 내고 다른 한쪽이 \"0\"을 냈다면 0을 낸 쪽은 그 숫자를 소모하지 않습니다\n");
    printf("기호는 동시 사용이 가능합니다 (ex: -8*2, -*2)\n\n");
    getchar();
}

short title(){
    short det;
    system("cls");
    printf("게임 모드를 선택해주세요\n\n");

    printf("1.short(0 ~ 20)\t2.medium(0 ~ 40)\t3.long(0 ~ 60)\t4.custom\t 5.도움말\n\n");

    short select;
    scanf("%hd", &select);
    getchar();          //입력버퍼는 시123발

    switch (select)
    {
    case 1:
        det = 0;
        maingame(0,20, 10);
        break;
    case 2:
        det = 0;
        maingame(0,40, 20);
        break;
    case 3:
        det = 0;
        maingame(0,60, 30);
        break;
    case 4:
        det = 0;
        short temp = 1;
        short mx, mn, st;
        while(temp){
            system("cls");
            printf("게임의 최소치와 최대치, 그리고 시작점을 순서대로 작성해주세요\n(최소치와 최대치의 절대값은 100을 넘을 수 없습니다)\n");
            if(scanf("%hd %hd %hd",&mn, &mx, &st) == 3){
                getchar();
                if(mn < -100 || mx > 100 || mn >= mx || st <= mn || st >= mx){
                    printf("범위 설정이 잘 못 되었습니다. 다시 한번 설정해주세요");
                    getchar();
                }
                else{
                    temp = 0;
                }
            }
            else{
                getchar();
                printf("값의 입력이 올바르지 않습니다. 다시 입력해주세요");
                getchar();
            }
        }
        maingame(mn, mx, st);
        break;
    case 5:
        det = 1;
        game_manual();
        break;
    default:
        printf("\n\n선택 범위가 올바르지 않습니다 다시 선택해주세요");
        getchar();
        det = 1;
        break;
    }

    return det;
}

int main(){
    int title_bool = 1;
    while(title_bool){
        title_bool = title();
    }
    return 0;
}