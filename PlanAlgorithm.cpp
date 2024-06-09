#include "PlanAlgorithm.h"
//这些是预定义的常量。它们在算法中用于比较和初始值设置。
#define MAX_RISK 999999//用于表示最大风险值、
#define MAX_PATH_TIME 9999//最大路径时间
#define MAX_MONEY 32767//最大费用

using std::set;
using std::stack;
using std::cout;
using std::endl;

//该构造函数的主要作用是将输入的参数值存储在对象的成员变量中，并建立与SQLite数据库的连接，以供后续的行程规划算法使用。
PlanAlgorithm::PlanAlgorithm(int t, QString src,QString dst, QStringList cities, vector<int> hours, DayTime scheduledDepartT, DayTime expectedDestT,int Budge)
{
    budge =Budge;//Budge：预算金额
    strategy = t;//t：策略类型
    depart = src;//src：出发城市
    dest = dst;//dst：目的地城市
    passCities = cities;//cities：途径城市列表
    passHours = hours;//hours：途径城市所需的停留时间列表
    departTime = scheduledDepartT;//scheduledDepartT：计划出发时间
    earliestDepartTime = scheduledDepartT;//expectedDestT：最早到达时间
    // sqlite数据库
    db = QSqlDatabase::addDatabase("QSQLITE");//创建一个 SQLite 数据库连接对象。
    QString dbPath = QDir::currentPath() + QString("/TimeTable.db");//构建数据库文件的路径。
    db.setDatabaseName(dbPath);//设置数据库连接对象的数据库文件名。
    qDebug() << dbPath;//输出数据库文件的路径。
    if (!db.open())//尝试打开数据库连接，如果连接失败，则输出错误消息 "Failed to connect to database"。
        cout << "Failed to connect to database";
}
//这是PlanAlgorithm类的析构函数。它的主要作用是关闭SQLite数据库连接。
PlanAlgorithm::~PlanAlgorithm()
{
    // sqlite数据库
    db.close();
}

//这是PlanAlgorithm类的一个公有成员函数，用于获取规划的旅行计划。它根据策略类型选择相应的规划算法，并返回计划结果。
Plan PlanAlgorithm::getPlan()
{
    switch (strategy) {
        case 1:
        default:
            return singlePlan(strategy);

        }
}
//用于根据策略类型选择直达路径的规划算法，并返回计划结果。
Plan PlanAlgorithm::directPlan(int strategyType, QString src, QString dst, DayTime scheduledDepartT)
{
    switch (strategyType) {
        case 1:
            return directFastestPlan(src, dst, scheduledDepartT);
        default:
            return directCheapestPlan(src, dst, scheduledDepartT);
    }
}

// 算法辅助函数,这是一个辅助函数，用于在字符串向量v中查找字符串str的索引。如果找到，返回索引值；如果未找到，返回-1。
long findIndex(vector<QString> v, QString str)
{
    for (unsigned int i = 0; i < v.size(); i++)
        if (v[i] == str)
            return i;
    return -1;
}

