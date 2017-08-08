#include "deklaracje.h"

void messages (char msg [], int liczba, int place)
{
   char c;
   int i = 0, j, _cyfra;
   char liczba_dodatnia = 0;

   if (liczba >= 0)
   	liczba_dodatnia = 1;

   if (place < 16)			// message box
   {
	   textcolor (place);
	   gotoxy (2 + litera, 23 + kolumna);

	   while ((c = msg [i]) != '\0')
   	{
		   if (litera >= 70 && !kolumna)
   	   {
      		gotoxy (2, 24);
	      	kolumna = 1;
   	      litera = 0;
      	}
         
	   	if (c == '|')
   	   {
      		c = '~';
         	gotoxy (2, 24);
	         litera = 0;
   	      kolumna = 1;
      	}
	      else if (c == '<')
   	   {
      		litera = 0;
         	kolumna = 0;
	         key = 0;
   	      c = '~';
      	   clear_area (2, 23, 79, 24);
         	gotoxy (2, 23);
	      }
         else if (c == '^')
         {
         	printw ("%d", liczba);
            c = '~';

            if (liczba >= 10000)
            	litera += 5;
            else if (liczba < 10000 && liczba >= 1000)
            	litera += 4;
            else if (liczba < 1000 && liczba >= 100)
            	litera += 3;
            else if (liczba < 100 && liczba >= 10)
            	litera += 2;
            else if (liczba <= -1 && liczba >= -9)
            	litera += 2;
            else if (liczba <= -10 && liczba >= -99)
            	litera += 3;
            else if (liczba <= -100 && liczba >= -999)
            	litera += 4;
            else
            	litera ++;
         }
   	   else if (c == '_' || litera == 65 && kolumna == 1)
      	{
	      	printw (" (more...)");
   	      litera = 0;
      	   kolumna = 0;

            if (c == '_')
					msg [i] = '~';

            c = '~';
            i --;

            do klawisz ();
      		while (key != 32);

				key = 0;
   	      clear_area (2, 23, 79, 24);
      	   gotoxy (2, 23);
	      }

         if (c != '~')
         {

            if (liczba == -1000)
            {
					c += 32;		// zmniejsz litere
               liczba = 0;
            }

            if (turns_amount_ != turns_amount)
            {
//            	message [buffor_counter] = 13;
  //             turns_amount_ = turns_amount;
    //           buffor_counter ++;
            }

				message [buffor_counter] = c;
            buffor_counter ++;

            if (buffor_counter >= M_BUFFOR - 1)
            {
               for (buffor_counter = 0; buffor_counter < M_BUFFOR - 101; buffor_counter ++)
               	message [buffor_counter] = message [buffor_counter + 99];
            }

			   addch (c);
	      	litera ++;
         }

   	   i ++;
	   }
   }
   else
   {
   	if (place == 100)
      {
      	if (!kolumna)
				clear_area (1, 23, 1 + litera, 23);
   		else
         {
				clear_area (1, 23, 79, 23);
            clear_area (1, 24, 1 + litera, 24);
         }

         litera = kolumna = 0;
      }
      else if (place < 80)    		// inventory
  	   {
	     	textcolor (place);

		   while ((c = msg [i]) != '\0')
	      {
   	      if (c == '^')
	         {
      	   	printw ("%d", liczba);
   	         c = '~';
	         }
   	      else if (c == '`')
	         {
      	   	printw ("%c", liczba);
   	         c = '~';
	         }
	   	   else if (c == '_')
	      	{
            	c = '~';
		      	printw (" (more...)");

	            do klawisz ();
   	   		while (key != 32);

					key = 0;
		      }

            if (liczba == -1000 && place < 48)
            {
					c += 32;		// zmniejsz litere
               liczba = 0;
            }

         	if (c != '~')
				   addch (c);

   	      i ++;
	      }
      }
      else if (place == 80)		// create flag
      {
      	litera = j = 1;

		   while ((c = msg [i]) != '\0')
	      {
	         if (c == '^')
   	      {
            	c = '~';

               if (liczba < 0)
     	   			putc ('-', temp10);

            	while (liczba > 9 || liczba < 0)
               {
		            if (liczba >= 10000)
                  {
   		         	_cyfra = liczba / 10000;
                     liczba %= 10000;

                     if (liczba < 1000)
		                  j = 0;
                  }
	   	         else if (liczba < 10000 && liczba >= 1000)
                  {
   	   	      	_cyfra = liczba / 1000;
                     liczba %= 1000;

                     if (liczba < 100)
		                  j = 0;
                  }
	      	      else if (liczba < 1000 && liczba >= 100)
                  {
		            	_cyfra = liczba / 100;
                     liczba %= 100;

                     if (liczba < 10)
		                  j = 0;
                  }
   		         else if (liczba < 100 && liczba >= 10)
                  {
      		      	_cyfra = liczba / 10;
                     liczba %= 10;
                  }
         		   else if (liczba <= -1 && liczba >= -9)
                  {
	            		_cyfra = (-1) * liczba;
                     liczba = 0;
                  }
	   	         else if (liczba <= -10 && liczba >= -99)
                  {
	            		_cyfra = (-1) * liczba / 10;
                     liczba %= 10;
                  }
	   	         else if (liczba <= -100 && liczba >= -999)
                  {
	            		_cyfra = (-1) * liczba / 100;
                     liczba %= 100;

                     if (liczba > -10)
		                  j = 0;
                  }
      	   	   else
                  {
	            		_cyfra = (-1) * liczba / 1000;
                     liczba %= 1000;

                     if (liczba > -100)
		                  j = 0;
                  }

                  putc (_cyfra + 48, temp10);

                  if (!j)		// wstaw zero
                  {
                  	putc(48, temp10);
                     j = 1;
                  }
               }

					if (liczba_dodatnia)
              		putc (liczba + 48, temp10);
	         }

            if (liczba == -1000)
            {
					c += 32;		// zmniejsz litere
               liczba = 0;
            }

         	if (c != '~')
				   putc (c, temp10);

   	      i ++;
	      }
      }
      else if (place > 128)
      {
	     	textcolor (place);

		   while ((c = msg [i]) != '\0')
	      {
   	      if (c == '^')
	         {
      	   	printw ("%d", liczba);
   	         c = '~';
	         }

         	if (c != '~')
				   addch (c);

   	      i ++;
	      }

//         textbackground (0);
      }

//      textcolor (8);
   }

   textcolor (COLOR_GRAY);
}

