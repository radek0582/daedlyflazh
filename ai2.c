#include "deklaracje.h"

void AI ()
{
	int j, a, x, y, cel, kod_p, distance, x_pos, y_pos, highest_enemy, enemy_amnt, enemy_factor, unpaid_items_amnt [2000], enemy_matrix [MAXMONSTERS] [2];

   for (a = 0; a < 2000; a ++)
   	unpaid_items_amnt [a] = 0;

	for (current_monster_id = 0; current_monster_id < monsters_amount; current_monster_id ++)
	{
   	kod_p = monster_code [current_monster_id];
	  	moves [current_monster_id] = (monster_speed [current_monster_id] * 32 + bonus [current_monster_id]) / total_speed / 32;
		bonus [current_monster_id] += (monster_speed [current_monster_id] * 32) % (total_speed * 32);

      if (kod_p >= 1100 && kod_p < 1200)
	      for (a = 0; a < items_amount; a ++)
   	   	if (unpaid_items [a] == kod_p)
            	unpaid_items_amnt [kod_p] ++;

	   for (j = 0; j < moves [current_monster_id]; j ++)
   	{
      	// szukanie celu
         if (monster_aim [current_monster_id] == -7 || monster_aim [current_monster_id] == - 5 || monster_aim [current_monster_id] >= -1 && !check_visibility (current_monster_id, monster_aim [current_monster_id]))
         {
         	highest_enemy = monster_aim [current_monster_id];
            enemy_amnt = 0;

         	for (x = -10 + h_pos_mon [current_monster_id]; x < h_pos_mon [current_monster_id] + 10; x ++)
            {
	         	for (y = -10 + v_pos_mon [current_monster_id]; y < v_pos_mon [current_monster_id] + 10; y ++)
               {
               	if (x >= 0 && y >= 0 && x < x_planszy && y < y_planszy)
                  {
	                  if (monsters_planszy [x] [y] >= 0 && check_visibility (current_monster_id, monsters_planszy [x] [y]))
  		               {
                     	enemy_factor = abs (monster_alignment [current_monster_id] - monster_alignment [monsters_planszy [x] [y]]);

     		            	if (monster_alignment [current_monster_id] < 0 && (enemy_factor > 5 || monster_alignment [monsters_planszy [x] [y]] > 0) || monster_alignment [current_monster_id] > 0 && monster_alignment [monsters_planszy [x] [y]] < 0)
                        {
                           enemy_matrix [enemy_amnt] [0] = monsters_planszy [x] [y];
                           enemy_matrix [enemy_amnt] [1] = enemy_factor;
                           enemy_amnt ++;
                        }
           		      }
              		   else if (monsters_planszy [x] [y] == -1 && check_visibility (current_monster_id, -1))
     	         	   {
                     	enemy_factor = abs (monster_alignment [current_monster_id]);

	               	  	if (badass_reputation [cl_id] <= -5 && monster_alignment [current_monster_id] <= -5 || goody_reputation [cl_id] <= -5 && monster_alignment [current_monster_id] >= 5)
                        {
                           enemy_matrix [enemy_amnt] [0] = -1;
                           enemy_matrix [enemy_amnt] [1] = enemy_factor;
                           enemy_amnt ++;
                        }
	      	         }
            	   }
  					}
            }

            for (x = 0; x < enemy_amnt; x ++)
            {
            	if (!x)
               	highest_enemy = 0;

               if (enemy_matrix [x] [1] > enemy_matrix [highest_enemy] [1])
	            	highest_enemy = x;
            }

				if (enemy_amnt)
	            monster_aim [current_monster_id] = enemy_matrix [highest_enemy] [0];
         }

        	cel = monster_aim [current_monster_id];

         if (cel == -1)
         {
         	x_pos = h_pos;
            y_pos = v_pos;
         }
         else if (cel >= 0)
         {
         	x_pos = h_pos_mon [cel];
            y_pos = v_pos_mon [cel];
         }

         distance = sqrt (pow (x_pos - h_pos_mon [current_monster_id], 2) + pow (y_pos - v_pos_mon [current_monster_id], 2));

			if (cel >= -1)
   	   {
	      	a = check_visibility (current_monster_id, cel);

   	      if (a)	// widzi cel
	         {
					if (kod_p == _BAYBARS)		// Baybars
				   {
/*   	         	if (monster_pp [current_monster_id] > 10)	// gdy moze jeszcze rzucic czar
							targeting (current_monster_id, 1, 1);		// 1: spell, 1: lightning ray
	               else*/
                  if (monster_decision)
	              		move_monster (current_monster_id, cel);

						if (monster_pp [current_monster_id] < monster_exp [current_monster_id] / 2)
	      	         monster_pp [current_monster_id] ++;
				   }
					else if (kod_p == _SOLDIER || kod_p == _ARMED_NOMAD || kod_p == _CLASS_Cyborg || kod_p == _Flint_Westwood)
				   {
               	if (losuj_2 (2, 40) > 35 && distance <= 5)
							targeting (current_monster_id, 1, 1);
                  else
					   	move_monster (current_monster_id, cel);
				   }
					else if (kod_p == _HENCHMEN)
				   {
               	if (losuj_2 (1, 5) > 3 && distance <= 4)
							targeting (current_monster_id, 1, 1);
                  else
					   	move_monster (current_monster_id, cel);
				   }
				   else
				   	move_monster (current_monster_id, cel);
         	}
      	   else		// nie widzi celu = random move
   	      	move_monster (current_monster_id, -2);
	      }
			else if (cel == -5 || cel == -6 || cel == -7)		// gdy neutralny / stoi w miejscu
         {
         	if (kod_p >= 1100 && kod_p < 1200)
            {
            	if (monster_pp [current_monster_id] == 1)
               {
                  if (unpaid_items_amnt [kod_p])
                  {
                  	if (floor_planszy [h_pos] [v_pos] != monster_char [current_monster_id])
                     {
		               	msg ("-Stop ya thief! _");
      		            monster_speed [current_monster_id] = 15;
            		   	monster_pp [current_monster_id] = -1;
               			monster_aim [current_monster_id] = -1;

                        for (a = 0; a < items_amount; a ++)
                        	if (unpaid_items [a] == kod_p)
                           {
						            item_value_material [a] -= 50;
                           	unpaid_items [a] = 0;
                           }
                     }
                     else
		               	move_monster (current_monster_id, -100 - search_door (1));			// do drzwi, monster_char = floor_code podlogi sklepu = floor_code drzwi
                  }
						else
                  	monster_pp [current_monster_id] = 0;
               }
               else if (monster_pp [current_monster_id] == 0 && unpaid_items_amnt [kod_p])
               {
               	msg ("Better do not try to steal that! ");
                  monster_pp [current_monster_id] = 1;
               }
               else
               	move_monster (current_monster_id, -2);
            }
           	else if (cel == -6 && check_visibility (current_monster_id, cel))	// jezeli monster stoi w miejscu i zauwazy gracza
            {
              	monster_aim [current_monster_id] = -1;
		     		move_monster (current_monster_id, cel);				// cel: -5 (neutralny): random move, -6: stoi w miejscu
           	}
            else if (cel == -5)						// neutralny
            {
	  	      	move_monster (current_monster_id, -2);				// random move
            }
         }
		}

		if (bonus [current_monster_id] / total_speed / 32)
			bonus [current_monster_id] = bonus [current_monster_id] - total_speed * 32;
   }
}

