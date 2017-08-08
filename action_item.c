#include "deklaracje.h"

void action_pickup (int selected, int x_pos, int y_pos)
{
	int itemy_na_glebie_amount = 0;
	int item_id_gleba, last_item_id = -1;
   int itemy_na_glebie [10000];
	int i, a, kod_p;
   int item_id_storage [1000];
   int grupa_items_storage [1000];
   int item_id_index = 0;
   int grupa_items_index = 0;

	kod_p = stan_planszy [x_pos] [y_pos];	// znajdz przedmiot na mapie

   if (kod_p == 1 || kod_p == 4 || kod_p == 5 || kod_p == 7)				// just one item
   	action_item (-1, x_pos, y_pos, 2, items_planszy [x_pos] [y_pos]);
   else if (kod_p > 7)		// several items
   {
	   for (item_id = 0; item_id < items_amount; item_id ++)
	   {
   		if (item [item_id] == 3 && h_pos_item [item_id] == x_pos && v_pos_item [item_id] == y_pos)
      	{
	      	itemy_na_glebie [itemy_na_glebie_amount] = item_id;
   	      itemy_na_glebie_amount ++;
      	}
	   }

		last_item_id = itemy_na_glebie [itemy_na_glebie_amount - 1];

		clrscr ();
		i_y = 0;
	   alfabet = 97;

		wybierz_item = 1;
   	item_id = temp = exit_list = 0;

		make_window (0, 2, 0, 0, 78, 23, -2,
		   "^n                       Select an item to pick up                    Weight"
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
               item_id_gleba = 0;
            else
               key = 0;

	   	   for (; item_id_gleba < itemy_na_glebie_amount; item_id_gleba ++)
   	   	{
            	item_id = itemy_na_glebie [item_id_gleba];

	   	    	if (item_group [item_id] == grupa_items)
   	   	   {
	            	if (!i_y)
   	               item_id_storage [item_id_index] = item_id_gleba;

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
                           item_id_gleba = item_id_storage [item_id_index - 1];
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
									item_id_gleba = -1;
           	               temp = 1;
        				         grupa_items = item_id_index = 0;
									alfabet = 97;
                           sub_messages (0, -1, -1);
  	            		      break;
   	               	}
  	   	            	else if (key >= 'a' && key < alfabet)
  		   	            {
        	      		      exit_list = 1;
           	      		   rysuj_ekran ();
                        	action_item (-1, x_pos, y_pos, 2, inv [key - 96]);
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
      		   if (exit_list || key == '+')
	         	  	break;
				}
   		   if (exit_list)		// po nacisnieciu ESC
      		  	break;
			}

	      if (item_id_index && !exit_list)
   	   	sub_messages (-1, 0, 0);

			while (!exit_list)
			{
				klawisz ();

				if (key == '-' && item_id_index)		// poprzednio nacisnieto '+' lub Enter
   	   	{
   		   	i_y = 1;
     	   		temp = 1;
      			clear_window (3, 5, 77, 21);
	  	         item_id_gleba = -1;

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
					item_id_gleba = item_id_storage [item_id_index - 1];
					item_id_index --;

					if (grupa_items_index)
      	      {
						grupa_items = 100 + grupa_items_storage [grupa_items_index - 1] - 1;
						grupa_items_index --;
	            }

					if (!item_id_index)
      	        	sub_messages (0, -1, -1);

	            break;
	     	   }
				else if (key >= 'a' && key < alfabet)
				{
         	   exit_list = 1;
            	rysuj_ekran ();
	            action_item (-1, x_pos, y_pos, 2, inv [key - 96]);
				}
				else if (key == 27)		// Esc
            {
            	rysuj_ekran ();
					exit_list = 1;
            }
			}
		}
      wybierz_item = 0;
   }
   else
   {
   	msg ("There is nothing to pick up.");
      msg_reset ();
   }
}