// 直达，最少时间
// 采用深度优先搜索算法结合回溯算法，遍历所有有效路径，从中选出用时最小的路径
//函数directFastestPlan接受源城市（src）、目标城市（dst）和预定出发时间（scheduledDepartT）作为输入，并返回一个表示最快路径的Plan对象。
Plan PlanAlgorithm::directFastestPlan(QString src, QString dst, DayTime scheduledDepartT)
{
//    qDebug() << "搜索直达，最少时间算法：" << src + "->" + dst;
    // 读取sqlite数据库
    QSqlQuery query(db);//连接到SQLite数据库
    query.exec("select * from timeTable");//执行一个查询来获取时刻表信息。

    // 读取城市列表
    vector<QString> cityList;
    set<QString> citySet;
    QString str;
    while (query.next()) {
        str = query.value("begin").toString();
        citySet.insert(str);
    }
    for (set<QString>::iterator iter = citySet.begin(); iter != citySet.end(); iter++) {
        cityList.push_back(*iter);
    }

    // 数据结构
    stack<QString> s;                // 策略二算法运行时记录路径的栈
    QString top;                     // 栈顶元素
    long n;                         // 临时存储序号
    QString next;                    // 需要访问的下一个元素
    int count = 0;                  // 记录找到的所有路径的个数
    QString tempCity;                // 临时存储元素
    stack<QString> tempS;            // 临时存储栈，便于提取栈中元素且不破坏原栈内容
    vector<QString> tempRoute;    // 临时存储找到的路径
    vector<QString> bestPath;        // 存储找到的最佳路径
    DayTime minscheduledDepartTime(10000, 10000, 10000); // 存储迭代过程中的最小到达时间
    unsigned long cityNum = cityList.size();// 存储城市个数
    bool **visited = new bool*[cityNum]; // 访问数组，visited[i][j]，第一列表示i是否走过，其余表示i之后j是否走过。
    for (unsigned long i = 0; i < cityNum; i++) {//循环遍历城市的索引，从0到cityNum-1。
        //为每个城市创建一个布尔数组，其中包含 cityNum + 1 个元素。这个额外的元素是用来标记该城市之后的所有城市是否被访问过。
        visited[i] = new bool[cityNum + 1];
        //循环遍历每个城市后面的城市的索引，从0到cityNum。
        for (unsigned long j = 0; j < cityNum + 1; j++)
            visited[i][j] = false;//将布尔数组中的元素初始化为 false，表示城市 i 后面的城市 j 尚未被访问过。
    }

    // 提高算法的运算效率，将终点放到前面来，以便先行入栈
    long destIndex = findIndex(cityList, dst);
    QString temp = cityList[0];
    cityList[0] = dst;
    cityList[destIndex] = temp;

    // 初始化 resPlan
    Plan resPlan;
    // 算法运算部分
    s.push(src);                                 // 出发地先行入栈
    visited[findIndex(cityList, src)][0] = true; // 已访问出发地
    // 搜索所有路径，并根据进行情况回溯
    while(!s.empty())
    {
        top = s.top();//将栈顶元素赋值给变量 top，表示当前处理的城市。
        // 找到了一条从起点到终点的路径
        if (top == dst)
        {
            count++;
            // 临时存储一个结果
            Plan tempPlan;//创建一个临时的路径规划对象 tempPlan，并初始化其属性。
            tempPlan.risk = 0;
            tempPlan.timeCost.day = 0;
            tempPlan.timeCost.hour = 0;
            tempPlan.timeCost.minute = 0;
            tempPlan.moneyCost = 0;
            tempPlan.route.clear();
            bool feasible = true;

            // 记录到达当前结点时的最佳时间
            DayTime scheduledDepartTime = scheduledDepartT;
            DayTime currentTime;

            // 产生调试信息：搜索出的一条路径
            // 并产生一个临时的 tempPlan
            tempRoute.clear();
            tempS = s;
            //std::cout << count << ": ";
            while (!tempS.empty()) {
                tempCity = tempS.top();//将临时栈顶的城市名称赋值给变量 tempCity，表示当前处理的城市。
                tempS.pop();//将临时栈顶的城市弹出，实现出栈操作。
                tempRoute.push_back(tempCity);//将当前处理的城市名称存储到临时路径
            }
            std::reverse(tempRoute.begin(), tempRoute.end());//将临时路径 tempRoute 中的元素进行反转，实现路径的正序存储（从起点到目的地）
            for (vector<QString>::iterator it = tempRoute.begin(); it != tempRoute.end() - 1; it++) {
                currentTime = scheduledDepartTime;//将出发时间赋值给当前时间 currentTime，以便进行时间的计算。
                currentTime.day = 0;//将当前时间的日期部分设置为0，以确保后续计算的时间差仅考虑小时和分钟。
                Path minPath;//创建一个临时存储路径信息的对象 minPath，用于记录找到的最佳路径。
                Path tempPath;//创建一个临时存储路径信息的对象 tempPath，用于临时存储遍历过程中的路径信息。
                minPath.endTime.day = MAX_PATH_TIME;//将最佳路径的结束时间的日期部分初始化为一个较大的值，用于后续比较。

                // 遍历两城市之间的时刻表
                bool flag = false;  // 判断是否有找到，如果没有，天数++
                //执行 SQL 查询语句，根据当前城市 *it 和下一个城市 *(it + 1) 的名称，在 TimeTable 数据表中查询符合条件的行。
                query.exec(QString("select * from TimeTable where begin='%1' and end='%2'").arg(*it).arg(*(it + 1)));
                while (query.next()) {
                    //从查询结果中获取开始时间，并将其转换为 DayTime 对象赋值给 tempPath.beginTime。
                    tempPath.beginTime.fromString(query.value("beginTime").toString());
                    if (tempPath.beginTime > currentTime) {//比较开始时间和当前时间的大小，如果开始时间晚于当前时间，则执行以下操作。
                        flag = true;//将 flag 设置为 true，表示找到了满足条件的路径。
                        //从查询结果中获取时间花费，并将其转换为 DayTime 对象赋值给 tempPath.timeCost。
                        tempPath.timeCost.fromString(query.value("timeCost").toString());
                        //的日期部分设置为出发时间的日期部分，以保持日期的一致性。
                        tempPath.beginTime.day = scheduledDepartTime.day;
                        //计算路径的结束时间，即开始时间加上时间花费，赋值给 tempPath.endTime。
                        tempPath.endTime = tempPath.beginTime + tempPath.timeCost;
                        if (tempPath.endTime < minPath.endTime) {//如果当前路径的结束时间早于最佳路径的结束时间，则执行以下操作。
                            minPath.endTime = tempPath.endTime;//将当前路径的结束时间赋值给 minPath.endTime，更新最佳路径的结束时间。
                            minPath.number = query.value("number").toString();//从查询结果中获取路径编号，并赋值给 minPath.number，记录最佳路径的编号。
                            minPath.beginTime = tempPath.beginTime;//将当前路径的开始时间赋值给 minPath.beginTime，记录最佳路径的开始时间。
                            minPath.waitTime = minPath.beginTime - scheduledDepartTime;//计算等待时间，即最佳路径的开始时间与出发时间的差值，赋值给 minPath.waitTime。
                            minPath.timeCost = tempPath.timeCost;//将当前路径的时间花费赋值给 minPath.timeCost，记录最佳路径的时间花费。
                            minPath.endTime = minPath.beginTime + minPath.timeCost;//重新计算最佳路径的结束时间，确保时间的一致性。
                            minPath.moneyCost = query.value("moneyCost").toInt();//从查询结果中获取路径的费用，并将其转换为整型赋值给 minPath.moneyCost，记录最佳路径的费用。
                            minPath.vehicle = query.value("vehicle").toString(); //计算路径的风险值，根据路径的时间花费、等待时间、交通工具风险和起点城市风险进行加权求和，赋值给 minPath.risk，记录最佳路径的风险值。
                        }
                    }
                }
                // 没有找到
                if (!flag) {
                    if (!feasible) { // 第二次搜索无果，代表该路径不可行
                        scheduledDepartTime.day = MAX_PATH_TIME;//将出发时间的天数设置为一个较大的值，表示该路径不可行。
                        break;
                    }
                    scheduledDepartTime.day += 1;//将出发时间的天数加1，进行下一天的搜索。
                    scheduledDepartTime.hour = 0;
                    scheduledDepartTime.minute = 0;
                    it--;//将迭代器 it 向前移动一步，以便重新检查上一对城市。
                    feasible = false;//将 feasible 设置为 false，表示第二次搜索仍然没有找到满足条件的路径。
                }
                // 找到了，向 tempPlan 中加入此条路径
                else {
                    scheduledDepartTime = minPath.endTime;//更新出发时间为当前路径的结束时间，以便继续搜索下一段路径。
                    minPath.begin = *it;//将当前路径的起点城市赋值给 minPath.begin。
                    minPath.end = *(it + 1);//将当前路径的终点城市赋值给 minPath.end。
                    tempPlan.moneyCost += minPath.moneyCost;//将当前路径的费用累加到临时计划 tempPlan 的总费用上。
                    tempPlan.timeCost = scheduledDepartTime - scheduledDepartT;//计算临时计划的总时间花费，即出发时间与计划的出发时间之差。
                    tempPlan.risk += minPath.risk;//将当前路径的风险值累加到临时计划的总风险上。
                    tempPlan.route.push_back(minPath);//将当前路径加入临时计划的路径列表中。
                }
            }
            // 更新最优值
            if (scheduledDepartTime < minscheduledDepartTime) {//如果当前计划的出发时间早于最优计划的出发时间。
                minscheduledDepartTime = scheduledDepartTime;//更新最优计划的出发时间为当前计划的出发时间。
                bestPath = tempRoute;//将当前路径作为最优计划的最佳路径。
                resPlan = tempPlan;//将临时计划赋值给最优计划，更新最优计划的相关信息。
            }
            // 回溯，搜索吓一条路径
            s.pop();//从栈中弹出当前城市，回溯到上一个城市。
            visited[findIndex(cityList, dst)][0] = false;//将目标城市的访问状态设置为未访问，以便在下一轮搜索中重新考虑该城市。
        }
        // 继续往下搜索
        else {
            for (unsigned int i = 0; i < cityList.size(); i++) {
                if (!visited[findIndex(cityList, top)][i + 1] && !visited[i][0]) {//如果当前城市和下一个城市都没有被访问过。
                    n = i;//将下一个城市的索引赋值给变量 n。
                    break;
                }
                else {
                    n = -1;//将变量 n 设置为-1，表示没有找到下一个要搜索的城市
                }
            }
            // 搜索到了下一个结点
            if (n != -1 && s.size() < 4) {//如果找到了下一个要搜索的城市，并且栈的大小小于4（路径长度限制）。
               next = cityList[n];//将下一个要搜索的城市赋值给变量 next。
               s.push(next);//将下一个要搜索的城市压入栈。
               visited[findIndex(cityList, top)][n + 1] = true;//将当前城市与下一个城市的访问状态设置为已访问。
               visited[n][0] = true;//将下一个城市的访问状态设置为已访问。
            }
            // 如果没有找到下一个结点（此方向遍历结束）或路径过长（不可能时最优解了）
            // 回溯，向另一个方向继续搜索下一条路径
            else {
               s.pop();
               for (unsigned long i = 0; i < cityNum + 1; i++)//循环遍历城市访问状态数组。
                 visited[findIndex(cityList, top)][i] = false;//将当前城市与所有邻接城市的访问状态设置为未访问。
            }
        }
    }
    // 释放内存
    for (unsigned long i=0; i < cityNum;i++)//循环遍历城市访问状态数组。
        delete[] visited[i];
    delete[] visited;
    resPlan.endTime = minscheduledDepartTime;//将最优计划的结束时间设置为计划的最佳出发时间。
    return resPlan;//返回最优计划
}

