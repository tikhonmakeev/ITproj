#include <iostream>
#include <string>
using namespace std;
class Player {
    public:
        void set_hp(int hp1){
            hp = hp1;
        }
        void take_damage(int damage_amount){
            hp = hp - damage_amount;
        }

        int get_hp() {
            return hp;
        };
    private:
        int hp = 1000;

};
class Monster {
    public:
        int hp;
        void set_hp(int hp1){
            hp = hp1;
        }
        void take_damage(int damage_amount){
            hp = hp - damage_amount;
        }

        int get_hp() {
            return hp;
        };
};
class Goblin: public Monster{
    public:
        Goblin(){
            set_hp(250);
            cout<<"goblin has been spawned"<<"\n";
        }
};
class Ork: public Monster{
    public:
        Ork(){
            set_hp(500);
            cout<<"ork has been spawned"<<"\n";
        }
};
int main() {
    Goblin gobl;
    Ork ork;
    Player player;
    int damage=100;
    return 0;
};