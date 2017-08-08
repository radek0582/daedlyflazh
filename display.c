#include "deklaracje.h"

void display_monsters ()
{
   int i, y;

	clear ();

   for (i = 0; i < x_planszy; i ++)
   	for (y = 0; y < y_planszy; y ++)
      	if (monsters_planszy [i] [y] >= 0)
				put_char (monster [monsters_planszy [i] [y]], h_pos_mon [monsters_planszy [i] [y]], v_pos_mon [monsters_planszy [i] [y]]);

   while (1)
   {
   	klawisz ();

      if (key == 27)
      	break;
   }

   rysuj_ekran ();
}

void rysuj_view_range ()
{
	int j, k, _j, _k, j_, k_;

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

	make_view_matrix ();

	if (drugs [0])		// drugged
   {
		for (j = _j; j <= j_; j ++)
		{
			for (k = _k; k <= k_; k ++)
         {
				if (v_pos + j >= 0 && v_pos + j < y_planszy && h_pos + k >= 0 && h_pos + k < x_planszy)
				{
  	         	if (view_matrix (X_MAX + k, Y_MAX + j))
	               mem_planszy [h_pos + k] [v_pos +j] = put_char (plansza [h_pos + k] [v_pos + j], h_pos + k, v_pos + j);

					if (h_pos_pl + k >= 0 && h_pos_pl + k < X_WINDOW && v_pos_pl + j >= 0 && v_pos_pl + j < Y_WINDOW && display_area [h_pos_pl + k] [v_pos_pl + j] != mem_planszy [h_pos + k] [v_pos + j])
               {
               	display_area [h_pos_pl + k] [v_pos_pl + j] = mem_planszy [h_pos + k] [v_pos + j];
	               enter_char (mem_planszy [h_pos + k] [v_pos + j], h_pos + k, v_pos + j);
               }
				}
			}
		}
   }
   else
   {
		for (j = _j; j <= j_; j ++)
		{
			for (k = _k; k <= k_; k ++)
         {
				if (v_pos + j >= 0 && v_pos + j < y_planszy && h_pos + k >= 0 && h_pos + k < x_planszy)
				{
  	         	if (view_matrix (X_MAX + k, Y_MAX + j))
               	mem_planszy [h_pos + k] [v_pos +j] = plansza [h_pos + k] [v_pos +j];

					if (h_pos_pl + k >= 0 && h_pos_pl + k < X_WINDOW && v_pos_pl + j >= 0 && v_pos_pl + j < Y_WINDOW && display_area [h_pos_pl + k] [v_pos_pl + j] != mem_planszy [h_pos + k] [v_pos + j])
               {
						display_area [h_pos_pl + k] [v_pos_pl + j] = mem_planszy [h_pos + k] [v_pos + j];
                  enter_char (mem_planszy [h_pos + k] [v_pos + j], h_pos + k, v_pos + j);
               }
				}
			}
		}
   }
}

