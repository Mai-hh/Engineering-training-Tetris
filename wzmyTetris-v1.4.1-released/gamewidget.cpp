#include "gamewidget.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <mybutton.h>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QTimer>
//七种不同方块
int item1[4][4]=
{
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};
int item2[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};
int item3[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};
int item4[4][4]=
{
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}
};
int item5[4][4]=
{
    {0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};
int item6[4][4]=
{
    {0,0,0,0},
    {0,0,1,0},
    {0,1,1,1},
    {0,0,0,0}
};
int item7[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0}
};

//复制函数
inline void BlockCopy(int dblock[4][4],int sblock[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            dblock[i][j]=sblock[i][j];
}
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);//设置焦点防止键盘事件失灵
    this->setFixedSize(650,1000);
    btn_set();
    btn_pause->setParent(this);

    stWidget = new settingWidget(this);//实例化设置窗口

    connect(btn_pause,&QPushButton::clicked,[=](){
        killTimer(gameTimer);
        killTimer(paintTimer);
        stWidget->exec();
    });//暂停

    connect(stWidget,&settingWidget::ClockRun,[=](){
       gameTimer =  startTimer(speed_ms);
       paintTimer = startTimer(refresh_ms);
    });//开始

    connect(stWidget,&settingWidget::backToMainWindow,[=](){
        this->hide();
        InitGame(speed_ms);
        emit this->backToMainWindow();
    });//返回主菜单
    connect(stWidget,&settingWidget::Restart,[=](){
       InitGame(speed_ms);
    });//重新开始初始化游戏

}

void GameWidget::paintEvent(QPaintEvent *event)
{
    //绘制背景图
    QPainter painter(this);

    QPen pen;

    painter.setPen(pen);


    QBrush brush(QColor(242,107,92));

    painter.setBrush(brush);

    painter.drawRect(QRect(0,0,this->width(),this->height()));


    painter.drawRect(Margin, Margin, SideLength*Row, SideLength*Line);

    QPixmap pix;
    pix.load(":/Image/piece.jpg");

    painter.drawPixmap(Margin, Margin, SideLength*Row, SideLength*Line,pix);

    pix.load(":/Image/piece1.jpg");

    painter.drawPixmap(Margin+SideLength*Row+10, Margin, 220, 280,pix);

    pix.load(":/Image/piece3.jpg");

    painter.drawPixmap(Margin+SideLength*Row+10, Margin+300, 220, 500,pix);
    //绘制游戏区域
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(Margin, Margin, SideLength*Row, SideLength*Line);
    //绘制绘制下一块方块区
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(nextBlock[i][j]==1)
                painter.drawRect(Row*(SideLength+3)+j*SideLength+Margin,Margin+i*SideLength+50,SideLength,SideLength);
    //绘制分数
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",12));
    painter.drawText(QRect(Margin*5+Row*SideLength,Margin*2+6*SideLength,SideLength*4,SideLength*3),Qt::AlignCenter,"score: "+QString::number(score));

    for(int i=0;i<Line;i++)
        for(int j=0;j<Row;j++)
        {
            //绘制活动方块
            if(GameArea[i][j]==1)
            {
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(j*SideLength+Margin,i*SideLength+Margin,SideLength,SideLength);
            }
            //绘制稳定方块
            else if(GameArea[i][j]==2)
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                painter.drawRect(j*SideLength+Margin,i*SideLength+Margin,SideLength,SideLength);
            }
        }
}

void GameWidget::btn_set()//初始化按钮
{
    btn_pause = new MyButton(":/Image/stop.png");
    btn_pause->setFixedSize(100,100);
    btn_pause->move(this->width()*0.75,this->height()*0.85);
}

void GameWidget::keyPressEvent(QKeyEvent *event)//重写键盘事件
{

    switch(event->key())
    {
    case Qt::Key_Up:
        BlockMove(UP);
        break;
    case Qt::Key_Down:
        BlockMove(DOWN);
        break;
    case Qt::Key_Left:
        BlockMove(LEFT);
        break;
    case Qt::Key_Right:
        BlockMove(RIGHT);
        break;
    case Qt::Key_Space:
        BlockMove(SPACE);
        break;
    default:
            break;

    }
}

