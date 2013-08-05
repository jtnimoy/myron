#include <stdio.h>
#include <GLUT/glut.h>
#include "../source/myron.h"


int main(int argc,char**argv){
  glutInit(&argc,argv);
  Myron *m = new Myron();
  m->start(160,120);
  m->settings();
  m->stop();
  delete m;
  return 0;
}
