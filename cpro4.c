#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct qna{
    int qna_num;
    int member_num;
    char q[251];
    char a[251];
    int condition;
}QNA;

typedef struct cus{
    int member_num;
    char id[101];
    char pw[101];
    char name[101];
    char add[101];
    int money;
    int condition;
}CUS;


/////////
typedef struct pro{
    int product_num;
    char product[101];
    char category[101];
    int price;
    int product_cond;
}PRO;

/////////

typedef struct his{
    int order_num;
    int product_num;
    int member_num;
    int del_cond;

}HIS;

/////////


int home(void);
int signup(CUS **cus, FILE **fp_cus, int *cus_n);
int login(CUS *cus, int cus_n);
int admin_login(CUS admin);
int searching_items(PRO *pro, int pro_n);
int user_home(char name[101]);
int admin_home(void);
int user_searching_items(int member_n, PRO *pro, int pro_n, CUS **cus, int *cus_n, HIS **his, int *his_n);
int user_info_change(int member_n, CUS **cus, int *cus_n);
int about_money(int member_n, CUS **cus);
int about_buying(int member_n, HIS *his, int his_n, PRO *pro, int pro_n);
int about_delivery(int member_n, HIS *his, int his_n, PRO *pro, int pro_n, CUS *cus);
int quit_member(int member_n, CUS **cus);

int logout(CUS *cus, HIS *his, PRO *pro);
int question(QNA **qna, int *qna_n, int member_n);
int answer(QNA **qna, int *qna_n, int member_n);
//
int members_info(CUS *cus, int cus_n);
int addelete_product(PRO **pro, int *pro_n);
int product_statistic(PRO *pro, int pro_n, HIS *his, int his_n, CUS *cus, int cus_n);
int product_check(PRO *pro, int pro_n, HIS *his, int his_n);
int delivery_change(PRO *pro, int pro_n, HIS *his, int his_n, CUS *cus, int cus_n);
//

int init_struct1(FILE **fp, CUS **);
int init_struct2(FILE **fp, PRO **);
int init_struct3(FILE **fp, HIS **);
int init_struct4(FILE **fp, QNA **);

int init_file1(FILE **fp, CUS **, int cus_n);
int init_file2(FILE **fp, PRO **, int pro_n);
int init_file3(FILE **fp, HIS **, int his_n);
int init_file4(FILE **fp, QNA **, int qna_n);

void buffer_clear(void);

//MMMMMMMAAAAAAAAAIIIIIIIIINNNNNNNNNN

int main(void){

    FILE *fp_cus = fopen("customer.csv", "r");
    FILE *fp_pro = fopen("product.csv", "r");
    FILE *fp_his = fopen("history.csv", "r");
    FILE *fp_qna = fopen("qna.csv", "r");

    CUS *customer = NULL;
    PRO *product = NULL;
    HIS *history = NULL;
    QNA *qna = NULL;

    int member_n = 0;   //The condition of login now;

    //admin_HardCoding
    CUS admin;
    admin.member_num = 1;
    strcpy(admin.id, "admin");
    strcpy(admin.pw, "password");
    strcpy(admin.name, "admin");
    strcpy(admin.add, "0");
    admin.money = 0;
    admin.condition = 0;
    //


    int cus_n;
    int pro_n;
    int his_n;
    int qna_n;


    //int temp;
    int sel, sel2, sel3;
    int i;
    cus_n = init_struct1(&fp_cus, &customer);
    //adm_n = init_struct1(&fp_adm, &admin);
    pro_n = init_struct2(&fp_pro, &product);
    his_n = init_struct3(&fp_his, &history);
    qna_n = init_struct4(&fp_qna, &qna);

    while(1){
        home();
        scanf("%d", &sel);
        switch(sel){
            case 1: //User_login
                member_n = login(customer, cus_n);
                system("clear");
                //////////////////The entrance for User_HOME////////////////////////
                if(member_n > 0){

                    while(1){
                        i = 0;
                        user_home(customer[member_n-1].name);
                        scanf("%d", &sel2);
                        switch(sel2){
                            case 1: //Changing the info of user
                                user_info_change(member_n, &customer, &cus_n);                           
                                break;
                            case 2: //about Account : 계좌
                                about_money(member_n, &customer); 
                                break;
                            case 3: //searching for items
                                user_searching_items(member_n, product, pro_n, &customer, &cus_n, &history, &his_n);
                                break;
                            case 4: //checking the buying
                                about_buying(member_n, history, his_n, product, pro_n);
                                break;
                            case 5: //checking the delivery
                                about_delivery(member_n, history, his_n, product, pro_n, customer);
                                break;
                            case 6:
                                question(&qna, &qna_n, member_n);
                                break;
                            case 7:
                                quit_member(member_n, &customer);
                                i = 1;
                                break;
                            case 8: //Logout and Quit
                                logout(customer, history, product);
                                return 0;
                        }
                        init_file1(&fp_cus, &customer, cus_n);
                        init_file2(&fp_pro, &product, pro_n);
                        init_file3(&fp_his, &history, his_n);
                        init_file4(&fp_qna, &qna, qna_n);
                        if(i == 1) break;
                    }
                }
                break;
            case 2:
                signup(&customer, &fp_cus, &cus_n);
                buffer_clear();
                break;
            case 3:
                searching_items(product, pro_n);           
                break;
            case 4: //Admin_login
                member_n = admin_login(admin);
                printf("member_n: %d\n", member_n);
                system("clear");
                //////////////////The entrance for Admin_HOME//////////////////////
                if(member_n < 0){
                    while(1){
                        admin_home();
                        scanf("%d", &sel2);
                        switch(sel2){
                            case 1:
                                members_info(customer, cus_n);
                                break;
                            case 2:
                                addelete_product(&product, &pro_n);
                                break;
                            case 3:
                                product_statistic(product, pro_n, history, his_n, customer, cus_n);
                                break;
                            case 4:
                                product_statistic(product, pro_n, history, his_n, customer, cus_n);
                                break;
                            case 5:
                                delivery_change(product, pro_n, history, his_n, customer, cus_n);
                            case 6:
                                answer(&qna, &qna_n, member_n);
                                break;
                            case 7:
                                logout(customer, history, product);
                                return 0;
                        }
                        init_file1(&fp_cus, &customer, cus_n);
                        init_file2(&fp_pro, &product, pro_n);
                        init_file3(&fp_his, &history, his_n);
                        init_file4(&fp_qna, &qna, qna_n);
                    }
                }  
                break;
            case 5:
                logout(customer, history, product);
                return 0;

        }

    }


    return 0;
}
//////////////MMMMMMMAAAAAAAAIIIIIIINNNNNNNNNN