void enter_item (int kod, int pl)		// pl - place (message box / inventory)
{
	int grupa = item_group [kod];
   int typ = item_type [kod];
   int material = item_value_material [kod] % 100;

	if (wybierz_item)		// gdy zakladamy do inventory
   {
		messages ("`- ", alfabet, 24);
		inv [alfabet - 96] = kod;
		alfabet ++;
   }

   write_params_prefix (kod, pl);		// kod: item_id, 1: prefix (2: postfix), pl: jw.

	if (grupa == _MELEE_SLOT)
	{
		if (typ == 1)
      {
      	if (pl > 32)
				messages ("b-bat", 0, pl);
         else
				messages ("baseball bat", 0, pl);
      }
		else if (typ == 2)
			messages ("axe", 0, pl);
		else if (typ == 3 || typ == 6)
			messages ("shiv", 0, pl);
		else if (typ == 4)
			messages ("hammer", 0, pl);
		else if (typ == 5)
			messages ("knife", 0, pl);
	}
	else if (grupa == _SIDEARM_SLOT)
	{
		if (typ == 1)
			messages ("2KRR", 0, pl);
		if (typ == 2)
			messages ("M119", 0, pl);
		if (typ == 3)
			messages ("6Wayne", 0, pl);
	}
	else if (grupa == _PRIME_SLOT)
	{
		if (typ == 1)
			messages ("NT9000", 0, pl);
		if (typ == 2)
			messages ("Reza", 0, pl);
		if (typ == 3)
			messages ("16M", 0, pl);
		if (typ == 4)
			messages ("Panzor", 0, pl);
		if (typ == 5)
			messages ("3GM3", 0, pl);
	}
	else if (grupa == _BODY_SLOT)
	{
		if (typ == 1)
			messages ("Rags", 0, pl);
		if (typ == 2)
			messages ("Jacket", 0, pl);
		if (typ == 3)
			messages ("Cevlar", 0, pl);
		if (typ == 4)
			messages ("Coat", 0, pl);
		if (typ == 5)
			messages ("M65", 0, pl);
	}
	else if (grupa == 5)
	{
		if (typ == 11)
			messages ("falchion", 0, pl);
      else if (typ == 12)
      	messages ("spear", 0, pl);
	}
  	else if (grupa == 6)
	{
		if (typ == 1)
			messages ("sting", 0, pl);
		if (typ == 2)
			messages ("katar", 0, pl);
		if (typ == 3)
			messages ("nizar spine", 0, pl);
		if (typ == 4)
			messages ("runic talon", 0, pl);
   }
  	else if (grupa == 7)
	{
		if (typ == 1)
			messages ("bow", 0, pl);
		if (typ == 2)
			messages ("xbow", 0, pl);
		if (typ == 3)
			messages ("small crossbow", 0, pl);
		if (typ == 4)
			messages ("siege bow", 0, pl);
   }
  	else if (grupa == 8)
	{
		if (typ == 21)
			messages ("arrow", 0, pl);
      else if (typ == 22)
      	messages ("shuriken", 0, pl);
      else if (typ == 23)
      	messages ("bolt", 0, pl);
   }
  	else if (grupa == 9)
	{
		if (typ == 1)
			messages ("rags", 0, pl);
      else if (typ == 2)
      	messages ("trousers", 0, pl);
      else if (typ == 3)
      	messages ("plate kit", 0, pl);
      else if (typ == 4)
      	messages ("assassin's kit", 0, pl);
   }
   else if (grupa == 15)
   {
   	if (typ == 1)
      	messages ("torch", 0, pl);
      else if (typ == 2)
      	messages ("hatchet", 0, pl);
      else if (typ == 3)
      	messages ("climbing set", 0, pl);
      else if (typ == 4)
      	messages ("medikit", 0, pl);
      else if (typ == 5)
      	messages ("sealed package", 0, pl);
      else if (typ == 6)
      	messages ("tool box", 0, pl);
      else if (typ == 7)
      	messages ("high explosive", 0, pl);
   }
   else if (grupa == 17)
   {
   	if (typ <= 2)
	     	messages ("coin", 0, pl);
      else
      	messages ("GCDC", 0, pl);
   }
   else if (grupa == 24)
   {
   	if (typ == 1)
	     	messages ("key to graveayrd", 0, pl);
      else if (typ == 2)
	     	messages ("president quarter key", 0, pl);
      else if (typ == 10)
	     	messages ("key signed \"RS\"", 0, pl);
      else if (typ == 13)
	     	messages ("key labeled \"my stuf\"", 0, pl);
   }
  	else if (grupa == 19)
	{
   	if (typ < 900)
      {
      	enter_monster (typ, pl, -1000, 0);
	      messages (" corpse", 0, pl);
      }
      else if (typ < 1000)
      {
      	if (typ == 900)
		      messages ("dead body", 0, pl);
      	else if (typ == 901)
		      messages ("mutilated body", 0, pl);
      }
      else
      {
      	switch (typ - 1000)
         {
         	case 1:
            	messages ("elven waffer", 0, pl);
               break;
            case 2:
            	messages ("iron ration", 0, pl);
               break;
            case 3:
            	messages ("food", 0, pl);
               break;
            case 20:
            	messages ("hallucinogen mushroom", 0, pl);
               break;
            case 30:
            	messages ("drug", 0, pl);
               break;
         }
      }
   }
   else if (grupa == 14)
   	messages ("spellbook of ", 0, pl);
	else if (grupa == 20)	// shield
	{
		if (typ == 1)
			messages ("buckler", 0, pl);
		else if (typ == 2)
			messages ("protector", 0, pl);
	}
  	else if (grupa == 21)
		messages ("wand of ", 0, pl);
  	else if (grupa == 25)
		enter_ammo (typ, pl);
  	else if (grupa == 29)
   {
   	if (typ == 1)
			messages ("crusaders icon", 0, pl);
   	else if (typ == 2)
			messages ("amulet", 0, pl);
   	else if (typ == 3)
			messages ("alloys", 0, pl);
   	else if (typ == 4)
			messages ("remains from droid", 0, pl);
   }
  	else if (grupa == 50)
   {
		messages ("stairs leading", 0, pl);

      if (typ == 1)
      	messages (" upwards", 0, pl);
      else
      	messages (" downwards", 0, pl);
   }
  	else if (grupa == 51)
   {
   	if (typ == 1)
			messages ("water", 0, pl);

      messages (" trap", 0, pl);
   }
  	else if (grupa == 52)
   {
   	if (typ == 1 || typ == 3)
      	messages ("closed", 0, pl);
      else if (typ == 2)
      	messages ("opened", 0, pl);

		enter_material (material, pl, 1);
		messages (" door", 0, pl);
   }
  	else if (grupa == 53)
   {
   	if (typ == 1)
      	messages ("christian", 0, pl);
      else if (typ == 2)
      	messages ("islamic", 0, pl);
      else if (typ == 3)
      	messages ("jewish", 0, pl);

		messages (" altar", 0, pl);
   }
  	else if (grupa == 54)
   {
   	if (typ == 1 || typ == 3)
      	messages ("closed", 0, pl);
      else
      	messages ("opened", 0, pl);

		enter_material (material, pl, 1);
		messages (" gate", 0, pl);
   }
  	else if (grupa == 55)
   {
		messages ("grave", 0, pl);
   }
  	else if (grupa == 60)
   {
		messages ("statue", 0, pl);
   }
  	else if (grupa == 61)
   {
		messages ("boat", 0, pl);
   }
  	else if (grupa == 62)
   {
   	if (typ == 1)
			messages ("water purifier", 0, pl);
   	else if (typ == 2)
			messages ("water purifier terminal", 0, pl);
   }
  	else if (grupa == 63)
   {
   	if (typ == 1)
			messages ("opened barrel with toxic waste", 0, pl);
   }
  	else if (grupa == 64)
   {
   	if (typ == 1)
      {
      	if (item_specials1 [kod] == -1)
				messages ("broken core64 terminal", 0, pl);
         else
				messages ("core64 terminal", 0, pl);
      }
   }

   write_params_postfix (kod, pl);

/*   if (pl > 16 && pl <= 32)
   {
	  	gotoxy (70, i_y + 5);

      if (item_weight [kod] * item_amount [kod] >= 10)
			printw ("%3d,%d", item_weight [kod] * item_amount [kod] / 100, item_weight [kod] * item_amount [kod] % 100);
      else
			printw ("%3d,0%d", item_weight [kod] * item_amount [kod] / 100, item_weight [kod] * item_amount [kod] % 100);

		gotoxy (76, i_y + 5);
      printw ("kg");
   }*/
}

