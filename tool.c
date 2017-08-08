#include "deklaracje.h"

int select_a_tool ()
{
   reset_inv_globals ();
   grupa_items = 15;
   inventory_selector (5, 0, 0);

   return 0;
}

void use_a_tool (int chosen_tool_id)
{
	int typ = item_type [chosen_tool_id];

   rysuj_ekran ();

	if (chosen_tool_id != -1)
   {
	   if (unpaid_items [chosen_tool_id])
   		msg ("<Do not try to use this! ");
		else if (chosen_tool_id >= 0)
		{
	   	if (typ == 1 || typ == 7)
         {
         	if (typ == 1)
            {
			   	msg ("<You light a torch. ");
	            item_specials2 [chosen_tool_id] = 1;		// lit
	   	      working_items [chosen_tool_id] = 1;
  	         }
            else if (typ == 7)
            {
            	msg ("<You've set high explosive. ");
               ujmij_item (chosen_tool_id, 1);
				   create_item (_high_explosive, 0, h_pos, v_pos, 1);
	            item_specials2 [item_id] = 1;		// ticking
		         working_items [item_id] = 1;
            }

            turn ();
         }
         else if (typ >= 2)
         {
         	msg ("<Which direction (5 = self) ?");

            while (1)
            {
            	klawisz ();

					if (key == '7')
               {
	               event_tool (chosen_tool_id, -1, h_pos - 1, v_pos - 1);
                  break;
               }
               else if (key == '8')
               {
	               event_tool (chosen_tool_id, -1, h_pos, v_pos - 1);
                  break;
               }
               else if (key == '9')
               {
	               event_tool (chosen_tool_id, -1, h_pos + 1, v_pos - 1);
                  break;
               }
               else if (key == '4')
               {
	               event_tool (chosen_tool_id, -1, h_pos - 1, v_pos);
                  break;
               }
               else if (key == '5')
               {
	               event_tool (chosen_tool_id, -1, h_pos, v_pos);
                  break;
               }
               else if (key == '6')
               {
	               event_tool (chosen_tool_id, -1, h_pos + 1, v_pos);
                  break;
               }
               else if (key == '1')
               {
	               event_tool (chosen_tool_id, -1, h_pos - 1, v_pos + 1);
                  break;
               }
               else if (key == '2')
               {
	               event_tool (chosen_tool_id, -1, h_pos, v_pos + 1);
                  break;
               }
               else if (key == '3')
               {
	               event_tool (chosen_tool_id, -1, h_pos + 1, v_pos + 1);
                  break;
               }
					else if (key == 27)
	               break;
            }
         }
	   }
   }
}

void mechanical_blade ()
{
/*	int kod_typ = item_type [item_body [_MECH_CLAW]];
   int chosen_tool_id = item_body [_MECH_CLAW];

	if (kod_typ == 1)		// STING
   {
	  	msg ("<Which direction ?");

   	while (1)
      {
        	klawisz ();

			if (key == '7')
         {
	         event_blade (chosen_tool_id, -1, h_pos - 1, v_pos - 1);
            break;
         }
         else if (key == '8')
         {
	         event_blade (chosen_tool_id, -1, h_pos, v_pos - 1);
            break;
         }
         else if (key == '9')
         {
	         event_blade (chosen_tool_id, -1, h_pos + 1, v_pos - 1);
            break;
         }
         else if (key == '4')
         {
	         event_blade (chosen_tool_id, -1, h_pos - 1, v_pos);
            break;
         }
         else if (key == '5')
         {
	         event_blade (chosen_tool_id, -1, h_pos, v_pos);
            break;
         }
         else if (key == '6')
         {
	         event_blade (chosen_tool_id, -1, h_pos + 1, v_pos);
            break;
         }
         else if (key == '1')
         {
	         event_blade (chosen_tool_id, -1, h_pos - 1, v_pos + 1);
            break;
         }
         else if (key == '2')
         {
	         event_blade (chosen_tool_id, -1, h_pos, v_pos + 1);
            break;
         }
         else if (key == '3')
         {
	         event_blade (chosen_tool_id, -1, h_pos + 1, v_pos + 1);
            break;
         }
			else if (key == 27)
	         break;
		}
	}*/
}