int question(QNA **qna, int *qna_n, int member_n){
    char temp[251]; 
    int len;
    int sel;
    int i;

    while(1){
        printf("--------QnA---------\n");
        printf("1. 질문하기\n");
        printf("2. 답변확인\n");
        printf("0. 뒤로가기\n");
        printf("입력: ");
        scanf("%d", &sel);
        buffer_clear();
        if(sel == 0) return 0;

        switch(sel){
            case 1:
                printf("질문을 입력하시오: ");
                fgets(temp, 250, stdin);
                len = strlen(temp);
                temp[len-1] = '\0';
                if(*qna == NULL){
                    *qna = (QNA *)malloc(sizeof(QNA));
                    (*qna)[0].qna_num = 1;
                    (*qna)[0].member_num = member_n;
                    strcpy((*qna)[0].q, temp);
                    strcpy((*qna)[0].a, "X");
                    (*qna)[0].condition = 1;
                    (*qna_n)++;
                }
                else{
                    *qna = (QNA *)realloc(*qna, (++(*qna_n))*sizeof(QNA));
                    (*qna)[*qna_n -1].qna_num = *qna_n;
                    (*qna)[*qna_n -1].member_num = member_n;
                    strcpy((*qna)[*qna_n -1].q, temp);
                    strcpy((*qna)[*qna_n -1].a, "X");
                    (*qna)[*qna_n -1].condition = 1;
                }
                printf("질문이 성공적으로 접수되었습니다!\n");
                break;
            case 2:
                printf("------ 질문확인 ------\n");
                for(i = 0; i<*qna_n; i++){
                    if((*qna)[i].member_num == member_n){
                        printf("질문: \n");
                        printf("%s\n", (*qna)[i].q);
                        printf("답변: \n");
                        if((*qna)[i].condition == 0)
                            printf("%s\n", (*qna)[i].a);
                        else printf("아직 답변이 안 달렸습니다.\n");
                        printf("-------------------\n");
                    }
                }
                break;
        }
       
    }
}

int answer(QNA **qna, int *qna_n, int member_n){
    int i;
    int sel;
    int sel2;
    char temp[251];
    int len;

    while(1){
        printf("----------- QnA ----------\n");
        printf("1. 전  체QnA보기\n");
        printf("2. 미답변QnA보기\n");
        printf("0. 뒤로가기\n");
        scanf("%d", &sel);
        if(sel == 0) return 0;

        switch(sel){
            case 1:
                printf("------ QnAs -------\n");
                for(i = 0; i<(*qna_n); i++){
                    printf("no.%d\n", (*qna)[i].qna_num);
                    printf("질문: \n");
                    printf("%s\n", (*qna)[i].q);
                    printf("답변: \n");
                    if((*qna)[i].condition == 0)
                        printf("%s\n", (*qna)[i].a);
                    else printf("아직 답변을 달지 않았습니다.\n");
                }
                break;
            case 2:
                printf("------ 미답변 QnA ------\n");
                for(i = 0; i<(*qna_n); i++){
                    if((*qna)[i].condition == 1){
                        printf("no.%d\n", (*qna)[i].qna_num);
                        printf("질문: \n");
                        printf("%s\n", (*qna)[i].q);
                        printf("답변: \n");
                        printf("아직 답변을 달지 않았습니다.\n");
                    }
                }
                break;
        }
        while(1){
            printf("답변 번호 입력(0: 나가기): ");
            scanf("%d", &sel2);
            buffer_clear();
            if(sel2 == 0) break;
            else if(((*qna)[sel2-1]).condition == 1){
                printf("답변: \n");
                fgets(temp, 250, stdin);
                len = strlen(temp);
                temp[len-1] = '\0';
                strcpy((*qna)[sel2-1].a, temp);
                (*qna)[sel2-1].condition = 0;
                printf("답변 완료\n");
                
            }

        }

    }
}

int quit_member(int member_n, CUS **cus){

    (*cus)[member_n -1].condition = -1;

    return 0;
}


int logout(CUS *cus, HIS *his, PRO *pro){
    free(cus);
    free(his);
    free(pro);

    return 0;
}

