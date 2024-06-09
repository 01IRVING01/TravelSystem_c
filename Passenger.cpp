#include "Passenger.h"


Passenger::Passenger()
{

}

void Passenger::setPlan(QString start, QString dest, QStringList Cities, vector<int> Hours, DayTime startTime, DayTime endTime, int strategyType, int Budge)
{
    begin = start;
    end = dest;
    budge = Budge*1000;
    passCity = Cities;
    passHours = Hours;
    strategy = strategyType;
    earliestDepartTime = startTime;
    latestArrivalTime = endTime;
}

void Passenger::getPlan()
{
    planAlgorithm = new PlanAlgorithm(strategy, begin, end, passCity, passHours, earliestDepartTime, latestArrivalTime, budge);
    plan = planAlgorithm->getPlan();
}

//QString Passenger::getDepart() {
//    return begin;
//}

//QString Passenger::getDest() {
//    return end;
//}

//int Passenger::getStrategy() {
//    return strategy;
//}


//QString Passenger::getLog() {
//    return log;
//}
