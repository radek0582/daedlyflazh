#include "deklaracje.h"

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
      	for (x = _HEAD; x <= _SUB_TOOL; x ++)
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

   	choosen = choice (10, "1111111111", _ESC, 'v', -1, 104, 5, 7, 23, 7, 6, position_inv);
		item_id = 0;

		if (choosen >= _HEAD && choosen <= _SUB_TOOL)
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

				clear_window (19, choosen + 5, 77, choosen + 5);
				position_inv = choosen;
            _refresh = 0;
			}
			else							// pusty slot -> szukaj item'a
			{
				grupa_items = choosen;			// 1 dla helmets, 2 dla necklackes...

				if (grupa_items == _RHAND || grupa_items == _LHAND)
     	      {
        	   	chosen_hand = grupa_items;
           		grupa_items = 100;	// wszystkie przedmioty do reki
            }
            else if (grupa_items == _LEGS)
            	grupa_items = 9;
            else if (grupa_items == _MECH_CLAW)
            	grupa_items = 6;

				wear ();
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
	clear_window (2, 24, 79, 24);
	gotoxy (2, 24);
	messages (warn_text, 0, 23);

   while (1)
   {
   	klawisz ();

      if (key == 'y' || key == 'n' || key == 32)
      	break;
   }

	clear_window (2, 24, 79, 24);
	gotoxy (2, 24);
	messages ("Esc - exit   'v' - backpack   'a' - 'n' - select a part of body", 0, 27);
}

void backpack ()
{
	int itemy_w_plecaq_amount = 0;
	int item_id_plecaq = 0, last_item_id = -1;
   int itemy_w_plecaq [10000];
   int item_id_storage [1000];
   int grupa_items_storage [1000];
   int item_id_index = 0;
   int grupa_items_index = 0;
//	int grupa_items_temp = 1, item_id_temp = 0;

   for (item_id = 0; item_id < items_amount; item_id ++)
   {
   	if (item [item_id] == 1)
      {
      	itemy_w_plecaq [itemy_w_plecaq_amount] = item_id;
         itemy_w_plecaq_amount ++;
      }
   }

	last_item_id = itemy_w_plecaq [itemy_w_plecaq_amount - 1];

	clrscr ();
	exit_list = item_id = 0;
  	wybierz_item = 0;
	grupa_items = 100;

	make_window (0, 2, 0, 0, 78, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
	   "^n                               Item                                 Weight"
	   "^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n Esc - exit"
  		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu

   while (!exit_list)
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
	         item_id_plecaq = 0;
         else
	         key = 0;

			for (; item_id_plecaq < itemy_w_plecaq_amount; item_id_plecaq ++)
			{
           	item_id = itemy_w_plecaq [item_id_plecaq];

				if (item_group [item_id] == grupa_items)		// czy danej grupy
				{
            	if (!i_y)
               {
  	               item_id_storage [item_id_index] = item_id_plecaq;
	               grupa_items_storage [grupa_items_index] = item_group [item_id];
               }

					gotoxy (4, 5 + i_y);
					list_item ();

					if (i_y > 12 && item_id != last_item_id)
					{
  	         		i_y = 0;
                  sub_messages (1, 0, 0);

						while (!exit_list)
						{
							klawisz ();

     	      	      if (key == '+' && item_id_index)
      	      	   {
        	            	clear_window (3, 5, 77, 21);
                        item_id_plecaq = item_id_storage [item_id_index - 1];
                        grupa_items = grupa_items_storage [grupa_items_index - 1] - 1;
                        item_id_index --;
                        grupa_items_index --;

                        if (!item_id_index)
                          	sub_messages (0, -1, -1);

         	            break;
	         	      }
							else if (key == 13)	// enter
							{
	                     sub_messages (0, 1, 1);
								temp = 1;
                        item_id_index ++;
                        grupa_items_index ++;
								clear_window (3, 5, 77, 21);
								break;
							}
      	            else if (key == '-' && item_id_index)
	      	         {
								clear_window (3, 5, 77, 21);
								item_id_plecaq = -1;
        	               temp = 1;
     				         grupa_items = item_id_index = 0;
                        sub_messages (0, -1, -1);
            		      break;
  	               	}
		               else if (key == 27)
     			         	exit_list = 1;
						}
					}
				}
				if (exit_list || key == '+')
					break;
			}
			if (exit_list)
				break;
		}

      if (item_id_index)
      	sub_messages (-1, 0, 0);

		while (!exit_list)
		{
			klawisz ();

			if (key == '-' && item_id_index)		// poprzednio nacisnieto '+' lub Enter
      	{
   	   	i_y = 1;
     	   	temp = 1;
      		clear_window (3, 5, 77, 21);
  	         item_id_plecaq = 0;

            if (grupa_items_index)
					grupa_items = 100;

            item_id_index = grupa_items_index = 0;
				sub_messages (0, -1, -1);
	      	break;
      	}
      	else if (key == '+' && item_id_index)
  		   {
  	         temp = 1;
           	clear_window (3, 5, 77, 21);
				item_id_plecaq = item_id_storage [item_id_index - 1];
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
			else if (key == 27)		// Esc
				exit_list = 1;
		}
	}
}