int delivery_change(PRO *pro, int pro_n, HIS *his, int his_n, CUS *cus, int cus_n){

    int i;
    int sel, sel2;

    while(1){
        printf("======= 배송 내역 수정 =======\n");
        for(i = his_n-1; i>=0; i--){
            printf("주문번호 : %d\n", his[i].order_num);
            printf("상품코드: %d\n", pro[(his[i].product_num)-1].product_num);
            printf("상품명: %s\n", pro[(his[i].product_num)-1].product);
            printf("가격: %d\n", pro[(his[i].product_num)-1].price);
            printf("\n회원번호: %d\n", his[i].member_num);
            printf("주문자: %s\n", cus[(his[i].member_num)-1].name);
            printf("주소: %s\n", cus[(his[i].member_num)-1].add);
            printf("배송현황: %d\n", his[i].del_cond); 
            printf("---------------------------------- \n");


        }
        printf("주문번호 입력(뒤로 가기 : 0) : ");
        scanf("%d", &sel);
        if(sel == 0) return 0;

        printf("0: 배송준비 1:배송중, 2:배송완료\n"); 
        printf("입력 : ");
        scanf("%d", &sel2);
        for(i = 0; i<his_n; i++){
            if(his[i].order_num == sel){
                system("clear");
                his[i].del_cond = sel2;


                printf("주문번호 : %d\n", his[i].order_num);
                printf("상품코드: %d\n", pro[(his[i].product_num)-1].product_num);
                printf("상품명: %s\n", pro[(his[i].product_num)-1].product);
                printf("가격: %d\n", pro[(his[i].product_num)-1].price);
                printf("\n회원번호: %d\n", cus[(his[i].member_num)-1].member_num);
                printf("주문자: %s\n", cus[(his[i].member_num)-1].name);
                printf("주소: %s\n", cus[(his[i].member_num)-1].add);
                printf("배송현황: %d\n", his[i].del_cond); 
                printf("---------------------------------- \n");

                printf("---------------배송 현황 수정완료------------- \n");
                break;
            }

        }
        buffer_clear();
        getchar();
    }

}


int product_statistic(PRO *pro, int pro_n, HIS *his, int his_n, CUS *cus, int cus_n){

    int i, j;
    int sel;
    int sum = 0;
    int sum2 = 0;
    int sum3 = 0;

    printf("======== 상품 정보 및 구매 내역 조회 =========\n");
    printf("------- 주문내역서 -------\n");

    for(i = 0; i<his_n; i++){
        for(j = 0; j<pro_n; j++){
            if(pro[j].product_num == his[i].product_num){

                printf("주문번호 : %d\n", his[i].order_num);
                printf("상품코드: %d\n", pro[j].product_num);
                printf("상품명: %s\n", pro[j].product);
                printf("카테고리: %s\n", pro[j].category);
                printf("가격: %d\n", pro[j].price);
                printf("\n회원번호: %d\n", cus[(his[i].member_num)-1].member_num);
                printf("주문자: %s\n", cus[(his[i].member_num)-1].name);
                printf("주소: %s\n", cus[(his[i].member_num)-1].add);

                printf("----------------------------- \n");
            }
        }
    }

    printf("------- 주문 통계 -------\n");

    for(i = 0; i<pro_n; i++){
        sum = 0;
        for(j = 0; j<his_n; j++){
            if(pro[i].product_num == his[j].product_num){
                sum++;
                sum2 += (pro[i].price);
                sum3++;
            }
        }
        printf("상품코드: %d\n", pro[i].product_num);
        printf("상품명: %s\n", pro[i].product);
        printf("카테고리: %s\n", pro[i].category);
        printf("가격: %d\n", pro[i].price);
        printf("상품 상태: %d\n", pro[i].product_cond);
        printf("주문수: %d\n", sum);
        printf("입금액: %d\n", pro[i].price * sum);
        printf("----------------------\n");
    }
    printf(" ======================== \n");
    printf("총 주문수 : %d\n", sum3);
    printf("매출 : %d\n", sum2);
    printf("-- Enter the any key --");
    while(getchar() != '\n');
    getchar();

    return 0;

}


int product_check(PRO *pro, int pro_n, HIS *his, int his_n){


}

