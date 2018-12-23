#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void buffer_clear(void);

int home(void);
int signup(CUS **cus, FILE **fp_cus, int *cus_n);
int login(CUS *cus, int cus_n);
int admin_login(CUS admin);
int searching_items(PRO *pro, int pro_n);
int user_home(char name[101]);
int admin_home(void);


int init_struct1(FILE **fp, CUS **);
int init_struct2(FILE **fp, PRO **);
int init_struct3(FILE **fp, HIS **);

//MMMMMMMAAAAAAAAAIIIIIIIIINNNNNNNNNN

int main(void){
    
    FILE *fp_cus = fopen("customer.csv", "r");
    FILE *fp_pro = fopen("product.csv", "r");
    FILE *fp_his = fopen("history.csv", "r");

    CUS *customer = NULL;
    PRO *product = NULL;
    HIS *history = NULL;

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
    
    //int temp;
    int sel, sel2, sel3;

    cus_n = init_struct1(&fp_cus, &customer);
    //adm_n = init_struct1(&fp_adm, &admin);
    pro_n = init_struct2(&fp_pro, &product);
    //his_n = init_struct3(&fp_his, &history);

    while(1){
        home();
        scanf("%d", &sel);
        switch(sel){
            case 1: //User_login
                member_n = login(customer, cus_n);
                printf("member_n: %d\n", member_n);
                //////////////////The entrance for User_HOME////////////////////////
                if(member_n > 0){
                    
                    while(1){
                    user_home(customer[member_n-1].name);
                    scanf("%d", &sel2);
                        switch(sel2){
                            case 1: //Changing the info of user
                                
                            case 2: //about Account : 계좌
                                
                            case 3: //searching for items
                                while(1){
                                                          
                                }
                            case 4: //checking the buying

                            case 5: //checking the delivery

                            case 6: //Logout and Quit
                                break;
                        }
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
                //////////////////The entrance for Admin_HOME//////////////////////
                if(member_n > 0){
                    while(1){
                    admin_home();
                    scanf("%d", &sel2);
                        switch(sel2){
                            case 1:
                                             
                            case 2:

                            case 3:

                            case 4:

                            case 5:

                            case 6:
                                break;
                        }
                    }
                }  
                break;
            case 5:
                return 0;

        }
        
    }


    return 0;
}

int user_home(char name[101]){
    
    printf("%s님, SG-MALL에 오신 것을 환영합니다.\n", name);
    
    printf("1. 회원 정보 수정\n");
    printf("2. 가상계좌 입금 및 출금\n");
    printf("3. 상품 검색\n");
    printf("4. 구매 내역 조회\n");
    printf("5. 배송 내역 조회\n");
    printf("6. 로그아웃 및 종료\n");
    
    printf("선택: ");
}

int admin_home(void){
    
    printf("SG-MALL 관리자 페이지\n");
    
    printf("1. 회원 정보 조회\n");
    printf("2. 상품 등록 및 삭제\n");
    printf("1. 상품 정보 수정\n");
    printf("1. 상품 조회 및 통계 보기\n");
    printf("1. 구매 내역 및 통계 보기\n");
    printf("1. 배송 내역 수정\n");
    printf("1. 로그아웃 및 종료\n");
    
    printf("선택: ");
}

int searching_items(PRO *pro, int pro_n){
    
    int i;
    int sel;
    char searching[101];

    while(1){
        printf("상품 검색 하기\n");
        printf("1. 이름으로 검색하기\n");
        printf("2. 카테고리로 검색하기\n");
        printf("3. 세일 상품 검색하기\n");
        printf("0. 이전 화면을 돌아가기\n");

        printf("선택: ");
        scanf("%d", &sel);
        printf("검색: ");
        scanf("%s", searching);
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
                while(getchar() != '\n');
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
                if(i == pro_n){
                    printf("--- 일치하는 상품이 없습니다. ---\n");
                }
                while(getchar() != '\n');
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
                if(strcmp(cus[i].pw, pw) == 0){
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
            if(his == NULL){
                *his = (HIS*)malloc(1*sizeof(HIS));
                
            }
            else{
                *his = (HIS*)realloc(*his, i*sizeof(HIS));
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

void buffer_clear(void){
    while(getchar() != '\n');
    return;
}
