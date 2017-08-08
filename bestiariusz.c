#include "deklaracje.h"

void enter_monster (int kod, char pl, int ltr, char amnt)
{
	switch (kod)
   {
   	case 1:
         messages ("Rat", ltr, pl);
      	break;
   	case 2:
         messages ("Mutated rat", ltr, pl);
      	break;                                                                  
   	case 3:
         messages ("Mutated rat leader", ltr, pl);
      	break;
   	case 4:
         messages ("Rat king", ltr, pl);
      	break;
   	case 20:
         messages ("Snake", ltr, pl);
      	break;
      case 50:
      	messages ("Red ant", ltr, pl);
         break;
      case _WILD_DOG:
      	messages ("Wild dog", ltr, pl);
         break;
      case _JACKAL:
      	messages ("Jackal", ltr, pl);
         break;
   	case 60:
      	if (!amnt)
	         messages ("Wolf", ltr, pl);
         else
         	messages ("Wolves", ltr, pl);
      	break;
   	case 61:
      	if (!amnt)
	         messages ("Old Wolf", ltr, pl);
         else
         	messages ("Old Wolves", ltr, pl);
      	break;
      case 80:
      	messages ("Spider", ltr, pl);
         break;
      case 100:
      	messages ("Kobold", ltr, pl);
         break;
      case 110:
      	messages ("Orc", ltr, pl);
         break;
      case _zombie:
      	messages ("Zombie", ltr, pl);
         break;
      case _ISLAM_BASHER:
      	messages ("Islam basher", ltr, pl);
         break;
      case _TEMPLAR:
      	messages ("Templar", ltr, pl);
         break;
      case _MILITIA:
      	messages ("Militia", ltr, pl);
         break;
      case _MILITIA_ARCHER:
      	messages ("Militia archer", ltr, pl);
         break;
      case _BANDIT:
      	messages ("Bandit", ltr, pl);
         break;
      case _MILITIA_CAPTAIN:
      	messages ("Sharif ibn Saha, militia captain", 0, pl);
         break;
      case _MALE_CIVILIAN:
      	messages ("Male civilian", ltr, pl);
         break;
      case _MALE_CIVILIAN_OLD:
      	messages ("Old male civilian", ltr, pl);
         break;
      case _FEMALE_CIVILIAN:
      	messages ("Female civilian", ltr, pl);
         break;
      case _MALE_CITIZEN:
      	messages ("Male citizen", ltr, pl);
         break;
      case _FEMALE_CITIZEN:
      	messages ("Female citizen", ltr, pl);
         break;
      case _MALE_NOMAD:
      	messages ("Male nomad", ltr, pl);
         break;
      case _ARMED_NOMAD:
      	messages ("Armed nomad", ltr, pl);
         break;
      case _JUNKIE:
      	messages ("Junkie", ltr, pl);
         break;
      case _SCUMM:
      	messages ("Scumm", ltr, pl);
         break;
      case _HENCHMEN:
      	messages ("Henchmen", ltr, pl);
         break;
      case _FEMALE_NOMAD:
      	messages ("Female nomad", ltr, pl);
         break;
      case _FEMALE_CIVILIAN_OLD:
      	messages ("Old female civilian", ltr, pl);
         break;
      case _SOLDIER:
      	messages ("Soldier", ltr, pl);
         break;
      case _Gina:
      	messages ("Gina", ltr, pl);
         break;
      case _PRIEST:
      	messages ("Priest", ltr, pl);
         break;
      case _TEMPLAR_LEADER:
      	messages ("Templar leader", ltr, pl);
         break;
      case _Bren_McGuire:
      	messages ("Bren McGuire", 0, pl);
         break;
      case _Pleasence:
      	messages ("Pleasence, president of NEW YORK CITY", 0, pl);
         break;
      case _vice_prezio:
      	messages ("Opama, vice-president of NEW YORK CITY", 0, pl);
         break;
      case _Heisen:
      	messages ("Heisen, drug lord", 0, pl);
         break;
      case _Jack:
      	messages ("Jack, shopkeeper boatman", 0, pl);
         break;
      case _D_Morgan:
      	messages ("D'Morgan", 0, pl);
         break;
      case 1000:
      	messages ("Baybars, General Sultan of Kutuzu", 0, pl);
         break;
      case _Father_Grigori:
      	messages ("Father Grigori", 0, pl);
         break;
      case _Wise_Arse:
      	messages ("Wise Arse, eldery nomad", 0, pl);
         break;
      case 1002:
      	if (quest [1] == 1)		// niezidentyfikowana
         	messages ("Female civilian", ltr, pl);
         else
	      	messages ("Chardashka, black widow", 0, pl);
         break;
      case 1003:
      	messages ("Hasrinaxx, human druid", 0, pl);
         break;
      case 1004:
      	messages ("Krev, human sage", 0, pl);
         break;
      case 1005:
      	messages ("Mohammed Hallash, human master assassin", 0, pl);
         break;
      case _Pinkman:
      	messages ("Pink, drug lord wannabe", 0, pl);
         break;
      case _Bum:
      	messages ("Bum, the nomad male hobo", 0, pl);
         break;
      case _Flint_Westwood:
      	messages ("Flint Westwood", 0, pl);
         break;
      case _Salesman:
      	messages ("Mustacho, salesman", 0, pl);
         break;
      case _Priest:
      	messages ("Carl, priest", 0, pl);
         break;
      case _Doc:
      	messages ("Doc, owner of drug store", 0, pl);
         break;
      case _Moom:
      	messages ("Moom, pleasure cyborg", 0, pl);
         break;
      case _CLASS_Cyborg:
      	messages ("Boolfrog, CLASS Cyborg", 0, pl);
         break;
      case _Shades:
      	messages ("Shades, CLASS megamind", 0, pl);
         break;
      case _Bavar:
      	messages ("Bavar, \"Bavarian Most Wanted\" shopkeeper", 0, pl);
         break;
      case _Marston:
      	messages ("Marston, male insane soldier", 0, pl);
         break;
      case _Bartender:
      	messages ("Bob, bartender", 0, pl);
         break;
      case _Helc:
      	messages ("Remains of Helc, brother of Rayo", 0, pl);
         break;
      case _Rayo:
      	messages ("Rayo", 0, pl);
         break;
   }
}