void enter_material (int kod_mater, int pl, char sufix_type)
{
	if (sufix_type == 1)
		messages (" ", 0, pl);

  	switch (kod_mater)
	{
		case 1:
        	messages ("steel", 0, pl);
			break;
     	case 2:
        	messages ("iron", 0, pl);
			break;
		case 3:
        	messages ("wooden", 0, pl);
			break;
		case 4:
        	messages ("mithril", 0, pl);
			break;
		case 5:
        	messages ("gold", 0, pl);
			break;
		case 6:
        	messages ("silver", 0, pl);
			break;
		case 10:
        	messages ("leather", 0, pl);
			break;
   }

	if (sufix_type == 2)
		messages (" ", 0, pl);
}

void enter_ammo (int typ, int pl)
{
  	if (typ == 1)
		messages ("9mm", 0, pl);
  	else if (typ == 2)
		messages (".357", 0, pl);
  	else if (typ == 3)
		messages (".233", 0, pl);
  	else if (typ == 4)
		messages ("gauge shell", 0, pl);
  	else if (typ == 5)
		messages ("7,63mm", 0, pl);
  	else if (typ == 101)
		messages ("grenade", 0, pl);
}

void enter_obstacle_desc (int typ, int pl)
{
 	if (typ == 1)
		messages ("Gordon Freeman, beloved mute father", 0, pl);
  	else if (typ == 2)
		messages ("Jahn Doee, rest in peace", 0, pl);
  	else if (typ == 3)
		messages ("Moe last words: Oh a shiny button,i try to press it", 0, pl);
  	else if (typ == 4)
		messages ("Satan, died at age of 666. Leaves wife and doughter", 0, pl);
  	else if (typ == 5)
		messages ("Andor, Fate Smile upon him. Good Luck", 0, pl);
  	else if (typ == 6)
		messages ("Ough! I found golden bracers", 0, pl);
  	else if (typ == 7)
		messages ("Flouriann, says : d**n, im wipe out.Me = invincible", 0, pl);
  	else if (typ == 8)
		messages ("White Wolf, great assassin. Died in Flotsam, by hand of Kayran", 0, pl);
}

void enter_one_item (int kod_p)
{
	int temp_;

	temp_ = item_amount [kod_p];
	item_amount [kod_p] = 1;
	enter_item (kod_p, COLOR_GRAY);
   item_amount [kod_p] = temp_;
}

void write_params_prefix (int kod, char pl)
{
	int material = item_value_material [kod] % 100;
   int grupa = item_group [kod];
   int typ = item_type [kod];

	if (item [kod] == 5)					// obstacle
   {
   	if (item_state [kod] == 1)		// burning
      	messages ("burning ", 0, pl);
   }

  	if (grupa == 17)		// kasa
	{
     	messages ("^ ", item_amount [kod], pl);
   }
  	else if (grupa == 62)
	{
   	if (item_specials1 [kod] == -1)
	     	messages ("broken ", 0, pl);
   }

/*  	if (item_ident [kod] == 2 && item_group [kod] != 17)
     	switch (item_status [kod])
      {
        	case 1:
           	messages ("uncursed ", 0, pl);
            break;
         case 2:
           	messages ("cursed ", 0, pl);
            break;
         case 3:
           	messages ("blessed ", 0, pl);
            break;
		}

	if (item_state [kod])
     	switch (item_state [kod])
      {
       	case 1:
           	messages ("broken ", 0, pl);
            break;
         case 2:
           	messages ("rusty ", 0, pl);
            break;
         case 3:
				messages ("broken rusty ", 0, pl);
            break;
		}

	if (item_ident [kod] && item_value_material [kod] % 100)
     	enter_material (material, pl, 2);

   if (item_group [kod] == 24)		// keys
   {
   	switch (item_type [kod])
      {
      	case 1:
         	messages ("Mohammed Hallash ", 0, pl);
            break;
      	case 2:
         	messages ("Graveyard gate ", 0, pl);
            break;
      }
   }*/
}

void write_params_postfix (int kod, char pl)
{
	int grupa = item_group [kod];
   int hit_value = item_hit [kod];

/*	if (item_amount [kod] > 1)
     	messages ("s", 0, pl);

	if (item_ident [kod])
   {
	  	if (grupa == 14 || grupa == 21)
        	switch (item_type [kod])
         {
           	case 1:
              	messages ("lightning ray", 0, pl);
               break;
           	case 101:
              	messages ("lightning bolt", 0, pl);
               break;
           	case 102:
              	messages ("ice bolt", 0, pl);
               break;
           	case 201:
              	messages ("webbing", 0, pl);
               break;
           	case _LIGHTNING_BALL:
              	messages ("lightning ball", 0, pl);
               break;
           	case 401:
              	messages ("light", 0, pl);
               break;
            case 402:
              	messages ("web ball", 0, pl);
               break;
            case 403:
              	messages ("darkness", 0, pl);
               break;
            case 501:
              	messages ("door creation", 0, pl);
               break;
            case 502:
              	messages ("trap creation", 0, pl);
               break;
			}
   }*/

	if (grupa <= _BODY_SLOT)
		messages (" {", 0, pl);

	if (grupa >= _MELEE_SLOT && grupa <= 3)	// weapons
	{
		messages ("^", item_dmg_bonus [kod], pl);		// BD = base damage

		if (grupa >= _SIDEARM_SLOT)
      {
      	messages (";^/", item_specials1 [kod], pl);		// SD = striking distance
      	messages ("^", item_specials2 [kod], pl);		// R = rounds
      }
	}
   else if (grupa	== _BODY_SLOT)
		messages ("^", item_dv [kod], pl);		// AV = armor value

	if (grupa <= _BODY_SLOT)
		messages ("}", 0, pl);

	if (item_amount [kod] > 1 && grupa != 17)
   {
     	messages (" (x ^", item_amount [kod], pl);
     	messages (")", 0, pl);
   }

   if (pl < 32 && item_value_material [kod] % 50 == 21)
   {
   	messages (", covered with blood", 0, pl);
   }

   if (pl < 32 && item_value_material [kod] % 100 >= 50)
   {
   	messages (" (unpaid, ", 0, pl);
   	messages ("^ $)", item_value_material [kod] / 100 * item_amount [kod], pl);
   }

   if (item [kod] == 5)		// obstacle
   {
   	if (item_ident [kod])
      {
      	messages (" \"", 0, pl);
         enter_obstacle_desc (item_ident [kod], pl);
         messages ("\"", 0, pl);
      }
   }

/*	if (item_dv [kod] || grupa == 1 || grupa == 2 || grupa == 20 || grupa == 9)
	{
   	if (item_dv [kod] < 0)
			messages (" [^,", item_dv [kod], pl);
      else
			messages (" [+^,", item_dv [kod], pl);

   	if (item_specials1 [kod] < 0)
			messages ("^]", item_specials1 [kod], pl);
      else
			messages ("+^]", item_specials1 [kod], pl);

		if (grupa != 4 && grupa != 5 && grupa != _MWAMMO && grupa != _MWEAPON)
      {
			if (hit_value < 0)
		      messages (" (^)", hit_value, pl);
			else if (hit_value > 0)
	         messages (" (+^)", hit_value, pl);
      }
	}

	if (grupa == 4 || grupa == 5 || grupa == _MWAMMO || grupa == 6)	// weapons
	{
		if (item_hit [kod] < 0)
			messages (" (^, ", item_hit [kod], pl);
		else
			messages (" (+^, ", item_hit [kod], pl);

		messages ("^d", item_dices [kod] / 100, pl);
      messages ("^", item_dices [kod] % 100, pl);

		if (item_dmg_bonus [kod] < 0)
			messages ("^", item_dmg_bonus [kod], pl);
		else if (item_dmg_bonus [kod] > 0)
			messages ("+^", item_dmg_bonus [kod], pl);

		messages (")", 0, pl);

      if (pl > 32 && item_amount [kod] > 0)
			messages (" {^}", item_amount [kod], pl);
	}
   else if (grupa == _MWEAPON)
   {
		if (item_hit [kod] < 0)
			messages (" (^, ", item_hit [kod], pl);
		else
			messages (" (+^, ", item_hit [kod], pl);

      if (item_specials1 [kod] / 100 < 0)
			messages ("^)", item_specials1 [kod] / 100, pl);
      else
			messages ("+^)", item_specials1 [kod] / 100, pl);
	}
   else if (grupa == 15)	// tools
   {
     	if (item_type [kod] == 1)		// torch
      {
        	messages (" (^ remained turns", item_specials1 [kod], pl);

			if (item_specials2 [kod])
           	messages (", lit", 0, pl);

        	messages (")", 0, pl);
		}
   }*/
}

