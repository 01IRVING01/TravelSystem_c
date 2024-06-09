#include "City.h"

City::City(QString city)
{
    this->name = city;
    if(city == "北京"){
        this->Disnum = 2;
        this->feature.append("宫殿建筑");
        this->feature.append("长城");
        this->feature.append("奥林匹克公园");
        this->food.append("煎饼果子：北京的传统早餐之一，是薄薄的饼皮里夹上蛋、蔬菜、香肠或火腿的美味选择。");
        this->food.append("北京烤鸭：这是北京的传统名菜，鸭肉酥脆，肉质鲜美，可以搭配薄饼、葱丝和甜面酱一起食用，非常美味。");
        this->food.append("羊蝎子火锅：这是北京的特色火锅之一，以羊肉和蝎子为主要食材，汤底麻辣鲜香，是冬天暖身的好选择。");

    }else if (city == "上海") {
        this->Disnum = 5;
        this->feature.append("江南园林");
        this->feature.append("黄浦江畔");
        this->feature.append("迪斯尼乐园");
        this->food.append("上海粢饭糕：这是一道以糯米和肉末为主要材料的传统上海早餐，口感软糯，味道香甜。");
        this->food.append("上海菜：尝试一些正宗的上海菜，比如红烧狮子头（狮子头是一道由猪肉制作的肉丸）或葱油拌面（一种炒面条，配有葱花和调料）。");
        this->food.append("上海夜市小吃：在上海的夜市中，你可以找到各种美味的小吃，比如生煎包、炸鸡爪、炒年糕等。这是体验当地美食文化的好机会。");
    }else if(city == "广州"){
        this->Disnum = 7;
        this->feature.append("粤剧文化");
        this->feature.append("湿地公园");
        this->feature.append("碉楼古村");
        this->food.append("早茶：广州是著名的早茶之都，您可以品尝到各种精美的早茶点心，如流沙包、肠粉、虾饺等。推荐的地点有陶陶居、點點心意粉店等。");
        this->food.append("广州炳胜餐厅：这是一家有着悠久历史的餐厅，以传统粤菜著称。您可以尝试他们的烧味拼盘、白切鸡、清蒸鱼等经典菜品。");
        this->food.append("广东粤菜以广州菜为代表，是中国八大菜系之一。你可以去一家正宗的粤菜餐厅，品尝粤菜的精髓。广东粤菜以清淡、鲜美、保持食材原味为特点，注重烹饪技巧和原料的选择。推荐尝试广东煲仔饭、蒸凤爪、清蒸鱼等经典菜品。");
    }else if(city == "深圳"){
        this->Disnum = 8;
        this->feature.append("华侨创意园");
        this->feature.append("大芬油画村");
        this->feature.append("科技产业园");
        this->food.append("潮汕牛肉丸粿条汤：深圳有许多潮汕牛肉丸粿条汤的摊位，这是一种传统的潮汕美食，可以让你开始一天的旅程。");
        this->food.append("深圳海鲜街：深圳有许多海鲜街，如沙头角海鲜街、大梅沙海鲜街等，你可以选择新鲜的海鲜并让餐馆为你烹饪。");
        this->food.append("深圳美食街：深圳有一些知名的美食街，如东门美食街、宝安美食街等，你可以在这里找到各种美食摊位，满足你的味蕾。");
    }else if(city == "杭州"){
        this->Disnum = 6;
        this->feature.append("龙井茶园");
        this->feature.append("西子湖畔");
        this->feature.append("大宋文化");
        this->food.append("杭州的早餐文化非常丰富多样，你可以去品尝当地的传统早餐美食之一——胡辣汤。胡辣汤是一道独特的杭州特色小吃，它是一种用鸡肉、虾皮等原料熬制而成的汤品，搭配上鸡蛋、豆腐、熟猪血等，味道鲜美，营养丰富。");
        this->food.append("中午你可以去尝试杭州的传统菜肴——西湖醋鱼。这是一道杭州非常有名的菜品，以鲜嫩的鱼肉为主料，配上醇厚的醋汁和细腻的调料，酸甜可口，是杭州的代表性美食之一。你可以选择去一家有口碑的本地餐厅品尝正宗的西湖醋鱼。");
        this->food.append("晚上你可以去尝尝杭州的传统夜宵之一——沙县小吃。沙县小吃是杭州的夜市特色之一，它包括各种小吃和烧烤食品，如炒年糕、羊肉串、烤鱿鱼等。你可以在夜市上逛逛，品尝各种美食，感受杭州夜晚的独特魅力。");
    }else if(city == "武汉"){
        this->Disnum = 9;
        this->feature.append("浪漫樱花");
        this->feature.append("黄鹤一去不复返，白云千载空悠悠");
        this->feature.append("楚文化");
        this->food.append("热干面：武汉的传统特色小吃，是一种以细面条为主，配以芝麻酱、辣椒油等调料的面食。");
        this->food.append("武昌鱼：武汉著名的地方菜品之一，选用活鱼制作，口感鲜嫩，常用红烧或清蒸方式烹制。");
        this->food.append("蛇鳝烧鸭：鲜嫩的鸭肉与滑嫩的蛇鳝相结合，烧制而成，是武汉著名的特色菜之一。");
    }else if(city == "南京"){
        this->Disnum = 4;
        this->feature.append("佛教文化");
        this->feature.append("国父-孙中山");
        this->feature.append("缅怀抗日历史");
        this->food.append("糯米卷：南京糯米卷是一种传统的早餐食物，由糯米、鲜肉、咸蛋黄和香菇等原料制成，口感独特。");
        this->food.append("盐水鸭：南京盐水鸭是当地著名的特色菜，鸭肉鲜嫩，腌制后入味，搭配蒜泥和辣椒酱，非常美味。");
        this->food.append("火腿炖鸭煲：这是一道南京传统的家常菜，将鸭肉和火腿炖煮，口味鲜美，可以搭配米饭一起食用。");
    }else if(city == "郑州"){
        this->Disnum = 1;
        this->feature.append("佛教文化");
        this->feature.append("黄帝故里");
        this->feature.append("黄河魅力");
        this->food.append("郑州烩面：郑州烩面是一道独特的面食，面条软糯，配以浓郁的汤汁和各种配料，非常美味。推荐尝试一碗正宗的郑州烩面。");
        this->food.append("羊肉泡馍：一道传统的陕西菜，在郑州也很受欢迎。它由炖煮的羊肉和小麦面团制成的馍片组成，配以香辣的汤汁。");
        this->food.append("面窝窝：一种类似于煎饼的煎面食品，通常与鸡蛋、蔬菜和调味料一起煎制。");
    }else if(city == "西安"){
        this->Disnum = 12;
        this->feature.append("先秦文物");
        this->feature.append("大唐文化");
        this->feature.append("大雁塔");
        this->food.append("肉夹馍是西安的经典早餐之一。它由烤肉、馍（一种类似于馒头的面饼）和调料组成。你可以去当地的小摊位或者知名的肉夹馍店品尝。另外，你还可以尝试一碗传统的豆腐脑，它是一种用豆浆做成的豆腐状食物，配上辣椒油、酱油和葱花，非常美味。");
        this->food.append("羊肉泡馍是西安最著名的传统面食之一。它由羊肉、馍和酱汁组成，非常有特色。你可以去当地的羊肉泡馍店品尝正宗的味道。此外，你还可以尝试一份凉皮，它是一种由凉面条配上各种蔬菜和调料制成的凉拌食品，口感清爽。");
        this->food.append("葫芦头是西安的传统小吃之一，它由酥皮和各种馅料（如肉末、蔬菜等）制成。你可以去当地的小摊位或者餐馆品尝葫芦头。此外，西安的烤肉也非常有名，你可以找一家烤肉店尝试当地特色的烤串。");
    }else if(city == "青岛"){
        this->Disnum = 3;
        this->feature.append("啤酒文化");
        this->feature.append("帆船运动");
        this->feature.append("海底世界");
        this->food.append("海鲜粥：青岛是一个海鲜丰富的城市，可以尝试当地的海鲜粥，如虾仁粥、螃蟹粥等，清淡可口。");
        this->food.append("炒海鲜：青岛的海鲜非常新鲜，可以选择一家海鲜餐厅品尝各种炒海鲜，如炒螃蟹、炒扇贝、炒虾等。");
        this->food.append("啤酒海鲜大排档：在青岛的沿海地区有很多海鲜大排档，可以边品尝新鲜的海鲜，边喝着冰镇的青岛啤酒，享受海风的吹拂。");
    }else if(city == "重庆"){
        this->Disnum = 10;
        this->feature.append("三峡风光");
        this->feature.append("红岩革命纪念");
        this->feature.append("长江索道");

        this->food.append("重庆小面：这是重庆的特色早餐，小面是细面条，配上浓郁的红油和各种配料，如猪肉、鸡蛋、豆芽等。可以去当地的小面摊或餐馆品尝正宗的重庆小面。");
        this->food.append("火锅：重庆的火锅是非常有名的，可以选择麻辣火锅或清汤火锅，配上各种蔬菜、肉类和海鲜，再蘸上特制的调料，非常开胃美味。");
        this->food.append("重庆烤鱼：这是一道以鱼为主要食材的菜肴，鱼身片成片后，配以各种调料和蔬菜，放入烤盘烤制而成，口感鲜美，味道独特。");
    }else if(city == "成都"){
        this->Disnum = 11;
        this->feature.append("国宝熊猫");
        this->feature.append("火锅文化");
        this->feature.append("川剧");

        this->food.append("早餐可以选择馄饨,馄饨是一种传统的中式小吃，内馅可以选择猪肉、虾仁或者素菜，口感鲜美。");
        this->food.append("成都以川菜而闻名，午餐可以尝试一些经典的川菜。比如宫保鸡丁，这是一道以鸡肉、花生和辣椒为主要材料的炒菜，口味麻辣微甜，非常有特色。另外，麻婆豆腐、水煮牛肉、回锅肉等也是非常经典的川菜，值得一试。");
        this->food.append("成都的晚餐推荐选择火锅。火锅是一种传统的中国菜肴，成都的火锅以麻辣著称。你可以选择麻辣火锅，将各种食材如肉类、海鲜、蔬菜等放入热汤中煮熟，再蘸上各种调料享用。在成都，有许多著名的火锅店可供选择，例如老码头火锅、小龙坎火锅等。");
    }
}
QStringList City::SelectCity(QStringList Fealist,vector<int> value,vector<int>& stayTime,QString departure){
    vector<City> citylist;
    City beijin("北京");
    citylist.push_back(beijin);
    City shanghai("上海");
    citylist.push_back(shanghai);
    City guangzhou("广州");
    citylist.push_back(guangzhou);
    City shenzhen("深圳");
    citylist.push_back(shenzhen);
    City hangzhou("杭州");
    citylist.push_back(hangzhou);
    City wuhan("武汉");
    citylist.push_back(wuhan);
    City nanjing("南京");
    citylist.push_back(nanjing);
    City zhengzhou("郑州");
    citylist.push_back(zhengzhou);
    City xian("西安");
    citylist.push_back(xian);
    City qingdao("青岛");
    citylist.push_back(qingdao);
    City chongqing("重庆");
    citylist.push_back(chongqing);
    City chengdu("成都");
    citylist.push_back(chengdu);


    vector<City>::iterator it;
    int i = 0;
    for (const QString& str : Fealist) {
        for (it = citylist.begin(); it != citylist.end(); ++it) {
            City temcity = *it;
            for(const QString& tem :(*it).feature){
                if(tem == str) (*it).value+=value[i];

            }
        }
        i++;
    }

    //debug 当前各城市期望值

    sort(citylist.begin(),citylist.end(),greater<City>());

    vector<City> tempcity;

    //确定要去的城市
     for (it = citylist.begin(); it != citylist.end(); ++it){
         if((*it).value>0 &&(*it).name != departure )
         {
//           qDebug()<<(*it).name<<" "<<(*it).value<<endl;
           tempcity.push_back((*it));
         }
     }
 qDebug()<<"*************************************";
     //优化路径
     QStringList rout;
     sort(tempcity.begin(),tempcity.end());
     City tem (departure);

     if(tem.Disnum < tempcity[0].Disnum)
     {
         tempcity.reserve(13);
     }

     for (it = tempcity.begin(); it != tempcity.end(); ++it){
//         qDebug()<<(*it).name<<" "<<(*it).Disnum<<endl;
//         qDebug() << (*it).value;
         stayTime.push_back((*it).value);
         rout.push_back((*it).name);
     }
     return rout;
}