void bestiariusz (int kod_potwora, int x_pos, int y_pos, int usposobienie)
{
	switch (kod_potwora)
	{
      case _MUTATED_RAT:
			monster_stats ('r' + GREEN, kod_potwora, 5, 20, 10, 10, 10, 50, 1, -1);
         break;
      case _MUTATED_RAT_LEADER:
      	monster_stats ('r' + DARK_GREEN, kod_potwora, 5, 50, 15, 20, 15, 100, 1, -1);
         break;
		case _SNAKE:
			monster_stats ('s' + BLUE, kod_potwora, 5, 10, 5, 10, 5, 80, 1, -1);
			break;
		case _RED_ANT:
			monster_stats ('a' + RED, kod_potwora, 5, 5, 5, 7, 5, 70, 1, -1);
			break;
		case _WOLF:
			monster_stats ('d' + GRAY, kod_potwora, 7, 10, 5, 4, 108, 50, 1, -1);
			break;
		case _WILD_DOG:
			monster_stats ('d' + GRAY, kod_potwora, 7, 10, 5, 4, 106, 50, 1, -1);
			break;
		case _JACKAL:
			monster_stats ('d' + DARK_GRAY, kod_potwora, 7, 15, 5, 4, 106, 50, 1, -1);
			break;
		case _OLD_WOLF:
			monster_stats ('d' + DARK_GRAY, kod_potwora, 5, 25, 4, 4, 10, 50, 1, -1);
			break;
      case _SPIDER:
      	monster_stats ('S' + BLUE, kod_potwora, 5, 20, 5, 10, 5, 20, 30, -1);
         break;
      case _ISLAM_BASHER:
      	monster_stats ('h' + YELLOW, kod_potwora, 5, 20, 5, 5, 112, 5, 5, -1);		// praworzadny neutralny
         break;
      case _TEMPLAR:
      	monster_stats ('h' + GRAY, kod_potwora, 5, 20, 5, 5, 106, 5, 5, -1);
         break;
      case _MILITIA_ARCHER:
      	monster_stats ('h' + CYAN, kod_potwora, 5, 20, 5, 5, 106, 200, 5, -1);
         break;
      case _BANDIT:
      	monster_stats ('b' + YELLOW, kod_potwora, 5, 20, 5, 5, 106, 10, 5, -1);
         break;
      case _MILITIA_CAPTAIN:
      	monster_stats ('h' + DARK_GRAY, kod_potwora, 7, 20, 5, 5, 306, 5, 5, -1);
         break;
      case _MALE_CIVILIAN:
      	monster_stats ('h' + CYAN, kod_potwora, 5, 20, 5, 5, 106, 5, 5, -1);
         break;
      case _MALE_CIVILIAN_OLD:
      	monster_stats ('h' + CYAN, kod_potwora, 5, 20, 5, 5, 104, 5, 5, -1);
         break;
      case _FEMALE_CIVILIAN_OLD:
      	monster_stats ('h' + RED, kod_potwora, 5, 20, 5, 5, 104, 5, 5, -1);
         break;
      case _CHARDASHKA:
      	monster_stats ('h' + RED, kod_potwora, 5, 20, 5, 5, 206, 5, 5, -1);
         break;
      case _PRIEST:
      	monster_stats ('h' + DARK_RED, kod_potwora, 5, 20, 5, 5, 106, 5, 5, -1);
         break;
      case _TEMPLAR_LEADER:
      	monster_stats ('h' + VIOLET, kod_potwora, 7, 20, 5, 5, 106, 5, 5, -1);
         break;
      case _BAYBARS:
      	monster_stats ('@' + 1280, kod_potwora, 8, 500, 10, 10, 306, 100, 50, -1);
         break;

		case _RAT:
			monster_stats ('r' + GRAY, kod_potwora, 	5, 		5, 			5, 		5, 	 	4, 		40, 		1, 		-1);
			break;
      case _RAT_KING:
			monster_stats ('r' + GREEN, kod_potwora, 	7, 		20, 			10, 		2, 	 	8, 		50,      1,       -1);
         break;
      case _zombie:		// icon       code		speed    health		hit		dv			dmg		exp		pp			char
      	monster_stats ('z' + GRAY, kod_potwora, 	4, 		20, 			5, 		2, 		5, 		5, 		20, 		-1);
         monster_alignment [monster_id] = -5;
         break;
      case _FEMALE_CITIZEN:
      	monster_stats ('t' + RED, 	kod_potwora, 	5, 		20, 			5, 		5, 		5, 		5, 		20, 		-1);
         break;
      case _MALE_CITIZEN:
      	monster_stats ('t' + BLUE, kod_potwora, 	5, 		20, 			5, 		5, 		5, 		5, 		20, 		-1);
         break;
      case _FEMALE_NOMAD:
      	monster_stats ('t' + DARK_RED, kod_potwora, 	5,  	10, 			5, 		1, 		3, 		5, 		20, 		-1);
         break;
      case _MALE_NOMAD:
      	monster_stats ('t' + DARK_BLUE, kod_potwora, 5, 		10, 		 5, 		5, 		5, 		5, 		20, 		-1);
         break;
      case _ARMED_NOMAD:
      	monster_stats ('t' + DARK_BLUE, kod_potwora, 5, 		15, 		 5, 		2, 		6, 		5, 		20, 		-1);
         break;
      case _JUNKIE:
      	monster_stats ('t' + BLUE, kod_potwora, 		5, 		5, 		 5, 		2, 		1, 		5, 		20, 		-1);
         break;
      case _SCUMM:
      	monster_stats ('t' + RED, kod_potwora, 		5, 		15, 		 5, 		2, 		6, 		5, 		20, 		-1);
         monster_alignment [monster_id] = -1;
         break;
      case _HENCHMEN:
      	monster_stats ('t' + RED, kod_potwora, 		5, 		25, 		 5, 		3, 		7, 		5, 		20, 		-1);
         break;
      case _SOLDIER:
      	monster_stats ('s' + BLUE, 	kod_potwora, 	5, 		50, 		 10, 		5, 		10, 		200, 		5, 		-1);
         monster_alignment [monster_id] = 5;
         break;

         				// monster icon, monster_code, speed, 	health, 	hit,     dv, 		damage, 	 exp, 	 pp, 	area

      case _Pinkman:
      	monster_stats ('@' + 1536, kod_potwora, 	7, 		150, 			20, 		20,      15, 		200, 		150,     -1);	// chaotyczny dobry
         break;
      case _Bum:
      	monster_stats ('@' + 1536, kod_potwora, 	5, 		20, 			20, 		20,      5, 		200, 		150,     -1);	// chaotyczny dobry
         break;
      case _Bartender:
      	monster_stats ('@' + 2304, kod_potwora, 	7, 		100, 			10, 		10,      10, 		150, 		100, 		-1);	// neutralny
         break;
      case _Priest:
      	monster_stats ('@' + YELLOW, kod_potwora, 7, 		100, 			10,      10, 		10, 		150, 		70, 		-1);
         break;
      case _Flint_Westwood:
      	monster_stats ('@' + DARK_GRAY, kod_potwora, 7, 	100, 			10, 		10, 		10, 		150, 		70, 		-1);
      	monster_alignment [monster_id] = 10;
         break;
      case _Helc:
      	monster_stats ('@' + VIOLET, kod_potwora, 5, 		100, 			10, 		10, 		10, 		150, 		100, 		-1);
         break;
      case _Rayo:
      	monster_stats ('@' + RED, kod_potwora, 	5, 		100, 			10, 		10, 		10, 		150, 		100, 		-1);
         break;
      case _Father_Grigori:
      	monster_stats ('@' + YELLOW, kod_potwora, 10,		100, 			10, 		10, 	 10, 		150, 		70, 		-1);
         break;
      case _Wise_Arse:
      	monster_stats ('@' + YELLOW, kod_potwora, 7, 		100,			10, 		10, 		7, 		150, 		70,		-1);
         break;
      case _Gina:
      	monster_stats ('@' + BLUE, kod_potwora, 5, 20, 5, 5, 104, 200, 5, -1);
         break;
      case _Heisen:
      	monster_stats ('@' + VIOLET, 	kod_potwora, 5, 		200, 			5, 		20, 		7, 		200, 		5, 		-1);
         break;
      case _Bren_McGuire:
      	monster_stats ('@' + DARK_GREEN, kod_potwora, 5, 	100, 			10, 		15, 		5, 		100,    	5, 		-1);
         break;
      case _Pleasence:
      	monster_stats ('@' + DARK_BLUE, kod_potwora,	8, 	50, 			10, 		2, 		10, 		100, 		50, 		-1);
      	monster_alignment [monster_id] = 10;
         break;
      case _vice_prezio:
      	monster_stats ('@' + BLUE, kod_potwora,	8, 	50, 			10, 		2, 		10, 		100, 		50, 		-1);
      	monster_alignment [monster_id] = 10;
         break;
      case _Bavar:
      	monster_stats ('@' + YELLOW,	kod_potwora, 		8, 		100, 		10, 		10, 		20, 		100, 		0, 		102);		// 0: not noticed
         break;
      case _Marston:
      	monster_stats ('@' + DARK_GREEN,	kod_potwora, 	5, 		50, 		10, 		2, 		20, 		100, 		0, 		102);		// 0: not noticed
         break;
      case _Salesman:
      	monster_stats ('@' + 1536, kod_potwora, 			8, 		100, 		20, 		20, 		20, 		100, 		0, 		102);
         break;
      case _Doc:
      	monster_stats ('@' + VIOLET, kod_potwora, 		7, 		50, 		10, 		10, 		20,     150, 		0, 		112);
         break;

      case _D_Morgan:
      	monster_stats ('@' + YELLOW, 	kod_potwora, 		10, 		40, 		7, 		10, 		10, 		100, 		50, 		-1);
         break;
      case _Jack:
      	monster_stats ('@' + DARK_RED, kod_potwora, 		8, 		100, 		10, 		10, 		20, 		100, 		0, 		102);
         break;
      case _Moom:
      	monster_stats ('C' + DARK_RED, 		kod_potwora,		5, 		50, 		10, 		10, 		20, 		50, 		5, 		-1);
         break;
      case _CLASS_Cyborg:
      	monster_stats ('C' + YELLOW,	kod_potwora,				5, 		30, 		10, 		4, 		7, 		50, 		5, 		-1);
         monster_alignment [monster_id] = losuj_2 (-5, -10);
         break;
      case _Shades:
      	monster_stats ('C' + BLUE, 		   kod_potwora,		5, 		50, 		10, 		10, 		10, 		50, 		5, 		-1);
         monster_alignment [monster_id] = -10;
         break;
      default:
			monster_stats ('r' + GRAY, kod_potwora, 5, 5, 5, 5, 5, 40, 1, -1);
			break;
	}

	h_pos_mon [monster_id] = x_pos;
   v_pos_mon [monster_id] = y_pos;
   monster_aim [monster_id] = usposobienie;
   monsters_planszy [x_pos] [y_pos] = monster_id;
}

