#include "deklaracje.h"

void change_location (char key_)
{
	char exit_lev = 0;
   int schody_id;
   int q, r, s, kod_p;
   int kod_floor = floor_planszy [h_pos] [v_pos];

	// na laptopa zamiana
   if (key_ == 4)
   	key_ = '4';
   else if (key_ == 5)
   	key_ = '6';
   else if (key_ == 3 || key_ == 83)
   	key_ = '8';
   else if (key_ == 2 || key_ == 82)
   	key_ = '2';

	if (cl_id != _WORLD)
	{
		switch (cl_id)
		{
         case _Test:
				if (key_ >= '1' && key_ <= '9')
					exit_lev = exit_location (key_);
            else if (key_ == 10 || key_ == 20)		// 10 = '>', 20 = '<'
            	exit_lev = 1;
				break;
			case _New_York_City:
			case _New_York_City_Warzone:
         case _Graveyard:
         case _Downtown:
         case _Downtown_Mayhem:
         case _Old_Remo:
         case _Mines:
         case _Marina_Harbour:
         case _CLASS_Corp:
         case _Shelter_Tec:
         case _Puerto_Zombico:
         case _Atlantic_Accelerator:
				if (key_ >= '1' && key_ <= '9')
					msg ("<Find a proper exit.");
				else if (key_ == 10 || key_ == 20)
					exit_lev = 1;
				break;
         default:
        		if (cl_id < 1200)
            {
            	if (key_ == 20)		// '<'
               {
	            	if (!exit_ability)
							exit_lev = exit_location (key_);
      	         else
         	      	msg ("<From this area you should exit manuanly.");
               }
               else			// brzeg planszy
               	exit_lev = exit_location (key_);
            }
            break;
		}
	}
	else
	{
		exit_lev = 1;
		h_pos_world = h_pos;
		v_pos_world = v_pos;

		if (key_ == '4')
			h_pos_world --;
		else if (key_ == '6')
			h_pos_world ++;
		else if (key_ == '8')
			v_pos_world --;
		else if (key_ == '2')
			v_pos_world ++;
		else if (key_ == '7')
   	{
			h_pos_world --;
   	   v_pos_world --;
	   }
		else if (key_ == '9')
	   {
			h_pos_world ++;
	      v_pos_world --;
   	}
		else if (key_ == '3')
   	{
     		h_pos_world ++;
			v_pos_world ++;
   	}
		else if (key_ == '1')
   	{
	  		h_pos_world --;
			v_pos_world ++;
		}
	}

	if (exit_lev)
	{
		zapisz_temp ();

		if (cl_id == _WORLD)
      	count_target_location ();
		else
		{
			if (cl_id >= 0 && cl_id <= 1199)		// lokacja na mapie generowana losowo
         {
            if (key_ == 20)		// = '<'
					tl_id = _WORLD;
        	   else						// brzeg planszy
     	      {
            	if (exit_ability)
               {
						if (h_pos == 1 && v_pos >= 6 && v_pos <= 13)
							h_pos_world --;
   		         else if (h_pos == 58 && v_pos >= 6 && v_pos <= 13)
         	      	h_pos_world ++;
						else if (v_pos == 1 && h_pos >= 10 && h_pos <= 49)
							v_pos_world --;
						else if (v_pos == 18 && h_pos >= 10 && h_pos <= 49)
							v_pos_world ++;
						else if (h_pos == 1 && v_pos >= 1 && v_pos <= 5 || v_pos == 1 && h_pos >= 1 && h_pos <= 9)
 	   	   	   {
							h_pos_world --;
					      v_pos_world --;
				      }
						else if (h_pos == 58 && v_pos >= 1 && v_pos <= 5 || v_pos == 1 && h_pos >= 50 && h_pos <= 58)
					   {
							h_pos_world ++;
					      v_pos_world --;
					   }
						else if (h_pos == 58 && v_pos >= 14 && v_pos <= 18 || v_pos == 18 && h_pos >= 50 && h_pos <= 58)
					   {
					     	h_pos_world ++;
							v_pos_world ++;
					   }
						else if (h_pos == 1 && v_pos >= 14 && v_pos <= 18 || v_pos == 18 && h_pos >= 1 && h_pos <= 9)
				   	{
						  	h_pos_world --;
							v_pos_world ++;
						}

	               tl_id = _WORLD;
   	            odczytaj_temp ();
      	         check_map_secret ();
						oblicz_stats ();
            	   make_view_matrix ();
               	zapisz_temp ();
	               count_target_location ();
               }
               else
               	tl_id = _WORLD;
            }
         }
			else
         {
         	if (key_ == 10 || key_ == 20)
            {
					schody_id = obstacles_planszy [h_pos] [v_pos];
					tl_id = item_specials2 [schody_id];
            }
            else		// brzeg planszy
            	tl_id = _WORLD;
         }
		}

		odczytaj_temp ();

		if (visited_locations [tl_id] && tl_id > 1199)	// gdy plansza do ktorej wchodzi gracz byla wczesniej odwiedzana
   	{
			clrscr ();

			if (tl_id == _WORLD)
			{
				h_pos = h_pos_world;
  	         v_pos = v_pos_world;
				check_map_secret ();
			}
			else
			{
				if (cl_id == _WORLD)
            {
              	h_pos = 29;
               v_pos = 1;

               schody_id = search_stairs (50, -1, -1);

               if (tl_id == _Atlantic_Accelerator)
               	schody_id = search_obstacle (61, 16);

               if (schody_id >= 0)
               {
        		      h_pos = h_pos_item [schody_id];
         	      v_pos = v_pos_item [schody_id];
               }
				}
				else if (key_ == 10 || key_ == 20)
            {
					schody_id = search_stairs (50, -1, cl_id);
     		      h_pos = h_pos_item [schody_id];
        	      v_pos = v_pos_item [schody_id];
            }
            else if (key_ >= '1' && key_ <= '9')
            {
					if (h_pos == 1 && v_pos >= 6 && v_pos <= 13)
   	         {
						h_pos = 58;
  		   	      v_pos = 9;
	            }
               else if (h_pos == 58 && v_pos >= 6 && v_pos <= 13)
   	         {
						h_pos = 1;
  		   	      v_pos = 9;
	            }
					else if (v_pos == 1 && h_pos >= 10 && h_pos <= 49)
	            {
  	      			h_pos = 29;
						v_pos = 18;
      	      }
					else if (v_pos == 18 && h_pos >= 10 && h_pos <= 49)
	            {
  			      	h_pos = 29;
						v_pos = 1;
	   	   	}
					else if (h_pos == 1 && v_pos >= 1 && v_pos <= 5 || v_pos == 1 && h_pos >= 1 && h_pos <= 9)
   	         {
						h_pos = 58;
				      v_pos = 18;
			      }
					else if (h_pos == 58 && v_pos >= 1 && v_pos <= 5 || v_pos == 1 && h_pos >= 50 && h_pos <= 58)
				   {
						h_pos = 1;
			      	v_pos = 18;
				   }
					else if (h_pos == 58 && v_pos >= 14 && v_pos <= 19 || v_pos == 18 && h_pos >= 50 && h_pos <= 58)
				   {
			   	  	h_pos = 1;
						v_pos = 1;
				   }
					else if (h_pos == 1 && v_pos >= 14 && v_pos <= 18 || v_pos == 18 && h_pos >= 1 && h_pos <= 9)
			   	{
					  	h_pos = 58;
						v_pos = 1;
					}
	         }
			}
		}
		else		// wchodzi w nieodwiedzane wczesniej miejsce	lub wilderness
		{
			monsters_amount = 0;

		  	for (q = 0; q < X_MAX_PL; q ++)
				for (r = 0; r < Y_MAX_PL; r ++)
					monsters_planszy [q] [r] = -15;

        	if (tl_id == _WORLD)
         	generuj_world_map ();
        	else if (tl_id == _New_York_City)
         	generuj_New_York_City ();
        	else if (tl_id == _New_York_City_Warzone)
         	generuj_New_York_City_Warzone ();
         else if (tl_id == _Downtown)
         	generuj_Downtown ();
         else if (tl_id == _Downtown_Mayhem)
         	generuj_Downtown_Mayhem ();
         else if (tl_id == _Old_Remo)
         	generuj_Old_Remo ();
         else if (tl_id == _Test)
         	generuj_Test ();
         else if (tl_id == _Mines)
         	generuj_Mines ();
         else if (tl_id == _CLASS_Corp)
         	generuj_CLASS_Corp ();
         else if (tl_id == _Shelter_Tec)
           	generuj_Shelter_Tec ();
         else if (tl_id == _Puerto_Zombico)
           	generuj_Puerto_Zombico ();
         else if (tl_id == _Graveyard)
           	generuj_Graveyard ();
         else if (tl_id == _Marina_Harbour)
           	generuj_Marina_Harbour ();
         else if (tl_id == _Atlantic_Accelerator)
           	generuj_Atlantic_Accelerator ();
			else	// wilderness
			{
         	if (cl_id <= 1299)	// gdy wchodzimy z innej lokacji na powierzchni lub wilderness
            {
					if (h_pos == 1 && v_pos >= 6 && v_pos <= 13)
						h_pos = 45;
   	         else if (h_pos == 58 && v_pos >= 6 && v_pos <= 13)
						h_pos = 15;
					else if (v_pos == 1 && h_pos >= 10 && h_pos <= 49)
						v_pos = 9;
					else if (v_pos == 18 && h_pos >= 10 && h_pos <= 49)
						v_pos = 9;
					else if (h_pos == 1 && v_pos >= 1 && v_pos <= 5 || v_pos == 1 && h_pos >= 1 && h_pos <= 9)
 	   	      {
						h_pos = 45;
			   	   v_pos = 9;
			      }
					else if (h_pos == 58 && v_pos >= 1 && v_pos <= 5 || v_pos == 1 && h_pos >= 50 && h_pos <= 58)
				   {
						h_pos = 15;
		      		v_pos = 9;
				   }
					else if (h_pos == 58 && v_pos >= 14 && v_pos <= 18 || v_pos ==  18 && h_pos >= 50 && h_pos <= 58)
				   {
		   		  	h_pos = 15;
						v_pos = 9;
				   }
					else if (h_pos == 1 && v_pos >= 14 && v_pos <= 18 || v_pos == 18 && h_pos >= 1 && h_pos <= 9)
			   	{
					  	h_pos = 45;
						v_pos = 9;
					}
            }
            else		// gdzie ustawia gracza gdy wchodzimy "z wymuszenia" (np. gdy przekraczamy rzeke po zapytaniu)
            {
            	h_pos = x_planszy / 2;
               v_pos = y_planszy / 2;

					if (key_ == '4')
  		         {
						h_pos = 58;
	   		      v_pos = 9;
	            }
   	         else if (key_ == '6')
	   	      {
						h_pos = 1;
	   	   	   v_pos = 9;
	            }
					else if (key_ == '8')
      	      {
      				h_pos = 29;
						v_pos = 18;
	     	      }
					else if (key_ == '2')
      	      {
		   	   	h_pos = 29;
						v_pos = 1;
	   	   	}
					else if (key_ == '7')
 	   	      {
						h_pos = 58;
			   	   v_pos = 18;
			      }
					else if (key_ == '9')
				   {
						h_pos = 1;
		      		v_pos = 18;
				   }
					else if (key_ == '3')
				   {
		   		  	h_pos = 1;
						v_pos = 1;
				   }
					else if (key_ == '1')
			   	{
					  	h_pos = 58;
						v_pos = 1;
					}
            }

           	generuj_plansze_wilderness (floor_planszy [h_pos_world - 1] [v_pos_world - 1], floor_planszy [h_pos_world] [v_pos_world - 1], floor_planszy [h_pos_world + 1] [v_pos_world - 1],
            									floor_planszy [h_pos_world - 1] [v_pos_world], floor_planszy [h_pos_world] [v_pos_world], floor_planszy [h_pos_world + 1] [v_pos_world],
                                       floor_planszy [h_pos_world - 1] [v_pos_world + 1], floor_planszy [h_pos_world] [v_pos_world + 1], floor_planszy [h_pos_world + 1] [v_pos_world + 1]);

				if (key_ == 31)
					generuj_potwory (losuj (4, 12), _BANDIT, -1, -1, -1);
            else if (key_ == 32)
            	generuj_potwory (losuj (5, 10), _WILD_DOG, -1, -1, -1);
            else if (key_ == 33)
            	generuj_potwory (losuj (3, 7), _JACKAL, -1, -1, -1);
			}

			for (q = 0; q < y_planszy; q ++)
				for (r = 0; r < x_planszy; r ++)
					mem_planszy [r] [q] = 32;
		}

      switch (cl_id)
      {
         case _WORLD:
         	if (tl_id == _Marina_Harbour && (kod_p = search_obstacle (61, 6)) >= 0 && quest [8] == -10)
            {
				   item_specials2 [kod_p] = _WORLD;			// kod lokacji docelowej
				   item_type [kod_p] = 16;			
               item_icon [kod_p] = 62 + kolor_wall;
            }
            break;
      	case _Marina_Harbour:
            if (key_ == 10 && tl_id == _WORLD)
            {
					h_pos = h_pos_world = 4;
               v_pos = v_pos_world = 7;
            }
            break;
      	case _Atlantic_Accelerator:
            if (key_ == 10 && tl_id == _WORLD)
            {
					h_pos = h_pos_world = 44;
               v_pos = v_pos_world = 13;
            }
            break;
      }

		cl_id = tl_id;
		statystyki (0);
      visible_monsters [0] = -15;

		for (q = 0; q < x_planszy; q ++)
      	for (r = 0; r < y_planszy; r ++)
         {
				stan_planszy [q] [r] = 0;
            items_planszy [q] [r] = -1;
            monsters_planszy [q] [r] = -15;
            obstacles_planszy [q] [r] = -1;

            for (s = 0; s < 15; s ++)
               coverers_planszy [q] [r] [s] = 0;

				if (visited_locations [cl_id])
      	   	convert_floor (q, r);
         }

		for (item_id = 0; item_id < items_amount; item_id ++)
      	put_item (item_id);

      for (monster_id = 0; monster_id < monsters_amount; monster_id ++)
      {
      	monsters_planszy [h_pos_mon [monster_id]] [v_pos_mon [monster_id]] = monster_id;

			if (visited_locations [tl_id] && monster_code [monster_id] != _Helc)
	         monster_hp [monster_id] = monster_health [monster_id];
      }

      monsters_planszy [h_pos] [v_pos] = -1;
		ustaw_gracza ();
		rysuj_ekran ();

		if (!visited_locations [cl_id])
      {
      	switch (cl_id)
         {
				case _Puerto_Zombico:
		   	  	area_description (_Puerto_Zombico);
               quest [13] = 1;
               break;
				case _Atlantic_Accelerator:
		   	  	area_description (_Atlantic_Accelerator);
               quest [14] = 1;
               break;
				case _Downtown:
		   	  	area_description (_Downtown);
               break;
				case _Downtown_Mayhem:
		   	  	area_description (_Downtown_Mayhem);
               break;
         }
      }

		if (kod_floor >= 180 && kod_floor < 200)
         count_achievement (7, kod_floor - 179, 7);

		if (!visited_locations [tl_id])
			visited_locations [tl_id] = 1;
		else if (tl_id != _WORLD)
	      turn ();
	}
}

