#include <graphics.h>
#include <stdio.h>
#include <conio.h>  // for getch()

int main() {
    int gd = DETECT, gm;

    // Initialize graphics mode and the graphics driver
    initgraph(&gd, &gm, "");

    // Set color and draw a circle at (250, 200) with radius 100
    setcolor(WHITE);
    circle(250, 200, 100);

    // Hold the screen until a key is pressed
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
