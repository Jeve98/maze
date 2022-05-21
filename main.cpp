// ▒ 모양 2개 == 1블럭 && 2 space == 1블럭
// 숫자 배열 선언 후 길 뚫기 0==길 1==블럭, if(arr[i]==1) draw ▒▒;
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <stack>
#include <time.h>

#define direction 224
#define space 32
#define mazeSize 41

using namespace std;

enum gameState{
    starting=0,
    clear=1,
    giveUp=2
};
enum menu{
    start=-1,
    quit=1
};
enum keyboard{
    Up=72,
    Left=75,
    Right=77,
    Down=80
};
enum mazeState{
    wall=0,
    street=1,
    origin=2,
    destination=3,
};
enum crush{
    //crushItem=1, item 추가시 사용
    crushDestination=2,
    notcrush=3
};

int maze[mazeSize][mazeSize]={0, };
int origin_x=0;
int origin_y=0;
clock_t startT=0;
clock_t endT=0;

menu previewGame(); // 대기화면에서 user의 선택 확인
void drawPreview(); // 대기화면 로드
void drawUserCusor(int y); // 대기화면에 유저 커서 로드
void gotoxy(int x, int y);
gameState startGame(); // game 결과 반환
void makeMaze(); // 미로 생성
void drawMap(); // game 화면 로드
int makeRandom(int a, int b); // random값 생성
crush userMove(); // user 움직임
bool testInside(int type); // 움직임이 maze 내부에 있는지 검사
clock_t timer(gameState state);

int main() {
    menu state;
    gameState game;
    int ending=0;

    while (1){
        state=previewGame();
        if(state==start){
            game=startGame();
            timer(starting);
            for(int i=0; i<mazeSize; i++){
                for(int j=0; j<mazeSize; j++){
                    maze[i][j]=wall;
                }
            }

            if(game==giveUp){
                cout<<"End Game";
                return 0;
            }
            else{
                ending=timer(game);
                cout<< "Clear" << "\n" << "Score: "<<ending<<"\n";
                return 0;
            }
        }
        else if(state==quit){
            return 0;
        }
    }

    return 0;
}

