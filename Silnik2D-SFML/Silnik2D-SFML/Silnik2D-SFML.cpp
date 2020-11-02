#include <iostream>
#include "Bartek.h"

int main()
{
   Engine* gra = Engine::MakeEngine("Test",800,800);
   //gra->setFullScreen();
   gra->setFrameRateCap(60);
   gra->start();
   
}