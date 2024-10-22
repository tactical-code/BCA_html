#include <stdio.h>
#include <conio.h>
#include <graphics.h>
int main(){
    int gd = DETECT, gm;
    int x1,y1,x2,y2,dx,dy,P,x,y;
    initgraph(&gd, &gm, "");
    x1 = 10, y1 = 20, x2 = 20, y2 = 10;
    //printf("Enter start and end point: ");
    //scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    dx = x2-x1;
    dy = y2-y1;
    P=dx-2*y;
    x=x1;
    y=y1;
    while (x!=x2){
        if(P>=0){
            putpixel(x,y,WHITE);
            P = P-2*dx;
        }
        else{
            y=y+1;
            P = P+2*dx-2*dy;
            putpixel(x,y,WHITE);
        }
        x=x+1;
    }
    getch();
    closegraph();
    return 0;
}