void monster_stats (int monster_ico, int monster_kod, int monster_spd, int monster_hlt,
	int monster_ht, int monster_def, int monster_dmg, int monster_xp, int monster_power,
   char monster_character)
{
	int i;

	monster_id = monsters_amount;
	monster [monster_id] = monster_ico;
   monster_code [monster_id] = monster_kod;
	monster_speed [monster_id] = monster_spd;
	monster_health [monster_id] = monster_hlt;
   monster_hit [monster_id] = monster_ht;
	monster_dv [monster_id] = monster_def;
	monster_damage [monster_id] = monster_dmg;
	monster_exp [monster_id] = monster_xp;
   monster_pp [monster_id] = monster_power;
   monster_hp [monster_id] = monster_health [monster_id];
   monster_char [monster_id] = monster_character;
   monster_alignment [monster_id] = 0;

	for (i = 0; i < 30; i ++)
		monster_state [monster_id] [i] = 0;

	for (i = 0; i < 15; i ++)
		monster_body [monster_id] [i] = -1;

	for (i = 0; i < 15; i ++)
		monster_backpack [monster_id] [i] = -1;

	for (i = 0; i < 7; i ++)
		monster_left_poison [monster_id] [i] = 0;

	monsters_amount ++;
}

void generuj_potwory (int liczba_mon, int monster_kod, int monster_place, int monster_floor, int cel_ataku)
{
   int kod_mon;
   int rand_x, rand_y, kod_floor, kod_f;

   liczba_mon += monsters_amount;

	while (monsters_amount < liczba_mon)
	{

   	if (monster_place == -1)
      {
			rand_x = rng (5, x_planszy - 5);
   	   rand_y = rng (5, y_planszy - 5);
      }
      else if (monster_place == 3)
      {
			rand_x = rand () % (x_planszy - 42) + 41;
   	   rand_y = rand () % (y_planszy - 13) + 1;
      }
      else if (monster_place == 9)	 	// prawy dolny rog
      {
			rand_x = rand () % (x_planszy - 42) + 41;
   	   rand_y = rand () % (y_planszy - 13) + 12;
      }

//      debug (rand_x, rand_y, 1000, 1);
//           generuj_potwory (10, 1, -1, 2, -5);

      kod_mon = monsters_planszy [rand_x] [rand_y];
      kod_f = floor_planszy [rand_x] [rand_y];

      if (monster_floor == -1)
      	kod_floor = monster_floor;
      else
	      kod_floor = floor_planszy [rand_x] [rand_y];

//      debug (kod_floor, kod_f, 1, 2);
//      debug (monsters_amount, kod_mon, 1, 3);

      if (kod_mon == -15 && kod_floor == monster_floor && kod_f < 11 && !view_matrix (X_MAX + rand_x - h_pos, Y_MAX + rand_y - v_pos))
			bestiariusz (monster_kod, rand_x, rand_y, cel_ataku);
	}
}

void generuj_potwory_extra ()
{
	int monsters_extra = monsters_amount;

   switch (tl_id)
   {
   	case 1302:
      		monsters_extra += 11;

      		while (monsters_amount < monsters_extra)
				{
            	if (monster_id - monsters_amount == -1)
               	bestiariusz (2, rand () % (x_planszy - 2) + 1, rand () % (y_planszy - 2) + 1, -1);
               else
               	bestiariusz (3, rand () % (x_planszy - 2) + 1, rand () % (y_planszy - 2) + 1, -1);

			      if (plansza [h_pos_mon [monster_id]] [v_pos_mon [monster_id]] > 8192)
      				monsters_amount --;
            }
            break;
	}
}

void monster_na_mapie (int nr_elementu, int kod_m, int kod_f, int kod_enemy)
{
   monster_floor [nr_elementu] [0] = kod_m;
   monster_floor [nr_elementu] [1] = kod_f;
   monster_floor [nr_elementu] [2] = kod_enemy;
}
