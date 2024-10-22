#include <stdio.h>
#include<conio.h>
#include <graphics.h>

int main(){
    int gd = DETECT, gm;
    int x1, x2, y1, y2, x, y, s, i, xi, yi, dx, dy;
    initgraph(&gd, &gm, "");

    x1 = 10, y1 = 20, x2 = 20, y2 = 10;
    //printf("Enter start and end point: ");
    //scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    dx = x2-x1;
    dy = y2-y1;
    x=x1;
    y=y1;
    i=0;
    if (dx >= dy){
        s=dx;
    }
    else{
        s=dy;
    }
    xi=dx/s;
    yi=dy/s;
    while(i!=s){
        putpixel(x,y,WHITE);
        x=x+xi;
        y=y+yi;
        i=i+1;
    }
    getch();
    closegraph();
    return 0;
}
