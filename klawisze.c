#include "deklaracje.h"

void klawisze (void)
{
	int i, j, kod_p, kod_s, kod_f1, kod_f2, x_pos, y_pos, swap_mon = -1;

//	_setcursortype (_NORMALCURSOR);
	klawisz ();
	_setcursortype (_NOCURSOR);

	switch (key)
	{
		case 54:	// w prawo
      case 5:
			move_xy (h_pos + 1, v_pos);
			break;
		case 57:	// w prawo - gora
			move_xy (h_pos + 1, v_pos - 1);
			break;
		case 56:	// w gore
      case 83:
      case 3:
			move_xy (h_pos, v_pos - 1);
			break;
		case 51:	// w prawo - dol
			move_xy (h_pos + 1, v_pos + 1);
			break;
		case 52:	// w lewo
		case 4:	// w lewo
			move_xy (h_pos - 1, v_pos);
			break;
		case 53:	// w miejscu
			move_xy (h_pos, v_pos);
			break;
		case 49:	// w lewo - dol
			move_xy (h_pos - 1, v_pos + 1);
			break;
		case 55:	// w lewo - gora
			move_xy (h_pos - 1, v_pos - 1);
			break;
		case 50:	// w dol
      case 82:
      case 2:
			move_xy (h_pos, v_pos + 1);
			break;
		case 'z':
			gear_menu ();
			rysuj_ekran ();
			break;
		case 'I':
      	instructions ();
			break;
		case 'd':	// 'd' - drop
  	      if (cl_id == 1999)
     	   	msg ("<You should enter to this location first. ");
         else
         {
				action_drop ();
     		   turn ();
         }
			break;
		case 'A':	// autoswap
      	msg ("<Autoswap mode ");

      	if (autoswap)
         {
     	   	msg ("off. ");
            autoswap = 0;
			}
         else
         {
         	msg ("on. ");
            autoswap = 1;
         }
			break;
		case 's':	// swap position
  	      if (cl_id == 1999)
     	   	msg ("<You should enter to this location first. ");
         else
         {
     	   	msg ("<Select a monster to swap.... ");
            key_direction ();
            swap_mon = monsters_planszy [temp1] [temp2];

            if (swap_mon >= 0)
            {
            	kod_f1 = floor_planszy [h_pos] [v_pos];
               kod_f2 = floor_planszy [h_pos_mon [swap_mon]] [v_pos_mon [swap_mon]];

            	if (monster_code [swap_mon] < 1100 && monster_aim [swap_mon] == -5 && (kod_f2 == kod_f1 || kod_f1 >= 0 && kod_f1 <= 10))		// ten sam teren, neutralny NPC
               {
						key = 0;
                  refresh_view_monsters ();

                  monsters_planszy [h_pos_mon [swap_mon]] [v_pos_mon [swap_mon]] = -1;
                  monsters_planszy [h_pos] [v_pos] = swap_mon;

                  h_pos_mon [swap_mon] = h_pos;
                  v_pos_mon [swap_mon] = v_pos;

                  h_pos = temp1;
                  v_pos = temp2;
					   ustaw_gracza ();
					   rysuj_view_range ();
                  verify_visible_monsters ();
                  event (h_pos, v_pos);
               	msg ("You swapped position");
               }
               else
               {
                  enter_monster (monster_code [swap_mon], COLOR_GRAY, 0, 0);
               	msg (" resists");
               }
            }
            else if (swap_mon == -1)
            	msg (" You cannot swap yourself");
            else
            	msg (" There is no monster to swap");

            kropka (COLOR_GRAY);
         }
			break;
		case 'f':	// 'f' = pick up
         if (cl_id == 1999)
  	      	msg ("<You should enter to this location first. ");
			else
         {
           	if (items_planszy [h_pos] [v_pos] == -1)
					msg ("<There is nothing to pick up. ");
				else
  	   	   {
					action_pickup (21, h_pos, v_pos);
  	   	      statystyki (0);
   	   	   turn ();
            }
         }
			break;
		case 'a':	// look
			look ();
			break;
		case 62: 	// '>' enter location
			kod_p = obstacles_planszy [h_pos] [v_pos];

			if (kod_p >= 0 && (item_group [kod_p] == 50 && item_type [kod_p] == 2 || item_group [kod_p] == 61 && item_type [kod_p] == 16) || cl_id == 1999)
				change_location (10);
			break;
		case 60:	// '<' leave location
			kod_p = obstacles_planszy [h_pos] [v_pos];

			if (kod_p >= 0 && (item_group [kod_p] == 50 && item_type [kod_p] == 1) || (cl_id >= 0 && cl_id <= 1199))
				change_location (20);
			break;
		case 'Q':       // save
			msg ("<Do you want to save game and exit (y/n) ?");

         if (answer ())
				save ();
         else
           	msg_reset ();
			break;
			break;
  	   case 'C':		// chat
     	   if (cl_id == 1999)
         	msg ("<You should enter to this location first. ");
  	      else
     	   {
	      	chat ();
  		   	turn ();
     	   }
     	   break;
  	   case 'q':
      	display_quests ();
  	      break;
/*     	case 'a':		// abilities
      	clrscr ();
  	      display_abilities ();
        	rysuj_ekran ();
  	   	break;*/
      case 'v':		// use a tool 
  	      if (cl_id == 1999)
     	   	msg ("<You should enter to this location first. ");
         else
	         select_a_tool ();
        	break;
      case 'P':		// pay
  	      if (cl_id == 1999)
     	   	msg ("<You should enter to this location first. ");
         else
	         select_item_to_pay ();
        	break;
/*      case 'A':		// assassinate
  	      if (cl_id == 1999)
     	   	msg ("<You should enter to this location to find a proper target. ");
         else
         {
	      	if (item_body [_MECH_CLAW] >= 0)
		         mechanical_blade ();
      	   else
					msg ("<Find a proper assassin's weapon first. ");
         }
        	break;*/
      case 't':		// shooting
     	   if (cl_id == 1999)
         	msg ("<You should enter to this location to find a certain target. ");
         else
         {
         	if (item_body [_SIDEARM_SLOT] != -1 || item_body [_PRIME_SLOT] != -1)
            {
            	if (current_weapon == 1)
               {
	            	if (item_specials2 [item_body [_SIDEARM_SLOT]])
                  {
                  	if (unpaid_items [item_body [_SIDEARM_SLOT]] && (kod_s = search_shopkeeper (floor_planszy [h_pos] [v_pos]) >= 0) && monster_pp [kod_s] >= 0)
		               	msg ("<Pay for this gun first! ");
                     else
				         	targeting (-1, current_weapon, 0);	// -1: shooter = player; 1: shooting; 0: spell type
                  }
   		         else
      		        	msg ("<Reload weapon first. ");
               }
               else
               {
	            	if (item_specials2 [item_body [_PRIME_SLOT]])
                  {
                  	if (unpaid_items [item_body [_PRIME_SLOT]] &&  (kod_s = search_shopkeeper (floor_planszy [h_pos] [v_pos]) >= 0) && monster_pp [kod_s] >= 0)
		               	msg ("<Pay for this weapon first! ");
                     else
				         	targeting (-1, current_weapon, 0);	// -1: shooter = player; 2: bazooka; 0: spell type
                  }
   		         else
      		        	msg ("<Load some ammo first. ");
               }

               statystyki (10);
            }
            else
     	        	msg ("<Arm yourself first. ");
         }
         break;
      case 'x':
      	if (current_weapon == 2 && item_body [_SIDEARM_SLOT] >= 0)
	      	current_weapon = 1;
      	else if (current_weapon == 1 && item_body [_PRIME_SLOT] >= 0)
	      	current_weapon = 2;
         statystyki (10);
      	break;
      case 'r':			// reload
      	if (current_weapon == 1 && item_body [_SIDEARM_SLOT] >= 0)
         {
         	kod_p = search_item (25, item_ident [item_body [_SIDEARM_SLOT]]);

            if (kod_p >= 0)
            {
            	if (unpaid_items [kod_p])
               	msg ("<Pay for the ammo first! ");
               else
               {
               	if (item_specials2 [item_body [_SIDEARM_SLOT]] < item_dv [item_body [_SIDEARM_SLOT]])
                  {
							msg ("<You reload ");
   		      		enter_item (item_body [_SIDEARM_SLOT], COLOR_GRAY);
      		        	ujmij_item (kod_p, 1);
         		      item_specials2 [item_body [_SIDEARM_SLOT]] ++;
            		   kropka (COLOR_GRAY);
               		turn ();
                  }
                  else
                  	msg ("<Your weapon is full already. ");
               }
            }
            else
              	msg ("<You do not have any ammo. ");
         }
      	else if (current_weapon == 2 && item_body [_PRIME_SLOT] >= 0)
         {
         	kod_p = search_item (25, item_ident [item_body [_PRIME_SLOT]]);

            if (kod_p >= 0)
            {
            	if (unpaid_items [kod_p])
               	msg ("<Pay for the ammo first! ");
               else
               {
               	if (item_specials2 [item_body [_PRIME_SLOT]] < item_dv [item_body [_PRIME_SLOT]])
                  {
							msg ("<You reload ");
      		   		enter_item (item_body [_PRIME_SLOT], COLOR_GRAY);
            		  	ujmij_item (kod_p, 1);
		               item_specials2 [item_body [_PRIME_SLOT]] ++;
      		         kropka (COLOR_GRAY);
            		   turn ();
                  }
                  else
                  	msg ("<Your weapon is full already. ");
               }
            }
            else
              	msg ("<You do not have any ammo. ");
         }
         statystyki (10);
      	break;
     	case 'w':		// basic characteristics
  	      display_character ();
         rysuj_ekran ();
     	   break;
     	case 'g':		// gear
//      	clrscr ();
  	      gear_menu ();
         rysuj_ekran ();
     	   break;
      case ':':		// advanced options
        	while (1)
         {
           	klawisz ();

            if (key == 'k')
            {
              	klawiszologia ();
               break;
            }
            else if (key == 'g')
            {
              	display_progress ();
               break;
            }
		     	else if (key == 'I')			// debug_info
            {
		      	clrscr ();
  	   			debug_info ();
		         rysuj_ekran ();
     				break;
            }
            else if (key == 'm')
            {
/*					clrscr ();

     		      for (i = 0; i < x_planszy; i ++)
               	for (j = 0; j < y_planszy; j ++)
                  	mem_planszy [i] [j] = plansza [i] [j];

           		rysuj_ekran ();*/
               break;
            }
            else if (key == 27)
              	break;
			}
         break;
		case 'm':		// message buffor
			clrscr ();
         message_buffor ();
         rysuj_ekran ();
         break;
/*      case 'z':		// 'z'ap a wand
	      if (cl_id != 1999)
         {
         	item_id = search_item (21, 0);

  	         if (item_id == -2)
     	      	msg ("<You don't own any wands. ");
	     	   else
           		select_a_wand ();	// choose a wand to zap
         }
         else
           	msg ("<Find a suitable place to use a wand first. ");
	     	break;*/
		case 'e':		// eat
	      item_id = search_item (19, 0);

         if (item_id == -2)
           	msg ("<You should hunt to find some food. ");
         else
         {
           	if (character_state [0] == 6)
              	msg ("<You are full now. ");
            else
            {
	      	   if (cl_id == 1999)
   		      	msg ("<Enter location to find suitable place. ");
               else
	            	eat ();
            }
         }
        	break;
		case 88:			// Shift + x = exit
			msg ("<Do you really want to quit (y/n) ?");

         if (answer ())
           	play = 0;
         else
           	msg_reset ();
			break;
		case 'k':
        	klawiszologia ();
			break;
		case 27:
      case '?':
        	msg ("<Press: k - keyboard   I - instructions    [Esc] - exit");

         while (1)
         {
           	klawisz ();

            if (key == 'k')
            {
              	klawiszologia ();
               break;
            }
            else if (key == 27)
            {
              	msg_reset ();
	           	break;
            }
            else if (key == 'I')
            {
              	instructions ();
	           	break;
            }
         }
         break;
	}
}

