// ▒ 모양 2개 == 1블럭 && 2 space == 1블럭
// 숫자 배열 선언 후 길 뚫기 0==길 1==블럭, if(arr[i]==1) draw ▒▒;

#include <iostream>
#include <conio.h>
#include <Windows.h>

#define direction 224
#define space 32

using namespace std;

enum gameState{
    clear=1,
    giveUp=2
};

gameState startGame();
void makeMaze(int *maze);
void drawMaze(int *maze);

int main() {
    gameState gaming;

    gaming=startGame();

    return 0;
}