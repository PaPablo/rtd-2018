#include <stdio.h>

char *character_generator(){
    static char c = 32;
    if (c>126){
        c=32;
    }
    char *buf = malloc(sizeof(char) * 2);
    snprintf(buf, sizeof(buf),"%c",c++);
    return buf;
}

void main(){
    for(int a=0;a<100;a++){
        char *s = character_generator();
        printf("%c",s[0]);
    }
}
