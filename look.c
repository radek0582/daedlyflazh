#include "deklaracje.h"

void look ()
{
	int _h_pos_pl = h_pos_pl, _h_pos, _x_pos, _h_cur = h_cur;
	int _v_pos_pl = v_pos_pl, _v_pos, _y_pos, _v_cur = v_cur;
	int kod_item, kod_mem, kod_cov, kod_stan, a, i, j, k, _j, _k, j_, k_, floor_type, view_ability;
	char petla = 1;

   h_cur = h_pos;
   v_cur = v_pos;

	while (petla)
	{
  		monster_id = monsters_planszy [h_cur] [v_cur];
		floor_type = floor_planszy [h_cur] [v_cur];
		item_id = items_planszy [h_cur] [v_cur];
      kod_item = obstacles_planszy [h_cur] [v_cur];
      kod_cov = coverers_planszy [h_cur] [v_cur] [0];
      kod_stan = stan_planszy [h_cur] [v_cur];
      kod_mem = mem_planszy [h_cur] [v_cur];
      clear_area (2, 23, 75, 24);
		gotoxy (2, 23);

		if (mem_planszy [h_cur] [v_cur] == 32)
  	   	messages ("Unknown place.", 0, COLOR_GRAY + 32);
      else
      {
      	if ((view_ability = check_own_visibility (h_cur, v_cur)))
         {
	      	if (monster_id >= 0 && check_own_visibility (h_cur, v_cur) == 2)
   	      {
			      enter_monster (monster_code [monster_id], 32 + COLOR_GRAY, 0, 0);

	            if (abilities [_SCIENCE])
   	         {
         	      i = sqrt (monster_health [monster_id]) + 1;
	         	   messages (" ", 0, 32 + COLOR_GRAY);

				      for (j = 0; j < i ; j ++)
				      {
				      	if (i * monster_hp [monster_id] / monster_health [monster_id] > j - 1 && monster_health [monster_id] > 0)
					      	messages (">", 0, 32 + COLOR_DARK_RED);
			   	      else
		   			   	messages (">", 0, 32 + COLOR_GRAY);
				      }

   	            messages (" AV: ^", monster_dv [monster_id], 32 + COLOR_GRAY);
	            }

         	   messages (" [m]ore. ", 0, 32 + COLOR_GRAY);
              	gotoxy (2, 24);
	         }

   	      if (item_id >= 0)
      	   {
         		enter_item (item_id, 32 + COLOR_GRAY);
            	kropka (32 + COLOR_GRAY);
	         }
				else if (item_id < -1)
      	   	messages ("Several items [v]iew. ", 0, COLOR_GRAY + 32);

/*               gotoxy (70, 16);
               printw ("s_pl %d ", kod_stan);
               gotoxy (70, 17);
               printw ("o_pl %d ", kod_item);
               gotoxy (70, 18);
               printw ("floor %d  ", floor_type);
               gotoxy (70, 19);
               printw ("mem   %d  ", kod_mem);*/

	         if (kod_item >= 0)
   	      {
	            if (item_group [kod_item] == 51)		// traps + czy zidentyfikowana
	            {
   	         }
               else
	   	      	enter_item (kod_item, COLOR_GRAY + 32);

	   	      kropka (COLOR_GRAY + 32);
	         }

	      	enter_floor (floor_type, 32 + COLOR_GRAY, 0);
   	      kropka (COLOR_GRAY + 32);
         }
         else
        	   messages ("Out of sight. ", 0, 32 + COLOR_GRAY);
      }

		_setcursortype (_NORMALCURSOR);
      ustaw_kursor ();
		gotoxy (h_pos_pl + LB, v_pos_pl + UB);
		klawisz ();
		_setcursortype (_NOCURSOR);

		if (key == 'm' && view_ability && monster_id > -2)
      	monster_description (monster_id);
		else if (key == 'v' && view_ability && item_id < -1)
      {
//         action_pickup (22, h_cur, v_cur);			// show items on place
//         clrscr ();
			inventory_selector (22, h_cur, v_cur);
			_h_pos = h_pos;
		   _v_pos = v_pos;
			h_pos = h_cur + h_pos_pl - 30;
		   v_pos = v_cur + v_pos_pl - 10;
			ustaw_gracza ();

			for (i = v_pos - v_pos_pl; i < Y_WINDOW + v_pos - v_pos_pl; i ++)
				for (j = h_pos - h_pos_pl; j < X_WINDOW + h_pos - h_pos_pl; j ++)
					enter_char (mem_planszy [j] [i], j, i);

		   msg_reset ();
         statystyki (0);
			h_pos = _h_pos;
		   v_pos = _v_pos;
      }
		else if (key == 27)
			petla = 0;

      refresh_view_monsters ();

		if ((key == '4' || key == 4) && h_cur >= 1)
			h_cur --;
		else if ((key == '6' || key == 5) && h_cur < x_planszy - 1)
			h_cur ++;
		else if ((key == '8' || key == 3 || key == 83) && v_cur >= 1)
			v_cur --;
		else if ((key == '2' || key == 2 || key == 82) && v_cur < y_planszy - 1)
			v_cur ++;
		else if (key == '7' && h_cur >= 1 && v_cur >= 1)
      {
			h_cur --;
         v_cur --;
      }
		else if (key == '9' && h_cur < x_planszy - 1 && v_cur >= 1)
      {
			h_cur ++;
         v_cur --;
      }
		else if (key == '3' && v_cur < y_planszy - 1 && h_cur < x_planszy - 1)
      {
      	h_cur ++;
			v_cur ++;
      }
		else if (key == '1' && v_cur < y_planszy - 1 && h_cur >= 1)
      {
      	h_cur --;
			v_cur ++;
      }
		else if (petla == 0)
      	break;

      move_area ();
	}

	clear_area (2, 23, 75, 24);
   ustaw_gracza ();
   rysuj_view_range ();
   verify_visible_monsters ();
   h_cur = _h_cur;
   v_cur = _v_cur;
	gotoxy (h_pos_pl + LB, v_pos_pl + UB);
}

