#include "deklaracje.h"

void move_xy (int x_pos, int y_pos)
{
	int kod_p, swap_mon, kod_f1, kod_f2;

	if (litera || kolumna)
		msg_reset ();

	kod_p = monsters_planszy [x_pos] [y_pos];

	if (kod_p >= 0)
	{
   	if (monster_aim [kod_p] != -1)
      {
      	if (cl_id != 1999)
         {
         	if (monster_aim [kod_p] != -1)
            {
            	if (!autoswap)
               {
						msg ("Do you want to attack ");
  				      enter_monster (monster_code [kod_p], COLOR_GRAY, -1000, 0);
   		   	   msg (" (y/n) ?");

						if (answer ())
 			   	   {
   			   	  	msg_reset ();
  	      	   		attack (kod_p, kod_p, 0, 0);
            	      reputation_change (kod_p);
                  	turn ();
	    	      	}
						else
      	         {
   				     	msg_reset ();
               	}
               }
               else
               {
		            swap_mon = kod_p;
						temp1 = h_pos_mon [swap_mon];
                  temp2 = v_pos_mon [swap_mon];
   	         	kod_f1 = floor_planszy [h_pos] [v_pos];
	               kod_f2 = floor_planszy [h_pos_mon [swap_mon]] [v_pos_mon [swap_mon]];

	            	if (monster_code [swap_mon] < 1100 && monster_aim [swap_mon] == -5 && (kod_f2 == kod_f1 || kod_f1 >= 0 && kod_f1 <= 10))		// ten sam teren, neutralny NPC
	               {
							key = 0;
      	            refresh_view_monsters ();

	                  monsters_planszy [h_pos_mon [swap_mon]] [v_pos_mon [swap_mon]] = -1;
   	               monsters_planszy [h_pos] [v_pos] = swap_mon;

	                  h_pos_mon [swap_mon] = h_pos;
   	               v_pos_mon [swap_mon] = v_pos;

	                  h_pos = temp1;
   	               v_pos = temp2;
						   ustaw_gracza ();
						   rysuj_view_range ();
	                  verify_visible_monsters ();
   	               event (h_pos, v_pos);
	               	msg ("You swapped position");
	               }
	               else
   	            {
	                  enter_monster (monster_code [swap_mon], COLOR_GRAY, 0, 0);
   	            	msg (" resists");
	               }
               }
            }
         }
         else		// wilderness
         {
         	enter_perm = 1;
         }
      }
      else
      {
			attack (kod_p, kod_p, 0, 0);
         turn ();
      }
	}
   else
   	event (x_pos, y_pos);
}

