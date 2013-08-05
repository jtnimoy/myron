/**

   on a mac, compile it like this:
   g++ helloworld.cpp -I/usr/local/include -L/usr/local/lib -lmyron -framework Carbon -framework Quicktime

*/

#include "myron.h"
#include <iostream>

using namespace std;

int main(){
  Myron *myron = new Myron();
  myron->start(320,240);
  while(true){
    myron->update();
    cout << "hi there\n";
    sleep(1);
  }
  return 0;
}
