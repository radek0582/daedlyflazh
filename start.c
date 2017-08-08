#include "deklaracje.h"

void ekran_powitalny ()
{
	int a;
	int kolor;
   int choosen = 0;

   for (a = 0; a < 1000; a ++)
   	monte_carlo [a] = rand () % 16384;

	clear ();
	make_window (1, 0, 5, 0, 70, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze

"############################################################^n"
"#                                                          #^n"
"#                                       ###      ###       #^n"
"#                                      #^08000^09#    #^08000^09#      #^n"
"# WELCOME IN THE WORLD OF...          #^080000^09#    #^080000^09#     #^n"
"#                                    #^08000000^09 ## ^08000000^09#    #^n"
"#                                    #^0800000^08/^080000^09\\^0800000^09#    #^n"
"# - - - - - - - - - - - - - - - - /  ######I^080  0^09I######    #^n"
"#- - - - - - - - - - - - - - -             I^080  0^09I          #^n"
"#                            /  /          \\^080000^09/          #^n"
"#                                           #^0800^09#           #^n"
"# ...DAEDLYFLAZH !         /  /            #^080000^09#          #^n"
"#                                         #^08000000^09#         #^n"
"#             (beta)     /  /            ##########        #^n"
"#                           - - - - - - - - - - - - - - - -#^n"
"#                      / - - - - - - - - - - - - - - - - - #^n"
"#                                                          #^n"
"#         (C) copyright 2011 by Radzio and freekE          #^n"
"#                    thanks to: Verdin, Deaven             #^n"
"#                                                          #^n"
"############################################################"
//"#^01#^02#^03#^04#^05#^06#^07#^08#^09#^10#^11#^12#^13#^14#^15#"
   , COLOR_DARK_GRAY, COLOR_DARK_GRAY);												// 8: kolor ramki, 8: kolor tekstu

	make_window (0, 2, 0, 0, 78, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
   	"^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n"
	   "^08                 (C) copyright 2011 by Radzio and freekE^n"
   	"^08                           all rights reserved"
	   , 9, 9);												// 8: kolor ramki, 8: kolor tekstu

	while(!choosen)
   {
		make_window (0, 0, 1, 1, 76, 18, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
	   "^n^n^n^n^n^n"
	   "^08DAEDLYFLAZH :"
	   , COLOR_DARK_GRAY, COLOR_DARK_GRAY);												// 8: kolor ramki, 8: kolor tekstu

		choosen = choice (4, "1111", -1, -1, -1, 3, -1, COLOR_GRAY, COLOR_WHITE, 20, 10, 0);		// 5: liczba wariantow, 0: 2-a czesc (binarnie), "1001": 1-a czesc, -1 (* 3): extra klawisze, 3: co wybieramy = menu gry, 20: dlugosc tekstu (opcjonalnie), 5: kolor tekstu, 7: kolor podswietlenia, 20: pozycja X, 10: poz. Y

   	if (choosen == 4)
	   	play = 0;
   	else if (choosen == 3)
      {
      	choosen = 0;
      	achievements ();
      }
      else if (choosen == 2)
      {
			if ((temp00 = fopen ("save.dfs", "rt")) == NULL)		// brak pliku
		   {
         	gotoxy (2, 24);
         	messages ("No saved game!_", 0, 30);
            gotoxy (2, 24);
         	messages ("########################", 0, 16 + COLOR_DARK_GRAY);
				fclose (temp00);
            choosen = 0;
		   }
         else
				play = load ();
      }
   }
}