void event (int x_pos, int y_pos)
{
   int floor_type, kod_p;
   char ruch = key, do_turn = 1;
   char coverers_amount;
   char stan_type;
   int obstacle_type;
   int i, kod_przedmiotu, grupa_p, swap_mon;

	if (litera || kolumna)
		msg_reset ();

//	if (enter_perm)		// na drodze nie ma potwora
//	{
	  	enter_perm = 0;
		floor_type = floor_planszy [x_pos] [y_pos];

     	if (floor_type != floor_planszy [h_pos] [v_pos])	// zmiana rodzaju terenu
      {
	      if (floor_type == 15)
   	   {
         	msg ("Do you want to dive into water (y/n) ?");

            if (answer ())
      	   	enter_perm = 1;

  	        	msg_reset ();
         }
	      else if (floor_type == 16)
   	   {
         	msg ("Do you want to dive into lava (y/n) ?");

  	         if (answer ())
     		   	enter_perm = 1;

	        	msg_reset ();
	      }
	      else if (floor_type == 17)
   	   {
         	msg ("Do you want to enter freezing area (y/n) ?");

            if (answer ())
      	   	enter_perm = 1;

  	        	msg_reset ();
         }
	      else if (floor_type == 21)
   	   {
	      	msg ("Do you want to swim in water (y/n) ?");

	         if (answer ())
      	   	enter_perm = 1;

  	        	msg_reset ();
         }
	      else if (floor_type == 22)		// ice
	         enter_perm = 1;
	      else if (floor_type == 23)
   	   {
	      	msg ("Do you want to swim in lava (y/n) ?");

   	      if (answer ())
         		enter_perm = 1;

  	        	msg_reset ();
         }
	      else if (floor_type == 26)
      		i = select_a_tool ();
      }
      else
      	enter_perm = 1;

      if (floor_type >= 1000 && floor_type <= 1149)		// brzeg planszy (w lokacji, nie mapie glownej)
      {
      	if (floor_type >= 1011 && floor_type <= 1014)
         {
	     	 	msg ("You crash into hard ");
   	     	enter_floor (floor_type, COLOR_GRAY, -1000);
      	   msg ("! ");
  	      	event_cost (2, floor_type);
         }
         else
	  	   	change_location (ruch);
      }
		else if (floor_type == 151)
			msg ("These mountains are too bold to climb. ");
		else if (floor_type == 150 || floor_type == 1150)
        	msg ("To cross the ocean you need a boat. ");
		else if (floor_type == 154)
		{
        	msg ("Do you want to enter area to dive into the water (y/n) ?");

			if (answer ())
           	change_location (ruch);
			else
           	msg_reset ();
      }
      else if (floor_type == 152)
      {
			msg ("Do you want to enter area to scale this mountains (y/n) ? ");

         if (answer ())
           	change_location (ruch);
         else
          	msg_reset ();
      }
		else if (floor_type % 1000 >= 0 && floor_type % 1000 <= 10 || floor_type >= 100 && floor_type <= 130 || floor_type >= 28 && floor_type <= 48 || floor_type == 19)
  	      enter_perm = 1;
      else if (floor_type % 1000 >= 11 && floor_type % 1000 <= 14)
  	   {
     	 	msg ("You crash into ");
        	enter_floor (floor_type, COLOR_GRAY, -1000);
         msg ("! ");
  	      event_cost (2, floor_type);	// crashing into wall
      }
      else if (cl_id == 1999)
      	enter_perm = 1;

		if (enter_perm)
      {
			kod_przedmiotu = items_planszy [x_pos] [y_pos];
			stan_type = stan_planszy [x_pos] [y_pos];
         obstacle_type = obstacles_planszy [x_pos] [y_pos];

	      if (!stan_type)					// just floor
          	change_position (ruch);
	      else if (stan_type == 1)		// item
         {
      	   change_position (ruch);
            msg ("You see ");
            enter_item (kod_przedmiotu, COLOR_GRAY);
            kropka (COLOR_GRAY);
         }
	      else if (stan_type == 2)		// only obstacle
         	event_obstacle (ruch, obstacle_type);
         else if (stan_type == 3)		// only coverer(s)
         {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
            change_position (ruch);

            for (i = 0; i < coverers_amount; i ++)
            	action_coverer (-1, x_pos, y_pos, i);
         }
	      else if (stan_type == 4)			// item + obstacle
   	   {
	        	event_obstacle (ruch, obstacle_type);

				if (enter_perm)
            {
	      		msg ("You see ");
		         enter_item (kod_przedmiotu, COLOR_GRAY);
					kropka (COLOR_GRAY);
            }
	      }
	      else if (stan_type == 5) 		// item + coverer(s)
   	   {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
            change_position (ruch);

            for (i = 0; i < coverers_amount; i ++)
            	action_coverer (-1, x_pos, y_pos, i);

      		msg ("You see ");
	         enter_item (kod_przedmiotu, COLOR_GRAY);
				kropka (COLOR_GRAY);
	      }
         else if (stan_type == 6)		// obstacle + coverer(s)
         {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
         	event_obstacle (ruch, obstacle_type);

				if (enter_perm)
            {
	            for (i = 0; i < coverers_amount; i ++)
   	         	action_coverer (-1, x_pos, y_pos, i);
            }
         }
         else if (stan_type == 7)		// item + obstacle + coverer(s)
         {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
         	event_obstacle (ruch, obstacle_type);

				if (enter_perm)
            {
	            for (i = 0; i < coverers_amount; i ++)
   	         	action_coverer (-1, x_pos, y_pos, i);

	      		msg ("You see ");
		         enter_item (kod_przedmiotu, COLOR_GRAY);
					kropka (COLOR_GRAY);
            }
         }
	      else if (stan_type == 8)		// several items
   	   {
      		msg ("Several items are lying here. ");
            change_position (ruch);
			}
	      else if (stan_type == 9)		// several items + obstacle
   	   {
         	event_obstacle (ruch, obstacle_type);

            if (enter_perm)
	      		msg ("Several items are lying here. ");
	      }
	      else if (stan_type == 10)		// several items + coverer(s)
   	   {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
            change_position (ruch);

            for (i = 0; i < coverers_amount; i ++)
            	action_coverer (-1, x_pos, y_pos, i);

      		msg ("Several items are lying here. ");
	      }

         if (enter_perm)
         {
         	enter_floor (floor_type, COLOR_GRAY, 0);
            kropka (COLOR_GRAY);
            enter_perm = 0;
         }
	   }
//   }

	if (do_turn)
	   turn ();
}