void make_view_matrix ()
{
	int a, y, x, l, k;
   int i, j;

	for (i = 0; i < Y_MATRIX; i ++)
		for (j = 0; j < X_MATRIX; j ++)
			view_matrix_table [j] [i] = 0;

	view_matrix_table [X_MAX] [Y_MAX] = 1;		// player

	for (a = RESOLUTION; a >= -RESOLUTION; a --)		// I - IV osemka
	{
		x = 0;

		while (x <= view_range)
		{
      	x ++;
			y = a * x / RESOLUTION;
			view_matrix_table [X_MAX - x] [Y_MAX - y] = 1;

			if (x > h_pos || y > v_pos || plansza [h_pos - x] [v_pos - y] > 8192)
				break;
		}

		x = 0;

		while (x <= view_range)
		{
      	x ++;
			y = a * x / RESOLUTION;
			view_matrix_table [X_MAX + x] [Y_MAX - y] = 1;

			if (x + h_pos >= x_planszy || y > v_pos || plansza [h_pos + x] [v_pos - y] > 8192)
				break;
		}
	}

	for (a = RESOLUTION; a >= -RESOLUTION; a --)		// V - VIII osemka
	{
		y = 0;

		while (y <= view_range)
		{
      	y ++;
			x = a * y / RESOLUTION;
			view_matrix_table [X_MAX - x] [Y_MAX - y] = 1;

			if (x > h_pos || y > v_pos || plansza [h_pos - x] [v_pos - y] > 8192)
				break;
		}

		y = 0;

		while (y <= view_range)
		{
      	y ++;
			x = a * y / RESOLUTION;
			view_matrix_table [X_MAX - x] [Y_MAX + y] = 1;

			if (x > h_pos || y + v_pos >= y_planszy || plansza [h_pos - x] [v_pos + y] > 8192)
				break;
		}
	}

	for (l = - view_range - 1; l <= view_range + 1; l ++)
		for (k = - view_range - 1; k <= view_range + 1; k ++)
			if (view_range <= sqrt (pow (l, 2) + pow (k, 2)) - 0.7)
				view_matrix_table [X_MAX + k] [Y_MAX + l] = 0;
}

char view_matrix (int x_value, int y_value)
{
	if (x_value < 0 || y_value < 0 || x_value > X_MATRIX || y_value >= Y_MATRIX)
   	return 0;
   else if (view_matrix_table [x_value] [y_value])
   	return 1;

	return 0;
}

void rysuj_plansze ()
{
	int q, r;

   for (q = 0; q < X_WINDOW; q ++)
     	for (r = 0; r < Y_WINDOW; r ++)
        	display_area [q] [r] = 0;

   for (q = 0; q < X_WINDOW; q ++)
     	for (r = 0; r < Y_WINDOW; r ++)
      	if (mem_planszy [q] [r] != 32)
	        	enter_char (mem_planszy [q] [r], q, r);

	oblicz_stats ();
   msg_reset ();
   rysuj_view_range ();
	put_monsters ();
}