void GameWidget::ConvertStable(int x, int y)//稳定方块
{
    for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
        for(int j=curBorder.lbound;j<=curBorder.rbound;j++)//扫描当前方块边界
            if(curBlock[i][j]==1)//
                GameArea[y+i][x+j]=2;//ps
}
bool GameWidget::IsCollide(int x,int y,Direction dir)//碰撞检测
{
    int tempBlock[4][4];
    BlockCopy(tempBlock,curBlock);
    Border tempBorder;
    GetBorder(tempBlock,tempBorder);
    //try
    switch(dir)
    {
    case UP:
        BlockRotate(tempBlock);
        GetBorder(tempBlock,tempBorder); //re
        break;
    case DOWN:
        y+=1;
        break;
    case LEFT:
        x-=1;
        break;
    case RIGHT:
        x+=1;
        break;
    default:
        break;
    }
    for(int i=tempBorder.ubound;i<=tempBorder.dbound;i++)
        for(int j=tempBorder.lbound;j<=tempBorder.rbound;j++)
            if((GameArea[y+i][x+j]==2 && tempBlock[i][j]==1) || (x+tempBorder.lbound<0) || (x+tempBorder.rbound>Row-1))
                return true;
    return false;//如果边界区域稳定且当前方块活动或者越界，说明碰撞
}
void GameWidget::BlockMove(Direction dir)//方块移动
{
    switch (dir) {
    case UP:
        if(IsCollide(blockPos.pos_x,blockPos.pos_y,UP))//如果碰撞，跳出，否则旋转
            break;

        BlockRotate(curBlock);

//        for(int i=curBorder.lbound;i<curBorder.rbound;i++)
//            for(int j=curBorder.ubound;j<curBorder.dbound;j++)
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {
                if(GameArea[blockPos.pos_y+i][blockPos.pos_x+j]==2) break;
                else GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];

            }
        //重新计算边界
        GetBorder(curBlock,curBorder);
        break;


    case DOWN:
        //方块到达边界则不再移动
        if(blockPos.pos_y+curBorder.dbound==Line-1)
        {
            ConvertStable(blockPos.pos_x,blockPos.pos_y);
            ResetBlock();
            break;
        }
        //碰撞检测，只计算上下左右边界，先尝试走一格，如果碰撞则稳定方块后跳出
        if(IsCollide(blockPos.pos_x,blockPos.pos_y,DOWN))
        {
        //只有最终不能下落才转成稳定方块
            ConvertStable(blockPos.pos_x,blockPos.pos_y);
            ResetBlock();
            break;
        }
        //清除下落痕迹
        for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
            GameArea[blockPos.pos_y][blockPos.pos_x+j]=0;
        //没有碰撞则下落一格
        blockPos.pos_y+=1;
        //拷贝到场景
        for(int i=0;i<4;i++)
            for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
                if(blockPos.pos_y+i<=Line-1 && GameArea[blockPos.pos_y+i][blockPos.pos_x+j]!=2)
                    GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];
        break;


    case LEFT:
        //到左边界或者碰撞不再往左
        if(blockPos.pos_x+curBorder.lbound==0||IsCollide(blockPos.pos_x,blockPos.pos_y,LEFT))
            break;
        //清除移动痕迹
        for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
            GameArea[blockPos.pos_y+i][blockPos.pos_x+3]=0;
        blockPos.pos_x-=1;
        //拷贝到场景
        for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
            for(int j=0;j<4;j++)
                if(blockPos.pos_x+j>=0 && GameArea[blockPos.pos_y+i][blockPos.pos_x+j]!=2)
                    GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];
        break;


    case RIGHT:
        //the same as LEFT
        if(blockPos.pos_x+curBorder.rbound==Row-1||IsCollide(blockPos.pos_x,blockPos.pos_y,RIGHT))
            break;

        for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
            GameArea[blockPos.pos_y+i][blockPos.pos_x]=0;
        blockPos.pos_x+=1;

        for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
            for(int j=0;j<4;j++)
                if(blockPos.pos_x+j<=Row-1 && GameArea[blockPos.pos_y+i][blockPos.pos_x+j]!=2) //注意场景数组不越界
                    GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];
        break;


    case SPACE:
        //按空格就一直下落
        while(blockPos.pos_y+curBorder.dbound<Line-1 && !IsCollide(blockPos.pos_x,blockPos.pos_y,DOWN))
        {

            for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
                GameArea[blockPos.pos_y][blockPos.pos_x+j]=0;

            blockPos.pos_y+=1;

            for(int i=0;i<4;i++)
                for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
                    if(blockPos.pos_y+i<=Line-1 && GameArea[blockPos.pos_y+i][blockPos.pos_x+j]!=2)
                        GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];
        }
        ConvertStable(blockPos.pos_x,blockPos.pos_y);
        ResetBlock();
        break;
    default:
        break;
    }
    //消除处理及分数增加
    int i=Line-1;
    int lineCount=0;
    while(i>=1)
    {
        bool is_line_full=true;
        for(int j=0;j<Row;j++)
            if(GameArea[i][j]==0 || GameArea[i][j]==1)
            {
                is_line_full=false;
                i--;
                break;
            }
        if(is_line_full)
        {
            for(int k=i;k>=1;k--)
                for(int j=0;j<Row;j++)
                    GameArea[k][j]=GameArea[k-1][j];
            lineCount++;
        }
    }
    score+=lineCount*10*lineCount;

    for(int j=0;j<Row;j++)
        if(GameArea[0][j]==2)//最顶端也有稳定方块
            GameOver();
}
void GameWidget::CreateBlock(int block[4][4], int blockId)
{
    switch (blockId)
    {
    case 0:
        BlockCopy(block,item1);
        break;
    case 1:
        BlockCopy(block,item2);
        break;
    case 2:
        BlockCopy(block,item3);
        break;
    case 3:
        BlockCopy(block,item4);
        break;
    case 4:
        BlockCopy(block,item5);
        break;
    case 5:
        BlockCopy(block,item6);
        break;
    case 6:
        BlockCopy(block,item7);
        break;
    default:
        break;
    }
}
void GameWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==gameTimer)
        BlockMove(DOWN);//自动下落
    if(event->timerId()==paintTimer)
        update();//画面刷新
}
void GameWidget::ResetBlock()//更新“下一个方块”信息
{
    BlockCopy(curBlock,nextBlock);//更换容器
    GetBorder(curBlock,curBorder);
    int blockId=rand()%7;
    CreateBlock(nextBlock,blockId);

    block_point startPoint;
    int temp = rand()%16;
    if(temp>12)
    {
        temp=12;
    }
    startPoint.pos_x=temp;
    startPoint.pos_y=0;
    blockPos=startPoint;
}
void GameWidget::GetBorder(int block[4][4],Border &border)//获取方块边界
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(block[i][j]==1)//在已有个4*4方块中缩小边界范围
            {
                border.dbound=i;
                break;
            }
    for(int i=3;i>=0;i--)
        for(int j=0;j<4;j++)
            if(block[i][j]==1)
            {
                border.ubound=i;
                break;
            }
    for(int j=0;j<4;j++)
        for(int i=0;i<4;i++)
            if(block[i][j]==1)
            {
                border.rbound=j;
                break;
            }
    for(int j=3;j>=0;j--)
        for(int i=0;i<4;i++)
            if(block[i][j]==1)
            {
                border.lbound=j;
                break;
            }
}
void GameWidget::StartGame()
{
    gameTimer=startTimer(speed_ms);//开启游戏定时器和画面刷新
    paintTimer=startTimer(refresh_ms);
    int blockId=rand()%7;
    CreateBlock(nextBlock,blockId);//根据Id在游戏区域创建方块
    ResetBlock();//替换 “下一个方块”
}

void GameWidget::GameOver()
{
    killTimer(gameTimer);//关闭定时器
    killTimer(paintTimer);
    if(QMessageBox::information(this,"failed","game over","Restart") == 0)//如果选择重开游戏
    {
        InitGame(speed_ms);
    }

}
void GameWidget::BlockRotate(int block[4][4])//方块旋转
{
    int tempBlock[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            tempBlock[3-j][i]=block[i][j];//90度顺时针旋转
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            block[i][j]=tempBlock[i][j];
}
void GameWidget::InitGame(int speed)//初始化游戏，参数决定游戏速度
{
    for(int i=0;i<Line;i++)
        for(int j=0;j<Row;j++)
            GameArea[i][j]=0;//清空游戏区域
    speed_ms=speed;
    refresh_ms=30;
    srand(time(nullptr));//设置随机数
    score=0;
    StartGame();//游戏开始
}