void event_obstacle (char ruch, int kod_o)
{
	int grupa_o = item_group [kod_o];
   int obstacle_type = item_type [kod_o];

   if (grupa_o == 50 || grupa_o == 53 || grupa_o == 55|| grupa_o == 61)		// stairs lub altar lub grave lub boat
   {
      enter_perm = 1;
  	   change_position (ruch);
      msg ("You see ");
      enter_item (kod_o, COLOR_GRAY);
      kropka (COLOR_GRAY);
   }
   else if (grupa_o == 51)		// trap
   {
      enter_perm = 1;
  	   change_position (ruch);
  		trap (-1, kod_o);
   }
   else if (grupa_o == 52 || grupa_o == 54)
   {
     	if (obstacle_type == 2)		// otwarte
      {
	      enter_perm = 1;
	     	change_position (ruch);
      }

    	door (-1, kod_o);
   }
}

/*char event_monster (int attacker_id, int x_pos, int y_pos)
{
   char coverers_amount;
   char stan_type;
   int obstacle_type;
	char event_code = 0;
   int floor_type;
   int monster_kod;

	monster_kod = monsters_planszy [x_pos] [y_pos];

	if (monster_kod == monster_aim [attacker_id])
		monster_attack (attacker_id, monster_kod, monster_kod, 0, 0);
	else if (monster_kod == -15)
	{
      floor_type = floor_planszy [x_pos] [y_pos];

      if (floor_type >= 1 && floor_type <= 10 || floor_type >= 100 && floor_type <= 120 || floor_type == 28)
      {
      	if (monster_char [attacker_id] == -1 || monster_char [attacker_id] == floor_type)			// por. sie potwora po okr. terenie tylko
  	         enter_perm = 1;
      }
      else if (floor_type == 21)
        	enter_perm = 1;
      else if (floor_type == 22)
        	enter_perm = 1;
      else if (floor_type == 23)
        	enter_perm = 1;

		if (enter_perm)
      {
			stan_type = stan_planszy [x_pos] [y_pos];
         enter_perm = 0;

	      if (!stan_type)			// just floor
   	      enter_perm = 1;
	      else if (stan_type == 1)		// one item
   	      enter_perm = 1;
	      else if (stan_type == 2)		// only obstacle
   	   {
      		obstacle_type = obstacles_planszy [x_pos] [y_pos];

				if (item_group [obstacle_type] == 50 || item_group [obstacle_type] == 53 || item_group [obstacle_type] == 55)
   	      	enter_perm = 1;
      	   else if (item_group [obstacle_type] == 51)
	         {
		      	trap (monster_code [attacker_id], obstacle_type);
	   	      enter_perm = 1;
         	}
	         else if (item_group [obstacle_type] == 52 || item_group [obstacle_type] == 54)
   	      	door (monster_code [attacker_id], obstacle_type);
			}
	      else if (stan_type == 4)		// item + obstacle
   	   {
      	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

	         if (item_group [obstacle_type] == 51)
		      	trap (monster_code [attacker_id], obstacle_type);
	         else if (item_group [obstacle_type] == 52)
   	      	door (monster_code [attacker_id], obstacle_type);
	      }
	      else if (stan_type == 8)		// several items
   	      enter_perm = 1;
	      else if (stan_type == 9)		// severeal items + obstacle
   	   {
      	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

	         if (item_group [obstacle_type] == 51)
		      	trap (monster_code [attacker_id], obstacle_type);
	         else if (item_group [obstacle_type] == 52)
   	      	door (monster_code [attacker_id], obstacle_type);
	      }
		}
   }
   event_code = enter_perm;

   return event_code;
}*/