void statystyki (char stat)
{
   char state = 0, j, state_level;
   int kod_p;

   wybierz_item = 0;

	if (!stat)
   {
		textcolor (COLOR_GRAY);
		gotoxy (63, 2); printw ("%s", player_name);
	   gotoxy (63, 10);

	   switch (cl_id)
   	{
	   	case _WORLD:
      		messages ("Wasteland", 0, 56);
   	      break;
	      case _New_York_City:
      		messages ("New York City", 0, 56);
   	      break;
	      case _Downtown:
      		messages ("NY City Downtown", 0, 56);
   	      break;
	      case _New_York_City_Warzone:
      		messages ("NY City Warzone", 0, 56);
   	      break;
	      case _Downtown_Mayhem:
      		messages ("Downtown Mayhem", 0, 56);
   	      break;
	      case _Old_Remo:
      		messages ("Old Remo", 0, 56);
   	      break;
	      case _Mines:
      		messages ("Mines", 0, 56);
   	      break;
	      case _Marina_Harbour:
      		messages ("Marina Harbour", 0, 56);
   	      break;
	      case _Graveyard:
      		messages ("Graveyard", 0, 56);
   	      break;
	      case _CLASS_Corp:
      		messages ("CLASS Corp", 0, 56);
   	      break;
	      case _Shelter_Tec:
      		messages ("Shelter Tec", 0, 56);
   	      break;
	      case _Puerto_Zombico:
      		messages ("Puerto Zombico", 0, 56);
   	      break;
	      case _Atlantic_Accelerator:
      		messages ("ATLTC Accelerator", 0, 56);
   	      break;
   	   default:
	      	messages ("Wilderness", 0, 56);
   	      break;
	   }
   }

   if (!stat || stat == 10)
   {
   	clear_area (63, 7, 78, 8);
      textcolor (8);
		gotoxy (63, 7);

      if (current_weapon == 1)
      {
      	if (item_body [_SIDEARM_SLOT] >= 0)
	      	enter_item (item_body [_SIDEARM_SLOT], 56);
         else if (item_body [_PRIME_SLOT] >= 0)
         {
         	current_weapon = 2;
				enter_item (item_body [_PRIME_SLOT], 56);
         }
      }
      else if (current_weapon == 2)
      {
      	if (item_body [_PRIME_SLOT] >= 0)
	      	enter_item (item_body [_PRIME_SLOT], 56);
         else if (item_body [_SIDEARM_SLOT] >= 0)
         {
         	current_weapon = 1;
				enter_item (item_body [_SIDEARM_SLOT], 56);
         }
      }

		gotoxy (63, 8);

      if (current_weapon == 1)
      {
      	if (item_body [_SIDEARM_SLOT] >= 0)
         {
				kod_p = search_item (25, item_ident [item_body [_SIDEARM_SLOT]]);

         	if (kod_p >= 0)						// jest amunicja w plecaku
					messages ("Ammo: ^", item_amount [kod_p], 56);
         }
      }
      else if (current_weapon == 2)
      {
      	if (item_body [_PRIME_SLOT] >= 0)
         {
				kod_p = search_item (25, item_ident [item_body [_PRIME_SLOT]]);

         	if (kod_p >= 0)						// jest amunicja w plecaku
					messages ("Ammo: ^", item_amount [kod_p], 56);
         }
      }
   }

   if (!stat || stat == 11)
   {
   	gotoxy (63, 4);

      for (j = 0; j < 17; j ++)
      {
      	if (17 * health / total_max_health > j - 1 && health > 0)
	      	messages (">", 0, 48 + COLOR_DARK_RED);
         else
	      	messages (">", 0, 48 + COLOR_GRAY);
      }
   }

   if (!stat || stat == 12)
   {
   }

	if (!stat || stat == 20)
   {
   	clear_area (63, 13, 75, 13);

      for (j = 0; j < 30; j ++)
      {
/*	   	if (character_state [0] != 4 && (state % 2))
  		   	gotoxy (72, 16 + state / 2);
     		else
  			gotoxy (63, 16 + state / 2);*/
  			gotoxy (63, 13);

        	if ((state_level = character_state [j]) != 0)
         {
           	switch (j)
            {
              	case 0:
                 	if (state_level == 5)
                    	messages ("Satiated", 0, 56);
                  else if (state_level == 6)
                    	messages ("Bloated", 0, 56);
                  else if (state_level == 2)
                    	messages ("Hungry!", 0, 56);
                  else if (state_level == 1)
                    	messages ("Starving", 0, 56);
                  else if (state_level == 3)
                    	messages ("Hungry", 0, 56);
                  else if (state_level == 7)
                    	messages ("STARVED", 0, 56);
                  break;
               case _POISONED:
               	if (!state_level)
                  	messages ("        ", 0, 56);
               	else if (state_level == 1)
                  	messages ("Poisoned", 0, 56);
               	else if (state_level == 2)
                  	messages ("Poisoned", 0, 62);
               	else if (state_level == 3)
                  	messages ("Poisoned", 0, 60);
                  break;
               case _DRUGGED:
               	if (!state_level)
                  	messages ("        ", 0, 56);
               	else if (state_level == 1)
                  	messages ("Drugged", 0, 56);
               	else if (state_level == 2)
                  	messages ("Drugged", 0, 62);
                  break;
					case _DEAD:
                 	messages ("Dead", 0, 55);
                  break;
				}

				state ++;
			}
      }
   }
}

void rysuj_ekran ()
{
	clear ();
   rysuj_plansze ();
   statystyki (0);
}

void aktualizuj_pole (int x_pos, int y_pos)
{
	int kod_p;

	if (check_own_visibility (x_pos, y_pos))
   {
		kod_p = monsters_planszy [x_pos] [y_pos];

  		if (kod_p >= 0)
 		   put_char (monster [kod_p], x_pos, y_pos);
      else if (kod_p == -1)
 		   put_char (player, x_pos, y_pos);
     	else // item lub plansza
 	   	put_char (mem_planszy [x_pos] [y_pos] = plansza [x_pos] [y_pos], x_pos, y_pos);
   }
}