void enter_player (char player_gender_, int pl)
{
	switch (player_gender_)
   {
   	case _MALE:
      	messages ("Male", 0, pl);
         break;
      case _FEMALE:
      	messages ("Female", 0, pl);
         break;
   }
}

void enter_gender (int gender_id, int kod_g, int ltr, int pl)
{
	if (kod_g == 1)
   {
		if (gender_id == _MALE)
   		messages ("He", ltr, pl);
	   else
   		messages ("She", ltr, pl);
   }
   else
   {
		if (gender_id == _MALE)
   		messages ("His", ltr, pl);
	   else
   		messages ("Her", ltr, pl);
   }
}

void enter_hand (char player_hand_, int pl)
{
	switch (player_hand_)
   {
   	case 1:
      	messages ("Right-handed", 0, pl);
         break;
      case 2:
      	messages ("Left-handed", 0, pl);
         break;
      case 3:
      	messages ("Bimanual", 0, pl);
         break;
   }
}

void enter_achievement (int achievement_no, int pl)
{
	if (achievement_no < 100 && pl <= 30 && pl > 16)
   {
   	if (achievement_no < 10)
	   	messages ("0", 0, pl);

   	messages ("^. ", achievement_no, pl);
   }

	switch (achievement_no)
   {
   	case 1:
      	messages ("SLICE OF LIFE", 0, pl);
         break;
      case 101:
      	messages ("- Hunt down and kill, serial killer.", 0, pl);
         break;
      case 2:
      	messages ("HERO OF OLD REMO", 0, pl);
         break;
      case 102:
      	messages ("- Finish all Flint Westwood quests ( 3/3 ).", 0, pl);
         break;
      case 3:
      	messages ("ANYTHING OF THE DEAD", 0, pl);
         break;
      case 103:
      	messages ("- Kill 50 zombies.", 0, pl);
         break;
      case 4:
      	messages ("RULER OF BATTLEFIELD", 0, pl);
         break;
      case 104:
      	messages ("- Kill at least one enemy with all prime weapons.", 0, pl);
         break;
      case 5:
      	messages ("IRON MIKE", 0, pl);
         break;
      case 105:
      	messages ("- Kill at least one enemy with all melee weapons.", 0, pl);
         break;
      case 6:
      	messages ("A DUTY CALL", 0, pl);
         break;
      case 106:
      	messages ("- Kill at least one enemy with all sidearms weapons.", 0, pl);
         break;
      case 7:
      	messages ("GPS MAN", 0, pl);
         break;
      case 107:
      	messages ("- Discover all locations in main map.", 0, pl);
         break;
      case 8:
      	messages ("DARTH YODA", 0, pl);
         break;
      case 108:
      	messages ("- Find and fix light saber.", 0, pl);
         break;
      case 9:
      	messages ("GUNS AND ROSES", 0, pl);
         break;
      case 109:
      	messages ("- Chat with female and kill her with your sidearm.", 0, pl);
         break;
      case 10:
      	messages ("I GOT A BMW", 0, pl);
         break;
      case 110:
      	messages ("- Sell or buy anything in shop \"Bavarian Most Wanted\" in NY CITY DOWNTOWN.", 0, pl);
         break;
      case 11:
      	messages ("I SHOOT THE...", 0, pl);
         break;
      case 111:
      	messages ("- Assassinate Flint Westwood in Old Reno.", 0, pl);
         break;
      case 12:
      	messages ("A GOT A CRASHED PLANE TOO!", 0, pl);
         break;
      case 112:
      	messages ("- Complete quest from Yaro in mines of OLD RENO.", 0, pl);
         break;
      case 13:
      	messages ("YOU GONNA FUCK WITH ME? YOU FUCK WITH THE BEST!", 0, pl);
         break;
      case 113:
      	messages ("- Kill 20 enemys with 16M rifle.", 0, pl);
         break;
      case 14:
      	messages ("DID YOU KNOW MARK13?", 0, pl);
         break;
      case 114:
      	messages ("- Destroy 20 CLASS cyborgs.", 0, pl);
         break;
      case 15:
      	messages ("WAR! WAR NEVER CHANGES", 0, pl);
         break;
      case 115:
      	messages ("- Solve poison water problem in SHELTER TEC location.", 0, pl);
         break;

      case 16:
      	messages ("PRESIDENT BOYSCOUT", 0, pl);
         break;
      case 116:
      	messages ("- Broke down Core64 the main computer in CLASS CORP.", 0, pl);
         break;

      case 17:
      	messages ("CYBERDINE BELIEVER", 0, pl);
         break;
      case 117:
      	messages ("- Fix Core64 the main computer in CLASS CORP.", 0, pl);
         break;

      case 18:
      	messages ("ITS REALLY END?", 0, pl);
         break;
      case 118:
      	messages ("- Finish game, standard ending.", 0, pl);
         break;

      case 19:
      	messages ("THE END", 0, pl);
         break;
      case 119:
      	messages ("- Finish game, alternative ending.", 0, pl);
         break;

      case 20:
      	messages ("HARDWARE MO?!", 0, pl);
         break;
      case 120:
      	messages ("- Did not finish the game - quit or die, with CLASS cyborg remains.", 0, pl);
         break;

      case 21:
      	messages ("BERSERKER", 0, pl);
         break;
      case 121:
      	messages ("- Kill every citizen in Old Remo.", 0, pl);
         break;

      case 22:
      	messages ("SPEEDY OR ROADRUNNER?", 0, pl);
         break;
      case 122:
      	messages ("- Finish the game in XYZ rounds.", 0, pl);
         break;

      case 23:
      	messages ("MEAT GRINDER", 0, pl);
         break;
      case 123:
      	messages ("- Kill 20 zombies with melee.", 0, pl);
         break;

      case 24:
      	messages ("REMEMBER RAVENHOLM?", 0, pl);
         break;
      case 124:
      	messages ("- Clean up Graveyard without single shoot (use only melee weapons).", 0, pl);
         break;

      case 25:
      	messages ("40TH HAMMER OF WAR", 0, pl);
         break;
      case 125:
      	messages ("- Kill one CLASS with hammer.", 0, pl);
         break;

      case 26:
      	messages ("LEFT 4 DEAD 2 ROOT 4 EVER", 0, pl);
         break;
      case 126:
      	messages ("- Die in GRAVEYARD or PUERTO ZOMBICO locations.", 0, pl);
         break;

      case 27:
      	messages ("NO AGENT CAN PERSUADE ME", 0, pl);
         break;
      case 127:
      	messages ("- Discover what happens in ATLANTIC ACCELERATOR.", 0, pl);
         break;

      case 28:
      	messages ("LOBO WITH A SHOTGUN", 0, pl);
         break;
      case 128:
      	messages ("- Kill 10 nomads with Panzor and rags equipped.", 0, pl);
         break;

      case 29:
      	messages ("GET RID OF ACAMANTOR AND HIS ARMY OF DEMONS.", 0, pl);
         break;
      case 129:
      	messages ("- Finish game with character named Hasrinaxx.", 0, pl);
         break;

      case 30:
      	messages ("\"REVENGE!\"", 0, pl);
         break;
      case 130:
      	messages ("- Complete quest from Bren McGuire.", 0, pl);
         break;

      case 31:
      	messages ("MICROPROSEXOR SOCCER MOM", 0, pl);
         break;
      case 131:
      	messages ("- Sex with Moom'a, CLASS female prostitue pleasure cyborg.", 0, pl);
         break;

      case 32:
      	messages ("GOOD BREAKING", 0, pl);
         break;
      case 132:
      	messages ("- Complete deal betwen two drug kingpins in NY CITY DOWNTOWN and OLD REMO.", 0, pl);
         break;

      case 33:
      	messages ("LOBO", 0, pl);
         break;
      case 133:
      	messages ("- Wipe out entire population, then talk to president of NEW YORK CITY.", 0, pl);
         break;

      case 34:
      	messages ("IM NOT AN ADDICT", 0, pl);
         break;
      case 134:
      	messages ("- Use narcotics 5 times.", 0, pl);
         break;

      case 35:
      	messages ("THIS BASTARD \"OD\"", 0, pl);
         break;
      case 135:
      	messages ("- Die by narcotics overdose.", 0, pl);
         break;

      case 36:
      	messages ("SCROOGE", 0, pl);
         break;
      case 136:
      	messages ("- Collect XYZ amount of GCDC.", 0, pl);
         break;

      default:
      	messages ("-", 0, pl);
         break;
   }
}

