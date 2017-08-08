#include "deklaracje.h"

#include "ekwipunek.c"
#include "floor.c"
#include "turn.c"
#include "klawisze.c"
#include "bestiariusz.c"
#include "achieve.c"
#include "stats.c"
#include "miejsca.c"
#include "display.c"
#include "text.c"
#include "chat.c"
#include "targeting2.c"
#include "inventory2.c"
#include "attack.c"
#include "events2.c"
#include "tool.c"
#include "pay.c"
#include "ai2.c"
#include "start.c"
#include "locations.c"
#include "action_item2.c"
#include "screens.c"
#include "choice.c"
#include "flag.c"
#include "rng.c"
#include "exp.c"
#include "look.c"
#include "eat.c"

#include "addch.c"
//#include "addchstr.c"
#include "addstr.c"
#include "attr.c"
#include "beep.c"
//#include "bkgd.c"
#include "border.c"
#include "clear.c"
#include "color.c"
//#include "debug.c"
//#include "delch.c"
//#include "deleteln.c"
//#include "deprec.c"
#include "getch.c"
#include "getstr.c"
#include "getyx.c"
//#include "inch.c"
//#include "inchstr.c"
#include "initscr.c"
#include "inopts.c"
#include "insch.c"
//#include "insstr.c"
#include "instr.c"
#include "kernel.c"
#include "keyname.c"
//#include "mouse.c"
#include "move.c"
//#include "outopts.c"
#include "overlay.c"
#include "pad.c"
//#include "panel.c"
//#include "pdcclip.c"
#include "pdcdisp.c"
#include "pdcgetsc.c"
#include "pdckbd.c"
#include "pdcscrn.c"
#include "pdcsetsc.c"
#include "pdcutil.c"
#include "printw.c"
#include "refresh.c"
//#include "scanw.c"
//#include "scr_dump.c"
#include "scroll.c"
#include "slk.c"
//#include "termattr.c"
//#include "terminfo.c"
#include "touch.c"
#include "util.c"
#include "window.c"

int main (void)
{
	initscr();
   cbreak ();
	noecho ();
	start_color ();
	keypad (stdscr, TRUE);
	curs_set (0);

	if (!has_colors ())
   {
		endwin ();
		fputs ("No colors!", stderr);
		exit (1);
	}

   inicjuj_kolory ();
	randomize ();

	if ((temp00 = fopen ("achieve.a", "rt")) == NULL)
   {
		fclose (temp00);
   	save_achievements ();
   }
   else
	   load_achievements ();

	if ((temp00 = fopen ("daedly.run", "rt")) == NULL)		// brak pliku
   {
		temp10 = fopen ("daedly.run", "w");
		messages ("This file is created when DAEDLYFLAZH starts.\nDelete it after unconventional closing.", 0, 80);
		fclose (temp10);
		ekran_powitalny ();
   }
   else
   {
   	messages ("Error! Erase daedly.run file first!_", 0, 14);
      play = 0;
   }

   if (play)
   {
   	if (play == 1)
      {
		   intro ();
			ekran_wyboru ();
      }

      ustaw_gracza ();
   	oblicz_stats ();
		rysuj_ekran ();
//  	  	area_description (cl_id);
		msg ("Welcome to the world of DAEDLYFLAZH! Press 'I' for instructions.");
   }

	while (play > 0)
   {
   	gotoxy (h_pos_pl + LB, v_pos_pl + UB);
		_setcursortype (_NORMALCURSOR);

		klawisze ();
   }

   if (death || play)
   {
      if (play < 0 && turns_amount < 1000)
      	gain_achievement (22);

      if ((item_id = search_item (17, 3)) >= 0 && item_amount [item_id] >= 100)
      	gain_achievement (36);

		if (play < 0 && player_name [0] == 'H' && player_name [1] == 'a' && player_name [2] == 's' && player_name [3] == 'r' && player_name [4] == 'i' && player_name [5] == 'n' && player_name [6] == 'a' && player_name [7] == 'x' && player_name [8] == 'x' && player_name [9] == 0)
       	gain_achievement (29);

      save_achievements ();
	   msg ("<Do you want to create a memorial file (y/n) ?");

	   if (answer ())
			create_flag ();
   }

	remove ("daedly.run");
   return 0;
}

void _setcursortype (int a)
{
	if (a == _NORMALCURSOR)
   	curs_set (1);
   else
   	curs_set (0);
}

void gotoxy (int x, int y)
{
	move (y, x);
}

void textcolor (int kolor)
{
   if (kolor < 128)
   {
   	if (kolor < 64)
		  	kolor %= 16;

		attron (COLOR_PAIR (kolor));
   }
   else
   	attron (COLOR_PAIR (kolor));
}
/*
void textbackground (int a)
{
	init_pair (a, COLOR_GREEN, COLOR_BLACK);
	attron (COLOR_PAIR (a));
} // j.w.*/

void change_character_state (char stat)
{
	if (stat == 1)
   {
		if (satiation > 14999 && satiation < 17000)
   		character_state [0] = 3;
	   else if (satiation > 21999 && satiation < 25000)
   		character_state [0] = 5;
   	else if (satiation > 24999)
   		character_state [0] = 6;
	   else if (satiation > 12999 && satiation < 15000)
   		character_state [0] = 2;
   	else if (satiation > 999 && satiation < 13000)
   		character_state [0] = 1;
	   else if (satiation > 16999 && satiation < 22000)
   		character_state [0] = 4;
      else if (satiation < 1000)
      {
      	character_state [0] = 7;
         character_state [_DEAD] = 1;
      }
   }

   statystyki (20);
}