void enter_char (int char_id, int x_pos, int y_pos)
{
	if (h_pos_pl + x_pos - h_pos >= 0 && v_pos_pl + y_pos - v_pos >= 0 && v_pos_pl + y_pos - v_pos < Y_WINDOW && h_pos_pl + x_pos - h_pos < X_WINDOW)
	{
	   x_pos = x_pos - h_pos + h_pos_pl;
	   y_pos = y_pos - v_pos + v_pos_pl;

		gotoxy (x_pos + LB, y_pos + UB);
  		textcolor (char_id / 256);
	   addch (char_id);
   }
}

int put_char (int char_id, int x_pos, int y_pos)
{
/*	if (floor_planszy [h_pos] [v_pos] == 21)
     	char_id = char_id % 256 + losuj_2 (CYAN, BLUE);*/

	if (character_state [_DRUGGED])
  	{
   	if (drugs [0])
	      char_id = char_id % 256 + losuj_2 (RED, VIOLET);
   }

	if (h_pos_pl + x_pos - h_pos >= 0 && v_pos_pl + y_pos - v_pos >= 0 && v_pos_pl + y_pos - v_pos < Y_WINDOW && h_pos_pl + x_pos - h_pos < X_WINDOW)
   {
	   x_pos = x_pos - h_pos + h_pos_pl;
   	y_pos = y_pos - v_pos + v_pos_pl;

		gotoxy (x_pos + LB, y_pos + UB);
		textcolor (char_id / 256);
	   addch (char_id);
	}

   return char_id;
}

void put_monsters ()
{
	verify_visible_monsters ();
}

void verify_visible_monsters ()
{
	int i, a = 0, x_pos, y_pos;

	for (i = 0; i < monsters_amount; i ++)
   {
   	x_pos = h_pos_mon [i];
      y_pos = v_pos_mon [i];

   	if (check_own_visibility (x_pos, y_pos))
      {
      	visible_monsters [a] = i;
         a ++;
      }
   }

   visible_monsters [a] = -15;
   i = 0;

   while ((a = visible_monsters [i]) != -15)		// wyswietla widziane potwory
  	{
   	x_pos = h_pos_mon [a];
  	   y_pos = v_pos_mon [a];
     	put_char (monster [a], x_pos, y_pos);
   	i ++;
   }

   if (check_own_visibility (h_pos, v_pos))
      put_char (player, h_pos, v_pos);
}

void generuj_text_line (char horizontal, char vertical, int kod_floor[])
{
	int x, string_length = 0;

	while ((x = kod_floor [string_length]) != '\0')
   	string_length ++;

	for (x = 0; x < string_length; x ++)
   {
   }
}

void put_char_on_cursor_shoot (int shooter, int kod_char, int x_mod, int y_mod)
{
	int _h_pos = h_pos, _v_pos = v_pos;

	if (shooter == -1)
   {
	  	ustaw_kursor ();
		gotoxy (h_pos_pl + LB + x_mod, v_pos_pl + UB + y_mod);

	  	if (drugs [0])
   	   kod_char = kod_char % 256 + losuj_2 (RED, VIOLET);

		textcolor (kod_char / 256);
		addch (kod_char);
	   ustaw_gracza ();
   }
   else
   	put_char (kod_char, h_cur + x_mod, v_cur + y_mod);
}

void change_color (int kod_c, int x_pos, int y_pos)
{
	int view_wall = plansza [x_pos] [y_pos] / 8192 * 8192;
  	int kod_k = plansza [x_pos] [y_pos] % 8192 / 256 * 256;

	if (kod_c == 1)			// burning
		plansza [x_pos] [y_pos] = plansza [x_pos] [y_pos] % 256 + losuj_2 (RED, DARK_RED) + view_wall;
   else		// water
   {
   }
}
