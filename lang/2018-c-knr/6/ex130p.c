#include <stdio.h>
#define XMAX    20
#define YMAX    10

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

int main(void)
{
    struct rect screen;
    struct point middle;
    struct point added;
    
    struct point makepoint(int, int);
    struct point addpoint(struct point, struct point);

    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x)/2, (screen.pt2.x + screen.pt2.y)/2);
    added = addpoint(screen.pt1, screen.pt2);

    printf("added\t\t: %d %d\n", added.x, added.y);                 /* (20, 10) */
    printf("screen.pt1\t: %d %d\n", screen.pt1.x, screen.pt1.y);    /* (0, 0), call by value */
}

/* makepoint:   make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

/* addpoint:    add two points */
struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

