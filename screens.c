#include "deklaracje.h"

void display_quests ()
{
	int i, quest_msg, quests_amount = 0;
   char quest_text [8000];

   for (i = 0; i < 16; i ++)
   {
   	if (quest [i] > -10 && quest [i] != 0)
      	quests_amount ++;
   }

   if (quests_amount == 0)
   	kopia (quest_text, "^n Currently you don't have any quests.^n");
	else
	   kopia (quest_text, "^n You are involved into following tasks:^n");

	for (i = 0; i < 128; i ++)
  	{
     	if (quest [i])
		{
			if (quest [i] != -10 && quest [i] != -5)
  				add_kopia (quest_text, quests_names [i]);

			switch (i)
			{
		      case 0:
   	        	if (quest [0] > 0)
						quest_msg = 1;
					break;
	         case 1:
   	        	if (quest [1] > 0)
						quest_msg = 2;
               else if (quest [1] == -1)
               	quest_msg = 3;
         	   break;
            case 2:
            	if (quest [2] == 1)
               	quest_msg = 4;
               else if (quest [2] == -1)
               	quest_msg = 8;
               break;
            case 3:				// friends issue
            	if (quest [3] == 1)
               	quest_msg = 6;
               else
               	quest_msg = 9;
               break;
            case 4:				//	help with fixing
            	if (quest [4] == 1)
               	quest_msg = 7;
            	else if (quest [4] == 2)
               	quest_msg = 10;
               else
               	quest_msg = 11;
               break;
            case 6:				// rat king
            	if (quest [6] == 1)
               	quest_msg = 12;
               break;
            case 7:				//
            	if (quest [7] == 1)
               	quest_msg = 13;
            	else
               	quest_msg = 16;
               break;
            case 8:				//
            	if (quest [8] == 1)
               	quest_msg = 14;
               else if (quest [8] == 2)
               	quest_msg = 15;
               else
               	quest_msg = 17;
               break;
            case 9:				//
            	if (quest [9] == 1)
               	quest_msg = 18;
               else if (quest [9] == -1)
               	quest_msg = 19;
               break;
            case 10:				//
            	if (quest [10] == 1)
               	quest_msg = 20;
               else if (quest [10] == -1)
               	quest_msg = 21;
               break;
            case 11:				//
            	if (quest [11] == 1)
               	quest_msg = 23;
               else if (quest [11] == -1)
               	quest_msg = 24;
               break;
            case 12:				//
            	if (quest [12] == 1)
               	quest_msg = 22;
            	else if (quest [12] == -1)
               	quest_msg = 33;
               break;
            case 13:				//
            	if (quest [13] == 1)
               	quest_msg = 25;
            	else if (quest [13] == -1)
               	quest_msg = 26;
               break;
            case 14:				//			AA quest 1
            	if (quest [14] == 1)
               	quest_msg = 27;
            	else if (quest [14] == 2)
               	quest_msg = 28;
            	else if (quest [14] == 3)
               	quest_msg = 29;
               break;
            case 15:				//			AA quest 2
            	if (quest [15] == 1)
               	quest_msg = 30;
            	else if (quest [15] == 2)
               	quest_msg = 31;
               break;
            case 16:				//			AA quest 3
            	if (quest [16] == 1)
               	quest_msg = 32;
            	else if (quest [16] == -1)
               	quest_msg = 3;
               break;
            default:
            	quest_msg = 0;
               break;
		   }

			if (quest [i] != -10 && quest [i] != -5 && quest_msg >= 0)
				add_kopia (quest_text, quests_descriptions [quest_msg]);
      }
   }

	make_window (2, 1, -10, -10, 50, 17, -3, quest_text, COLOR_GRAY, COLOR_GRAY);
}

