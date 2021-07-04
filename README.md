# QT creator  学习之路 #

## main ##

> * QApplication 应用程序对象，有且仅有一个
>
>   ~~~c++
>   QApplication a(argc, argv);
>   ~~~
>
> * xx.show()
>
>   ~~~c++
>   MainWindow w;
>   w.show();//窗口对象窗口化输出
>   //show()方法默认顶层输出（单独一个窗口）
>   ~~~
>
> * a.exec()
>
>   ~~~c++
>   return a.exec();//进入消息循环，等待信息输入
>   ~~~
>
> 

对象

> * QPushButton 需要<QPushiButton>库
>
>   ~~~c++
>   QPushButton *btn = new QPushButton;
>                                       
>   btn->show();//单独一个窗口创建按钮
>   btn->setParent(this);//在Widget上创建
>   btn->setText("xxxx");//设置按钮上出现的字符串
>   btn->move(x,y);//移动按钮到绝对坐标
>   ~~~

## 方法 ##

以上四个+

> * resize(w,h);
>
>   ~~~c++
>   resize(int w, int h);//改变窗口大小
>   xx->resize();//改变对象尺寸（可放缩）
>   ~~~
>
> * setFixedSize(w,h) 设置固定窗口大小

## 新建类 ##

> * 右键文件名添加文件
>
>   文件名就是要添加的类
>
>   继承类选择对象树最近的类，如：创建新Button继承QPushButton的爷类QWidget，创建成功后修改对应的头文件库名和继承的父类名，在对应的.cpp文件中修改传出的类名
>
>   ~~~c++
>       MyPushiButton *btn = new MyPushiButton;
>       btn->setText("mybtn");
>       btn->setParent(this);//创建一个自己写的类new出来的对象
>   ~~~
>
>   ps: setParent到QWidget对象树上之后不需要.Close()释放内存，会自动释放
>
> * 类的析构（内存释放）
>
>   用 xxx::~xxx()读取
>
>   ~~~c++
>   MyPushiButton::~MyPushiButton()
>   {
>       qDebug() << "MyPushButton's xigouo "<<endl;
>   }
>   //当需要析构时（内存释放）执行代码体
>   //可以针对对象树做析构抓取
>   //例如这里的MyPushButton是Widget的下级类
>   //可以同时抓取Widget类的析构
>   Widget::~Widget()
>   {
>       qDebug()<<"Widget.xigou";
>       delete ui;
>   }
>   //以上则会打印两行，顺序是先上级后下级，但是析构顺序是从下级到上级的，与编译运行逻辑有关
>   ~~~
>
>   ### 总而言之，QObject的派生类不需要管理释放 ###
>
>   

## 信号槽 ##

>* connect()方法
>
>  ~~~c++
>  connect(A,B,C,D);
>  //A是信号发送者的指针
>  //B是发送的信号的地址
>  //C是信号接收者的指针
>  //D是槽函数
>  ~~~
>
>  ~~~C++
>  connect(btn, &QPushButton::clicked, this, &QWidget::close);
>  //点击btn 调用QPushButton下的clicked方法 使当前窗口调用QWidget类下的close方法
>  ~~~

## 自定义信号和槽 ##