int addelete_product(PRO **pro, int *pro_n){

    int sel, sel2, sel3;
    int product_num;
    char product[101];
    char category[101];
    int price;
    int product_cond;
    int i;
    char searching[101];


    while(1){
        printf("-------------------------------\n");

        printf("상품 등록 및 삭제\n");
        printf("1. 상품 등록\n");
        printf("2. 상품 삭제\n");
        printf("3. 상품 수정\n");
        printf("0. 이전 화면으로 돌아가기\n");

        printf("선택: ");
        scanf("%d", &sel);
        if(sel == 0) return 1;
        switch(sel){
            case 1:
                printf("------ 상품 등록 ------\n");

                printf("상품명: ");
                scanf("%s", product);
                printf("카테고리: ");
                scanf("%s", category);
                printf("가격: ");
                scanf("%d", &price);
                printf("제품상태(0:판매 준비, 1:판매 중, -1:판매중단) : ");
                scanf("%d", &product_cond);
                //
                *pro = (PRO *)realloc(*pro, (++(*pro_n))*sizeof(PRO));
                ((*pro)[*pro_n - 1]).product_num = *pro_n;
                strcpy((*pro)[*pro_n -1].product, product);
                strcpy((*pro)[*pro_n -1].category, category);            
                ((*pro)[*pro_n - 1]).price = price;
                ((*pro)[*pro_n - 1]).product_cond = product_cond;
                //
                printf("--- 등록 완료 ---\n");
                break;
            case 2:
                printf("------ 상품 삭제 ------\n");

                while(1){
                    printf("1. 전체 상품 보기\n"); 
                    printf("2. 이름으로 검색하기\n"); 
                    printf("3. 카테고리로 검색하기\n"); 
                    printf("4. 세일 상품 검색하기\n"); 
                    printf("0. 이전 화면으로 돌아가기\n"); 
                    printf("선택: ");
                    scanf("%d", &sel2);
                    if(sel2 == 0) break;
                    switch(sel2){
                        case 1: 
                            for(i = 0; i<*pro_n; i++){
                                printf("상품코드: %d\n", ((*pro)[i]).product_num);
                                printf("상퓸명: %s\n", (*pro)[i].product);
                                printf("카테고리: %s\n", (*pro)[i].category);
                                printf("가격: %d\n", (*pro)[i].price);
                                printf("상품 상태 : %d\n", (*pro)[i].product_cond);
                                printf("------------------------\n");

                            }
                            break;
                        case 2:
                            printf("검색: ");
                            scanf("%s", searching);

                            for(i = 0; i<*pro_n; i++){
                                if(strcmp((*pro)[i].product, searching) == 0){
                                    printf("상품코드: %d\n", ((*pro)[i]).product_num);
                                    printf("상품명: %s\n", (*pro)[i].product);
                                    printf("카테고리: %s\n", (*pro)[i].category);
                                    printf("가격: %d\n", (*pro)[i].price);
                                    printf("상품 상태 : %d\n", (*pro)[i].product_cond);
                                    printf("------------------------\n");
                                    break;
                                }
                            }
                            if(i == *pro_n){
                                printf("--- 일치하는 상품이 없습니다. ---\n");
                                buffer_clear();
                                getchar();
                                continue;
                            }
                            break;
                        case 3:
                            printf("검색: ");
                            scanf("%s", searching);

                            for(i = 0; i< *pro_n; i++){
                                if(strcmp((*pro)[i].category, searching) == 0){
                                    printf("상품코드: %d\n", (*pro)[i].product_num);
                                    printf("상퓸명: %s\n", (*pro)[i].product);
                                    printf("카테고리: %s\n", (*pro)[i].category);
                                    printf("가격: %d\n", (*pro)[i].price);
                                    printf("상품 상태 : %d\n", (*pro)[i].product_cond);
                                    printf("------------------------\n");
                                }
                            }
                            if(i == *pro_n){
                                printf("--- 일치하는 상품이 없습니다. ---\n");
                                buffer_clear();
                                getchar();
                                continue;
                            }
                            break;
                    }
                    printf("삭제할 상품의 상품코드를 입력: ");
                    scanf("%d", &sel3);
                    if(1 <= sel3 && sel3 <= *pro_n){
                        (*pro)[sel3-1].product_cond = -1;
                        printf("--- 삭제 완료 ---------\n");
                    }


                }
                break;
            case 3:
                while(1){
                    printf("------ 상품 수정 ------\n");
                    printf("1. 전체 상품 보기\n"); 
                    printf("2. 이름으로 검색하기\n"); 
                    printf("3. 카테고리로 검색하기\n"); 
                    printf("4. 세일 상품 검색하기\n"); 
                    printf("0. 이전 화면으로 돌아가기\n"); 
                    printf("선택: ");
                    scanf("%d", &sel2);
                    if(sel2 == 0) break;
                    switch(sel2){
                        case 1: 
                            for(i = 0; i<*pro_n; i++){
                                printf("상품코드: %d\n", ((*pro)[i]).product_num);
                                printf("상퓸명: %s\n", (*pro)[i].product);
                                printf("카테고리: %s\n", (*pro)[i].category);
                                printf("가격: %d\n", (*pro)[i].price); 
                                printf("상품 상태 : %d\n", (*pro)[i].product_cond);
                                printf("------------------------\n");

                            }
                            break;
                        case 2:
                            printf("검색: ");
                            scanf("%s", searching);

                            for(i = 0; i<*pro_n; i++){
                                if(strcmp((*pro)[i].product, searching) == 0){
                                    printf("상품코드: %d\n", ((*pro)[i]).product_num);
                                    printf("상퓸명: %s\n", (*pro)[i].product);
                                    printf("카테고리: %s\n", (*pro)[i].category);
                                    printf("가격: %d\n", (*pro)[i].price);
                                    printf("상품 상태 : %d\n", (*pro)[i].product_cond);
                                    printf("------------------------\n");
                                    break;
                                }
                            }
                            if(i == *pro_n){
                                printf("--- 일치하는 상품이 없습니다. ---\n");
                                buffer_clear();
                                getchar();
                                continue;
                            }
                            break;
                        case 3:
                            printf("검색: ");
                            scanf("%s", searching);

                            for(i = 0; i< *pro_n; i++){
                                if(strcmp((*pro)[i].category, searching) == 0){
                                    printf("상품코드: %d\n", (*pro)[i].product_num);
                                    printf("상퓸명: %s\n", (*pro)[i].product);
                                    printf("카테고리: %s\n", (*pro)[i].category);
                                    printf("가격: %d\n", (*pro)[i].price);
                                    printf("상품 상태 : %d\n", (*pro)[i].product_cond);
                                    printf("------------------------\n");
                                }
                            }
                            if(i == *pro_n){
                                printf("--- 일치하는 상품이 없습니다. ---\n");
                                buffer_clear();
                                getchar();
                                continue;
                            }
                            break;
                    }
                    printf("수정할 상품의 상품코드를 입력: ");
                    scanf("%d", &sel3);
                    printf("상품코드: %d\n", (*pro)[sel3-1].product_num);
                    printf("상퓸명: %s\n", (*pro)[sel3-1].product);
                    printf("카테고리: %s\n", (*pro)[sel3-1].category);
                    printf("가격: %d\n", (*pro)[sel3-1].price);
                    printf("상품 상태 : %d\n", (*pro)[sel3-1].product_cond);
                    printf("--- 아래에 수정 사항을 입력하시오-----------\n");


                    printf("상품명: ");
                    scanf("%s", product);
                    printf("카테고리: ");
                    scanf("%s", category);
                    printf("가격: ");
                    scanf("%d", &price);
                    printf("제품상태(0:판매 준비, 1:판매 중, -1:판매중단) : ");
                    scanf("%d", &product_cond);

                    ((*pro)[sel3 - 1]).product_num = *pro_n;
                    strcpy((*pro)[sel3 -1].product, product);
                    strcpy((*pro)[sel3 -1].category, category);            
                    ((*pro)[sel3 - 1]).price = price;
                    ((*pro)[sel3 - 1]).product_cond = product_cond;

                    printf("--- 수정 완료 --------------\n");
                    printf("상품코드: %d\n", (*pro)[sel3-1].product_num);
                    printf("상퓸명: %s\n", (*pro)[sel3-1].product);
                    printf("카테고리: %s\n", (*pro)[sel3-1].category);
                    printf("가격: %d\n", (*pro)[sel3-1].price);
                    printf("상품 상태 : %d\n", (*pro)[sel3-1].product_cond);
                    printf("---------------------------------------\n");

                }
                break;
            case 0: return 1;
        }
    }
}