void action_drop ()
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

	last_item_id = itemy_w_plecaq [itemy_w_plecaq_amount - 1];
	clrscr ();
   alfabet = 97;
   item_id = exit_list = 0;

	make_window (0, 2, 0, 0, 78, 23, -2,
	   "^n                       Select an item to drop                     Weight"
   	"^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n Esc - exit"
  		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu

	wybierz_item = 1;

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
     	      		      exit_list = 1;
	                     action_item (-1, h_pos, v_pos, 1, inv [key - 96]);
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
      	   if (exit_list || key == '+')
	           	break;
			}
      	if (exit_list)		// po nacisnieciu ESC
	        	break;
		}

      if (item_id_index && !exit_list)
  	   	sub_messages (-1, 0, 0);

		while (!exit_list)
		{
			klawisz ();

			if (key == '-' && item_id_index)		// poprzednio nacisnieto '+' lub Enter
  	   	{
  		   	i_y = 1;
  	   		temp = 1;
     			clear_window (3, 5, 77, 21);
  	         item_id_plecaq = -1;

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

            break;
     	   }
			else if (key >= 'a' && key < alfabet)
			{
        	   exit_list = 1;
            action_item (-1, h_pos, v_pos, 1, inv [key - 96]);
			}
			else if (key == 27)		// Esc
         {
           	rysuj_ekran ();
				exit_list = 1;
         }
		}
	}
   wybierz_item = 0;
}

