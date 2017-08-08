#include "deklaracje.h"

void targeting (int shooter, char attack_type, int spell_type)		// shooter: -1 - gracz, 0... - enemy; attack_type: 1 - throw/shoot, 2 - spell, 3 - wand; spell_type: 1 - lightning ball, 12 - ice bolt...
{
	int temp_, a = 1, b = 0, c = 0, i, j, k, _j, _k, j_, k_, x, y, x_ = 0, y_ = 0, x_wzg, y_wzg, h_shooter, v_shooter, kod_p, bolt_range, x_temp, y_temp;
   int x_pos_, y_pos_, x_pos, y_pos, equation, target_monster = 0;
	int _h_pos_pl = h_pos_pl, _h_pos, _x_pos, h_aim, v_aim;
	int _v_pos_pl = v_pos_pl, _v_pos, _y_pos;
  	int kod_item, kod_cov, kod_stan, floor_type;
   int char_code;
   char kierunek, throw_status = 1, target = 0;
   char shoot = 0;

   key = 0;

	if (shooter == -1)			// shooter = player
   {
   	action_cost = 90;
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

      if (monster_aim [shooter] == -1)
      {
      	h_cur = h_aim = h_pos;
         v_cur = v_aim = v_pos;
      }
      else
      {
	      h_cur = h_aim = h_pos_mon [monster_aim [shooter]];
   	   v_cur = v_aim = v_pos_mon [monster_aim [shooter]];
      }

   	x_wzg = sqrt (pow (h_aim - h_shooter, 2)) + 1;
      y_wzg = sqrt (pow (v_aim - v_shooter, 2)) + 1;
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

   while (target)
   {
   	x_wzg = sqrt (pow (h_cur - h_shooter, 2)) + 1;
		y_wzg = sqrt (pow (v_cur - v_shooter, 2)) + 1;
	   x_pos_ = h_cur;
      y_pos_ = v_cur;
      textcolor (7);

		if (shooter == -1)		// player
      {
	      clear_window (10, 24, 60, 24);
         gotoxy (2, 23);

         if (attack_type == 1)
         {
         	if (item_body [_MWEAPON] != -1)
            {
		         messages ("MW: ", 0, 39);
      	      enter_item (item_body [_MWEAPON], item_icon [item_body [_MWEAPON]] / 256 + 32);
               messages (" ", 0, 39);
            }
            messages ("MA: ", 0, 39);
            enter_item (item_body [_MWAMMO], item_icon [item_body [_MWAMMO]] / 256 + 32);
         }

     		monster_id = monsters_planszy [h_cur] [v_cur];
			gotoxy (2, 24);
         messages ("Target: ", 0, 39);

			if (!mem_planszy [h_cur] [v_cur])
   	   	messages ("Unknown", 0, 39);

	      if (monster_id >= 0 && check_own_visibility (h_cur, v_cur) == 2)
		      enter_monster (monster_code [monster_id], monster [monster_id] / 256 + 32, 0, 0);

//			_setcursortype (_NORMALCURSOR);
			ustaw_kursor ();

	      if (x_wzg > y_wzg)		// wybieranie celu (tylko dla gracza)
   	   {
      		for (x = 1; x < x_wzg; x ++)
         	{
	         	y = x * y_wzg / x_wzg;

					if (v_shooter >= v_cur)
         	   {
		      	   if (h_shooter >= h_cur)
                  {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl + y;
                  }
	         	   else
                  {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl + y;
                     debug (x_temp, y_temp, 1, x);
//                     debug (x, y, 1, x + 10);
                  }
      	      }
         	   else
	            {
			         if (h_shooter >= h_cur)
                  {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl - y;
                  }
         		   else
                  {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl - y;
                  }
   	         }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
                     debug (x_temp, y_temp, 1, 10 + x);
	               gotoxy (x_temp, y_temp);
						putch ('X');
               }
	         }
   	   }
	      else if (x_wzg < y_wzg)
   	   {
      		for (y = 1; y < y_wzg; y ++)
         	{
	         	x = y * x_wzg / y_wzg;

					if (v_shooter >= v_cur)
	            {
			         if (h_shooter >= h_cur)
                  {
                  	x_temp = h_pos_pl + x;
                     y_temp = v_pos_pl + y - 1;
                  }
         		   else
                  {
                  	x_temp = h_pos_pl - x;
                     y_temp = v_pos_pl + y - 1;
                  }
   	         }
      	      else
         	   {
			         if (h_shooter >= h_cur)
                  {
                  	x_temp = h_pos_pl + x;
                     y_temp = v_pos_pl - y + 1;
                  }
      	   	   else
                  {
                  	x_temp = h_pos_pl - x;
                     y_temp = v_pos_pl - y + 1;
                  }
	            }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						putch ('X');
               }
      	   }
	      }
         else
         {
      		for (y = 1; y < y_wzg; y ++)
         	{
	         	x = y;

					if (v_shooter >= v_cur)
	            {
			         if (h_shooter >= h_cur)
                  {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl + y - 1;
                  }
         		   else
                  {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl + y - 1;
                  }
   	         }
      	      else
         	   {
			         if (h_shooter >= h_cur)
                  {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl - y + 1;
                  }
      	   	   else
                  {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl - y + 1;
                  }
	            }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						putch ('X');
               }
      	   }
         }

/*			while (1)
				if (kbhit ())
				{
					key = getch ();
					break;
				}*/
			klawisz ();

//			_setcursortype (_NOCURSOR);

	      if (x_wzg > y_wzg)
   	   {
      		for (x = 1; x < x_wzg; x ++)
         	{
	         	y = x * y_wzg / x_wzg;

					if (v_shooter >= v_cur)
      	      {
		   	      if (h_shooter >= h_cur)
            	   {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl + y;

	                  if (view_matrix (X_MAX - x_wzg + x - 1, Y_MAX - y_wzg + y) != 0)
   	               {
	                     kod_p = monsters_planszy [h_cur + x - 1] [v_cur + y];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
					            textcolor (plansza [h_cur + x - 1] [v_cur + y] / 256);
					            char_code = plansza [h_cur + x - 1] [v_cur + y];
                     	}
            	      }
	                  else
   	               {
	   	               if (mem_planszy [h_cur + x - 1] [v_cur + y])
   	   	            {
					            textcolor (mem_planszy [h_cur + x - 1] [v_cur + y] / 256);
				   	         char_code = mem_planszy [h_cur + x - 1] [v_cur + y];
        	   	   	   }
		                  else
   		               {
					            textcolor (0);
					            char_code = 32;
            		      }
               	   }
	               }
   	      	   else
      	         {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl + y;

            	      if (view_matrix (X_MAX + x_wzg - x + 1, Y_MAX - y_wzg + y) != 0)
               	   {
                     	kod_p = monsters_planszy [h_cur - x + 1] [v_cur + y];

	                    	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				         	   textcolor (plansza [h_cur - x + 1] [v_cur + y] / 256);
				            	char_code = plansza [h_cur - x + 1] [v_cur + y];
                        }
	      	         }
   	               else
      	            {
	      	            if (mem_planszy [h_cur - x + 1] [v_cur + y])
   	      	         {
				   	         textcolor (mem_planszy [h_cur - x + 1] [v_cur + y] / 256);
				      	      char_code = mem_planszy [h_cur - x + 1] [v_cur + y];
      	   	      	}
	               	   else
		                  {
   		               	textcolor (0);
      		               char_code = 32;
         		         }
               	   }
	               }
   	         }
      	      else
         	   {
			         if (h_shooter >= h_cur)
   	            {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl - y;

            	      if (view_matrix (X_MAX - x_wzg + x - 1, Y_MAX + y_wzg - y) != 0)
               	   {
                     	kod_p = monsters_planszy [h_cur + x - 1] [v_cur - y];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				         	   textcolor (plansza [h_cur + x - 1] [v_cur - y] / 256);
					            char_code = plansza [h_cur + x - 1] [v_cur - y];
                        }
   	      	      }
      	            else
         	         {
	         	         if (mem_planszy [h_cur + x - 1] [v_cur - y])
   	         	      {
				      	      textcolor (mem_planszy [h_cur + x - 1] [v_cur - y] / 256);
				         	   char_code = mem_planszy [h_cur + x - 1] [v_cur - y];
	         		      }
   	            	   else
      	            	{
	      	            	textcolor (0);
   	      	            char_code = 32;
      	      	      }
                  	}
	               }
   	      		else
      	         {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl - y;

            	      if (view_matrix (X_MAX + x_wzg - x + 1, Y_MAX + y_wzg - y) != 0)
               	   {
                     	kod_p = monsters_planszy [h_cur - x + 1] [v_cur - y];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				         	   textcolor (plansza [h_cur - x + 1] [v_cur - y] / 256);
				            	char_code = plansza [h_cur - x + 1] [v_cur - y];
                        }
	      	         }
   	               else
      	            {
	      	            if (mem_planszy [h_cur - x + 1] [v_cur - y])
   	      	         {
				   	         textcolor (mem_planszy [h_cur - x + 1] [v_cur - y] / 256);
				      	      char_code = mem_planszy [h_cur - x + 1] [v_cur - y];
      	   	      	}
		                  else
   		               {
      		            	textcolor (0);
         		            char_code = 32;
            		      }
               	   }
	               }
   	         }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						putch (char_code);
               }
      	   }
	      }
	      else if (x_wzg < y_wzg)
   	   {
      		for (y = 1; y < y_wzg; y ++)
         	{
         		x = y * x_wzg / y_wzg;

					if (v_shooter >= v_cur)
   	         {
			         if (h_shooter >= h_cur)
         	      {
                  	x_temp = h_pos_pl + x;
                     y_temp = v_pos_pl + y - 1;

	                  if (view_matrix (X_MAX - x_wzg + x, Y_MAX - y_wzg + y - 1) != 0)
   	               {
                     	kod_p = monsters_planszy [h_cur + x] [v_cur + y - 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
					            textcolor (plansza [h_cur + x] [v_cur + y - 1] / 256);
					            char_code = plansza [h_cur + x] [v_cur + y - 1];
                        }
      	   	      }
               	   else
	                  {
		                  if (mem_planszy [h_cur + x] [v_cur + y - 1])
   		               {
					            textcolor (mem_planszy [h_cur + x] [v_cur + y - 1] / 256);
					            char_code = mem_planszy [h_cur + x] [v_cur + y - 1];
      	   		      }
	               	   else
	   	               {
   	   	            	textcolor (0);
      	   	            char_code = 32;
								}
            	      }
               	}
	         	   else
   	            {
                  	x_temp = h_pos_pl - x;
                     y_temp = v_pos_pl + y - 1;

            	      if (view_matrix (X_MAX + x_wzg - x, Y_MAX - y_wzg + y - 1) != 0)
               	   {
                     	kod_p = monsters_planszy [h_cur - x] [v_cur + y - 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				         	   textcolor (plansza [h_cur - x] [v_cur + y - 1] / 256);
				            	char_code = plansza [h_cur - x] [v_cur + y - 1];
                        }
	                  }
   	               else
      	            {
	      	            if (mem_planszy [h_cur - x] [v_cur + y - 1])
   	      	         {
				   	         textcolor (mem_planszy [h_cur - x] [v_cur + y - 1] / 256);
				      	      char_code = mem_planszy [h_cur - x] [v_cur + y - 1];
            	      	}
		                  else
   		               {
      		            	textcolor (0);
         		            char_code = 32;
            		      }
               	   }
	               }
   	         }
      	      else
         	   {
		      	   if (h_shooter >= h_cur)
	               {
                  	x_temp = h_pos_pl + x;
                     y_temp = v_pos_pl - y + 1;

         	         if (view_matrix (X_MAX - x_wzg + x, Y_MAX + y_wzg - y + 1) != 0)
            	      {
                     	kod_p = monsters_planszy [h_cur + x] [v_cur - y + 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				      	      textcolor (plansza [h_cur + x] [v_cur - y + 1] / 256);
					            char_code = plansza [h_cur + x] [v_cur - y + 1];
                        }
   	               }
      	            else
         	         {
	         	         if (mem_planszy [h_cur + x] [v_cur - y + 1])
   	         	      {
				      	      textcolor (mem_planszy [h_cur + x] [v_cur - y + 1] / 256);
					            char_code = mem_planszy [h_cur + x] [v_cur - y + 1];
   	         	      }
      	         	   else
	      	            {
   	      	         	textcolor (0);
      	      	         char_code = 32;
         	      	   }
	                  }
   	            }
      	   	   else
         	      {
                  	x_temp = h_pos_pl - x;
                     y_temp = v_pos_pl - y + 1;

	                  if (view_matrix (X_MAX + x_wzg - x, Y_MAX + y_wzg - y + 1) != 0)
   	               {
                     	kod_p = monsters_planszy [h_cur - x] [v_cur - y + 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
					            textcolor (plansza [h_cur - x] [v_cur - y + 1] / 256);
					            char_code = plansza [h_cur - x] [v_cur - y + 1];
                        }
            	      }
               	   else
                  	{
		                  if (mem_planszy [h_cur - x] [v_cur - y + 1])
   		               {
					            textcolor (mem_planszy [h_cur - x] [v_cur - y + 1] / 256);
					            char_code = mem_planszy [h_cur - x] [v_cur - y + 1];
	         	         }
   	         	      else
      	         	   {
	         	         	textcolor (0);
   	         	         char_code = 32;
      	         	   }
         	         }
            	   }
	            }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						putch (char_code);
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
			         if (h_shooter >= h_cur)
         	      {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl + y - 1;

	                  if (view_matrix (X_MAX - x_wzg + x - 1, Y_MAX - y_wzg + y - 1) != 0)
   	               {
                     	kod_p = monsters_planszy [h_cur + x - 1] [v_cur + y - 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
					            textcolor (plansza [h_cur + x - 1] [v_cur + y - 1] / 256);
					            char_code = plansza [h_cur + x - 1] [v_cur + y - 1];
                        }
      	   	      }
               	   else
	                  {
		                  if (mem_planszy [h_cur + x - 1] [v_cur + y - 1])
   		               {
					            textcolor (mem_planszy [h_cur + x - 1] [v_cur + y - 1] / 256);
					            char_code = mem_planszy [h_cur + x - 1] [v_cur + y - 1];
      	   		      }
	               	   else
	   	               {
   	   	            	textcolor (0);
      	   	            char_code = 32;
								}
            	      }
               	}
	         	   else
   	            {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl + y - 1;

            	      if (view_matrix (X_MAX + x_wzg - x + 1, Y_MAX - y_wzg + y - 1) != 0)
               	   {
                     	kod_p = monsters_planszy [h_cur - x + 1] [v_cur + y - 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				         	   textcolor (plansza [h_cur - x + 1] [v_cur + y - 1] / 256);
				            	char_code = plansza [h_cur - x + 1] [v_cur + y - 1];
                        }
	                  }
   	               else
      	            {
	      	            if (mem_planszy [h_cur - x + 1] [v_cur + y - 1])
   	      	         {
				   	         textcolor (mem_planszy [h_cur - x + 1] [v_cur + y - 1] / 256);
				      	      char_code = mem_planszy [h_cur - x + 1] [v_cur + y - 1];
            	      	}
		                  else
   		               {
      		            	textcolor (0);
         		            char_code = 32;
            		      }
               	   }
	               }
   	         }
      	      else
         	   {
		      	   if (h_shooter >= h_cur)
	               {
                  	x_temp = h_pos_pl + x - 1;
                     y_temp = v_pos_pl - y + 1;

         	         if (view_matrix (X_MAX - x_wzg + x - 1, Y_MAX + y_wzg - y + 1) != 0)
            	      {
                     	kod_p = monsters_planszy [h_cur + x - 1] [v_cur - y + 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
				      	      textcolor (plansza [h_cur + x - 1] [v_cur - y + 1] / 256);
					            char_code = plansza [h_cur + x - 1] [v_cur - y + 1];
                        }
   	               }
      	            else
         	         {
	         	         if (mem_planszy [h_cur + x - 1] [v_cur - y + 1])
   	         	      {
				      	      textcolor (mem_planszy [h_cur + x - 1] [v_cur - y + 1] / 256);
					            char_code = mem_planszy [h_cur + x - 1] [v_cur - y + 1];
   	         	      }
      	         	   else
	      	            {
   	      	         	textcolor (0);
      	      	         char_code = 32;
         	      	   }
	                  }
   	            }
      	   	   else
         	      {
                  	x_temp = h_pos_pl - x + 1;
                     y_temp = v_pos_pl - y + 1;

	                  if (view_matrix (X_MAX + x_wzg - x + 1, Y_MAX + y_wzg - y + 1) != 0)
   	               {
                     	kod_p = monsters_planszy [h_cur - x + 1] [v_cur - y + 1];

                     	if (kod_p != -15)
                        {
					            textcolor (monster [kod_p] / 256);
					            char_code = monster [kod_p];
                        }
                        else
                        {
					            textcolor (plansza [h_cur - x + 1] [v_cur - y + 1] / 256);
					            char_code = plansza [h_cur - x + 1] [v_cur - y + 1];
                        }
            	      }
               	   else
                  	{
		                  if (mem_planszy [h_cur - x + 1] [v_cur - y + 1])
   		               {
					            textcolor (mem_planszy [h_cur - x + 1] [v_cur - y + 1] / 256);
					            char_code = mem_planszy [h_cur - x + 1] [v_cur - y + 1];
	         	         }
   	         	      else
      	         	   {
	         	         	textcolor (0);
   	         	         char_code = 32;
      	         	   }
         	         }
            	   }
	            }
               x_temp += LB;
               y_temp += UB;

					if (x_temp > 1 && x_temp <= X_WINDOW + 1 && y_temp > 1 && y_temp <= Y_WINDOW + 1)
               {
	               gotoxy (x_temp, y_temp);
						putch (char_code);
               }
   	      }
	      }

			if (key == 'm' && monster_id > -2)
	      {
				h_pos_pl = _h_pos_pl;
			   v_pos_pl = _v_pos_pl;
		   	ustaw_gracza ();
	      	monster_description (monster_id);
            target = 0;
      	}
  	      else if (key == 27)	// esc
  	  	   {
     	  		target = 0;
//        	   msg_reset ();
	        	clear_window (1, 23, 79, 24);
//  	         break;
  	  	   }

		   check_visible_monsters ();
			_h_pos = h_pos;
	      _v_pos = v_pos;
			h_pos = h_cur + h_pos_pl - 30;
	      v_pos = v_cur + v_pos_pl - 10;
   	   ustaw_gracza ();
	   	move_visible_monsters ();

			if (check_own_visibility (h_pos, v_pos))
			   put_char (mem_planszy [_h_pos] [_v_pos], _h_pos, _v_pos);

			h_pos = _h_pos;
			v_pos = _v_pos;

			if (key == '4' && h_cur > 0)
				h_cur --;
			else if (key == '6' && h_cur < x_planszy - 1)
				h_cur ++;
			else if (key == '8' && v_cur > 0)
				v_cur --;
			else if (key == '2' && v_cur < y_planszy - 1)
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
         else if (key == 't')	// shoot
	      {
   	      target = 0;
  	   		shoot = 1;
            msg_reset ();
 	         clear_window (1, 23, 79, 24);
    	  		break;
        	}
         else if (target == 0)
         	break;

         move_area ();
         textcolor (7);
      }
   }

   msg_reset ();
  	ustaw_gracza ();
   rysuj_view_range ();
  	verify_visible_monsters ();
	gotoxy (h_pos_pl + LB, v_pos_pl + UB);

   if (shoot || shooter >= 0)		// strzelanie - gracz lub przeciwnik
	{
   	h_aim = h_cur;
		v_aim = v_cur;
   	h_cur = h_pos;
      v_cur = v_pos;
   	x_wzg = sqrt (pow (h_aim - h_shooter, 2)) + 1;
      y_wzg = sqrt (pow (v_aim - v_shooter, 2)) + 1;

     	if (attack_type == 1 || spell_type >= 200 && spell_type < 300)	// rzut / strzal przedmiotem lub czar nie odbijajacy sie od scian i nie ball
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
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter - y, h_shooter - x_, v_shooter - y_);
     	   		   else
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter - y, h_shooter + x_, v_shooter - y_);
         	   }
   	         else
  	   	      {
		   	      if (h_shooter >= h_aim)
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter + y, h_shooter - x_, v_shooter + y_);
        		   	else
                     throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter + y, h_shooter + x_, v_shooter + y_);
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
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter - y, h_shooter - x_, v_shooter - y_);
  	      		   else
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter - y, h_shooter + x_, v_shooter - y_);
  	   	      }
     	   	   else
         	   {
		      	   if (h_shooter >= h_aim)
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter - x, v_shooter + y, h_shooter - x_, v_shooter + y_);
      	   	   else
	                  throw_status = event_throw (shooter, attack_type, spell_type, h_shooter + x, v_shooter + y, h_shooter + x_, v_shooter + y_);
     	      	}

               y_ = y;
               x_ = x;
	         }
  		   }

		   ustaw_kursor ();
