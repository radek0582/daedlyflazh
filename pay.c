#include "deklaracje.h"

int select_item_to_pay ()
{
   reset_inv_globals ();
   inventory_selector (6, 0, 0);

   return 0;
}

void pay (int chosen_item_id)
{
 	int kasa_id = search_item (17, 3);

   rysuj_ekran ();

	if (chosen_item_id != -1)
   {
		if (chosen_item_id >= 0)
		{
      	if (kasa_id < 0 || item_amount [kasa_id] < item_value_material [chosen_item_id] / 100 * item_amount [chosen_item_id])
         {
         	msg ("-You do not have enough money! ");
         }
         else
         {
			   msg ("-Thanks a lot. ");

         	if (unpaid_items [chosen_item_id] == _Bavar && !achievement [10])
            	gain_achievement (10);

            unpaid_items [chosen_item_id] = 0;
            item_value_material [chosen_item_id] -= 50;
				ujmij_item (kasa_id , item_value_material [chosen_item_id] / 100 * item_amount [chosen_item_id]);
         }

	      turn ();
	   }
   }
}