void key_direction ()
{
	int x_pos, y_pos;

	while (1)
   {
	  	klawisz ();

      switch (key)
		{
	     	case '1':
  	         x_pos = h_pos - 1; y_pos = v_pos + 1;
     	      break;
        	case '2':
         case 2:
         case 82:
            x_pos = h_pos; y_pos = v_pos + 1;
            break;
  	   	case '3':
     	      x_pos = h_pos + 1; y_pos = v_pos + 1;
            break;
       	case '4':
         case 4:
	         x_pos = h_pos - 1; y_pos = v_pos;
  	         break;
     		case '5':
            x_pos = h_pos; y_pos = v_pos;
            break;
  	   	case '6':
         case 5:
            x_pos = h_pos + 1; y_pos = v_pos;
            break;
			case '7':
  	         x_pos = h_pos - 1; y_pos = v_pos - 1;
            break;
        	case '8':
         case 3:
         case 83:
  	         x_pos = h_pos; y_pos = v_pos - 1;
            break;
       	case '9':
            x_pos = h_pos + 1; y_pos = v_pos - 1;
            break;
		}

      if (key >= 49 && key <= 57 || key >= 2 && key <= 5 || key == 82 || key == 83)
	     	break;
      else if (key == 27)
      {
	     	x_pos = h_pos;
         y_pos = v_pos;
		}
	}

   temp1 = x_pos;
   temp2 = y_pos;
}