int members_info(CUS *cus, int cus_n){

    int i, sel;
    printf("회원 정보 조회-------------\n");
    for(i = 0; i<cus_n; i++){
        printf("회원번호: %d\n", cus[i].member_num);
        printf("아이디  : %s\n", cus[i].id);
        printf("비밀번호: %s\n", cus[i].pw);
        printf("이름    : %s\n", cus[i].name);
        printf("주소    : %s\n", cus[i].add);
        printf("잔액    : %d\n", cus[i].money);
        printf("상태    : %d :", cus[i].condition);
        if(cus[i].condition == 1) printf("일반회원\n");
        else if(cus[i].condition == -1) printf("회원탈퇴\n");
        printf("-----------------------\n");
    }
    printf("아무키나 누르면 뒤로 갑니다 ");
    buffer_clear();
    getchar();

    printf("-------------------------------\n");
    return 0;
}

int about_buying(int member_n, HIS *his, int his_n, PRO *pro, int pro_n){
    int i;

    printf("구매 내역 조회-------------\n");
    for(i = 0; i<his_n; i++){
        if(member_n == his[i].member_num){
            printf("상품명: %s\n", pro[his[i].product_num-1].product);
            printf("카테고리: %s\n", pro[his[i].product_num-1].category);
            printf("가격: %d\n", pro[his[i].product_num-1].price);
            printf("------------------------\n");
        }
    }
    buffer_clear();
    getchar();
    return 0;
}

int about_delivery(int member_n, HIS *his, int his_n, PRO *pro, int pro_n, CUS *cus){
    int i;

    printf("배송 내역 조회-------------\n");
    for(i = 0; i<his_n; i++){
        if(member_n == his[i].member_num){
            printf("상품명: %s\n", pro[his[i].product_num].product);
            printf("주문자: %s\n", cus[member_n-1].name);
            printf("주소: %s\n", cus[member_n-1].add);
            if(his[i].del_cond == 0) printf("배송상태: 배송 준비중\n");
            else if(his[i].del_cond == 1) printf("배송상태: 배송중\n");
            else if(his[i].del_cond == 2) printf("배송상태: 배송완료\n");
            printf("------------------------\n");

        }
    }
    buffer_clear();
    getchar();
    return 0;
}


int about_money(int member_n, CUS **cus){
    int sel;
    int money;

    while(1){
        printf("-------가상계좌 입금 및 출금-------\n");
        printf("내 가상계좌 잔액: %d원\n", (*cus)[member_n -1].money);
        printf("--------------------------\n");
        printf("1. 입금하기\n");
        printf("2. 출금하기\n");
        printf("3. 이전 페이지로 돌아가기\n");
        printf("선택: ");
        scanf("%d", &sel);
        if(sel == 1){
            printf("입금 금액 입력: ");
            scanf("%d", &money);
            if(money>=0){
                (*cus)[member_n-1].money += money; 
                printf("입금이 완료되었습니다.\n");
                printf("현재 잔액: %d\n", (*cus)[member_n-1].money);
            }
            else{
                printf("입금액 오류\n");
            }
            buffer_clear();
            getchar();
        }
        else if(sel == 2){
            printf("출금 금액 입력: ");
            scanf("%d", &money);
            if(money>=0 && money <= (*cus)[member_n -1].money){
                (*cus)[member_n-1].money -= money; 
                printf("출금이 완료되었습니다.\n");
                printf("현재 잔액: %d\n", (*cus)[member_n-1].money);
            }
            else{
                printf("출금액 오류\n");
            }
            buffer_clear(); 
            getchar();
        }
        else if(sel == 3) return 0;
    }
    return 0;

}

int user_info_change(int member_n, CUS **cus, int *cus_n){
    char name[101];
    char pw1[101];
    char pw2[101];
    char add[201];

    char temp[601];
    int i;
    int len;

    printf("------------------------\n");
    while(1){
        printf("회원정보 변경\n\n");

        printf("이름: ");
        scanf("%s", name);
        printf("비밀번호: ");
        scanf("%s", pw1);
        printf("비밀번호 확인: ");
        scanf("%s", pw2);
        printf("주소: ");
        //scanf("%s", add);
        buffer_clear();
        fgets(add, 200, stdin);
        len = strlen(add);
        add[len-1] = '\0';

        if(strcmp(pw1, pw2) != 0){
            printf("--- 비밀번호가 일치하기 않습니다. ---\n");
            continue;
        }
        else break;
    }
    strcpy((*cus)[member_n-1].name, name);
    strcpy((*cus)[member_n-1].pw, pw1);
    strcpy((*cus)[member_n-1].add, add);

    printf("%s\n", (*cus)[member_n -1].id);
    printf("%s\n", (*cus)[member_n -1].add);
    //
    printf("회원정보가 성공적으로 수정되었습니다.");
    getchar();

    return 20;

}

