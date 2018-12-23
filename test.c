#include <stdio.h>


int main(void){

    char str[100];

    FILE *fp = fopen("output.csv", "w");
    
    int num = 1;
    char id[100] = "cds06126";
    char pw[100] = "xx1245";
    char name[100] = "choiGun";
    char add[100] = "Seoul Korea";

    int i;

    for(i = 0; i<3; i++){
        fprintf(fp, "%d,%s,%s,%s,%s\n", num, id, pw, name, add);
    }
    


    return 0;
} 