char event_throw (int shooter, char attack_type, int spell_type, int x_pos, int y_pos, int x_, int y_, int h_aim, int v_aim)
{
	int kod_p, h_cur_temp = h_cur, v_cur_temp = v_cur;
	char stan_rzutu = 1;
	int cel_ataku;
   int i_color;
   int x_wzg = x_pos - x_;
   int y_wzg = y_pos - y_;
   char directed_arrow;
	int _h_pos;
	int _v_pos;
	int kod_item, kod_cov, kod_stan, a, i, j, k, _j, _k, j_, k_, floor_type;
	char petla = 1;
   int radius, osemka;
   int weapon_range;
   int h_shooter, v_shooter;

	if (attack_type == 1)
	   weapon_range = item_specials1 [item_body [_SIDEARM_SLOT]];
   else
	   weapon_range = item_specials1 [item_body [_PRIME_SLOT]];

   if (shooter == -1)
	  	cel_ataku = monsters_planszy [h_aim] [v_aim];
   else
   	cel_ataku = monster_aim [shooter];

	if (x_pos >= x_planszy || y_pos >= y_planszy || x_pos < 0 || y_pos < 0)
   	return 0;

	if (shooter == -1 && check_own_visibility (h_cur, v_cur))
      refresh_view_monsters ();

   if (x_wzg == 1 && y_wzg == 1)					// osemka 8
   {
   	directed_arrow = '\\';
      h_cur ++;
      v_cur ++;
      osemka = 8;
   }
   else if (x_wzg == -1 && y_wzg == -1)		// 1
   {
   	directed_arrow = '\\';
      h_cur --;
      v_cur --;
      osemka = 1;
   }
   else if (x_wzg == 1 && y_wzg == 0)			// 5
   {
   	directed_arrow = '-';
      h_cur ++;
      osemka = 5;
   }
   else if (x_wzg == -1 && y_wzg == 0)			// 4
   {
   	directed_arrow = '-';
      h_cur --;
      osemka = 4;
   }
   else if (x_wzg == 1 && y_wzg == -1)			// 3
   {
   	directed_arrow = '/';
      h_cur ++;
      v_cur --;
      osemka = 3;
   }
   else if (x_wzg == -1 && y_wzg == 1)			// 1
   {
   	directed_arrow = '/';
      h_cur --;
      v_cur ++;
      osemka = 1;
   }
   else if (x_wzg == 0 && y_wzg == 1)			// 7
   {
   	directed_arrow = '|';
      v_cur ++;
      osemka = 7;
   }
   else if (x_wzg == 0 && y_wzg == -1)			// 2
   {
   	directed_arrow = '|';
      v_cur --;
      osemka = 2;
   }

   if (attack_type == 2 && plansza [h_cur] [v_cur] > 8192 || shooter == -1 && sqrt (pow (h_cur - h_pos, 2) + pow (v_cur - v_pos, 2)) - 0.7 > weapon_range)
   {
   	if (1)//shooter == -1 && item_ident [item_body [_PRIME_SLOT]] > 10 || shooter != -1)
		{
			h_cur = h_cur_temp;
   	   v_cur = v_cur_temp;
      	stan_rzutu = 0;
	      move_area ();
      }
   }
	else if (check_own_visibility (h_cur, v_cur))
   {
   	temp1 = h_cur;
      temp2 = v_cur;

   	if (shooter == -1)
	   	move_area ();

   	if (attack_type <= 2)
  	   {
      	if (shooter == -1)
         {
         	if (attack_type == 1)
		        	i_color = item_icon [item_body [_SIDEARM_SLOT]] / 256 * 256;
            else
		        	i_color = item_icon [item_body [_PRIME_SLOT]] / 256 * 256;
         }
         else
         	i_color = monster [shooter] / 256 * 256;

      	if ((attack_type == 2 || attack_type == 1 && item_type [item_body [_SIDEARM_SLOT]] != 22) && shooter == -1 || shooter >= 0)
				put_char_on_cursor_shoot (shooter, directed_arrow + i_color, 0, 0);
         else if (attack_type == 1 && item_type [item_body [_SIDEARM_SLOT]] == 22)			// shuriken
         {
	      	put_char_on_cursor_shoot (shooter, '\\' + i_color, 0, 0);
  		      wait (35);
     		   addch (8);
      		put_char_on_cursor_shoot (shooter, '|' + i_color, 0, 0);
  	      	wait (35);
      		addch (8);
     	   	put_char_on_cursor_shoot (shooter, '/' + i_color, 0, 0);
	     	   wait (35);
  	      	addch (8);
   	   	put_char_on_cursor_shoot (shooter, '-' + i_color, 0, 0);
  	   	   wait (35);
         }
         else
	      	put_char_on_cursor_shoot (shooter, '*' + i_color, 0, 0);

         if (shooter == -1)
	         wait (100);
         else
         	wait (50);
		}
   	else				// spell or wand
      {
        	switch (spell_type)
         {
           	case 1:
            case 101:
            case _LIGHTNING_BALL:
              	i_color = YELLOW;
               break;
	        	case 2:
            case 102:
            case 201:
            case 302:
              	i_color = WHITE;
               break;
			}

        	if (spell_type < 200)				// ray lub bolt ricocheting
         {
				put_char (directed_arrow + i_color, x_pos, y_pos);
		   	wait (100);
         }
        	else if (spell_type < 300)			// bolt nie ricocheting
         {
				put_char (directed_arrow + i_color, x_pos, y_pos);
		   	wait (100);
         }
	   }
	}

	kod_p = monsters_planszy [h_cur] [v_cur];

   if (stan_rzutu && kod_p >= -1)
   {
		if (shooter >= 0)		// monster strzela
   		stan_rzutu = monster_attack (shooter, cel_ataku, kod_p, attack_type, spell_type);
	   else 				// gracz strzela
	   	stan_rzutu = attack (cel_ataku, kod_p, attack_type, spell_type);
   }

   if (h_aim == h_cur && v_aim == v_cur)
   	stan_rzutu = 0;

/*   if (spell_type < 200)		// ricochet shot
   {
   	if (plansza [x_pos] [y_pos] > 8192)
      {
	   	if (directed_arrow == '-')		// po zetknieciu ze sciana
   	   	stan_rzutu = 2;
      	else if (directed_arrow == '/')
         	stan_rzutu = 3;
      }
   }*/

	if (stan_rzutu && spell_type == 201)			// web
   {
   	if (plansza [h_cur] [v_cur] <= 8192)
      {
	     	ekwipunek (1200, -5, COLOR_GRAY);
		   h_pos_item [item_id] = h_pos;
      	v_pos_item [item_id] = v_pos;
			put_item (item_id);
      }
      else
      	stan_rzutu = 0;
   }
   else		// strzaly etc
   {
   	if (plansza [h_cur] [v_cur] > 8192)
      	stan_rzutu = 0;
   }

   if (attack_type == 2 && stan_rzutu == 0)
   {
   	if (shooter == -1 && item_ident [item_body [_PRIME_SLOT]] > 10 || shooter != -1)		// wybuchowa amunicja
	   	create_a_ball (shooter, h_cur, v_cur, 3, 3, spell_type);
   }

	if (check_own_visibility (h_cur, v_cur))
   {
   	if (stan_rzutu && kod_p >= 0)
		   put_char_on_cursor_shoot (shooter, monster [kod_p], 0, 0);
      else if (kod_p == -1)
		   put_char_on_cursor_shoot (shooter, player, 0, 0);
      else // item lub plansza
		   put_char_on_cursor_shoot (shooter, mem_planszy [h_cur] [v_cur], 0, 0);// = plansza [h_cur] [v_cur]);
   }

   if (!stan_rzutu)
   {
   }

   return stan_rzutu;
}