void do_character_state (char stat)
{
	int state_type, poison_dmg [7];

	if (stat == _POISONED)
   {
     	for (state_type = 0; state_type < 7; state_type ++)
      {
        	if (left_poison_turns [state_type])
         {
           	left_poison_turns [state_type] --;

            if (cl_id == 1999)
              	left_poison_turns [state_type] -= 20;

            switch (state_type)
            {
            	case 0:		// light poison (eg. spider)
               default:
		            poison_dmg [0] = (left_poison_turns [0] + 1) * 2;
                  break;
               case 1:		// middle power poison (eg. demon's daisy)
		            poison_dmg [1] = (left_poison_turns [1] + 3) * 2;
                  break;
               case 4:		// strong poison (eg. black lotos)
		            poison_dmg [4] = left_poison_turns [4] * 2 + 10;
                  break;
            }

            if (left_poison_turns [state_type] < 1)
            {
            	character_state [_POISONED] = 0;
  	         	left_poison_turns [state_type] = 0;
               statystyki (20);
            }
		     	else if ((left_poison_turns [state_type] % losuj_3 (2, 5, 7)))
			   {
		        	msg ("Poison is coursing through your veins!");
		         drain_health (poison_dmg [state_type] + rand () % (poison_dmg [state_type] / 2), 2);
		      }
			}
		}
   }
	else if (stat == _DRUGGED)
   {
     	for (state_type = 0; state_type < 7; state_type ++)
      {
        	if (drugs [state_type])
         {
           	drugs [state_type] --;

            if (cl_id == 1999)
              	drugs [state_type] -= 20;

            if (drugs [state_type] < 1)
            {
            	character_state [_DRUGGED] = 0;
  	         	drugs [state_type] = 0;
               statystyki (20);
            }
			}
		}
   }
   else if (stat == _DEAD)
   {
     	health = 0;
		drain_health (0, 5);
   }
}

void drain_health (int health_to_drain, char drain_type)
{
	health -= health_to_drain;

	switch (drain_type)
   {
      case 6:		// fire
			health -= (10 + rand () % 15) / (1 + resistance [0]);
         break;
      case 7:		// lava
			health -= -(20 + rand () % 30) / (1 + resistance [0]);
         break;
   }

   statystyki (11);

   if (health < 1)
		death = drain_type;
}

void reputation_change (int kod_p)
{
	if (monster_alignment [kod_p] >= 0 && goody_reputation [cl_id] >= -5)
     	goody_reputation [cl_id] = -5;
   else if (monster_alignment [kod_p] < 0 && badass_reputation [cl_id] >= -5)
     	badass_reputation [cl_id] = -5;
}

void cast (int shooter, char attack_type, int spell_type)
{
	int x_pos, y_pos;
   int radius;

   if (shooter == -1)
   {
   	x_pos = h_pos;
      y_pos = v_pos;
      radius = total_mind / 16 + 3;
   }
   else
   {
   	x_pos = h_pos_mon [shooter];
      y_pos = v_pos_mon [shooter];
      radius = 3;
   }

   if (spell_type == 403)		// darkness
   	create_a_ball (shooter, x_pos, y_pos, radius, attack_type, spell_type);
   else if (spell_type == _LIGHTNING_BALL)
   {
   	create_a_ball (shooter, x_pos, y_pos, radius, attack_type, spell_type);
   }
   else if (spell_type == 201)
   {
		event_throw (shooter, attack_type, spell_type, x_pos, y_pos, 0, 0, 0, 0);
   }

   if (attack_type == 2)		// a wand - odejmowanie ladunku
   {
   }
}


