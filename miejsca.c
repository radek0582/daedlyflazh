#include "deklaracje.h"

void generuj_world_map ()
{                                                                                                           
	int x, y;

	plansza_xy (60, 20, 0);

   h_pos = h_pos_world;
   v_pos = v_pos_world;

   generuj_floor_main (0, 0,

/*012345678901234567890123456789012345678901234567890123456789*/
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~.....~~~~~~~~~~~~~~~~~~~~~~~~~~.....~~~~~~~~~~~~~|"
 "~~~~~~~..~~.............~~~~~~~~~~~~~~~~~.....~~~~~~~~~~~~~~|"
 "~~~~~~~.........................~~..~~.......~~~~~~~~~~~~~~~|"
 "~~~~~~~~.......................~............1~~~~~~~~~~~~~~~|"
 "~~~~~~~~~......................~.............~~~~~~~~~~~~~~~|"
 "~~~~8~~~~..................3...................~~~~~~~~~~~~~|"
 "~~~~~~~~~..............2......................~~~~~~~~~~~~~~|"
 "~~~~~~~~~~...................................~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~..................................~~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~..........................~~~.....~~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~.......7................~~~~~...~~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~....................~~~~~~~~~...5~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~................~~~~~~~~~~~....~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~~~~..~~~.......~~~~~~~~~~~~~~...~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~~~~~~~~~~~..6.~~~~~~~~~~~~~~~~..~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~~~~~~~~~~~~..~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
 	);

  	convert_area ();
}

void generuj_plansze (int level_type)
{
   int floor_type = 1;
   int x, y, a, b, i, j;
   int river_width1, river_width2;

   for (y = 0; y < (y_planszy = 20); y ++)
   	for (x = 0; x < (x_planszy = 60); x ++)
      	floor_planszy [x] [y] = 0;

	switch (level_type)
   {
   	case 563:
      case 564:
			river_width1 = rand () % 3 + 9;
   	   river_width2 = rand () % 5 + 3;

			for (a = 0; a < x_planszy; a ++)
   		{
				river_width1 += rand () % 3 - 1;
		      river_width2 += rand () % 3 - 1;

         	if (river_width2 < 5)
         		river_width2 = 5;

	         if (river_width1 < 2)
   	      	river_width1 = 2;

      	   if (river_width1 + river_width2 > 18)
         		while (river_width1 + river_width2 > 18)
		         	river_width1 --;

		   	for (b = 0; b < river_width2; b ++)
   			  	floor_planszy [a] [river_width1 + b] = 21;	// water
		   }
         break;
   }

	for (i = 0; i < y_planszy; i ++)
	{
		for (j = 0; j < x_planszy; j ++)
		{
			if (!floor_planszy [j] [i])
         {
				floor_planszy [j] [i] = floor_type;

            if (rand () % 100 < 10)
            	floor_planszy [j] [i] = 5;

	         if (rand () % 1000 < 50)
   	      {
      	   	char a = rand () % 5;

	            if (!a)
			         floor_planszy [j] [i] = 6;
      	      else if (a == 1)
			         floor_planszy [j] [i] = 7;
					else if (a == 2)
			         floor_planszy [j] [i] = 8;
					else if (a == 3)
		   	      floor_planszy [j] [i] = 9;
					else
			         floor_planszy [j] [i] = 10;
	         }
         }
		}
	}

   convert_area ();
}

