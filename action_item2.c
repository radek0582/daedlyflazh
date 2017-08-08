#include "deklaracje.h"

void action_pickup (int selected, int x_pos, int y_pos)
{
	int i, a, kod_p, kod_mon;
	int itemy_na_glebie_amount = 0;
	int item_id_gleba, last_item_id = -1;
   int itemy_na_glebie [10000];
   int item_id_storage [1000];
   int grupa_items_storage [1000];
   int item_id_index = 0;
   int grupa_items_index = grupa_items;

	kod_mon = monsters_planszy [x_pos] [y_pos];
	kod_p = stan_planszy [x_pos] [y_pos];	// znajdz przedmiot na mapie

   if (kod_p == 1 || kod_p == 4 || kod_p == 5 || kod_p == 7)				// just one item
   	action_item (-1, x_pos, y_pos, 2, items_planszy [x_pos] [y_pos]);
   else if (kod_p > 7)		// several items
   	inventory_selector (selected, x_pos, y_pos);
   else
   {
   	msg ("There is nothing to pick up.");
      msg_reset ();
   }
}

void action_drop ()
{
	grupa_items = 100;
	inventory_selector (2, 0, 0);
}

void action_item (int kod_mon, int x_pos, int y_pos, char action_type, int kod)	// czyli item management
{
   int temp_, temp_2, i, j, k;
	char tablica [5];
   int amount = 1;
	char nr_klawisza = 0;
   char selling = 0;

//	item_id = stan_planszy [x_pos] [y_pos];
   tablica [0] = tablica [1] = tablica [2] = tablica [3] = tablica [4] = 0;

	if (kod_mon == -1 && action_type == 1)		// player
   {
		exit_list = 1;
     	rysuj_ekran ();
   }

	if (action_type == 1 && kod_mon == -1 && item_amount [kod] > 1 && item_value_material [kod] % 100 < 50)
   {
		msg ("<How many of ");
   	enter_item (kod, COLOR_GRAY);
	   msg (" do you want to ");

//	   if (action_type == 1)
		   messages ("drop (0 - ^) ? ", item_amount [kod], COLOR_GRAY);

//	   else
//   		messages ("pick up (0 - ^) ? ", item_amount [kod], COLOR_GRAY);

	   gotoxy (2 + litera, 23 + kolumna);
   	addch (95);

		while (1)
		{
			klawisz ();

			if (key == 8 && nr_klawisza > 0)	// co gdy wcisniemy backspace
			{
				addch (key);
	         addch (key);
				addch (32);
				addch (32);
	         addch (key);
   	      addch (key);
				addch (95);
				nr_klawisza --;
				tablica [nr_klawisza] = 0;
			}

			if (key >= 48 && key <= 57)
			{
      		addch (8);
				addch (key);
   	      addch (95);
				tablica [nr_klawisza] = key - 48;
				nr_klawisza ++;
			}

			if (nr_klawisza > 4 || key == _ENTER || key == _ENTER2)
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

   if (kod_mon != -1 || action_type == 2 || action_type == 1 && item_amount [kod] > 1 && item_value_material [kod] % 100 >= 50)
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
         	if (item_group [kod] != 17 && floor_planszy [x_pos] [y_pos] % 1000 >= 100 && !unpaid_items [kod] && search_shopkeeper (floor_planszy [x_pos] [y_pos]) >= 0)// && monster_char [unpaid_items [kod]] == floor_planszy [x_pos] [y_pos])		// sell
            {
            	messages ("<-I will offer you ^ for this. Do you accept my offer ? (y/n)", amount * item_value_material [kod] / 200 + 1, COLOR_GRAY);

				   if (answer ())
					{
						msg ("<Thank you for this transaction! ");
                  selling = 1;
                  take_new_item (_GCDC, amount * item_value_material [kod] / 200 + 1, 1);

		         	if (monster_code [search_shopkeeper (floor_planszy [x_pos] [y_pos])] == _Bavar && !achievement [10])
      		      	gain_achievement (10);
               }
               else
               	msg ("<Then don't waste my time! ");
            }
            else
            {
			   	messages ("<You drop ^ of ", amount, COLOR_GRAY);
               messages ("^ ", item_amount [kod], COLOR_GRAY);
			     	enter_one_item (kod);
					kropka (COLOR_GRAY);
					weight -= item_weight [kod] * amount;

	            if (item_value_material [kod] % 100 >= 50 && floor_planszy [h_pos] [v_pos] >= 100)		// unpaid i w sklepie
   	         	unpaid_items [kod] = 0;
            }
   	   }
	   }
	   else if (action_type < 5)
   	{
	    	if (kod_mon == -1)
   	   {
	   		messages ("<You pick up ^ of ", amount, COLOR_GRAY);
		     	enter_item (kod, COLOR_GRAY);
  			   kropka (COLOR_GRAY);
				weight += item_weight [kod] * amount;

            if (item_value_material [kod] % 100 >= 50 && floor_planszy [h_pos] [v_pos] >= 100)		// unpaid i w sklepie
            	unpaid_items [kod] = monster_code [search_shopkeeper (floor_planszy [h_pos] [v_pos])];
	      }
	   }
		else if (action_type < 7)
	   {
			if (kod_mon == -1)
      	{
         	if (item_group [kod] != 17 && floor_planszy [x_pos] [y_pos] % 1000 >= 100 && !unpaid_items [kod] && search_shopkeeper (floor_planszy [x_pos] [y_pos]) >= 0)// && monster_char [unpaid_items [kod]] == floor_planszy [x_pos] [y_pos])		// sell
            {
            	messages ("<-I will offer you ^ for this. Do you accept my offer?", amount * item_value_material [kod] / 200 + 1, COLOR_GRAY);

				   if (answer ())
					{
						msg ("<Thank you for this transaction! ");
                  selling = 1;
                  take_new_item (_GCDC, amount * item_value_material [kod] / 200 + 1, 1);

		         	if (monster_code [search_shopkeeper (floor_planszy [x_pos] [y_pos])] == _Bavar && !achievement [10])
      		      	gain_achievement (10);
               }
               else
               	msg ("<Then don't waste my time! ");
            }
            else
            {
					msg ("<You drop ");
					enter_item (kod, COLOR_GRAY);
      		   kropka (COLOR_GRAY);
					weight -= item_weight [kod] * amount;

	            if (item_value_material [kod] % 100 >= 50 && floor_planszy [h_pos] [v_pos] >= 100)		// unpaid i w sklepie
   	         	unpaid_items [kod] = 0;
            }
   	   }
	   }
   	else
	   {
			if (kod_mon == -1)
      	{
				msg ("<You pick up ");
				enter_item (kod, COLOR_GRAY);
      	   kropka (COLOR_GRAY);
				weight += item_weight [kod] * amount;

            if (item_value_material [kod] % 100 >= 50 && floor_planszy [h_pos] [v_pos] >= 100)		// unpaid i w sklepie
            	unpaid_items [kod] = monster_code [search_shopkeeper (floor_planszy [h_pos] [v_pos])];
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

            if (selling)
            	item_value_material [temp] += 50;
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

            if (selling)
            	item_value_material [kod] += 50;
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

void take_new_item (int kod, int amount, int msg_)
{
	int temp_;

	ekwipunek (kod, -1, 3);
	item_amount [item_id] = amount;

   if (msg_ == 1)
   {
	   msg ("You take ");
	  	enter_item (item_id, COLOR_GRAY);
   	kropka (COLOR_GRAY);
   }

	if ((temp_ = search_identical_item (-1, item_id)) == -1)		// nie ma w plecaku?
   	item [item_id] = 1;
   else							// jest w plecaku
   {
     	delete_item (item_id);
 		item_amount [temp_] += amount;
   }
}

void delete_item (int kod)
{
	int a, k;
   int last_item_id = items_amount - 1;

	if (kod != last_item_id && item [last_item_id] == 3 && items_planszy [h_pos_item [last_item_id]] [v_pos_item [last_item_id]] >= 0)	// w miejscu usuwanego przedmiotu jest tylko 1 podmieniany przedmiot
		items_planszy [h_pos_item [last_item_id]] [v_pos_item [last_item_id]] = kod;

	if (kod != last_item_id && item [last_item_id] == 5 && obstacles_planszy [h_pos_item [last_item_id]] [v_pos_item [items_amount - 1]] >= 0)
	   obstacles_planszy [h_pos_item [last_item_id]] [v_pos_item [last_item_id]] = kod;

   for (a = 0; a < 15; a ++)
		if (kod != last_item_id && item [last_item_id] == 7 && coverers_planszy [h_pos_item [last_item_id]] [v_pos_item [items_amount - 1]] [a] >= 0)
		   coverers_planszy [h_pos_item [last_item_id]] [v_pos_item [last_item_id]] [a] = kod;

   working_items [kod] = working_items [last_item_id];
   unpaid_items [kod] = unpaid_items [last_item_id];



   //	working_items [last_item_id] = 0;

	h_pos_item [kod] = h_pos_item [last_item_id];
	v_pos_item [kod] = v_pos_item [last_item_id];
	item [kod] = item [last_item_id];
	item_icon [kod] = item_icon [last_item_id];
	item_group [kod] = item_group [last_item_id];
	item_type [kod] = item_type [last_item_id];
	item_dv [kod] = item_dv [last_item_id];
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

   items_amount --;
}

void divide_items (int kod, int amount)
{
	item_amount [kod] -= amount;
   temp = items_amount;

  	working_items [temp] = working_items [kod];
  	unpaid_items [temp] = unpaid_items [kod];

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
//		if (item_body [_MWAMMO] == kod_p)
//			item_body [_MWAMMO] = -1;

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
		if (stan_planszy [x_pos] [y_pos] == 1)		// one item
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

     	if (items_planszy [x_pos] [y_pos] == -2)	// several items
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

