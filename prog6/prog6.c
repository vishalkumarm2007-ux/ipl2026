#include<stdio.h>
#include<math.h>

#define ROWS 25
#define COLS 50

struct circle{
int x;
int y;
int radius;
};

void clear_buffer(char buffer[ROWS][COLS]);
void draw_circle(char buffer[ROWS][COLS],struct circle c);
void print_buffer(char buffer[ROWS][COLS]);
void set_pixel(char buffer[ROWS][COLS],int x,int y);

int main(){

char buffer[ROWS][COLS];

struct circle c;

c.x=25;
c.y=12;
c.radius=10;

clear_buffer(buffer);

draw_circle(buffer,c);

print_buffer(buffer);

return 0;
}

void clear_buffer(char buffer[ROWS][COLS]){

int i,j;

for(i=0;i<ROWS;i++){
for(j=0;j<COLS;j++){
buffer[i][j]=' ';
}
}
}

void set_pixel(char buffer[ROWS][COLS],int x,int y){

if(x>=0&&x<COLS&&y>=0&&y<ROWS){
buffer[y][x]='*';
}
}

void draw_circle(char buffer[ROWS][COLS],struct circle c){

int x,y;

for(y=0;y<ROWS;y++){
for(x=0;x<COLS;x++){

int dx=x-c.x;
int dy=y-c.y;

float distance=sqrt(dx*dx+dy*dy);

if(distance>=c.radius-0.5&&distance<=c.radius+0.5){
set_pixel(buffer,x,y);
}
}
}
}

void print_buffer(char buffer[ROWS][COLS]){

int i,j;

for(i=0;i<ROWS;i++){
for(j=0;j<COLS;j++){
printf("%c",buffer[i][j]);
}
printf("\n");
}
}