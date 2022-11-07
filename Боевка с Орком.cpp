#include <iostream>
#include <string>
using namespace std;
class gg {
    public:
        int changeHp(int value){
            hp = value;
        }
        int getHp(){
            return hp;
        }
    private:
        int hp;
        bool isDry;
        bool isFlaming;
        bool isBlocking;
};
class orc{
    public:
        int setHp(int value){
            hp=value;
            return hp;
        }
        int getHp(){
            return hp;
        }
    private:
        int hp;
};
int main()
{
    gg Kolyan;
    Kolyan.setHp(100);
    orc Smorch;
    Smorch.setHp(500);
    while(Kolyan.getHp()>0 & Smorch.getHp()>0){
        int damage = rand()%20;
        if (isBlocking){
            cout<<"Вы заблокировали удар("<<damage<<" урона)."<<endl;
        }
        else{
            Kolyan.setHp(Kolyan.getHp()-damage);
            if (Kolyan.getHp()<0){
                cout<<"Вам нанесли добивающий удар("<<damage<<" урона)."<<endl;
                break;
            }
            cout<<"Вам нанесли "<<damage<<" урона! Ваш уровень здоровья: "<<Kolyan.getHp()<<endl;
        }
        cout<<"Куда нанести удар?"<<endl<<"Голова/Туловище/Ноги"<<endl;
        string wherePunched;
        cin>>wherePunched;
        if (wherePunched ==  "Голова"){
                damage = rand()%200;
        }
        else if (wherePunched == "Туловище"){
                damage = rand()%150;
        }
        else if (wherePunched == "Ноги"){
                damage = rand()%50;
        }
        Smorch.setHp(Smorch.getHp()-damage);
        cout<<"Вы нанесли "<<damage<<" урона. Уровень здоровья врага: "<<Smorch.getHp()<<endl;
    }
    if (Kolyan.getHp()<0){
        if (Smorch.getHp()<0){
            cout<<"Вы сыграли вничью"<<endl;
        }
        else{
            cout<<"Вы терпите поражение."<<endl;
        }
    }
    else{
        cout<<"Вы одержали победу!"<<endl;
    }
    return 0;
}
