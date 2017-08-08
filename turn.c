#include "deklaracje.h"

void turn ()
{
	int i, j, k, l, typ, floor_type, monster_kod, test1, check_luck, visibility, x_pos, y_pos;

	oblicz_stats ();
	rysuj_view_range ();
	verify_visible_monsters ();
	AI ();

  	moves_env = (SPEED_ENV * 32 + bonus_env) / total_speed / 32;
	bonus_env += (SPEED_ENV * 32) % (total_speed * 32);

	if (bonus_env / total_speed / 32)
		bonus_env = bonus_env - total_speed * 32;

   for (i = 0; i < moves_env; i ++)
	{
		for (j = 1; j < 20; j ++)
   		if (character_state [j])
      		do_character_state (j);

      for (k = 0; k < x_planszy; k ++)
      	for (l = 0; l < y_planszy; l ++)
         {
		      floor_type = floor_planszy [k] [l];
		     	action_floor (floor_type, k, l);
         }

	   if (!air)
      {
      	msg ("You are choking! ");
	   	drain_health (rand () % 15, 4);
      }

		if (air < total_max_air)
   	{
	  		air ++;
   	   statystyki (14);
	   }

		if (health > 0 && health < max_health)		// regeneracja HP
   	{
		   if (abilities [_CONDITION] == 30)
   			health_bonus += losuj (1, 16);

	      health_bonus += losuj (1, abilities [_CONDITION] + 1);

   	   if (health_bonus >= 30)
      	{
	      	health_bonus -= 30;
   	      health += 1;

            if (health > max_health)
            	health = max_health;

      	   statystyki (11);		// update HP state
	      }
   	}

//	   if (!do_eat)
//		   satiation -= 1;

	   switch (cl_id)
   	{
      	case _Graveyard:
   		   if (quest [1] == 1 && find_npc (_zombie) == -2)
		      {
		      	quest [1] = -1;
			      msg ("All zombies have been killed. Talk to Father Grigori._");

               if (!achievement_temp [24 * 50])
               	gain_achievement (24);
		      }
   			break;
	   	case _Puerto_Zombico:
   	   	if (quest [13] == 1 && find_npc (_zombie) == -2)
      	   {
         		msg ("You feel that Puerto Zombico is now clear._");
	            quest [13] = -1;
   	      }
      	   break;
	   	case _Old_Remo:
   	   	if (!monsters_amount)
      	   {
            	gain_achievement (21);
					count_achievement (33, (cl_id - 1200) / 5 + 1, 5);
   	      }
      	   break;
	   	case _Downtown:
	   	case _Marina_Harbour:
	   	case _Shelter_Tec:
   	   	if (!monsters_amount)
//               achievement_temp [33 * 50 + (cl_id - 1200) / 5] = 1;
					count_achievement (33, (cl_id - 1200) / 5 + 1, 5);
      	   break;
	   	case _New_York_City:
   	   	if (monsters_amount == 1 && monster_code [0] == _Pleasence)
					count_achievement (33, (cl_id - 1200) / 5 + 1, 5);
      	   break;
	   	case 1300:
   	   case 1301:
      	case 1302:
	      	if (monsters_amount < 5)
					generuj_potwory (5, 1, -1, 2, -5);
	         break;
   		case 1999:
      		passed_event_turns ++;
//      		satiation -= 20;
	  	      elapsed_time += 10000 / total_speed;

				if (health < max_health)
   	      {
	   	      for (j = 0; j < 20; j ++)
   	   	   {
					   if (abilities [_CONDITION] == 30)
   						health_bonus += losuj (1, 16);

				      health_bonus += losuj (1, abilities [_CONDITION] + 1);

				      if (health_bonus >= 30)
				      {
			   	   	health_bonus -= 30;
         				health += 1;

			            if (health > max_health)
         			   	health = max_health;
				      }
				   }
	   	      statystyki (11);		// update HP state
         	}
	         break;
      	default:
         	if (cl_id < 1200)
            {
//		      	if (monsters_amount < 20)
//						generuj_potwory (5, _ORC, -1, 1, -1);
            }
            break;
	   }

  		for (j = 0; j < items_amount; j ++)		// oddzialywanie srodowiska na przedmioty i vice versa
	   {
      	if (working_items [j])
         {
	      	k = item_group [j];
            typ = item_type [j];

            if (item_owner [j] == -1)
            {
	            h_pos_item [j] = h_pos;
   	         v_pos_item [j] = v_pos;
            }
            else if (item_owner [j] >= 0)
            {
	            h_pos_item [j] = h_pos_mon [item_owner [j]];
   	         v_pos_item [j] = v_pos_mon [item_owner [j]];
            }

            x_pos = h_pos_item [j];
  	         y_pos = v_pos_item [j];

	         if (cl_id == 1999)
	         	i = 20;
   	      else
      	   	i = 1;

	     		if (k == 19 && typ < 1000 && item_specials1 [j] > 0)		// gnicie jedzenia
	   	   {
					item_specials1 [j] -= (35 - abilities [_SCIENCE]) * i;

	         	if (item_specials1 [j] < 1)
					{
						if (item [j] == 1 || item [j] == 4)		// w plecaku lub w lapie
		            {
      	   	   	msg ("You feel slightly lighter.");
   	   	      }
		            else if (item [j] == 3 && check_own_visibility (x_pos, y_pos))
   	            {
							msg ("You see");
	      		     	enter_item (j, COLOR_GRAY);
   		   	     	msg (" rots away.");
	               }

						ujmij_item (j, item_amount [j]);
	      	   }
				}
      	   else if (k == 15 && item_specials2 [j])		// pochodnia plonie/ bomba tyka
	         {
   	      	item_specials1 [j] -= i;							// ujmij ladunki pochodni/bomby

	            if (!item_specials1 [j])
   	         {
						ujmij_item (j, 1);

               	if (typ == 1)
                  {
	      	      	if (item [j] == 4)
		   	         	msg ("Suddenly your torch bunrs out.");
	   	            else if (item [j] == 3 && check_own_visibility (x_pos, y_pos))
   	   	         	msg ("Suddenly a torch burns out.");
                  }
                  else if (typ == 7)
                  {
                  	if (check_own_visibility (x_pos, y_pos))
		   	         	msg ("You see huge explosion! ");
                     else
		   	         	msg ("KABOOOOM!!! ");

					   	create_a_ball (-5, x_pos, y_pos, 3, 3, 300);
                  }
   	         }
      	   }
      	   else if (item [j] == 5 && item_state [j] == 1)		// burning obstacle
	         {
            	if (stan_planszy [x_pos] [y_pos] == 2)
	            	change_color (1, x_pos, y_pos);
      	   }
         }
	   }

      for (j = 0; j < monsters_amount; j ++)
      {
      	floor_type = floor_planszy [h_pos_mon [j]] [v_pos_mon [j]];
         monster_kod = monster_code [j];

			if (monster_hp [j] < monster_health [j])
   	   {
      		switch (monster_code [j])
	         {
   	      	case _BAYBARS:
      	      	monster_hp [j] += rand () % 2;
         	      break;
	         }
   	   }

         if (monster_hp [j] < 1)
         {
			   test1 = rzut (320);
		   	check_luck = rzut (luck * 100 + 6);

				if (1)//test1 < check_luck + abilities [_FOOD] - weapon_modifier)	// test na food preservation i luck
		      {
		      	switch (monster_code [j])
      		   {
		            case 1:		// rat
      		      case 60:		// wolf
            		case 80:		// spider
		            case 100: 	// kobold
      			  	case 110: 	// orc
							create_item (2000 + monster_kod, 0, h_pos_mon [j], v_pos_mon [j], 1);		// zostaw cialo ubitego potwora
		               break;
   		      }
		      }

			   test1 = rzut (320);
		   	check_luck = rzut (luck * 100 + 6);

		      if (test1 - 2 < check_luck + abilities [_CONDITION])							// test na alertness i luck
		      {
					switch (monster_kod)
		         {
      		   	case 100:	// kobold
		            	monster_drop (j, 41, 1);		// dagger
      		         break;
		         	case 110:	// orc
	   		   		monster_drop (j, 42, 1);	// spear
		               break;
		         }
				}

				if (check_own_visibility (h_pos_mon [j], v_pos_mon [j]))
            {
		         enter_monster (monster_kod, COLOR_GRAY, -1000, 0);
			      msg (" drops dead.");
            }

		      delete_monster (-5, j, 0);

		      if (monster_kod == 3)	// gdy zabity mutated rat leader - dodaje nowy item na plansze
		      {
      		   create_item (2003, 0, h_pos_mon [j], v_pos_mon [j], 1);
		         quest [0] = 2;
      		}
         }
      }
	}

/*   if (cl_id == _Old_Remo)
   {
  	  	area_description (5000);
   	play = -1;
   }*/

   if (death)
  	{
   	msg ("You die... _");
      turn_to_do = 10000;
  	   play = 0;

      if (monster_code [killing_monster_id] == _zombie && (cl_id == _Graveyard || cl_id == _Puerto_Zombico))		// left 4 dead
      	gain_achievement (26);

      if (search_item (29, 3) >= 0)		// jest w plecaku alloys
      	gain_achievement (20);
   }

  	turns_amount ++;
   elapsed_time += 150 / total_speed;

	if (play > 0 && cl_id == 1999)
   {
	  	if (passed_event_turns > 2 && losuj (1, 40) < 3)		// wilderness event
   	{
	     	floor_type = floor_planszy [h_pos] [v_pos];
   		passed_event_turns = 0;
  	   	j = losuj (1, 3);

	     	if (0) //floor_type < 180)	// gdy nie specjlana lokacja
   	   {
      		msg ("You are ambushed by");

	         if (j == 1)
					msg ("some bandits_.");
      	   else if (j == 2)
            {
	  				msg ("wild dogs_.");
            }
      	   else
            {
	  				msg ("jackals_.");
            }

	         change_location (30 + j);
   	   }
	  	}
   }
}
