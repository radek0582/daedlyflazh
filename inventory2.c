#include "deklaracje.h"

void gear_menu ()
{
	int i = 1, kod_k, kod_p, kod_f, position_inv = 0, x, _refresh = 1;
   int choosen;
   char place = 32;
   
   chosen_hand = 0;
  	wybierz_item = 0;

	while (i)
	{
   	if (_refresh)
			make_window (0, 2, 0, 0, 60, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
			 "-GEAR MENU-                                       - ESC -^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                                                         ^n"
			 "                      **************G*E*A*R**************^n"
			 "                      *                                 *^n"
			 "                      *                                 *^n"
			 "                      *                                 *^n"
			 "                      *                                 *^n"
			 "                      *                                 *^n"
			 "                      *                                 *^n"
			 "                      ***********************************"
		   , 8, 8);												// 8: kolor ramki, 8: kolor tekstu

      if (!position_inv)
		{
      	for (x = _MELEE_SLOT; x <= _BODY_SLOT; x ++)
         {
	      	gotoxy (41, 17 + x);
   	     	item_id = item_body [x];
            i_y = x;

      	   if (item [item_body [x]] == 4)
         		enter_item (item_id, place + 7);
            else
            	messages ("[none]", 0, place + 7);
         }
		}
      else
		{
      	gotoxy (41, 17 + position_inv);
        	item_id = item_body [position_inv];
			i_y = position_inv + 3;

         if (item [item_body [position_inv]] == 4)
         	enter_item (item_id, place + 7);
         else
           	messages ("[none]", 0, place + 7);
		}

   	choosen = choice (4, "1111", _ESC, 'v', -1, 104, -1, COLOR_GRAY, COLOR_GRAY, 26, 18, position_inv);
		item_id = 0;

		if (choosen >= 1 && choosen <= 4)
		{
			kod_p = item_body [choosen];

			if (item [kod_p] == 4)			// jest zalozony
			{
        		temp = search_identical_item (-1, kod_p);

				if (item_group [kod_p] == 17)				// kasa
              	inventory_to_backpack (temp, kod_p, choosen);
            else
            {
	            if (item_group [kod_p] == 15)			// tools
   	         {
  	   	      	kod_f = floor_planszy [h_pos] [v_pos];

     	   	   	if (item_type [kod_p] == 3)		// climbing set
                  {
                    	if (kod_f == 26 || kod_f == 27 || kod_f == 42)		// mountains
          	   	   {
            	   		inventory_message ("Are you sure to put to backpack the climbing set while being on a mountain ?!");

  	               		if (key == 'y')
									inventory_to_backpack (temp, kod_p, choosen);
                     }
                     else
                       	inventory_to_backpack (temp, kod_p, choosen);
						}
                  else if (item_type [kod_p] == 1)		// torch
                  {
                    	if (item_specials2 [kod_p])
                     {
                       	inventory_message ("Do you want to extinguish the torch and put it into backpack ?");

                        if (key == 'y')
                        {
                          	inventory_to_backpack (temp, kod_p, choosen);
                           item_specials2 [kod_p] = 0;
                        }
                     }
                     else
                      	inventory_to_backpack (temp, kod_p, choosen);
                  }
                  else
                    	inventory_to_backpack (temp, kod_p, choosen);
	            }
               else
		           	inventory_to_backpack (temp, kod_p, choosen);
            }

				clear_area (40, choosen + 17, 57, choosen + 17);
				position_inv = choosen;
            _refresh = 0;
			}
			else							// pusty slot -> szukaj item'a
			{
				grupa_items = choosen;			// 1 dla helmets, 2 dla necklackes...
     	   	chosen_hand = grupa_items;

/*				if (grupa_items == _RHAND || grupa_items == _LHAND)
           		grupa_items = 100;	// wszystkie przedmioty do reki
            else if (grupa_items == _LEGS)
            	grupa_items = 9;
            else if (grupa_items == _MECH_CLAW)
            	grupa_items = 6;*/

				inventory_selector (1, 0, 0);
//				wear ();
            position_inv = 0;
				_refresh = 1;
			}
		}
		else if (choosen == _ESC + 300)		// ESC = Exit
			i = 0;
		else if (choosen == _v + 300)
		{
			backpack ();
         position_inv = 0;
			_refresh = 1;
		}
   }
}

