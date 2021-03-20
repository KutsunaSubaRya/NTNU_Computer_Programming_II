//
// Created by jw910731 on 3/20/21.
//

#include "mixed.h"

#include <stdio.h>

int main(){
    sMixedNumber mix[2];
    int32_t a, b, c;
    for(int i = 0 ; i < 2 ; ++i){
        int ret = 0;
        do{
            if(ret) printf("Error!\n");
            printf("Input Numbers: ");
            scanf("%d%d%d", &a, &b, &c);
            ret = mixed_set(mix+i, a, b, c);
        } while (ret);
    }
    puts("R1");
    mixed_print(mix[0]);
    putchar('\n');
    printf("[%d, %d]\n", mix[0].a, mix[0].b);
    puts("R2");
    mixed_print(mix[1]);
    putchar('\n');
    printf("[%d, %d]\n", mix[1].a, mix[1].b);
    sMixedNumber tmp;
    puts("Add:");
    mixed_add(&tmp, mix[0], mix[1]);
    mixed_print(tmp);
    putchar('\n');
    printf("[%d, %d]\n", tmp.a, tmp.b);
    puts("Sub:");
    mixed_sub(&tmp, mix[0], mix[1]);
    mixed_print(tmp);
    putchar('\n');
    printf("[%d, %d]\n", tmp.a, tmp.b);
    puts("Mul:");
    mixed_mul(&tmp, mix[0], mix[1]);
    mixed_print(tmp);
    putchar('\n');
    printf("[%d, %d]\n", tmp.a, tmp.b);
    puts("Div:");
    mixed_div(&tmp, mix[0], mix[1]);
    mixed_print(tmp);
    putchar('\n');
    printf("[%d, %d]\n", tmp.a, tmp.b);
    return 0;
}