void action_item (int kod_mon, int x_pos, int y_pos, char action_type, int kod)	// czyli item management
{
   int temp_, temp_2, i, j, k;
	char tablica [5];
   int amount = 1;
	char nr_klawisza = 0;

	item_id = stan_planszy [x_pos] [y_pos];
   tablica [0] = tablica [1] = tablica [2] = tablica [3] = tablica [4] = 0;

	if (kod_mon == -1 && action_type == 1)		// player
   {
		exit_list = 1;
     	rysuj_ekran ();
   }

	if (kod_mon == -1 && item_amount [kod] > 1)
   {
		msg ("<How many items of ");
   	enter_item (kod, 7);
	   msg (" do you want to ");

	   if (action_type == 1)
		   messages ("drop (0 - ^) ? ", item_amount [kod], 7);
	   else
   		messages ("pick up (0 - ^) ? ", item_amount [kod], 7);

	   gotoxy (2 + litera, 23 + kolumna);
   	putch (95);

		while (1)
		{
			klawisz ();

			if (key == 8 && nr_klawisza > 0)	// co gdy wcisniemy backspace
			{
				putch (key);
	         putch (key);
				putch (32);
				putch (32);
	         putch (key);
   	      putch (key);
				putch (95);
				nr_klawisza --;
				tablica [nr_klawisza] = 0;
			}

			if (key >= 48 && key <= 57)
			{
      		putch (8);
				putch (key);
   	      putch (95);
				tablica [nr_klawisza] = key - 48;
				nr_klawisza ++;
			}

			if (nr_klawisza > 4 || key == 13)
				break;
		}

   	if (nr_klawisza == 1)
	   	amount = tablica [0];
   	else if (nr_klawisza == 2)
	   	amount = tablica [0] * 10 + tablica [1];
   	else if (nr_klawisza == 3)
	   	amount = tablica [0] * 100 + tablica [1] * 10 + tablica [2];
   	else if (nr_klawisza == 4)
	   	amount = tablica [0] * 1000 + tablica [1] * 100 + tablica [2] * 10 + tablica [3];
   	else if (nr_klawisza == 5)
	   	amount = tablica [0] * 10000 + tablica [1] * 1000 + tablica [2] * 100 + tablica [3] * 10 + tablica [4];

		if (!nr_klawisza || amount > item_amount [kod])
   		amount = item_amount [kod];
   }

   if (kod_mon != -1 && item_amount [kod] > 1)
   	amount = item_amount [kod];

	if (!amount)
   {
   	msg ("<You did not ");

      if (action_type == 1)
      	msg ("drop ");
      else
      	msg ("pick up ");

      msg ("anything.");
   }
   else
   {
	   if (action_type == 1)					// action drop?
  		{
	   	if ((temp_ = search_identical_item_on_map (kod, x_pos, y_pos)) == -1)		// nie ma pod graczem / potworem / w tym miejscu?
   	   	action_type = 1;
      	else							// jest pod graczem / potworem / w tym miejscu
	      	action_type = 2;
	   }
   	else			// action pick up
	   {
   		if ((temp_ = search_identical_item (kod_mon, kod)) == -1)		// nie ma w plecaku?
      		action_type = 3;
	      else							// jest w plecaku
   	   	action_type = 4;
	   }

	   if (amount == item_amount [kod])		// caly przedmiot?
   		action_type += 4;

	 	if (action_type < 3)
   	{
			if (kod_mon == -1)
   	   {
		   	messages ("<You drop ^ of ", amount, 7);
		     	enter_item (kod, 7);
				kropka (7);
				weight -= item_weight [kod] * amount;
   	   }
	   }
	   else if (action_type < 5)
   	{
	    	if (kod_mon == -1)
   	   {
	   		messages ("<You pick up ^ of ", amount, 7);
		     	enter_item (kod, 7);
  			   kropka (7);
				weight += item_weight [kod] * amount;
	      }
	   }
		else if (action_type < 7)
	   {
			if (kod_mon == -1)
      	{
				msg ("<You drop ");
				enter_item (kod, 7);
      	   kropka (7);
				weight -= item_weight [kod] * amount;
   	   }
	   }
   	else
	   {
			if (kod_mon == -1)
      	{
				msg ("<You pick up ");
				enter_item (kod, 7);
      	   kropka (7);
				weight += item_weight [kod] * amount;
   	   }
	   }

	   switch (action_type)
   	{
	   	case 1:		// tworzy nowy item pod graczem / potworem
				divide_items (kod, amount);
			   item [temp] = 3;
  				h_pos_item [temp] = x_pos;
	   		v_pos_item [temp] = y_pos;
   	      put_item (temp);
				item_owner [temp] = -5;
	      	break;
   		case 2:		// zwieksza ilosc przedmiotu na ziemi i zmniejsza w plecaku gracza / potwora
     			item_amount [temp_] += amount;
	     		item_amount [kod] -= amount;
   	   	break;
   		case 3:		// tworzy nowy item w plecaku gracza / potwora
				divide_items (kod, amount);

      	   if (kod_mon == -1)
	         {
					item [temp] = 1;		// !!! temp - globalna - nie zmieniac na kod
      	      item_owner [temp] = -1;
	      	}
   	      else
      	   {
	         	item [temp] = 6;
   	         item_owner [temp] = kod_mon;
      	   }
	      	break;
   		case 4:		// zwieksza ilosc przedmiotu w plecaku gracza / potwora i zmniejsza na ziemi
     			item_amount [temp_] += amount;
	     		item_amount [kod] -= amount;
   	   	break;
   		case 5:		// przenosi przedmiot z plecaka na ziemie
		      item [kod] = 3;
  				h_pos_item [kod] = x_pos;
   			v_pos_item [kod] = y_pos;
	         put_item (kod);
				item_owner [kod] = -5;
      		break;
	   	case 6:		// usuwa przedmiot z plecaka i zwieksza ilosc na ziemi
   	  		item_amount [temp_] += amount;

	         if (kod_mon != -3)
   	      {
					remove_item (kod, x_pos, y_pos);
	   	      delete_item (kod);
   	      }
      	   else
         		items_amount --;
	      	break;
   		case 7:		// przenosi przedmiot z ziemi do plecaka
      		remove_item (kod, x_pos, y_pos);

	         if (kod_mon == -1)
   	      {
					item [kod] = 1;
         	   item_owner [kod] = -1;
	         }
   	      else
      	   {
         		item [kod] = 6;		// monster's backpack
	            item_owner [kod] = kod_mon;
   	      }
      		break;
	   	case 8:		// usuwa przedmiot z ziemi i zwieksza ilosc w plecaku
   	  		item_amount [temp_] += amount;
      	   remove_item (kod, x_pos, y_pos);
         	delete_item (kod);
	      	break;
   	}
   }
}

