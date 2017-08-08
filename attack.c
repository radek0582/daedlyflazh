#include "deklaracje.h"

int attack (int cel_ataku, int kod_p, char attack_type, int spell_type)
{
   char visibility = 0;
   int weapon_modifier = 0, a, b = 2 - attack_type;	// bardziej niszczaca bron - mniejsze prawdopod. pozostawienia cialka
	int attacks = 1, shots, i;
   int hit1, hit2, damage1, damage2, test1, test2, check_luck, suma_weapon = 0;
   int stan = 0;

   if (cel_ataku >= 0)
   	 visibility = check_own_visibility (h_pos_mon [cel_ataku], v_pos_mon [cel_ataku]);

   switch (attack_type)
	{
  		case 1:
      	shots = item_status [item_body [_SIDEARM_SLOT]];

         if (shots > item_specials2 [item_body [_SIDEARM_SLOT]])
         	shots = item_specials2 [item_body [_SIDEARM_SLOT]];
         break;
      case 2:
      	shots = item_status [item_body [_PRIME_SLOT]];

         if (shots > item_specials2 [item_body [_PRIME_SLOT]])
         	shots = item_specials2 [item_body [_PRIME_SLOT]];
         break;
   }

	while (attacks -- > 0)
	{
		if (!attack_type)		// walka wrecz
      {
      	monster_aim [cel_ataku] = -1;
			damage1 = total_damage;// - monster_dv [cel_ataku];

		   if (damage1 > 0)
	  		{
				monster_hp [cel_ataku] -= damage1;
//	        	weapon_marks [item_type [item_body [_RHAND]]] ++;

				if (visibility == 2)
	  	   	{
			   	msg ("You hit ");
				   enter_monster (monster_code [cel_ataku], COLOR_GRAY, -1000, 0);
				}
		   }
	  		else
		   {
				if (visibility == 2)
	   	   {
   				msg ("You miss ");
		   		enter_monster (monster_code [cel_ataku], COLOR_GRAY, -1000, 0);
		      }
			}
		}
      else if (attack_type == 1)		// strzelanie/rzucanie
      {
      	if (cel_ataku == kod_p)		// atakowany jest potwor bedacy celem glownym
	      	monster_aim [cel_ataku] = -1;
         else								// pocisk ma ominac potwora stojacego na torze lotu pocisku
         {
         	if (1)//abilities [_SIDEARMS] > 0)		// omija
            {
				   enter_monster (monster_code [kod_p], COLOR_GRAY, 0, 0);
            	msg (" is missed. ");
               stan = 1;
            }
            else
            {
            	monster_aim [kod_p] = -1;
               cel_ataku = kod_p;
            }
         }

			if (!stan)
         {
			   damage1 = item_dmg_bonus [item_body [_SIDEARM_SLOT]];

			   if (abilities [_SIDEARMS] >= 0)
	  			{
		      	if (cel_ataku > -1)
						monster_hp [cel_ataku] -= damage1 * shots;
      	      else
         	   	drain_health (damage1 * shots, 1);

//		        	weapon_marks [item_type [item_body [_MWEAPON]]] ++;

					if (visibility)
		  	   	{
				   	msg ("You hit ");
					   enter_monster (monster_code [cel_ataku], COLOR_GRAY, -1000, 0);
					}
			   }
		  		else
			   {
					if (visibility)
		   	   {
   					msg ("You miss ");
			   		enter_monster (monster_code [cel_ataku], COLOR_GRAY, -1000, 0);
         	      stan = 1;
			      }
				}
			}
      }
      else			// bazooka
      {
      	if (cel_ataku >= 0 && cel_ataku == kod_p)		// atakowany jest potwor bedacy celem glownym
	      	monster_aim [cel_ataku] = -1;
         else if (attack_type == 2)								// pocisk ma ominac potwora stojacego na torze lotu pocisku
         {
         	if (1)//abilities [_PRIME] > 0)		// omija
            {
				   enter_monster (monster_code [kod_p], COLOR_GRAY, 0, 0);
            	msg (" is missed. ");
               stan = 1;
            }
            else
            {
            	monster_aim [kod_p] = -1;
               cel_ataku = kod_p;
            }
         }

			if (!stan)
         {
         	if (attack_type == 3)
            {
            	if (spell_type == 300) 		// high explosive
					   damage1 = rzut (606);
            }
            else
				   damage1 = item_dmg_bonus [item_body [_PRIME_SLOT]];

			   if (attack_type == 3 || abilities [_PRIME] >= 0)
	  			{
		      	if (cel_ataku > -1)
						monster_hp [cel_ataku] -= damage1 * shots;
      	      else
         	   	drain_health (damage1 * shots, 1);

//		        	weapon_marks [item_type [item_body [_MWEAPON]]] ++;

					if (visibility)
		  	   	{
               	if (attack_type == 2)
					   	msg ("You hit ");

					   enter_monster (monster_code [cel_ataku], COLOR_GRAY, -1000, 0);

                  if (attack_type == 3)
                  {
                  	if (monster_aim [cel_ataku] != -1)
                     	reputation_change (cel_ataku);

                  	msg (" is being hit");
                  }
					}
			   }
		  		else
			   {
					if (visibility)
		   	   {
   					msg ("You miss ");
			   		enter_monster (monster_code [cel_ataku], COLOR_GRAY, -1000, 0);
         	      stan = 1;
			      }
				}
			}
      }
   }

	if (cel_ataku > -1 && monster_hp [cel_ataku] <= 0)
	{
   	killed_monsters [0] ++;
      killed_monsters [monster_code [cel_ataku]] ++;
		gain_experience (monster_exp [cel_ataku]);
	   test1 = rzut (320);
   	check_luck = rzut (luck * 100 + 6);

		if (1)//test1 < check_luck + abilities [3] - weapon_modifier)	// test na food preservation i luck
      {
      	switch (monster_code [cel_ataku])
         {
            case 1:		// rat
            case 60:		// wolf
            case 80:		// spider
            case 100: 	// kobold
         	case 110: 	// orc
            case _RAT_KING:
            {
					create_item (2000 + monster_code [cel_ataku], 0, h_pos_mon [cel_ataku], v_pos_mon [cel_ataku], 1);		// zostaw cialo ubitego potwora
            }
               break;
         }
      }

	   test1 = rzut (320);
   	check_luck = rzut (luck * 100 + 6);

      if (losuj (1, 5) > 3)							// test na alertness i luck
      {
      	if (monster_code [cel_ataku] >= 143 && monster_code [cel_ataku] <= 146)
	        	monster_drop (cel_ataku, losuj_3 (_B_BAT, _AXE, _KNIFE), 1);
         else if (monster_code [cel_ataku] == _SOLDIER)
         {
	        	monster_drop (cel_ataku, losuj_3 (_bullets_9mm, _357, _233), losuj (1, 10));

            if (losuj (1, 10) > 7)
		        	monster_drop (cel_ataku, losuj_2 (_COAT, _JACKET), 1);
         }
		}

      for (i = 0; i < 15; i ++)
      	if (monster_body [cel_ataku] [i] != -1)
         	monster_drops_item (cel_ataku, monster_body [cel_ataku] [i]);

     	if (monster_code [cel_ataku] >= _Marston)
        	monster_drop (cel_ataku, _M65, 1);

      if (monster_code [cel_ataku] == 3)	// gdy zabity mutated rat leader - dodaje nowy item na plansze
      {
         create_item (2003, 0, h_pos_mon [cel_ataku], v_pos_mon [cel_ataku], 1);
         quest [0] = 2;
      }
      else if (monster_code [cel_ataku] == _CHARDASHKA)
         create_item (_STING, 0, h_pos_mon [cel_ataku], v_pos_mon [cel_ataku], 1);

      killed_monsters [monster_code [cel_ataku]] += 1;
      event_cost (3, monster_code [cel_ataku]);

		if (visibility)
      {
      	if (!spell_type)
		      msg (" and slay it. ");
         else if (spell_type == _LIGHTNING_BALL)
         	msg (" and electroduced it right away! ");
      }

      if (monster_code [cel_ataku] == _CLASS_Cyborg && !attack_type && item_body [_MELEE_SLOT] >= 0 && item_type [item_body [_MELEE_SLOT]] == 4)
      	gain_achievement (25);

      if ((monster_code [cel_ataku] == _MALE_NOMAD || monster_code [cel_ataku] == _FEMALE_NOMAD) && attack_type == 2 && item_body [_BODY_SLOT] >= 0 && item_type [item_body [_BODY_SLOT]] == 1 && item_type [item_body [_PRIME_SLOT]] == 4)
      {
      	if (achievement_temp [28 * 50] == 9)
	      	gain_achievement (28);
         else
				achievement_temp [28 * 50] ++;
      }

      if ((attack_type == 1 || attack_type == 2) && monster_code [cel_ataku] == _zombie && cl_id == _Graveyard)
      	achievement_temp [24 * 50] = 1;

      if (attack_type == 1 && (monster_code [cel_ataku] == _FEMALE_NOMAD || monster_code [cel_ataku] == _FEMALE_CITIZEN))
      {
      	if (achievement_temp [9 * 50] == 1 && cl_id == achievement_temp [9 * 50 + 1])
	      	gain_achievement (9);
      }
      else if (attack_type == 2 && item_type [item_body [_PRIME_SLOT]] == 3)
      {
      	if (achievement_temp [13 * 50] == 19)
	      	gain_achievement (13);
         else
				achievement_temp [13 * 50] ++;
      }

	   if (monster_code [cel_ataku] == _Flint_Westwood)
	     	gain_achievement (11);
	   else if (monster_code [cel_ataku] == _zombie)
   	{
	      if (achievement [3] < 49)
		      achievement [3] ++;
	   	else if (achievement [3] == 49)
	      {
   	   	achievement [3] = 51;
				gain_achievement (3);
	      }

         if (achievement [23] < 19 && !attack_type)
         	achievement [23] ++;
	   	else if (achievement [23] == 19 && !attack_type)
	      {
   	   	achievement [23] = 51;
				gain_achievement (23);
	      }
		}
	   else if (monster_code [cel_ataku] == _CLASS_Cyborg)
   	{
      	if (achievement [14] < 19)
		      achievement [14] ++;
		   else if (achievement [14] == 19)
	      {
   	   	achievement [14] = 51;
				gain_achievement (14);
	      }
		}

      if (cl_id == _Old_Remo && monsters_amount == 1)
      	gain_achievement (21);

      delete_monster (-1, cel_ataku, attack_type);

      if (!attack_type && item_body [_MELEE_SLOT] >= 0)			// MELEE
      	count_achievement (5, item_type [item_body [_MELEE_SLOT]], 5);
      else if (attack_type == 1)				// SIDEARM
      	count_achievement (6, item_type [item_body [_SIDEARM_SLOT]], 3);
      else if (attack_type == 2)				// PRIME
      	count_achievement (4, item_type [item_body [_PRIME_SLOT]], 5);
	}
   else
   {
   	if (visibility)
			kropka (COLOR_GRAY);
   }

   return stan;
}

