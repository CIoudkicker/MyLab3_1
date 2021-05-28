#include "ICalculateSize.h"

float ICalculateSize::trim(float in)    // округляет число
{
   int v1 = static_cast<int>(in);
   int v2 = static_cast<int>((in - v1)*100);
   float v3 = (in - v1)*100 - v2;
   if ( v3*10 >= 5 )
   {
      ++v2;
   }
   return (v1 + 0.01*v2);
}
