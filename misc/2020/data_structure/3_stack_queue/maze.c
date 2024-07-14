/* maze problem
 * 20200212
 * 재귀적으로 작성하는 것이 정신 건강에 훨씬 이로움 
 */

#include <stdio.h>
#include <stdbool.h>

/*
#define ROW 10
#define COL 15
short maze[ROW][COL] = {
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
    {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}
};
*/
#define ROW 5
#define COL 5
short maze[ROW][COL] = {
    {0, 0, 1, 1, 0},
    {1, 1, 0, 0, 1},
    {1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1},
    {0, 1, 1, 0, 0}
};

typedef struct {
    int row, col, dir;
} Element;

/* stack */

#define STACKSZ 100
Element _stack[STACKSZ];
int _top = -1;
bool empty()
{
    return _top == -1;
}
Element top()
{
    return _stack[_top];
}
void push(Element e)
{
    if (_top == STACKSZ - 1)
        return;
    _stack[++_top] = e;
}
void pop()
{
    if (_top == -1)
        return;
    _top--;
}

/* maze algorithm */

bool visited[ROW][COL];
struct {int row, col;} move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {1, -1}};
void path(int startRow, int startCol, int endRow, int endCol)
{
    Element e;
    bool found;
    int row, col, dir;
    int nextRow, nextCol;

    found = false;
    visited[startRow][startCol] = true;
    e.row = startRow, e.col = startCol, e.dir = 0, push(e);
    while (!found && !empty()) {
        e = top(), pop(), row = e.row, col = e.col, dir = e.dir;
        for (; dir < 8; dir++) {
            nextRow = row + move[dir].row, nextCol = col + move[dir].col;
            if (!(0 <= nextRow && nextRow < ROW && 0 <= nextCol && nextCol < COL))
                continue;
            if (maze[nextRow][nextCol] || visited[nextRow][nextCol])
                continue;
            e.row = row, e.col = col, e.dir = dir + 1, push(e);
            if (nextRow == endRow && nextCol == endCol) {
                found = true;
                break;
            }
            visited[nextRow][nextCol] = true;
            row = nextRow, col = nextCol, dir = -1; //
        }
    }
    if (!found) {
        printf("not found\n");
        return;
    }
    printf("path : ");
    while (!empty()) {
        e = top(), pop();
        printf("(%d,%d)", e.col, e.row);
    }
    printf("\n");
}

/* main */

int main()
{
    path(0, 0, ROW - 1, COL - 1);
    return 0;
}