#include <iostream>
#include "Bartek.h"

int main()
{
   Engine* gra = Engine::MakeEngine("Test",700,700);
   //gra->setFullScreen();
   gra->setFrameRateCap(100);
   gra->start();

   return 0;
}