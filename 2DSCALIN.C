#include<stdio.h>
#include<graphics.h>

struct x{
	int x1;
	int y1;
}
ReadTriangle(struct x p[3]){
	printf("Enter three point: ");
	scanf("%d%d%d%d%d%d", &p[0].x1, &p[0].y1, &p[1].x1, &p[1].y1, &p[2].x1, &p[2].y1);

}
DrawTriangle(struct x p[3]){
	line(p[0].x1,p[0].y1,p[1].x1,p[1].y1);
	line(p[1].x1,p[1].y1,p[2].x1,p[2].y1);
	line(p[2].x1,p[2].y1,p[0].x1,p[0].y1);
}
Scaling(struct x p[3], int sx, int sy){
	p[0].x1=p[0].x1*sx;
	p[0].y1=p[0].y1*sy;
	p[1].x1=p[1].x1*sx;
	p[1].y1=p[1].y1*sy;
	p[2].x1=p[2].x1*sx;
	p[2].y1=p[2].y1*sy;
}
main(){
	int d=1, m=1, tx, ty;
	struct x p[3];
	initgraph(&d, &m, "C:/TURBOC3/BGI");
	ReadTriangle(p);
	DrawTriangle(p);
	printf("Enter tx and ty: ");
	scanf("%d%d", &tx, &ty);
	Scaling(p, tx, ty);
	DrawTriangle(p);
	getch();
}