void list_item ()
{
	if (temp == 1)
	{
   	textcolor (6);

		switch (grupa_items)
		{
			case 1:
				cprintf ("\n### Helmets ###");
				break;
			case 2:
				cprintf ("\n### Body armors ###");
				break;
         case 4:
         	cprintf ("\n### One-handed weapons ###");
            break;
         case 5:
         	cprintf ("\n### Two-handed weapons ###");
            break;
         case 6:
         	cprintf ("\n### Mechanical blades ###");
            break;
         case 7:
         	cprintf ("\n### Missile weapons ###");
            break;
         case 8:
         	cprintf ("\n### Missiles ###");
            break;
         case 9:
         	cprintf ("\n### Downgears ###\n\n\r ");
            break;
         case 15:
         	cprintf ("\n### Tools ###\n\n\r ");
            break;
         case 16:
         	cprintf ("\n### Gems ###\n\n\r ");
            break;
         case 17:
         	cprintf ("\n### Money ###\n\n\r ");
            break;
         case 18:
         	cprintf ("\n### Scrolls ###\n\n\r ");
            break;
         case 19:
         	cprintf ("\n### Food ###\n\n\r ");
            break;
         case 20:
         	cprintf ("\n### Shields ###\n\n\r ");
            break;
         case 21:
         	cprintf ("\n### Wands ###\n\n\r ");
            break;
         case 23:
         	cprintf ("\n### Potions ###\n\n\r ");
            break;
         case 24:
         	cprintf ("\n### Keys ###\n\n\r ");
            break;
		}
		i_y += 3;
	}

	gotoxy (4, i_y + 5);
	enter_item (item_id, 23);
	temp = 0;
	i_y ++;
}

void sub_messages (int msg_no1, int msg_no2, int msg_no3)
{
   if (msg_no1 == 1)
   {
     	gotoxy (18, 22);
     	messages ("Enter - page down", 0, 24);
	}
   else if (msg_no1 == -1)
   	clear_window (18, 22, 37, 22);

   if (msg_no2 == 1)
   {
     	gotoxy (38, 22);
     	messages ("'-' - first page", 0, 24);
   }
   else if (msg_no2 == -1)
   	clear_window (38, 22, 57, 22);

   if (msg_no3 == 1)
   {
     	gotoxy (58, 22);
	  	messages ("'+' - page up", 0, 24);
	}
   else if (msg_no3 == -1)
   	clear_window (58, 22, 77, 22);
}

