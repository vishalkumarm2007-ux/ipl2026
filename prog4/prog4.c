#include<stdio.h>

struct Status{
unsigned int power:1;
unsigned int mode:2;
unsigned int error:1;
unsigned int value:4;
};

int main(){
struct Status s;
s.power=1;
s.mode=2;
s.error=0;
s.value=9;

printf("Power:%u\n",s.power);
printf("Mode:%u\n",s.mode);
printf("Error:%u\n",s.error);
printf("Value:%u\n",s.value);
printf("Size=%lu bytes\n",sizeof(s));

return 0;
}