> 1. 明确触发流程，如：下课了，学生要请老师吃饭
>
> 2. 拆分
>
>    > * 信号：下课了
>    > * 对象：学生，老师
>    > * 事件：请吃饭
>
> 3. 抽象成代码
>
>    * 信号在signals下声明函数，不需要实现，可以重载
>
>       ~~~c++
>       signals :
>       	void hungry();
>       ~~~
>
> 
>
>    * 槽函数在public slots下声名，需要实现
>
>      ~~~c++
>      public slots:
>      	void treat();
>      //转到student.cpp
>      void Student::treat()
>      {
>          ...;
>      }
>      ~~~
>
>    * 对象定义在widget .h中作为成员变量(跨类调用)，并在widget.cpp中new出来
>
>      ps：这样做的好处是可以使用外部类操作成员变量，如果所有的操作都进行在widget函数中，也可以不用成员变量
>
> 
>
>    * 信号连接connect
>
>      ~~~c++
>      connect(teacher, &Teacher::hungry, student, &Student::treat);
>      //将对象以及信号用connect建立联系
>      ~~~
>
>    * 信号触发
>
>      需求：
>
>      1. 下课
>      2. 老师hungry
>      3. 触发student treat
>
>      ~~~c++
>      //声名下课函数
>      //在widget.h中public下
>      void ClassIsOver();
>      //在widget.cpp中实现
>      void Widget::ClassIsOver()
>      {
>          emit teacher -> hungry;//触发自定义signals专用emit
>      }
>                                                  
>      //以上即读取到下课时触发老师hungry信号，那么学生运行treat槽函数
>      ~~~
>
>      较为完整代码如下：
>
>      ~~~c++
>      #include "ui_widget.h"
>                                                  
>      Widget::Widget(QWidget *parent)
>          : QWidget(parent)
>          , ui(new Ui::Widget)
>      {
>          ui->setupUi(this);
>          tc = new Teacher(this);//在这里使用Teacher tc = new Teacher会发生什么呢
>          sd = new Student(this);//这里的this是为了自动释放内存
>          connect(tc, &Teacher::hungry, sd, &Student::treat);//下面信号重写部分会修改这里的参数
>          ClassisOver();
>      }
>                                                  
>      void Widget::ClassisOver()
>      {
>          emit tc->hungry();
>      
> }
>
> ```c++
> //尝试自写信号
> //人题狗 狗叫
> //成功
> ```
>
> * ### 信号方法的重 写(同名不同参可以同时存在) ###
>
>   此时使用 _函数指针_  来选择指向带参的重写
>
>   ~~~C++
>   //当signals下和public slots下只声名了一个方法时可以这么写
>   connect(tc, &Teacher::hungry, sd, &Student::treat);
>   
>   //当这些方法被重写时，如：
>   signals:
>   void hungry();
>   void hungry(QString xxx);//同名不同参
>   
>   public slots:
>   void treat();
>   void treat(QString xxx);
>   //===============================
>   //此时就要构造函数指针 
>   ~~~
>
>   _函数指针指向函数地址_
>
>   > * 定义规则：
>   >
>   >   返回值类型 + （作用域 :: *  指针名）+  （参数类型）
>   >
>   >   ~~~c++
>   >   void (Teacher:: *teachersignals)(QString) = &Teacher::hungry;
>   >   //声名一个指向参数为QString类型方法的指针，将对应类型的hungry方法地址赋给此指针
>   >   //同理
>   >   void (Student:: *studentslots)(QString) = &Student::treat;
>   >   //此时connect中的指针就要改写
>   >   connect(people, teachersignals, dog, studentslots);//信号中的参数也会提供给槽函数 
>   >                       
>   >   {
>   >       emit teacher -> hungry("宫保鸡丁");//触发hungry(QString xxx)
>   >                                         //并将"宫保鸡丁"传给treat(QString xxx)
>   >   }
>   >                       
>   >   //此时
>   >   void Student::treat(QString xxx)
>   >   {
>   >       qDebug()<< xxx ; 
>   >   }
>   >   //输出 "xxx"
>   >   ~~~
>   >
>   >   
>   >
>   > * QSstring转化为char * （"xxx" 转为 xxx）
>   >
>   >   Qt自带API
>   >
>   >   ~~~c++
>   >   xxx.toUtf8().data();
>   >   //.toUtf8将QString类型转为字节数组
>   >   //.data()将字节数组转为char *
>   >   ~~~
>   >   
>   >   
>
> * ### 信号和槽断开 ###
>
>   disconnect()
>
>   ~~~c++
>   disconnect(A, B, C, D);
>   ~~~
>
>   
>
> * ### 信号连接信号 ###
>
>   ~~~C++
>   connect(A, As, B, Bs);
>   //连锁触发
>   ~~~
>
> * ### 一个信号可以连接多个槽（槽方法的执行顺序时随机的） ###
>
> * ### 多个信号可以连接同一个槽
>
> * ### 信号和槽参数一一对应
>
> * ### 信号参数数量可以多于槽参数
>
>   ~~~c++
>   void (Teacher:: *teachersignals)(QString, int) = &Teacher::hungry;
>   void (Student:: *studentslots)(QString) = &Student::hungry;
>   //这样的信号和槽是可以连接的
>   ~~~
>
>   尝试简化以下流程：
>
>   无参信号1 —— 无参槽1 —— 触发信号2并传参 —— 带参信号2 —— 带参槽3
>
>   为：
>
>   无参信号1——带参信号2——带参槽3（无参信号和带参信号不对应！）
>
>   ~~~c++
>   //目前搞不定
>   //学完lambda表达式就可以了
>   //无参信号——lambda表达式{emit tc->hungry("xxx")}
>   ~~~
>
>   
>
> * ### QT4版本的信号和槽
>
>   ~~~C++
>   connect(tc, SIGNAL(hungry(QString)), sd, SLOT(treat(QString)));
>   //好处：不需要写指针函数直接调用重写方法
>   //坏处：参数类型不检测，无法实现：
>   void (Teacher:: *teachersignals)(QString, int) = &Teacher::hungry;
>   void (Student:: *studentslots)(QString) = &Student::hungry;
>   //更推荐新版本的写法
>   ~~~
>
>   

