#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int Xmax, Ymax, X0, X1, Y0, Y1;
float Rmax = 0.0;

// Function to draw the graph of f(x) = sin^2(x/2) + sqrt(x)
void drawf(int pixelToX, int pixelToY) {
    int startXcoord = X0 + (int)(1.5 * pixelToX); // Start point at 1.5*pi
    int endXcoord = X0 + (int)(15 * pixelToX);    // End point at 15*pi
    int N = endXcoord - startXcoord;              // Number of pixels for the graph
    double dx2 = (15 * M_PI - 1.5 * M_PI) / N;    // Step change in x
    double x = 1.5 * M_PI;                        // Initial value of x (1.5*pi)
    int i;
    float R;

    // Loop to plot the graph
    for (i = 0; x <= 15 * M_PI; x += dx2, i++) {
        // Calculate the function value
        R = (pow(sin(x / 2), 2.0) + sqrt(x));

        // Update the maximum value of the function
        if (Rmax < R) Rmax = R;

        // Draw the pixel on the graph
        // Y0 - 225 adjusts the vertical shift of the graph
        putpixel(startXcoord + i, Y0 - 225 - (int)(R * pixelToY), WHITE);
    }
}

int main() {
    char cRmax[20];
    char str[50];
    int driver, mode, graph_error;
    int zeroX;
    int pixelToX;
    int pixelToY;
    int i;
    int j;
    char kPi[10];
    char kPj[10];

    clrscr();
    driver = DETECT;
    initgraph(&driver, &mode, "C://Turboc3//BGI");
    graph_error = graphresult();

    if (graph_error != grOk) {
        cprintf("ERROR WITH GRAPH %d", graph_error);
        getchar();
        return 255;
    }

    // Get maximum window dimensions
    Xmax = getmaxx();
    Ymax = getmaxy();

    // Set the starting and ending coordinates for the graph
    X0 = 20;
    Y0 = Ymax - 19;
    X1 = Xmax - 19;
    Y1 = 10;

    // Set line style and color
    setlinestyle(0, 1, 3);
    setcolor(WHITE);

    // Draw the graph window border
    rectangle(2, 0, Xmax - 2, Ymax - 30);

    // Fill the graph area with black
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(20, 20, WHITE);

    // Reset line style
    setlinestyle(0, 1, 1);

    // Set the zero axis for X
    zeroX = Y0 - 225;

    // Draw the coordinate axes
    line(X0, Y0 - 15, X0, Y1 - 20);  // Y-axis
    line(X0, zeroX, X1, zeroX);      // X-axis

    // Add text labels
    outtextxy(X0 + 40, Y1 + 40, "sin^2(x/2)+sqrt(x)"); // Updated function
    outtextxy(X1 + 3, zeroX + 5, "x");
    outtextxy(X0 + 3, Y1 + 3, "y");
    settextstyle(SMALL_FONT, HORIZ_DIR, 4);

    // Define scales for the axes
    pixelToX = (X1 - X0) / 16;  // X-axis scale to 16*pi
    pixelToY = 15;

    // Call the function to draw the graph
    drawf(pixelToX, pixelToY);

    // Draw ticks and labels on the X-axis up to 16*pi
    for (i = 1; i <= 16; ++i) {  // Ticks up to 16*pi
        line(X0 + pixelToX * i, zeroX, X0 + pixelToX * i, zeroX - 5);
        sprintf(kPi, "%dPI", i);
        outtextxy(X0 + pixelToX * i - 10, zeroX + 5, kPi);
    }

    // Draw ticks and labels on the Y-axis
    for (j = 1; j <= 10; ++j) {  // Fixed loop condition
        line(X0, zeroX - pixelToY * j, X0 + 10, zeroX - pixelToY * j);
        sprintf(kPj, "%d", j);
        if (j != 10) {
            outtextxy(X0 - 15, zeroX - pixelToY * j - 5, kPj);
        } else {
            outtextxy(X0 - 20, zeroX - pixelToY * j - 5, kPj);
        }
    }

    // Display the maximum function value
    sprintf(cRmax, "%.2f", Rmax); // Format with two decimal places
    strcpy(str, "MAX(f(x)) = ");
    strcat(str, cRmax);

    setlinestyle(0, 1, 3);
    setcolor(RED);
    rectangle(X0 + 25, Ymax - 25, X0 + 200, Ymax);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    floodfill(X0 + 30, Ymax - 10, WHITE); // Fill color
    setcolor(WHITE);
    outtextxy(X0 + 30, Ymax - 20, str);

    getchar();
    closegraph();
    return 0;
}
