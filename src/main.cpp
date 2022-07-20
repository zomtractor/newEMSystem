#include "EMSystem.h"
using namespace std;
int main(){

    EMSystem sys;
    sys.readData();
    sys.showWelcome();
    while(sys.showMenu());

    sys.writeData();
    return 0;

}