## lambda表达式

>* 规则
>
>  ~~~C++
>  // [函数对象参数](操作符重载函数参数)mutable -> 返回值{方法体}
>  //lambda表达式本质上是一个方法名(所以是一个指针类型)
>  ~~~
>
>  1. 对象参数
>
>     * [=]，使函数体可以使用所有可见的局部变量 (值传递：拷贝一份，_不能改变外部变量的值_)
>     * [&]，同上（引用传递：直接用原来的，_可以修改外部变量的值_ ）
>     * [this]，[=]的子集
>     * [a]，只值传递a
>     * [&a]，只引用传递a
>     * [=,&a]，除a引用传递，其他都值传递
>     * .........
>
>  2. mutable关键字
>
>     * 加上mutable修饰符以后，可以修改值传递的拷贝，不会影响外部变量本身
>
>     * ### 没有mutable关键字时值传递是不能修改的
>
>  3. -> 返回值
>
>     ~~~c++
>     int n = 10;
>     n = []()->int{ return 100000;}();
>     //可以这样修改变量值
>     ~~~
>
>  4. 简化connect写法
>
>     在信号接收者是this时可以省略this
>
>     ~~~c++
>     connect(A,B,[])
>     ~~~



# QMainWindow

## 菜单栏

>~~~c++
>#include<QMenuBar>//头文件
>//==============================
>	QMenuBar *bar = menuBar();//因为QMenuBar在MainWindow下是静态类，不需要new
>    	setMenuBar(bar);//将bar设置到本窗口上，
>    	QMenu * fileMenu = bar->addMenu("File");//在bar下创建File菜单，并将返回指针接收
>    	QAction *NewAction = fileMenu->addAction("NewAction");//在File菜单下创建NewAction菜单项
>	fileMenu->addSeparator();//添加分隔线
>    	QAction *NewAction2 = fileMenu->addAction("NewAction2");
>~~~
>
><img src="C:\Users\mohua\Desktop\Markdown\QQ截图20210701232537.png" alt="QQ截图20210701232537" style="zoom:50%;" />
>
>

## 工具栏

>~~~c++
>#include <QToolBar>
>	QToolBar *toolBar = new QToolBar(this);//标准的实例化对象
>	addToolBar(Qt::LeftToolBarArea,toolBar);//Qt::枚举值，表示初始化默认在左边，未定义则默认Qt::TopToolBarArea
>	toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea); //限定只在左右停靠
>	toolBar->setFloatable(false);//不允许在窗口浮动
>	toolBar->setMovable(false);//动都不给动
>	toolBar->addWidget(xxx);//xxx可以是菜单项，按钮等k
>~~~
>
>![QQ截图20210701233540](C:\Users\mohua\Desktop\Markdown\QQ截图20210701233540.png)
>
>