void create_a_ball (int shooter, int x_pos, int y_pos, int radius, char attack_type, int spell_type)
{
   char ball_matrix [120] [40];
	int a, y, x, l, k, i, j, h_shooter, v_shooter, kod_p, kolor_id, kod_o;

	for (i = 0; i < 40; i ++)
		for (j = 0; j < 120; j ++)
			ball_matrix [j] [i] = 0;

//	if (spell_type == 403)
		ball_matrix [60] [20] = 1;

	if (shooter == -1)
   {
	   h_shooter = h_pos;
   	v_shooter = v_pos;
   }
   else if (shooter >= 0)
   {
	  	h_cur = h_pos_mon [shooter];
	   v_cur = v_pos_mon [shooter];
   }
   else
   {
	  	h_cur = x_pos;
	   v_cur = y_pos;
   }

/*	if (v_shooter >= v_cur)
   {
	   if (h_shooter >= h_cur)
      {
	      x_pos = h_shooter - h_cur;
         y_pos = v_shooter - v_cur;
      }
	   else
      {
         x_pos = h_cur - h_shooter;
         y_pos = v_shooter - v_cur;
      }
   }
   else
   {
	   if (h_shooter >= h_cur)
      {
	      x_pos = h_shooter - h_cur;
         y_pos = v_cur - v_shooter;
      }
	   else
      {
         x_pos = h_cur - h_shooter;
         y_pos = v_cur - v_shooter;
      }
  	}*/

/*   x_pos += h_pos_pl;
   y_pos += v_pos_pl;*/

	for (a = RESOLUTION; a >= -RESOLUTION; a --)
	{
		x = 0;

		while (x <= radius)
		{
      	x ++;
			y = a * x / RESOLUTION;
			ball_matrix [60 - x] [20 - y] = 1;

			if (plansza [x_pos - x] [y_pos - y] > 8192)
				break;
		}

		x = 0;

		while (x <= radius)
		{
      	x ++;
			y = a * x / RESOLUTION;
			ball_matrix [60 + x] [20 - y] = 1;

			if (plansza [x_pos + x] [y_pos - y] > 8192)
				break;
		}
	}

	for (a = RESOLUTION; a >= -RESOLUTION; a --)
	{
		y = 0;

		while (y <= radius)
		{
      	y ++;
			x = a * y / RESOLUTION;
			ball_matrix [60 - x] [20 - y] = 1;

			if (plansza [x_pos - x] [y_pos - y] > 8192)
				break;
		}

		y = 0;

		while (y <= radius)
		{
      	y ++;
			x = a * y / RESOLUTION;
			ball_matrix [60 - x] [20 + y] = 1;

			if (plansza [x_pos - x] [y_pos + y] > 8192)
				break;
		}
	}

	for (l = - radius - 1; l <= radius + 1; l ++)
		for (k = - radius - 1; k <= radius + 1; k ++)
			if (x_pos + k < 0 || y_pos + l < 0 || x_pos + k + 1 > x_planszy || y_pos + l + 1 > y_planszy || radius <= sqrt (pow (l, 2) + pow (k, 2)) - 0.7)
				ball_matrix [60 + k] [20 + l] = 0;

	for (a = 1; a <= radius; a ++)
   {
		for (l = - a - 1; l <= a + 1; l ++)
			for (k = - a - 1; k <= a + 1; k ++)
      	{
				if (k == 0 && l == 0 && a == 1 || ball_matrix [60 + k] [20 + l] && a >= sqrt (pow (l, 2) + pow (k, 2)) - 0.7 && a <= sqrt (pow (l, 2) + pow (k, 2)) + 0.7)
            {
              	kolor_id = RED;

					if (check_own_visibility (x_pos + k, y_pos + l))
		            put_char_on_cursor_shoot (shooter, '*' + kolor_id, k, l);

               kod_p = monsters_planszy [x_pos + k] [y_pos + l];
               kod_o = obstacles_planszy [x_pos + k] [y_pos + l];

               if (kod_p >= -1)
               	attack (kod_p, kod_p, attack_type, spell_type);

               if (floor_planszy [x_pos + k] [y_pos + l] == 12)
               {
               	floor_planszy [x_pos + k] [y_pos + l] = _floor;
                  convert_floor (x_pos + k, y_pos + l);
                  msg ("The wall is destroyed! ");
               }

               if (kod_o >= 0)
               {
	               if (spell_type == 300 && item_group [kod_o] == 64 && item_type [kod_o] == 1)		// core 64
                  {
	                  msg ("Core64 is destroyed! ");
                     ujmij_item (kod_o, 1);
						   create_item (_ALLOYS, 0, x_pos + k, y_pos + l, losuj (1, 7));
                    	quest [10] = -1;
                     gain_achievement (16);
							badass_reputation [cl_id] = -10;
                  }
               }
	         }
	      }

      wait (100);
   }

   wait (300);

	for (a = 1; a <= radius; a ++)
   {
		for (l = - a - 1; l <= a + 1; l ++)
			for (k = - a - 1; k <= a + 1; k ++)
      	{
				if (ball_matrix [60 + k] [20 + l])// && a > sqrt (pow (l, 2) + pow (k, 2)) - 0.7 && a <= sqrt (pow (l, 2) + pow (k, 2)) + 0.7)
            {
					if (check_own_visibility (x_pos + k, y_pos + l))
               {
               	kod_p = monsters_planszy [x_pos + k] [y_pos + l];

				   	if (kod_p >= 0)
						   put_char_on_cursor_shoot (shooter, monster [kod_p], k, l);
				      else if (kod_p == -1)
						   put_char_on_cursor_shoot (shooter, player, k, l);
				      else // item lub plansza
						   put_char_on_cursor_shoot (shooter, mem_planszy [h_cur + k] [v_cur + l], k, l);
               }
	         }
	      }
   }

/*	for (l = - radius - 1; l <= radius + 1; l ++)
		for (k = - radius - 1; k <= radius + 1; k ++)
			if (ball_matrix [60 + k] [20 + l] && radius > sqrt (pow (l, 2) + pow (k, 2)) - 0.7 && check_own_visibility (x_pos + k, y_pos + l))
			  	aktualizuj_pole (x_pos + k, y_pos + l);*/
}

void select_a_wand ()
{
	int typ_wedki;

   reset_inv_globals ();
   wybierz_item = 1;
   messages ("\n #### Select a wand to zap ####\n\r", 0, 27);

	do
   {
		for (item_id = 0; item_id < items_amount; item_id ++)
		{
			if (item [item_id] == 1 && item_group [item_id] == 21)	// czy w plecaku i czy nalezy do danej grupy (21 = wands)
			{
				gotoxy (2, 3 + i_y);
				list_item ();

				if (i_y > 17)
				{
					gotoxy (2, 24);
					messages ("'-' - First page   '+' - Page up   Enter - Page down   Esc - Exit", 0, 27);

					while (!exit_list)
					{
						klawisz ();

						if (key == 27)		// esc
						{
							i_y = 0;
							exit_list = 1;
							alfabet = 97;
               	   rysuj_ekran ();
							break;
						}
						else if (key == 13)		// enter = pg down
						{
							i_y = 0;
							clear_area (1, 3, 80, 22);
							alfabet = 97;
							break;
						}
						else if (key == 45)		// first page
						{
        	         	i_y = 1;
							clear_area (1, 3, 80, 22);
							gotoxy (1, 3);
                    	item_id = 0;
							alfabet = 97;
                     break;
						}
						else if (key >= 'a' && key < alfabet)
            	   {
                  	typ_wedki = item_type [inv [key - 96]];
                  	rysuj_ekran ();

                     if (typ_wedki < 300)
	               		targeting (-1, 2, typ_wedki);
                     else
                     	cast (-1, 2, typ_wedki);

                     exit_list = 1;
                  	break;
	               }
					}
				}
			}
			if (exit_list == 1)
				break;
		}

		if (!exit_list)
      {
			while (1)
			{
				klawisz ();

				if (key >= 'a' && key < alfabet)
				{
              	typ_wedki = item_type [inv [key - 96]];
            	rysuj_ekran ();

					if (typ_wedki < 300)
		      		targeting (-1, 2, typ_wedki);
               else
                 	cast (-1, 2, typ_wedki);

               exit_list = 1;
					break;
				}
				else if (key == 45)		// first page
				{
					alfabet = 97;
      	   	i_y = 1;
					clear_area (1, 3, 80, 22);
					gotoxy (1, 3);
   	        	item_id = 0;
      	      break;
				}
				else if (key == 27)
      		{
		      	rysuj_ekran ();
   	         exit_list = 1;
					break;
      		}
			}
      }
   }
   while (!exit_list);

   wybierz_item = 0;
}

void reset_inv_globals ()
{
//	clear ();
	exit_list = 0;
	i_y = 1;
	temp = 0;
   alfabet = 97;
}