// 最少费用，直达
Plan PlanAlgorithm::directCheapestPlan(QString src, QString dst, DayTime scheduledDepartT)
{
    qDebug() << "PlanAlgorithm::directCheapestPlan";
    // 读取sqlite数据库
    QSqlQuery query(db);//创建一个 QSqlQuery 对象 query，
    query.exec("select * from timeTable");//并执行查询语句 "select * from timeTable"，从数据库中获取时间表的数据。

    // 读取城市列表
    vector<QString> cityList;//定义一个空的城市列表 cityList
    set<QString> citySet;//和一个空的城市集合 citySet。
    QString str;
    while (query.next()) {
        str = query.value("begin").toString();//使用 while 循环遍历查询结果，将每个起始城市（begin 字段）添加到 citySet 集合中，以去除重复的城市。
        citySet.insert(str);
    }
    set<QString>::iterator iter;//使用 set<QString>::iterator 迭代器遍历 citySet 集合，并将每个城市添加到 cityList 向量中。
    for (iter = citySet.begin(); iter != citySet.end(); iter++) {
        cityList.push_back(*iter);
    }

    /* 建立算法所需要的 Graph 类 */
    Graph G(cityList.size());//创建一个 Graph 类对象 G，其顶点数量为城市列表的大小，
    G.setVexsList(cityList);//并使用 setVexsList 函数将城市列表设置为 G 的顶点列表。

    // 建立费用邻接矩阵
    vector<QString>::iterator i, j;//使用两个迭代器 i 和 j 遍历城市列表中的每对不同城市（起始城市和目标城市不同）
    int value;
    QString select;
    for (i = cityList.begin(); i != cityList.end(); i++)
        for (j = cityList.begin(); j != cityList.end(); j++) {
            if (*i != *j) {//对于每对城市，首先检查它们是否相同，如果相同则跳过。
                QString s1 = *i;
                QString s2 = *j;
                //构建查询语句 select，查询起始城市和目标城市之间费用最低的一条记录，使用 order by 和 limit 子句来保证只返回最低费用的记录。
                select = QString("select * from timeTable where begin='%1' and end='%2' order by moneyCost asc limit 1").arg(s1).arg(s2);
                query.exec(select);//执行查询语句
                if (query.next()) {
                    value = query.value("moneyCost").toInt();//如果查询结果存在，从结果中提取费用值，
                    G.setDistence(*i, *j, value);//并使用 G.setDistence 函数将费用值存储在 G 的距离矩阵中。
                    QString MyTimeCost = query.value("timeCost").toString();//从结果中提取时间成本值，
                    DayTime t1;//并将其转换为 DayTime 对象 t1
                    t1.day = 0;
                    t1.hour = MyTimeCost.section(":", 0, 0).toUShort();
                    t1.minute = MyTimeCost.section(":", 1, 1).toUShort();
                    G.setTime(*i, *j, t1);
                }
                else {//如果查询结果不存在（即两个城市之间没有可用的交通方式），将最大费用值 MAX_MONEY 存储在 G 的距离矩阵中，表示不可达。
                    G.setDistence(*i, *j, MAX_MONEY);
                }
            }
        }
    qDebug() << "printMatrix:";
//    G.printMatrix();
    Plan resPlan;
    resPlan.risk = 0;
    // 调用Graph类中的Dijkstra函数，传入起始城市（src）、目的城市（dst）和resPlan对象，执行 Dijkstra 算法来计算最短路径。
    G.Dijkstra(src, dst, resPlan);    // 调用算法

    vector<Path>::iterator it;
    DayTime timeUsed;
    DayTime currentTime;
    DayTime scheduledDepartTime = scheduledDepartT; // 上一次到达时间
    // 根据Dijkstra结果重新遍历得到完整数据
    //这是一个迭代循环，遍历resPlan中的路径列表route。对于每个路径，获取起始城市和目的城市
    for (it = resPlan.route.begin(); it != resPlan.route.end(); it++) {
        QString start = (*it).begin;
        QString end = (*it).end;
//        qDebug() << "get Dij res: " << start << "->" << end << "cost: " << (*it).moneyCost;

        timeUsed = G.getTime((*it).begin, (*it).end);//这行代码调用Graph类的getTime函数，根据起始城市和目的城市获取两个城市之间的旅行时间。
        // 相同价格取乘坐时间最短的
        //这部分代码使用 SQL 查询从数据库中选择符合条件的时间表记录。具体查询条件为起始城市、目的城市和路径的费用，并按照时间成本升序排列结果。
        select = QString("select * from timeTable where begin='%1' and end='%2' and moneyCost=%3 order by timeCost asc").arg(start).arg(end).arg((*it).moneyCost);
        query.exec(select);
        query.first();//然后使用query.first()将查询结果指向第一条记录。
//这些代码从查询结果中获取各种数据，并将其存储在当前迭代的路径对象(*it)中。
        it->beginTime.fromString(query.value("beginTime").toString());
        it->number = query.value("number").toString();
        it->vehicle = query.value("vehicle").toString();
        it->timeCost.fromString(query.value("timeCost").toString());

        qDebug() << "scheduledDepartTime";
        scheduledDepartTime.print();
//这段代码处理旅程的开始时间。将预定出发时间scheduledDepartTime的日期赋值给it->beginTime.day。
        it->beginTime.day = scheduledDepartTime.day;
        // 当天无法乘车
        //如果预定出发时间晚于路径的开始时间，则将it->beginTime.day增加1，以确保旅程在正确的日期开始。
        if (scheduledDepartTime > it->beginTime) {
             it->beginTime.day++;
        }
        qDebug() << "beginTime:";
        it->beginTime.print();
//计算等待时间，即路径开始时间与上一次到达时间之间的时间间隔。
        it->waitTime = it->beginTime - scheduledDepartTime;
        qDebug() << "waitTime:";
        it->waitTime.print();

        qDebug() << "timeCost:";
        it->timeCost.print();
//计算路径的结束时间，即路径开始时间加上旅行时间。
        it->endTime = it->beginTime + it->timeCost;
        qDebug() << "endTime:";
        it->endTime.print();
        resPlan.risk += it->risk;
        resPlan.timeCost = resPlan.timeCost + it->timeCost;
        resPlan.endTime = it->endTime;
        scheduledDepartTime = it->endTime;
    }
    return resPlan;//函数返回resPlan作为最终的旅行计划。
}