//			gotoxy (h_pos_pl + LB, v_pos_pl + UB);
		   check_visible_monsters ();
			_h_pos = h_pos;
      	_v_pos = v_pos;
			h_pos = h_cur + h_pos_pl - 30;
   	   v_pos = v_cur + v_pos_pl - 10;
  	   	ustaw_gracza ();
	   	move_visible_monsters ();

			if (check_own_visibility (h_pos, v_pos))
			   put_char (mem_planszy [_h_pos] [_v_pos], _h_pos, _v_pos);

	   	h_pos = _h_pos;
   	   v_pos = _v_pos;

	     	msg_reset ();
		   ustaw_gracza ();
  			rysuj_view_range ();
		   verify_visible_monsters ();
			gotoxy (h_pos_pl + LB, v_pos_pl + UB);

         if (shooter == -1)
	      {
		      switch (attack_type)
  			   {
	      		case 1:		// strzal / rzut
               	ujmij_item (item_body [_MWAMMO], 1);
  		            break;
     		      case 2:		// czar
      	         break;
	         }
            turn ();
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

	            throw_status = event_throw (shooter, attack_type, spell_type, x, y, x_, y_);
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

/*   	check_visible_monsters ();
		_h_pos = h_pos;
   	_v_pos = v_pos;
		h_pos = h_cur + h_pos_pl - 30;
   	v_pos = v_cur + v_pos_pl - 10;
	   ustaw_gracza ();
		move_visible_monsters ();

		if (check_own_visibility (h_pos, v_pos))
		   put_char (mem_planszy [_h_pos] [_v_pos], _h_pos, _v_pos);

		h_pos = _h_pos;
		v_pos = _v_pos;*/

	}

   if (shooter == -1)
	{
	   action_cost = 128;
      oblicz_stats ();
	}
}
