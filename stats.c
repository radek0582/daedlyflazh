#include "deklaracje.h"

void oblicz_stats ()                                                                                                 
{
	int i;
	int armor_inv = 0;		// armor level z calego inventory
   int event_subgroup = action_type % 64;
   int event_group = (action_type - event_subgroup) / 64;
//   int r_hand = item_body [_RHAND], l_hand = item_body [_LHAND];
   int damage_1, hit_1, damage_2, hit_2, attacks_r, attacks_l;
   char ustawienie;
	int current_strength = total_strength = strength;
   int current_knowledge = total_knowledge = knowledge;
   int current_mind = total_mind = mind;
   int current_dexterity = total_dexterity = dexterity;
   int current_max_health = total_max_health = max_health;
   int current_max_power = total_max_power = max_power;
   int current_max_air = total_max_air = max_air;
   int current_speed = total_speed = speed;
   int current_armor = total_armor = armor;

	damage_r = damage_l = 0;

/*	if (experience >= exp_next)
   {
   	exp_lev ++;
	   exp_next += (exp_lev + 1) * experience;
   	messages ("You advanced on next experience level ^. (more...)", exp_lev, 7);
      statystyki (13);

      do klawisz ();
      while (key != 32);

      level_upgrade ();
   }*/

	if (	character_state [0] == 4 && (satiation < 17000 || satiation > 21999) ||
   		character_state [0] == 5 && (satiation < 22000 || satiation > 24999) ||
         character_state [0] == 6 && satiation < 25000 ||
         character_state [0] == 3 && (satiation < 15000 || satiation > 16999) ||
         character_state [0] == 2 && (satiation < 13000 || satiation > 14999) ||
         character_state [0] == 1 && (satiation < 1000 || satiation > 12999))
		change_character_state (1);

   switch (character_state [0])
   {
      case 6:
      case 5:
   	case 4:
      	break;
      case 3:
      	current_strength = current_strength * 7 / 8;
         break;
      case 2:
      	current_strength = current_strength * 3 / 4;
         break;
      case 1:
      	current_strength = current_strength / 2;
         break;
   }

   if (total_strength != current_strength)
   {
   	total_strength = current_strength;
   	statystyki (1);
   }

   if (total_knowledge != current_knowledge)
   {
   	total_knowledge = current_knowledge;
   	statystyki (2);
   }

   if (total_mind != current_mind)
   {
   	total_mind = current_mind;
   	statystyki (4);
   }

   if (total_dexterity != current_dexterity)
   {
   	total_dexterity = current_dexterity;
   	statystyki (5);
   }

   if (total_max_health != current_max_health)
   {
   	total_max_health = current_max_health;
      statystyki (11);
   }

   if (total_max_power != current_max_power)
   {
   	total_max_power = current_max_power;
      statystyki (12);
   }

   if (total_max_air != current_max_air)
   {
   	total_max_air = current_max_air;
      statystyki (14);
   }

//   current_speed = speed + (total_dexterity * 3 + total_strength * 2) / 10 + 15;

//   if (floor_planszy [h_pos] [v_pos] == 21)	// kara za plywanie
//   	current_speed = (current_speed * sqrt (abilities [_CONDITION])) / ;

   current_speed = current_speed * action_cost / 128;		// modyfikator action_cost za ostatnia akcje

   if (!current_speed )
		current_speed = 1;

   if (total_speed != current_speed)
   {
   	total_speed = current_speed;
   	statystyki (9);
   }

/*	for (i = 1; i < 13; i ++)
		if (item [item_body [i]] == 4)
			armor_inv += item_dv [item_body [i]];

	current_armor = total_dexterity / 8 + armor_inv;
*/
	total_armor = item_dv [item_body [_BODY_SLOT]];

	if (player_gender == _MALE)
	   total_damage = 2;
   else
	   total_damage = 1;

   if (player_age == 2)			// adult
   	total_damage ++;

   if (item_body [_MELEE_SLOT] >= 0)			// w lapie bron
   	total_damage += item_dmg_bonus [item_body [_MELEE_SLOT]];

   update_weapon_level (1);		// uaktualnia poziom wyszkolenia w (1) noszonej broni

//	Ustawienia broni (rzeczy) w lapach. Symbole:
//	A - bron jednoreczna
// B - pusty slot
// C - inny przedmiot
// D - tarcza
// E - bron obureczna
// Np. A-D oznacza: A - bron jednoreczna w prawej lapie i D - tarcza w lewej

	if (cl_id == 1999)			// main map
   	view_range = 2;
   else if (cl_id == _Test)
   	view_range = 10;//total_mind * 5 / 8 + 1;
   else if (cl_id < 1300)		// surface
   	view_range = 10;//total_mind * 5 / 8 + 1;
   else								// dungeons
   	view_range = 5;//total_mind * 7 / 16 + 1;

/*	if (cl_id < 1999)
   {
	   if (item_group [item_body [_RHAND]] == 15 && item_specials2 [item_body [_RHAND]])		// pochodnia w prawej lapie
			view_range += 5;

	   if (item_group [item_body [_LHAND]] == 15 && item_specials2 [item_body [_LHAND]])		// p. w lewej lapie
   		view_range += 5;
   }*/
}

int weapon_damage (char rodzaj_broni, int typ_broni)
{
	int dmg_bns = 0;

	if (rodzaj_broni == 3)				// one-handed weapon
   {
   	switch (typ_broni)
      {
      	case 0:							// gola reka
         	dmg_bns = (weapon_level [0] + 1) * 2 - 2;
            break;
      }
   }
   else if (rodzaj_broni == 4)		// two-handed weapon
   {
   	switch (typ_broni)
      {
      }
   }
   else if (rodzaj_broni == 13)		// missiles
   {
   	switch (typ_broni)
      {
      }
   }

	return dmg_bns;
}

int weapon_hit (char rodzaj_broni, int typ_broni)
{
	int hit = 0;

	if (rodzaj_broni == 3)				// one-handed weapon
   {
   	switch (typ_broni)
      {
      }
   }
   else if (rodzaj_broni == 4)		// two-handed weapon
   {
   	switch (typ_broni)
      {
      }
   }
   else if (rodzaj_broni == 13)		// missiles
   {
   	switch (typ_broni)
      {
      }
   }

	return hit;
}