void wear ()
{
	int itemy_w_plecaq_amount = 0;
	int item_id_plecaq, last_item_id = -1;
   int itemy_w_plecaq [10000];
   int item_id_storage [1000];
   int grupa_items_storage [1000];
   int item_id_index = 0;
   int grupa_items_index = 0;

   for (item_id = 0; item_id < items_amount; item_id ++)
   {
   	if (item [item_id] == 1)
      {
      	itemy_w_plecaq [itemy_w_plecaq_amount] = item_id;
         itemy_w_plecaq_amount ++;
      }
   }

   if (grupa_items == 100)
		last_item_id = itemy_w_plecaq [itemy_w_plecaq_amount - 1];
   else
   {
   	for (item_id_plecaq = itemy_w_plecaq_amount - 1; item_id_plecaq >= 0; item_id_plecaq --)
			if (item_group [itemy_w_plecaq [item_id_plecaq]] == grupa_items)
         {
         	last_item_id = itemy_w_plecaq [item_id_plecaq];
            break;
         }
   }

	item_id_plecaq = exit_list = temp = item_id = 0;
	clrscr ();
	i_y = 1;
   alfabet = 97;
	wybierz_item = 1;

	make_window (0, 2, 0, 0, 78, 23, -2,
	   "^n                    Choose an item to wear                          Weight"
	   "^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n Esc - exit"
  		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu

   while (!exit_list)
   {
		if (grupa_items < 100)		// itemy z jednej grupy
   	{
      	temp = 1;
  	      i_y = 0;

			for (; item_id_plecaq < itemy_w_plecaq_amount; item_id_plecaq ++)
			{
           	item_id = itemy_w_plecaq [item_id_plecaq];

				if (item_group [item_id] == grupa_items)	// czy nalezy do danej grupy
				{
            	if (!i_y)
                  item_id_storage [item_id_index] = item_id_plecaq;

  		      	gotoxy (4, 5 + i_y);
					list_item ();

					if (i_y > 12 && item_id != last_item_id)
					{
  	         		i_y = 0;
                  sub_messages (1, 0, 0);

						while (!exit_list)
						{
							klawisz ();

							if (key == 13)	// enter
							{
	                     sub_messages (0, 1, 1);
        	               alfabet = 97;
								temp = 1;
                        item_id_index ++;
								clear_window (3, 5, 77, 21);
								break;
							}
     	      	      else if (key == '+' && item_id_index)
      	      	   {
  	      	      		alfabet = 97;
                        temp = 1;
       	            	clear_window (3, 5, 77, 21);
                        item_id_plecaq = item_id_storage [item_id_index - 1] - 1;
                        item_id_index --;

                        if (!item_id_index)
                          	sub_messages (0, -1, -1);

         	            break;
	         	      }
							else if (key == '-' && item_id_index)
							{
								clear_window (3, 5, 77, 21);
								item_id_plecaq = -1;
        	               temp = 1;
     				         item_id_index = 0;
								alfabet = 97;
                        sub_messages (0, -1, -1);
            		      break;
							}
							else if (key >= 'a' && key < alfabet)
							{
        	   	      	item_id = inv [key - 96];

	                  	if (item_amount [item_id] > 1 && grupa_items != _MWAMMO)
  		                  {
     		               	divide_items (item_id, 1);
        		               item_id = items_amount - 1;
           		         }

								item [item_id] = 4;	// item do inventory

      	               if (!item_ident [item_id])
									item_ident [item_id] = 1;	// czesciowa identyfikacja

/*	   	      	      if (grupa_items == 23)
									grupa_items = 12;
            			   else if (grupa_items == 12 || grupa_items == 13)
									grupa_items ++;*/

								item_body [grupa_items] = item_id;
								exit_list = 1;
								clrscr ();
							}
							else if (key == 27)
								exit_list = 1;
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
               item_id_plecaq = 0;
            else
               key = 0;

  		      for (; item_id_plecaq < itemy_w_plecaq_amount; item_id_plecaq ++)
     		   {
            	item_id = itemy_w_plecaq [item_id_plecaq];

	         	if (item_group [item_id] == grupa_items)
  		         {
	            	if (!i_y)
   	               item_id_storage [item_id_index] = item_id_plecaq;

   		      	gotoxy (4, 5 + i_y);
  	   		      list_item ();

	     	   	   if (i_y > 12 && item_id != last_item_id)
   	   	   	{
   	         		i_y = 0;
                     sub_messages (1, 0, 0);

	         	      while (!exit_list)
  		         	   {
     		         		klawisz ();

      	      	      if (key == '+' && item_id_index)
  	      	      	   {
     	      	      		alfabet = 97;
         	            	clear_window (3, 5, 77, 21);
                           item_id_plecaq = item_id_storage [item_id_index - 1];
                           grupa_items = grupa_items_storage [grupa_items_index - 1] - 1;
                           item_id_index --;
                           grupa_items_index --;

                           if (!item_id_index)
                             	sub_messages (0, -1, -1);

	         	            break;
  		         	      }
								else if (key == 13)	// enter
								{
		                     sub_messages (0, 1, 1);
         	               alfabet = 97;
									temp = 1;
                           grupa_items_storage [grupa_items_index] = item_group [inv [1]];
                           item_id_index ++;
                           grupa_items_index ++;
									clear_window (3, 5, 77, 21);
									break;
								}
	      	            else if (key == '-' && item_id_index)
  		      	         {
									clear_window (3, 5, 77, 21);
									item_id_plecaq = -1;
           	               temp = 1;
        				         grupa_items = item_id_index = 0;
									alfabet = 97;
                           sub_messages (0, -1, -1);
  	            		      break;
   	               	}
  	   	            	else if (key >= 'a' && key < alfabet)
  		   	            {
        	   	         	item_id = inv [key - 96];

		                  	if (item_amount [item_id] > 1 && grupa_items != _MWAMMO)
  		                     {
  			                  	divide_items (item_id, 1);
        		                  item_id = items_amount - 1;
           		            }

      	   	         	item_body [chosen_hand] = item_id;

   	            	      if (!item_ident [item_id])
										item_ident [item_id] = 1;	// czesciowa identyfikacja

     	   	   	         item [item_id] = 4;
        	      		      exit_list = 1;
           	      		   clrscr ();
		                  }
  			               else if (key == 27)
        			         	exit_list = 1;
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

			if (key == '-' && item_id_index)		// poprzednio nacisnieto '+' lub Enter
      	{
   	   	i_y = 1;
     	   	temp = 1;
      		clear_window (3, 5, 77, 21);
  	         item_id_plecaq = 0;

            if (grupa_items_index)
					grupa_items = 100;

        	   alfabet = 97;
            item_id_index = grupa_items_index = 0;
				sub_messages (0, -1, -1);
	      	break;
      	}
      	else if (key == '+' && item_id_index)
  		   {
      		alfabet = 97;
  	         temp = 1;
           	clear_window (3, 5, 77, 21);
				item_id_plecaq = item_id_storage [item_id_index - 1];
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
			else if (key >= 'a' && key < alfabet)
			{
     			item_id = inv [key - 96];

   	     	if (item_amount [item_id] > 1 && grupa_items != _MWAMMO)
	         {
     	   	  	divide_items (item_id, 1);
     		      item_id = items_amount - 1;
   	      }

				item [item_id] = 4;	// item do inventory

     	   	if (!item_ident [item_id])
					item_ident [item_id] = 1;	// czesciowa identyfikacja

   	      if (chosen_hand)
	         	item_body [chosen_hand] = item_id;
      	   else
  		      {
/*					if (grupa_items == 23)
  						grupa_items = 12;
  				   else if (grupa_items == 12 || grupa_items == 13)
						grupa_items ++;*/

					item_body [grupa_items] = item_id;
	  	      }

				clrscr ();
				exit_list = 1;
			}
			else if (key == 27)		// Esc
				exit_list = 1;
		}
	}

   chosen_hand = 0;
	wybierz_item = 0;
}

/*void inventory_selector (int selected)
{
	int itemy_w_plecaq_amount = 0;
	int item_id_plecaq, last_item_id = -1;
   int itemy_w_plecaq [10000];
   int item_id_storage [1000];
   int grupa_items_storage [1000];
   int item_id_index = 0;
   int grupa_items_index = 0;

   for (item_id = 0; item_id < items_amount; item_id ++)
   {
   	if (item [item_id] == 1)
      {
      	itemy_w_plecaq [itemy_w_plecaq_amount] = item_id;
         itemy_w_plecaq_amount ++;
      }
   }

   if (grupa_items == 100)
		last_item_id = itemy_w_plecaq [itemy_w_plecaq_amount - 1];
   else
   {
   	for (item_id_plecaq = itemy_w_plecaq_amount - 1; item_id_plecaq >= 0; item_id_plecaq --)
			if (item_group [itemy_w_plecaq [item_id_plecaq]] == grupa_items)
         {
         	last_item_id = itemy_w_plecaq [item_id_plecaq];
            break;
         }
   }

	item_id_plecaq = exit_list = temp = item_id = 0;
	clrscr ();
	i_y = 1;
   alfabet = 97;
	wybierz_item = 1;

	make_window (0, 2, 0, 0, 78, 23, -2,
	   "^n                    Choose an item to wear                          Weight"
	   "^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n Esc - exit"
  		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu

   while (!exit_list)
   {
		if (grupa_items < 100)		// itemy z jednej grupy
   	{
      	temp = 1;
  	      i_y = 0;

			for (; item_id_plecaq < itemy_w_plecaq_amount; item_id_plecaq ++)
			{
           	item_id = itemy_w_plecaq [item_id_plecaq];

				if (item_group [item_id] == grupa_items)	// czy nalezy do danej grupy
				{
            	if (!i_y)
                  item_id_storage [item_id_index] = item_id_plecaq;

  		      	gotoxy (4, 5 + i_y);
					list_item ();

					if (i_y > 12 && item_id != last_item_id)
					{
  	         		i_y = 0;
                  sub_messages (1, 0, 0);

						while (!exit_list)
						{
							klawisz ();

							if (key == 13)	// enter
							{
	                     sub_messages (0, 1, 1);
        	               alfabet = 97;
								temp = 1;
                        item_id_index ++;
								clear_window (3, 5, 77, 21);
								break;
							}
     	      	      else if (key == '+' && item_id_index)
      	      	   {
  	      	      		alfabet = 97;
                        temp = 1;
       	            	clear_window (3, 5, 77, 21);
                        item_id_plecaq = item_id_storage [item_id_index - 1] - 1;
                        item_id_index --;

                        if (!item_id_index)
                          	sub_messages (0, -1, -1);

         	            break;
	         	      }
							else if (key == '-' && item_id_index)
							{
								clear_window (3, 5, 77, 21);
								item_id_plecaq = -1;
        	               temp = 1;
     				         item_id_index = 0;
								alfabet = 97;
                        sub_messages (0, -1, -1);
            		      break;
							}
							else if (key >= 'a' && key < alfabet)
                     	action_inventory (selected);
							else if (key == 27)
								exit_list = 1;
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
               item_id_plecaq = 0;
            else
               key = 0;

  		      for (; item_id_plecaq < itemy_w_plecaq_amount; item_id_plecaq ++)
     		   {
            	item_id = itemy_w_plecaq [item_id_plecaq];

	         	if (item_group [item_id] == grupa_items)
  		         {
	            	if (!i_y)
   	               item_id_storage [item_id_index] = item_id_plecaq;

   		      	gotoxy (4, 5 + i_y);
  	   		      list_item ();

	     	   	   if (i_y > 12 && item_id != last_item_id)
   	   	   	{
   	         		i_y = 0;
                     sub_messages (1, 0, 0);

	         	      while (!exit_list)
  		         	   {
     		         		klawisz ();

      	      	      if (key == '+' && item_id_index)
  	      	      	   {
     	      	      		alfabet = 97;
         	            	clear_window (3, 5, 77, 21);
                           item_id_plecaq = item_id_storage [item_id_index - 1];
                           grupa_items = grupa_items_storage [grupa_items_index - 1] - 1;
                           item_id_index --;
                           grupa_items_index --;

                           if (!item_id_index)
                             	sub_messages (0, -1, -1);

	         	            break;
  		         	      }
								else if (key == 13)	// enter
								{
		                     sub_messages (0, 1, 1);
         	               alfabet = 97;
									temp = 1;
                           grupa_items_storage [grupa_items_index] = item_group [inv [1]];
                           item_id_index ++;
                           grupa_items_index ++;
									clear_window (3, 5, 77, 21);
									break;
								}
	      	            else if (key == '-' && item_id_index)
  		      	         {
									clear_window (3, 5, 77, 21);
									item_id_plecaq = -1;
           	               temp = 1;
        				         grupa_items = item_id_index = 0;
									alfabet = 97;
                           sub_messages (0, -1, -1);
  	            		      break;
   	               	}
  	   	            	else if (key >= 'a' && key < alfabet)
                        	action_inventory (1);
  			               else if (key == 27)
        			         	exit_list = 1;
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

			if (key == '-' && item_id_index)		// poprzednio nacisnieto '+' lub Enter
      	{
   	   	i_y = 1;
     	   	temp = 1;
      		clear_window (3, 5, 77, 21);
  	         item_id_plecaq = 0;

            if (grupa_items_index)
					grupa_items = 100;

        	   alfabet = 97;
            item_id_index = grupa_items_index = 0;
				sub_messages (0, -1, -1);
	      	break;
      	}
      	else if (key == '+' && item_id_index)
  		   {
      		alfabet = 97;
  	         temp = 1;
           	clear_window (3, 5, 77, 21);
				item_id_plecaq = item_id_storage [item_id_index - 1];
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
			else if (key >= 'a' && key < alfabet)
         	action_inventory (1);
			else if (key == 27)		// Esc
				exit_list = 1;
		}
	}

   chosen_hand = 0;
	wybierz_item = 0;
}

void action_inventory (int selected)
{
	item_id = inv [key - 96];

	if (selected == 1)
   {
	  	if (item_amount [item_id] > 1 && grupa_items != _MWAMMO)
		{
	     	divide_items (item_id, 1);
   	   item_id = items_amount - 1;
	   }

		item [item_id] = 4;	// item do inventory

      if (!item_ident [item_id])
			item_ident [item_id] = 1;	// czesciowa identyfikacja

	   if (grupa_items == 23)
			grupa_items = 12;
	   else if (grupa_items == 12 || grupa_items == 13)
			grupa_items ++;

		item_body [grupa_items] = item_id;
		exit_list = 1;
		clrscr ();
	}
   else if (selected == 2)
   {
   }
}*/