/*void gear_menu ()
{
	exit_list = 0;

	make_window (0, 0, 1, 0, 77, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze

//0123456789012345678901234567890123456789012345678901234567890123456789
 "##########################################################################^n"
 "#-GEAR MENU-                                                      - ESC -#^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                                                                        #^n"
 "#                       **********************G*E*A*R********************#^n"
 "#                       *                                               *#^n"
 "#                       *MELEE SLOT   :                                 *#^n"
 "#                       *SIDEARM SLOT :                                 *#^n"
 "#                       *PRIME SLOT   :                                 *#^n"
 "#                       *BODY         :                                 *#^n"
 "#                       *                                               *#^n"
 "#                       *************************************************#^n"
 "##########################################################################"
   , 8, 8);												// 8: kolor ramki, 8: kolor tekstu

   if (item_body [_MELEE_SLOT] != -1)
   {
   	gotoxy (4, 6);
	   messages ("Right hand: ", 0, 23);

      if (hit_r >= 0)
			messages ("+", 0, 23);

      messages ("^ bonus to hit. ", hit_r, 23);
		messages ("^", item_dices [item_body [_RHAND]] / 100, 23);
      messages ("d^", item_dices [item_body [_RHAND]] % 100, 23);

      if (damage_r >= 0)
      	messages (" +", 0, 23);

		messages ("^ damage.", damage_r, 23);
   }

	if (item_body [_LHAND] != -1)		// lewa lapa
   {
   	gotoxy (4, 8);
	   messages ("Left hand: ", 0, 23);

      if (hit_l >= 0)
			messages ("+", 0, 23);

      messages ("^ bonus to hit. ", hit_l, 23);
		messages ("^", item_dices [item_body [_LHAND]] / 100, 23);
      messages ("d^", item_dices [item_body [_LHAND]] % 100, 23);

      if (damage_l >= 0)
      	messages (" +", 0, 23);

		messages ("^ damage.", damage_l, 23);
   }

	if (item_body [_MWAMMO] != -1)		// missiles
   {
   	gotoxy (4, 10);
	   messages ("Missiles. Hit bonus: ", 0, 23);

      if (hit_m >= 0)
			messages ("+", 0, 23);

      messages ("^. Damage: ", hit_m, 23);
		messages ("^", item_dices [item_body [_MWAMMO]] / 100, 23);
      messages ("d^", item_dices [item_body [_MWAMMO]] % 100, 23);

      if (damage_m >= 0)
      	messages (" +", 0, 23);

     	messages ("^.", damage_m, 23);
   }

	while (!exit_list)
   {
   	klawisz ();

		if (key == _ESC)
      	exit_list = 1;
   }
}*/

