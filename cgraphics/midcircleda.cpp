#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void setpixel(int x, int y){
    putpixel(200 + x, 200 + y, WHITE);  // First quadrant
    putpixel(200 - x, 200 + y, WHITE);  // Second quadrant
    putpixel(200 + x, 200 - y, WHITE);  // Fourth quadrant
    putpixel(200 - x, 200 - y, WHITE);  // Third quadrant
    putpixel(200 + y, 200 + x, WHITE);  // Reflected point (y, x)
    putpixel(200 - y, 200 + x, WHITE);
    putpixel(200 + y, 200 - x, WHITE);
    putpixel(200 - y, 200 - x, WHITE);
}

int main(){
    int gd = DETECT, gm;
    int x,y,r,p;
    initgraph(&gd, &gm, "");
    r = 100;
    x=0;
    y=r;
    p=1-r;
    while(x<=y){
        setpixel(x,y);
        x++;
        if(p>0){
            y=y-1;
            p=p+2*(x-y)+5;
        }
        else{
            p=p+2*x-3;
        }
    }
    getch();
    closegraph();
    return 0;
}
