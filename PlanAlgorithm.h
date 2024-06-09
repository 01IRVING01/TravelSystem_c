#ifndef STRATEGY_H
#define STRATEGY_H

#include "Graph.h"
#include "Plan.h"
#include "DayTime.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QtSql>
#include <QMessageBox>

#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>

using std::string;


class PlanAlgorithm
{
public:
    /* 构造函数 */
    PlanAlgorithm(int t, QString src, QString dst, DayTime departTime, DayTime expectedDestT);
    PlanAlgorithm(int t, QString src, QString dst, QStringList cities,vector<int> hours,DayTime departTime, DayTime expectedDestT,int Budge);
    ~PlanAlgorithm();

    /* 需要与其他类交互的数据结构 */
    DayTime departTime;              // 出发时间
    DayTime arrivalTime;                // 到达时间
    DayTime earliestDepartTime;      // 期望的出发时间
    QStringList passCities;
    vector<int> passHours;          // 途经城市停留时间，不计入算法，因为所有路径都等待相同时间
    QString depart;
    QString dest;
    int strategy;
    int budge;
//    Plan plan;

    Plan getPlan();
    // 两个城市直达方案
    Plan directPlan(int strategyType, QString src, QString dst, DayTime scheduledDepartT);
    // 直达方案分类
    Plan directFastestPlan(QString src, QString dst, DayTime scheduledDepartT);
    Plan directCheapestPlan(QString src, QString dst, DayTime scheduledDepartT);

    Plan singlePlan(int strategyType); // 单一策略：1.最少时间 2.最少费用


private:
    QSqlDatabase db;
};

#endif // STRATEGY_H
