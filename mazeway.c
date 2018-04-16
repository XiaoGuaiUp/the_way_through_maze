#include <stdio.h>

#define MAX_ROW 6
#define MAX_COL 6

//用一个二维数组来表示迷宫地图
typedef struct Maze{
    int map[MAX_ROW][MAX_COL];
} Maze;

typedef struct Point{
    int row;
    int col;
} Point;//入口点

//迷宫初始化
void MazeInit(Maze* maze){
    int map[MAX_ROW][MAX_COL]={
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,0,0},
        {0,1,0,1,1,0},
        {0,1,1,0,0,0},
        {0,0,1,0,0,0}
    };
    size_t i=0;
    for(;i<MAX_ROW;++i){
        size_t j=0;
        for(;j<MAX_COL;++j){
            maze->map[i][j]=map[i][j];
        }
    }
    return;
}

//迷宫地图打印
void MazePrintf(Maze* maze){
    size_t i=0;
    for(;i<MAX_ROW;++i){
        size_t j=0;
        for(;j<MAX_COL;++j){
            printf("%2d",maze->map[i][j]);
        }
        printf("\n");
    }
}

int CanStay(Maze* maze,Point pt,Point entry){
    //1.若pt在地图外，排除
    if(pt.row<0||pt.row>=MAX_ROW||pt.col<0||pt.col>=MAX_COL){
        return 0;
    }
    //2.若pt在地图内，若其值为1，可落脚，其他值（0,2）排除
    int value=maze->map[pt.row][pt.col];
    if(value==1){
        return 1;
    }
    return 0;
}

void Mark(Maze* maze,Point cur){
    maze->map[cur.row][cur.col]=2;
}

//是否为出口
int IsExit(Maze* maze,Point cur,Point entry){
    //1.当前点是否为入口，若是一定不是出口
    if(cur.row==entry.row&&cur.col==entry.col){
        return 0;
    }
    //2.若点在地图的边界上，也说明是出口
    if(cur.row==0 || cur.row==MAX_ROW-1 || cur.col==0 || cur.col==MAX_COL-1){
        return 1;
    }
    return 0;
}

//递归函数
void _GetPath(Maze* maze,Point cur,Point entry){
    //1.判定当前点是否能走，是否可落脚
    if(!CanStay(maze,cur,entry)){
        return;
    }
    //2.若能落脚，把当前位置做标记，例如：将原来的1改为2
    Mark(maze,cur);
    //3.若当前点为出口，说明就找到了
    if(IsExit(maze,cur,entry)){
        //说明找到了这条路
        printf("找到了一条路径\n");
        return;
    }
    //4.若不为出口，就按顺时针探测四个相邻的点，递归调用函数自身，递归时，更新cur
    //  每次递归时，点都是下一次要走的点，这个点是否能走，由递归做判断
    Point up=cur;
    up.row -=1;//当前点的上一个
    _GetPath(maze,up,entry);

    Point right=cur;
    right.col +=1;
    _GetPath(maze,right,entry);

    Point down=cur;
    down.row +=1;
    _GetPath(maze,down,entry);

    Point left=cur;
    left.col -=1;
    _GetPath(maze,left,entry);
}

//使用递归方式
void GetPath(Maze* maze,Point entry){
    if(maze==NULL){
        return;
    }
    //使用下面的函数辅助我们完成递归
    _GetPath(maze,entry,entry);
}

void main(){
    Maze maze;
    MazeInit(&maze);
    MazePrintf(&maze);
    Point entry={0,1};
    GetPath(&maze,entry);
    MazePrintf(&maze);
}