void door (int guest, int door_id)
{
	int i, icon_d = item_icon [door_id];

	if (icon_d > 8192)
   	icon_d -= 8192;

	if (guest == -1)		// na drzwi wchodzi gracz
   {
  		switch (item_type [door_id])
      {
  	   	case 1:		// closed
     	   	item_type [door_id] = 2;
				item_icon [door_id] = icon_d / 256 * 256 + 47;
            msg ("<You open the ");
            enter_item (door_id, COLOR_GRAY);
            kropka (COLOR_GRAY);
            plansza [h_pos_item [door_id]] [v_pos_item [door_id]] = item_icon [door_id];
            aktualizuj_pole (h_pos_item [door_id], v_pos_item [door_id]);
            break;
         case 2:		// opened
         	msg ("You pass through ");
            enter_item (door_id, COLOR_GRAY);
            kropka (COLOR_GRAY);
            break;
  	   	case 3:		// locked
            enter_item (door_id, COLOR_GRAY);
            msg (" is locked. ");

            if ((i = search_key (item_specials2 [door_id])) != -1)		// klucz ma gracz
            {
	     	   	item_type [door_id] = 2;
					item_icon [door_id] = icon_d / 256 * 256 + 47;
   	         msg ("<You open the ");
      	      enter_item (door_id, COLOR_GRAY);
               msg (" with ");
               enter_item (i, COLOR_GRAY);
         	   kropka (COLOR_GRAY);
	            plansza [h_pos_item [door_id]] [v_pos_item [door_id]] = item_icon [door_id];
   	         aktualizuj_pole (h_pos_item [door_id], v_pos_item [door_id]);
            }
            else
            	msg ("You don't have a proper key to open this door. ");
            break;
  	   }
   }
   else
   {
  		switch (item_type [door_id])
      {
      	case 1:
         	item_type [door_id] = 2;
            item_icon [door_id] = icon_d / 256 * 256 + 47;
            listening (1, h_pos_item [door_id], v_pos_item [door_id]);
            plansza [h_pos_item [door_id]] [v_pos_item [door_id]] = item_icon [door_id];
            aktualizuj_pole (h_pos_item [door_id], v_pos_item [door_id]);
            break;
  	   	case 2:
				enter_perm = 1;
            break;
  	   }
   }
}