int user_searching_items(int member_n, PRO *pro, int pro_n, CUS **cus, int *cus_n, HIS **his, int *his_n){

    int i;
    int sel, sel2, sel3, sel4, sel5, sel6;
    char searching[101];
    int needs = 0;
    int inmoney = 0;
    int len;

    while(1){
        printf("\n---------- 상품 검색 하기 ----------\n");
        printf("1. 이름으로 검색하기\n");
        printf("2. 카테고리로 검색하기\n");
        printf("3. 세일 상품 검색하기\n");
        printf("0. 이전 화면을 돌아가기\n");

        printf("선택: ");
        scanf("%d", &sel);
        if(sel == 0) return 0;
        printf("검색: ");
        while(getchar() != '\n');
        fgets(searching, 100, stdin);
        len = strlen(searching);
        searching[len-1] = '\0';
        printf("\n");
        switch(sel){
            case 1:
                for(i = 0; i<pro_n; i++){
                    if(strcmp(pro[i].product, searching) == 0){
                        printf("상품코드: %d\n", (pro[i]).product_num);
                        printf("상퓸명: %s\n", pro[i].product);
                        printf("카테고리: %s\n", pro[i].category);
                        printf("가격: %d\n", pro[i].price);
                        printf("------------------------\n");
                        break;
                    }
                }
                if(i == pro_n){
                    printf("--- 일치하는 상품이 없습니다. ---\n");
                    getchar();
                    continue;
                }
                break;
            case 2:
                for(i = 0; i<pro_n; i++){
                    if(strcmp(pro[i].category, searching) == 0){
                        printf("상품코드: %d\n", pro[i].product_num);
                        printf("상퓸명: %s\n", pro[i].product);
                        printf("카테고리: %s\n", pro[i].category);
                        printf("가격: %d\n", pro[i].price);
                        printf("------------------------\n");
                    }
                }
                if(i > pro_n){
                    printf("--- 일치하는 상품이 없습니다. ---\n");
                }
                getchar();
                break;
            case 3:

            case 0:
                return 0;
        }
        printf("상품코드를 입력하시오. ( 0 : 뒤로 가기) --- \n");
        scanf("%d", &sel2);
        if(sel2 == 0) continue;
        else if(sel2 <= pro_n){
            printf("상품코드: %d\n", pro[i].product_num);
            printf("상퓸명: %s\n", pro[i].product);
            printf("카테고리: %s\n", pro[i].category);
            printf("가격: %d\n", pro[i].price);
            printf("------------------------\n"); 
        }
        printf("1. 구매하기\n");
        printf("2. 이전 페이지로 돌아가기\n");
        printf("선택: ");
        scanf("%d", &sel3);
        if(sel3 == 1){
            printf("내 가상계좌 잔액: %d원\n", (*cus)[member_n-1].money);
            printf("상품 가격: %d원\n", pro[sel2-1].price);
            needs = ((*cus)[member_n -1].money - pro[sel2-1].price) > 0 ? 0 : (pro[sel2-1].price - (*cus)[member_n -1].money);
            printf("필요금액: %d\n", needs);
            printf("------------------------\n"); 
            printf("1. 가상계좌 입금하고 구매하기\n");
            printf("2. 이전 페이지로 돌아가기\n");

            printf("선택: ");
            scanf("%d", &sel4);
            if(sel4 == 1){
                printf("가상계좌 입금 및 출금\n");
                printf("내 가상계좌 잔액: %d원\n", (*cus)[member_n -1].money);
                printf("필요 금액: %d원\n", needs);
                printf("------------------------\n"); 
                printf("1. 입금하기\n");
                printf("2. 이전 페이지로 돌아가기\n");
                printf("선택: \n");
                scanf("%d", &sel5);
                if(sel5 == 1){
                    printf("입금금액 입력: ");
                    scanf("%d", &inmoney);
                    (*cus)[member_n-1].money+= inmoney;
                    printf("입금이 완료되었습니다.\n");
                    printf("현재 잔액: %d원\n", (*cus)[member_n-1].money);
                    printf("------------------------\n"); 
                    printf("상품을 구매하시겠습니까?\n");
                    printf("1. 구매\n");
                    printf("2. 이전 페이지로 돌아가기\n");
                    printf("선택: ");
                    scanf("%d", &sel6);
                    if(sel6 == 1){
                        (*cus)[member_n -1].money -= pro[sel2-1].price;
                        *his = (HIS*)realloc(*his, sizeof(HIS)* (++*his_n));
                        (*his)[*his_n -1].order_num = *his_n;
                        (*his)[*his_n -1].product_num = sel2;
                        (*his)[*his_n -1].member_num = member_n;
                        (*his)[*his_n -1].del_cond = 0;

                        printf("--- 구매가 완료 되었습니다 ---\n");
                        printf("거래후 잔액 : %d원\n", (*cus)[member_n-1].money);
                        getchar();
                        continue;
                    }
                    else if(sel6 == 2) continue;
                }
                else if(sel5 == 2) continue;

            }
            else if(sel4 == 2) continue;
        }
        else if(sel3 == 2) continue;


    }

    return 0;


}

int user_home(char name[101]){

    system("clear");
    printf("%s님, SG-MALL에 오신 것을 환영합니다.\n", name);

    printf("1. 회원 정보 수정\n");
    printf("2. 가상계좌 입금 및 출금\n");
    printf("3. 상품 검색\n");
    printf("4. 구매 내역 조회\n");
    printf("5. 배송 내역 조회\n");
    printf("6. QnA\n");
    printf("7. 회원 탈퇴\n");
    printf("8. 로그아웃 및 종료\n");

    printf("선택: ");
}