void inicjuj_kolory ()
{
	if (0)//can_change_color () != ERR)
   {
		// black background
		init_pair (1, COLOR_RED, COLOR_BLACK);
		init_pair (2, COLOR_GREEN, COLOR_BLACK);
		init_pair (3, COLOR_YELLOW, COLOR_BLACK);
		init_pair (4, COLOR_BLUE, COLOR_BLACK);
		init_pair (5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair (6, COLOR_CYAN, COLOR_BLACK);
		init_pair (7, COLOR_WHITE, COLOR_BLACK);
		init_pair (8, COLOR_GRAY, COLOR_BLACK);
		init_pair (9, COLOR_DARK_GRAY, COLOR_BLACK);
		init_pair (10, COLOR_DARK_RED, COLOR_BLACK);
		init_pair (11, COLOR_DARK_GREEN, COLOR_BLACK);
		init_pair (12, COLOR_DARK_BLUE, COLOR_BLACK);
		init_pair (13, COLOR_BROWN, COLOR_BLACK);
		init_pair (14, COLOR_VIOLET, COLOR_BLACK);
		init_pair (15, COLOR_OLIVE, COLOR_BLACK);

		// color background
		init_pair (128 + COLOR_DARK_BLUE, COLOR_DARK_BLUE, COLOR_DARK_RED);
		init_pair (128 + COLOR_DARK_GRAY, COLOR_DARK_GRAY, COLOR_DARK_RED);
		init_pair (128 + COLOR_GRAY, COLOR_GRAY, COLOR_DARK_RED);

		  											// RED     GREEN		BLUE
   	init_color (COLOR_BLUE, 				0, 		0,       950);
	   init_color (COLOR_DARK_BLUE, 			0, 		0,       700);
   	init_color (COLOR_RED, 					900,		0,       0);
	   init_color (COLOR_DARK_RED, 			500, 		0, 		0);
   	init_color (COLOR_WHITE, 				900, 		900,  	900);
	   init_color (COLOR_GRAY, 				600, 		600,  	600);
   	init_color (COLOR_DARK_GRAY, 			400, 		400, 		400);
   	init_color (COLOR_GREEN, 				0, 		900,		0);
	   init_color (COLOR_DARK_GREEN, 		0, 		500, 		0);
	   init_color (COLOR_MAGENTA,				900, 		0, 		900);
   	init_color (COLOR_YELLOW, 				900, 		900, 		0);
	   init_color (COLOR_BROWN, 				500, 		250, 		0);
   	init_color (COLOR_VIOLET, 				700, 		0, 		900);
	   init_color (COLOR_OLIVE, 				500, 		500, 		0);
   }
   else
   {
		// black background
		init_pair (1, 12, COLOR_BLACK);					  	// red
		init_pair (2, 10, COLOR_BLACK);						// green
		init_pair (3, 14, COLOR_BLACK);						// yellow
		init_pair (4, 9, COLOR_BLACK);						// blue
		init_pair (5, 13, COLOR_BLACK);						// magenta
		init_pair (6, 11, COLOR_BLACK);						// cyan
		init_pair (7, 15, COLOR_BLACK);						// white
		init_pair (8, 7, COLOR_BLACK);						// (test) 7 = gray
		init_pair (9, 8, COLOR_BLACK);						// dark gray
		init_pair (10, 4, COLOR_BLACK);						// dark red
		init_pair (11, 2, COLOR_BLACK);						// dark green
		init_pair (12, 1, COLOR_BLACK);						// dark blue
		init_pair (13, 6, COLOR_BLACK);						// dark yellow / brown
		init_pair (14, 5, COLOR_BLACK);						// dark magenta / violet
		init_pair (15, 3, COLOR_BLACK);						// dark cyan / olive

		// color background
		init_pair (128 + 7, 15, COLOR_RED);
		init_pair (128 + 8, 7, COLOR_RED);
		init_pair (128 + 9, 8, COLOR_RED);
   }
}

void intro ()
{
	clear ();
	make_window (1, -1, 15, -10, 50, 15, -2,
   " In the future (about year 2069), a nuclear war has transformed the Earth into a radioactive"
   " wasteland where the sea has dried up leaving it as a post-apocalyptic desert."
   " In the desert, scavengers patrols (called Nomads) wide areas to geather alloys,"
   " junk, tools - anything they could sell to junkyard dealers. The most precious treasure"
   " is parts of a military projects that was abandoned. Wasted remains of cyborg army is"
   " most profit and desireable stuff. Destroyed, manufuncted and broken cyborgs called"
   " CLASS are rare product but they also can start a violent rampage and has become the"
   " Nomads (and peoples generaly) prime target for extermination. Save the Americas Wasteland"
   " by the word of President or lead the CLASS cyborg army wipe out all humanity."
	"^n^n New York City is largest town in this wasteland. Massive metropolis contains military Corp's, junkies, mutants and scumms."
	, COLOR_DARK_GRAY, COLOR_DARK_GRAY);
}

void save_achievements ()
{
   int x, i, j, k, m, n, q, r, s, t;

	temp00 = fopen ("achieve.a", "w");

	for (x = 1; x <= 100; x ++)
	{
		if (achievement [x])
      {
      	if (x == 3 || x == 14 || x == 23)
         	i = achievement [x] + 50;
         else
         	i = achievement [x] + 50 + x;

			putc (i, temp00);
      }
      else
			putc (49, temp00);
	}

	putc (255, temp00);
	fclose (temp00);
}

void load_achievements ()
{
   int a, b, c, d, m, n, q, r, s, t;

	temp00 = fopen ("achieve.a", "r");
   a = 1;

	while (c != 255)
	{
		c = getc (temp00);

		if (c == 255 || c == EOF)
			break;
      else if (c != 49)					// != 0
      {
      	if (a == 3 || a == 14 || a == 23)
		   	achievement [a] = c - 50;
      	else
		   	achievement [a] = c - 50 - a;
      }

      a ++;
	}

	fclose (temp00);
}

void achievements ()
{
	int current_page = 1, a, b = 1;

	make_window (0, 0, 1, 1, 60, 15, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
	   "^08ACHIEVEMENTS :"
	   , COLOR_DARK_GRAY, COLOR_DARK_GRAY);												// 8: kolor ramki, 8: kolor tekstu

/*	for (a = 1; a < 16; a ++)
	   achievement [a] = 1;

   achievement [7] = 0;*/

	for (a = 1; a <= 7; a ++)
   {
  		gotoxy (4, 4 + a * 2);

      if ((a == 3 || a == 14 || a == 23) && achievement [a] == 51 || a != 3 && a != 14 && a != 23 && achievement [a] == 1)
	  	   enter_achievement (a, 19);
      else
   	   enter_achievement (a, 24);

      if ((a == 3 || a == 14 || a == 23) && achievement [a] == 51 || a != 3 && a != 14 && a != 23 && achievement [a] == 1)
      {
	  		gotoxy (4, 5 + a * 2);
	  	   enter_achievement (a + 100, 19);
      }
	}

   while (key != _ESC)
   {
   	klawisz ();

		if (current_page < 6 && (key == '2' || key == 2 || key == 82) || current_page > 1 && (key == '8' || key == 3 || key == 83))			// page down / up
      {
      	if (key == '2' || key == 2 || key == 82)
	      	current_page ++;
         else if (key == '8' || key == 3 || key == 83)
	      	current_page --;

         clear_area (3, 5, 77, 20);

			for (a = current_page * 7 - 6; a <= current_page * 7; a ++)
   	   {
      		gotoxy (4, 4 + b * 2);

		      if ((a == 3 || a == 14 || a == 23) && achievement [a] == 51 || a != 3 && a != 14 && a != 23 && achievement [a] == 1)
		   	   enter_achievement (a, 19);
            else
		   	   enter_achievement (a, 24);

		      if ((a == 3 || a == 14 || a == 23) && achievement [a] == 51 || a != 3 && a != 14 && a != 23 && achievement [a] == 1)
            {
	      		gotoxy (4, 5 + b * 2);
		   	   enter_achievement (a + 100, 19);
            }
            b ++;
	      }
         b = 1;
      }
   }
}

void ekran_wyboru ()
{
	int i, j, k;
	char nr_klawisza = 0;
   int choosen;

	make_window (0, 2, 0, -1, 78, 24, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
   "^n^n^08 DAEDLYFLAZH : STARTING NEW GAME..."
   "^n^n^n GENDER : "
   "^n^n^n^n^n^n^n^n^n^n^n^n^09             <choose your gender>"
   "^n^n^08      (C) copyright 2011 by Radzio and freekE^n"
   "^08                 all rights reserved"
   , 9, 9);												// 8: kolor ramki, 8: kolor tekstu

	textcolor (COLOR_DARK_GRAY);
	gotoxy (3, 2);
	choosen = choice (2, "11", -1, -1, -1, 0, 12, COLOR_GRAY, COLOR_GRAY, 13, 7, 0);
   player_gender = choosen;

	textcolor (COLOR_DARK_GRAY);
	gotoxy (3, 11);
	messages (" CLASS  : ", 0, 16 + COLOR_DARK_GRAY);
	gotoxy (15, 19);
	messages ("     <choose your age>      ", 0, 16 + COLOR_DARK_GRAY);
	player_age = choice (3, "111", -1, -1, -1, 2, -1, COLOR_GRAY, 4, 13, 11, 0);
	gotoxy (8, 19);
	messages ("<type name, then press Enter to start>", 0, 16 + COLOR_DARK_GRAY);
	gotoxy (3, 15);
	messages (" NAME   : ", 0, 16 + COLOR_DARK_GRAY);
   addch (95);

	while (1)
	{
   	klawisz ();

		if (key == _BACKSPACE && nr_klawisza > 0)	// co gdy wcisniemy backspace
		{
			addch (key);
         addch (key);
			addch (32);
			addch (32);
         addch (key);
         addch (key);
			addch (95);
			nr_klawisza --;
			player_name [nr_klawisza] = 0;
		}

		if (nr_klawisza < 17 && (key > 47 && key < 127 || key == 32 && nr_klawisza > 0))
		{
      	addch (8);
			addch (key);
         addch (95);
			player_name [nr_klawisza] = key;
			nr_klawisza ++;
		}

		if (key == _ENTER || key == _ENTER2)
			break;
	}               

	if (!nr_klawisza)
	  	kopia (player_name, names (player_gender));

	switch (player_gender)
	{
		case _MALE:
			player = 64 + BLUE;
			max_health = 25;
			break;
		case _FEMALE:
			player = 64 + RED;
			max_health = 20;
         abilities [_SCIENCE] += 1;
			break;
	}

	switch (player_age)
	{
		case 1:
         abilities [_MELEE_ATTACK] = 4;
			break;
		case 2:
      	max_health += 15;
         abilities [_PRIME] = 4;
         abilities [_SCIENCE] += 1;
			break;
		case 3:
         abilities [_SCIENCE] += 2;
			break;
	}

   health = max_health;
//	power = max_power = mana * 2 + rand () % 10;
   speed = 5;
	character_state [0] = 3;
   satiation = 20000;
   exp_next = 500;

   for (i = 1; i < 8; i ++)
   {
//     	abilities [i] += 3;//losuj (1, 6);
      abilities_pot [i] = 10;//abilities [i] + losuj (4, 16);
   }

	air = max_air = abilities [_CONDITION] * 3 + losuj (1, 10);
	generuj_ekwipunek ();

	for (i = 0; i < X_MAX_PL; i ++)
     	for (j = 0; j < Y_MAX_PL; j ++)
      {
	      items_planszy [i] [j] = -1;
         obstacles_planszy [i] [j] = -1;
         monsters_planszy [i] [j] = -15;
         mem_planszy [i] [j] = 32;
		}

	cl_id = _WORLD;
   current_weapon = 1;
	h_pos_world = 45; v_pos_world = 2;
	generuj_world_map ();
	visited_locations [1999] = 1;

/*  	cl_id = _YERUSHALAYIM;
	visited_locations [_YERUSHALAYIM] = 1;
   h_pos_world = 9; v_pos_world = 5;
	generuj_Yerushalayim ();*/

	for (i = 0; i < x_planszy; i ++)
     	for (j = 0; j < y_planszy; j ++)
  	   	convert_floor (i, j);

	for (item_id = 0; item_id < items_amount; item_id ++)
     	put_item (item_id);

   for (monster_id = 0; monster_id < monsters_amount; monster_id ++)
     	monsters_planszy [h_pos_mon [monster_id]] [v_pos_mon [monster_id]] = monster_id;

	monsters_planszy [h_pos] [v_pos] = -1;
   visible_monsters [0] = -15;
}

void generuj_ekwipunek ()
{
	int i;

	for (i = 1; i < 20; i ++)
		item_body [i] = -1;

   if (player_gender == _MALE)
   {
	   ekwipunek (_M119, -1, 4);
   	item_body [_SIDEARM_SLOT] = item_id;
	   ekwipunek (_bullets_9mm, -1, 1);
      item_amount [item_id] = 14;
   }
   else
   {
	   ekwipunek (_6Wayne, -1, 4);
   	item_body [_SIDEARM_SLOT] = item_id;
	   ekwipunek (_RAGS, -1, 4);
   	item_body [_BODY_SLOT] = item_id;
	   ekwipunek (_bullets_9mm, -1, 1);
      item_amount [item_id] = 12;
	   ekwipunek (_MEDIKIT, -1, 1);
	   item_amount [item_id] = 2;
   }
                                       
   if (player_age == 1)
   {
	   ekwipunek (_B_BAT, -1, 4);
   	item_body [_MELEE_SLOT] = item_id;
   }
   else if (player_age == 2)
   {
   	if (item_body [_BODY_SLOT] == -1)
      {
		   ekwipunek (_JACKET, -1, 4);
   		item_body [_BODY_SLOT] = item_id;
      }
      else
		   ekwipunek (_JACKET, -1, 1);

	  	ekwipunek (_GCDC, -1, 1);
	   item_amount [item_id] = 5;
   }
   else if (player_age == 3)
   {
	   ekwipunek (_bullets_9mm, -1, 1);
      item_amount [item_id] = 10;
	  	ekwipunek (_GCDC, -1, 1);
	   item_amount [item_id] = 10;
   }

   weapon_level [2] = weapon_level [20] = 1;	// wyszkolenie w broni z ktora bohater zaczyna gre = 1
  	weapon_level [23] = 1;

   switch (player_gender)
   {
   	case 103:
      	break;
   }

   for (i = 0; i < items_amount; i ++)
   {
//   	item_ident [i] = 1;

   	if (item [i] == 1 || item [i] == 4)
	   	weight += item_weight [i] * item_amount [i];
   }
}