void move_area ()
{
	int _h_pos_pl = h_pos_pl, _h_pos, _x_pos;
	int _v_pos_pl = v_pos_pl, _v_pos, _y_pos;
	int kod_item, kod_cov, kod_stan, a, i, j, k, _j, _k, j_, k_, floor_type;
	char petla = 1;

	ustaw_kursor ();
	_j = - view_range;
  	j_ = view_range;
   _k = - view_range;
  	k_ = view_range;

  	if (h_pos_pl > view_range)
  	  	_k = - h_pos_pl;

  	if (X_WINDOW - h_pos_pl > view_range)
  	  	k_ = X_WINDOW - h_pos_pl;

   if (v_pos_pl > view_range)
  	  	_j = - v_pos_pl;

  	if (Y_WINDOW - v_pos_pl > view_range)
  	  	j_ = Y_WINDOW - v_pos_pl;

	for (j = _j; j <= j_; j ++)
	{
		for (k = _k; k <= k_; k ++)
      {
			if (v_cur + j >= 0 && v_cur + j < y_planszy && h_cur + k >= 0 && h_cur + k < x_planszy)
			{
				if (h_pos_pl + k >= 0 && v_pos_pl + j >= 0 && v_pos_pl + j < Y_WINDOW && h_pos_pl + k < X_WINDOW && display_area [h_pos_pl + k] [v_pos_pl + j] != mem_planszy [h_cur + k] [v_cur + j])
            {
					display_area [h_pos_pl + k] [v_pos_pl + j] = mem_planszy [h_cur + k] [v_cur + j];
					gotoxy (k + h_pos_pl + LB, j + v_pos_pl + UB);
					textcolor (mem_planszy [h_cur + k] [v_cur +j] / 256);
				   addch (mem_planszy [h_cur + k] [v_cur +j]);
            }
			}
		}
	}

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

   if (check_own_visibility (h_pos, v_pos))
	   put_char (player, _h_pos, _v_pos);

	h_pos = _h_pos;
   v_pos = _v_pos;
}

void refresh_view_monsters ()
{
	int _h_pos;
   int _v_pos;

   ustaw_kursor ();
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
}
