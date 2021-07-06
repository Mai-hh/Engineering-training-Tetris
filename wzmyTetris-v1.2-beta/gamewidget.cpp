#include "gamewidget.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <mybutton.h>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
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
inline void BlockCopy(int dblock[4][4],int sblock[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            dblock[i][j]=sblock[i][j];
}
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFixedSize(650,1000);
    btn_set();
    btn_pause->setParent(this);

//    QLabel *label=new QLabel;
//    label->setParent(this);
//    QFont font;
//    font.setFamily("Segeo UI");
//    font.setPointSize(20);

//    label->setFont(font);

//    label->setGeometry(QRect(Margin, Margin+SideLength*Line, 300, 100));//设置位置和大小


    //创建暂停界面
    stWidget = new settingWidget(this);

    connect(btn_pause,&QPushButton::clicked,[=](){
        killTimer(gameTimer);
        killTimer(paintTimer);
        stWidget->exec();
    });

    connect(stWidget,&settingWidget::ClockRun,[=](){
       gameTimer =  startTimer(speed_ms);
       paintTimer = startTimer(refresh_ms);
    });

    connect(stWidget,&settingWidget::backToMainWindow,[=](){
        this->hide();
        InitGame(speed_ms);
        emit this->backToMainWindow();
    });
    connect(stWidget,&settingWidget::Restart,[=](){
       InitGame(speed_ms);
    });

}

void GameWidget::paintEvent(QPaintEvent *event)
{

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

    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(Margin, Margin, SideLength*Row, SideLength*Line);
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(nextBlock[i][j]==1)
                painter.drawRect(Row*(SideLength+3)+j*SideLength+Margin,Margin+i*SideLength+50,SideLength,SideLength);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
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

void GameWidget::btn_set()
{
    btn_pause = new MyButton(":/Image/stop.png");
    btn_pause->setFixedSize(100,100);
    btn_pause->move(this->width()*0.75,this->height()*0.85);
//    btn_pause->setText("Pause");
//SideLength * (Row+2) + Margin, Margin + SideLength * (Line-2)
}

void GameWidget::keyPressEvent(QKeyEvent *event)
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

void GameWidget::ConvertStable(int x, int y)
{
    for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
        for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
            if(curBlock[i][j]==1)
                GameArea[y+i][x+j]=2;//ps
}
bool GameWidget::IsCollide(int x,int y,Direction dir)
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
            if(GameArea[y+i][x+j]==2 && (tempBlock[i][j]==1) || (x+tempBorder.lbound<0) || (x+tempBorder.rbound>Row-1))
                return true;
    return false;
}
void GameWidget::BlockMove(Direction dir)
{
    switch (dir) {
    case UP:
        if(IsCollide(blockPos.pos_x,blockPos.pos_y,UP))
            break;

        BlockRotate(curBlock);

        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];

        GetBorder(curBlock,curBorder);
        break;


    case DOWN:
        if(blockPos.pos_y+curBorder.dbound==Line-1)
        {
            ConvertStable(blockPos.pos_x,blockPos.pos_y);
            ResetBlock();
            break;
        }

        if(IsCollide(blockPos.pos_x,blockPos.pos_y,DOWN))
        {

            ConvertStable(blockPos.pos_x,blockPos.pos_y);
            ResetBlock();
            break;
        }

        for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
            GameArea[blockPos.pos_y][blockPos.pos_x+j]=0;

        blockPos.pos_y+=1;

        for(int i=0;i<4;i++)
            for(int j=curBorder.lbound;j<=curBorder.rbound;j++)
                if(blockPos.pos_y+i<=Line-1 && GameArea[blockPos.pos_y+i][blockPos.pos_x+j]!=2)
                    GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];
        break;


    case LEFT:
        if(blockPos.pos_x+curBorder.lbound==0||IsCollide(blockPos.pos_x,blockPos.pos_y,LEFT))
            break;

        for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
            GameArea[blockPos.pos_y+i][blockPos.pos_x+3]=0;
        blockPos.pos_x-=1;

        for(int i=curBorder.ubound;i<=curBorder.dbound;i++)
            for(int j=0;j<4;j++)
                if(blockPos.pos_x+j>=0 && GameArea[blockPos.pos_y+i][blockPos.pos_x+j]!=2)
                    GameArea[blockPos.pos_y+i][blockPos.pos_x+j]=curBlock[i][j];
        break;


    case RIGHT:
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

    int i=Line-1;
    int line_count=0;
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
            line_count++;
        }
    }
    score+=line_count*10;

    for(int j=0;j<Row;j++)
        if(GameArea[0][j]==2)
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
        BlockMove(DOWN);
    if(event->timerId()==paintTimer)
        update();
}
void GameWidget::ResetBlock()
{
    BlockCopy(curBlock,nextBlock);
    GetBorder(curBlock,curBorder);
    int blockId=rand()%7;
    CreateBlock(nextBlock,blockId);

    block_point start_point;
    start_point.pos_x=Row/2-2;
    start_point.pos_y=0;
    blockPos=start_point;
}
void GameWidget::GetBorder(int block[4][4],Border &border)
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(block[i][j]==1)
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
    gameTimer=startTimer(speed_ms);
    paintTimer=startTimer(refresh_ms);
    int blockId=rand()%7;
    CreateBlock(nextBlock,blockId);
    ResetBlock();
}

void GameWidget::GameOver()
{
    killTimer(gameTimer);
    killTimer(paintTimer);
    if(QMessageBox::information(this,"failed","game over","Restart") == 0)
    {
        InitGame(speed_ms);
    }

}
//void GameWidget::GameOver()
//{

//    QPushButton *btn_gameOver = new QPushButton(this);

//    btn_gameOver->setFixedSize(50,50);
//    btn_gameOver->move(SideLength * (Row+2) + Margin, Margin);
//    btn_gameOver->setText("GG");

//    gameOverWidget = new GameOverWidget(this);
//    connect(btn_gameOver,&QPushButton::clicked,[=](){
//        gameOverWidget->exec();
//    });

//}
void GameWidget::BlockRotate(int block[4][4])
{
    int tempBlock[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            tempBlock[3-j][i]=block[i][j];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            block[i][j]=tempBlock[i][j];
}
void GameWidget::InitGame(int speed)
{
    for(int i=0;i<Line;i++)
        for(int j=0;j<Row;j++)
            GameArea[i][j]=0;
    speed_ms=speed;
    refresh_ms=30;
    srand(time(nullptr));
    score=0;
    StartGame();
}