void delete_item (int kod)
{
	int a, k;
   int last_item_id = items_amount - 1;

	if (kod != last_item_id && item [last_item_id] == 3 && items_planszy [h_pos_item [last_item_id]] [v_pos_item [last_item_id]] >= 0)	// w miejscu usuwanego przedmiotu jest tylko 1 podmieniany przedmiot
		items_planszy [h_pos_item [last_item_id]] [v_pos_item [last_item_id]] = kod;

	h_pos_item [kod] = h_pos_item [items_amount - 1];
	v_pos_item [kod] = v_pos_item [items_amount - 1];
	item [kod] = item [items_amount - 1];
	item_icon [kod] = item_icon [items_amount - 1];
	item_group [kod] = item_group [items_amount - 1];
	item_type [kod] = item_type [items_amount - 1];
	item_dv [kod] = item_dv [items_amount - 1];
	item_hit [kod] = item_hit [items_amount - 1];
	item_dices [kod] = item_dices [items_amount - 1];
	item_dmg_bonus [kod] = item_dmg_bonus [items_amount - 1];
	item_status [kod] = item_status [items_amount - 1];
	item_ident [kod] = item_ident [items_amount - 1];
	item_specials1 [kod] = item_specials1 [items_amount - 1];
	item_specials2 [kod] = item_specials2 [items_amount - 1];
	item_weight [kod] = item_weight [items_amount - 1];
	item_value_material [kod] = item_value_material [items_amount - 1];
   item_state [kod] = item_state [items_amount - 1];
  	item_owner [kod] = item_owner [items_amount - 1];
   item_amount [kod] = item_amount [items_amount - 1];

	for (a = 1; a < 20; a ++)
  		if (item_body [a] == last_item_id)
     		item_body [a] = kod;
      else if (item_body [a] == kod)
     		item_body [a] = -1;

	for (a = 0; a < working_items_amount; a ++)
   	if (working_items [a] == kod)
      {
	   	working_items [a] = working_items [working_items_amount - 1];
   		working_items_amount --;
      }

   items_amount --;
}

void divide_items (int kod, int amount)
{
	item_amount [kod] -= amount;
   temp = items_amount;
   item_amount [temp] = amount;
  	item_icon [temp] = item_icon [kod];
 	item_group [temp] = item_group [kod];
   item_type [temp] = item_type [kod];
   item_dv [temp] = item_dv [kod];
   item_hit [temp] = item_hit [kod];
   item_dmg_bonus [temp] = item_dmg_bonus [kod];
   item_dices [temp] = item_dices [kod];
   item_state [temp] = item_state [kod];
   item_status [temp] = item_status [kod];
   item_ident [temp] = item_ident [kod];
   item_specials1 [temp] = item_specials1 [kod];
   item_specials2 [temp] = item_specials2 [kod];
   item_value_material [temp] = item_value_material [kod];
   item_owner [temp] = item_owner [kod];
   item_weight [temp] = item_weight [kod];
   items_amount ++;
}

void ujmij_item (int kod_p, int amount)
{
	item_amount [kod_p] -= amount;

   if (item [kod_p] == 4 || item [kod_p] == 1)		// w plecaku lub w lapie
   	weight -= item_weight [kod_p] * amount;

	if (item_amount [kod_p] < 1)
   {
		if (item_body [_MWAMMO] == kod_p)
			item_body [_MWAMMO] = -1;

		remove_item (kod_p, h_pos_item [kod_p], v_pos_item [kod_p]);
      delete_item (kod_p);
   }
}

