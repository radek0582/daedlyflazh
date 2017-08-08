#include "deklaracje.h"

void display_monsters ()
{
   int i, y;

	clrscr ();

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

void display_view ()
{
/*	int i = 0, j = 0, k, l, m, n;

	if (h_pos > 30)
	  	i = h_pos - h_pos_pl;

	if (v_pos > 10)
	   j = v_pos - v_pos_pl;

   m = i - h_pos;
   n = j - v_pos;
   k = i + X_WINDOW;
   l = j + Y_WINDOW;

   for (i = 0; i < 60; i ++)
   	for (j = 0; j < 20; j ++)
      {
      	if (display_area [i] [j] != mem_planszy [i] [j])
				put_char (display_area [i] [j], i, j);
      }

/*   for (; i < k; i ++)
   	for (; j < l; j ++)
      {
//      	if (display_area [i] [j] == mem_planszy [i] [j])
				put_char (display_area [i] [j], i, j);
      }*/
}

void make_view_matrix ()
{
	int a, y, x, l, k, _view_range;
   int i, j;

	for (i = 0; i < Y_MATRIX; i ++)
		for (j = 0; j < X_MATRIX; j ++)
			view_matrix_table [j] [i] = 0;

	view_matrix_table [X_MAX] [Y_MAX] = 1;		// player
   _view_range = view_range;

	for (a = RESOLUTION; a >= -RESOLUTION; a --)
	{
		x = 0;
      view_range = _view_range;

		while (x <= view_range)
		{
      	x ++;
			y = a * x / RESOLUTION;
			view_matrix_table [X_MAX - x] [Y_MAX - y] = 1;

			if (x > h_pos || y > v_pos || plansza [h_pos - x] [v_pos - y] > 8192)
				break;
         else if (floor_planszy [h_pos - x] [v_pos - y] == 2)
         	view_range /= 2;
		}

		x = 0;
      view_range = _view_range;

		while (x <= view_range)
		{
      	x ++;
			y = a * x / RESOLUTION;
			view_matrix_table [X_MAX + x] [Y_MAX - y] = 1;

			if (x + h_pos >= x_planszy || y > v_pos || plansza [h_pos + x] [v_pos - y] > 8192)
				break;
         else if (floor_planszy [h_pos + x] [v_pos - y] == 2)
         	view_range /= 2;
		}
	}

	for (a = RESOLUTION; a >= -RESOLUTION; a --)
	{
		y = 0;
      view_range = _view_range;

		while (y <= view_range)
		{
      	y ++;
			x = a * y / RESOLUTION;
			view_matrix_table [X_MAX - x] [Y_MAX - y] = 1;

			if (x > h_pos || y > v_pos || plansza [h_pos - x] [v_pos - y] > 8192)
				break;
         else if (floor_planszy [h_pos - x] [v_pos - y] == 2)
         	view_range /= 2;
		}

		y = 0;
      view_range = _view_range;

		while (y <= view_range)
		{
      	y ++;
			x = a * y / RESOLUTION;
			view_matrix_table [X_MAX - x] [Y_MAX + y] = 1;

			if (x > h_pos || y + v_pos >= y_planszy || plansza [h_pos - x] [v_pos + y] > 8192)
				break;
         else if (floor_planszy [h_pos - x] [v_pos + y] == 2)
         	view_range /= 2;
		}
	}

   view_range = _view_range;

	for (l = - view_range - 1; l <= view_range + 1; l ++)
		for (k = - view_range - 1; k <= view_range + 1; k ++)
			if (view_range <= sqrt (pow (l, 2) + pow (k, 2)) - 0.5)
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
      	if (mem_planszy [q] [r])
	        	enter_char (mem_planszy [q] [r], q, r);

	oblicz_stats ();
   msg_reset ();
   rysuj_view_range ();
	put_monsters ();
}

void statystyki (char stat)
{
   char state = 0, j, state_level;

	if (!stat)
   {
		textcolor (7);
		gotoxy (63, 2); cprintf ("%s", player_name);
	   gotoxy (63, 14); messages ("Lev: ", 0, 24);

	   switch (cl_id)
   	{
	   	case _WORLD:
      		messages ("Ishmar", 0, 56);
   	      break;
	      case _SMALLVILLAGE:
      		messages ("SmallVill", 0, 56);
   	      break;
	      case _OUTLAWSVILLAGE:
      		messages ("Outlaws", 0, 56);
   	      break;
	      case _YERUSHALAYIM:
      		messages ("Yerushalayim", 0, 56);
   	      break;
	      case _ARENA:
      		messages ("Arena", 0, 56);
   	      break;
	      case _LUNE1:
      		messages ("ShaDun1", 0, 56);
   	      break;
	      case _LUNE2:
      		messages ("ShaDun2", 0, 56);
   	      break;
	      case _LUNE3:
   	   	messages ("ShaDun3", 0, 56);
	         break;
   	   default:
	      	messages ("Wilderness", 0, 56);
   	      break;
	   }
   }

	if (!stat || stat >= 1 && stat <= 8)
   	textcolor (8);

   if (!stat || stat == 1)
   {
		gotoxy (63, 4);
      cprintf ("Str: %2d", total_strength);
   }

   if (!stat || stat == 2)
   {
		gotoxy (63, 5);
      cprintf ("Kno: %2d", total_knowledge);
   }

   if (!stat || stat == 4)
   {
		gotoxy (72, 5);
      cprintf ("Min: %2d", total_mind);
   }

   if (!stat || stat == 5)
   {
		gotoxy (72, 4);
      cprintf ("Dex: %2d", total_dexterity);
   }

   if (!stat || stat == 9)
   {
   	clear_window (63, 7, 70, 7);
      textcolor (8);
		gotoxy (63, 7);
      cprintf ("Sp: %3d", total_speed);
   }

   if (!stat || stat == 10)
   {
   	clear_window (72, 7, 78, 7);
      textcolor (8);
		gotoxy (72, 7);
      cprintf ("AL: %3d", total_armor);
   }

   if (!stat || stat == 11)
   {
   	gotoxy (63, 8);
		messages ("HP: ^", health, 56);
      messages (" (^)  ", total_max_health, 56);
   }

   if (!stat || stat == 12)
   {
		gotoxy (63, 9);
      messages ("PP: ^", power, 56);
      messages (" (^)  ", total_max_power, 56);
   }

   if (!stat || stat == 13)
   {
		gotoxy (63, 11);
      messages ("Exp: ^", exp_lev, 56);
      messages ("/^", experience, 56);
   }

	if (!stat || stat == 14)
   {
   	gotoxy (63, 10);
      messages ("O2: ^", air, 56);
      messages (" (^)  ", total_max_air, 56);
   }

	if (!stat || stat == 20)
   {
   	clear_window (63, 16, 79, 20);

      for (j = 0; j < 30; j ++)
      {
	   	if (character_state [0] != 4 && (state % 2))
  		   	gotoxy (72, 16 + state / 2);
     		else
     			gotoxy (63, 16 + state / 2);

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
	clrscr ();
   rysuj_plansze ();
   statystyki (0);
}

void msg (char _msg [])
{
	messages (_msg, 0, 7);
	messages (" ", 0, 7);
}

void msg_reset ()
{
	messages ("", 0, 100);
}

void kropka (char p_color)
{
	messages (". ", 0, p_color);
}

void message_buffor ()
{
	int i, temp_, j = 0, esc_ = 0;

   textcolor (13);

	for (i = 0; i < buffor_counter; i ++)
   {
   	if (message [i] == 13)
      {
      	j++;
         putch (10);
         putch (13);

         if (!(j % 20))
         {
         	while (1)
            {
            	klawisz ();

               if (key == 27)		// esc
               {
               	esc_ = 1;
                  break;
               }
               else if (key == 13)	// enter = page down
               {
               	temp_ = i;
                  clrscr ();
                  break;
               }
               else if (key == '+')	// page up
               {
               	j -= 20;
                  i = temp_;
                  break;
               }
               else if (key == '-')	// poczatek
               {
               	i = 0;
               	j = 0;
                  break;
               }
            }
         }
      }
      else
		  	putch (message [i]);

      if (esc_)
      	break;
   }

	if (!esc_)
   {
	   do klawisz ();
   	while (key != 27);
   }
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
	   putch (char_id);
   }
}

int put_char (int char_id, int x_pos, int y_pos)
{
/*	if (floor_planszy [h_pos] [v_pos] == 21)
     	char_id = char_id % 256 + losuj_2 (CYAN, BLUE);*/

	if (character_state [_DRUGGED])
  	{
   	if (drugs [0])
	      char_id = char_id % 256 + losuj_4 (RED, DARK_RED, DARK_VIOLET, VIOLET);
   }

	if (h_pos_pl + x_pos - h_pos >= 0 && v_pos_pl + y_pos - v_pos >= 0 && v_pos_pl + y_pos - v_pos < Y_WINDOW && h_pos_pl + x_pos - h_pos < X_WINDOW)
   {
	   x_pos = x_pos - h_pos + h_pos_pl;
   	y_pos = y_pos - v_pos + v_pos_pl;

		gotoxy (x_pos + LB, y_pos + UB);
		textcolor (char_id / 256);
	   putch (char_id);
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

void put_char_on_cursor_shoot (int shooter, int kod_char)
{
	int _h_pos = h_pos, _v_pos = v_pos;

	if (shooter == -1)
   {
	  	ustaw_kursor ();
		gotoxy (h_pos_pl + LB, v_pos_pl + UB);

	  	if (drugs [0])
   	   kod_char = kod_char % 256 + losuj_4 (RED, DARK_RED, DARK_VIOLET, VIOLET);

		textcolor (kod_char / 256);
		putch (kod_char);
	   ustaw_gracza ();
   }
   else
   	put_char (kod_char, h_cur, v_cur);
}