void monster_description (int monster_kod)
{
	int size_x = 40, size_y = 12, kolor_ramki = 8, kolor_tekstu = 8, monster_msg = 0;
   char monster_text [8000];

   switch (monster_code [monster_kod])
   {
   	case _BAYBARS:
      	monster_msg = 1;
         break;
   	case _MILITIA:
      	monster_msg = 2;
         break;
   	case _FEMALE_CIVILIAN:
      	monster_msg = 3;
         break;
   	case _FEMALE_CIVILIAN_OLD:
      	monster_msg = 4;
         break;
   	case _MALE_CIVILIAN:
      	monster_msg = 5;
         break;
   	case _MALE_CIVILIAN_OLD:
      	monster_msg = 6;
         break;
   	case _MILITIA_CAPTAIN:
      	monster_msg = 7;
         break;
   	case _BANDIT:
      	monster_msg = 8;
         break;
   	case _WILD_DOG:
      	monster_msg = 9;
         break;
   	case _Heisen:
      	monster_msg = 10;
         break;
   	case _Bren_McGuire:
      	monster_msg = 11;
         break;
   	case _Pleasence:
      	monster_msg = 12;
         break;
   	case _Rayo:
      	monster_msg = 13;
         break;
   	case _RAT_KING:
      	monster_msg = 14;
         break;
   	case _Pinkman:
      	monster_msg = 15;
         break;
   	case _Bum:
      	monster_msg = 16;
         break;
   }

	kopia (monster_text, monsters_descriptions [monster_msg]);
	make_window (1, 3, -10, -10, size_x, size_y, monster_kod, monster_text, kolor_ramki, kolor_tekstu);
}

void area_description (int area_kod)
{
   switch (area_kod)
   {
   	case _Downtown:
			make_window (2, 3, -10, -10, 49, 10, -15, " You enter to commercial suburb New York, the Downtown. With proper amount of money, you can have access to biggest warriaty of goods and services in whole wasteland or involved in some unlawful business, if you need any additional cash.", 8, 8);	// 49 = size_x, 10 = size_y, 8 = kolor ramki, 8 = kolor tekstu
			break;
   	case _Downtown_Mayhem:
			make_window (2, 3, -10, -10, 49, 10, -15, " As you are getting closer to the city you notice smoke, fire almost everywhere... some shots and explosions in distance, strange green and blue light luminations. As you've found a passage to Downtown with your CLASS companions the extermination is beginning leading you to the new world.", 8, 8);	// 49 = size_x, 10 = size_y, 8 = kolor ramki, 8 = kolor tekstu
			break;
   	case _Puerto_Zombico:
			make_window (2, 3, -10, -10, 49, 10, -15, " You hear a distant \"Get out of here you damned fukers!\".", 8, 8);	// 49 = size_x, 10 = size_y, 8 = kolor ramki, 8 = kolor tekstu
			break;
   	case _Atlantic_Accelerator:
			make_window (2, 3, -10, -10, 49, 10, -15, " What happens here? Talk to Bum and Boolfrog. Figure out whats happens in AA oil rig.", 8, 8);	// 49 = size_x, 10 = size_y, 8 = kolor ramki, 8 = kolor tekstu
			break;
   	case 5000:
			make_window (2, 3, -10, -10, 49, 10, -15, " Brave adventurer!^n"
																         " You have just finished your road to city of Yerushalayim and as for now your quest is over..."
																			" Before You there is the city of big opportunities, challenges and wealth... And that will be the another story...",
																         8, 8);	// 49 = size_x, 10 = size_y, 8 = kolor ramki, 8 = kolor tekstu
         break;
   }
}