void put_item (int kod)
{
	int q;
   int x_pos = h_pos_item [kod];
   int y_pos = v_pos_item [kod];

  	if (item [kod] == 3)			// stuff
   {
     	if (!stan_planszy [x_pos] [y_pos])
        	stan_planszy [x_pos] [y_pos] = 1;
		else if (stan_planszy [x_pos] [y_pos] == 1)
        	stan_planszy [x_pos] [y_pos] = 8;
		else if (stan_planszy [x_pos] [y_pos] == 2)
        	stan_planszy [x_pos] [y_pos] = 4;
		else if (stan_planszy [x_pos] [y_pos] == 3)
        	stan_planszy [x_pos] [y_pos] = 5;
		else if (stan_planszy [x_pos] [y_pos] == 4)
        	stan_planszy [x_pos] [y_pos] = 9;
      else if (stan_planszy [x_pos] [y_pos] == 5)
        	stan_planszy [x_pos] [y_pos] = 10;
      else if (stan_planszy [x_pos] [y_pos] == 6)
        	stan_planszy [x_pos] [y_pos] = 7;
      else if (stan_planszy [x_pos] [y_pos] == 7)
        	stan_planszy [x_pos] [y_pos] = 11;

      if (items_planszy [x_pos] [y_pos] == -1)
			items_planszy [x_pos] [y_pos] = kod;
      else if (items_planszy [x_pos] [y_pos] >= 0)
			items_planszy [x_pos] [y_pos] = -2;		// several (two) items
      else
			items_planszy [x_pos] [y_pos] --;		// several (more) items
	}
   else if (item [kod] == 5)		// obstacle
   {
     	if (!stan_planszy [x_pos] [y_pos])
        	stan_planszy [x_pos] [y_pos] = 2;
      else if (stan_planszy [x_pos] [y_pos] == 1)
        	stan_planszy [x_pos] [y_pos] = 4;
      else if (stan_planszy [x_pos] [y_pos] == 3)
        	stan_planszy [x_pos] [y_pos] = 6;
      else if (stan_planszy [x_pos] [y_pos] == 5)
        	stan_planszy [x_pos] [y_pos] = 7;
      else if (stan_planszy [x_pos] [y_pos] == 8)
		  	stan_planszy [x_pos] [y_pos] = 9;
      else if (stan_planszy [x_pos] [y_pos] == 10)
        	stan_planszy [x_pos] [y_pos] = 11;

      if (obstacles_planszy [x_pos] [y_pos] == -1)
			obstacles_planszy [x_pos] [y_pos] = kod;
	}
   else if (item [kod] == 7)		// coverer(s)
   {
     	if (!stan_planszy [x_pos] [y_pos])
        	stan_planszy [x_pos] [y_pos] = 3;
      else if (stan_planszy [x_pos] [y_pos] == 1)
        	stan_planszy [x_pos] [y_pos] = 5;
      else if (stan_planszy [x_pos] [y_pos] == 2)
        	stan_planszy [x_pos] [y_pos] = 6;
      else if (stan_planszy [x_pos] [y_pos] == 4)
        	stan_planszy [x_pos] [y_pos] = 7;
      else if (stan_planszy [x_pos] [y_pos] == 8)
        	stan_planszy [x_pos] [y_pos] = 10;
      else if (stan_planszy [x_pos] [y_pos] == 9)
        	stan_planszy [x_pos] [y_pos] = 11;

		q = coverers_planszy [x_pos] [y_pos] [0];
      coverers_planszy [x_pos] [y_pos] [q + 1] = kod;
		coverers_planszy [x_pos] [y_pos] [0] ++;
	}

   convert_plansza (x_pos, y_pos);
}