void gotoxy(int x, int y){
    COORD pos;

    pos.X=2*x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

menu previewGame(){
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
                    return start;
                case quit:
                    return quit;
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

int makeRandom(int a, int b){
    int random=0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(a, b);
    random=dis(gen);

    return random;
}

void makeMaze(){
    stack<int> x;
    stack<int> y;
    int startPoint=makeRandom(1, mazeSize-2);
    int mazeDirection[4]={0,};
    int Direction=makeRandom(1,4);
    int i=2, j=startPoint;
    int mid_i=0, mid_j=0;
    int testing_number=1;
    int tempX=0, tempY=0;
    int desti= makeRandom(1, mazeSize);

    mazeDirection[Direction-1]=1;
    maze[0][startPoint]=origin;
    maze[2][startPoint]=street;
    maze[1][startPoint]=street;
    origin_x=startPoint;
    origin_y=0;
    x.push(j);
    y.push(i);

    do{
        tempX=j;
        tempY=i;
        switch(Direction){
            case 1: i+=2; mid_i=-1; mid_j=0; break;    // 아래
            case 2: j+=2; mid_i=0; mid_j=-1; break;    // 오른쪽
            case 3: i-=2; mid_i=1; mid_j=0; break;   // 위
            case 4: j-=2; mid_i=0; mid_j=1; break;   // 왼쪽
        }
        if((i>0)&&(i<mazeSize-1)&&(j>0)&&(j<mazeSize-1)){ //안에서만 놀아
            if(maze[i][j]==wall){
                for(int ii=0; ii<4; ii++){
                    mazeDirection[ii]=0;
                }

                x.push(j);
                y.push(i);
                maze[i][j]=street;
                maze[i+mid_i][j+mid_j]=street;

                Direction= makeRandom(1,4);
            }
            else{
                mazeDirection[Direction-1]=1;

                testing_number=1;
                for(int ii=0; ii<4; ii++){
                    if(mazeDirection[ii]==0){
                        i=tempY;
                        j=tempX;
                        Direction=ii+1;
                        mazeDirection[ii]=1;
                        testing_number=0;
                        break;
                    }
                }

                if(testing_number==1){
                    i=y.top();
                    y.pop();
                    j=x.top();
                    x.pop();
                    Direction= makeRandom(1,4);
                }
            }
        }
        else{
            mazeDirection[Direction-1]=1;

            testing_number=1;
            for(int ii=0; ii<4; ii++){
                if(mazeDirection[ii]==0){
                    i=tempY;
                    j=tempX;
                    Direction=ii+1;
                    mazeDirection[ii]=1;
                    testing_number=0;
                    break;
                }
            }

            if(testing_number==1){
                i=y.top();
                y.pop();
                j=x.top();
                x.pop();
                Direction= makeRandom(1,4);
            }
        }
    }while(!(x.empty()));

    for(int ii=0; ; ii++){
        if(maze[mazeSize-3][ii]==street){
            desti--;
            if(desti==0){
                maze[mazeSize-1][ii]=destination;
                maze[mazeSize-2][ii]=street;
                break;
            }
            else if(ii>=mazeSize-2){
                ii=0;
            }
        }
    }
}

void drawMap(){
    int x=0, y=0;
    for(int i=0; i<mazeSize; i++){
        gotoxy(x,y++);
        for(int j=0; j<mazeSize; j++){
            if(maze[i][j]==wall){
                cout<<"▒▒";
            }
            else if(maze[i][j]==street||maze[i][j]==destination){
                cout<<"  ";
            }
            else if(maze[i][j]==origin){
                cout<<"ㅇ";
            }
        }
        cout<<"\n";
    }
}

gameState startGame(){
    makeMaze();
    while(1){
        system("cls");
        drawMap();
        if(userMove()==crushDestination){
            return clear;
        }
    }
}

crush userMove(){
    int input=0;
    input=_getch();

    if(input==direction){
        input=_getch();
        if(testInside(input)){

            switch (input) {
                case Up: if(maze[origin_y-1][origin_x]==street){
                        origin_y--;
                        maze[origin_y][origin_x]=origin;
                        maze[origin_y+1][origin_x]=street;
                        return notcrush;
                    }
                    else if(maze[origin_y-1][origin_x]==destination){
                        return crushDestination;
                    }
                    else{
                        return notcrush;
                    }
                case Down: if(maze[origin_y+1][origin_x]==street){
                        origin_y++;
                        maze[origin_y][origin_x]=origin;
                        maze[origin_y-1][origin_x]=street;
                        return notcrush;
                    }
                    else if(maze[origin_y+1][origin_x]==destination){
                        return crushDestination;
                    }
                    else{
                        return notcrush;
                    }
                case Right: if(maze[origin_y][origin_x+1]==street){
                        origin_x++;
                        maze[origin_y][origin_x]=origin;
                        maze[origin_y][origin_x-1]=street;
                        return notcrush;
                    }
                    else if(maze[origin_y][origin_x+1]==destination){
                        return crushDestination;
                    }
                    else{
                        return notcrush;
                    }
                case Left: if(maze[origin_y][origin_x-1]==street){
                        origin_x--;
                        maze[origin_y][origin_x]=origin;
                        maze[origin_y][origin_x+1]=street;
                        return notcrush;
                    }
                    else if(maze[origin_y][origin_x-1]==destination){
                        return crushDestination;
                    }
                    else{
                        return notcrush;
                    }
            }
        }
    }
}

bool testInside(int type){
    switch (type) {
        case Up: if(origin_y-1<0){
            return false;
            }
            else{
                return true;
            }
        case Down: if(origin_y+1>=mazeSize){
            return false;
            }
            else{
                return true;
            }
        case Right: if(origin_x+1>=mazeSize){
            return false;
            }
            else{
                return true;
            }
        case Left: if(origin_x-1<0){
            return false;
            }
            else{
                return true;
            }
    }
}

clock_t timer(gameState state){
    if(state==clear){
        endT=clock();
        return static_cast<int>(endT-startT)/CLOCKS_PER_SEC;
    }
    else if(state==starting){
        startT=clock();
        return 0;
    }
}