## 状态栏 +  标签

> ~~~C++
> #include <QStatus>
> #include <QLabel>
> 	QStatusBar *status = statusBar();//和菜单栏同理
> 	setStatusBar(status);
> 
> 	QLabel *label = new QLabel("xxx",this);//类似于实例化按钮
>     QLabel *label2 = new QLabel("yyy",this);
>     status->addWidget(label);//左侧信息
>     status->addPermanentWidget(label2);//右侧信息
> 
> 
> ~~~

## 铆接部件（相对于核心部件）

> 
>
> ~~~C++
> #include <QDockWidget>
> 	QDockWidget *doc = new QDockWidget("Doc",this);
>     addDockWidget(Qt::BottomDockWidgetArea,doc);//和toolBar类似的操作方式
> //但是在没有核心部件的情况下Qt::BottomDockWidgetArea是无法体现出效果的
> //所以尝试创建一个TextEdit核心
> #include <QTextEdit>
> 	QTextEdit *txt = new QTextEdit(this);
>     setCentralWidget(txt);//创建窗口的核心部件
> //同样可以使用setAllowedArea()，setFloatable()，setMovable()等方法限定
> ~~~
>
> ![QQ截图20210702133557](C:\Users\mohua\Desktop\Markdown\QQ截图20210702133557.png)
>
> _核心部件一个窗口只能有一个_
>
> _使用add添加的可以有多个，set添加的一般只有一个_
>
> 

## UI界面