char event_monster (int attacker_id, int x_pos, int y_pos)
{
   char coverers_amount;
   char stan_type;
   int obstacle_type;
	char event_code = 0;
   int floor_type;
   int monster_kod;

	monster_kod = monsters_planszy [x_pos] [y_pos];

	if (monster_aim [attacker_id] >= -1 && monster_kod >= -1)		// wrogo nastawiony monster
   {
   	if (monster_kod == monster_aim [attacker_id]		// napatacza sie cel potwora
      || (monster_alignment [attacker_id] >= 0 && goody_reputation [cl_id] < 0 || monster_alignment [attacker_id] < 0 && badass_reputation < 0) && monster_kod == -1	// napatacza sie gracz
      || monster_kod >= 0 && monster_alignment [attacker_id] > 0 && monster_alignment [monster_kod] < 0		// napatacza sie przeciwny alignment
      || monster_kod >= 0 && monster_alignment [attacker_id] < 0 && monster_alignment [monster_kod] > 0)		// napatacza sie przeciwny alignment
			monster_attack (attacker_id, monster_kod, monster_kod, 0, 0);
	}
	else if (monster_kod == -15)
	{
     	floor_type = floor_planszy [x_pos] [y_pos];
		stan_type = stan_planszy [x_pos] [y_pos];

      if (!stan_type)			// just floor
  	      enter_perm = 1;
      else if (stan_type == 1)		// one item
  	      enter_perm = 1;
      else if (stan_type == 2)		// only obstacle
  	   {
     		obstacle_type = obstacles_planszy [x_pos] [y_pos];

			if (item_group [obstacle_type] == 50 || item_group [obstacle_type] == 53 || item_group [obstacle_type] == 55)
  	      	enter_perm = 1;
     	   else if (item_group [obstacle_type] == 51)
         {
	      	trap (monster_code [attacker_id], obstacle_type);
   	      enter_perm = 1;
        	}
         else if (item_group [obstacle_type] == 52 || item_group [obstacle_type] == 54)
  	      	door (monster_code [attacker_id], obstacle_type);
		}
      else if (stan_type == 4)		// item + obstacle
  	   {
     	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

         if (item_group [obstacle_type] == 51)
	      	trap (monster_code [attacker_id], obstacle_type);
         else if (item_group [obstacle_type] == 52)
  	      	door (monster_code [attacker_id], obstacle_type);
      }
      else if (stan_type == 8)		// several items
  	      enter_perm = 1;
      else if (stan_type == 9)		// severeal items + obstacle
  	   {
     	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

         if (item_group [obstacle_type] == 51)
	      	trap (monster_code [attacker_id], obstacle_type);
         else if (item_group [obstacle_type] == 52)
  	      	door (monster_code [attacker_id], obstacle_type);
      }
   }

	event_code = enter_perm;

   return event_code;
}