void add_plan(Plan &main, Plan add)//这是一个函数定义，函数名为add_plan，接受两个参数：一个是引用类型的Plan变量main，另一个是Plan类型的变量add。
{
    main.timeCost = main.timeCost + (add.endTime - main.endTime);//将main计划的timeCost（时间成本）增加add计划的结束时间减去main计划的结束时间。
    main.endTime = add.endTime;//将main计划的结束时间更新为add计划的结束时间。
    main.moneyCost += add.moneyCost;//将main计划的moneyCost（金钱成本）增加add计划的金钱成本。
    main.risk += add.risk;//将main计划的risk（风险）增加add计划的风险。
    for (auto path : add.route)//将add计划中的每个路径（route）添加到main计划的路径中。
        main.route.push_back(path);
}

Plan PlanAlgorithm::singlePlan(int strategyType)
{
    qDebug() << "PlanAlgorithm::singlePlan: " << strategyType;//当调用singlePlan函数时，会输出一条调试信息，显示strategyType的值。这个值表示计划策略的类型。
    int cityCount = passCities.length();//这行代码声明一个整型变量cityCount，并将其赋值为passCities列表的长度。passCities是一个存储城市的列表。
    Plan resPlan;//声明一个Plan类型的变量resPlan，用于存储最终的计划结果。
    if(cityCount == 0) {//检查cityCount是否为0。如果是0，表示没有经过的城市，直接调用directPlan函数生成一个直达计划，将其赋值给resPlan。
        resPlan = directPlan(strategyType, depart, dest, earliestDepartTime);
    }
    else {
//如果cityCount不为0，表示有经过的城市。首先，调用directPlan函数生成一个从出发地到第一个经过的城市的计划，将其赋值给resPlan。
//然后，创建一个DayTime类型的变量newDepartTime，并将其初始化为(0, passHours[0], 0)，其中passHours是存储经过城市的小时数的列表。
//接着，将newDepartTime与resPlan.endTime相加，更新newDepartTime的值。
//最后，使用directPlan函数生成一个从第一个经过的城市到目的地的计划，将其赋值给lastplan。
        resPlan = directPlan(strategyType, depart, passCities.at(0), earliestDepartTime);
        DayTime newDepartTime(0,passHours[0],0);
        newDepartTime = newDepartTime + resPlan.endTime;
        qDebug() << "newDeTime:" << newDepartTime.day << ". " << newDepartTime.hour << ":" << newDepartTime.minute;
        int i = 0;
        Plan lastplan = directPlan(strategyType, passCities.at(i+1), dest, newDepartTime);

        if(cityCount > 1) {//如果经过的城市数量大于1，则进入条件块。
            for(; i < cityCount-1; i++) {//使用for循环遍历经过的城市列表，其中i是循环变量，初始值为0，每次循环结束后递增1，直到cityCount-1。
//调用directPlan函数生成从当前经过的城市到下一个经过的城市的计划，并将其赋值给middleplan。
                Plan middleplan = directPlan(strategyType, passCities.at(i), passCities.at(i+1), newDepartTime);
                //如果加上当前的计划和最后一个计划的总成本超过预算，并且策略类型等于2，则进入条件块。
                                if(resPlan.moneyCost+middleplan.moneyCost+lastplan.moneyCost > budge && strategyType==2){
                                    add_plan(resPlan, lastplan);//将最后一个计划lastplan添加到结果计划
                                    newDepartTime = resPlan.endTime + lastplan.endTime;//更新新的出发时间为当前计划的结束时间加上最后一个计划的结束时间。
                                    qDebug() << "newDeTime:";//输出调试信息，显示"newDeTime:"。
                                    newDepartTime.print();//输出新的出发时间。
                                    return resPlan;//返回结果计划。
                                }else
                                    add_plan(resPlan, middleplan);//将当前计划middleplan添加到结果计划
                                    DayTime passTime(0,passHours[i+1],0);//创建一个DayTime类型的变量passTime，用于存储经过城市的时间。
                                    newDepartTime = resPlan.endTime + passTime;//更新新的出发时间为当前计划的结束时间加上经过城市的时间。
                                    qDebug() << "newDeTime:";//输出调试信息，显示"newDeTime:"。
                                    newDepartTime.print();//输出新的出发时间。
                            }
                //生成从最后一个经过的城市到目的地的计划，并将其赋值给backplan。
                            Plan backplan = directPlan(strategyType, passCities.at(cityCount-1), dest, newDepartTime);
                            add_plan(resPlan, backplan);//将最后一个计划backplan添加到结果计划resPlan中。
                      }


        }
                    return resPlan;//最后，函数返回结果计划resPlan。
}