void event_tool (int chosen_tool_id, char event_type, int x_pos, int y_pos)
{
	int floor_type, kod_m, kod_o, i;
   int typ_p;

   turn_to_do = 0;
   typ_p = item_type [chosen_tool_id];

	if (event_type == -1)
   {
      if (typ_p == 1)			// torch
      {
      }
   	else if (typ_p == 2)		// hatchet
      {
	   	floor_type = floor_planszy [x_pos] [y_pos];

			if (floor_type >= 6 && floor_type <= 10)
      	{
	      	msg ("<You start to cut ");
   	      enter_floor (floor_type, COLOR_GRAY, -1000);
      	   kropka (COLOR_GRAY);

	         turn_to_do = 30 - abilities [10] + rand () % 5;

			   while (turn_to_do > 0)
			   {
			     	turn_to_do --;
		   	   turn ();

			      if (!turn_to_do)
		      	{
      	      	msg ("You cut down ");
	   		      enter_floor (floor_type, COLOR_GRAY, -1000);
						kropka (COLOR_GRAY);
		            floor_planszy [x_pos] [y_pos] = 1;
      	         convert_floor (x_pos, y_pos);

         	      if (abilities [10] + luck > rand () % 30)
							create_item (900 + floor_type, 0, x_pos, y_pos, 1);

	              	aktualizuj_pole (x_pos, y_pos);
      	         rysuj_view_range ();
         	      break;
					}
			      else if (turn_to_do < 0)
			      {
		   	   	msg ("Continue cutting (y/n) ?");

			         if (answer ())
   	   		   	turn_to_do *= -1;

			        	msg_reset ();
    			  	}
            	else if (turn_to_do == 10000)
	            	break;
				}
			   turn_to_do = 0;
	      }
   	}
      else if (typ_p == 3)		// climbing set
      {
      }
   	else if (typ_p == 4 && (kod_m = monsters_planszy [x_pos] [y_pos]) >= -1)		// medikit
      {
			if (kod_m == -1 && health == total_max_health)
         	msg ("<You feel absoulutely healthy. ");
         else if (kod_m >= 0 && monster_hp [kod_m] == monster_health [kod_m])
         	msg ("<This monster is absoulutely healthy. ");
         else
      	{
	      	msg ("<You start to heal ");

            if (kod_m == -1)
            	msg ("yourself");
            else
	   	      enter_monster (monster_code [kod_m], COLOR_GRAY, -1000, 0);
               
      	   kropka (COLOR_GRAY);

	         turn_to_do = 5;

			   while (turn_to_do > 0)
			   {
			     	turn_to_do --;
		   	   turn ();

			      if (!turn_to_do)
		      	{
                  if (kod_m == -1)
                  {
                  	msg ("You are healed. ");
                     health = total_max_health;
                     statystyki (11);
                  }
						else
                  {
	      	      	msg ("You healed ");
		   		      enter_monster (monster_code [kod_m], COLOR_GRAY, -1000, 0);
							kropka (COLOR_GRAY);
	                  monster_hp [kod_m] = monster_health [kod_m];

							if (monster_code [kod_m] == _Helc)
	                  {
   	               	msg ("You finished your quest. ");
         	            quest [7] = -1;
      	            }
                  }

						ujmij_item (chosen_tool_id, 1);
         	      break;
					}
			      else if (turn_to_do < 0)
			      {
		   	   	msg ("Continue healing (y/n) ?");

			         if (answer ())
   	   		   	turn_to_do *= -1;

			        	msg_reset ();
    			  	}
            	else if (turn_to_do == 10000)
	            	break;
				}
			   turn_to_do = 0;
	      }
   	}
   	else if (typ_p == 6 && (kod_o = obstacles_planszy [x_pos] [y_pos]) != -1)		// fixing tool
      {
			if (item_specials1 [kod_o] == -1)			// -1 = broken
      	{
	      	msg ("<You start to fix ");
   	      enter_item (kod_o, COLOR_GRAY);
      	   kropka (COLOR_GRAY);

	         turn_to_do = 10;

			   while (turn_to_do > 0)
			   {
			     	turn_to_do --;
		   	   turn ();

			      if (!turn_to_do)
		      	{
               	if (_SCIENCE > losuj (3, 6))
                  {
	      	      	msg ("You fixed ");
		   		      enter_item (kod_o, COLOR_GRAY);
							kropka (COLOR_GRAY);
         	         item_specials1 [kod_o] = 1;

							if (item_group [kod_o] == 62 && item_type [kod_o] == 2)
               	   {
                  		msg ("You finished your quest. ");
                     	quest [9] = -1;
                        gain_achievement (15);
	                  }
                     else if (item_group [kod_o] == 64 && item_type [kod_o] == 1)		// core 64 terminal
                     {
                       	gain_achievement (17);
                        quest [11] = -1;
                     }
                  }
                  else
                  {
	      	      	msg ("You failed to fix ");
		   		      enter_item (kod_o, COLOR_GRAY);
							kropka (COLOR_GRAY);
                  }
         	      break;
					}
			      else if (turn_to_do < 0)
			      {
		   	   	msg ("Continue fixing (y/n) ?");

			         if (answer ())
   	   		   	turn_to_do *= -1;

			        	msg_reset ();
    			  	}
            	else if (turn_to_do == 10000)
	            	break;
				}
			   turn_to_do = 0;
	      }
   	}
      else
	   	msg ("You don't know how to use it. ");
   }
}

void event_blade (int chosen_blade_id, char event_type, int x_pos, int y_pos)
{
	int monster_kod;
   int typ_p;
   int damage1;
   int test1;

   typ_p = item_type [chosen_blade_id];

	if (event_type == -1)
   {
		if (typ_p == 1)		// sting
      {
	   	monster_kod = monsters_planszy [x_pos] [y_pos];

			if (monster_kod >= 0)
      	{
	      	msg ("<The blade immediately shoots from mechanical claws..._");
        	   monster_aim [monster_kod] = -1;
         	test1 = abilities [_MELEE_ATTACK] - losuj (1, 20);
				ujmij_item (chosen_blade_id, 1);

            if (test1 > 0)
            {
					enter_monster (monster_code [monster_kod], COLOR_GRAY, -1000, 0);
	   	   	msg (" is hit with your sting!");

		   		damage1 = rzut (item_dices [chosen_blade_id]);
					monster_hp [monster_kod] -= damage1;

	            if (monster_hp [monster_kod] < 1)
   	         {
						enter_monster (monster_code [monster_kod], COLOR_GRAY, -1000, 0);
         	   	msg (" is assassinated!");
			   		killed_monsters [0] ++;
		      		killed_monsters [monster_code [monster_kod]] ++;
						gain_experience (monster_exp [monster_kod]);
      	         delete_monster (-1, monster_kod, 0);
	            }
            }
            else
            {
            	msg ("<Bad luck!");
               msg ("You missed");
					enter_monster (monster_code [monster_kod], COLOR_GRAY, -1000, 0);
               kropka (COLOR_GRAY);
            }

           	turn ();
	      }
         else
         	msg ("<There is no suitable victim!");
   	}
   }
}