int admin_home(void){

    system("clear");
    printf("SG-MALL 관리자 페이지\n");

    printf("1. 회원 정보 조회\n");
    printf("2. 상품 등록 및 수정 삭제\n");
    printf("3. 상품 조회 및 통계 보기\n");
    printf("4. 구매 내역 및 통계 보기\n");
    printf("5. 배송 내역 수정\n");
    printf("6. QnA\n");
    printf("7. 로그아웃 및 종료\n");

    printf("선택: ");
}

int searching_items(PRO *pro, int pro_n){

    int i;
    int sel;
    char searching[101];
    int len;

    while(1){
        printf("\n상품 검색 하기\n");
        printf("1. 이름으로 검색하기\n");
        printf("2. 카테고리로 검색하기\n");
        printf("3. 세일 상품 검색하기\n");
        printf("0. 이전 화면을 돌아가기\n");

        printf("선택: ");
        scanf("%d", &sel);
        if(sel == 0) return 0;
        printf("검색: ");

        while(getchar() != '\n');
        fgets(searching, 100, stdin);
        len = strlen(searching);
        searching[len-1] = '\0';
        printf("\n");

        switch(sel){
            case 1:
                for(i = 0; i<pro_n; i++){
                    if(strcmp(pro[i].product, searching) == 0){
                        printf("상품코드: %d\n", (pro[i]).product_num);
                        printf("상퓸명: %s\n", pro[i].product);
                        printf("카테고리: %s\n", pro[i].category);
                        printf("가격: %d\n", pro[i].price);
                        printf("------------------------\n");
                        break;
                    }
                }
                if(i == pro_n){
                    printf("--- 일치하는 상품이 없습니다. ---\n");
                }
                getchar();
                break;
            case 2:
                for(i = 0; i<pro_n; i++){
                    if(strcmp(pro[i].category, searching) == 0){
                        printf("상품코드: %d\n", pro[i].product_num);
                        printf("상퓸명: %s\n", pro[i].product);
                        printf("카테고리: %s\n", pro[i].category);
                        printf("가격: %d\n", pro[i].price);
                        printf("------------------------\n");
                    }
                }
                if(i > pro_n){
                    printf("--- 일치하는 상품이 없습니다. ---\n");
                }
                getchar();
                break;
            case 3:

            case 0:
                return 0;
        }
    }

    return 0;
}

//MMMMMMMAAAAAAAAAIIIIIIIIINNNNNNNNNN
int admin_login(CUS admin){

    char id[101];
    char pw[101];

    int i;
    int j =0;

    while(1){
        printf("회원 로그인 페이지\n");
        printf("아이디: ");
        scanf("%s", id);
        printf("비밀번호: ");
        scanf("%s", pw);

        if(strcmp((admin.id), id) == 0 && strcmp((admin.pw), pw) == 0){
            printf("관리자 계정 로그인 성공\n");
            return -1;
        }
        else if((++j) == 3){
            printf("관리자 아이디 또는 비밀번호가 일치하지 않습니다.\n");
            printf("확인 후 다시 로그인을 시도하여 주세요.\n");
            return 0;
        }
    }

}


int home(void){

    system("clear");
    printf("SG-MALL에 오신 것을 환영합니다.\n");
    printf("1. 회원 로그인\n");
    printf("2. 회원 가입\n");
    printf("3. 상품 검색\n");
    printf("4. 관리자 로그인\n");
    printf("5. 종료\n");

    printf("선택: ");

}

int signup(CUS **cus, FILE **fp_cus, int *cus_n){
    char name[101];
    char id[101];
    char pw1[101];
    char pw2[101];
    char add[201];

    char temp[601];
    int i;
    int len;

    while(1){
        printf("회원가입 페이지\n");

        printf("이름: ");
        scanf("%s", name);
        printf("아이디: ");
        scanf("%s", id);
        printf("비밀번호: ");
        scanf("%s", pw1);
        printf("비밀번호 확인: ");
        scanf("%s", pw2);
        printf("주소: ");
        scanf("%s", add);
        //buffer_clear();
        //fgets(add, 200, stdin);

        if(strcmp(pw1, pw2) != 0){
            printf("--- 비밀번호가 일치하기 않습니다. ---\n");
            continue;
        }
        for(i = 0; i<*cus_n; i++){
            if(strcmp((*cus)[i].id, id) == 0){
                printf("--- 아이디가 중복됩니다. ---\n");  
                break;
            }
        }
        if(strcmp((*cus)[i].id, id) == 0) continue;
        break;
    }

    *fp_cus = fopen("customer.csv", "a");
    fprintf(*fp_cus, "%d,%s,%s,%s,%s,%d,%d", *cus_n+1, id, pw1, name, add, 0, 1);
    fprintf(*fp_cus, "\n");

    fclose(*fp_cus);
    *cus_n = init_struct1(fp_cus, cus);
    printf("Cus_n : %d\n", *cus_n);
    return 20;
}

int login(CUS *cus, int cus_n){

    char id[101];
    char pw[101];

    int i;
    int j = 0;

    while(1){
        printf("회원 로그인 페이지\n");
        printf("아이디: ");
        scanf("%s", id);
        printf("비밀번호: ");
        scanf("%s", pw);

        for(i = 0; i<cus_n; i++){
            if(strcmp(cus[i].id, id) == 0){
                if(strcmp(cus[i].pw, pw) == 0 && cus[i].condition != -1){
                    printf("회원 로그인 성공\n");
                    return i+1;

                }
            }
        }

        printf("회원 아이디 또는 비밀번호가 일치하지 않습니다.\n");
        if((++j) == 3){
            printf("확인 후 다시 로그인을 시도하여 주세요.\n");
            return 0;
        }
    }

}