void event_cost (int event_group, int event_subgroup)
{
	if (event_group == 1)				// move
   {
   	if (event_subgroup == 1)		// grass
	   	action_cost = 110;
      else if (event_subgroup == 2)
      	action_cost = 128;			// stone floor
      else if (event_subgroup == 4)
      	action_cost = 90;			// sand
   }
	else if (event_group == 2)		// crushing into wall
   	action_cost = 128;			// normalna kara
   else if (event_group == 3)		// zabicie potwora
   	action_cost = 128;

   action_type = event_group *  64 + event_subgroup;
}

void create_item (int kod_itema, int item_place, int x_pos, int y_pos, int ilosc)
{
	ekwipunek (kod_itema, -5, item_place);
  	item_amount [item_id] = ilosc;
  	action_item (-3, x_pos, y_pos, 1, item_id);		// put item (action drop)
//  	aktualizuj_pole (x_pos, y_pos);
}

void monster_drop (int kod_potwora, int kod_przedmiotu, int ilosc)
{
   create_item (kod_przedmiotu, 0, h_pos_mon [kod_potwora], v_pos_mon [kod_potwora], ilosc);
}

void monster_drops_item (int kod_potwora, int kod_przedmiotu)
{
	action_item (kod_potwora, h_pos_mon [kod_potwora], v_pos_mon [kod_potwora], 1, kod_przedmiotu);
}

void delete_monster (int kod_p, int kod, int attack_type)
{
	int i, a = 0, j = 0;
   int x_pos = h_pos_mon [kod], y_pos = v_pos_mon [kod];
   int last_monster_id = monsters_amount - 1;

   if (monster_code [kod] == _D_Morgan)
  	{
      if (quest [8] == 2)
  	   {
   	   msg ("You have killed D'Morgan finishing your task. Return to Flint Westwood. ");
	  		quest [8] = -1;
  	   	gain_achievement (1);
  	   }
   }
  	else if (monster_code [kod] == _Bum)
   {
  	   if (quest [16] == 1)
     	{
	      msg ("Bum is killed, the murder of Atlantic Accelerator crew. Return to father Grigori. ");
	   	quest [16] = -1;
      }
  	}
  	else if (monster_code [kod] == _Pleasence || monster_code [kod] == _vice_prezio)
   {
  	   if (quest [12] == 1)
     	{
	      msg ("The president of NYC is killed. Go and talk with Shades. ");
	   	quest [12] = -1;
      }
  	}
   else if (monster_code [kod] >= 1100 && monster_code [kod] < 1200)
   	for (i = 0; i < items_amount; i ++)
      	if (unpaid_items [i] == kod)
         	unpaid_items [i] = 0;

	if (kod != last_monster_id)
		monsters_planszy [h_pos_mon [last_monster_id]] [v_pos_mon [last_monster_id]] = kod;
   else
		monsters_planszy [h_pos_mon [last_monster_id]] [v_pos_mon [last_monster_id]] = -15;

   if (kod_p == last_monster_id)			// atakujacy potwor ma indeks ostatni
   	current_monster_id = kod;

   if (kod != last_monster_id)
   {
		for (i = 0; i < monsters_amount; i ++)
   		if (monster_aim [i] == kod)
				monster_aim [i] = -5;
   		else if (monster_aim [i] == last_monster_id)
				monster_aim [i] = kod;
   }
   else
   {
		for (i = 0; i < monsters_amount; i ++)
   		if (monster_aim [i] == last_monster_id)
				monster_aim [i] = -5;
   }

	monsters_planszy [x_pos] [y_pos] = -15;

  	if (attack_type < 2 && check_own_visibility (x_pos, y_pos))			// widzi potwora i nie-kaboom
   	aktualizuj_pole (x_pos, y_pos);
//		put_char (plansza [x_pos] [y_pos], x_pos, y_pos);

	h_pos_mon [kod] = h_pos_mon [monsters_amount - 1];
	v_pos_mon [kod] = v_pos_mon [monsters_amount - 1];
	monster [kod] = monster [monsters_amount - 1];
	monster_char [kod] = monster_char [monsters_amount - 1];
	monster_code [kod] = monster_code [monsters_amount - 1];
	monster_health [kod] = monster_health [monsters_amount - 1];
	monster_damage [kod] = monster_damage [monsters_amount - 1];
	monster_dv [kod] = monster_dv [monsters_amount - 1];
	monster_hit [kod] = monster_hit [monsters_amount - 1];
	monster_exp [kod] = monster_exp [monsters_amount - 1];
	monster_speed [kod] = monster_speed [monsters_amount - 1];
	monster_aim [kod] = monster_aim [monsters_amount - 1];
	monster_pp [kod] = monster_pp [monsters_amount - 1];
	monster_hp [kod] = monster_hp [monsters_amount - 1];
	monster_alignment [kod] = monster_alignment [monsters_amount - 1];
	moves [kod] = moves [monsters_amount - 1];
	bonus [kod] = bonus [monsters_amount - 1];

	for (i = 0; i < 30; i ++)
		monster_state [kod] [i] = monster_state [monsters_amount - 1] [i];

	for (i = 0; i < 15; i ++)
		monster_body [kod] [i] = monster_body [monsters_amount - 1] [i];

	for (i = 0; i < 15; i ++)
		monster_backpack [kod] [i] = monster_backpack [monsters_amount - 1] [i];

	for (i = 0; i < 7; i ++)
		monster_left_poison [kod] [i] = monster_left_poison [monsters_amount - 1] [i];

/*	for (a = 1; a < 20; a ++)
  		if (item_body [a] == last_item_id)
     		item_body [a] = kod;
      else if (item_body [a] == kod)
     		item_body [a] = -1;*/

/*	for (j = 0; visible_monsters [j] != -15; j ++);

   for (i = 0; visible_monsters [i] != -15; i ++)
   	if (visible_monsters [i] == kod)
      {
      	visible_monsters [i] = visible_monsters [j - 1];
         visible_monsters [j - 1] = -15;
         break;
      }*/

	-- monsters_amount;
//	check_visible_monsters ();
}