> * ### 给控件添加图标
>
>   ~~~C++
>   ui->setupUi(this);
>   ui->menuNew->setIcon(QIcon("/home/qt-mod/Pictures/QtIcon/test.png"));//硬盘路径下
>   //其中menuNew是在ui界面中手动新建的菜单项名称，使用菜单项下的setIcon方法设置图片路径出现以下效果
>   ~~~
>
>   ![QQ截图20210702162909](C:\Users\mohua\Desktop\Markdown\QQ截图20210702162909.png)
>
>   ~~~C++
>   ui->menuNew->setIcon(QIcon(":/QtIcon/test.png"));//在资源文件.qrc下 "： + 前缀名 + 文件名"
>   ~~~
>
> * ### 点击控件弹出对话框Dialog
>
>   ~~~C++
>   //代码测试菜单项响应    
>   connect(ui->actionNew,&QAction::triggered,[=](){
>           qDebug()<<"test";
>       });//triggered信号用于菜单项被激活时
>   ~~~
>
>   #### 模态对话框：不可操作其他窗口
>
>   ~~~c++
>   #include <QDialog>
>   connect(ui->actionNew,&QAction::triggered,[=](){
>     
>           qDebug()<<"test";
>   //        QDialog dlg(this);
>   //        dlg.resize(100,100);
>   //        dlg.exec();
>       //指针的两种写法
>           QDialog *dlg = new QDialog(this);
>           dlg->resize(200,100);
>           dlg->exec();
>   }；
>   ~~~
>
> 
>
>   #### 		非模态对话框：可操作其他窗口
>
>   ~~~c++
>       connect(ui->actionNew,&QAction::triggered,[=](){
> 
>   //        qDebug()<<"test";
>   //        QDialog dlg(this);
>   //        dlg.resize(100,100);
>   //        dlg.show();
>        //上一种写法会导致窗口一闪而过
>        //因为没有实例化导致函数运行结束之后会直接消失
>        //所以就需要下面实例化的方法
>           QDialog *dlg = new QDialog(this);
>           dlg->resize(200,100);
>           dlg->show();
>           dlg->setAttribute(Qt::WA_DeleteOnClose);//释放内存，因为每次都会新建一个
> 
>       });
>   ~~~
>
> * ### 标准对话框QMessageBox
>
>   ~~~c++
>   //错误对话框
>   #include <QMessage>
>       connect(ui->actionNew,&QAction::triggered,[=](){
>           QMessageBox::critical(this,"Error","critical");//弹出标题为Error文本为critical的标准对话框
>           QMessageBox::information(this,x,x);
>           QMessageBox::warning(this,x,x);
>       });
>   ~~~
>
>   ~~~c++
>   QMessageBox::question(this,x,x,x,x,x);
>   if(QMessageBox::Save == QMessageBox::question(this,"x","x",QMessageBox::Save | QMessageBox::No | QMessageBox::No)){
>               qDebug()<<"test1";
>           }
>   else if(QMessageBox::No == QMessageBox::question(this,"x","x",QMessageBox::Save | QMessageBox::No | QMessageBox::No)){
>               qDebug()<<"test2";
>           }//这个可以判断点击哪个按钮被按了
>
>   if(QMessageBox::Save == QMessageBox::question(this,"x","x",QMessageBox::Save | QMessageBox::No | QMessageBox::No)){
>               qDebug()<<"test2";
>           }
>   else{
>               qDebug()<<"test3";
>           }//简化
>   ~~~
>
> * ### 文件对话框
>
>   ~~~c++
>   #include <QFileDialog>
>   QFileDialog::getOpenFileName(this,"open","/home/qt-mod",(*.doc));//只显示.doc文件
>   //QFileDialog返回一个QString值，存储打开文件的路径
>   ~~~
>
> * ### 颜色对话框
>
>   ~~~C++
>   #include <QColorDialog>
>   QColor color = QColorDialog::getColor(QColor());//QColor内可以指定打开的yan    
>   qDebug()<<color.rgba();
>   ~~~
>
> * ### 字体对话框
>
>   ~~~C++
>   #include <QFontDialog>
>   bool ok;//判断有没有这个字体再字体库
>   QFont font = QFontDialog::getFont(&ok,QFont());//QFont内可以指定打开的默认字体及属性
>   ~~~
>
> * ### 按钮组 + 按钮信息捕获
>
>   ~~~c++
>       ui->radioButton->setChecked(true);
>       connect(ui->radioButton,&QRadioButton::clicked,[=](){
>           qDebug()<<"test";
>       });
>   ~~~
>
> * ### QListWidget
>
>   ~~~C++
>       QListWidgetItem *item = new QListWidgetItem("hhh");//QListWidget的每个项都叫QListWidgetItem
>       ui->listWidget->addItem(item);
>       item->setTextAlignment(Qt::AlignCenter);//单行设置可以设置对齐
>       QStringList list;
>       list << "a" <<"b";
>       ui->listWidget->addItems(list);//不能设置对齐
>   ~~~
>
> 
>
>
> ![QQ截图20210703001904](C:\Users\mohua\Desktop\Markdown\QQ截图20210703001904.png)
>
> * ### QTreeWidget（树状）
>
>   ~~~c++
>       ui->treeWidget->setHeaderLabels(QStringList()<< "Legence" << "Introduce");
>   //可以用nameList[i]或nameList.at(i)来访问QStringList内的某个项
>       QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"Power");
>       QTreeWidgetItem *item2 = new QTreeWidgetItem(QStringList()<<"2");
>       ui->treeWidget->addTopLevelItem(item);
>       item->addChild(item2);
>   ~~~
>
> 
>
>   ![vmware_cAnoYkaQtN](C:\Users\mohua\Desktop\Markdown\vmware_cAnoYkaQtN.png)
>
>   * ### QTableWidget（表格状）
>
>     ~~~c++
>     //暂时跳过
>     ~~~
>
>   * ### 其他控件
>
>     1. Scroll Area
>
>     2. QToolbox
>
>     3. TabWidget
>
>     4. Stacked Widget（翻页窗口）
>
>     5. Combo Box
>
>     6. 用QLabel显示图片，动图movie
>
>        ~~~c++
>            QMovie *movie = new QMovie(":/Gif/run.gif");
>            ui->label->setMovie(movie);
>            movie->setScaledSize(QSize(100,200));
>            movie->start();
>        ~~~
>
> * ### 自定义控件封装
>
>   1. 新建Qt设计师界面类，生成一套.h .cpp .ui文件![vmware_8AVPvNkYNV](C:\Users\mohua\Desktop\Markdown\vmware_8AVPvNkYNV.png)
>
>   2. 在新建的类ui上操作![vmware_5RPbpS3RCh](C:\Users\mohua\Desktop\Markdown\vmware_5RPbpS3RCh.png)
>
>   3. 在widget.ui中创建一个Widget窗口，右键提升为新建的类，这个窗口就是封装好的控件![vmware_F7aFzTQVAf](C:\Users\mohua\Desktop\Markdown\vmware_F7aFzTQVAf.png)
>
>      ~~~c++
>      //封装一个spinBox和Slider控件    
>      void (QSpinBox:: *spinSignals)(int) = &QSpinBox::valueChanged;
>      connect(ui->spinBox,spinSignals,ui->horizontalSlider,&QSlider::setValue);
>      connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
>      ~~~
>
>      ![vmware_MgexkCqg4r](C:\Users\mohua\Desktop\Markdown\vmware_MgexkCqg4r.png)
>
>      ### _相当于一个UI子类_