void move_monster (int kod_p, int move_type)
{
	int x_pos, y_pos;
   int cel = monster_aim [kod_p], x_move = 0, y_move = 0;
	int taken_way [10];

  	if (move_type >= -1 || move_type <= -100)
	{
   	if (move_type == -1)		// celem jest player
      {
			x_pos = h_pos;
         y_pos = v_pos;
      }
      else if (move_type >= 0)
      {
      	x_pos = h_pos_mon [cel];
         y_pos = v_pos_mon [cel];
      }
      else							// celem sa np. drzwi sklepu
      {
      	move_type *= -1;
      	x_pos = h_pos_item [move_type - 100];
         y_pos = v_pos_item [move_type - 100];
      }

		taken_way [_UPPER_LEFT] = check_way (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] - 1);		// check_way: zwraca -5 gdy mozna przejsc
		taken_way [_UP] = check_way (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] - 1);
		taken_way [_UPPER_RIGHT] = check_way (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] - 1);
		taken_way [_LEFT] = check_way (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p]);		// check_way: zwraca -5 gdy mozna przejsc
		taken_way [_RIGHT] = check_way (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p]);
		taken_way [_DOWN_LEFT] = check_way (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] + 1);
		taken_way [_DOWN] = check_way (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] + 1);		// check_way: zwraca -5 gdy mozna przejsc
		taken_way [_DOWN_RIGHT] = check_way (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] + 1);

		if (x_pos == h_pos_mon [kod_p] && y_pos < v_pos_mon [kod_p])			// ruch w gore
		{
			if (taken_way [_UP] != -100 && taken_way [_UP] < -1 || taken_way [_UP] == monster_aim [kod_p])
			{
				y_move = -1;
				event_monster (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] - 1);
				current_way [kod_p] = _UP;
			}
			else if (taken_way [_UPPER_LEFT] != -100)
			{
				x_move = y_move = -1;
				event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] - 1);
				current_way [kod_p] = _UPPER_LEFT;
			}
			else if (taken_way [_UPPER_RIGHT] != -100)
			{
				x_move = 1;
            y_move = -1;
				event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] - 1);
				current_way [kod_p] = _UPPER_RIGHT;
			}