void generuj_New_York_City ()			// New York City
{
   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   monster_na_mapie (_A, _Bren_McGuire, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _Pleasence, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_C, _MALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_D, _FEMALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_E, _SOLDIER, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_F, _SOLDIER, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
".......-.........-.........-..........-.............-.......|"
".######-#########-#########-##########-#############-######.|"
".#....#-#..C....#-#....C..#-#........#-#....D......#-1....#.|"
".###1##-#1#######-#1#####1#-#1########-######11#####-##1###.|"
"------------------------------------------------------------|"
".######-#########-####################-#############-..C....|"
".#..C.#-#.......#-#####.#.F#F..#.....#-#...........#-...D...|"
".#....1-#.......#-##B##F.......##1#..#-#..D..C.....1-.......|"
".#.D..#-#...C...#-##.11..##.##1...#..#-#...........#-.......|"
".#1####-####1####-########E.E#########-#############-.......|"
"------------------------------------------------------------|"
".######-#########-.C....***-***......C-#####1#######-.......|"
".#.D..#-#..C....#-......*=*-*=*..C....-#...........#-.......|"
".#....#-#.......#-.D....*=*-*=*.......-#...D.......#-.......|"
".##11##-##1##1###-......***-***.......-#############-.C.....|"
"------------------------------------------------------------|"
".##1###-#########-#####1###-#1######1#-##1##.####1#.-####...|"
".#....#-1...A...1-#...C...1-#..C.....#-#...#.#..C.#.-1..#...|"
".#C...#-#.......#-#.......#-#.....D..#-1...#.1....#.-#..#.C.|"
".######-#########-#########-##########-#####.######.-####...|"
	);

  	convert_area ();

   h_pos = 58;
   v_pos = 15;

	add_item (1111, 27, 18, 5);	// schody w dol, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _Downtown;	// kod lokacji docelowej

	add_item (1110, 58, 15, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej

	add_item (1102, 27, 8, 5);					// locked steel door
   item_specials2 [item_id] = 201;			// typ zamka

   /*	bestiariusz (_BAYBARS, startX [6] + 10, startY [6] + 7, -5);
	bestiariusz (_MILITIA_CAPTAIN, 25, 10, -5);
	generuj_potwory (rand () % 2 + 5, _FEMALE_CIVILIAN, -1, 4, -5);	// -1: dowolne miejsce na mapie, 4: tylko sand
*/
}

void generuj_New_York_City_Warzone ()		
{
   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _mutilated_body, _street, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (3, _mutilated_body, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)

	if (!killed_monsters [_Bren_McGuire])
	   monster_na_mapie (_A, _Bren_McGuire, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	if (!killed_monsters [_Pleasence])
	   monster_na_mapie (_B, _Pleasence, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   else
	   monster_na_mapie (_B, _vice_prezio, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

   monster_na_mapie (_C, _MALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_D, _FEMALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_E, _SOLDIER, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_F, _CLASS_Cyborg, _street, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_G, _SOLDIER, _street, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_H, _CLASS_Cyborg, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
".......-.........-.........-..........-.............-.......|"
".######-#########2#########-##########-#############-{{##{{.|"
".#....#-#..C....#2#....C...-#........#2#....D......#-.....#.|"
".###1##-#1######{-#1##{{#1{-#1{{{.{{##-##{{##{1##{{{-#{1{{#.|"
"-------2---G----------G--2------G22-------G----2---------2--|"
".######-#######{{-##################{#-##{{{{###{{##-..C....|"
".#..C.#-#.......{-#####.#.E#E..#.....#-#...3.......{-.{.D...|"
".#....12#....3...-##B##E.......##1#..{-#..D.3C.....1-.{..3..|"
".#.D..#-#...C...{-##.11..##.##1...#..#-............#-..H....|"
".#1####-####1###{-########E.E######{{#-{{{#{###{{{##-....33.|"
"----G---2-2---G---------G--------G-------G----G---2-----2---|"
".######-#####{{##-.C....***-*.*...3.FC-#..##1##{{{#{-.{{....|"
".#.D..#-#..C....{-..33..*=*-*=*..C.3..-#.......3...#-.3H.#..|"
".#....#2#.....3.{-.D....*=*-*=...3.F..-#...D.......{F....H..|"
".##11##-##1##1###-.....3*}}-*}}.......-#{{###{{{###{-.C.....|"
"-----G----2-G-------G----2-----2-G--------G----2-G----2--2--|"
".##1###-######{{{-##.{{1###-#1#{{.##1#-{#1#{.{{{{1#.-##{{.3.|"
".#....#21...A3..1-{...C..312#..C..3..#-....{.#..C.#.-1..{...|"
".#C...#-#.......#-{.......{-#.....D..#-1.....1....{.-{..#.C.|"
".######-######{{{-##{{.{{#{-##{{{{{{{#-#{{#{.##...{.-#.{{...|"
	);

  	convert_area ();

   h_pos = 51;
   v_pos = 18;

	add_item (1111, 51, 18, 5);	// schody w dol, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _Downtown_Mayhem;	// kod lokacji docelowej

/*	add_item (1110, 58, 15, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej*/

	add_item (1102, 27, 8, 5);					// locked steel door
   item_specials2 [item_id] = 201;			// typ zamka

   /*	bestiariusz (_BAYBARS, startX [6] + 10, startY [6] + 7, -5);
	bestiariusz (_MILITIA_CAPTAIN, 25, 10, -5);
	generuj_potwory (rand () % 2 + 5, _FEMALE_CIVILIAN, -1, 4, -5);	// -1: dowolne miejsce na mapie, 4: tylko sand
*/
}

void generuj_Downtown_Mayhem ()		// downtown
{
   plansza_xy (60, 20, _floor);

   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _MEDIKIT, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (3, _mutilated_body, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (4, _remains_from_droid, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)

   monster_na_mapie (_A, _FEMALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _MALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	if (!killed_monsters [_Bavar])
	   monster_na_mapie (_C, _Bavar, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	if (!killed_monsters [_Heisen])
	   monster_na_mapie (_D, _Heisen, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
      
   monster_na_mapie (_E, _SOLDIER, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_F, _CLASS_Cyborg, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
"...........................-........................-.......|"
"----------------------------#{{{{{#..#----------------------|"
".....B..-#.{{{{{#-..E{.....-{3.C.....{-.....E..3....-..A.3..|"
"...3....-...3.#..-.....AE..-{.3..3{..{-............-...3....|"
"....A....###{...1-...3.3...-{......{..-...A...B....-....E...|"
"....B.3.-.4...#.{-.........-#.3....3.#-.........F.........3.|"
"........-##.{{##{-..A.F.....##{..###..-..F...-......-..F....|"
"----.--...-.---.....--.....-...----.......--...--.F..A--..-.|"
"........-............3.........F......-.............-.......|"
"...3..##{.{..E..F-.....B...-....3.....-.F......F........E.3.|"
"......1..31......-..A......-.......E.........B..3...-.......|"
"......#...#...........................-...........F....F....|"
"...#{{##1#{{{#...3.B..3......F.}}**.......3...3.......B..3..|"
".&.{3.{...#.3{...A.........-...*==*...-..........E..........|"
"..&{..1.A.1.3{.......&...{.1#{#{{{{#{#1#{...&..3F...F..A....|"
"&&....{...#..#......&&.{.#...#..3...{...#{..&&......3.......|"
"&&.{##{.{##..{..B...&&.#.#..31.{.1#.1...#.{.&&...E.......F..|"
"&&.&.&#...#.....3....&.#.....#.#.D#.#.....#.&.F....3..A.....|"
"&&&.&.1.A.1.........&&.#..{{{###..###..{{{#.&&..............|"
"..&&&&##{{{&.......&&&&&&&&&&&&#{{{&&&&&&&&&&&&.............|"
	);

  	convert_area ();

   h_pos = 55;
   v_pos = 18;

	add_item (1110, 27, 1, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _New_York_City_Warzone;	// kod lokacji docelowej

	add_item (1110, 55, 18, 5);	// schody w dol, 5 = obstacle
   item_specials1 [item_id] = 2;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;

   monster_char [find_npc (_Bavar)] = -1;
}

void generuj_Downtown ()		// downtown
{
   plansza_xy (60, 20, _floor);

   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _MEDIKIT, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)

   przedmiot_na_mapie (3, _SHIV, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (4, _AXE, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (5, _bullets_9mm, _floor + 100, 3, losuj (5, 7));				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (6, _granates, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (7, _Reza, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (8, _16M, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (9, _Panzor, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)

   monster_na_mapie (_A, _FEMALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _MALE_CITIZEN, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_C, _Bavar, _floor + 100, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_D, _Heisen, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_E, _Gina, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_F, _Moom, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
"...........................-........................-.......|"
"----------------------------##########----------------------|"
"........-########-.........-#$$$$$3$4#-.............-..A....|"
"........-#F.1.#.#-.........-$$C$$$5$6#-............-...B....|"
"....A....####E..1-...B.A...-#$$$$$7$8#-...A........-........|"
"........-#B.1.#.#-.........-##$$$$$$9#-.....................|"
"........-########-..........##########-......-......-.......|"
"----.--...-.---.....--.....-...----.......--...--.....--..-.|"
"........-.............................-.............-.......|"
"......#####......-.....B...-..........-.....................|"
"......1..A1......-..A......-........................-.......|"
"......#...#...........................-.....................|"
"...#####1#####.................****.........................|"
".&.#2.#...#.2#.............-...*==*...-.....................|"
"..&#2.1.A.1.2#.......&...##1##########1##...&..........A....|"
"&&.#2.#...#.2#......&&.###...#......#...###.&&......B.......|"
"&&.#####1#####..B...&&.#.#...1.#11#.1...#.#.&&..............|"
"&&.&.&#...#..........&.#.....#.#.D#.#.....#.&.........A.....|"
"&&&.&.1.A.1.........&&.#########..#########.&&..............|"
"..&&&&#####&.......&&&&&&&&&&&&####&&&&&&&&&&&&.............|"
	);

  	convert_area ();

   h_pos = 27;
   v_pos = 1;

	add_item (1110, 27, 1, 5);	// schody w dol, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _New_York_City;	// kod lokacji docelowej

	add_item (1103, 28, 3, 5);	// drzwi do sklepu
   item_status [item_id] = 1;					// nr drzwi
}

void generuj_Graveyard ()
{
	int i;

   plansza_xy (60, 20, _grass);

   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, 1105, _grass, 5, 1);
   przedmiot_na_mapie (3, 1107, _grass, 5, 1);
   przedmiot_na_mapie (4, 1152, _floor, 5, 1);
   przedmiot_na_mapie (5, _GRAVE, _grass, 5, 1);
   monster_na_mapie (_A, _zombie, _grass, -6);		// A- oznaczenie na mapie
   monster_na_mapie (_B, _Father_Grigori, _floor, -7);

	generuj_floor (0, 0,

 "............................................................|"
 ".##################################################.........|"
 "##..............##&...........................&&&####.......|"
 ".#.5..5..5..5A.5.#&&....#............#........&&&##.........|"
 "##..............##&....###..........###.......&&&#..........|"
 ".#........A......#&&.#######.........#........&&&##.........|"
 "##.5A.5..5..5..5##&....###.........#####......&&&###........|"
 ".#...............#&&....#..........#,4,#......&&&#..........|"
 "##.5..5..5..5..5##&.....#.........##,B,##.....#####.........|"
 ".#....A......A...##########......####1#########...2.........|"
 "##A..............3...............#,,,,,,,##.......2.........|"
 ".#.5..5..5..5..5.##########......#,,,,,,,##.###...2.........|"
 "##...A..........##&.....#........####1#####.#.#####.........|"
 ".#........A...A..#&&....#.................#.#.&&&#..........|"
 "##.5..5..5..5..5##&....###...............##.#.&&&###........|"
 ".#...............#&&.#######................#.&&&##.........|"
 "##....A.........##&....###...............####.&&&#..........|"
 ".#.5..5..5..5..5.#&&....#.....................&&&##.........|"
 "##..............##&&..........................&&&####.......|"
 ".#################################################..........|"
	);

  	convert_area ();

   h_pos = 58;
   v_pos = 18;

	add_item (1110, 58, 18, 5);	// schody, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej

   for (i = 0; i < items_amount; i ++)
   	if (item [i] == 5 && item_group [i] == 55 && losuj (1, 5) > 4)
			item_ident [i] = losuj (1, 8);
}

void generuj_Puerto_Zombico ()
{
   plansza_xy (60, 22, _grass);

   przedmiot_na_mapie (1, 1100, _grass, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (9, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, 1103, _grass, 5, 1);
   przedmiot_na_mapie (3, _bullets_9mm, _floor, 3, 25);
   przedmiot_na_mapie (4, _233, _floor, 3, 25);
   przedmiot_na_mapie (5, _GCDC, _floor, 3, 5);
   przedmiot_na_mapie (6, _16M, _floor, 3, 1);
   przedmiot_na_mapie (7, _toxic_barrel, _grass, 5, 1);
   przedmiot_na_mapie (8, _toxic_barrel, _floor, 5, 1);
   monster_na_mapie (_A, _zombie, _grass, -6);		// A- oznaczenie na mapie
   monster_na_mapie (_B, _Marston, _floor, -7);

	generuj_floor (0, 0,
//012345678901234567890123456789012345678901234567890123456789
 "..#.......#.#...............................#.#.#........#..|"
 ".#.#.....#................#.#.#.#.....#..#.........###...#..|"
 "..#....A...#..#.##.##...........#...AA#............###...A..|"
 "....AA....................#.....#......##....7...A........#.|"
 "..............##..A.#.....#####.....................7.......|"
 "....#.##.##.A.#.....#.................A..A.......7..........|"
 ".......#..#....#...#...A......A..........#............#####.|"
 "...A#...#.#.............................#.#...........,888#.|"
 "...............A...A....#2##.....###.....#..A....7..#,,888#.|"
 "....###.#1#............#...#..###...###.......A.....#,,8.8#.|"
 "...................A....#.....#..AA.................#888,,#.|"
 ".....A.....A...A.......#.##...#...........A.........#888,,#.|"
 "..................................2##............#######9##.|"
 "#####......................A..................A..#53,,,,,,#.|"
 "##.#....#.###.A...#.##.............A.............#64#,,,,,#.|"
 "#.A.2......A#.....#..#...#.#1.#.......#..A.....######,,,,,#.|"
 "####....#.#.#..A....#....#..AA#......##.........299,,,,,#9#.|"
 "........#...#..........A.#........A..##........####,##,##,#.|"
 "........###.....AA.......#.#.##.......#....A.....#,,#555#B#.|"
 "..........#..........#.#.........................##########.|"
 "........#............#.#......#.......#......#..............|"
 "............................................................|"
/*012345678901234567890123456789012345678901234567890123456789*/
	);

  	convert_area ();

   h_pos = 1;
   v_pos = 20;

	add_item (1110, 1, 20, 5);	// schody, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej

	add_item (1102, 52, 13, 5);					// locked steel door
   item_specials2 [item_id] = 13;			// typ zamka
	add_item (1102, 54, 17, 5);					// locked steel door
   item_specials2 [item_id] = 13;			// typ zamka
}

void generuj_Atlantic_Accelerator ()
{
	int kod_o;

   plansza_xy (60, 20, _sea);

   przedmiot_na_mapie (1, 1100, _platform, 5, 1);
   przedmiot_na_mapie (2, _body, _platform, 3, 1);
   przedmiot_na_mapie (3, _bloody_shiv, _platform, 3, 1);
   przedmiot_na_mapie (4, _boat_element_1, _sea, 5, 1);
   przedmiot_na_mapie (5, _boat_element_6, 0, 5, 1);
   przedmiot_na_mapie (6, _boat_element_3, _sea, 5, 1);
   monster_na_mapie (_A, _Bum, _platform, -5);		
   monster_na_mapie (_C, _CLASS_Cyborg, _platform, -7);

	generuj_floor (0, 0,

"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~##########~~~~~~~~~~~~~~~~~~~~~~~~~~~###~~~~~~~~~~~~~~~~~~|"
"~~##:2:::#:#~~~~~~~~~~~~~~~~~~~~~~~~~~~#A#~~~~~~~~~~~~~~~~~~|"
"~~#::##::#:####*****#######~~~~~~~~~~~~#:#~~~~~~~~~~~~~~~~~~|"
"~~#:##2#:::1::::2:::::::::#~~~~~~~~~~~~#:#~~~###~~~~~~~~~~~~|"
"~~#:#3:#:#:######:#######:#:#********#~#:#~~~#:#~~~~~~~~~~~~|"
"~~#2#####::#~~~~#:#~~~~~#:#:#::::::::#~#:#~~~#:#~~~~~~~~~~~~|"
"~~#:#2:2#:##~~~~#:#~~~~~#:#:#:_::::_:#~#:#~~~#:#~~~~~~~~~~~~|"
"~~#:1:C2#::#~~~*#:#######:###:_::::_:###:#####:#~~~~~~~~4~~~|"
"~~#:#2:2##2#~~~*::::::::::::::______::::2:::::::::::::::5~~~|"
"~~#:#####::#~~~*#:#######:###:_::::_:####:####:#~~~~~~~~6~~~|"
"~~#:::::####~~~~#:#~~~~~#:#~#:_::::_:#~~#:#~~#:#~~~~~~~~~~~~|"
"~~#####:::##~~~~#:#~~~~~#:#~#::::::::#~~#:#~~#:#~~~~~~~~~~~~|"
"~~#::::::########:#######:#~#********#~~#:#~~#:#~~~~~~~~~~~~|"
"~~#:2##::#:1:::::::::::2::#~~~~~~~~~~~~~###~~#:######~~~~~~~|"
"~~##:#####:###**######**###~~~~~~~~~~~~~~~~~~#:::::::~~~~~~~|"
"~~#::::::::#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~########~~~~~~~|"
"~~##########~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"

/*012345678901234567890123456789012345678901234567890123456789*/
	);

  	convert_area ();

   h_pos = 56;
   v_pos = 10;

	kod_o = search_obstacle (61, 6);
   item_specials2 [kod_o] = _WORLD;			// kod lokacji docelowej
   item_type [kod_o] = 16;
   item_icon [kod_o] = 62 + kolor_wall;
}

void generuj_Test ()
{
	int i;

   plansza_xy (120, 40, _grass);

   monster_na_mapie (_A, _RAT, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_B, _RAT_KING, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_C, _Salesman, _grass, -5);		// A- oznaczenie na mapie*/
   monster_na_mapie (_D, _CLASS_Cyborg, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_E, _Flint_Westwood, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_F, _SOLDIER, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_G, _zombie, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_H, _SCUMM, _grass, -5);		// A- oznaczenie na mapie
   monster_na_mapie (_I, _Father_Grigori, _grass, -5);		// A- oznaczenie na mapie
//   monster_na_mapie (_C, _Helc, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
//   monster_na_mapie (_D, _Rayo, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (5, 10,

/* "###############AAAAAAAAA..###############|"
 "#..BBBBBBBBBA...#&&....#...&&&#..BBBB...#|"
 "#..BAAAAAAAAA..##&....###..&&&###.AAAAA.%|"
 "#BBBBBBBBBBBB...#&&.%%%%%%%&&&##.BBBBB..%|"
 "#..BBBBBBBBBB..%%&....%%%..&&&#..BBBB...%|"
 "#..AAAABAABAAA..%&&....%....&&##.AAAAAAA%|"
 "#BBBBBBBBBBBBB.%%&&...BBBBB.&&####.BBBB.#|"
 "####AAAAAAAAAAAAAAAAAA....##...CCCCC.####"*/
/* "###############...........###############|"
 "#...............#&&....#...&&&#.........#|"
 "#......E.......##&....###..&&&###.......%|"
 "#...............#&&.%%%%%%%&&&##........%|"
 "#....D.AAAAA...%%&....%%%..&&&#.........%|"
 "#..........E....%&&....%....&&##........%|"
 "#.......DAAAA..%%&&..AAAAA..&&####......#|"
 "####.......AA.D..EAAAAAA..##..BBBB...####"*/
 "*****...***.***.***...............****{{.{*{{{{{{|"
 "*...***...*.....*.*.***....................{````{|"
 "*...*.*.***.....***.*.*....................{``{`{|"
 "*...*.*.............***....................{{{{..|"
 "*A..*.*.............*.*..........................|"
 "*...*.*.............***..........................|"
 "*...***.............***..........................|"
 "*................................................|"
 "*................................................|"
 "*................................................|"
 "*................................................|"
 "*................................................|"
 "************************************.************"
	);

  	convert_area ();
	add_item (1104, 49, 12, 5);
   item_specials2 [item_id] = 10;				// typ zamka

	add_item (_KEY, 35, 11, 3);
	add_item (_B_BAT, 30, 12, 3);
	add_item (_AXE, 31, 12, 3);
	add_item (_SHIV, 32, 12, 3);
	add_item (_HAMMER, 33, 12, 3);
	add_item (_KNIFE, 34, 12, 3);

	add_item (_2KRR, 35, 12, 3);
	add_item (_M119, 36, 12, 3);
	add_item (_6Wayne, 37, 12, 3);

	add_item (_NT9000, 35, 13, 3);
	add_item (_Reza, 36, 13, 3);
	add_item (_16M, 37, 13, 3);
	add_item (_Panzor, 38, 13, 3);
	add_item (_3GM3, 39, 13, 3);

	add_item (_RAGS, 30, 14, 3);
	add_item (_JACKET, 31, 14, 3);
	add_item (_CEVLAR, 32, 14, 3);
	add_item (_COAT, 33, 14, 3);

 	add_item (_ALLOYS, 30, 15, 3);
	add_item (_bullets_9mm, 31, 15, 3);
   item_amount [item_id] = 15;
	add_item (_granates, 32, 15, 3);
   item_amount [item_id] = 5;
	add_item (_357, 33, 15, 3);
   item_amount [item_id] = 15;
	add_item (_233, 34, 15, 3);
   item_amount [item_id] = 10;

 	add_item (_MEDIKIT, 30, 16, 3);
   item_amount [item_id] = 5;
	add_item (_Sealed_package, 31, 16, 3);
	add_item (_tool_box, 32, 16, 3);
	add_item (_high_explosive, 33, 16, 3);
}

void generuj_Old_Remo ()
{
   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, 1106, _floor, 5, 1);
   przedmiot_na_mapie (3, _MEDIKIT, _floor + 110, 3, 1);

   przedmiot_na_mapie (4, _M119, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (5, _6Wayne, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (6, _RAGS, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (7, _JACKET, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (8, _2KRR, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (9, _CEVLAR, _floor + 100, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)

   monster_na_mapie (_A, _Doc, _floor + 110, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _Flint_Westwood, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_C, _Pinkman, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_D, _Salesman, _floor + 100, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_E, _Bartender, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_F, _Priest, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
".................................&&&.&&&&.&&&.&&.&&&........|"
".'''.&#####'''#''''&&.....###...&&#######&&&###########.....|"
".'''.&#...#'''#''''&&....##E##...&#33333#.&.#...#.#.#.#.....|"
"####..##1##'''#''''&&..####.####..#!!!!!#...###2#2#.#.#.....|"
"#..#.&#...#'''#####...##.#.....##.#!!!!!#...###.......#.&...|"
"#..1..1...#&..#...#...##1#......#.###!###...#.2...B.###.&...|"
"####..#####&..#...#...#..1......#.#!A!!!#...####.....##.....|"
"..............#1###...#####1#####.###!###......###1###......|"
"------------------------------------------------------------|"
".&&&&..-....##1##...##1###.....######$######...***....-.&...|"
"..&&&&.-...##...##..#....#.....#$$$$$$$$$$$#...*=*....-.&...|"
"...&&&&-...#.....#..###1##.....#$$$$$$D$$$$#...***....-.....|"
"#*.....-...#.....#..##..##.....#$$$456789$$#..........-.....|"
"#**....-...##.F.##...####......#############...........-....|"
"#^**..-.....##.##....''''..............#######........#1#...|"
"#^^*.-.&&....###.....''''.............##..#..#.......##.##..|"
"#^^^**..&&....#.....&..&...&&...&&...###..#..1......&#...#&.|"
"#^^^^**..&&..###...&&&&&&&&..&&&&.&...##..1..#.'''.&&#.C.#&.|"
"#^^^^^**..&&&.#...&&.&.&&&&.&&&&.&.&&..#######.'''&&&#####&&|"
"#########........&&&&.&&&.&.&&&.&&&&&&............&&.&&&&.&&|"
	);

 	convert_area ();

   h_pos = 58;
   v_pos = 1;

	add_item (1110, 58, 1, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej

	add_item (1111, 4, 15, 5);
   item_specials1 [item_id] = 2;
   item_specials2 [item_id] = _Mines;

	add_item (1100, 52, 4, 5);
   item_type [item_id] = 3;					// closed
   item_specials2 [item_id] = 103;	// typ zamka

	add_item (1103, 37, 9, 5);	// drzwi do sklepu
   item_status [item_id] = 1;					// nr drzwi
}

void generuj_CLASS_Corp ()
{
   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _core64_terminal, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (3, _nomad_body, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   monster_na_mapie (_A, _Shades, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _CLASS_Cyborg, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
"#^^^^^##############^^^^^^^^^^^^^^^^^^^^....................|"
"#^^^^################^^^^############^^..................3..|"
"#^^^##..#...B...#...##^^^#..........#^....3.................|"
"#^^##...#.......#....##^^#......#####..............3........|"
"#^^##...####1####....##^^###..#..#..#.......................|"
"#^##....#.......1.....##^^^#..##.#..#..........3............|"
"#^##....###.....#.....##^^^#...#.#..#####..3.............3..|"
"###.....#.###...###1#..#####.###....#...#...................|"
"##...##1#.#.#...#...#####......######B.B#......3............|"
"######....#.##1##.B.....1..B#B..#.#.##B.............3.......|"
"##2.1...B.1A....1..BBB..1..###......11.B#B..................|"
"######....#.##1##.B.....1..B#B..#.#.##B.......3.............|"
"##...##1#.#.#...#...#####......######B.B#...................|"
"###.....#.###...###1#..#####.###....#...#..............3....|"
"#^##....###.....#.....##^^^#...#.#..#####...3...............|"
"#^##....#.......1.....##^^^#..##.#..#.......................|"
"#^^##...####1####....##^^###..#..#..#.............3.......3.|"
"#^^##...#.......#....##^^#......#####^......................|"
"#^^^##..#...B...#...##^^^#..........#^^.......3.............|"
"#^^^^################################^^^...............3....|"
	);

 	convert_area ();

   h_pos = 58;
   v_pos = 10;

	add_item (1110, 58, 10, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej

	add_item (1100, 5, 10, 5);
   item_specials2 [item_id] = 102;	// typ zamka
}

void generuj_Shelter_Tec ()
{
   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _water_purifier, _water, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (3, _water_purifier_terminal, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   monster_na_mapie (_A, _MALE_NOMAD, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _FEMALE_NOMAD, _floor, -5);		// B- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_C, _Wise_Arse, _floor, -5);		// B- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
"##############################.......&&.......&.............|"
"##############################=============&&....&&&...&.==.|"
"##==============222############....&....&&======..&..&.====.|"
"##........#####1####........####............A..=========....|"
"##1######1#####1####.#####..#####...B...........&&.....&....|"
"##.#...#C...#.....##....##..######.....&....................|"
"##.#...#....#.....####.###..#####..........&...&.........&..|"
"##.#...1....1.....###..##...####...................B........|"
"##.#...#....##+#####..##..#####....A......A......&..........|"
"##.#####.....#..###..##..#######A............&..............|"
"##.#.........1....1.##..##..1.1......&................&.....|"
"##.#.....#...#..#####..###..####A.........&....&...&........|"
"##.#.....#...#1#####..####..###......A......................|"
"##1###########....##.#####..####............................|"
"##.##..1..........##.#####..#####..........&....B.....&.....|"
"##.##..#..........##.#####..######....&&....................|"
"##1#####1##1##1##1##..###..######.................&.........|"
"##1###...#...#..#.###..#..######.....&...A...........B......|"
"##.3##...##1##..#.####...######..............&...........&..|"
"###############################..................&&&&.......|"
	);

 	convert_area ();

   h_pos = 58;
   v_pos = 10;

	add_item (1110, 58, 10, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej
}

void generuj_Mines ()
{
	int dlX [3], dlY [3], startX [10], startY [10], dom, i, j, x, y;

   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _ALLOYS, _floor, 3, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   monster_na_mapie (_A, _RAT, _floor, -6);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _RAT_KING, _floor, -6);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_C, _Helc, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_D, _Rayo, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
"^^^^^^^^^^^^^^^^^^^####^####^^^^^^^^^^^^#^^^^^^^^^^^^^^^^^##|"
"^***#^^^^^#######^^^##^^^##^^#######^^^^^#^^^^^^^^^^^^^^^###|"
"^#..##^^###.....#^^^^##^##^^^#...A.*^^^^^^#^^^^^^^^^^^^^#^##|"
"^##..#^^#.2.##..###^^^###^^^^*.###A**#####^#^^#^^^#^^^##^^^#|"
"^^##.#^^#...##....#^^^^#^^^^^*.#^#...AA..##^####^###^##^^^^^|"
"^^^#.#^^###.##....#^^^^^^^^^^*A#########.A##^#########^^^^^^|"
"^^^#.##^^^#.##..###^^^^^^^^^^#....####^##.A##^#######^^^^^^^|"
"^^^#..##^^#.##..#^^^^^^^^^^^^###.....#^^##..#^^#####^^^^^^^^|"
"^^^##..##^#.#..##^^^^^^^^^^##^####...#^^^##A#^^^###^^^^^^^^^|"
"^^^^##..#^#.#..##^^####^^#######^#.###^^^^#.#^^^^#^^^^^^^^^^|"
"^^^^^#..#^#.#..#####..####....##^#.#^^^^^^#.#^^^^^^^^^^^^^^^|"
"^^^^^*..###.#.####.......#..D.##^#.#^^^^^^#A#^^^^^^^^^^^^^^^|"
"^^^^^*......#.#^#..#####.......#^#.#^^^^^^#.#######^^^^^^^^#|"
"#^^^^***##..#.#^#..#^^#####.####^#.#^^^^^^#A##....#**^^^^^##|"
"##*^^^^^^#.##.#^#.##^^^^^##.#^^###.#^^^^^^#..B......*^^^^#^^|"
"#^**^^^^^####.###.*^^^#^^^#.#^^##..#^^^^^^####...C..#^^^#^^^|"
"#^^**^^^^^^^#.....*^^#^#^^*.####...*^^^^^^^^^#......#^^#^^^^|"
"#^^^*#^^^^^^#******^#^^^#^*.......**^^^^^^^^^#....###^#^^^^^|"
"#^^^^##^^^^^^^^^^^^#^^^^^#######***^^^^^^^^^^######^^#^^^^^^|"
"#^^^^^##^^^^^^^^^^#^^^^^^^#^^^^^^^^^^^^^^^^^^^^^^^^^#^^^^^^^|"
	);

 	convert_area ();

   h_pos = 2;
   v_pos = 2;

   monster_hp [find_npc (_Helc)] -= 20;

	add_item (1110, 2, 2, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _Old_Remo;	// kod lokacji docelowej
}

void generuj_Marina_Harbour ()
{
   plansza_xy (60, 20, _floor);
   przedmiot_na_mapie (1, _boat_element_1, _sea, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (2, _boat_element_2, _sea, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (3, _boat_element_3, _sea, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (4, _boat_element_4, _sea, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (5, _boat_element_5, _sea, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (6, _boat_element_6, 0, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (7, 1100, _floor, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   przedmiot_na_mapie (8, 1100, _floor + 100, 5, 1);				// 1- nr oznaczenia na mapie, 1100- kod przedmiotu (drzwi), 2- kod floor'a, 5- obstacle (tu: drzwi)
   monster_na_mapie (_A, _D_Morgan, _floor, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_B, _MALE_NOMAD, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_C, _FEMALE_NOMAD, _floor, -5);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)
   monster_na_mapie (_D, _Jack, _floor + 100, -7);		// A- oznaczenie na mapie, 4 - kod floor'a, stone floor)

	generuj_floor (0, 0,
/*12345678901234567890123456789012345678901234567890123456789*/
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~1####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~67A.#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~~~~~~~~3#..#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~45~~~~~~##7#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~~~~~~~22~~~~~~#..#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~~~~~~~11~~~~22~~~~~~#7##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|"
"~~~~~~~1~~~~~22~~~~22~~~****..*~*~*~*~*~*~*~*~*~*~*~*~*~**##|"
"~~~~~~~2~~~~~22~~~~22~~**&&.....................B.......&&##|"
"*******3~****33****54****.........#&...B........###########.|"
"**&&&&****&&****&&****............#&&&......C...#$$$#$$$$$#.|"
"..........B..C..............C.....#&&&&&........$$D$#$$$$$#.|"
"..B...&...........................####..........#$$$8$$$$$#.|"
"...............&................................###########.|"
"............................................................|"
	);

 	convert_area ();

   h_pos = 29;
   v_pos = 18;

	add_item (1110, 29, 18, 5);	// schody w gore, 5 = obstacle
   item_specials1 [item_id] = 1;					// nr porz. schodow
   item_specials2 [item_id] = _WORLD;	// kod lokacji docelowej

	add_item (1103, 48, 16, 5);	// drzwi do sklepu
   item_status [item_id] = 1;					// nr drzwi
}

void generuj_plansze_wilderness (int lgr, int gr, int pgr, int lr, int sr, int pr, int ldr, int dr, int pdr)
{
	int a, b, c, d, e, f, i, j, x, y;
	int floor_type;
   char current = 0;
   int level_part [9];

	level_part [0] = sr;
	level_part [1] = lgr;
	level_part [2] = gr;
	level_part [3] = pgr;
	level_part [4] = lr;
	level_part [5] = pr;
	level_part [6] = ldr;
	level_part [7] = dr;
	level_part [8] = pdr;

   for (; current < 9; current ++)
   {
		if (level_part [current] == 154)					// river/lake
   		floor_type = 21;
	   else if (level_part [current] == 150 || level_part [current] == 1150)			// ocean
      	floor_type = 24;
      else if (level_part [current] == 151)			// extremally high and bold mountain
      	floor_type = 25;
      else if (level_part [current] == 152)			// mountains
      	floor_type = 26;
      else if (level_part [current] == 49)			// very high mountains
      	floor_type = 49;
      else if (level_part [current] == 2)				// stone floor
      	floor_type = 2;
      else if (level_part [current] == 153)			// ice
      	floor_type = 22;
      else if (level_part [current] == 155)			// ice covered mountain (just need a special equipment to climb)
      	floor_type = 27;
      else if (level_part [current] == 156)			// road
      	floor_type = 28;
      else if (level_part [current] == 157)			// ice earth
      	floor_type = 29;
      else if (level_part [current] == 159)			// bush (random trees)
      	floor_type = 1;
      else if (level_part [current] == 161)	// extremally lava mountains
      	floor_type = 41;
      else if (level_part [current] == 162)			// lava covered mountain (just need a special equipment to climb)
      	floor_type = 42;
      else if (level_part [current] == 163)			// lava
      	floor_type = 23;
      else if (level_part [current] == 164)			// pustynia
      	floor_type = 4;
      else if (level_part [current] == 158)			// hills
      	floor_type = 1;
      else
      	floor_type = 4;

      if (!current)	// generuj srodek planszy
      {
      	if (floor_type == 21 || floor_type == 26)
         	exit_ability = 1;
         else
         	exit_ability = 0;

         for (a = 0; a < (x_planszy = 60); a ++)
         	for (b = 0; b < (y_planszy = 20); b ++)
            	floor_planszy [a] [b] = floor_type;
      }
		else if (current == 1)	// lewy gorny rog
      {
      	d = 6;

         for (a = 0; a < 2; a ++)
         	for (b = 0; b < d; b ++)
            	floor_planszy [a] [b] = floor_type;

			for (a = 2; a < 10; a ++)
         {
         	d += rand () % 3 - 1;

            if (d > 6)
            	d = 6;

            if (d < 2)
            	d = 2;

         	for (b = 0; b < d; b ++)
            	floor_planszy [a] [b] = floor_type;
         }
      }
      else if (current == 2)	// gora planszy
      {
      	d = 3;

         for (a = 10; a < 50; a ++)
         {
         	d += rand () % 3 - 1;

            if (d > 6)
            	d = 6;

            if (d < 2)
            	d = 2;

            for (b = 0; b < d; b ++)
            	floor_planszy [a] [b] = floor_type;
         }
      }
      else if (current == 3)	// prawy gorny rog
      {
      	d = 6;

         for (a = 58; a < 60; a ++)
         	for (b = 0; b < d; b ++)
            	floor_planszy [a] [b] = floor_type;

         for (a = 59; a > 49; a --)
         {
         	d += rand () % 3 - 1;

            if (d > 6)
            	d = 6;

            if (d < 2)
            	d = 2;

            for (b = 0; b < d; b ++)
            	floor_planszy [a] [b] = floor_type;
         }
      }
      else if (current == 4)	// lewica planszy
      {
      	d = 3;

         for (b = 6; b < 14; b ++)
         {
         	d += rand () % 3 - 1;

            if (d > 10)
            	d = 10;

            if (d < 3)
            	d = 3;

            for (a = 0; a < d; a ++)
            	floor_planszy [a] [b] = floor_type;
         }
      }
      else if (current == 5)	// prawica planszy
      {
      	d = 3;

         for (b = 6; b < 14; b ++)
         {
         	d += rand () % 3 - 1;

            if (d > 10)
            	d = 10;

            if (d < 3)
            	d = 3;

            for (a = 0; a < d; a ++)
            	floor_planszy [59 - a] [b] = floor_type;
         }
      }
		else if (current == 6)	// lewy dolny rog
      {
      	d = 6;

         for (a = 0; a < 2; a ++)
         	for (b = 19; b > 19 - d; b --)
            	floor_planszy [a] [b] = floor_type;

			for (a = 2; a < 10; a ++)
         {
         	d += rand () % 3 - 1;

            if (d > 6)
            	d = 6;

            if (d < 2)
            	d = 2;

         	for (b = 19; b > 19 - d; b --)
            	floor_planszy [a] [b] = floor_type;
         }
      }
      else if (current == 7)	// dol planszy
      {
      	d = 3;

         for (a = 10; a < 50; a ++)
         {
         	d += rand () % 3 - 1;

            if (d > 6)
            	d = 6;

            if (d < 2)
            	d = 2;

            for (b = 19; b > 19 - d; b --)
            	floor_planszy [a] [b] = floor_type;
         }
      }
		else if (current == 8)	// prawy dolny rog
      {
      	d = 6;

         for (a = 59; a > 57; a --)
         	for (b = 19; b > 19 - d; b --)
            	floor_planszy [a] [b] = floor_type;

			for (a = 59; a > 49; a --)
         {
         	d += rand () % 3 - 1;

            if (d > 6)
            	d = 6;

            if (d < 2)
            	d = 2;

         	for (b = 19; b > 19 - d; b --)
            	floor_planszy [a] [b] = floor_type;
         }
      }
   }

//	generuje drzewa i krzaki
	for (i = 0; i < y_planszy; i ++)
	{
		for (j = 0; j < x_planszy; j ++)
		{
			if (floor_planszy [j] [i] == 1)
         {
	         if (rand () % 1000 < 50)
   	      {
      	   	char a = rand () % 5;

	            if (!a)
			         floor_planszy [j] [i] = 6;
      	      else if (a == 1)
			         floor_planszy [j] [i] = 7;
					else if (a == 2)
			         floor_planszy [j] [i] = 8;
					else if (a == 3)
		   	      floor_planszy [j] [i] = 9;
					else
			         floor_planszy [j] [i] = 10;
	         }

            if (rand () % 100 < 10)
            	floor_planszy [j] [i] = 5;

            if (h_pos == j && v_pos == i)
            	floor_planszy [j] [i] = 1;
         }
		}
	}

   convert_area ();
}

void generuj_dungeon (int floor_type, char stairs_amount, char liczba_pokoi)
{
	int k, a, j, i, b;
	int pok_in = 0, pok_out = 0;
	int lgc_h [8];
	int lgc_v [8];
	int startX [8];
	int startY [8];
	int dlX, dlY;
	int radius, center_x, center_y;

   x_planszy = 100;
   y_planszy = 40;

   switch (floor_type)
   {
   	case 1:
      case 2:
      	kolor_wall = 2048;
         break;
      case 3:
      	kolor_wall = 1536;
         break;
      case 4:
      	kolor_wall = YELLOW;
         break;
   }

   kolor_floor = kolor_wall;

   for (j = 0; j < y_planszy; j ++)
   	for (k = 0; k < x_planszy; k ++)
      	floor_planszy [k] [j] = floor_type + 10;

	if (!liczba_pokoi)
		liczba_pokoi = rand () % 5 + 4;

	j = 0;

	if (liczba_pokoi < 8)
		j = 10;

	if (liczba_pokoi == 4)
		j = 15;

	for (i = 0; i < liczba_pokoi / 2; i ++)	// lewy gorny rog pokoju
	{
		lgc_h [i] = rand () % 3 + 2 + j;
		lgc_v [i] = rand () % 2 + 2;
		j += 15;
	}

	j = 0;

	if (liczba_pokoi < 7)
		j = 7;

	if (liczba_pokoi == 4)
		j = 15;

	i = liczba_pokoi / 2;
	k = liczba_pokoi;

	for (; i < k; i ++)
	{
		lgc_h [i] = rand () % 3 + 2 + j;
		lgc_v [i] = rand () % 2 + 11;
		j += 15;
	}

	for (k = 0; k < liczba_pokoi; k ++)		// tworzy pomieszczenia
	{
		if (rand () % 3)
		{
			dlX = rand () % 6 + 4;
			dlY = rand () % 2 + 4;
			startX [k] = dlX / 2 + lgc_h [k];
			startY [k] = dlY / 2 + lgc_v [k];

			for (i = 0; i < dlY; i ++)
				for (j = 0; j < dlX; j ++)
					floor_planszy [lgc_h [k] + j] [lgc_v [k] + i] = floor_type;
		}
		else
		{
			radius = (rand () % 3 + 4) / 2;
			center_x = lgc_h [k] + radius;
			center_y = lgc_v [k] + radius;
			startX [k] = rand () % radius + center_x - radius / 2 + 1;
			startY [k] = rand () % radius + center_y - radius / 2;

			for (i = 0; i < y_planszy; i ++)
				for (j = 0; j < x_planszy; j ++)
					if (sqrt (pow (center_x - j, 2) + pow (center_y - i, 2)) - 0.5 < radius)
						floor_planszy [j] [i] = floor_type;
		}
	}

/*	for (a = 0; a < liczba_pokoi; a ++)
		for (i = 0; i < y_planszy; i ++)
			for (j = startX [a]; j < startX [a + 1]; j ++)
				if (i == (j - startX [a]) * (startY [a + 1] - startY [a]) / (startX [a + 1] - startX [a]) + startY [a])
					floor_planszy [j] [i] = floor_type;
*/
   debug (101, 100, -1, 1);

	b = rand () % 2;

	if (b)
	{
		a = 0;
		b = 3;
	}

	switch (liczba_pokoi)
	{
		case 4:
			if (!b)
			{
				a = 2;
				b = 1;
			}
			break;
		case 5:
			if (!b)
			{
				a = 1;
				b = 4;
			}
			break;
		case 6:
			if (b)
			{
				a = 0;
				b = 4;
			}
			else
			{
				a = 4;
				b = 2;
			}
			break;
		case 7:
			if (b)
			{
				a = 5;
				b = 2;
				startX [5] -= 2;
				startX [2] += 2;
			}
			else
			{
				a = 3;
				b = 0;
				startX [3] -= 2;
				startX [0] += 2;
			}
			break;
		case 8:
			if (b)
			{
				a = 0;
				b = 5;
			}
			else
			{
				a = 6;
				b = 3;
				startX [6] -= 2;
			}
			break;
	}

	for (i = 0; i < y_planszy; i ++)
		for (j = startX [a]; j <= startX [b]; j ++)
			if (i == (j - startX [a]) * (startY [b] - startY [a]) / (startX [b] - startX [a]) + startY [a])
				floor_planszy [j] [i] = floor_type;

	for (i = 0; i < y_planszy; i ++)
		for (j = 0; j < x_planszy; j ++)
			if (floor_planszy [j] [i] != floor_type && floor_planszy [j - 1] [i] == floor_type &&
         	floor_planszy [j - 1] [i - 1] != floor_type && floor_planszy [j] [i - 1] == floor_type ||
            floor_planszy [j] [i] != floor_type && floor_planszy [j + 1] [i] == floor_type &&
            floor_planszy [j] [i - 1] == floor_type && floor_planszy [j + 1] [i - 1] != floor_type)
					floor_planszy [j] [i] = floor_type;

	while (pok_in == pok_out)
	{
		pok_in = rand () % liczba_pokoi;
		pok_out = rand () % liczba_pokoi;
	}

  	ekwipunek (1110, -5, 5);
	h_pos_item [item_id] = startX [pok_in];
	v_pos_item [item_id] = startY [pok_in];

	if (!stairs_amount)
   {
	  	ekwipunek (1111, -5, 5);
		h_pos_item [item_id] = startX [pok_out];
		v_pos_item [item_id] = startY [pok_out];
   }

   convert_area ();
}

void generuj_elipse ()
{
	int i, j, k;
	int radius_a = rand () % 3 + 9;
	int radius_b = rand () % 2 + 4;
	int center_x = 27 + rand () % 5;
	int center_y = 8 + rand () % 3;

/*  	generuj_plansze_wilderness (floor_planszy [h_pos_world - 1] [v_pos_world - 1], floor_planszy [h_pos_world] [v_pos_world - 1], floor_planszy [h_pos_world + 1] [v_pos_world - 1],
		floor_planszy [h_pos_world - 1] [v_pos_world], 159, floor_planszy [h_pos_world + 1] [v_pos_world],
      floor_planszy [h_pos_world - 1] [v_pos_world + 1], floor_planszy [h_pos_world] [v_pos_world + 1], floor_planszy [h_pos_world + 1] [v_pos_world + 1]);*/

	for (k = 0; k < 5; k ++)
   {
		for (i = 0; i < y_planszy; i ++)
      {
			for (j = 0; j < x_planszy; j ++)
         {
		   	if (!k) // otoczka areny
      		{
					if (pow (j - center_x, 2) / pow (radius_a + 1, 2) + pow (i - center_y, 2) / pow (radius_b + 1, 2) - 0.5 < 1)
						floor_planszy [j] [i] = 4;		// sand
		      }
		      else if (k == 1)
		      {
					if (pow (j - center_x, 2) / pow (radius_a, 2) + pow (i - center_y, 2) / pow (radius_b, 2) - 0.5 < 1)
						floor_planszy [j] [i] = 52;	// twardy mur
		      }
		      else if (k == 2)
      		{
					if (pow (j - center_x, 2) / pow (radius_a - 1, 2) + pow (i - center_y, 2) / pow (radius_b - 1, 2) - 0.5 < 1)
						floor_planszy [j] [i] = 2;		// posadzka
		      }
		      else if (k == 3)
      		{
					if (floor_planszy [j] [i] != 52 && floor_planszy [j - 1] [i] == 52 &&
      		   	floor_planszy [j - 1] [i - 1] != 52 && floor_planszy [j] [i - 1] == 52 ||
            		floor_planszy [j] [i] != 52 && floor_planszy [j + 1] [i] == 52 &&
		            floor_planszy [j] [i - 1] == 52 && floor_planszy [j + 1] [i - 1] != 52)
							floor_planszy [j] [i] = 52;
		      }
			}
      }
   }

   floor_planszy [center_x] [center_y] = 21;				// water
  	floor_planszy [center_x + 2] [center_y] = 23;		// lava
	convert_area ();

	bestiariusz (1010, center_x, center_y + radius_b + 2, -6);		// arena master
}

void generuj_water_dungeon ()
{
	int a, b, c;

	for (a = 0; a < x_planszy; a ++)
   	for (b = 0; b < y_planszy; b ++)
      	floor_planszy [a] [b] = 16;

	c = rand () % 3 + 1;

   if (c == 3)
   {
   	floor_planszy [rand () % 5 + 15] [rand () % 14 + 3] = 1;
   	floor_planszy [rand () % 5 + 30] [rand () % 14 + 3] = 1;
   	floor_planszy [rand () % 5 + 45] [rand () % 14 + 3] = 1;
   }

	a = rand () % 5 + 3;
   b = rand () % 14 + 3;
  	ekwipunek (1110, -5, 5);				// '<'
	h_pos_item [item_id] = a;
	v_pos_item [item_id] = b;
	a = rand () % 5 + 50;
   b = rand () % 14 + 3;
  	ekwipunek (1111, -5, 5);				// '>'
	h_pos_item [item_id] = a;
	v_pos_item [item_id] = b;
}

void generuj_triangle ()
{
	int i, j;
   int x1, x2, x3, y1, y2, y3;
   kolor_floor = kolor_wall = 2048;

   x1 = rand () % 10 + 2;
   y1 = rand () % 7 + 12;
   x2 = rand () % 11 + 20;
   y2 = rand () % 3 + 2;
   x3 = rand () % 10 + 48;
   y3 = rand () % 7 + 12;
   y_planszy = 20;
   x_planszy = 60;

	for (i = 0; i < y_planszy; i ++)
		for (j = 0; j < x_planszy; j ++)
      {
			if ((i >= (y2 - y1) * (j - x1) / (x2 - x1) + y1) && (i >= (y3 - y2) * (j - x2) / (x3 - x2) + y2) && (i < (y1 - y3) * (j - x3) / (x1 - x3) + y3))
         	floor_planszy [j] [i] = 2;
         else
         	floor_planszy [j] [i] = 12;
   	}

   convert_area ();
  	ekwipunek (1110, -5, 5);
   h_pos_item [item_id] = 30;
   v_pos_item [item_id] = 10;

/*	while (stan_planszy [h_pos_item [item_id]] [v_pos_item [item_id]] && floor_planszy [h_pos_item [item_id]] [v_pos_item [item_id]] != 2)
   {
		h_pos_item [item_id] = rand () % (x_planszy - 2) + 1;
		v_pos_item [item_id] = rand () % (y_planszy - 2) + 1;
   }*/
}

void plansza_xy (int x_size, int y_size, int kod_f)
{
	int i, j;

   for (i = 0; i < (x_planszy = x_size); i ++)
   	for (j = 0; j < (y_planszy = y_size); j ++)
      	floor_planszy [i] [j] = kod_f;		// 2 = stone floor
}
