#include "deklaracje.h"

void eat ()
{
	turn_to_do = 0;
   reset_inv_globals ();
   grupa_items = 19;
   inventory_selector (3, 0, 0);
}

void zjadaj (int kod_j)
{
	char eat_mod = 1;		// modyfikator zalezny od statusu jedzenia (cursed, blessed...)
	char eaten = 0;		// niuans do usuwania przedmiotow (jedzenia)
   int typ_j = item_type [kod_j];
   int satiation_j = item_specials2 [kod_j];
   int waga_j = item_weight [kod_j];

   rysuj_ekran ();

   if (unpaid_items [kod_j])
   	msg ("<Do not try to eat this! ");
   else
   {
		if (typ_j < 1000)
   		turn_to_do = waga_j / 128 + 3;
	   else
   	   turn_to_do = waga_j / 16 + 1;

	   msg ("<You start to eat ");
	   enter_one_item (kod_j);
   	kropka (COLOR_GRAY);
	   item_specials1 [kod_j] *= -1;		// nie gnije w czasie zjadania

	   while (turn_to_do > 0)
   	{
     		turn_to_do --;
	      turn ();

   	   if (!turn_to_do)	// udane zjedzenie posilku
      	{
	        	msg ("You have eaten ");
   	      enter_one_item (kod_j);
      	   kropka (COLOR_GRAY);
         	satiation += satiation_j * eat_mod;

				if (typ_j == 1030)
   	      {
      	      msg ("Suddenly everything looks so different.");
         	   drugs [0] += waga_j * 5;
         		character_state [_DRUGGED] = 1;	// drugs mode on
	            rysuj_view_range ();
   	         put_monsters ();

					if (achievement [34] < 5)
	               achievement_temp [34 * 50] ++;
               else
               	gain_achievement (34);
      	   }
            else if (typ_j == 1)		// rat corpse
            {
            	if (health < total_max_health)
               {
	              	health += losuj (1, 4);

      	         if (health > total_max_health)
         	      	health = total_max_health;

            	   statystyki (11);
						msg ("You feel a little better! ");
               }
            }

	         eaten = 1;

   	      if (item_amount [kod_j] > 1)
      	   	eaten = 0;

				ujmij_item (kod_j, 1);
				oblicz_stats ();
			}
	      else if (turn_to_do < 0)		// przerwanie jedzenia z pewnego powodu (np. atak monstera)
   	   {
      		msg ("Continue eating (y/n) ?");

         	if (answer ())
	         	turn_to_do *= -1;

   	     	msg_reset ();
	      }
   	   else if (turn_to_do == 10000)	// death
      		break;
		}

	   if (!eaten)						// nie dojedzono lub kilka sztuk jedzenia - przywrocic gnicie
		   item_specials1 [kod_j] *= -1;

	   turn_to_do = 0;
   }
}