/*			else
			{
				if ((current_way [kod_p] == _RIGHT || current_way [kod_p] == _UPPER_RIGHT) && taken_way [_RIGHT] != -1 && taken_way [_UP] != monster_aim [kod_p])
				{
					event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p]);
					x_move = 1;
				}
				else if ((current_way [kod_p] == _LEFT || current_way [kod_p] == _LEFT) && taken_way [_LEFT] != -1 && taken_way [_UP] != monster_aim [kod_p])
				{
					event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p]);
					x_move = -1;
				}
			}*/
		}
		else if (x_pos < h_pos_mon [kod_p] && y_pos < v_pos_mon [kod_p])	// ruch lewo-gora
		{
			if (taken_way [_UPPER_LEFT] != -100 && taken_way [_UPPER_LEFT] < -1 || taken_way [_UPPER_LEFT] == monster_aim [kod_p])
			{
            x_move = -1;
				y_move = -1;
				current_way [kod_p] = _UPPER_LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_UP] != -100)
			{
				y_move = -1;
				current_way [kod_p] = _UP;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_LEFT] != -100)
			{
				x_move = -1;
				current_way [kod_p] = _LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN] != -100)
			{
				y_move = 1;
				current_way [kod_p] = _DOWN;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
		}
		else if (x_pos > h_pos_mon [kod_p] && y_pos < v_pos_mon [kod_p])	// ruch prawo-gora
		{
			if (taken_way [_UPPER_RIGHT] != -100 && taken_way [_UPPER_RIGHT] < -1 || taken_way [_UPPER_RIGHT] == monster_aim [kod_p])
			{
            x_move = 1;
				y_move = -1;
				current_way [kod_p] = _UPPER_RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_UP] != -100)
			{
				y_move = -1;
				current_way [kod_p] = _UP;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_RIGHT] != -100)
			{
				x_move = 1;
				current_way [kod_p] = _RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
		}
		else if (x_pos > h_pos_mon [kod_p] && y_pos > v_pos_mon [kod_p])	// ruch prawo-dol
		{
			if (taken_way [_DOWN_RIGHT] != -100 && taken_way [_DOWN_RIGHT] < -1 || taken_way [_DOWN_RIGHT] == monster_aim [kod_p])
			{
            x_move = 1;
				y_move = 1;
				current_way [kod_p] = _DOWN_RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_RIGHT] != -100)
			{
				x_move = 1;
				current_way [kod_p] = _RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN] != -100)
			{
				y_move = 1;
				current_way [kod_p] = _DOWN;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
		}
		else if (x_pos < h_pos_mon [kod_p] && y_pos > v_pos_mon [kod_p])	// ruch lewo-dol
		{
			if (taken_way [_DOWN_LEFT] != -100 && taken_way [_DOWN_LEFT] < -1 || taken_way [_DOWN_LEFT] == monster_aim [kod_p])
			{
            x_move = -1;
				y_move = 1;
				current_way [kod_p] = _DOWN_LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN] != -100)
			{
				y_move = 1;
				current_way [kod_p] = _DOWN;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_LEFT] != -100)
			{
				x_move = -1;
				current_way [kod_p] = _LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
		}
		else if (x_pos > h_pos_mon [kod_p] && y_pos == v_pos_mon [kod_p])	// ruch w prawo
		{
			if (taken_way [_RIGHT] != -100 && taken_way [_RIGHT] < -1 || taken_way [_RIGHT] == monster_aim [kod_p])
			{
            x_move = 1;
				current_way [kod_p] = _RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_UPPER_RIGHT] != -100)
			{
				x_move = 1;
				y_move = -1;
				current_way [kod_p] = _UPPER_RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN_RIGHT] != -100)
			{
				x_move = 1;
				y_move = 1;
				current_way [kod_p] = _DOWN_RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
		}
		else if (x_pos < h_pos_mon [kod_p] && y_pos == v_pos_mon [kod_p])	// ruch w lewo
		{
			if (taken_way [_LEFT] != -100 && taken_way [_LEFT] < -1 || taken_way [_LEFT] == monster_aim [kod_p])
			{
            x_move = -1;
				current_way [kod_p] = _LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_UPPER_LEFT] == -15)
			{
				x_move = -1;
				y_move = -1;
				current_way [kod_p] = _UPPER_LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN_LEFT] != -100)
			{
				x_move = -1;
				y_move = 1;
				current_way [kod_p] = _DOWN_LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else
			{
				if ((current_way [kod_p] == _UP || current_way [kod_p] == _UPPER_LEFT) && taken_way [_UP] < -1 && taken_way [_UP] != -100 || taken_way [_UP] == monster_aim [kod_p])
				{
					y_move = -1;
					event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
				}
				else if ((current_way [kod_p] == _DOWN || current_way [kod_p] == _DOWN_LEFT) && taken_way [_DOWN] < -1 && taken_way [_DOWN] != -100 || taken_way [_DOWN] == monster_aim [kod_p])
				{
					y_move = 1;
					event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
				}
			}
/*			else if (taken_way [_UP] != -100)
			{
				y_move = -1;
				current_way [kod_p] = _UP;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN] != -100)
			{
				y_move = 1;
				current_way [kod_p] = _DOWN;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}*/
		}
		else if (y_pos > v_pos_mon [kod_p] && x_pos == h_pos_mon [kod_p])	// ruch w dol
		{
			if (taken_way [_DOWN] != -100 && taken_way [_DOWN] < -1 || taken_way [_DOWN] == monster_aim [kod_p])
			{
            y_move = 1;
				current_way [kod_p] = _DOWN;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN_RIGHT] != -100)
			{
				x_move = 1;
				y_move = 1;
				current_way [kod_p] = _DOWN_RIGHT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
			else if (taken_way [_DOWN_LEFT] != -100)
			{
				x_move = -1;
				y_move = 1;
				current_way [kod_p] = _DOWN_LEFT;
				event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
			}
		}
	}
	else if (move_type == -5 || move_type == -2)			// random move -5: neutrala, -2: wrogiego
	{
		x_move = losuj (-1, 1);
		y_move = losuj (-1, 1);

      if (check_way (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move) != -100)
			event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);
	}

	if (enter_perm)
	{
		change_monster_position (x_move, y_move, current_monster_id);
		enter_perm = 0;
	}

   return 0;
}

