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
    short gaming = 1;           //���� �ǰ�
    short winner = 0;           //���� �ǰ�

    short plus_w, minus_w, sol_w, mul_w, zero_w, user_op_w, normal_w;      //AI�Ǵ� ����ġ
    short p_dist, m_dist, ab_c;                                       //AI�Ǵ� ���
    short en_minus, en_mul, en_answer;
    short enemy_used = 0;

    while(gaming){
        system("cls");
        printf("\n\t\t���� ���� : %hd\n\n ���� \'-\' Ƚ�� : %hd,  ���� \'*\' Ƚ�� : %hd,   �켱���� : %hd\n\n  ",now, minus_stack, mul_stack, first);
        
        for(int i = 0; i < 11; i++){
            if(numlist[i] == 0){
                printf("%d ", i);
            }
            else{
                printf("  ");
            }
        }

        while(1){                           //���� ���� ����
            det_mul = 1;
            char num_sugg[5];
            det_minus = 1;
            en_minus = 1;
            en_mul = 1;
            temp = 0;
            printf("\n\n���ڸ� �������ּ��� : ");
            if(scanf("%s",num_sugg) != 1){              //c��� �ʹ� �ȴ� ��¥
                getchar();
                printf("\n�Է��� �ùٸ��� �ʽ��ϴ�.\n");
                getchar();
                continue;
            }

            if(num_sugg[0] == '-'){         //�ܿ�Ƚ�� üũ
                if(minus_stack == 0){
                    printf("\n-�� �ܿ�Ƚ���� �������� �ʽ��ϴ�.\n");
                    getchar();
                    continue;
                }
                det_minus = -1;
            }

            temp = atoi(num_sugg);          //Ư������ �����

            if(temp < 0){                   //���� �Ǻ�
                temp = -1 * temp;
            }

            if(temp > 10){                  //����ó��
                printf("\n�Է¹��� ������ ������ �ùٸ��� �ʽ��ϴ�.\n");
                getchar();
                continue;
            }

            if(num_sugg[0] == '*' || num_sugg[min(det_minus, 0) * (-1) + 2] == '*' || num_sugg[min(det_minus, 0) * (-1) + 2] == '2'){       //�ܿ� Ƚ�� üũ
                if(mul_stack == 0){
                    printf("\n*2�� �ܿ�Ƚ���� �������� �ʽ��ϴ�.\n");
                    getchar();
                    continue;
                }
                det_mul = 2;
            }

            if(temp == 0){          //��ȣ�� �� ������ üũ
                if(det_mul == 2 || det_minus == -1){
                    mul_stack -= det_mul - 1;
                    minus_stack += min(det_minus, 0);
                    f_suggest = 0;
                    sent = -1;
                    break;
                }
                else if(numlist[0]){
                    printf("\n�̹� ����� �����Դϴ�\n");
                    getchar();
                    continue;
                }
            }

            if(numlist[temp]){      //����� �������� üũ
                printf("\n�̹� ����� �����Դϴ�");
                getchar();
                continue;
            }

            f_suggest = temp * det_minus * det_mul;         //���
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
        p_dist = high_set - now;                            //AI�Ǵ� ����
        m_dist = now - low_set;
        ab_c = 0;
        int temp = enemy_minus_stack + enemy_mul_stack;

        for(int i = 0; i < (p_dist + m_dist)/2; i++){
            if(enemy_mumlist[i]){
                ab_c++;
            }
        }

        srand(time(NULL));

        if(rand() % (ab_c + temp) < ab_c){                  //AI�ൿ �Ǵ�
            srand(time(NULL));
            if(enemy_mumlist[0] && rand() % 3 == 0){        //0�� ����
                e_sent = 0;
                enemy_mumlist[0] = 1; 
                e_f_suggest = 0;
            }
            else{
                ab_c = 0;                                       //����
                minus_w = 2;
                plus_w = 2;
                if(p_dist < m_dist){
                    minus_w++;
                }
                else{
                    plus_w++;
                }

                srand(time(NULL));
                if(rand() % (minus_w + plus_w) < minus_w){      //���� �Ǻ�
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
            en_answer = 0;                                  //��ȣ��
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

        if(first == 0){                                     //�߸���Ȳ�� �켱���� ����
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
                    printf("\n������� ���� ������ �̹� ���� ���� ���� ��ȭ���� �ʽ��ϴ�\n");
                    getchar();
                }
            }
        }

        system("cls");

        if(first == 1){                                      //�켱���� 1 ���� �Ǵ�
            now += f_suggest * en_mul * en_minus;           //����
            printf("���� �켱���� : ���\n");
            printf("\n\t�������� �� = %hd * %hd * %hd\n\t���簪 : %hd\n", f_suggest, en_mul, en_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = -1;
                printf("\n\t����� �й��Դϴ�");
                getchar();
                break;
            }
            getchar();

            now += e_f_suggest * det_minus * det_mul;
            printf("\n\t�������� �� = %hd * %hd * %hd\n\t���簪 : %hd", e_f_suggest, det_mul, det_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = 1;
                printf("\n\t����� �¸��Դϴ�");
                getchar();
                break;
            }
        }
        else if(first == -1){                               //�켱���� 2 ���� �Ǵ�
            printf("���� �켱���� : ���\n");

            now += e_f_suggest * det_minus * det_mul;
            printf("\n\t�������� �� = %hd * %hd * %hd\n\t���簪 : %hd\n", e_f_suggest, det_mul, det_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = 1;
                printf("\n\t����� �¸��Դϴ�");
                getchar();
                break;
            }
            getchar();

            now += f_suggest * en_mul * en_minus;
            printf("\n\t�������� �� = %hd * %hd * %hd\n\t���簪 : %hd\n", f_suggest, en_mul, en_minus, now);
            if(now <= low_set || now >= high_set){
                gaming = 0;
                winner = -1;
                printf("\n\t����� �й��Դϴ�");
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
    printf("�� ������ AI�� �ڽ��� ���� ���� 0 ~ 10������ ������ �ϳ��� ���ϰų� ����\n �ڽ��� �� ���ڷ� ���� ������ �ִ��̳� �ּڰ��� �����ϰ� �Ǹ� �й��ϴ� �����Դϴ�\n");
    printf("�ѹ� �� ���ڴ� �Ҹ�Ǹ� ���ڸ� ��� �Ҹ����� �� ��� ���ڿ� ��ȣ�� �纸�� �˴ϴ�\n");
    printf("������ ������ ����Ǹ� 1�Ͽ� AI�� ������ ���ÿ� ���ڸ� ���� �Ǹ� �켱������ ���� �� ���� ������ �Ͼ�� �˴ϴ�\n");
    printf("�켱���� �� �Ͽ� ���溸�� �� ���� ���ڸ� �� ���� ���� �켱������ ������ �˴ϴ�\n");
    printf("���ӽ��� ���ĳ� ���Ͽ� ���� ������ ������ ���� ���ٸ� �̹��Ͽ� �� ���ڰ� �� ���� ���� �켱���� ������ �˴ϴ�\n");
    printf("�쿬�� �켱���� ������ �� ���� ��Ȳ�̶�� �������� �켱���� �־����ϴ�\n");
    printf("���ӿ��� Ư���� ��ȣ�� ������ �� ��ȣ���� ���Ͽ� ������ �����ϰų� �ڽſ��� ������ ��Ȳ�� ���� �� �ֽ��ϴ�. ���� ��ȣ�� ���� 3���� �� �� �ֽ��ϴ�\n");
    printf("��ȣ�� ���� -, *2�� ������ �ڽ��� �� ���ڿ� ������ �� �ֽ��ϴ�(ex: \"-8\")\n");
    printf("���� �ڽ��� �� ���ڸ� ���� �ʰ� ��ȣ�� ���´ٸ� �� ��ȣ�� ȿ���� ������ �� ���ڿ� ����˴ϴ�\n");
    printf("�̹��Ͽ� ������ ��ȣ�� ���ÿ� �´ٸ� �ƹ��ϵ� �Ͼ�� �ʰ� ���� �켱���� ������ ü ���� ������ �Ѿ�� �˴ϴ�\n");
    printf("���� ������ ��ȣ�� ���� �ٸ� ������ \"0\"�� �´ٸ� 0�� �� ���� �� ���ڸ� �Ҹ����� �ʽ��ϴ�\n");
    printf("��ȣ�� ���� ����� �����մϴ� (ex: -8*2, -*2)\n\n");
    getchar();
}

short title(){
    short det;
    system("cls");
    printf("���� ��带 �������ּ���\n\n");

    printf("1.short(0 ~ 20)\t2.medium(0 ~ 40)\t3.long(0 ~ 60)\t4.custom\t 5.����\n\n");

    short select;
    scanf("%hd", &select);
    getchar();          //�Է¹��۴� ��123��

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
            printf("������ �ּ�ġ�� �ִ�ġ, �׸��� �������� ������� �ۼ����ּ���\n(�ּ�ġ�� �ִ�ġ�� ���밪�� 100�� ���� �� �����ϴ�)\n");
            if(scanf("%hd %hd %hd",&mn, &mx, &st) == 3){
                getchar();
                if(mn < -100 || mx > 100 || mn >= mx || st <= mn || st >= mx){
                    printf("���� ������ �� �� �Ǿ����ϴ�. �ٽ� �ѹ� �������ּ���");
                    getchar();
                }
                else{
                    temp = 0;
                }
            }
            else{
                getchar();
                printf("���� �Է��� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ���");
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
        printf("\n\n���� ������ �ùٸ��� �ʽ��ϴ� �ٽ� �������ּ���");
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