void remove_item (int kod, int x_pos, int y_pos)
{
	int q;
   int kod_p = item [kod];

  	if (kod_p == 3)			// stuff (na planszy)
   {
		if (stan_planszy [x_pos] [y_pos] == 1)
      {
        	stan_planszy [x_pos] [y_pos] = 0;
         items_planszy [x_pos] [y_pos] = -1;		// no items
      }
		else if (stan_planszy [x_pos] [y_pos] == 4)
        	stan_planszy [x_pos] [y_pos] = 2;
      else if (stan_planszy [x_pos] [y_pos] == 5)
        	stan_planszy [x_pos] [y_pos] = 3;
      else if (stan_planszy [x_pos] [y_pos] == 7)
        	stan_planszy [x_pos] [y_pos] = 6;

     	if (items_planszy [x_pos] [y_pos] == -2)
      {
	      if (stan_planszy [x_pos] [y_pos] == 8)
	      	stan_planszy [x_pos] [y_pos] = 1;
	      else if (stan_planszy [x_pos] [y_pos] == 9)
	      	stan_planszy [x_pos] [y_pos] = 4;
	      else if (stan_planszy [x_pos] [y_pos] == 10)
	      	stan_planszy [x_pos] [y_pos] = 5;
	      else if (stan_planszy [x_pos] [y_pos] == 11)
	      	stan_planszy [x_pos] [y_pos] = 7;

			for (q = 0; q < items_amount; q ++)
         {
         	if (item [q] == 3 && h_pos_item [q] == x_pos && v_pos_item [q] == y_pos && q != kod)
            {
		         items_planszy [x_pos] [y_pos] = q;
               break;
            }
         }
      }
      else if (items_planszy [x_pos] [y_pos] < -2)
			items_planszy [x_pos] [y_pos] ++;
      else
      	items_planszy [x_pos] [y_pos]	= -1;

	   convert_plansza (x_pos, y_pos);
   	aktualizuj_pole (x_pos, y_pos);
	}
   else if (kod_p == 5)		// obstacle
   {
      if (stan_planszy [x_pos] [y_pos] == 2)
        	stan_planszy [x_pos] [y_pos] = 0;
      else if (stan_planszy [x_pos] [y_pos] == 4)
        	stan_planszy [x_pos] [y_pos] = 1;
      else if (stan_planszy [x_pos] [y_pos] == 6)
		  	stan_planszy [x_pos] [y_pos] = 3;
      else if (stan_planszy [x_pos] [y_pos] == 7)
        	stan_planszy [x_pos] [y_pos] = 5;
      else if (stan_planszy [x_pos] [y_pos] == 9)
        	stan_planszy [x_pos] [y_pos] = 8;
      else if (stan_planszy [x_pos] [y_pos] == 11)
        	stan_planszy [x_pos] [y_pos] = 10;

		obstacles_planszy [x_pos] [y_pos] = -1;
	   convert_plansza (x_pos, y_pos);
   	aktualizuj_pole (x_pos, y_pos);
	}
   else if (kod_p == 7)		// coverer(s)
   {
   	coverers_planszy [x_pos] [y_pos] [0] --;

		if (!coverers_planszy [x_pos] [y_pos] [0])
      {
	      if (stan_planszy [x_pos] [y_pos] == 3)
   	     	stan_planszy [x_pos] [y_pos] = 0;
      	else if (stan_planszy [x_pos] [y_pos] == 5)
	        	stan_planszy [x_pos] [y_pos] = 1;
   	   else if (stan_planszy [x_pos] [y_pos] == 6)
      	  	stan_planszy [x_pos] [y_pos] = 2;
	      else if (stan_planszy [x_pos] [y_pos] == 7)
   	     	stan_planszy [x_pos] [y_pos] = 4;
      	else if (stan_planszy [x_pos] [y_pos] == 10)
        		stan_planszy [x_pos] [y_pos] = 8;
      	else if (stan_planszy [x_pos] [y_pos] == 11)
        		stan_planszy [x_pos] [y_pos] = 9;
      }

	   convert_plansza (x_pos, y_pos);
   	aktualizuj_pole (x_pos, y_pos);
   }
}

int search_item (int grupa_items, int typ_items)
{
	int i = 0;
	int a;

	if (!typ_items)
   {
		for (a = 0; a < items_amount; a ++)
      {
   		if (item_group [a] == grupa_items && (item [a] == 1 || item [a] == 4))
      		i ++;
         if (i > 1)		// wiecej niz 1 item danej grupy
         	return -1;
      }
   }
   else
   {
		for (a = 0; a < items_amount; a ++)
   		if (item_group [a] == grupa_items && item_type [a] == typ_items && (item [a] == 1 || item [a] == 4))
      		return a;
   }

   if (i == 1)
		for (a = 0; a < items_amount; a ++)
   		if (item_group [a] == grupa_items && (item [a] == 1 || item [a] == 4))
      		return a;

   return -2;
}