void convert_plansza (int x_pos, int y_pos)
{
   if (!stan_planszy [x_pos] [y_pos])
   	convert_floor (x_pos, y_pos);
   else if (stan_planszy [x_pos] [y_pos] == 1)
   	plansza [x_pos] [y_pos] = item_icon [items_planszy [x_pos] [y_pos]];
   else if (stan_planszy [x_pos] [y_pos] == 2)
   	plansza [x_pos] [y_pos] = item_icon [obstacles_planszy [x_pos] [y_pos]];
   else if (stan_planszy [x_pos] [y_pos] == 3)
   	plansza [x_pos] [y_pos] = convert_coverer (x_pos, y_pos);
   else if (stan_planszy [x_pos] [y_pos] == 4)
   	plansza [x_pos] [y_pos] = item_icon [items_planszy [x_pos] [y_pos]];
   else if (stan_planszy [x_pos] [y_pos] == 5)
   	plansza [x_pos] [y_pos] = convert_coverer (x_pos, y_pos);
   else if (stan_planszy [x_pos] [y_pos] == 6)
   	plansza [x_pos] [y_pos] = convert_coverer (x_pos, y_pos);
   else if (stan_planszy [x_pos] [y_pos] == 7)
   	plansza [x_pos] [y_pos] = convert_coverer (x_pos, y_pos);
   else if (stan_planszy [x_pos] [y_pos] == 8)
   	plansza [x_pos] [y_pos] = 37 + DARK_GRAY;
   else if (stan_planszy [x_pos] [y_pos] == 9)
   	plansza [x_pos] [y_pos] = 37 + DARK_GRAY;
   else if (stan_planszy [x_pos] [y_pos] >= 10)
   	plansza [x_pos] [y_pos] = convert_coverer (x_pos, y_pos);
}

void trap (int guest, int trap_id)
{
	int i;

	if (guest == -1)		// na pulapke wchodzi gracz
   {
	   if (!item_status [trap_id])	// nie wykryta wczesniej
   	{
	   	item_status [trap_id] = 1;

   		switch (item_type [trap_id])
	      {
   	   	case 1:
      	   	msg ("A gush of water hits you.");
					item_icon [trap_id] = 94 + 2304;
	            break;
   	   }

         if (stan_planszy [h_pos_item [trap_id]] [v_pos_item [trap_id]] == -6)
		      plansza [h_pos_item [trap_id]] [v_pos_item [trap_id]] = item_icon [trap_id];
	   }
   	else
	   {
   		switch (item_type [trap_id])
      	{
	      	case 1:
   	      	msg ("There is");
               enter_item (trap_id, COLOR_GRAY);
               kropka (COLOR_GRAY);
      	      break;
	      }
   	}
   }
   else
   {
  		switch (item_type [trap_id])
      {
  	   	case 1:	// a gush of water hits an enemy
            break;
  	   }
   }
}

int find_npc (int kod_p)
{
	int i;

	for (i = 0; i < monsters_amount; i ++)
   	if (kod_p == monster_code [i])
      	return i;

   return -2;
}

int search_stairs (int grupa, int typ, int schody_id)
{
	int i;

	if (typ > 0)
   {
		for (i = 0; i < items_amount; i ++)
   		if (item [i] == 5 && item_group [i] == grupa && item_type [i] == typ && item_specials1 [i] == schody_id)
      		return i;
   }
   else
   {
		for (i = 0; i < items_amount; i ++)
   		if (item [i] == 5 && item_group [i] == grupa && item_specials2 [i] == cl_id)
      		return i;
   }

   return -1;
}

int search_door (int kod_d)
{
	int i;

	for (i = 0; i < items_amount; i ++)
  		if (item [i] == 5 && item_group [i] == 52 && item_status [i] == kod_d)
     		return i;

   return -1;
}

int search_obstacle (int grupa, int typ)
{
	int i;

	for (i = 0; i < items_amount; i ++)
  		if (item [i] == 5 && item_group [i] == grupa && item_type [i] == typ)
     		return i;

   return -1;
}

int search_shopkeeper (int kod_f)
{
	int i;

	for (i = 0; i < monsters_amount; i ++)
  		if (monster_char [i] == kod_f)
     		return i;

   return -1;
}

void generuj_items (int liczba_items)
{
	int a, b, c;
	liczba_items += items_amount;

	if (liczba_items > MAXITEMS)
		liczba_items = MAXITEMS;

	while (item_id < liczba_items)
	{
		int random_item, i;
		random_item = rand () % 9;
		ekwipunek (random_item, -5, 3);

/*		b = rand () % (X_PLANSZY - 2) + 1;
		c = rand () % (Y_PLANSZY - 2) + 1;

      a = stan_planszy [b] [c];

      if (item [a] != 5)
      {*/
     	h_pos_item [item_id] = rand () % (x_planszy - 2) + 1;
      v_pos_item [item_id] = rand () % (y_planszy - 2) + 1;
/*      else
      	item_id --;*/

/*		for (i = 0; i <= item_id; i ++)
			if (i != item_id && h_pos_item [item_id] == h_pos_item [i] && v_pos_item [item_id] == v_pos_item [i])
					item_id --;*/
	}
}

void listening (int zdarzenie, int x_event, int y_event)
{
	int listen_range = total_perception / 4 + 1;

	if (sqrt (pow (h_pos - x_event, 2) + pow (v_pos - y_event, 2)) < listen_range)
   {
		switch (zdarzenie)
   	{
   		case 1:
      		msg ("You hear door opening.");
	         break;
   	}
   }
}