void item_description (int body_part_id)
{
	int size_x = 22, size_y = 14, kolor_ramki = COLOR_GRAY, kolor_tekstu = COLOR_GRAY, item_msg = 0;
   char item_text_info [4000];
   char item_text_desc [4000];
   int grupa_id = item_group [item_body [body_part_id]];
   int typ_id = item_type [item_body [body_part_id]];

   if (grupa_id == 1)
   {
   	if (typ_id == 1)				// bbat
      	item_msg = 2;
   	else if (typ_id == 2)		// axe
      	item_msg = 20;
   	else if (typ_id == 3)		// shiv
      	item_msg = 22;
   	else if (typ_id == 4)		// hammer
      	item_msg = 24;
   }
   else if (grupa_id == 2)
   {
   	if (typ_id == 1)				// 2KRR
      	item_msg = 4;
   	else if (typ_id == 2)				// M119
      	item_msg = 16;
   	else if (typ_id == 3)				// 6Wayne
      	item_msg = 18;
   }
   else if (grupa_id == 3)
   {
   	if (typ_id == 1)				// NT9000
      	item_msg = 6;
   	else if (typ_id == 2)		// Reza
      	item_msg = 8;
   	else if (typ_id == 3)		// 16M
      	item_msg = 10;
   	else if (typ_id == 4)		// Panzor
      	item_msg = 12;
   	else if (typ_id == 5)		// 3GM3
      	item_msg = 14;
   }
   else if (grupa_id == 4)
   {
   	if (typ_id == 1)				// 
      	item_msg = 26;
   	else if (typ_id == 2)		//
      	item_msg = 27;
   	else if (typ_id == 3)		//
      	item_msg = 28;
   	else if (typ_id == 4)		// 
      	item_msg = 29;
   	else if (typ_id == 5)		//
      	item_msg = 30;
   }

	if (grupa_id == 4)
   {
		kopia (item_text_desc, "DESCRIPTION:^n^n");
		add_kopia (item_text_desc, items_descriptions [item_msg]);
   }
   else
   {
		kopia (item_text_info, "INFO:^n^n");
		add_kopia (item_text_info, items_descriptions [item_msg]);
		kopia (item_text_desc, "DESCRIPTION:^n^n");
		add_kopia (item_text_desc, items_descriptions [item_msg + 1]);
   }

	if (grupa_id == 4)
   {
		make_window (0, -1, 1,  2,  size_x + 36, size_y - 2, 	-2, item_text_desc, kolor_ramki, kolor_tekstu);
   }
   else
   {
		make_window (0, -1, 1,  2, size_x     , size_y + 5,  	-2, item_text_info, kolor_ramki, kolor_tekstu);
		make_window (0, -1, 22, 2, size_x + 15, size_y - 2, 	-2, item_text_desc, kolor_ramki, kolor_tekstu);
   }
}

void age_description (char age_id)
{
//	clear_area (37, 7, 77, 19);
   gotoxy (40, 7);

	if (age_id == 1)
		make_window (0, 0, 23, 5, 25, 10, -2, "MELEE Perk^nBaseball bat", COLOR_GRAY, COLOR_GRAY);
	else if (age_id == 2)
   {
		make_window (0, 0, 23, 5, 25, 10, -2, "PRIME Perk^nSCIENCE + 1^nJacket, 5 GCDC", COLOR_GRAY, COLOR_GRAY);
   }
	else if (age_id == 3)
		make_window (0, 0, 23, 5, 25, 10, -2, "SCIENCE + 2^n10 GCDC", COLOR_GRAY, COLOR_GRAY);
}

void gender_description (char _id)
{
	clear_area (48, 3, 78, 23);
   gotoxy (40, 7);

	if (_id == 1)
		make_window (0, 0, 23, 4, 25, 9, -2, "25 HP on start^nM119", COLOR_GRAY, COLOR_GRAY);
	else if (_id == 2)
   {
		make_window (0, 0, 23, 4, 25, 9, -2, "20 HP on start^nSCIENCE + 1^n6Wayne, Rags, Medikit", COLOR_GRAY, COLOR_GRAY);
		make_window (0, 0, 48, 0, 30, 23, -2,
       "^n    .---.    "
       "^n   (_,/\\ \\   "
       "^n  (`a a(  )  "
       "^n  ) \\=  ) (  "
       "^n (.--' '--.) "
       "^n / (_) (_) \\ "
       "^n| / \\   / \\ |"
       "^n \\ /   \\ // "
       "^n  \\/\\   /\\/  "
       "^n  |  \\_/  |  "
       "^n   \\  /  /   "
       "^n    \\/  /    "
       "^n     ( (     "
       "^n     |\\ \\    "
       "^n     | \\ \\   "
       "^n    /_Y/_Y   "

/*".            .--.          "
"^n\\\\          //\\\\ \\         "
"^n.\\\\        ///_\\\\\\\\        "
"^n:/>`      /(| `|'\\\\\\       "
"^n Y/\\      )))\\_-_/((\\      "
"^n  \\ \\    ./'_/ \" \\_`\\)     "
"^n   \\ \\.-\" ._ \\   /   \\     "
"^n    \\ _.-\" (_ \\Y/ _) |     "
"^n     \"      )\" | \"\"/||     "
"^n         .-'  .'  / ||     "
"^n        /    `   /  ||     "
"^n       |    __  :   ||_    "
"^n       |   / \\   \\ '|\\`    "
"^n       |  |   \\   \\        "
"^n       |  |    `.  \\       "
"^n       |  |      \\  \\      "
"^n       |  |       \\  \\     "
"^n       |  |        \\  \\    "
"^n       |  |         \\  \\   "
"^n       /__\          |__\  "
"^n       /.|    DrS.    |.\\_ "
"^n      `-''            ``--'"*/

	 	, COLOR_DARK_GRAY, COLOR_DARK_GRAY);
   }
}

void enter_age (char player_age_, int pl)
{
	switch (player_age_)
   {
   	case 1:
      	messages ("Youngster", 0, pl);
         break;
      case 2:
      	messages ("Adult", 0, pl);
         break;
      case 3:
      	messages ("Elder", 0, pl);
         break;
   }
}

void enter_menu_selection (char menu_selection, int pl)
{
	switch (menu_selection)
   {
   	case 1:
      	messages ("NEW GAME", 0, pl);
         break;
      case 2:
      	messages ("LOAD PREVIOUS GAME", 0, pl);
         break;
      case 3:
      	messages ("ACHIEVEMENTS", 0, pl);
         break;
      case 4:
      	messages ("EXIT GAME", 0, pl);
         break;
   }
}

void enter_ability (int ability_id, int place)
{
  	switch (ability_id)
   {
     	case 1:
        	messages ("MIGHT", 0, place);
         break;
      case 2:
        	messages ("CONDITION", 0, place);
         break;
      case 3:
        	messages ("MELEE", 0, place);
         break;
      case 4:
         messages ("SIDEARMS", 0, place);
         break;
      case 5:
        	messages ("PRIME", 0, place);
	      break;
      case 6:
        	messages ("SCIENCE", 0, place);
         break;
      case 7:
        	messages ("TRADE", 0, place);
         break;
      case 8:
        	messages ("Mechanics", 0, place);
         break;
      case 9:
      	messages ("Sight", 0, place);
         break;
      case 10:
      	messages ("First Aid", 0, place);
         break;
      case 11:
        	messages ("Woodcrafting", 0, place);
         break;
	}
}

