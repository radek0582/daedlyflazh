#include "deklaracje.h"

void gain_achievement (int kod_a)
{
	if (!achievement [kod_a] || achievement [kod_a] == 51)
   {
   	if (!achievement [kod_a])
		  	achievement [kod_a] = 1;

	   messages ("Congratulations! You have just gained an achievement \"", 0, 3);
   	enter_achievement (kod_a, 3);
	   messages ("\" ! _", 0, 3);
   	save_achievements ();
   }
}

void count_achievement (int achieve_id, int przyrost, int suma_achievement)
{
	int suma = 0, q;

  	achievement_temp [50 * achieve_id + przyrost] = 1;

   for (q = 1; q < 50; q ++)
	  	if (achievement_temp [50 * achieve_id + q])
        	suma ++;

	if (suma >= suma_achievement)
   {
   	if (achieve_id == 33)
      {
      	achievement_temp [33 * 50] = 1;
         messages ("You've just been predestinated to special title from President of NYC._", 0, 3);
      }
      else
		  	gain_achievement (achieve_id);
   }
}
