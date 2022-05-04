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
enum menu{
    start=1,
    quit=-1
};
enum keyboard{
    up=72,
    left=75,
    right=77,
    down=80
};

void previewGame(); // 대기화면에서 user의 선택 확인
void drawPreview(); // 대기화면 로드
void drawUserCusor(int y); // 대기화면에 유저 커서 로드
void gotoxy(int x, int y);
gameState startGame(); // game 결과 반환
void makeMaze(); // 미로 생성
void drawMap(int *maze); // game 화면 로드

int main() {
    previewGame();

    return 0;
}

void gotoxy(int x, int y){
    COORD pos;

    pos.X=2*x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void previewGame(){
    int y=-1, input=0;

    while (y!=space){
        drawPreview();
        drawUserCusor(y);
        input=_getch();
        if(input==direction) {
            y *= -1;
        }
        else if(input==space){
            switch(y){
                case start:
                    //makeMaze();
                case quit: break;
            }
        }
    }
}

void drawPreview(){
    system("cls");
    gotoxy(5,2);
    cout<<"---------------------";
    gotoxy(5,3);
    cout<<"|        Maze       |";
    gotoxy(5,4);
    cout<<"---------------------";
    gotoxy(10,8);
    cout<<"Start";
    gotoxy(10,10);
    cout<<"Quit"<<"\n";
}

void drawUserCusor(int y){
    gotoxy(9,9+y);
    cout<<">";
}