void enter_body_part (char part, int place)
{
	switch (part)
   {
		case _MELEE_SLOT:
			messages ("MELEE SLOT   :", 0, place);
   	   break;
		case _BODY_SLOT:
			messages ("BODY         :", 0, place);
   	   break;
		case _PRIME_SLOT:
			messages ("PRIME SLOT   :", 0, place);
   	   break;
		case _SIDEARM_SLOT:
			messages ("SIDEARM SLOT :", 0, place);
   	   break;
/*		case _HEAD:
			messages ("Head:        ", 0, place);
   	   break;
      case _TORSO:
			messages ("Torso:       ", 0, place);
         break;
      case _RHAND:
			messages ("Right hand:  ", 0, place);
         break;
      case _LHAND:
			messages ("Left hand:   ", 0, place);
         break;
      case _LEGS:
			messages ("Downgear:    ", 0, place);
         break;
      case _MECH_CLAW:
			messages ("Mech. blade: ", 0, place);
         break;
      case _MWEAPON:
			messages ("M Weapon:    ", 0, place);
         break;
      case _MWAMMO:
			messages ("MW Ammo:     ", 0, place);
         break;
      case _PRIME_TOOL:
			messages ("Prime tool:  ", 0, place);
         break;
      case _SUB_TOOL:
			messages ("Sub tool:    ", 0, place);
         break;*/
	}
}

void enter_floor (int floor_type, int pl, int ltr)
{
	if (floor_type >= 1000 && floor_type <= 2000)
   	floor_type -= 1000;

	switch (floor_type)
   {
   	case 1:
   	case 101:
   	case 1001:
      	messages ("Grass", ltr, pl);
         break;
   	case 2:
      case 102:
      case 112:
      case 1002:
      	messages ("Floor", ltr, pl);
         break;
   	case 3:
      case 1003:
      	messages ("Platform", ltr, pl);
         break;
   	case 4:
      case 104:
      case 1004:
      	messages ("Sand", ltr, pl);
         break;
   	case 5:
      	messages ("Bushes", ltr, pl);
         break;
      case 6:
      	messages ("Tree", ltr, pl);				// dab
         break;
		case 7:
      	messages ("Hornbeam tree", ltr, pl);		// grab
			break;
		case 8:
      	messages ("Grapewine", ltr, pl);			
         break;
      case 9:
      	messages ("Olive tree", ltr, pl);
			break;
      case 10:
      	messages ("Almond tree", ltr, pl);			
         break;
      case 11:
      	messages ("Wooden wall", ltr, pl);
         break;
      case 12:
      	messages ("Stone wall", ltr, pl);
         break;
      case 13:
      	messages ("Clay wall", ltr, pl);
         break;
      case 14:
      	messages ("Sand wall", ltr, pl);
      	break;
      case 19:
      	messages ("Farm", ltr, pl);
      	break;
      case 20:
      	messages ("Lower wall", ltr, pl);
      	break;
      case 2002:
      	messages ("Burning floor", ltr, pl);
      	break;
      case 2012:
      	messages ("Burning wall", ltr, pl);
      	break;
      case 21:
      case 1021:
      	messages ("Water", ltr, pl);
      	break;
      case 24:
      case 1024:
      	messages ("Ocean", ltr, pl);
      	break;
      case 28:
      case 1028:
      	messages ("Street", ltr, pl);
      	break;
      case 29:
      case 1029:
      	messages ("Helipad", ltr, pl);
      	break;
      case 49:
      	messages ("Mountains", ltr, pl);
      	break;
      case 150:
      case 1150:
      	messages ("Sea", ltr, pl);
      	break;
      case 164:
      	messages ("Wasteland", ltr, pl);
      	break;
      case 180:
      	messages ("New York City", ltr, pl);
      	break;
      case 181:
      	messages ("Graveyard", ltr, pl);
      	break;
      case 182:
      	messages ("Old Remo", ltr, pl);
      	break;
      case 183:
      	messages ("Marina Harbour", ltr, pl);
      	break;
      case 184:
      	messages ("CLASS Corp", ltr, pl);
      	break;
      case 185:
      	messages ("Shelter Tec", ltr, pl);
      	break;
      case 186:
      	messages ("Puerto Zombico", ltr, pl);
      	break;
      case 187:
      	messages ("Atlantic Accelerator", ltr, pl);
      	break;
      case 188:
      	messages ("New York City Warzone", ltr, pl);
      	break;
      case 189:
      	messages ("An observation tower", ltr, pl);
      	break;
      case 190:
      	messages ("A wizard's tower", ltr, pl);
      	break;
      case 191:
      	messages ("A volcano", ltr, pl);
      	break;
      case 192:
      	messages ("A cave entrance", ltr, pl);
      	break;
      case 193:
      	messages ("The hidden garden", ltr, pl);
      	break;
	}
}