void display_abilities ()
{
	int i;

   messages ("\n                      Character's abilities\r\n", 0, 23);

   for (i = 1; i < 9; i ++)
   {
   	if (i < 19)
	   	gotoxy (2, i + 4);
      else
      	gotoxy (41, i - 15);

      if (abilities [i] == 100)
			enter_ability (i, 22);
      else if (abilities [i])
   	  	enter_ability (i, 30);
      else
   	  	enter_ability (i, 24);

   	if (i < 19)
	   	gotoxy (21, i + 4);
      else
      	gotoxy (60, i - 15);

		if (abilities [i] != abilities_pot [i])
			textcolor (14);
      else if (!abilities [i])
      	textcolor (8);
      else
      	textcolor (6);

      printw ("%3d", abilities [i]);
      printw ("   /");

		if (abilities [i] != abilities_pot [i])
			textcolor (14);
      else if (!abilities [i])
      	textcolor (8);
      else
      	textcolor (6);

      printw (" %3d", abilities_pot [i]);
   }

   gotoxy (2, 24);
   messages ("[Esc] - exit", 0, 23);
 	do klawisz ();
   while (key != 27);
}

void display_character ()
{
	int i;

	exit_list = 0;
	make_window (0, 2, 0, 0, 60, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze

//0123456789012345678901234567890123456789012345678901234567890123456789
 "-CHARACTER TAB-                                   - ESC -^n"
 "                                                         ^n"
 " name:                     ********O*V*E*R*V*I*E*W*******^n"
 "                           *                            *^n"
 " gender:                   *HIT POINTS   :              *^n"
 "                           *TOTAL DAMAGE :              *^n"
 " age:                      *ARMOUR       :              *^n"
 "                           *GCDC         :              *^n"
 "                           *                            *^n"
 "    //  PERKS   \\\\         ******************************^n"
   , 8, 8);												// 8: kolor ramki, 8: kolor tekstu

	gotoxy (12, 5);
	messages (player_name, 0, 24);
	gotoxy (14, 7);
   enter_player (player_gender, 24);
	gotoxy (11, 9);
   enter_age (player_age , 24);

   for (i = 1; i < 25; i ++)
   {
	 	gotoxy (4 + (i / 10) * 18, 13 + i - (i / 10) * 9);

      if (abilities [i])
      {
      	enter_ability (i, 24);

         if (abilities [i] < 4)
         {
				gotoxy (16 + (i / 10) * 19, 13 + i - (i / 10) * 9);
				messages ("- ", 0, 24);
         }
      }

      if (abilities [i] == 1)
      	messages ("ADE", 0, 24);
      else if (abilities [i] == 2)
      	messages ("SCA", 0, 24);
      else if (abilities [i] == 3)
      	messages ("PRO", 0, 24);
   }

   if ((i = search_item (17, 3)) >= 0)
   	GCDC = item_amount [i];
   else
   	GCDC = 0;

 	gotoxy (46, 7);
   messages ("^/", health , 24);
   messages ("^", total_max_health , 24);
 	gotoxy (46, 8);
   messages ("^", total_damage , 24);
 	gotoxy (46, 9);
   messages ("^", total_armor , 24);
 	gotoxy (46, 10);
   messages ("^", GCDC , 24);

	while (!exit_list)
   {
   	klawisz ();

		if (key == _ESC)
      	exit_list = 1;
   }
}

void display_progress ()
{
	unsigned long int elapsed_years = elapsed_time / 31104000;
	unsigned long int elapsed_months = (elapsed_time / 2592000) % 12;
	unsigned long int elapsed_weeks = (elapsed_time / 604800) % 4;
	unsigned long int elapsed_days = (elapsed_time / 86400) % 7;
	unsigned long int elapsed_hours = (elapsed_time / 3600) % 24;
	unsigned long int elapsed_minutes = (elapsed_time / 60) % 60;
	unsigned long int elapsed_seconds = elapsed_time % 60;

	clrscr ();
   textcolor (COLOR_GRAY);
   gotoxy (2, 2);
   messages (" Game progress", 0, 24);
   messages (" Elapsed time: ", 0, 24);

   if (elapsed_years == 1)
	   messages ("^ year ", elapsed_years, 24);
   else if (elapsed_years)
	   messages ("^ years ", elapsed_years, 24);

   if (elapsed_months == 1)
	   printw ("%d month ", elapsed_months);
   else if (elapsed_months)
	   printw ("%d months ", elapsed_months);

   if (elapsed_weeks == 1)
	   printw ("%d week ", elapsed_weeks);
   else if (elapsed_weeks)
	   printw ("%d weeks ", elapsed_weeks);

   if (elapsed_days == 1)
	   printw ("%d day ", elapsed_days);
   else if (elapsed_days)
	   printw ("%d days ", elapsed_days);

   if (elapsed_hours == 1)
	   printw ("%d hour ", elapsed_hours);
   else if (elapsed_hours)
	   printw ("%d hours ", elapsed_hours);

   if (elapsed_minutes == 1)
	   printw ("%d minute ", elapsed_minutes);
   else if (elapsed_minutes)
	   printw ("%d minutes ", elapsed_minutes);

   if (elapsed_seconds == 1)
	   printw ("%d second.", elapsed_seconds);
   else
	   printw ("%d seconds.", elapsed_seconds);

   messages (" Elapsed turns: ^.", turns_amount, 24);

	printw (" Killed monsters amount: %d ('m' - display)", killed_monsters [0]);

   while (1)
   {
   	klawisz ();

      if (key == 27)
      	break;
      else if (key == 'm')
      {
//      	display_victims ();
         break;
      }
   }

   rysuj_ekran ();
}