## 事件处理

>* ### 将ui中控件提升为自己写的类
>
> 在之前自定义类的基础上多一步在ui界面的提升操作
>
> _事件的捕获在默认类中是不允许的_
>
> _但在自己写的类中可以重写实现捕获_
>
>* ### 捕获鼠标进入 鼠标离开
>
> ~~~c++
> //在NewLabel.h下
> public：
> 	void enterEvent(QEvent *);    
> 	void leaveEvent(QEvent *);
> //在cpp下写
> void NewLabel::enterEvent(QEvent *)
> {
>     qDebug()<< "test1";
> }
> void NewLabel::leaveEvent(QEvent *)
> {
>     qDebug()<< "test2";
> }
> ~~~
>
>* ###  捕获鼠标移动 + QString占位符写法
>
> ~~~C++
> void NewLabel::mouseMoveEvent(QMouseEvent *ev)
> {
>     QString str = QString("x = %1, y = %2").arg(ev->x()).arg(ev->y());
>     int x=(ev->x()),y=(ev->y());
>     qDebug()<<x<<" "<<y;
>     qDebug()<<str << endl << "----------";
> }
> //鼠标移动状态判断法
> void NewLabel::mouseMoveEvent(QMouseEvent *ev)
> {
>     if(ev->buttons() == Qt::LeftButton){
>     QString str = QString("x = %1, y = %2").arg(ev->x()).arg(ev->y());
>     int x=(ev->x()),y=(ev->y());
>     qDebug()<<x<<" "<<y;
>     qDebug()<<str << endl << "----------";
>     }
> }
> //mousePressedEvent和mouseReleasedEvent操作类似
> //ev->button()返回坐标
> //ev->buttons()返回移动范围
> ~~~
>
>* ### 定时器事件
>
> ~~~c++
> //widget函数下
> startTimer(1000);
> //public声名后
> void Widget::timerEvent(QTimerEvent *)
> {
>     static int n = 1;//在只初始化一次
>     ui->label->setText(QString::number(n++));
> }
> 
> //如果存在多个定时器
>     id1 = startTimer(1000);
>     id2 = startTimer(2000);//定义成员变量
> 
> void Widget::timerEvent(QTimerEvent *e)
> {
>     if(e->timerId() == id1){
>     static int n = 1;
>     ui->label->setText(QString::number(n++));
>     }
>     else if(e->timerId() == id2){
>     static int m = 1;
>     ui->label_2->setText((QString::number(m++)));
>     }
> }
> 
> ~~~
>
>