int init_struct1(FILE **fp, CUS** cus){

    char temp[601];
    int i;

    *fp = fopen("customer.csv", "r");

    fgets(temp, 600, *fp);
    i = 0;
    while(1){
        if(fgets(temp, 600, *fp) == NULL) break;
        else{    
            if(*cus == NULL){
                *cus = (CUS*)malloc(1*sizeof(CUS));

            }
            else{
                *cus = (CUS*)realloc(*cus, (i+1)*sizeof(CUS));
            }
            (*cus)[i].member_num = atoi(strtok(temp, ","));
            strcpy((*cus)[i].id, strtok(NULL, ","));
            strcpy((*cus)[i].pw, strtok(NULL, ","));
            strcpy((*cus)[i].name, strtok(NULL, ","));
            strcpy((*cus)[i].add, strtok(NULL, ","));
            (*cus)[i].money = atoi(strtok(NULL, ","));
            (*cus)[i].condition = atoi(strtok(NULL, ","));
            i++;
        }
    }
    fclose(*fp);
    return i;
}

int init_struct2(FILE **fp, PRO** pro){ //ERROR IS HERE
    char temp[601];
    int i;

    *fp = fopen("product.csv", "r");
    fgets(temp, 600, *fp);
    i = 0;
    while(1){
        if(fgets(temp, 600, *fp) == NULL) break;
        else{    
            if(*pro == NULL){
                *pro = (PRO*)malloc(1 * sizeof(PRO));

            }
            else{
                *pro = (PRO*)realloc(*pro, (i+1)*sizeof(PRO));
            }
            (*pro)[i].product_num = atoi(strtok(temp, ","));
            strcpy((*pro)[i].product, strtok(NULL, ","));
            strcpy((*pro)[i].category, strtok(NULL, ","));
            (*pro)[i].price = atoi(strtok(NULL, ","));
            (*pro)[i].product_cond = atoi(strtok(NULL, ","));
            i++;
        }
    }
    fclose(*fp);
    return i;

}

int init_struct3(FILE **fp, HIS** his){

    char temp[601];
    int i;

    *fp = fopen("history.csv", "r");
    fgets(temp, 600, *fp);
    i = 0;
    while(1){
        if(fgets(temp, 600, *fp) == NULL) break;
        else{    
            if(*his == NULL){
                *his = (HIS*)malloc(1*sizeof(HIS));

            }
            else{
                *his = (HIS*)realloc(*his, (i+1)*sizeof(HIS));
            }
            (*his)[i].order_num = atoi(strtok(temp, ","));
            (*his)[i].product_num = atoi(strtok(NULL, ","));
            (*his)[i].member_num = atoi(strtok(NULL, ","));
            (*his)[i].del_cond = atoi(strtok(NULL, ","));
            i++;
        }
    }
    fclose(*fp);
    return i;

}

int init_struct4(FILE **fp, QNA **qna){

    char temp[601];
    int i;

    *fp = fopen("qna.csv", "r");
    fgets(temp, 600, *fp);

    i = 0;
    while(1){
        if(fgets(temp, 600, *fp) == NULL) break;
        else{
            if(*qna == NULL){
                *qna = (QNA *)malloc(1*sizeof(QNA));
            }
            else{
                *qna = (QNA *)realloc(*qna, (i+1)*sizeof(QNA));
            }
            (*qna)[i].qna_num = atoi(strtok(temp, ","));
            (*qna)[i].member_num = atoi(strtok(NULL, ","));
            strcpy((*qna)[i].q, strtok(NULL, ","));
            strcpy((*qna)[i].a, strtok(NULL, ","));
            (*qna)[i].condition = atoi(strtok(NULL, ","));
            i++;
        }
    }
    fclose(*fp);
    return i;

}

int init_file1(FILE **fp, CUS **cus, int cus_n){

    int i;

    *fp = fopen("customer.csv", "w");
    fprintf(*fp, "회원번호,아이디,비밀번호,이름,주소,잔액,상태\n");
    for(i = 0; i<cus_n; i++){
        fprintf(*fp, "%d,%s,%s,%s,", (*cus)[i].member_num, (*cus)[i].id, (*cus)[i].pw, (*cus)[i].name);
        fputs((*cus)[i].add, *fp);
        fprintf(*fp, ",%d,%d\n", (*cus)[i].money, (*cus)[i].condition);
    }
    fclose(*fp);
}

int init_file2(FILE **fp, PRO **pro, int pro_n){

    int i;
    *fp = fopen("product.csv", "w");
    fprintf(*fp, "상품번호,상품명,카테고리,가격,상태\n");
    for(i = 0; i<pro_n; i++){
        fprintf(*fp, "%d,", (*pro)[i].product_num);
        fputs((*pro)[i].product, *fp);
        fprintf(*fp, ",%s,%d,%d\n",(*pro)[i].category, (*pro)[i].price, (*pro)[i].product_cond);

    }
    fclose(*fp);
}

int init_file3(FILE **fp, HIS **his, int his_n){

    int i;
    *fp = fopen("history.csv", "w");
    fprintf(*fp, "주문번호,상품번호,회원번호,배송현황\n");
    for(i = 0; i<his_n; i++){
        fprintf(*fp, "%d,%d,%d,%d\n", (*his)[i].order_num, (*his)[i].product_num, (*his)[i].member_num, (*his)[i].del_cond);
    }
    fclose(*fp);
}

int init_file4(FILE **fp, QNA **qna, int qna_n){

    int i;
    *fp = fopen("qna.csv", "w");
    fprintf(*fp, "질문번호,회원번호,질문,답변,상태\n");
    for(i = 0; i<qna_n; i++){
        fprintf(*fp, "%d,%d,%s,%s,%d\n", (*qna)[i].qna_num,(*qna)[i].member_num, (*qna)[i].q, (*qna)[i].a, (*qna)[i].condition);
    }
    fclose(*fp);
}

void buffer_clear(void){
    while(getchar() != '\n');
    return;
}

