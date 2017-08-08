#include "deklaracje.h"

void update_weapon_level (char weapons)
{
	int hand_ [2];
	int missile_slot = item_body [_SIDEARM_SLOT];
   char hand_no;
   int kod_b;

   hand_ [0] = item_body [_MELEE_SLOT];
   hand_ [1] = 0;//item_body [_RHAND];

	for (hand_no = 0; hand_no < 2; hand_no ++)
   {
		if ((kod_b = hand_ [hand_no]) != -1)						// w lewej lapie bron - obliczaj
   	{
   		if (item_group [kod_b] == 3)				// bron jednoreczna
	      {
				if (weapon_marks [item_type [kod_b]] < 100)
   		   	weapon_level [item_type [kod_b]] = 0;
				else if (weapon_marks [item_type [kod_b]] < 200)
      			weapon_level [item_type [kod_b]] = 1;
	      }
   	   else if (item_group [kod_b] == 4)		// bron obureczna
      	{
				if (weapon_marks [item_type [kod_b]] < 100)
   		   	weapon_level [item_type [kod_b]] = 0;
				else if (weapon_marks [item_type [kod_b]] < 200)
      			weapon_level [item_type [kod_b]] = 1;
	      }
      }
	}

   if (missile_slot != -1)
   {
   }

	if (!weapons)		// przelicz reszte weapon leveli
   {
   }
}

void gain_experience (long int exp_points)
{
	experience += exp_points;
	statystyki (13);
}

void level_upgrade ()
{
	int i = 1, j = 0, kod_k, kod_p, kod_f, _position = 0, x, _refresh = 1;
   int choosen, choice_no = 1;
   int exp_limit = total_knowledge / 4 + 1;
   char _choice_variants [100];

   for (x = 1; x <= 9; x ++)
   	if (abilities [x] == abilities_pot [x])
      	_choice_variants [x - 1] = '0';
      else
      	_choice_variants [x - 1] = '1';

   _choice_variants [x] = '\0';

	while (i)
	{
		if (_refresh)
			make_window (0, 2, 0, 0, 78, 23, -2,		// 0: typ okna = nie oczekuj na klawisz (1: oczekuj), 2: rodzaj ramki, 0: X lewego g. rogu, 0: Y lewego g. rogu, 78: size_x, 23: size_y, -2: okno NIE informacji o potworze
		   "^n       Ability         Current    Potential"
	   	"^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n^n   Select ability to progress            Press '+' or Enter"
	  		, 8, 8);												// 8: kolor ramki, 8: kolor tekstu

      if (!_position)
		{
		   for (x = 1; x <= 9; x ++)
		   	if (abilities [x] < abilities_pot [x])
					j ++;

         if (!j)		// brak abilities do wymaxowania
            j = -1;
      	else
         	j = 0;

      	for (x = 1; x <= 9; x ++)
         {
	      	gotoxy (19, 5 + x);
            messages ("^", abilities [x], 23);
            gotoxy (22, 5 + x);
            messages ("[^]", abilities_pot [x], 24);
         }
		}
      else
		{
      	gotoxy (19, 5 + _position);
         messages ("^", abilities [_position], 23);
      	gotoxy (22, 5 + _position);
         messages ("[^]", abilities_pot [_position], 24);
		}

      gotoxy (33, 22);

      if (!j)
      {
	      messages ("(^ of ", choice_no, 23);
   	   messages ("^)", exp_limit, 23);
			choosen = choice (9, _choice_variants, '+', -1, -1, 105, 5, 7, 23, 7, 6, _position);
      }
      else
      {
	      messages ("            Press Esc or 'x' to exit", 0, 23);
		  	choosen = choice (9, _choice_variants, _ESC, 'x', -1, 105, 5, 7, 23, 7, 6, _position);
      }

		if (choosen >= 1 && choosen <= 9)
		{
			_position = choosen;
			_refresh = 0;
		}
		else if (choosen >= 101 && choosen <= 109)
		{
      	choosen -= 100;

			abilities [choosen] += rzut (106);

         if (abilities [choosen] >= abilities_pot [choosen])
         {
         	abilities [choosen] = abilities_pot [choosen];
            _choice_variants [choosen - 1] = '0';
         }

		   for (x = 1; x <= 9; x ++)
		   	if (abilities [x] < abilities_pot [x])
					j ++;

			_position = choosen;
			_refresh = 0;
			choice_no ++;

      	if (choice_no == exp_limit + 1 || !j)
         {
         	for (x = 1; x <= 9; x ++)
	         	_choice_variants [x - 1] = '0';

            if (abilities [_position] == abilities_pot [_position])
					_choice_variants [_position - 1] = '2';

         	j = -1;
         }
         else
         	j = 0;
		}
		else if (choosen == _ESC + 300 || choosen == 'x' + 300)
			i = 0;
   }

   rysuj_ekran ();
}

