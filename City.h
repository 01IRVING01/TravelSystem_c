#ifndef CITY_H
#define CITY_H

#include <QDebug>
#include <QString>
#include <QStringList>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class City {
public:
    static QStringList SelectCity(QStringList Fealist,vector<int> value,vector<int>& stayTime,QString departure);
    /* 由交互见面传来的某游客的信息 */
    QString name;                         // 城市名称
    QStringList feature;               //城市标签
    QStringList food;                  //美食
    int value = 0;                     //期望值
    int Disnum;
    /* 构造函数 */
    City(QString Fealist);

    //重载运算符 按照期望值排序
    bool operator<(const City& other) const {
           return Disnum < other.Disnum;
       }
    bool operator>(const City& other) const {
           return value > other.value;
       }
};
#endif // CITY_H


