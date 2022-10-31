#include <iostream>//ПЕРЕДЕЛАТЬ
#include <string>
using namespace std;
string magick(element_1,element_2){
    if (element_1 = "water" and element_2 = "fire"){
        return "steam";
    }
    if (element_1 = "water" and element_2 = "cold"){
        return "ice";
    }
    if (element_1 = "water" and element_2 = "earth"){
        return "dirt";
    }
    if (element_1 = "water" and element_2 = "fire"){
        return "steam";
    }
}
int main() {
    string element_1 = "water";
    string element_2 = "fire";
    magick(element_1, element_2);
    return 0;
}   
