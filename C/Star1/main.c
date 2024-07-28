#include <stdio.h>

int main(){
    int h, i, l_blank, l_star, r_blank, r_star;

    scanf("%d", &h);

    for(i = 1; i <= h; i++){
        for(l_blank = 1; l_blank <= h - i; l_blank++){
            printf(" ");
        }

        for(l_star = 1; l_star <= i; l_star++){
            printf("*");
        }

        for(r_star = 1; r_star <= i - 1; r_star++){
            printf("*");
        }

        for(r_blank = 1; r_blank <= h; r_blank++){
            printf(" ");
        }

        printf("\n");
    }

    return 0;
}