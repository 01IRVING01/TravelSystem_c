#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "PlanAlgorithm.h"
#include "Passenger.h"
#include "City.h"
#include <QSet>
#include <QDate>
#include <QDebug>
#include <QQueue>
#include <QTimer>
#include <QString>
#include <QPainter>
#include <QDateTime>
#include <QLineEdit>
#include <QInputDialog>
#include <QTextStream>
#include <QMainWindow>
#include <QMessageBox>
#include <QStringList>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <cmath>
#include <queue>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void paintMap();
    void mapPaint();
    void initCityPoint();

    void setUiDefault();


private slots:
    void changeDepartCity();
    void changeBudget();
    void changePassenger();
    void on_addPassenger_clicked();
    void on_removePassenger_clicked();

    void on_addCity_clicked();
    void on_removeCity_clicked();
    void changeTravelStatus();
    void on_strategyBox_currentIndexChanged(int index);
    void on_planButton_clicked();
    void on_simButton_clicked();
//    void on_pauseButton_clicked();
    void on_changePlanButton_clicked();

    void on_speedSlider_valueChanged();

private:
    Ui::MainWindow *ui;
//    QList<QString> addedCities;
//    QString departCity;
//    QString destCity;
    QStringList cityList = {"北京", "上海", "广州" , "深圳", "成都", "杭州", "重庆", "武汉", "南京", "郑州", "西安", "青岛"};
    QStringList cityFeatures = {"啤酒文化","三峡风光","国宝熊猫","先秦文物","佛教文化","国父-孙中山","浪漫樱花","龙井茶园",
                                "华侨创意园","粤剧文化","江南园林","长城","火锅文化","红岩革命纪念","帆船运动","大唐文化","黄帝故里",
                                "缅怀抗日历史","黄鹤一去不复返，白云千载空悠悠","西子湖畔","大芬油画村","黄浦江畔","宫殿建筑","川剧",
                                "长江索道","海底世界","大雁塔","黄河魅力","楚文化","大宋文化","科技产业园","碉楼古村","迪斯尼乐园","奥林匹克公园"};
    QStringList Budget ={"1000","2000","3000","4000","5000","6000","7000","8000","9000"};
    QStringList strategyList = {"头等规划", "经济规划"};
    QPointF cityPoint[12];
    QTimer *qtimer;

    vector<Passenger> psgList; // 乘客名单
    int Idx; // 当前乘客序号
    QDateTime sysTime; // 系统时间
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWINDOW_H
