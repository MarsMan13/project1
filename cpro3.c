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


int home(void);
int signup(CUS **cus, FILE **fp_cus, int *cus_n);
int login(CUS *cus, int cus_n);

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
    
    int cus_n;
    int pro_n;
    int his_n;
    //int temp;
    int sel;
    int member_n = 0;

    cus_n = init_struct1(&fp_cus, &customer);
    //pro_n = init_struct2(&fp_pro, &product);
    //his_n = init_struct3(&fp_his, &history);
    

    while(1){
        home();
        scanf("%d", &sel);
        switch(sel){
            case 1:
                member_n = login(customer, cus_n);
                printf("member_n: %d\n", member_n);
                break;
            case 2:
                signup(&customer, &fp_cus, &cus_n);
                break;
            case 3:
                break;
            case 4:
                //member_n = admin_login();
                break;
            case 5:
                return 0;

        }

    }


    return 0;
}

//MMMMMMMAAAAAAAAAIIIIIIIIINNNNNNNNNN

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
    fprintf(*fp_cus, "%d,%s,%s,%s,%s,%d,%d", *cus_n, id, pw1, name, add, 0, 1);
    fprintf(*fp_cus, "\n");
    
    fclose(*fp_cus);
    *cus_n = init_struct1(fp_cus, cus);

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
                    printf("Login Success\n");
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
            if(pro == NULL){
                *pro = (PRO*)malloc(1 * sizeof(PRO));
                
            }
            else{
                *pro = (PRO*)realloc(*pro, i*sizeof(PRO));
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