void action_coverer (int kod_p, int x_pos, int y_pos, char coverer_no)	// akcja coverer'a przy wlazeniu nan
{
	int coverer_id = coverers [coverer_no];

   if (kod_p == -1)		// player
   {
   	if (item_type [coverer_id] == 1)		// web
      	msg ("You are standing in the web.");

      item_value_material [coverer_id] --;

      if (!item_value_material [coverer_id])
      {
			action_item (-2, h_pos_item [coverer_id], v_pos_item [coverer_id], 2, coverer_id);
         msg ("You destroyed webs!");
      }
      else
      	character_state [_MATTED] = 1;		// matted in webs
   }
}

void action_floor (int floor_type, int x_pos, int y_pos)		// akcja floor'a przy wlazeniu nan
{
	int kod_k, view_wall;
   int visibility;
   char result = 0;
   int kod_p = monsters_planszy [x_pos] [y_pos];

   if (kod_p == -1)					// player
   {
		if (floor_type == 21)		// czy woda pod graczem
  	   {
     	  	if (abilities [_CONDITION] < rand () % 30)
        	{
				msg ("You are drowning! ");
	         air -= rand () % 15;

   	      if (air < 0)
      	   	air = 0;

	         statystyki (14);
     	   }
        	else
        		msg ("You easily swimm the water. ");
      }
		else if (floor_type == 23)		// czy lava pod graczem
     	{
			msg ("You are burning! ");
     	   drain_health (0, COLOR_GRAY);
		}
   }
   else if (kod_p >= 0)
   {
      if (floor_type == 21 || floor_type == 23)
      {
			visibility = check_own_visibility (h_pos_mon [kod_p], v_pos_mon [kod_p]);

	      if (visibility)
   	   {
	        	msg ("You see ");
   			enter_monster (monster_code [kod_p], COLOR_GRAY, -1000, 0);
   	   }

	     	if (floor_type == 21)		// monster w wodzie
   	   {
	   	   switch (monster_code [kod_p])
	         {
   	        	case _FEMALE_CIVILIAN:
      	       	if (rand () % 5 > 1)
         	      	result = 1;
            	   else
	                	monster_hp [kod_p] -= rand () % 15;
   	            break;
      	     	default:
         	   	result = 1;
	               break;
				}

	         if (visibility)
   	      {
      	   	if (result)
						msg (" easily swims the water. ");
   	         else
						msg (" is drowing. ");
	         }
			}
     		else if (floor_type == 23)		// monster w lawie
	      {
	        	switch (monster_code [kod_p])
   	      {
      	    	default:
         	    	monster_hp [kod_p] -= rand () % 25;
	              	msg (" burns. ");
   	            break;
      	   }
			}
		}
   }

   if (floor_type >= 2000 && floor_type < 3000)		//	burning
   {
   	change_color (1, x_pos, y_pos);
   }
}

