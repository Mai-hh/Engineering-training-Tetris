#ifndef SETTINGPUSHBTN_H
#define SETTINGPUSHBTN_H

#include <QPushButton>

class SettingPushBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit SettingPushBtn(QWidget *parent = nullptr);

    //构造函数 参数1 正常显示的图片路径  参数2   按下后的图片路径
    SettingPushBtn (QString normalImg,QString pressImg = "");

    //成员属性  保存正常状态下的按钮图片路径
    QString normalImgPath;
    QString presssImgPath;

    //弹跳的特效
    void zoom1();
    void zomm2();

signals:

public slots:
};

#endif // SETTINGPUSHBTN_H
