#include "stdio.h"
int main(){
    int x = 1;
    x = 0;
    for (;;){
        x=1;
        printf("here\n");
        break;
    }
    printf("nope\n");
    return x;
}