char check_visibility (int obserwator_id, int obiekt_id)	// sprawdza czy potwor widzi swoj cel z uwzglednieniem przeszkod
{
	int x, y;
   int x_wzg, y_wzg, x_pos, y_pos;
   int monster_view_range = 10;

   if (obiekt_id >= 0)		// celem potwora jest inny potwor
   {
      x_pos = h_pos_mon [obiekt_id];
      y_pos = v_pos_mon [obiekt_id];
   }
   else							// celem potwora jest player
   {
      x_pos = h_pos;
      y_pos = v_pos;
   }

   if (sqrt (pow (x_pos - h_pos_mon [obserwator_id], 2) + pow (y_pos - v_pos_mon [obserwator_id], 2)) > monster_view_range)
		return 0;	// poza zasiegiem wzroku potwora

 	x_wzg = sqrt (pow (x_pos - h_pos_mon [obserwator_id], 2)) + 1;
	y_wzg = sqrt (pow (y_pos - v_pos_mon [obserwator_id], 2)) + 1;

	if (x_wzg >= y_wzg)
   {
  		for (x = 1; x < x_wzg; x ++)
     	{
        	y = x * y_wzg / x_wzg;

			if (v_pos_mon [obserwator_id] >= y_pos)
    	   {
      	   if (h_pos_mon [obserwator_id] >= x_pos)
            {
            	if (plansza [h_pos_mon [obserwator_id] - x] [v_pos_mon [obserwator_id] - y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
       	   else
            {
            	if (plansza [h_pos_mon [obserwator_id] + x] [v_pos_mon [obserwator_id] - y] > 8192)
               	return 0;
            }
  	      }
     	   else
         {
	         if (h_pos_mon [obserwator_id] >= x_pos)
            {
            	if (plansza [h_pos_mon [obserwator_id] - x] [v_pos_mon [obserwator_id] + y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
     		   else
            {
            	if (plansza [h_pos_mon [obserwator_id] + x] [v_pos_mon [obserwator_id] + y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
         }
		}
   }
	else
   {
  		for (y = 1; y < y_wzg; y ++)
     	{
        	x = y * x_wzg / y_wzg;

			if (v_pos_mon [obserwator_id] >= y_pos)
         {
	         if (h_pos_mon [obserwator_id] >= x_pos)
            {
            	if (plansza [h_pos_mon [obserwator_id] - x] [v_pos_mon [obserwator_id] - y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
     		   else
            {
            	if (plansza [h_pos_mon [obserwator_id] + x] [v_pos_mon [obserwator_id] - y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
         }
  	      else
     	   {
	         if (h_pos_mon [obserwator_id] >= x_pos)
            {
            	if (plansza [h_pos_mon [obserwator_id] - x] [v_pos_mon [obserwator_id] + y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
  	   	   else
            {
            	if (plansza [h_pos_mon [obserwator_id] + x] [v_pos_mon [obserwator_id] + y] > 8192)
               	return 0;	// cel ataku za przeszkoda (niewidoczny)
            }
         }
  	   }
	}

   return 1;
}

char check_own_visibility (int x_pos, int y_pos)
{
	if (!view_matrix (X_MAX + x_pos - h_pos, Y_MAX + y_pos - v_pos))
   	return 0;
   else
     	return 2;

   // return 1 dla niewidzialnego potwora/mimica itp.
}

void teleport (int kod_p, int x_pos, int y_pos)
{
	if (kod_p == -1)
   {
      if (mem_planszy [h_pos] [v_pos])
		  	put_char (mem_planszy [h_pos] [v_pos], h_pos, v_pos);

      monsters_planszy [h_pos] [v_pos] = -15;
      monsters_planszy [x_pos] [y_pos] = -1;
      h_pos = x_pos;
      v_pos = y_pos;

      rysuj_view_range ();
      verify_visible_monsters ();
   }
   else		// monster
   {
   	if (check_own_visibility (x_pos, y_pos))
		  	put_char (mem_planszy [h_pos_mon [kod_p]] [v_pos_mon [kod_p]], h_pos_mon [kod_p], v_pos_mon [kod_p]);

      monsters_planszy [h_pos_mon [kod_p]] [v_pos_mon [kod_p]] = -15;
      monsters_planszy [x_pos] [y_pos] = kod_p;
      h_pos_mon [kod_p] = x_pos;
      v_pos_mon [kod_p] = y_pos;
   }
}

void change_position (char ruch)
{
	int i;

	if (check_own_visibility (h_pos, v_pos))
	   put_char (plansza [h_pos] [v_pos], h_pos, v_pos);

   monsters_planszy [h_pos] [v_pos] = -15;
   check_visible_monsters ();
   move_visible_monsters ();

	if (ruch == '4' || ruch == 4)
		h_pos --;
	else if (ruch == '6' || ruch == 5)
		h_pos ++;
	else if (ruch == '8' || ruch == 3 || ruch == 83)
		v_pos --;
	else if (ruch == '2' || ruch == 2 || ruch == 82)
		v_pos ++;
	else if (ruch == '7')
   {
		h_pos --;
      v_pos --;
   }
	else if (ruch == '9')
   {
		h_pos ++;
      v_pos --;
   }
	else if (ruch == '3')
   {
     	h_pos ++;
		v_pos ++;
   }
	else if (ruch == '1')
   {
	  	h_pos --;
		v_pos ++;
	}

   if (h_pos > x_planszy - 30)
      h_pos_pl = 60 + h_pos - x_planszy;
   else if (h_pos < 30)
     	h_pos_pl = h_pos;
   else
     	h_pos_pl = 30;

   if (v_pos > y_planszy - 10)
      v_pos_pl = 20 + v_pos - y_planszy;
   else if (v_pos < 10)
     	v_pos_pl = v_pos;
   else
     	v_pos_pl = 10;

   monsters_planszy [h_pos] [v_pos] = -1;

	if (check_own_visibility (h_pos, v_pos))
	   put_char (player, h_pos, v_pos);

   if (floor_planszy [h_pos] [v_pos] > 4)
		action_floor (floor_planszy [h_pos] [v_pos], h_pos, v_pos);
}

void check_visible_monsters ()
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
}

void move_visible_monsters ()
{
	int a, i = 0, x_pos, y_pos;

	while ((a = visible_monsters [i]) != -15)		// usuwa widziane potwory
  	{
   	x_pos = h_pos_mon [a];
  	   y_pos = v_pos_mon [a];
     	put_char (mem_planszy [x_pos] [y_pos], x_pos, y_pos);
   	i ++;
   }
}

/*void change_monster_position (char ruch, int kod_p)
{
	int x_pos = h_pos_mon [kod_p], y_pos = v_pos_mon [kod_p];

	if (check_own_visibility (x_pos, y_pos) && cl_id != 1999)
   	put_char (plansza [x_pos] [y_pos], x_pos, y_pos);

	monsters_planszy [x_pos] [y_pos] = -15;

	if (ruch == 4)
		h_pos_mon [kod_p] --;
	else if (ruch == 6)
		h_pos_mon [kod_p] ++;
	else if (ruch == 8)
		v_pos_mon [kod_p] --;
	else if (ruch == 2)
		v_pos_mon [kod_p] ++;
	else if (ruch == 7)
   {
		h_pos_mon [kod_p] --;
      v_pos_mon [kod_p] --;
   }
	else if (ruch == 9)
   {
		h_pos_mon [kod_p] ++;
      v_pos_mon [kod_p] --;
   }
	else if (ruch == 3)
   {
     	h_pos_mon [kod_p] ++;
		v_pos_mon [kod_p] ++;
   }
	else if (ruch == 1)
   {
	  	h_pos_mon [kod_p] --;
		v_pos_mon [kod_p] ++;
	}

	if (check_own_visibility (h_pos_mon [kod_p], v_pos_mon [kod_p]) && cl_id != 1999)
		put_char (monster [kod_p], h_pos_mon [kod_p], v_pos_mon [kod_p]);

	monsters_planszy [h_pos_mon [kod_p]] [v_pos_mon [kod_p]] = kod_p;
}*/

void ustaw_gracza ()
{
	if (h_pos > x_planszy - 30)
      h_pos_pl = 60 + h_pos - x_planszy;
   else if (h_pos < 30)
     	h_pos_pl = h_pos;
   else
     	h_pos_pl = 30;

   if (v_pos > y_planszy - 10)
      v_pos_pl = 20 + v_pos - y_planszy;
   else if (v_pos < 10)
     	v_pos_pl = v_pos;
   else
     	v_pos_pl = 10;
}

void ustaw_kursor ()
{
   if (h_cur > x_planszy - 30)
  	   h_pos_pl = 60 + h_cur - x_planszy;
   else if (h_cur < 30)
  	  	h_pos_pl = h_cur;
   else
  	  	h_pos_pl = 30;

   if (v_cur > y_planszy - 10)
  	   v_pos_pl = 20 + v_cur - y_planszy;
   else if (v_cur < 10)
  	  	v_pos_pl = v_cur;
   else
  	  	v_pos_pl = 10;
}

void hexy (char konwersja, int liczba)
{
	unsigned char znak;

	if (konwersja == 2)
   {
		znak1 = liczba / 220 + 32;
		znak2 = liczba % 220 + 32;
	}
   else if (konwersja == 3)
   {
		znak1 = liczba / 64 + 60;
		znak2 = liczba % 64 + 60;
   }

   if (!plik)
   {
   	putc (znak1, temp00);
   	putc (znak2, temp00);
   }
   else if (plik == 1)
   {
   	putc (znak1, temp01);
   	putc (znak2, temp01);
   }
}

void hexy_save (int liczba)
{
	hexy (2, liczba + 1000);
}

int hexy_load ()
{
	int c, liczba;

	c = getc (temp00);
	znak1 = c - 32;
	znak2 = getc (temp00) - 32;
   liczba = znak1 * 220 + znak2 - 1000;

   return (liczba);
}

/*long int decimal (char binary_code [])
{
	long int decimal_value = 0;
   int bin_lenght = 0, power = 1, bin_length = 0;

   while (binary_code [bin_length] != '\0')
   	bin_length ++;

	while (bin_length >= 0)
   {
	   decimal_value += binary_code [bin_length] * power;
   	bin_length --;
   	power *= 2;
   }

	return decimal_value;
}*/

void kopia (char *t, char *s)
{
	int i = 0;

	while (s [i] != 0)
	{
		t [i] = s [i];
		i ++;
	}

	t [i] = 0;
}

void add_kopia (char *t, char *s)
{
	int i = 0, j = 0;

	while (t [i] != 0)
		i ++;

	while (s [j] != 0)
	{
		t [i] = s [j];
		i ++;
		j ++;
	}

	t [i] = 0;
}

void kopia_tablicy (char *t, char *s, int _length)
{
	int i = 0;

	while (_length && s [i] != 0)
	{
		t [i] = s [i];
      _length --;
      i ++;
	}
}

char answer ()
{
	while (1)
	{
		klawisz ();

		if (key == 'y')
			return 1;

		if (key == 'n' || key == _ESC)
			return 0;
	}
}

void clear_area (char startX, char startY, char koniecX, char koniecY)
{
	int dlugX = koniecX - startX + 1;
	int dlugY = koniecY - startY + 1;
   int x, y;

   gotoxy (startX, startY);

   for (y = 0; y < dlugY; y ++)
   {
      gotoxy (startX, startY + y);

   	for (x = 0; x < dlugX; x ++)
      	addch (32);
   }
}

char create_window (char text_0 [], char ch_1, char text_1 [], char ch_2, char text_2 [],
	 char ch_3, char text_3 [], char ch_4, char text_4 [], char ch_5, char text_5 [],
    char ch_6, char text_6 [], char ch_7, char text_7 [], char size_x, char size_y)
{
	int start_x, start_y, x, y;
   char msge, txt [16], y_txt = 1, key_choice = -1;
	char texts [8] [100];

   for (x = 0; x < 16; x ++)
   	txt [x] = 0;

   while ((texts [0] [txt [8]] = text_0 [txt [8] ++]) != '\0');
   while ((texts [1] [txt [9]] = text_1 [txt [9] ++]) != '\0');
   while ((texts [2] [txt [10]] = text_2 [txt [10] ++]) != '\0');
   while ((texts [3] [txt [11]] = text_3 [txt [11] ++]) != '\0');
   while ((texts [4] [txt [12]] = text_4 [txt [12] ++]) != '\0');
   while ((texts [5] [txt [13]] = text_5 [txt [13] ++]) != '\0');
   while ((texts [6] [txt [14]] = text_6 [txt [14] ++]) != '\0');
   while ((texts [7] [txt [15]] = text_7 [txt [15] ++]) != '\0');

   for (x = 8; x < 16; x ++)
   	txt [x] = 0;

	if (v_pos < y_planszy / 2)
	   start_y = 9;
   else
   	start_y = 0;

   start_x = (x_planszy - size_x) / 2;
   textcolor (COLOR_DARK_GRAY);

   for (y = 1; y <= size_y; y ++)
   {
   	gotoxy (start_x + LB, start_y + y + UB - 1);

   	for (x = 1; x <= size_x; x ++)
      {
      	if (y == 1 && x == 1)
         	addch (201);
      	else if (y == size_y && x == 1)
         	addch (200);
      	else if (y == 1 && x == size_x)
         	addch (187);
      	else if (y == size_y && x == size_x)
         	addch (188);
			else if (x > 1 && x < size_x && (y == 1 || y == size_y))
				addch (205);
         else if (y > 1 && y < size_y && (x == 1 || x == size_x))
         	addch (186);
			else if (x > 1 && x < size_x && y > 1 && y < size_y)
         	addch (32);
      }
   }

	for (x = 0; x < 8; x ++)
	{
	   while ((msge = texts [x] [++ txt [x + 8]]) != '\0')
  		{
      	txt [x] ++;
			gotoxy (start_x + LB + txt [x], start_y + UB + y_txt);

   	   if (msge == '|')
      	{
	      	txt [x] = 0;
				y_txt ++;
      	}
	      else
		      addch (msge);
	   }

      if (!txt [x])
      	break;

   	y_txt ++;
   }

  	while (1)
   {
     	klawisz ();

		if (key == ch_1 || key == ch_2 || key == ch_2 || key == ch_3 || key == ch_4 || key == ch_5 || key == ch_6 || key == ch_7 || key == 27)
        	break;
	}

	for (y = start_y; y < start_y + size_y; y ++)
	{
		for (x = start_x; x < start_x + size_x; x ++)
		{
			gotoxy (x + LB, y + UB);

			if (mem_planszy [x] [y])
			{
				textcolor (mem_planszy [x] [y] / 256);
				addch (mem_planszy [x] [y]);
			}
         else
				addch (32);
		}
	}

	put_monsters ();
	return key;
}

void klawisz ()
{
	key = getch ();
}

void wait (int msec)
{
/*	double duration = 0, start, finish;
	start = clock ();

	while (duration < msec)
	{
		finish = clock ();
		duration = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
	}*/
//   _sleep (1);
   refresh ();
   napms (msec);
}

void debug_info ()
{
	int i, j = 0;

/*   printw ("\n\r left_poison [0] = %d, char_state [1] = %d", left_poison_turns [0], character_state [1]);
	printw ("\n\r view_range = %d, temp = %d, items_amount = %d", view_range, temp, items_amount);
   printw ("\n\r satiation = %d, character_state [0] = %d, items_amount = %d", satiation, character_state [0], items_amount);
   printw ("\n\r litera = %d", litera);
   printw ("\n\r h_pos = %d, v_pos = %d", h_pos, v_pos);
   printw ("\n\r cl_id = %d", cl_id);
   printw ("\n\r %d", elapsed_time);*/

/*  for (i = 0; i < items_amount; i ++)
  		if (1)
   	printf ("\n\r i: %d, %d, %d,%d,%d,%d,%d,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ",
       i, h_pos_item [i], v_pos_item [i], item [i], item_icon [i], item_group [i],
       item_type [i], item_dv [i], item_hit [i], item_dices [i], item_dmg_bonus [i],
       item_state [i], item_status [i], item_ident [i], item_amount [i], item_specials1 [i],
       item_specials2 [i], item_weight [i], item_value_material [i], item_owner [i]);

//	printf ("\r\n items_amount %d, item_id %d", items_amount, item_id);

/*   for (i = 0; i < items_amount; i ++)
   	if (unpaid_items [i])
         j ++;

	printf ("\r\n unpaid items_amount %d", j);

   for (i = 0; i < items_amount; i ++)
   	if (working_items [i])
         j ++;

	printf ("\r\n working items_amount %d", j);*/

/*   while ((i = visible_monsters [j ++]) != -15);
  */

   i = search_stairs (50, 1, 1);

	printf ("\n\rPotwory:");
	for (i = 0; i < monsters_amount; i ++)
		printf ("\n\r %d %d %d %d %d %d %d %d %d %d", i, monster [i], h_pos_mon [i], v_pos_mon [i], monster_hp [i], monster_left_poison [i] [0], monster_body [i] [0], monster_backpack [i] [0], monster_aim [i], monster_alignment [i]);

/*   printf ("\n\r");

/*   for (i = 0; i < X_MAX_PL; i ++)
   	for (j = 0; j < Y_MAX_PL; j ++)
      	if (monsters_planszy [i] [j] >= -1)
         	printf ("X: %d Y: %d mon_id: %d, ", i, j, monsters_planszy [i] [j]);*/

   printf ("\n\r h_pos = %d, v_pos = %d, schody_id = %d, schody_h = %d, schody_v = %d", h_pos, v_pos, i, h_pos_item [i], v_pos_item [i]);
   printf ("\n\r items_amount = %d monsters_amount = %d h_pos_pl = %d, v_pos_pl = %d", items_amount, monsters_amount, h_pos_pl, v_pos_pl);
   printf ("\n\r x-planszy %d y-planszy %d", x_planszy, y_planszy);
   printf ("\n\r cl_id %d", cl_id);

   do klawisz ();
   while (key != 27);
}

void debug (int info1, int info2, int time1, int y_pos)
{
	gotoxy (62, y_pos);
   printf ("%d  %d  ", info1, info2);

	if (time1 >= 0)
	   wait (time1);
   else
   	klawisz ();
}