void inventory ()
{
	int i = 1, kod_k, kod_p, kod_f, position_inv = 0, x, _refresh = 1;
   int choosen;
   char place = 16;
   chosen_hand = 0;
  	wybierz_item = 0;

	while (i)
	{
   	if (_refresh)
			make_window (0, 2, 0, 0, 78, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
		   "^n   Part of body                      Item                           Weight"
		   "^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n   Esc - exit   'v' - backpack   'a' - 'j' - select a part of body"
   		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu

      if (!position_inv)
		{
      	for (x = _MELEE_SLOT; x <= _BODY_SLOT; x ++)
         {
	      	gotoxy (20, 5 + x);
   	     	item_id = item_body [x];
            i_y = x;

      	   if (item [item_body [x]] == 4)
         		enter_item (item_id, place + 7);
         }
		}
      else
		{
      	gotoxy (20, 5 + position_inv);
        	item_id = item_body [position_inv];
			i_y = position_inv + 3;

         if (item [item_body [position_inv]] == 4)
         	enter_item (item_id, place + 7);
		}

   	choosen = choice (10, "1111111111", _ESC, 'v', -1, 104, 5, 7, 4, 7, 6, position_inv);
		item_id = 0;

		if (choosen >= _MELEE_SLOT && choosen <= _BODY_SLOT)
		{
			kod_p = item_body [choosen];

			if (item [kod_p] == 4)			// jest zalozony
			{
        		temp = search_identical_item (-1, kod_p);

				if (item_group [kod_p] == 17)				// kasa
              	inventory_to_backpack (temp, kod_p, choosen);
            else
            {
					if (item_status [kod_p] != 2)				// nie cursed
  	            {
   	            if (item_group [kod_p] == 15)			// tools
  	   	         {
     	   	      	kod_f = floor_planszy [h_pos] [v_pos];

        	   	   	if (item_type [kod_p] == 3)		// climbing set
                     {
                       	if (kod_f == 26 || kod_f == 27 || kod_f == 42)		// mountains
            	   	   {
  	            	   		inventory_message ("Are you sure to put to backpack the climbing set while being on a mountain ?!");

     	               		if (key == 'y')
										inventory_to_backpack (temp, kod_p, choosen);
                        }
                        else
                          	inventory_to_backpack (temp, kod_p, choosen);
	                  }
                     else if (item_type [kod_p] == 1)		// torch
                     {
                       	if (item_specials2 [kod_p])
                        {
                          	inventory_message ("Do you want to extinguish the torch and put it into backpack ?");

                           if (key == 'y')
                           {
                             	inventory_to_backpack (temp, kod_p, choosen);
                              item_specials2 [kod_p] = 0;
                           }
                        }
                        else
                          	inventory_to_backpack (temp, kod_p, choosen);
                     }
                     else
                       	inventory_to_backpack (temp, kod_p, choosen);
  		            }
                  else
	               	inventory_to_backpack (temp, kod_p, choosen);
     	         }
            }

				clear_area (19, choosen + 5, 77, choosen + 5);
				position_inv = choosen;
            _refresh = 0;
			}
			else							// pusty slot -> szukaj item'a
			{
				grupa_items = choosen;			// 1 dla helmets, 2 dla necklackes...
     	   	chosen_hand = grupa_items;

/*				if (grupa_items == _RHAND || grupa_items == _LHAND)
           		grupa_items = 100;	// wszystkie przedmioty do reki
            else if (grupa_items == _LEGS)
            	grupa_items = 9;
            else if (grupa_items == _MECH_CLAW)
            	grupa_items = 6;*/

				inventory_selector (1, 0, 0);
//				wear ();
            position_inv = 0;
				_refresh = 1;
			}
		}
		else if (choosen == _ESC + 300)		// ESC = Exit
			i = 0;
		else if (choosen == _v + 300)
		{
			backpack ();
         position_inv = 0;
			_refresh = 1;
		}
   }
}

void inventory_to_backpack (int kod_in, int kod_out, char body_part)
{
	if (kod_in != -1)								// gdy identyczny item jest w plecaku
   {
      item_amount [kod_in] ++;
     	delete_item (kod_out);
		item_body [body_part] = -1;			 
   }
   else
   {
		item [kod_out] = 1;						// z powrotem do plecaka
		item_body [body_part] = -1;
  	}
}

void inventory_message (char warn_text [])
{
	clear_area (2, 24, 79, 24);
	gotoxy (2, 24);
	messages (warn_text, 0, 23);

   while (1)
   {
   	klawisz ();

      if (key == 'y' || key == 'n' || key == 32)
      	break;
   }

	clear_area (2, 24, 79, 24);
	gotoxy (2, 24);
	messages ("Esc - exit   'v' - backpack   'a' - 'n' - select a part of body", 0, 27);
}

void backpack ()
{
	grupa_items = 100;
   inventory_selector (4, 0, 0);		// backpack
}

void list_item ()
{
/*	if (temp == 1)
	{
   	textcolor (6);

		switch (grupa_items)
		{
			case _MELEE_SLOT:
				printwf ("\n### Melee weapons ###");
				break;
         case _SIDEARM_SLOT:
         	printwf ("\n### Sidearm weapons ###");
            break;
			case _PRIME_SLOT:
				printwf ("\n### Helmets ###");
				break;
         case _BODY:
         	printwf ("\n### Wearings ###");
            break;
         case 6:
         	printwf ("\n### Mechanical blades ###");
            break;
         case 7:
         	printwf ("\n### Missile weapons ###");
            break;
         case 8:
         	printwf ("\n### Missiles ###");
            break;
         case 9:
         	printwf ("\n### Downgears ###\n\n\r ");
            break;
         case 15:
         	printwf ("\n### Tools ###\n\n\r ");
            break;
         case 16:
         	printwf ("\n### Gems ###\n\n\r ");
            break;
         case 17:
         	printwf ("\n### Money ###\n\n\r ");
            break;
         case 18:
         	printwf ("\n### Scrolls ###\n\n\r ");
            break;
         case 19:
         	printwf ("\n### Food ###\n\n\r ");
            break;
         case 20:
         	printwf ("\n### Shields ###\n\n\r ");
            break;
         case 21:
         	printwf ("\n### Wands ###\n\n\r ");
            break;
         case 23:
         	printwf ("\n### Potions ###\n\n\r ");
            break;
         case 24:
         	printwf ("\n### Keys ###\n\n\r ");
            break;
         case 29:
         	printwf ("\n### Miscellaneous stuff ###\n\n\r ");
            break;
		}
		i_y += 3;
	}*/

	gotoxy (4, i_y + 5);		// i_y zwiekszone
	enter_item (item_id, 23);
	temp = 0;
	i_y ++;
}

void sub_messages (int msg_no1, int msg_no2, int msg_no3)
{
   if (msg_no1 == 1)
   {
     	gotoxy (8, 23);
     	messages ("v - page down", 0, 24);
	}
   else if (msg_no1 == -1)
   	clear_area (8, 23, 21, 23);

   if (msg_no2 == 1)
   {
     	gotoxy (22, 23);
     	messages ("Home - first page", 0, 24);
   }
   else if (msg_no2 == -1)
   	clear_area (22, 23, 40, 23);

   if (msg_no3 == 1)
   {
     	gotoxy (41, 23);
      addch ('^');
	  	messages (" - page up", 0, 24);
	}
   else if (msg_no3 == -1)
   	clear_area (41, 23, 60, 23);
}

void inventory_selector (int selected, int x_pos, int y_pos)
{
	int itemy_w_miejscu_amount = 0;
	int item_id_w_miejscu, last_item_id = -1;
   int itemy_w_miejscu [10000];
   int item_id_storage [1000];
   int grupa_items_storage [1000];
   int item_id_index = 0;
   int grupa_items_index;

	if (selected <= 20)			// w plecaku
	   for (item_id = 0; item_id < items_amount; item_id ++)
   	{
	   	if (item [item_id] == 1)
   	   {
      		itemy_w_miejscu [itemy_w_miejscu_amount] = item_id;
         	itemy_w_miejscu_amount ++;
	      }
   	}
   else
   {
   	grupa_items = 100;

	   for (item_id = 0; item_id < items_amount; item_id ++)
   	{
	  		if (item [item_id] == 3 && h_pos_item [item_id] == x_pos && v_pos_item [item_id] == y_pos)
   	  	{
      		itemy_w_miejscu [itemy_w_miejscu_amount] = item_id;
         	itemy_w_miejscu_amount ++;
	     	}
   	}
   }

   grupa_items_index = grupa_items;

   if (grupa_items == 100)
   {
   	for (grupa_items = 30; grupa_items > 0; grupa_items --)
      {
      	for (item_id_w_miejscu = 0; item_id_w_miejscu < itemy_w_miejscu_amount; item_id_w_miejscu ++)
	      	if (item_group [itemy_w_miejscu [item_id_w_miejscu]] == grupa_items)
					break;

         if (item_group [itemy_w_miejscu [item_id_w_miejscu]] == grupa_items)
         	break;
      }
   }

  	for (item_id_w_miejscu = itemy_w_miejscu_amount - 1; item_id_w_miejscu >= 0; item_id_w_miejscu --)
   {
		if (item_group [itemy_w_miejscu [item_id_w_miejscu]] == grupa_items)
      {
        	last_item_id = itemy_w_miejscu [item_id_w_miejscu];
         break;
	   }
   }

   grupa_items = grupa_items_index;
	grupa_items_index = item_id_w_miejscu = exit_list = temp = item_id = 0;
//	clear ();
	i_y = 0;
   alfabet = 97;
	wybierz_item = 1;

	if (selected == 1)
   {
		make_window (0, 2, 0, 0, 60, 23, -2,
		   "       Choose an item to wear                     - ESC -"
	  		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
   }
   else if (selected == 2)
   {
		make_window (0, 2, 0, 0, 60, 20, -2,
		   "       Select an item to drop                     - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
   }
   else if (selected == 3)
   {
		make_window (0, 2, 0, 0, 60, 20, -2,
		   "         Select your meal                         - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
   }
   else if (selected == 4)
   {
		make_window (0, 2, 0, 0, 60, 23, -2,
		   "              Item                                - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
      wybierz_item = 0;
   }
   else if (selected == 5)
   {
		make_window (0, 2, 0, 0, 60, 20, -2,
		   "        Select item to use                        - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
   }
   else if (selected == 6)
   {
		make_window (0, 2, 0, 0, 60, 20, -2,
		   "        Select item to pay for                    - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
      grupa_items = 100;
   }
	else if (selected == 21)
   {
		make_window (0, 2, 0, 0, 60, 20, -2,
		   "    Select an item to pick up                     - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
   }
   else if (selected == 22)
   {
		make_window (0, 2, 0, 0, 60, 20, -2,
		   "    You see following items                       - ESC -"
  			, 8, 8);												// 8: kolor ramki, 8: kolor tekstu
		wybierz_item = 0;
   }

   while (!exit_list)
   {
		if (grupa_items < 100)		// itemy z jednej grupy
   	{
      	temp = 1;
  	      i_y = 0;

			for (; item_id_w_miejscu < itemy_w_miejscu_amount; item_id_w_miejscu ++)
			{
           	item_id = itemy_w_miejscu [item_id_w_miejscu];

				if (item_group [item_id] == grupa_items)	// czy nalezy do danej grupy
				{
            	if (!i_y)
                  item_id_storage [item_id_index] = item_id_w_miejscu;

  		      	gotoxy (4, 4 + i_y);
					list_item ();

					if (i_y > 12 && item_id != last_item_id)
					{
  	         		i_y = 0;
                  sub_messages (1, 0, 0);

						while (!exit_list)
						{
							klawisz ();

							if (key == 2 || key == '2' || key == 82)
							{
	                     sub_messages (0, 1, 1);
        	               alfabet = 97;
								temp = 1;
                        item_id_index ++;
								clear_area (3, 5, 60, 20);
								break;
							}
     	      	      else if ((key == '8' || key == 3 || key == 83) && item_id_index)
      	      	   {
  	      	      		alfabet = 97;
                        temp = 1;
       	            	clear_area (3, 5, 60, 20);
                        item_id_w_miejscu = item_id_storage [item_id_index - 1] - 1;
                        item_id_index --;

                        if (!item_id_index)
                          	sub_messages (0, -1, -1);

         	            break;
	         	      }
							else if (key == 6 && item_id_index)
							{
								clear_area (3, 5, 60, 20);
								item_id_w_miejscu = -1;
        	               temp = 1;
     				         item_id_index = 0;
								alfabet = 97;
                        sub_messages (0, -1, -1);
            		      break;
							}
							else if (key >= 'a' && key < alfabet && wybierz_item)
                     	action_inventory (selected);
							else if (key == 27)
                     {
                      	if (selected == 2 || selected == 3 || selected == 5 || selected == 6)
                          	rysuj_ekran ();

								exit_list = 1;
                     }
						}
					}
	         }
  	         if (exit_list)
            	break;
  		   }
		}
	   else		// wszystkie itemy
	   {
	   	i_y = 0;

         if (grupa_items == 100)
			   grupa_items = 1;
         else
         	grupa_items -= 100;

   		for (; grupa_items < 30; grupa_items ++)
  	   	{
	      	temp = 1;

            if (key != '+')
               item_id_w_miejscu = 0;
            else
               key = 0;

  		      for (; item_id_w_miejscu < itemy_w_miejscu_amount; item_id_w_miejscu ++)
     		   {
            	item_id = itemy_w_miejscu [item_id_w_miejscu];

	         	if (item_group [item_id] == grupa_items && (selected != 6 || selected == 6 && item_value_material [item_id] % 100 >= 50))
  		         {
	            	if (!i_y)
   	               item_id_storage [item_id_index] = item_id_w_miejscu;

   		      	gotoxy (4, 4 + i_y);
  	   		      list_item ();

	     	   	   if (i_y > 12 && item_id != last_item_id)
   	   	   	{
   	         		i_y = 0;
                     sub_messages (1, 0, 0);

	         	      while (!exit_list)
  		         	   {
     		         		klawisz ();

      	      	      if ((key == '8' || key == 3 || key == 83) && item_id_index)		// + lub PgUP
  	      	      	   {
     	      	      		alfabet = 97;
         	            	clear_area (3, 5, 60, 20);
                           item_id_w_miejscu = item_id_storage [item_id_index - 1];
                           grupa_items = grupa_items_storage [grupa_items_index - 1] - 1;
                           item_id_index --;
                           grupa_items_index --;

                           if (!item_id_index)
                             	sub_messages (0, -1, -1);

	         	            break;
  		         	      }
								else if (key == 2 || key == '2' || key == 82) 		// pgDown
								{
		                     sub_messages (0, 1, 1);
         	               alfabet = 97;
									temp = 1;
                           grupa_items_storage [grupa_items_index] = item_group [itemy_w_miejscu [item_id_storage [item_id_index]]];
                           item_id_index ++;
                           grupa_items_index ++;
									clear_area (3, 5, 60, 20);
									break;
								}
	      	            else if (key == 6 && item_id_index)			// first page = Home
  		      	         {
									clear_area (3, 5, 60, 20);
									item_id_w_miejscu = -1;
           	               temp = 1;
        				         grupa_items = item_id_index = 0;
									alfabet = 97;
                           sub_messages (0, -1, -1);
  	            		      break;
   	               	}
  	   	            	else if (key >= 'a' && key < alfabet && wybierz_item)
                        	action_inventory (selected);
  			               else if (key == 27)			// Esc
                        {
                        	if (selected == 2 || selected == 3 || selected == 5 || selected == 6 || selected == 21 )
                           	rysuj_ekran ();

        			         	exit_list = 1;
                        }
		               }
  		            }
     		      }
      	      if (exit_list || key == '+')
  	      	   	break;
      	   }
	         if (exit_list)		// po nacisnieciu ESC
  		      	break;
     		}
	   }

      if (item_id_index)
      	sub_messages (-1, 0, 0);

		while (!exit_list)
		{
			klawisz ();

			if (key == 6 && item_id_index)
      	{
    	   	temp = 1;
      		clear_area (3, 5, 60, 20);
  	         item_id_w_miejscu = 0;

            if (grupa_items_index)
					grupa_items = 100;

        	   alfabet = 97;
            item_id_index = grupa_items_index = 0;
				sub_messages (0, -1, -1);
	      	break;
      	}
      	else if ((key == '8' || key == 3 || key == 83) && item_id_index)					// pgUP
  		   {
      		alfabet = 97;
  	         temp = 1;
           	clear_area (3, 5, 60, 20);
				item_id_w_miejscu = item_id_storage [item_id_index - 1];
				item_id_index --;

				if (grupa_items_index)
            {
					grupa_items = 100 + grupa_items_storage [grupa_items_index - 1] - 1;
					grupa_items_index --;
            }

				if (!item_id_index)
              	sub_messages (0, -1, -1);

//            item_id = item_id_temp;
//            grupa_items = 100 + grupa_items_temp;
            break;
     	   }
			else if (key >= 'a' && key < alfabet && wybierz_item)
         	action_inventory (selected);
			else if (key == 27)		// Esc
         {
           	if (selected == 2 || selected == 3 || selected == 5 || selected == 6 || selected == 21)
              	rysuj_ekran ();

				exit_list = 1;
         }
		}
	}

   chosen_hand = 0;
	wybierz_item = 0;
}

void action_inventory (int selected)
{
	item_id = inv [key - 96];

	if (selected == 1)		// wear
   {
	  	if (item_amount [item_id] > 1)// && grupa_items != _MWAMMO)
		{
	     	divide_items (item_id, 1);
   	   item_id = items_amount - 1;
	   }

		item [item_id] = 4;	// item do inventory

      if (!item_ident [item_id])
			item_ident [item_id] = 1;	// czesciowa identyfikacja

/*	   if (grupa_items == 23)
			grupa_items = 12;
	   else if (grupa_items == 12 || grupa_items == 13)
			grupa_items ++;*/

		item_body [chosen_hand] = item_id;
		exit_list = 1;
//		clear ();
	}
   else if (selected == 2)		// drop
   {
  	   exit_list = 1;
      action_item (-1, h_pos, v_pos, 1, item_id);
   }
   else if (selected == 3)		// eat
   {
  	   exit_list = 1;
  		zjadaj (item_id);
   }
   else if (selected == 5)		// use
   {
  	   exit_list = 1;
  		use_a_tool (item_id);
   }
   else if (selected == 6)		// pay
   {
  	   exit_list = 1;
      pay (item_id);
   }
   else if (selected == 21)		// pick up
   {
	   exit_list = 1;
      rysuj_ekran ();
     	action_item (-1, h_pos_item [item_id], v_pos_item [item_id], 2, item_id);
   }
}
