#include "deklaracje.h"

void targeting (int shooter, char attack_type, int spell_type)		// shooter: -1 - gracz, 0... - enemy; attack_type: 1 - throw/shoot, 2 - spell, 3 - wand; spell_type: 1 - lightning ball, 12 - ice bolt...
{
	int temp_, a = 1, b = 0, c = 0, i, j, k, _j, _k, j_, k_, x, y, x_ = 0, y_ = 0, attacks;
   int weapon_range, x_wzg, y_wzg, h_shooter, v_shooter, kod_s, kod_mon, kod_p, bolt_range, x_temp, y_temp, view_ability;
   int x_pos_, y_pos_, x_pos, y_pos, equation, target_monster = 0;
	int _h_pos_pl = h_pos_pl, _h_pos, _x_pos, h_aim, v_aim, _h_cur = h_cur;
	int _v_pos_pl = v_pos_pl, _v_pos, _y_pos, _v_cur = v_cur;
  	int kod_item, kod_cov, kod_stan, floor_type = floor_planszy [h_pos] [v_pos];
   int char_code;
   char kierunek, throw_status = 1, target = 0;
   char shoot = 0;

   key = 0;

	if (shooter == -1)			// shooter = player
   {
//   	action_cost = 90;
      oblicz_stats ();
   	target = 1;
   	h_shooter = h_pos;		// strzelca horizontal
      v_shooter = v_pos;		// strzelca vertical
	   h_cur = h_aim = h_pos;				// celu horizontal
   	v_cur = v_aim = v_pos;				// celu vertical
   }
   else
   {
   	h_shooter = h_pos_mon [shooter];
      v_shooter = v_pos_mon [shooter];

      if (monster_aim [shooter] == -1)		// celem jest gracz
      {
     		h_cur = h_pos;
         v_cur = v_pos;
      }
      else
      {
	      h_cur = h_pos_mon [monster_aim [shooter]];
   	   v_cur = v_pos_mon [monster_aim [shooter]];
      }

   	x_wzg = sqrt (pow (h_cur - h_shooter, 2)) + 1;
      y_wzg = sqrt (pow (v_cur - v_shooter, 2)) + 1;
   }

   if (shooter == -1)
   {
/*      for (kod_p = 0; kod_p < monsters_amount; kod_p ++)
      	if (check_own_visibility (h_pos_mon [kod_p], v_pos_mon [kod_p]) == 2)			// potwor widzialny i w zasiegu wzroku
         {
         	h_aim = h_pos_mon [kod_p];
            v_aim = v_pos_mon [kod_p];
            break;
         }*/
   }

   while (target)			// namierzanie celu (tylko gracz)
   {
   	x_wzg = sqrt (pow (h_cur - h_shooter, 2)) + 1;
		y_wzg = sqrt (pow (v_cur - v_shooter, 2)) + 1;
	   x_pos_ = h_cur;
      y_pos_ = v_cur;
      textcolor (COLOR_GRAY);

		if (shooter == -1)		// player
      {
		   if (attack_type == 1)
			   weapon_range = item_specials1 [item_body [_SIDEARM_SLOT]];
		   else if (attack_type == 2)
			   weapon_range = item_specials1 [item_body [_PRIME_SLOT]];

	      clear_area (2, 23, 75, 24);
         gotoxy (2, 23);

         if (attack_type == 1)
         {
	         messages ("Weapon: ", 0, 32 + COLOR_GRAY);
     	      enter_item (item_body [_SIDEARM_SLOT], 32 + COLOR_GRAY);
            messages (" Ammo: ", 0, 32 + COLOR_GRAY);
            enter_ammo (item_ident [item_body [_SIDEARM_SLOT]], 32 + COLOR_GRAY);
            attacks = item_status [item_body [_SIDEARM_SLOT]];
         }
         else if (attack_type == 2)
         {
	         messages ("Weapon: ", 0, 32 + COLOR_GRAY);
     	      enter_item (item_body [_PRIME_SLOT], 32 + COLOR_GRAY);
            messages (" Ammo: ", 0, 32 + COLOR_GRAY);
            enter_ammo (item_ident [item_body [_PRIME_SLOT]], 32 + COLOR_GRAY);
            attacks = item_status [item_body [_PRIME_SLOT]];
         }

     		kod_mon = monsters_planszy [h_cur] [v_cur];
			gotoxy (2, 24);
         messages ("Target: ", 0, 32 + COLOR_GRAY);

			if (mem_planszy [h_cur] [v_cur] == 32)
   	   	messages ("Unknown", 0, 32 + COLOR_GRAY);

	      if (kod_mon >= 0 && (view_ability = check_own_visibility (h_cur, v_cur)) == 2)
         {
		      enter_monster (monster_code [kod_mon], 32 + COLOR_GRAY, 0, 0);
            messages (" [m]ore ", 0, 32 + COLOR_GRAY);

            if (abilities [_SCIENCE])
            {
               i = sqrt (monster_health [kod_mon]) + 1;

			      for (j = 0; j < i ; j ++)
			      {
			      	if (i * monster_hp [kod_mon] / monster_health [kod_mon] > j - 1 && monster_health [kod_mon] > 0)
				      	messages (">", 0, 32 + COLOR_DARK_RED);
			         else
		   		   	messages (">", 0, 32 + COLOR_GRAY);
			      }

               messages (" AV: ^", monster_dv [kod_mon], 32 + COLOR_GRAY);
            }
         }

			ustaw_kursor ();

	      if (x_wzg >= y_wzg)		// wybieranie celu (tylko dla gracza)
   	   {
      		for (x = 1; x < x_wzg; x ++)
         	{
	         	y = x * y_wzg / x_wzg;

					if (v_shooter >= v_cur)
         	   {
		      	   if (h_shooter >= h_cur)					// I osemka
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
                  }
	         	   else											// II
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
                  }
      	      }
         	   else
	            {
			         if (h_shooter >= h_cur)					// III
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
                  }
         		   else											// IV
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
                  }
   	         }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);

                  if (sqrt (pow (h_cur - h_shooter, 2) + pow (v_cur - v_shooter, 2)) - 0.7 <= weapon_range)
                  	textcolor (COLOR_GREEN);
                  else
                  	textcolor (1);

						addch ('X');
               }
	         }
   	   }
	      else
   	   {
      		for (y = 1; y < y_wzg; y ++)
         	{
	         	x = y * x_wzg / y_wzg;

					if (v_shooter >= v_cur)
	            {
			         if (h_shooter >= h_cur)					// V
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
                  }
         		   else											// VI
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
                  }
   	         }
      	      else
         	   {
			         if (h_shooter >= h_cur)					// VII
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
                  }
      	   	   else											// VIII
                  {
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
                  }
	            }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);

                  if (sqrt (pow (h_cur - h_shooter, 2) + pow (v_cur - v_shooter, 2)) - 0.7 <= weapon_range)
	                 	textcolor (COLOR_GREEN);
                  else
                  	textcolor (1);

						addch ('X');
               }
      	   }
	      }

			klawisz ();

	      if (x_wzg >= y_wzg)
   	   {
      		for (x = 1; x < x_wzg; x ++)
         	{
	         	y = x * y_wzg / x_wzg;

					if (v_shooter >= v_cur)
      	      {
		   	      if (h_shooter >= h_cur)								// I osemka
            	   {
                  	char_code = osemka (h_shooter, v_shooter, -x, -y);
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;

	               }
   	      	   else														// II
      	         {
                  	char_code = osemka (h_shooter, v_shooter, x, -y);
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
	               }
   	         }
      	      else
         	   {
			         if (h_shooter >= h_cur)             // III
   	            {
                  	char_code = osemka (h_shooter, v_shooter, -x, y);
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
	               }
   	      		else										// IV
      	         {
                  	char_code = osemka (h_shooter, v_shooter, x, y);
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
	               }
   	         }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						addch (char_code);
               }
      	   }
	      }
	      else
   	   {
      		for (y = 1; y < y_wzg; y ++)
         	{
         		x = y * x_wzg / y_wzg;

					if (v_shooter >= v_cur)
   	         {
			         if (h_shooter >= h_cur)							// V
         	      {
                  	char_code = osemka (h_shooter, v_shooter, -x, -y);
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
               	}
	         	   else											// VI
   	            {
                  	char_code = osemka (h_shooter, v_shooter, x, -y);
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter - y;
	               }
   	         }
      	      else
         	   {
		      	   if (h_shooter >= h_cur)						// VII
	               {
                  	char_code = osemka (h_shooter, v_shooter, -x, y);
                  	x_temp = h_pos_pl - h_cur + h_shooter - x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
   	            }
      	   	   else                         				// VIII
         	      {
                  	char_code = osemka (h_shooter, v_shooter, x, y);
                  	x_temp = h_pos_pl - h_cur + h_shooter + x;
                     y_temp = v_pos_pl - v_cur + v_shooter + y;
            	   }
	            }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						addch (char_code);
               }
   	      }
	      }

			if (key == 'm' && kod_mon > -2 && view_ability)
	      {
/*				_h_pos = h_pos;
			   _v_pos = v_pos;
				h_pos = h_cur + h_pos_pl - 30;
		   	v_pos = v_cur + v_pos_pl - 10;
				ustaw_gracza ();*/
	      	monster_description (kod_mon);
//				h_pos = _h_pos;
  //		   	v_pos = _v_pos;
      	}
  	      else if (key == 27 || key == 't' && (kod_s = search_shopkeeper (floor_type) >= 0) && monster_pp [kod_s] >= 0 && (attack_type == 1 && unpaid_items [item_body [_SIDEARM_SLOT]] || attack_type == 2 && unpaid_items [item_body [_PRIME_SLOT]]))	// esc lub unpaid item
  	  	   {
     	  		target = 0;
	        	clear_area (1, 23, 79, 24);

         	if (key != 27)
	           	msg ("<Pay for this gun first!_");
  	  	   }
  	      else if (key == 't' && kod_mon >= 0 && monster_aim [kod_mon] != -1)
  	  	   {
           	msg ("<Do you want to attack ");
		      enter_monster (monster_code [kod_mon], COLOR_GRAY, -1000, 0);
            msg (" ? (y/n)");
				target = 0;

				if (answer ())
            {
  		   		shoot = 1;
	            msg_reset ();
 	   	      clear_area (1, 23, 79, 24);
               reputation_change (kod_mon);
            }
  	  	   }

         refresh_view_monsters ();

			if ((key == '4' || key == 4) && h_cur > 0)
				h_cur --;
			else if ((key == '6' || key == 5) && h_cur < x_planszy - 1)
				h_cur ++;
			else if ((key == '8' || key == 3 || key == 83) && v_cur > 0)
				v_cur --;
			else if ((key == '2' || key == 2 || key == 82) && v_cur < y_planszy - 1)
				v_cur ++;
			else if (key == '7' && h_cur > 0 && v_cur > 0)
   		{
				h_cur --;
   	   	v_cur --;
  	     	}
			else if (key == '9' && h_cur < x_planszy - 1 && v_cur > 0)
	   	{
				h_cur ++;
  	      	v_cur --;
	   	}
			else if (key == '3' && v_cur < y_planszy - 1 && h_cur < x_planszy - 1)
  	   	{
  		   	h_cur ++;
				v_cur ++;
      	}
			else if (key == '1' && v_cur < y_planszy - 1 && h_cur > 0)
   		{
  	   		h_cur --;
				v_cur ++;
  	   	}
   	   else if (key == 'n')		// jak 'next' monster
        		target_monster ++;
   	   else if (key == 'x')		// change weapon slot
			{
	      	if (current_weapon == 2 && item_body [_SIDEARM_SLOT] >= 0 && item_specials2 [item_body [_SIDEARM_SLOT]])
            	attack_type = current_weapon = 1;
	      	else if (current_weapon == 1 && item_body [_PRIME_SLOT] >= 0 && item_specials2 [item_body [_PRIME_SLOT]])
            	attack_type = current_weapon = 2;

   	      statystyki (10);
			}
         else if (key == 't' && !(h_cur == h_pos && v_cur == v_pos))	// shoot
	      {
   	      target = 0;
  	   		shoot = 1;
            msg_reset ();
 	         clear_area (1, 23, 79, 24);
    	  		break;
        	}
         else if (target == 0)
         	break;

         move_area ();
         textcolor (COLOR_GRAY);
      }
   }

	if (shooter == -1)
   {
	   msg_reset ();
  		ustaw_gracza ();
	   rysuj_view_range ();
  		verify_visible_monsters ();
		gotoxy (h_pos_pl + LB, v_pos_pl + UB);
   }

   if (shoot || shooter >= 0)		// strzelanie - gracz lub przeciwnik
	{
   	h_aim = h_cur;
		v_aim = v_cur;

      if (shooter == -1)
      {
	   	h_cur = h_pos;
   	   v_cur = v_pos;
      }
      else
      {
	   	h_cur = h_pos_mon [shooter];
   	   v_cur = v_pos_mon [shooter];
      }

   	x_wzg = sqrt (pow (h_aim - h_shooter, 2)) + 1;
      y_wzg = sqrt (pow (v_aim - v_shooter, 2)) + 1;

     	if (attack_type == 1 || attack_type == 2 || spell_type >= 200 && spell_type < 300)	// rzut / strzal przedmiotem lub czar nie odbijajacy sie od scian i nie ball
      {
	      if (x_wzg >= y_wzg)
	      {
  		   	for (x = 1; x < x_wzg; x ++)
     		   {
	            if (!throw_status)
                 	break;

        			y = x * y_wzg / x_wzg;

					if (v_shooter >= v_aim)
  		         {
			         if (h_shooter >= h_aim)
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter - y, h_shooter - x_, v_shooter - y_, h_aim, v_aim);
     	   		   else
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter - y, h_shooter + x_, v_shooter - y_, h_aim, v_aim);
         	   }
   	         else
  	   	      {
		   	      if (h_shooter >= h_aim)
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter + y, h_shooter - x_, v_shooter + y_, h_aim, v_aim);
        		   	else
                     throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter + y, h_shooter + x_, v_shooter + y_, h_aim, v_aim);
  		         }

               y_ = y;
               x_ = x;
      	   }
   	   }
  	   	else
   	   {
  	   		for (y = 1; y < y_wzg; y ++)
      	   {
	            if (!throw_status)
                 	break;

  	      		x = y * x_wzg / y_wzg;

					if (v_shooter >= v_aim)
  	   	      {
		   	      if (h_shooter >= h_aim)
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter - y, h_shooter - x_, v_shooter - y_, h_aim, v_aim);
  	      		   else
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter - y, h_shooter + x_, v_shooter - y_, h_aim, v_aim);
  	   	      }
     	   	   else
         	   {
		      	   if (h_shooter >= h_aim)
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter + y, h_shooter - x_, v_shooter + y_, h_aim, v_aim);
      	   	   else
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter + y, h_shooter + x_, v_shooter + y_, h_aim, v_aim);
     	      	}

               y_ = y;
               x_ = x;
	         }
  		   }

         if (attack_type == 2)
         {
         }

			if (shooter == -1)
         {
         	h_cur = temp1;
         	v_cur = temp2;
         }
         else
         {
         	h_cur = h_pos;
         	v_cur = v_pos;
         }

         refresh_view_monsters ();
		   ustaw_gracza ();
  			rysuj_view_range ();
		   verify_visible_monsters ();
         h_cur = _h_cur;
         v_cur = _v_cur;
			gotoxy (h_pos_pl + LB, v_pos_pl + UB);

         if (shooter == -1)
	      {
			   switch (attack_type)
				{
			  		case 1:
			         if (item_status [item_body [_SIDEARM_SLOT]] > item_specials2 [item_body [_SIDEARM_SLOT]])
      			   	item_specials2 [item_body [_SIDEARM_SLOT]] = 0;
                  else
				       	item_specials2 [item_body [_SIDEARM_SLOT]] -= item_status [item_body [_SIDEARM_SLOT]];
   	   		   break;
			      case 2:
			         if (item_status [item_body [_PRIME_SLOT]] > item_specials2 [item_body [_PRIME_SLOT]])
      			   	item_specials2 [item_body [_PRIME_SLOT]] = 0;
                  else
				       	item_specials2 [item_body [_PRIME_SLOT]] -= item_status [item_body [_PRIME_SLOT]];
      			   break;
	  		   }
         }
         else		// strzela potwor
         {
         	switch (attack_type)
            {
            	case 12:		// bolt/ball
		  	         monster_pp [shooter] -= 7;
                  break;
            }
         }
  	   }
      else		 	// czar odbijajacy sie od sciany lub ball-range
      {
      	if (spell_type < 200)		// bolt odbijajacy sie od scian
         {
	      	bolt_range = total_mind / 2 + 100;
   	      x = h_shooter;
            y = v_shooter;

      		if (x_wzg >= y_wzg)
            {
         		equation = 1;

	            if (h_shooter >= h_aim)
      	        	kierunek = -1;
      	      else
            	  	kierunek = 1;
            }
            else
            {
            	equation = -1;

	            if (v_shooter >= v_aim)
      	        	kierunek = -1;
      	      else
            	  	kierunek = 1;
            }

            x_wzg = h_aim - h_shooter;
            y_wzg = v_aim - v_shooter;

	      	while (throw_status)
   	      {
	            if (equation == 1)
   	         {
      	      	if (kierunek == -1)
         	      	x --;
	               else
   	            	x ++;

						if (y_wzg != 1)
        	    			y = x;// - h_shooter) * y_wzg / x_wzg + v_shooter + c;
	            }
   	         else
      	      {
         	   	if (kierunek == -1)
            	   	y --;
	               else
   	            	y ++;

						if (x_wzg != 1)
	      	         x = y * x_wzg / y_wzg + h_shooter + v_shooter * x_wzg / y_wzg + c;
   	         }

	            throw_status = event_throw (shooter, attack_type, spell_type, x, y, x_, y_, h_aim, v_aim);
   	         x_ = x;
      	      y_ = y;

               if (throw_status == 2)		// odbicie od sciany
               {
                 	a *= -1;
               	kierunek *= -1;

						if (x_wzg >= y_wzg)
	                  b = 2 * y - b;
                  else
                  	b = 2 * x - b;
               }
               else if (throw_status == 3)		// odbicie od kantu sciany
               {
               	if (equation == 1)
	               {
	                  equation = -1;
//	                 	c = v_shooter - h_shooter * y_wzg / x_wzg;
                     temp_ = x_wzg;
                     x_wzg = y_wzg;
							y_wzg = temp_;
	               }
               }

	            bolt_range --;

   	         if (!bolt_range)
      	      	throw_status = 0;
	         }
         }
         else if (spell_type < 500)	// ball-range
         {
         }
      }
	}

   h_cur = _h_cur;
   v_cur = _v_cur;

   if (shoot)
	   turn ();

   if (shooter == -1)
	{
//	   action_cost = 128;
      oblicz_stats ();
	}
}

int osemka (int h_shooter, int v_shooter, int x, int y)
{
	int kod_p, char_code;

   if (view_matrix (X_MAX + x, Y_MAX + y) != 0)
   {
	   kod_p = monsters_planszy [h_shooter + x] [v_shooter + y];

		if (kod_p != -15)
         char_code = monster [kod_p];
      else
         char_code = mem_planszy [h_shooter + x] [v_shooter + y];
	}
   else
   {
	   if (mem_planszy [h_shooter + x] [v_shooter + y] != 32)
         char_code = mem_planszy [h_shooter + x] [v_shooter + y];
      else
      {
	      textcolor (1);
         return 32;
      }
   }

	textcolor (char_code / 256);

   return char_code;
}