void make_window (char window_type, char ramka_typ, int start_x, int start_y, char size_x, char size_y, int monster_kod, char text [], char kolor_ramki, char kolor_tekstu)
{
	char msge, txt [16], key_choice = -1;
	char linia [40] [80], ltr, wyr_no = 0, texting = 1, kolor_tekstu_wew;
   int y_txt, x, y, akt_linia_upper, litera_tekstu = 0, litera_wyrazu = 0, prev_a = 0, litera_wiersza = 0, litera_linii = 0, lin_no = 0, offset = 0;
   int _h_pos, _v_pos;

   msg_reset ();

	while ((msge = text [litera_tekstu]) != '\0')			// konwersja textu na pojedyncze linie
   {
		if (litera_linii == size_x - 2 + offset)		// koniec linijki = nowa linia
      {
         if (msge != 32 && msge != '^')
         {
         	while ((msge = text [litera_tekstu]) != 32 && msge != '^')
            {
					litera_linii --;
               litera_tekstu --;
            }

            litera_tekstu ++;
         }
         else if (msge == 32)
         	litera_tekstu ++;

         linia [lin_no] [litera_linii] = '\0';
         lin_no ++;
         litera_linii = 0;
         offset = 0;
      }
      else
      {
	   	linia [lin_no] [litera_linii] = msge;

         if (msge == '^')
         {
         	if (text [litera_tekstu + 1] >= '0' && text [litera_tekstu + 1] <= '9')
            {
      		   litera_linii ++;
			      litera_tekstu ++;
	         	offset += 3;
            }
   	      else if (text [litera_tekstu + 1] == 'n')		// znacznik nowej linii
            {
               linia [lin_no] [litera_linii] = '\0';
               litera_linii = 0;
            	lin_no ++;
               litera_tekstu += 2;
               offset = 0;
            }
         }
         else
         {
	         litera_linii ++;
		      litera_tekstu ++;
         }
		}
   }

   linia [lin_no] [litera_linii] = '\0';

	if (start_y == -10)
   {
	   if (v_pos < Y_WINDOW / 2 && size_y < 16)
			start_y = 3;
		else
			start_y = 0;
   }

	if (start_x == -10)
   {
		if (size_x < 60)
		   start_x = (X_WINDOW - size_x) / 2;
	   else
   		start_x = (80 - size_x) / 2;
   }

   textcolor (kolor_ramki);

   for (y = 1; y <= size_y; y ++)		// tworzy ramke
   {
   	gotoxy (start_x + LB, start_y + y + UB - 1);

   	for (x = 1; x <= size_x; x ++)
      {
      	if (y == 1 && x == 1)
         {
         	if (ramka_typ == 1)
		      	addch (201);
            else if (ramka_typ == 2)
            	addch ('#');
            else if (ramka_typ == 3)
            	addch (218);
            else if (ramka_typ == -1)
            	addch (32);
         }
     		else if (y == size_y && x == 1)
         {
         	if (ramka_typ == 1)
	        		addch (200);
				else if (ramka_typ == 2)
            	addch ('#');
            else if (ramka_typ == 3)
            	addch (192);
            else if (ramka_typ == -1)
            	addch (32);
         }
      	else if (y == 1 && x == size_x)
         {
         	if (ramka_typ == 1)
	        		addch (187);
				else if (ramka_typ == 2)
            	addch ('#');
            else if (ramka_typ == 3)
            	addch (191);
            else if (ramka_typ == -1)
            	addch (32);
         }
     		else if (y == size_y && x == size_x)
         {
         	if (ramka_typ == 1)
	        		addch (188);
				else if (ramka_typ == 2)
            	addch ('#');
            else if (ramka_typ == 3)
            	addch (217);
            else if (ramka_typ == -1)
            	addch (32);
         }
			else if (x > 1 && x < size_x && (y == 1 || y == size_y))
         {
         	if (ramka_typ == 1)
	        		addch (205);
				else if (ramka_typ == 2)
            	addch ('#');
            else if (ramka_typ == 3)
            	addch (196);
            else if (ramka_typ == -1)
            	addch (32);
         }
     	   else if (y > 1 && y < size_y && (x == 1 || x == size_x))
         {
         	if (ramka_typ == 1)
	        		addch (186);
				else if (ramka_typ == 2)
            	addch ('#');
            else if (ramka_typ == 3)
            	addch (179);
            else if (ramka_typ == -1)
            	addch (32);
         }
			else if (x > 1 && x < size_x && y > 1 && y < size_y)
        		addch (32);
      }
   }

   x = 0;
   akt_linia_upper = 0;

	if (lin_no < size_y - 2)
   	y = lin_no;
   else
   	y = size_y - 3;

  	while (texting)				// wypisywanie tekstu w przesuwanych liniach
   {
   	y_txt = 0;

		for (x = akt_linia_upper; x <= y + akt_linia_upper; x ++)
		{
	      textcolor (kolor_tekstu);
		   litera_linii = 0;
			gotoxy (start_x + LB + 1, start_y + UB + y_txt + 1);
			y_txt ++;

		   while ((msge = linia [x] [litera_linii]) != '\0')
			{
         	if (msge == '^')
            {
            	kolor_tekstu_wew = linia [x] [litera_linii + 1] * 10 + linia [x] [litera_linii + 2];
            	textcolor (kolor_tekstu_wew);
               litera_linii += 3;
            }
            else
            {
			      addch (msge);
   		      litera_linii ++;
         	}
	   	}

         while (litera_linii < size_x - 2)
         {
         	addch (32);
            litera_linii ++;
         }
  		}

		if (akt_linia_upper)
      {
			gotoxy (start_x + LB + size_x - 2, start_y + UB);
         textcolor (kolor_ramki - 1);
         addch ('^');
      }

		if (!akt_linia_upper)
      {
			gotoxy (start_x + LB + size_x - 2, start_y + UB);
         textcolor (kolor_ramki);

       	if (ramka_typ == 1)
        		addch (205);
			else if (ramka_typ == 2)
           	addch ('#');
         else if (ramka_typ == 3)
           	addch (196);
         else if (ramka_typ == -1)
           	addch (32);
      }

		if (akt_linia_upper + size_y - 3 < lin_no)
      {
			gotoxy (start_x + LB + size_x - 2, start_y + UB + size_y - 1);
         textcolor (kolor_ramki - 1);
         addch ('v');
      }

		if (akt_linia_upper + size_y - 3 == lin_no)
      {
			gotoxy (start_x + LB + size_x - 2, start_y + UB + size_y - 1);
         textcolor (kolor_ramki);

       	if (ramka_typ == 1)
        		addch (205);
			else if (ramka_typ == 2)
           	addch ('#');
         else if (ramka_typ == 3)
 	        	addch (196);
         else if (ramka_typ == -1)
           	addch (32);
      }

		if (window_type)		// samo okienko (bez czekania na klawisz)
      {
			while (1)
   	   {
		     	klawisz ();

				if (key == _ENTER || key == _ENTER2 || key == 32 || key == 27)
      	   {
	         	texting = 0;
   	   	  	break;
      	   }
	      	else if (akt_linia_upper + size_y - 3 < lin_no && (key == '2' || key == 2 || key == 82))	// page down
	         {
   		      akt_linia_upper += 1;
      	      break;
	         }
   	   	else if (akt_linia_upper >= 1 && (key == '8' || key == 83 || key == 3))	// page up
      	   {
         		akt_linia_upper -= 1;
         	   break;
	         }
         }
      }
      else
      	texting = 0;
	}

	if (window_type)
   {
   	if (window_type == 2)
      {
      	h_cur = h_pos;
         v_cur = v_pos;
      }

		_h_pos = h_pos;
		_v_pos = v_pos;
		h_pos = h_cur + h_pos_pl - 30;
		v_pos = v_cur + v_pos_pl - 10;
		ustaw_gracza ();

		for (y = start_y + v_pos - v_pos_pl; y < start_y + size_y + v_pos - v_pos_pl; y ++)
			for (x = start_x + h_pos - h_pos_pl; x < start_x + size_x + h_pos - h_pos_pl; x ++)
				enter_char (mem_planszy [x] [y], x, y);

		h_pos = _h_pos;
	   v_pos = _v_pos;

      if (window_type == 2)
      {
      	ustaw_gracza ();
         verify_visible_monsters ();
      }
//      rysuj_plansze ();
	}
}

char* names (char _religion)
{
	if (_religion == 1)
		return christian_names_list [rand () % _CHRISTIAN_NAMES_AMOUNT];

	return islamic_names_list [rand () % _ISLAMIC_NAMES_AMOUNT];
}

void msg (char _msg [])
{
	messages (_msg, 0, COLOR_GRAY);
}

void msg_reset ()
{
	messages ("", 0, 100);
}

void kropka (char p_color)
{
	messages (". ", 0, p_color);
//	msg (".");
}

void message_buffor ()
{
	int i, temp_, j = 0, esc_ = 0;

   textcolor (COLOR_GRAY);

	for (i = 0; i < buffor_counter; i ++)
   {
/*   	if (message [i] == 13)
      {
      	j++;
         addch (10);
         addch (13);

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
               else if (key == 2)	// enter = page down
               {
               	temp_ = i;
                  clrscr ();
                  break;
               }
               else if (key == 3)	// page up
               {
               	j -= 20;
                  i = temp_;
                  break;
               }
               else if (key == 6)	// poczatek
               {
               	i = -1;
               	j = 0;
                  clrscr ();
                  break;
               }
            }
         }
      }
      else*/
		  	addch (message [i]);

      if (esc_)
      	break;
   }

	if (!esc_)
   {
	   do klawisz ();
   	while (key != 27);
   }
}