void change_monster_position (int x_move, int y_move, int kod_p)
{
	int x_pos = h_pos_mon [kod_p], y_pos = v_pos_mon [kod_p];

	if (check_own_visibility (x_pos, y_pos) && cl_id != 1999)
  		put_char (plansza [x_pos] [y_pos], x_pos, y_pos);

	monsters_planszy [x_pos] [y_pos] = -15;

	h_pos_mon [kod_p] += x_move;
	v_pos_mon [kod_p] += y_move;

	if (check_own_visibility (h_pos_mon [kod_p], v_pos_mon [kod_p]) && cl_id != 1999)
		put_char (monster [kod_p], h_pos_mon [kod_p], v_pos_mon [kod_p]);

	monsters_planszy [h_pos_mon [kod_p]] [v_pos_mon [kod_p]] = kod_p;
}

int check_way (int attacker_id, int x_pos, int y_pos)
{
   char coverers_amount;
   char stan_type;
   int obstacle_type;
	int event_code = -100;		// nie mozna przejsc
   int floor_type;
   int monster_kod;

	monster_kod = monsters_planszy [x_pos] [y_pos];

	if (monster_kod != -15)
		event_code = monster_kod;
	else if (monster_kod == -15)
	{
      floor_type = floor_planszy [x_pos] [y_pos];

      if (monster_char [attacker_id] >= 0 && floor_type == monster_char [attacker_id])
      	event_code = -15;
      else if (monster_char [attacker_id] == -1 || monster_aim [attacker_id] >= -1)
      {
      	if (floor_type >= 0 && floor_type <= 10 || floor_type >= 100 && floor_type <= 120 || floor_type == 28)
	         event_code = -15;
   	   else if (floor_type == 21)		
      	  	event_code = -15;
	      else if (floor_type == 22)
   	     	event_code = -15;
      	else if (floor_type == 23)
        		event_code = -15;
      }

		if (event_code == -15)
      {
			stan_type = stan_planszy [x_pos] [y_pos];
         enter_perm = 0;

	      if (!stan_type)			// just floor
   	      event_code = -15;
	      else if (stan_type == 1)		// one item
   	      event_code = -15;
	      else if (stan_type == 2)		// only obstacle
   	   {
      		obstacle_type = obstacles_planszy [x_pos] [y_pos];

				if (item_group [obstacle_type] == 50 || item_group [obstacle_type] == 53 || item_group [obstacle_type] == 55)
   	      	event_code = -15;
      	   else if (item_group [obstacle_type] == 51)		// pulapka
	         {
	   	      event_code = -20;
         	}
	         else if (item_group [obstacle_type] == 52 || item_group [obstacle_type] == 54)
   	      	event_code = -30;				// drzwi
			}
	      else if (stan_type == 3)		// several items
   	      event_code = -15;
	      else if (stan_type == 4)		// item + obstacle
   	   {
      	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

	         if (item_group [obstacle_type] == 51)
		      	event_code = -20;
	         else if (item_group [obstacle_type] == 52)
  	      		event_code = -30;
	      }
	      else if (stan_type == 9)		// severeal items + obstacle
   	   {
      	   obstacle_type = obstacles_planszy [x_pos] [y_pos];

	         if (item_group [obstacle_type] == 51)
		      	event_code = -20;
	         else if (item_group [obstacle_type] == 52)
            	event_code = -30;
	      }
		}
   }

   return event_code;
}

