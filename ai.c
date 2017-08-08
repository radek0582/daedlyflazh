#include "deklaracje.h"

void AI ()
{
	int i, j, cel, kod_p;

	for (i = 0; i < monsters_amount; i ++)
	{
   	kod_p = monster_code [i];
	  	moves [i] = (monster_speed [i] + bonus [i]) / total_speed;
		bonus [i] += monster_speed [i] % total_speed;

	   for (j = 0; j < moves [i]; j ++)
   	{
        	cel = monster_aim [i];

			if (cel >= -1)
   	   {
	      	char a = check_visibility (i, cel);

   	      if (a)	// widzi cel
	         {
					if (kod_p == _BAYBARS)		// Baybars
				   {
/*   	         	if (monster_pp [i] > 10)	// gdy moze jeszcze rzucic czar
							targeting (i, 1, 1);		// 1: spell, 1: lightning ray
	               else*/
                  if (monster_decision)
	              		move_monster (i, cel);

						if (monster_pp [i] < monster_exp [i] / 2)
	      	         monster_pp [i] ++;
				   }
					else if (kod_p == _NECROMANCER1)		// Malek
				   {
   	         	if (monster_pp [i] > 10)	// gdy moze jeszcze rzucic czar
							targeting (i, 1, 102);	// 1: spell, 2: ice bolt
	               else
               		move_monster (i, cel);

						if (monster_pp [i] < monster_exp [i] / 2)
	      	         monster_pp [i] ++;
				   }
				   else
				   	move_monster (i, cel);
         	}
      	   else		// nie widzi celu = random move
	   	      	move_monster (i, -2);
	      }
			else if (cel == -5 || cel == -6)		// gdy neutralny / stoi w miejscu
         {
				if (kod_p == 1010)		// arena master
				{
             	if (quest [4] && !quest [5])
               {
                	quest [4] --;
                  quest [5] = -1;
	               teleport (-1, h_pos_mon [i] - 1, v_pos_mon [i]);
               }
               else
                 	move_monster (i, cel);
            }
            else
		     		move_monster (i, cel);				// cel: -5 (neutralny): random move, -6: stoi w miejscu
         }
		}

		if (bonus [i] / total_speed)
			bonus [i] = bonus [i] - total_speed;
   }
}

char monster_decision (int kod_p)
{
	return 0;	// don't move
}

char move_monster (int kod_p, int move_type)
{
	int x_pos, y_pos;
   int cel = monster_aim [kod_p], x_move, y_move;

  	if (move_type >= -1)
	{
   	if (move_type == -1)		// celem jest player
      {
			x_pos = h_pos;
         y_pos = v_pos;
      }
      else
      {
      	x_pos = h_pos_mon [cel];
         y_pos = v_pos_mon [cel];
      }

		if (x_pos - h_pos_mon [kod_p] < 0 && y_pos == v_pos_mon [kod_p])	// ruch w lewo
		{
			event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p]);

			if (enter_perm)
         {
  				enter_perm = 0;
	        	change_monster_position (4, kod_p);
         }
		}
		else if (x_pos - h_pos_mon [kod_p] < 0 && y_pos - v_pos_mon [kod_p] < 0)	// ruch lewo-gora
		{
			event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] - 1);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (7, kod_p);
			}
		}
		else if (x_pos - h_pos_mon [kod_p] > 0 && y_pos - v_pos_mon [kod_p] < 0)	// ruch prawo-gora
		{
			event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] - 1);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (9, kod_p);
			}
		}
		else if (x_pos - h_pos_mon [kod_p] > 0 && y_pos - v_pos_mon [kod_p] > 0)	// ruch prawo-dol
		{
			event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p] + 1);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (3, kod_p);
			}
		}
		else if (x_pos - h_pos_mon [kod_p] < 0 && y_pos - v_pos_mon [kod_p] > 0)	// ruch lewo-dol
		{
			event_monster (kod_p, h_pos_mon [kod_p] - 1, v_pos_mon [kod_p] + 1);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (1, kod_p);
			}
		}
		else if (x_pos - h_pos_mon [kod_p] > 0 && y_pos == v_pos_mon [kod_p])	// ruch w prawo
		{
			event_monster (kod_p, h_pos_mon [kod_p] + 1, v_pos_mon [kod_p]);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (6, kod_p);
			}
		}
		else if (y_pos - v_pos_mon [kod_p] < 0 && x_pos == h_pos_mon [kod_p])	// ruch w gore
		{
			event_monster (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] - 1);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (8, kod_p);
			}
		}
		else if (y_pos - v_pos_mon [kod_p] > 0 && x_pos == h_pos_mon [kod_p])	// ruch w dol
		{
			event_monster (kod_p, h_pos_mon [kod_p], v_pos_mon [kod_p] + 1);

			if (enter_perm)
			{
				enter_perm = 0;
	        	change_monster_position (2, kod_p);
			}
		}
	}
	else if (move_type == -5 || move_type == -2)			// random move -5: neutrala, -2: wrogiego
	{
     	x_move = rand () % 3 - 1;
      y_move = rand () % 3 - 1;
		event_monster (kod_p, h_pos_mon [kod_p] + x_move, v_pos_mon [kod_p] + y_move);

		if (enter_perm)
		{
      	if (x_move == -1 && y_move == -1)
         	x_move = 7;
      	else if (x_move == -1 && y_move == 0)
         	x_move = 4;
      	else if (x_move == -1 && y_move == 1)
         	x_move = 1;
      	else if (x_move == 0 && y_move == -1)
         	x_move = 8;
      	else if (x_move == 0 && y_move == 0)
         	x_move = 5;
      	else if (x_move == 0 && y_move == 1)
         	x_move = 2;
      	else if (x_move == 1 && y_move == -1)
         	x_move = 9;
      	else if (x_move == 1 && y_move == 0)
         	x_move = 6;
      	else if (x_move == 1 && y_move == 1)
         	x_move = 3;

			enter_perm = 0;
        	change_monster_position (x_move, kod_p);
		}
	}

   return 0;	// don't move
}

int monster_decision (int kod_m, int kod_v)
{
	int decision [3], a, road_move, monster_choice = 0;

   for (a = 0; a < 3; a ++)
   	decision [a] = 0;

	road_move = find_road (kod_m, kod_v)

	return monster_choice;
}
