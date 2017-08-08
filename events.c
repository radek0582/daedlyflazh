#include "deklaracje.h"

void event (int x_pos, int y_pos)
{
   int floor_type;
   char ruch = key;
   char coverers_amount;
   char stan_type;
   int obstacle_type;
   int i, kod_przedmiotu, grupa_p;

	monster_id = monsters_planszy [x_pos] [y_pos];

	if (litera || kolumna)
		msg_reset ();

	if (monster_id >= 0)
	{
   	if (monster_aim [monster_id] == -5 || monster_aim [monster_id] == -6)
      {
      	if (cl_id != 1999)
         {
				msg ("Do you really want to attack");
   	      enter_monster (monster_code [monster_id], 7, -1000, 0);
      	   msg (" (y/n) ?");

				if (answer ())
   	      {
	   	     	msg_reset ();
				  	monster_aim [monster_id] = -1;
         		attack (monster_id, 0, 0);
	         }
				else
	   	     	msg_reset ();
         }
         else		// wilderness
         {
         	enter_perm = 1;
         }
      }
      else
			attack (monster_id, 0, 0);
	}
   else
   	enter_perm = 1;

	if (enter_perm)		// na drodze nie ma potwora
	{
   	enter_perm = 0;
		floor_type = floor_planszy [x_pos] [y_pos];

     	if (floor_type != floor_planszy [h_pos] [v_pos])	// zmiana rodzaju terenu
      {
	      if (floor_type == 15)
   	   {
         	msg ("Do you want to dive into water (y/n) ?)");

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

      if (floor_type >= 1000 && floor_type <= 2000)		// brzeg planszy
      {
      	if (floor_type >= 1011 && floor_type <= 1014)
         {
	     	 	msg ("You crash into hard ");
   	     	enter_floor (floor_type, 7, -1000);
      	   msg ("! ");
  	      	event_cost (2, floor_type);	
         }
         else
	  	   	change_location (ruch);
      }
		else if (floor_type == 151)
			msg ("These mountains are too bold to climb.");
		else if (floor_type == 150)
        	msg ("You need a boat or powerful magic to cross the sea.");
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
			msg ("Do you want to enter area to scale this mountains (y/n) ?");

         if (answer ())
           	change_location (ruch);
         else
          	msg_reset ();
      }
		else if (floor_type >= 0 && floor_type <= 5 || floor_type == 28)
  	      enter_perm = 1;
      else if (floor_type >= 6 && floor_type <= 10)
  	   {
     	 	msg ("You pass beneath");
        	enter_floor (floor_type, 7, -1000);
         msg (". ");
         enter_perm = 1;
      }
      else if (floor_type >= 11 && floor_type <= 14)
  	   {
     	 	msg ("You crash into");
        	enter_floor (floor_type, 7, -1000);
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
            msg ("You see");
            enter_item (kod_przedmiotu, 7);
            kropka (7);
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
	      		msg ("You see");
		         enter_item (kod_przedmiotu, 7);
					kropka (7);
            }
	      }
	      else if (stan_type == 5) 		// item + coverer(s)
   	   {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
            change_position (ruch);

            for (i = 0; i < coverers_amount; i ++)
            	action_coverer (-1, x_pos, y_pos, i);

      		msg ("You see");
	         enter_item (kod_przedmiotu, 7);
				kropka (7);
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

	      		msg ("You see");
		         enter_item (kod_przedmiotu, 7);
					kropka (7);
            }
         }
	      else if (stan_type == 8)		// several items
   	   {
      		msg ("Several items are lying here.");
            change_position (ruch);
			}
	      else if (stan_type == 9)		// several items + obstacle
   	   {
         	event_obstacle (ruch, obstacle_type);

            if (enter_perm)
	      		msg ("Several items are lying here.");
	      }
	      else if (stan_type == 10)		// several items + coverer(s)
   	   {
         	coverers_amount = coverers_planszy [x_pos] [y_pos] [0];
            change_position (ruch);

            for (i = 0; i < coverers_amount; i ++)
            	action_coverer (-1, x_pos, y_pos, i);

      		msg ("Several items are lying here.");
	      }

         if (enter_perm)
         {
         	enter_floor (floor_type, 7, 0);
            kropka (7);
            enter_perm = 0;
         }
	   }
   }

   turn ();
}