void check_map_secret ()
{
	if (map_secret [0] == 1)
		floor_planszy [9] [7] = 184;

	if (map_secret [1] == 1)
		floor_planszy [44] [5] = 188;
}

void count_target_location ()
{
	int kod_floor = floor_planszy [h_pos_world] [v_pos_world];

   tl_id = h_pos_world + v_pos_world * x_planszy;

	if (kod_floor == 180)
		tl_id = _New_York_City;
	else if (kod_floor == 181)
		tl_id = _Graveyard;
	else if (kod_floor == 182)
		tl_id = _Old_Remo;
	else if (kod_floor == 183)
		tl_id = _Marina_Harbour;
	else if (kod_floor == 184)
		tl_id = _CLASS_Corp;
	else if (kod_floor == 185)
		tl_id = _Shelter_Tec;
	else if (kod_floor == 186)
		tl_id = _Puerto_Zombico;
	else if (kod_floor == 187)
		tl_id = _Atlantic_Accelerator;
	else if (kod_floor == 188)
		tl_id = _Downtown_Mayhem;
	else if (kod_floor == 200)
		tl_id = _Test;
}

void zapisz_temp ()
{
	char nazwa_pliku [12] = {"tmp_"};
	char nr_znaku = 0;
   int x, i, j, k, m, n, q, r, s, t;

	plik = -1;
	hexy (3, cl_id);
	nazwa_pliku [4] = znak1; nazwa_pliku [5] = znak2;
	plik = 0;
	temp00 = fopen ("tmp_inv.txt", "w");	// tymczasowy plik z danymi przedmiotow niesionymi przez postac

	for (x = 1; x <= 19; x ++)	// zapisuje nowe index'y zalozonych przedmiotow
	{
		if (item_body [x])
		{
			for (item_id = 0; item_id < items_amount; item_id ++)
			{
				if (item [item_id] == 1 || item [item_id] == 4)
					nr_znaku ++;

				if (item_body [x] == item_id)
					item_body [x] = nr_znaku - 1;
			}

			nr_znaku = 0;
		}

		hexy (2, item_body [x] + 128);
	}

	putc (255, temp00);

	for (item_id = 0; item_id < items_amount; item_id ++)
	{
		if (item [item_id] == 1 || item [item_id] == 4)
		{
			hexy (2, item [item_id] + 64);
			hexy (2, item_icon [item_id] + 128);
			hexy (2, item_type [item_id] + 128);
			hexy (2, item_group [item_id] + 40);
			hexy (2, item_dv [item_id] + 80);
			hexy (2, item_dices [item_id] + 128);
			hexy (2, item_dmg_bonus [item_id] + 80);
			hexy (2, item_status [item_id] + 64);
			hexy (2, item_specials1 [item_id] + 128);
			hexy (2, item_specials2 [item_id] + 128);
			hexy (2, item_weight [item_id] + 128);
			hexy (2, item_value_material [item_id] + 128);
			hexy (2, item_amount [item_id] + 128);
			hexy (2, item_owner [item_id] + 128);
			hexy (2, item_state [item_id] + 64);
			hexy (2, item_ident [item_id] + 64);
			hexy (2, item_hit [item_id] + 80);
		}
	}

	putc (255, temp00);	// znacznik
	fclose (temp00);
   plik = 1;

	if (cl_id >= 1200)
	{
		temp01 = fopen (nazwa_pliku, "w");	// tymczasowy plik z info o planszy z ktorej postac wychodzi

		hexy (2, x_planszy);
		hexy (2, y_planszy);

		for (item_id = 0; item_id < items_amount; item_id ++)
		{
			if (item [item_id] != 1 && item [item_id] != 4)
			{
				hexy (2, item [item_id] + 64);
				hexy (2, item_icon [item_id] + 128);
				hexy (2, item_type [item_id] + 128);
				hexy (2, item_group [item_id] + 40);
				hexy (2, item_dv [item_id] + 80);
				hexy (2, item_dices [item_id] + 128);
				hexy (2, item_dmg_bonus [item_id] + 80);
				hexy (2, item_status [item_id] + 64);
				hexy (2, item_specials1 [item_id] + 128);
				hexy (2, item_specials2 [item_id] + 128);
				hexy (2, item_weight [item_id] + 128);
				hexy (2, item_value_material [item_id] + 128);
				hexy (2, item_amount [item_id] + 128);
				hexy (2, item_owner [item_id] + 128);
				hexy (2, h_pos_item [item_id] + 40);
				hexy (2, v_pos_item [item_id] + 40);
				hexy (2, item_state [item_id] + 64);
				hexy (2, item_ident [item_id] + 64);
				hexy (2, item_hit [item_id] + 80);
			}
		}

		putc (255, temp01);	// znacznik

		for (monster_id = 0; monster_id < monsters_amount; monster_id ++)
      {
			hexy (2, monster [monster_id] + 128);
        	hexy (2, monster_code [monster_id] + 128);
			hexy (2, monster_speed [monster_id] + 128);
			hexy (2, monster_health [monster_id] + 128);
			hexy (2, monster_damage [monster_id] + 128);
			hexy (2, monster_hit [monster_id] + 128);
			hexy (2, monster_exp [monster_id] + 128);
			hexy (2, monster_aim [monster_id] + 128);
			hexy (2, monster_pp [monster_id] + 128);
			hexy (2, monster_hp [monster_id] + 128);

        	for (m = 0; m < 30; m ++)
				hexy (2, monster_state [monster_id] [m] + 64);

        	for (m = 0; m < 15; m ++)
				hexy (2, monster_body [monster_id] [m] + 128);

        	for (m = 0; m < 15; m ++)
				hexy (2, monster_backpack [monster_id] [m] + 128);

        	for (m = 0; m < 7; m ++)
				hexy (2, monster_left_poison [monster_id] [m] + 128);

			hexy (2, h_pos_mon [monster_id] + 64);
			hexy (2, v_pos_mon [monster_id] + 64);
			hexy (2, monster_char [monster_id] + 64);
         hexy (2, monster_alignment [monster_id] + 64);
		}

		putc (255, temp01);

		for (q = 0; q < y_planszy; q ++)
			for (r = 0; r < x_planszy; r ++)
				hexy (2, mem_planszy [r] [q] + 128);

		for (s = 0; s < y_planszy; s ++)
			for (t = 0; t < x_planszy; t ++)
				hexy (2, floor_planszy [t] [s] + 16);

		fclose (temp01);
   }
}