int search_key (int kod_zamka)
{
	int a, kod_klucza = -1;

	for (a = 0; a < items_amount; a ++)
  		if (item_group [a] == 24 && item_specials2 [a] == kod_zamka && item_owner [a] == -1)
      {
      	kod_klucza = a;
     		break;
      }

   return kod_klucza;
}

int search_identical_item (int kod_mon, int kod)
{
	int i;

	if (kod_mon == -1)
   {
		if (item_group [kod] != 17)
   	{
			for (i = 0; i < items_amount; i ++)
		   	if (item [i] == 1 && item_group [i] == item_group [kod] &&
   		   item_type [i] == item_type [kod] && item_dv [i] == item_dv [kod] &&
      		item_hit [i] == item_hit [kod] && item_dmg_bonus [i] == item_dmg_bonus [kod] &&
		      item_dices [i] == item_dices [kod] && item_state [i] == item_state [kod] &&
   		   item_status [i] == item_status [kod] && item_ident [i] == item_ident [kod] &&
      		item_specials1 [i] == item_specials1 [kod] && item_specials2 [i] == item_specials2 [kod] &&
	      	item_value_material [i] == item_value_material [kod])
   		   	return i;
	   }
	   else
   	{
			for (i = 0; i < items_amount; i ++)
	      	if (item [i] == 1 && item_group [i] == 17 && item_type [i] == item_type [kod])
   	      	return i;
	   }
   }
   else if (kod_mon >= 0)
   {
		if (item_group [kod] != 17)
   	{
			for (i = 0; i < items_amount; i ++)
		   	if (item [i] == 6 && item_group [i] == item_group [kod] &&
   		   item_type [i] == item_type [kod] && item_dv [i] == item_dv [kod] &&
      		item_hit [i] == item_hit [kod] && item_dmg_bonus [i] == item_dmg_bonus [kod] &&
		      item_dices [i] == item_dices [kod] && item_state [i] == item_state [kod] &&
   		   item_status [i] == item_status [kod] && item_ident [i] == item_ident [kod] &&
      		item_specials1 [i] == item_specials1 [kod] && item_specials2 [i] == item_specials2 [kod] &&
	      	item_value_material [i] == item_value_material [kod])
   		   	return i;
	   }
	   else
   	{
			for (i = 0; i < items_amount; i ++)
	      	if (item [i] == 6 && item_group [i] == 17 && item_type [i] == item_type [kod])
   	      	return i;
	   }
   }

   return -1;
}

int search_identical_item_on_map (int kod, int x_pos, int y_pos)
{
	int i;

	if (item_group [kod] != 17)
   {
		for (i = 0; i < items_amount; i ++)
   		if (item [i] == 3 && h_pos_item [i] == x_pos &&
      	v_pos_item [i] == y_pos && item_group [i] == item_group [kod] &&
	      item_type [i] == item_type [kod] && item_dv [i] == item_dv [kod] &&
   	   item_hit [i] == item_hit [kod] && item_dmg_bonus [i] == item_dmg_bonus [kod] &&
      	item_dices [i] == item_dices [kod] && item_state [i] == item_state [kod] &&
	      item_status [i] == item_status [kod] && item_ident [i] == item_ident [kod] &&
   	   item_specials1 [i] == item_specials1 [kod] && item_specials2 [i] == item_specials2 [kod] &&
      	item_value_material [i] == item_value_material [kod])
      		return i;
   }
   else
   {
		for (i = 0; i < items_amount; i ++)
      	if (item [i] == 3 && item_group [i] == 17 && h_pos_item [i] == x_pos &&
      	v_pos_item [i] == y_pos && item_type [i] == item_type [kod])
         	return i;
   }

   return -1;
}