char monster_decision (int kod_p, int kod_m)
{
	char decision [3], a, road_move, monster_choice = 0;

   for (a = 0; a < 3; a ++)
   	decision [a] = 0;

	road_move = find_road (kod_p, kod_m);

	return monster_choice;
}

char find_road (int kod_p, int kod_m)
{
		int x_pos, y_pos;

   	if (kod_m == -1)		// celem jest player
      {
			x_pos = h_pos;
         y_pos = v_pos;
      }
      else
      {
      	x_pos = h_pos_mon [kod_m];
         y_pos = v_pos_mon [kod_m];
      }

		if (x_pos - h_pos_mon [kod_p] < 0 && y_pos == v_pos_mon [kod_p])	// ruch w lewo
		{
			event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p]);
		}
		else if (x_pos - h_pos_mon [kod_p] < 0 && y_pos - v_pos_mon [kod_p] < 0)	// ruch lewo-gora
		{
			event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] - 1);
		}
		else if (x_pos - h_pos_mon [kod_p] > 0 && y_pos - v_pos_mon [kod_p] < 0)	// ruch prawo-gora
		{
			event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] - 1);
		}
		else if (x_pos - h_pos_mon [kod_p] > 0 && y_pos - v_pos_mon [kod_p] > 0)	// ruch prawo-dol
		{
			event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] + 1);
		}
		else if (x_pos - h_pos_mon [kod_p] < 0 && y_pos - v_pos_mon [kod_p] > 0)	// ruch lewo-dol
		{
			event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] + 1);
		}
		else if (x_pos - h_pos_mon [kod_p] > 0 && y_pos == v_pos_mon [kod_p])	// ruch w prawo
		{
			event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p]);
		}
		else if (y_pos - v_pos_mon [kod_p] < 0 && x_pos == h_pos_mon [kod_p])	// ruch w gore
		{
			event_monster (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] - 1);
		}
		else if (y_pos - v_pos_mon [kod_p] > 0 && x_pos == h_pos_mon [kod_p])	// ruch w dol
		{
			event_monster (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] + 1);
		}
}
