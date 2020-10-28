#include <iostream>
#include "Bartek.h"

int main()
{
   Engine* gra = Engine::MakeEngine("Test",500,500);
   //gra->setFullScreen();
   gra->start();
   
}