void odczytaj_temp ()
{
	char nazwa_pliku [12] = {"tmp_"};
   int a, b, c = 0, d, m, n, q, r, s, t;

	item_id = 1;
	temp02 = fopen ("tmp_inv.txt", "r");

	while (c != 255)
	{
		c = getc (temp02);

		if (c == 255 || c == EOF)
			break;

		znak1 = c - 32;
		znak2 = getc (temp02) - 32;
		item_body [item_id] = znak1 * 220 + znak2 - 128;
		item_id ++;
	}

	a = 0;
   item_id = 0;

	while (c != EOF)
	{
   	a ++;
		c = getc (temp02);

		if (c == 255 || c == EOF)
			break;

		znak1 = c - 32;
		znak2 = getc (temp02) - 32;

		switch (a)
		{
			case 1:
				item [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 2:
				item_icon [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 3:
				item_type [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 4:
				item_group [item_id] = znak1 * 220 + znak2 - 40;
				break;
			case 5:
				item_dv [item_id] = znak1 * 220 + znak2 - 80;
				break;
			case 6:
				item_dices [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 7:
				item_dmg_bonus [item_id] = znak1 * 220 + znak2 - 80;
				break;
			case 8:
				item_status [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 9:
				item_specials1 [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 10:
				item_specials2 [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 11:
				item_weight [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 12:
				item_value_material [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 13:
				item_amount [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 14:
				item_owner [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 15:
				item_state [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 16:
				item_ident [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 17:
				item_hit [item_id] = znak1 * 220 + znak2 - 80;
            a = 0;
				break;
		}

      if (!a)
			item_id ++;
	}

	fclose (temp02);
//	remove ("tmp_inv.txt");			// usuwa tymczasowy plik noszonych przedmiotow
	items_amount = item_id;

	if (visited_locations [tl_id] && tl_id >= 1200)	// gdy plansza do ktorej wchodzi gracz byla wczesniej odwiedzana
	{
   	plik = -1;
		hexy (3, tl_id);
		nazwa_pliku [4] = znak1; nazwa_pliku [5] = znak2;
		temp03 = fopen (nazwa_pliku, "r");

		x_planszy = (getc (temp03) - 32) * 220 + getc (temp03) - 32;
		y_planszy = (getc (temp03) - 32) * 220 + getc (temp03) - 32;

		b = 0;
     	item_id = items_amount;

		while (1)
		{
      	b ++;
			c = getc (temp03);

			if (c == 255 || c == EOF)
				break;

			znak1 = c - 32;
			znak2 = getc (temp03) - 32;

			switch (b)
			{
				case 1:
					item [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 2:
					item_icon [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 3:
					item_type [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 4:
					item_group [item_id] = znak1 * 220 + znak2 - 40;
					break;
				case 5:
					item_dv [item_id] = znak1 * 220 + znak2 - 80;
					break;
				case 6:
					item_dices [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 7:
					item_dmg_bonus [item_id] = znak1 * 220 + znak2 - 80;
					break;
				case 8:
					item_status [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 9:
					item_specials1 [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 10:
					item_specials2 [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 11:
					item_weight [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 12:
					item_value_material [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 13:
					item_amount [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 14:
					item_owner [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 15:
					h_pos_item [item_id] = znak1 * 220 + znak2 - 40;
					break;
				case 16:
					v_pos_item [item_id] = znak1 * 220 + znak2 - 40;
					break;
				case 17:
					item_state [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 18:
					item_ident [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 19:
					item_hit [item_id] = znak1 * 220 + znak2 - 80;
               b = 0;
					break;
			}

			if (!b)
				item_id ++;
		}

      items_amount = item_id;

		d = 0;
		monster_id = 0;

		while (1)
		{
      	d ++;

			if (d < 11 || d > 14)
         {
				c = getc (temp03);

				if (c == 255 || c == EOF)
					break;

				znak1 = c - 32;
				znak2 = getc (temp03) - 32;
         }

			switch (d)
			{
				case 1:
					monster [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 2:
					monster_code [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 3:
					monster_speed [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 4:
					monster_health [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 5:
					monster_damage [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 6:
					monster_hit [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 7:
					monster_exp [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 8:
					monster_aim [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 9:
					monster_pp [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 10:
					monster_hp [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 11:
               for (m = 0; m < 30; m ++)
               {
						znak1 = getc (temp03) - 32;
						znak2 = getc (temp03) - 32;
						monster_state [monster_id] [m] = znak1 * 220 + znak2 - 64;
               }
					break;
				case 12:
               for (m = 0; m < 15; m ++)
               {
						znak1 = getc (temp03) - 32;
						znak2 = getc (temp03) - 32;
						monster_body [monster_id] [m] = znak1 * 220 + znak2 - 128;
               }
					break;
				case 13:
               for (m = 0; m < 15; m ++)
               {
						znak1 = getc (temp03) - 32;
						znak2 = getc (temp03) - 32;
						monster_backpack [monster_id] [m] = znak1 * 220 + znak2 - 128;
               }
					break;
				case 14:
               for (m = 0; m < 7; m ++)
               {
						znak1 = getc (temp03) - 32;
						znak2 = getc (temp03) - 32;
						monster_left_poison [monster_id] [m] = znak1 * 220 + znak2 - 128;
               }
					break;
				case 15:
					h_pos_mon [monster_id] = znak1 * 220 + znak2 - 64;
					break;
				case 16:
					v_pos_mon [monster_id] = znak1 * 220 + znak2 - 64;
					break;
				case 17:
					monster_char [monster_id] = znak1 * 220 + znak2 - 64;
					break;
				case 18:
					monster_alignment [monster_id] = znak1 * 220 + znak2 - 64;
               d = 0;
					break;
			}

			if (!d)
				monster_id ++;
		}

		monsters_amount = monster_id;

		for (q = 0; q < y_planszy; q ++)
		{
			for (r = 0; r < x_planszy; r ++)
			{
				c = getc (temp03);

				if (c == 255 || c == EOF)
					break;

				znak1 = c - 32;
				znak2 = getc (temp03) - 32;
				mem_planszy [r] [q] = znak1 * 220 + znak2 - 128;
			}
		}

		for (s = 0; s < y_planszy; s ++)
		{
			for (t = 0; t < x_planszy; t ++)
			{
				c = getc (temp03);

				if (c == 255 || c == EOF)
					break;

				znak1 = c - 32;
				znak2 = getc (temp03) - 32;
				floor_planszy [t] [s] = znak1 * 220 + znak2 - 16;
			}
		}
		fclose (temp03);
//		remove (nazwa_pliku);
	}

   for (a = 0; a < MAXITEMS; a ++)
   {
   	working_items [a] = 0;
      unpaid_items [a] = 0;
   }

   for (a = 0; a < items_amount; a ++)
   {
   	m = item_group [a];
  	   n = item_type [a];
      s = item_value_material [a] % 100;

		if (m == 19 && n < 1000 && item_specials1 [a] > 0)		// gnijace jedzenie
	   	working_items [a] = 1;
   	else if (m == 15 && n == 1 && item_specials2 [a])		// pochodnia plonaca
   		working_items [a] = 1;
   	else if (item [a] == 5 && item_state [a] == 1)				// burning obstacle
   		working_items [a] = 1;
   	else if (m == 15 && n == 7 && item_specials2 [a] == 1)				// high explosive ticking
   		working_items [a] = 1;

//      if (s >= 50)
//      	unpaid_items [a] = 1;
   }
}

char exit_location (char key_)
{
	int p, q, hostile_presence = 0;
	int x_pos, y_pos, near_monster = 0;

   if (cl_id < 1200)
	  	for (q = 0; q < monsters_amount; q ++)
   	  	if (monster_aim [q] == -1)
      	{
				hostile_presence = 1;
   	     	break;
      	}

	for (y_pos = v_pos - 1; y_pos <= v_pos + 1; y_pos ++)
   	for (x_pos = h_pos - 1; x_pos <= h_pos + 1; x_pos ++)
		   if (monsters_planszy [x_pos] [y_pos] >= 0 && monster_aim [monsters_planszy [x_pos] [y_pos]] == -1)
        		hostile_presence = 2;

   if (key_ != 20 && hostile_presence == 2)
   	msg ("<Not while being by a hostile enemy!");
   else if (key_ != 20 && hostile_presence == 1)
   {
  	  	msg ("<There is still some enemy here. Do you still want to leave area ?");

		if (answer ())
			return 1;
		else
			msg_reset ();
   }
   else if (hostile_presence == 0)
   {
		msg ("<Do you want to exit area (y/n) ?");

		if (answer ())
			return 1;
		else
			msg_reset ();
   }

	return 0;
}

void save ()
{
	char nazwa_pliku [12] = {"tmp_"};
//	char nazwa_pliku [12] = {"            "};
   int a, b, c = 0, d, i, j, m, n, q, r, s, t, x = 0, nr_znaku = 0;
   int current_arrow = 1;

	plik = 0;

//   kopia_tablicy (nazwa_pliku, player_name, 8);
/*	nazwa_pliku [8] = '.';
	nazwa_pliku [9] = 'd';
	nazwa_pliku [10] = 'f';
	nazwa_pliku [11] = 's';*/
   msg_reset ();
   msg ("Writing save file...");
	temp00 = fopen ("save.dfs", "w");

   for (a = 1200; a < 2000; a ++)
		hexy_save (visited_locations [a]);

	hexy_save (cl_id);
   hexy_save (current_weapon);
   hexy_save (x_planszy);
   hexy_save (y_planszy);
   hexy_save (h_cur);
   hexy_save (v_cur);
   hexy_save (h_pos);
   hexy_save (v_pos);
   hexy_save (h_pos_world);
   hexy_save (v_pos_world);
   hexy_save (h_pos_pl);
   hexy_save (v_pos_pl);
   hexy_save (health);
   hexy_save (max_health);
   hexy_save (air);
   hexy_save (max_air);
   hexy_save (speed);
   hexy_save (armor);
   hexy_save (GCDC);
   hexy_save (exp_lev);
   hexy_save (experience);
   hexy_save (exp_next);
   hexy_save (luck);
   hexy_save (total_max_health);
   hexy_save (total_max_air);
   hexy_save (total_speed);
   hexy_save (total_armor);
   hexy_save (health_bonus);
   hexy_save (total_damage);
   hexy_save (action_cost);
   hexy_save (action_type);
//   hexy_save (autoswap);
   hexy_save (satiation);
   hexy_save (weight);

   for (i = 0; i < 10; i ++)
  	   hexy_save (resistance [i]);

   hexy_save (elapsed_time);

   for (i = 0; i < 7; i ++)
  	   hexy_save (left_poison_turns [i]);

   for (i = 0; i < 7; i ++)
  	   hexy_save (drugs [i]);

   hexy_save (attacks);
   hexy_save (player_gender);
   hexy_save (player_age);
   hexy_save (exit_ability);
   hexy_save (turns_amount);
   hexy_save (turns_amount_);
   hexy_save (moves_env);
   hexy_save (bonus_env);

   for (i = 0; i < 10; i ++)
  	   hexy_save (coverers [i]);

   hexy_save (chosen_hand);

   for (i = 0; i < 20; i ++)
  	   hexy_save (map_secret [i]);

   for (i = 0; i < 128; i ++)
  	   hexy_save (quest [i]);

   for (i = 0; i < 101; i ++)
  	   hexy_save (achievement [i]);

   for (i = 0; i < 5051; i ++)
  	   hexy_save (achievement_temp [i]);

   for (i = 0; i < 50; i ++)
  	   hexy_save (abilities [i]);

   for (i = 0; i < 20; i ++)
  	   hexy_save (character_state [i]);

   hexy_save (player);

   for (i = 0; i < 20; i ++)
  	   hexy_save (player_name [i]);

   for (i = 0; i < 2000; i ++)
  	   hexy_save (goody_reputation [i]);

   for (i = 0; i < 2000; i ++)
  	   hexy_save (badass_reputation [i]);

   for (i = 0; i < 2000; i ++)
  	   hexy_save (killed_monsters [i]);

	hexy_save (passed_event_turns);
//   hexy_save (items_amount);

	for (x = 1; x <= 19; x ++)	// zapisuje nowe index'y zalozonych przedmiotow
	{
		if (item_body [x])
		{
			for (item_id = 0; item_id < items_amount; item_id ++)
			{
				if (item [item_id] == 1 || item [item_id] == 4)
					nr_znaku ++;

				if (item_body [x] == item_id)
					item_body [x] = nr_znaku - 1;
			}

			nr_znaku = 0;
		}

		hexy (2, item_body [x] + 128);
	}

	putc (255, temp00);

	for (item_id = 0; item_id < items_amount; item_id ++)
	{
		if (item [item_id] == 1 || item [item_id] == 4)
		{
			hexy (2, item [item_id] + 64);
			hexy (2, item_icon [item_id] + 128);
			hexy (2, item_type [item_id] + 128);
			hexy (2, item_group [item_id] + 40);
			hexy (2, item_dv [item_id] + 80);
			hexy (2, item_dices [item_id] + 128);
			hexy (2, item_dmg_bonus [item_id] + 80);
			hexy (2, item_status [item_id] + 64);
			hexy (2, item_specials1 [item_id] + 128);
			hexy (2, item_specials2 [item_id] + 128);
			hexy (2, item_weight [item_id] + 128);
			hexy (2, item_value_material [item_id] + 128);
			hexy (2, item_amount [item_id] + 128);
			hexy (2, item_owner [item_id] + 128);
			hexy (2, item_state [item_id] + 64);
			hexy (2, item_ident [item_id] + 64);
			hexy (2, item_hit [item_id] + 80);
		}
	}

   putc (255, temp00);

	if (1)		// info o planszy w ktorej aktualnie jest postac
	{
		hexy (2, x_planszy);
		hexy (2, y_planszy);

		for (item_id = 0; item_id < items_amount; item_id ++)
		{
			if (item [item_id] != 1 && item [item_id] != 4)
			{
				hexy (2, item [item_id] + 64);
				hexy (2, item_icon [item_id] + 128);
				hexy (2, item_type [item_id] + 128);
				hexy (2, item_group [item_id] + 40);
				hexy (2, item_dv [item_id] + 80);
				hexy (2, item_dices [item_id] + 128);
				hexy (2, item_dmg_bonus [item_id] + 80);
				hexy (2, item_status [item_id] + 64);
				hexy (2, item_specials1 [item_id] + 128);
				hexy (2, item_specials2 [item_id] + 128);
				hexy (2, item_weight [item_id] + 128);
				hexy (2, item_value_material [item_id] + 128);
				hexy (2, item_amount [item_id] + 128);
				hexy (2, item_owner [item_id] + 128);
				hexy (2, h_pos_item [item_id] + 40);
				hexy (2, v_pos_item [item_id] + 40);
				hexy (2, item_state [item_id] + 64);
				hexy (2, item_ident [item_id] + 64);
				hexy (2, item_hit [item_id] + 80);
			}
		}

		putc (255, temp00);	// znacznik

		for (monster_id = 0; monster_id < monsters_amount; monster_id ++)
      {
			hexy (2, monster [monster_id] + 128);
        	hexy (2, monster_code [monster_id] + 128);
			hexy (2, monster_speed [monster_id] + 128);
			hexy (2, monster_health [monster_id] + 128);
			hexy (2, monster_damage [monster_id] + 128);
			hexy (2, monster_hit [monster_id] + 128);
			hexy (2, monster_exp [monster_id] + 128);
			hexy (2, monster_aim [monster_id] + 128);
			hexy (2, monster_pp [monster_id] + 128);
			hexy (2, monster_hp [monster_id] + 128);

        	for (m = 0; m < 30; m ++)
				hexy (2, monster_state [monster_id] [m] + 64);

        	for (m = 0; m < 15; m ++)
				hexy (2, monster_body [monster_id] [m] + 128);

        	for (m = 0; m < 15; m ++)
				hexy (2, monster_backpack [monster_id] [m] + 128);

        	for (m = 0; m < 7; m ++)
				hexy (2, monster_left_poison [monster_id] [m] + 128);

			hexy (2, h_pos_mon [monster_id] + 64);
			hexy (2, v_pos_mon [monster_id] + 64);
			hexy (2, monster_char [monster_id] + 64);
         hexy (2, monster_alignment [monster_id] + 64);
		}

		putc (255, temp00);

		for (q = 0; q < y_planszy; q ++)
			for (r = 0; r < x_planszy; r ++)
				hexy (2, mem_planszy [r] [q] + 128);

		for (s = 0; s < y_planszy; s ++)
			for (t = 0; t < x_planszy; t ++)
				hexy (2, floor_planszy [t] [s] + 16);
   }

   for (a = 1200; a < 2000; a ++)
   {
   	if (visited_locations [a] && a != cl_id)
      {
//      	gotoxy (2, 24);
//         messages ("cl_id ^", a, COLOR_GRAY + 32);
	   	plik = -1;
			hexy (3, a);
			nazwa_pliku [4] = znak1; nazwa_pliku [5] = znak2;
			temp01 = fopen (nazwa_pliku, "r");

			while (c != EOF)
			{
				c = getc (temp01);

				if (c == EOF)
					break;

				putc (c, temp00);
            gotoxy (78, 23);
            messages ("#", 0, COLOR_DARK_RED + 32);
			}

         wait (300);
         gotoxy (78, 23);
         messages ("#", 0, COLOR_GRAY + 32);
         wait (100);
         fclose (temp01);
         c = 254;
         putc (254, temp00);
      }
	}

	fclose (temp00);
//	remove ("tmp_inv.txt");			// usuwa tymczasowy plik noszonych przedmiotow
   play = 0;
}

int load ()
{
	char nazwa_pliku [12] = {"tmp_"};
//	char nazwa_pliku [12] = {"            "};
   int a, b, c = 0, d, i, j, m, n, q, r, s, t;
   int done;
//   struct ffblk ffblk;

/*   done = findfirst ("*.dfs", &ffblk, 0);

   while (!done)
   {
      printf ("  %s\n", ffblk.ff_name);
      done = findnext (&ffblk);
   }

   wait (2000);*/

	item_id = 0;
   msg_reset ();

	if (fopen ("save.dfs", "rt") == NULL)
   	return 0;
   else
   {
   	gotoxy (2, 24);
	   messages ("Reading save file...", 0, 32 + COLOR_GRAY);
		temp00 = fopen ("save.dfs", "r");
   }

   for (a = 1200; a < 2000; a ++)
		visited_locations [a] = hexy_load ();

	cl_id = hexy_load ();
   current_weapon = hexy_load ();
   x_planszy = hexy_load ();
   y_planszy = hexy_load ();
   h_cur = hexy_load ();
   v_cur = hexy_load ();
   h_pos = hexy_load ();
   v_pos = hexy_load ();
   h_pos_world = hexy_load ();
   v_pos_world = hexy_load ();
   h_pos_pl = hexy_load ();
   v_pos_pl = hexy_load ();
   health = hexy_load ();
   max_health = hexy_load ();
   air = hexy_load ();
   max_air = hexy_load ();
   speed = hexy_load ();
   armor = hexy_load ();
   GCDC = hexy_load ();
   exp_lev = hexy_load ();
   experience = hexy_load ();
   exp_next = hexy_load ();
   luck = hexy_load ();
   total_max_health = hexy_load ();
   total_max_air = hexy_load ();
   total_speed = hexy_load ();
   total_armor = hexy_load ();
   health_bonus = hexy_load ();
   total_damage = hexy_load ();
   action_cost = hexy_load ();
   action_type = hexy_load ();
//   autoswap = hexy_load ();
   satiation = hexy_load ();
   weight = hexy_load ();

   for (i = 0; i < 10; i ++)
  	   resistance [i] = hexy_load ();

   elapsed_time = hexy_load ();

   for (i = 0; i < 7; i ++)
  	   left_poison_turns [i] = hexy_load ();

   for (i = 0; i < 7; i ++)
  	   drugs [i] = hexy_load ();

   attacks = hexy_load ();
   player_gender = hexy_load ();
   player_age = hexy_load ();
   exit_ability = hexy_load ();
   turns_amount = hexy_load ();
   turns_amount_ = hexy_load ();
   moves_env = hexy_load ();
   bonus_env = hexy_load ();

   for (i = 0; i < 10; i ++)
  	   coverers [i] = hexy_load ();

   chosen_hand = hexy_load ();

   for (i = 0; i < 20; i ++)
  	   map_secret [i] = hexy_load ();

   for (i = 0; i < 128; i ++)
  	   quest [i] = hexy_load ();

   for (i = 0; i < 101; i ++)
  	   achievement [i] = hexy_load ();

   for (i = 0; i < 5051; i ++)
  	   achievement_temp [i] = hexy_load ();

   for (i = 0; i < 50; i ++)
  	   abilities [i] = hexy_load ();

   for (i = 0; i < 20; i ++)
  	   character_state [i] = hexy_load ();

   player = hexy_load ();

   for (i = 0; i < 20; i ++)
  	   player_name [i] = hexy_load ();

   for (i = 0; i < 2000; i ++)
  	   goody_reputation [i] = hexy_load ();

   for (i = 0; i < 2000; i ++)
  	   badass_reputation [i] = hexy_load ();

   for (i = 0; i < 2000; i ++)
  	   killed_monsters [i] = hexy_load ();

	passed_event_turns = hexy_load ();
//   items_amount = hexy_load ();

   // info o noszonych przedmiotach
   item_id = 1;

	while (c != 255)
	{
		c = getc (temp00);

		if (c == 255 || c == EOF)
			break;

		znak1 = c - 32;
		znak2 = getc (temp00) - 32;
		item_body [item_id] = znak1 * 220 + znak2 - 128;
		item_id ++;
	}

	a = c = 0;
   item_id = 0;

	// odczytuje wszystkie itemy z plecaku
	while (c != 255)
	{
   	a ++;
		c = getc (temp00);

		if (c == 255 || c == EOF)
			break;

		znak1 = c - 32;
		znak2 = getc (temp00) - 32;

		switch (a)
		{
			case 1:
				item [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 2:
				item_icon [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 3:
				item_type [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 4:
				item_group [item_id] = znak1 * 220 + znak2 - 40;
				break;
			case 5:
				item_dv [item_id] = znak1 * 220 + znak2 - 80;
				break;
			case 6:
				item_dices [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 7:
				item_dmg_bonus [item_id] = znak1 * 220 + znak2 - 80;
				break;
			case 8:
				item_status [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 9:
				item_specials1 [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 10:
				item_specials2 [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 11:
				item_weight [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 12:
				item_value_material [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 13:
				item_amount [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 14:
				item_owner [item_id] = znak1 * 220 + znak2 - 128;
				break;
			case 15:
				item_state [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 16:
				item_ident [item_id] = znak1 * 220 + znak2 - 64;
				break;
			case 17:
				item_hit [item_id] = znak1 * 220 + znak2 - 80;
            a = 0;
				break;
		}

      if (!a)
			item_id ++;
	}

//	fclose (temp02);
//	remove ("tmp_inv.txt");			// usuwa tymczasowy plik noszonych przedmiotow
//	items_amount = item_id;
	if (1)			// current area info
	{
		x_planszy = (getc (temp00) - 32) * 220 + getc (temp00) - 32;
		y_planszy = (getc (temp00) - 32) * 220 + getc (temp00) - 32;

		b = c = 0;
//     	item_id = items_amount;

		while (1)
		{
      	b ++;
			c = getc (temp00);

			if (c == 255 || c == EOF)
				break;

			znak1 = c - 32;
			znak2 = getc (temp00) - 32;

			switch (b)
			{
				case 1:
					item [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 2:
					item_icon [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 3:
					item_type [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 4:
					item_group [item_id] = znak1 * 220 + znak2 - 40;
					break;
				case 5:
					item_dv [item_id] = znak1 * 220 + znak2 - 80;
					break;
				case 6:
					item_dices [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 7:
					item_dmg_bonus [item_id] = znak1 * 220 + znak2 - 80;
					break;
				case 8:
					item_status [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 9:
					item_specials1 [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 10:
					item_specials2 [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 11:
					item_weight [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 12:
					item_value_material [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 13:
					item_amount [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 14:
					item_owner [item_id] = znak1 * 220 + znak2 - 128;
					break;
				case 15:
					h_pos_item [item_id] = znak1 * 220 + znak2 - 40;
					break;
				case 16:
					v_pos_item [item_id] = znak1 * 220 + znak2 - 40;
					break;
				case 17:
					item_state [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 18:
					item_ident [item_id] = znak1 * 220 + znak2 - 64;
					break;
				case 19:
					item_hit [item_id] = znak1 * 220 + znak2 - 80;
               b = 0;
					break;
			}

			if (!b)
				item_id ++;
		}

      items_amount = item_id;
//debug_info ();
		d = 0;
		monster_id = 0;

		while (1)
		{
      	d ++;

			if (d < 11 || d > 14)
         {
				c = getc (temp00);

				if (c == 255 || c == EOF)
					break;

				znak1 = c - 32;
				znak2 = getc (temp00) - 32;
         }

			switch (d)
			{
				case 1:
					monster [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 2:
					monster_code [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 3:
					monster_speed [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 4:
					monster_health [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 5:
					monster_damage [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 6:
					monster_hit [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 7:
					monster_exp [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 8:
					monster_aim [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 9:
					monster_pp [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 10:
					monster_hp [monster_id] = znak1 * 220 + znak2 - 128;
					break;
				case 11:
               for (m = 0; m < 30; m ++)
               {
						znak1 = getc (temp00) - 32;
						znak2 = getc (temp00) - 32;
						monster_state [monster_id] [m] = znak1 * 220 + znak2 - 64;
               }
					break;
				case 12:
               for (m = 0; m < 15; m ++)
               {
						znak1 = getc (temp00) - 32;
						znak2 = getc (temp00) - 32;
						monster_body [monster_id] [m] = znak1 * 220 + znak2 - 128;
               }
					break;
				case 13:
               for (m = 0; m < 15; m ++)
               {
						znak1 = getc (temp00) - 32;
						znak2 = getc (temp00) - 32;
						monster_backpack [monster_id] [m] = znak1 * 220 + znak2 - 128;
               }
					break;
				case 14:
               for (m = 0; m < 7; m ++)
               {
						znak1 = getc (temp00) - 32;
						znak2 = getc (temp00) - 32;
						monster_left_poison [monster_id] [m] = znak1 * 220 + znak2 - 128;
               }
					break;
				case 15:
					h_pos_mon [monster_id] = znak1 * 220 + znak2 - 64;
					break;
				case 16:
					v_pos_mon [monster_id] = znak1 * 220 + znak2 - 64;
					break;
				case 17:
					monster_char [monster_id] = znak1 * 220 + znak2 - 64;
					break;
				case 18:
					monster_alignment [monster_id] = znak1 * 220 + znak2 - 64;
               d = 0;
					break;
			}

			if (!d)
				monster_id ++;
		}

		monsters_amount = monster_id;
      c = 0;

		for (q = 0; q < y_planszy; q ++)
		{
			for (r = 0; r < x_planszy; r ++)
			{
				c = getc (temp00);

				if (c == 255 || c == EOF)
					break;

				znak1 = c - 32;
				znak2 = getc (temp00) - 32;
				mem_planszy [r] [q] = znak1 * 220 + znak2 - 128;
			}
		}

      c = 0;

		for (s = 0; s < y_planszy; s ++)
		{
			for (t = 0; t < x_planszy; t ++)
			{
				c = getc (temp00);

				if (c == 255 || c == EOF)
					break;

				znak1 = c - 32;
				znak2 = getc (temp00) - 32;
				floor_planszy [t] [s] = znak1 * 220 + znak2 - 16;
			}
		}
//		remove (nazwa_pliku);
	}

   for (a = 0; a < MAXITEMS; a ++)
   {
   	working_items [a] = 0;
      unpaid_items [a] = 0;
   }

   for (a = 0; a < items_amount; a ++)
   {
   	m = item_group [a];
  	   n = item_type [a];
      s = item_value_material [a] % 100;

		if (m == 19 && n < 1000 && item_specials1 [a] > 0)		// gnijace jedzenie
	   	working_items [a] = 1;
   	else if (m == 15 && n == 1 && item_specials2 [a])		// pochodnia plonaca
   		working_items [a] = 1;
   	else if (item [a] == 5 && item_state [a] == 1)				// burning obstacle
   		working_items [a] = 1;
   	else if (m == 15 && n == 7 && item_specials2 [a] == 1)				// high explosive ticking
   		working_items [a] = 1;

//      if (s >= 50)
//      	unpaid_items [a] = 1;
   }

//		cl_id = tl_id;
//		statystyki (0);
	visible_monsters [0] = -15;

	for (q = 0; q < x_planszy; q ++)
     	for (r = 0; r < y_planszy; r ++)
      {
			stan_planszy [q] [r] = 0;
         items_planszy [q] [r] = -1;
         monsters_planszy [q] [r] = -15;
         obstacles_planszy [q] [r] = -1;

         for (s = 0; s < 15; s ++)
	         coverers_planszy [q] [r] [s] = 0;

//			if (visited_locations [cl_id])
     	   	convert_floor (q, r);
      }

	for (item_id = 0; item_id < items_amount; item_id ++)
     	put_item (item_id);

   for (monster_id = 0; monster_id < monsters_amount; monster_id ++)
   {
     	monsters_planszy [h_pos_mon [monster_id]] [v_pos_mon [monster_id]] = monster_id;

		if (visited_locations [tl_id] && monster_code [monster_id] != _Helc)
         monster_hp [monster_id] = monster_health [monster_id];
   }

   monsters_planszy [h_pos] [v_pos] = -1;
	ustaw_gracza ();
   b = i = 0;

   for (a = 1200; a < 2000; a ++)
   	if (visited_locations [a])
         b ++;

   gotoxy (22, 24);
   messages (" [", 0, 32 + COLOR_DARK_GRAY);

   for (j = 0; j < b; j ++)
   	messages (".", 0, 32 + COLOR_DARK_GRAY);

  	messages ("] ", 0, 32 + COLOR_DARK_GRAY);

   for (a = 1200; a < 2000; a ++)
   	if (visited_locations [a] && a != cl_id)
      {
//      	gotoxy (2, 24);
//         messages ("cl_id ^", a, COLOR_GRAY + 32);
	   	plik = -1;
			hexy (3, a);
			nazwa_pliku [4] = znak1; nazwa_pliku [5] = znak2;
			temp01 = fopen (nazwa_pliku, "w");
         i ++;
         gotoxy (79, 24);
         messages ("A", 0, COLOR_DARK_BLUE + 32);

			while (c != 254)
			{
				c = getc (temp00);

				if (c == 254)
					break;

				putc (c, temp01);
			}

         speed_star (i);
  	      gotoxy (79, 24);
     	   messages ("#", 0, COLOR_GRAY + 32);
        	wait (losuj (10, 20));
         c = 255;
  	      fclose (temp01);
      }

	fclose (temp00);
	remove ("save.dfs");
   return 2;
}

void speed_star (int i)
{
	int r, s;

	for (r = 0; r < (s = losuj (2, 5)); r ++)
   {
	   gotoxy (23 + i, 24);
     	messages ("/", 0, 32 + COLOR_DARK_GRAY);
  	   wait (losuj (30, 70));
      gotoxy (23 + i, 24);
    	messages ("-", 0, 32 + COLOR_DARK_GRAY);
 	   wait (losuj (30, 70));
     	gotoxy (23 + i, 24);
    	messages ("\\", 0, 32 + COLOR_DARK_GRAY);
      wait (losuj (30, 70));
  	   gotoxy (23 + i, 24);
  		messages ("|", 0, 32 + COLOR_DARK_GRAY);
      wait (losuj (30, 70));
   }

	gotoxy (23 + i, 24);
	messages ("#", 0, 32 + COLOR_DARK_GRAY);
}