void klawiszologia ()
{
	clear ();
   messages ("\n\r C   - Chat with monster", 0, 16 + COLOR_GRAY);
   messages ("\n\r P   - Pay for an item", 0, 16 + COLOR_GRAY);
   messages ("\n\r w   - Character information page", 0, 16 + COLOR_GRAY);
   messages ("\n\r d   - Drop an item / sell in shop", 0, 16 + COLOR_GRAY);
   messages ("\n\r s   - swap position with neutral character", 0, 16 + COLOR_GRAY);
   messages ("\n\r q   - Disply current quests", 0, 16 + COLOR_GRAY);
   messages ("\n\r f   - Pick up an item", 0, 16 + COLOR_GRAY);
   messages ("\n\r a   - Look", 0, 16 + COLOR_GRAY);
   messages ("\n\r Esc - Quick help", 0, 16 + COLOR_GRAY);
   messages ("\n\r X   - Exit game", 0, 16 + COLOR_GRAY);
   messages ("\n\r x   - Change current range weapon (also during targeting mode)", 0, 16 + COLOR_GRAY);
   messages ("\n\r e   - Eat", 0, 16 + COLOR_GRAY);
   messages ("\n\r m   - Message buffor", 0, 16 + COLOR_GRAY);
   messages ("\n\r t   - Throw/shoot", 0, 16 + COLOR_GRAY);
   messages ("\n\r r   - Reload current range weapon", 0, 16 + COLOR_GRAY);
   messages ("\n\r z   - Gear menu", 0, 16 + COLOR_GRAY);
   messages ("\n\r Q   - Save game and exit", 0, 16 + COLOR_GRAY);
   messages ("\n\r >   - Enter location", 0, 16 + COLOR_GRAY);
   messages ("\n\r <   - Exit location", 0, 16 + COLOR_GRAY);
   messages ("\n\r v   - Use an item", 0, 16 + COLOR_GRAY);
   messages ("\n\r I   - Instructions", 0, 16 + COLOR_GRAY);

   while (1)
   {
   	klawisz ();

      if (key == 27)
      	break;
   }

   rysuj_ekran ();
}

void instructions (void)
{
	make_window (2, 3, -10, -10, 49, 15, -15,

   "                 INSTRUCTIONS^n"
   "                 ------------^n^n"
   " DAEDLYFLAZH is a post nuclear roguelike game. As typical roguelike this game uses only ASCI characters as a graphic."
	" Main character is shown as '@' and starts on the main map of the World. ^n^n To move you use arrows or numpad arrows (numlock ON)."
	" To enter location on the map you have to press '>'. Try to go around the whole location and talk to other non-personal characters (NPC) with pressing 'C'. NPCs are usually showed as \"@\" like main character."
	" ^n^n Important thing in DAEDLYFLAZH is shooting."
	" You shoot by pressing 't' and then you choose your target."
	" At the moment you can use one of two wielded range weapons - PRIME or SIDEARM."
	" PRIME weapons are bigger guns carried on back like bazookas, shotguns, grenade launchers."
	" SIDEARM weapons are a smaller ones like pistols."
	" To switch currenty used weapon press 'x'."
	" Remember of limited ammo to your range weapons. You will still have to collect or buy ammunition to your pistols and guns of various type."
	" ^n During the game press 'k' to see keyboard."

   , 8, 8);	// 49 = size_x, 10 = size_y, 8 = kolor ramki, 8 = kolor tekstu
}
