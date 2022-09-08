/* 
 * Random grid generator
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2022-09-08
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define SWAP(x, y) ((y) = (x)^(y), (x) = (x)^(y), (y) = (x)^(y))
#define ARRSZ(arr) (sizeof(arr) / sizeof(*(arr)))

#define Y 10
#define X 10
#define PLAYERS 10

int map[Y][X];
int start[PLAYERS][2]; 

void init() {
    int p;
    int y, x, tmp;
    for (p = 1; p <= PLAYERS; p++) {
        while (TRUE) {
            tmp = rand() % (Y * X);
            y = tmp / X, x = tmp % X;
            if (map[y][x]) continue;
            map[y][x] = p;
            start[p][0] = y, start[p][1] = x;
            break;
        }
    }
}

void shuffle_array(int arr[], int len) {
    int i, j;
    for (i = 0; i < len - 1; i++) {
        j = (i + 1) + rand() % (len - i - 1);
        SWAP(arr[i], arr[j]);
    }
}

void play(int p) {
    int y = start[p][0], x = start[p][1];
    int y_m = y, y_M = y;
    int x_m = x, x_M = x;

    int order[] = { 0, 1, 2, 3 };
    shuffle_array(order, ARRSZ(order));

    int i, b;
    for (i = 0; i < ARRSZ(order); i++) {
        switch (order[i]) {
        case 0:     // to +X
            for (x = x_M + 1; x < X; x++) {
                b = TRUE;
                for (y = y_m; y <= y_M; y++)
                    if (map[y][x]) {
                        b = FALSE;
                        break;
                    }
                if (!b) break;
                for (y = y_m; y <= y_M; y++)    map[y][x] = p;
                x_M = x;
            }
            break;
        case 1:     // to +Y
            for (y = y_M + 1; y < Y; y++) {
                b = TRUE;
                for (x = x_m; x <= x_M; x++)
                    if (map[y][x]) {
                        b = FALSE;
                        break;
                    }
                if (!b) break;
                for (x = x_m; x <= x_M; x++)    map[y][x] = p;
                y_M = y;
            }
            break;
        case 2:     // to -X
            for (x = x_m - 1; x >= 0; x--) {
                b = TRUE;
                for (y = y_m; y <= y_M; y++)
                    if (map[y][x]) {
                        b = FALSE;
                        break;
                    }
                if (!b) break;
                for (y = y_m; y <= y_M; y++)    map[y][x] = p;
                x_m = x;
            }
            break;
        case 3:     // to -Y
            for (y = y_m - 1; y >= 0; y--) {
                b = TRUE;
                for (x = x_m; x <= x_M; x++)
                    if (map[y][x]) {
                        b = FALSE;
                        break;
                    }
                if (!b) break;
                for (x = x_m; x <= x_M; x++)    map[y][x] = p;
                y_m = y;
            }
            break;
        }
    }
}

void print() {
    int y, x;
    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++)
            printf("%2d ", map[y][x]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    srand((unsigned int)time(NULL));
    
    init();
    //print();
    for (int p = 1; p <= PLAYERS; p++)  play(p);
    print();
}