void event_obstacle (char ruch, int kod_o)
{
	int grupa_o = item_group [kod_o];
   int obstacle_type = item_type [kod_o];

   if (grupa_o == 50)		// stairs
   {
     	enter_item (kod_o, 7);
      enter_perm = 1;
  	   change_position (ruch);
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
   else if (grupa_o == 53)	// altar
   {
      enter_perm = 1;
     	change_position (ruch);
      msg ("You see");
      enter_item (kod_o, 7);
      kropka (7);
   }
}

char event_monster (int attacker_id, int x_pos, int y_pos)
{
   char coverers_amount;
   char stan_type;
   int obstacle_type;
	char event_code = 0;
   int floor_type;
   int monster_kod;

	monster_kod = monsters_planszy [x_pos] [y_pos];

	if (monster_kod == monster_aim [attacker_id])
		monster_attack (attacker_id, monster_kod, 0, 0);
	else if (monster_kod == -15)
	{
      floor_type = floor_planszy [x_pos] [y_pos];

      if (floor_type >= 1 && floor_type <= 5)
         enter_perm = 1;
      else if (floor_type == 21)
        	enter_perm = 1;
      else if (floor_type == 22)
        	enter_perm = 1;
      else if (floor_type == 23)
        	enter_perm = 1;

		if (enter_perm)
      {
			stan_type = stan_planszy [x_pos] [y_pos];

	      if (!stan_type)			// just floor
   	      enter_perm = 1;
	      else if (stan_type == 1)		// one item
   	      enter_perm = 1;
	      else if (stan_type == 2)		// only obstacle
   	   {
      		obstacle_type = obstacles_planszy [x_pos] [y_pos];

				if (item_group [obstacle_type] == 50)
   	      	enter_perm = 1;
      	   else if (item_group [obstacle_type] == 51)
	         {
		      	trap (monster_code [attacker_id], obstacle_type);
	   	      enter_perm = 1;
         	}
	         else if (item_group [obstacle_type] == 52)
   	      	door (monster_code [attacker_id], obstacle_type);
			}
	      else if (stan_type == 3)		// several items
   	      enter_perm = 1;
	      else if (stan_type == 4)		// item + obstacle
   	   {
      	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

	         if (item_group [obstacle_type] == 51)
		      	trap (monster_code [attacker_id], obstacle_type);
	         else if (item_group [obstacle_type] == 52)
   	      	door (monster_code [attacker_id], obstacle_type);
	      }
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

   return event_code;
}

char event_throw (int shooter, char attack_type, int spell_type, int x_pos, int y_pos, int x_, int y_)
{
	int kod_p;
	char stan_rzutu = 1;
	int cel_ataku = monsters_planszy [x_pos] [y_pos];
   int i_color;
   int x_wzg = x_pos - x_;
   int y_wzg = y_pos - y_;
   char directed_arrow;
	int _h_pos_pl = h_pos_pl, _h_pos, _x_pos;
	int _v_pos_pl = v_pos_pl, _v_pos, _y_pos;
	int kod_item, kod_cov, kod_stan, a, i, j, k, _j, _k, j_, k_, floor_type;
	char petla = 1;

	if (x_pos >= x_planszy || y_pos >= y_planszy || x_pos < 0 || y_pos < 0)
   	return 0;

	if (check_own_visibility (h_cur, v_cur))
   {
	   ustaw_kursor ();
		gotoxy (h_pos_pl + LB, v_pos_pl + UB);
   	check_visible_monsters ();
		_h_pos = h_pos;
   	_v_pos = v_pos;
		h_pos = h_cur + h_pos_pl - 30;
   	v_pos = v_cur + v_pos_pl - 10;
	   ustaw_gracza ();
		move_visible_monsters ();

//		if (check_own_visibility (h_pos, v_pos))
//		   put_char (mem_planszy [_h_pos] [_v_pos], _h_pos, _v_pos);

		h_pos = _h_pos;
		v_pos = _v_pos;
   }

   if (x_wzg == 1 && y_wzg == 1)
   {
   	directed_arrow = '\\';
      h_cur ++;
      v_cur ++;
   }
   else if (x_wzg == -1 && y_wzg == -1)
   {
   	directed_arrow = '\\';
      h_cur --;
      v_cur --;
   }
   else if (x_wzg == 1 && y_wzg == 0)
   {
   	directed_arrow = '-';
      h_cur ++;
   }
   else if (x_wzg == -1 && y_wzg == 0)
   {
   	directed_arrow = '-';
      h_cur --;
   }
   else if (x_wzg == 1 && y_wzg == -1)
   {
   	directed_arrow = '/';
      h_cur ++;
      v_cur --;
   }
   else if (x_wzg == -1 && y_wzg == 1)
   {
   	directed_arrow = '/';
      h_cur --;
      v_cur ++;
   }
   else if (x_wzg == 0 && y_wzg == 1)
   {
   	directed_arrow = '|';
      v_cur ++;
   }
   else if (x_wzg == 0 && y_wzg == -1)
   {
   	directed_arrow = '|';
      v_cur --;
   }

	if (check_own_visibility (h_cur, v_cur))
   {
   	move_area ();

//		if (shooter == -1)	// strzela gracz
		if (1)
   	{
	   	if (attack_type == 1)
   	   {
           	i_color = item_icon [item_body [_MWAMMO]] / 256 * 256;

  	      	if (item_type [item_body [_MWAMMO]] == 21)	// arrow
     	      {
					put_char_on_cursor (directed_arrow + i_color);
			   	wait (500);
           	}
            else if (item_type [item_body [_MWAMMO]] == 22)	// shuriken
  	         {
              	if (hand == 1)
  	            {
     		      	put_char_on_cursor ('\\' + i_color);
	     		      wait (35);
 	      		   putch (8);
     	      		put_char_on_cursor ('|' + i_color);
      	      	wait (35);
     	      		putch (8);
  	      	   	put_char_on_cursor ('/' + i_color);
   	      	   wait (35);
  	   	      	putch (8);
    	   	   	put_char_on_cursor ('-' + i_color);
      	   	   wait (35);
               }
  	            else
     	         {
     		      	put_char_on_cursor ('/' + i_color);
      		      wait (35);
  	      		   putch (8);
     	      		put_char_on_cursor ('|' + i_color);
  	      	      wait (35);
  	  	      		putch (8);
     	   	   	put_char_on_cursor ('\\' + i_color);
      	   	   wait (35);
  	      	   	putch (8);
    	      		put_char_on_cursor ('-' + i_color);
      	      	wait (35);
               }
     	      }
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
   	else
	   {
   		switch (attack_type)
      	{
	      	case 1:
   	         break;
      		case 2:				// lightning ball
					textcolor (14);
					putch ('*');
				   wait (100);
         	   break;
	      }
   	}
	}
   else
   {
//   	debug (h_cur, v_cur, 1000, 1);
/*   	_h_pos_pl = h_pos_pl;
      _v_pos_pl = v_pos_pl;
   	ustaw_kursor ();
	   check_visible_monsters ();
		_h_pos = h_pos;
	   _v_pos = v_pos;
		h_pos = h_cur + h_pos_pl - 30;
	   v_pos = v_cur + v_pos_pl - 10;
   	ustaw_gracza ();
	   i = 0;

   	while ((a = visible_monsters [i]) != -15)		// wyswietla widziane potwory
		{
  			_x_pos = h_pos_mon [a];
   		_y_pos = v_pos_mon [a];
	     	put_char (monster [a], _x_pos, _y_pos);
  			i ++;
	   }

//   	if (check_own_visibility (h_pos, v_pos))
//		   put_char (player, _h_pos, _v_pos);

		h_pos = _h_pos;
   	v_pos = _v_pos;*/
   }

   kod_p = monsters_planszy [h_cur] [v_cur];

   if (kod_p >= -1)
   {
		if (shooter >= 0)		// monster strzela
	   {
//   		monster_attack (shooter, cel_ataku, attack_type, spell_type);
   		stan_rzutu = 0;
	   }
	   else 				// gracz strzela
   	{
	   	attack (cel_ataku, attack_type, spell_type);
   	   stan_rzutu = 0;
  	   }
   }

   if (spell_type < 200)		// ricochet shot
   {
   	if (plansza [x_pos] [y_pos] > 8192)
      {
	   	if (directed_arrow == '-')		// po zetknieciu ze sciana
   	   	stan_rzutu = 2;
      	else if (directed_arrow == '/')
         	stan_rzutu = 3;
      }
   }
	else if (spell_type == 201)			// web
   {
   	if (plansza [x_pos] [y_pos] <= 8192)		// po zetknieciu ze sciana
      {
	     	ekwipunek (1200, -5, 7);
		   h_pos_item [item_id] = x_pos;
      	v_pos_item [item_id] = y_pos;
			put_item (item_id);
      }
      else
      	stan_rzutu = 0;
   }

/*	if (check_own_visibility (h_cur, v_cur))
   {
   	if (kod_p >= 0)
		   put_char_on_cursor (monster [kod_p]);
      else if (kod_p == -1)
		   put_char_on_cursor (player);
      else // item lub plansza
		   put_char_on_cursor (mem_planszy [h_cur] [v_cur] = plansza [h_cur] [v_cur]);
   }*/

   if (!stan_rzutu)
   {
   }

   return stan_rzutu;
}