int monster_attack (int attacker_id, int cel_ataku, int kod_p, char attack_type, int spell_type)
{
	int test, monster_dmg, monster_ht, rzut_hit, i, j, health_to_cut = 0;
   int suma_PV = item_dv [item_body [_BODY_SLOT]];
   int stan = 0;
   int visibility_of_victim;
   int visibility_of_attacker = check_own_visibility (h_pos_mon [attacker_id], v_pos_mon [attacker_id]);
   int temp_cel_ataku = cel_ataku;

   if (kod_p == -1)
   	visibility_of_victim = 1;
   else
   	visibility_of_victim = check_own_visibility (h_pos_mon [kod_p], v_pos_mon [kod_p]);

	rzut_hit = losuj (1, 20);
//	test = rzut (monster_damage [attacker_id]);
	monster_dmg = monster_damage [attacker_id];
   monster_ht = monster_hit [attacker_id] + rzut_hit;

   if (cel_ataku == -1 && turn_to_do > 0)
  	  	turn_to_do *= -1;

  	if (cel_ataku == kod_p && cel_ataku >= 0)		// atakowany jest potwor bedacy celem glownym, nie gracz
     	monster_aim [cel_ataku] = attacker_id;
   else if (cel_ataku != kod_p)								// pocisk ma ominac potwora stojacego na jeto torze lotu
   {
     	if (1)						// omija
      {
        	if (visibility_of_attacker && visibility_of_victim)
         {
			   enter_monster (monster_code [attacker_id], COLOR_GRAY, 0, 0);
  	      	msg (" misses ");

            if (kod_p >= 0)
				   enter_monster (monster_code [kod_p], COLOR_GRAY, -1000, 0);
            else
              	msg ("you");

				kropka (COLOR_GRAY);
         }

         stan = 1;
      }
      else			// trafia
      {
        	if (kod_p >= 0)
           	monster_aim [kod_p] = attacker_id;			// postrzelony potwor ma nowy cel

         cel_ataku = kod_p;
      }
   }

	if (!stan)
   {
		if (visibility_of_attacker && visibility_of_victim)
   		enter_monster (monster_code [attacker_id], COLOR_GRAY, 0, 0);
      else if (visibility_of_victim)
        	msg ("Someone");

	   if (1)					// czy trafia
		{
        	if (cel_ataku == -1)		// celem jest gracz
         {
				health_to_cut += monster_dmg - suma_PV;
	         killing_monster_id = attacker_id;
            msg (" hits you");

  	   	   if (health_to_cut > 0)
  		      	drain_health (health_to_cut, 1);
		      else
			   	msg (" but did not manage to harm you");
         }
         else
         {
				monster_hp [cel_ataku] -= monster_dmg;

				if (visibility_of_victim)
	  	   	{
            	if (attack_type == 1)
               	msg (" shoots ");
               else
	     	         msg (" hits ");

				   enter_monster (monster_code [kod_p], COLOR_GRAY, -1000, 0);
            }
			}
	   }
  		else
	   {
			if (visibility_of_victim)
   	   {
	   		enter_monster (monster_code [attacker_id], COLOR_GRAY, 0, 0);
				msg (" misses ");

            if (kod_p >= 0)
		   		enter_monster (monster_code [kod_p], COLOR_GRAY, -1000, 0);
            else
              	msg ("you");
	      }
  	      stan = 1;
		}
	}

  	if (!stan && visibility_of_victim)
		kropka (COLOR_GRAY);

	if (cel_ataku >= 0 && monster_hp [cel_ataku] <= 0)
   {
     	if (temp_cel_ataku == cel_ataku)
			monster_aim [attacker_id] = -5;
//         else
//				monster_aim [attacker_id] = temp_cel_ataku;

     	delete_monster (attacker_id, cel_ataku, attack_type);
   }

   return stan;
}
