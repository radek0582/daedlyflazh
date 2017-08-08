#include "deklaracje.h"

void enter_choice_segregator (char choice_type, char choice_no, int color_code, int color_b)
{
	if (color_code > 128)
	  	textcolor (color_code);

   if (choice_type == 0)				// gender
   {
		enter_player (choice_no, color_code);

      if (color_code > 128)
	      gender_description (choice_no);
   }
   else if (choice_type == 1)			// hand preference
		enter_hand (choice_no, color_code);
   else if (choice_type == 2)			// age
   {
		enter_age (choice_no, color_code);

      if (color_code > 128)
	      age_description (choice_no);
   }
	else if (choice_type == 3)			// game menu
		enter_menu_selection (choice_no, color_code);
	else if (choice_type == 104)			// body part selection (inventory)
   {
		enter_body_part (choice_no, color_code);

      if (color_code > 128)
	      item_description (choice_no);
   }
	else if (choice_type == 105)			// ability selection
		enter_ability (choice_no, color_code);

	if (color_code > 128)
	  	textcolor (color_code - 128);
}

int choice (int choice_amount, char _choice_variants [], char extra_choice1, char extra_choice2, char extra_choice3, char choice_type, char text_length, int kolor_t, int kolor_b, char x_pos, char y_pos, char prev_choice)
{
	int choosen = 0, a, b = 0, selected_position = 1;
   char y_offset = 0, repeat_choice = 1, choice_variants [100];
   int color_code_t = kolor_t, color_code_b = kolor_b;

   choice_variants [0] = '1';
   choice_variants [1] = 0;
	add_kopia (choice_variants, _choice_variants);
	key = 0;
	gotoxy (x_pos, y_pos);

   for (a = 1; a <= choice_amount; a ++)
   	if (choice_variants [a] != '1')
      	b ++;

	if (!prev_choice)
   {
		for (a = 1; a <= choice_amount; a ++)
		{
         if (choice_variants [a] == '0')
         	color_code_t = COLOR_DARK_GRAY;
         else
         	color_code_t = kolor_t;

			gotoxy (x_pos, y_pos + a - 1);
	   	enter_choice_segregator (choice_type, a, color_code_t + 16, kolor_b + 16);
		}

		a = 1;

		while (choice_variants [a] != '\0')
      {
      	if (choice_variants [a] == '1')
         	break;

      	a ++;
   	  	y_offset ++;
      }

	   selected_position = y_offset + 1;
   }
   else
   {
   	y_offset = prev_choice - 1;
	   selected_position = prev_choice;

		if (choice_variants [prev_choice] != '1')
        	color_code_t = COLOR_DARK_GRAY;
		else
        	color_code_t = kolor_t;

		if (b != choice_amount || choice_variants [prev_choice] == '2')
      {
			gotoxy (x_pos, y_pos + y_offset);
   		enter_choice_segregator (choice_type, selected_position, color_code_t + 16, kolor_b + 16);
      }

      while (1)
      {
      	if (b == choice_amount)
         	break;

			if (choice_variants [selected_position] == '1')
         {
			   selected_position = y_offset + 1;
           	break;
         }

        	if (y_offset >= choice_amount - 1)
         {
  	      	y_offset = 0;
     	      selected_position = 1;
         }
         else
  	      {
		   	y_offset += 1;
      	   selected_position += 1;
         }
      }
   }

	while (repeat_choice)
   {
   	if (b != choice_amount)
      {
		   gotoxy (x_pos, y_pos + y_offset);
  			enter_choice_segregator (choice_type, selected_position, kolor_t + 128, kolor_b + 16);
      }

      klawisz ();

		if ((key > 96 && key < 97 + choice_amount) && choice_variants [key - 96] == '1')
	   {
		   gotoxy (x_pos, y_pos + y_offset);
		   choosen = key - 96;
	   	enter_choice_segregator (choice_type, selected_position, kolor_t + 16, kolor_b + 16);
		   gotoxy (x_pos, y_pos + choosen - 1);
	   	enter_choice_segregator (choice_type, choosen, color_code_t + 128, kolor_b + 16);
   		repeat_choice = 0;
	   }
   	else if ((key == _ENTER || key == _ENTER2) && b != choice_amount)
	   {
   		repeat_choice = 0;
   		choosen = selected_position;
	   }
   	else if (key == extra_choice1 || key == extra_choice2 || key == extra_choice3)
	   {
   		repeat_choice = 0;

         if (key == '+')
	   		choosen = selected_position + 100;
         else if (key == '-')
         	choosen = selected_position + 200;
         else		// ESC, Bacskpace, etc...
         	choosen = key + 300;

		   gotoxy (x_pos, y_pos + y_offset);
	   	enter_choice_segregator (choice_type, selected_position, kolor_t + 16, kolor_b + 16);
	   }
   	else if ((key == '2' || key == '8' || key == 3 || key == 2 || key == 82 || key == 83) && b != choice_amount)
      {
		   gotoxy (x_pos, y_pos + y_offset);
	   	enter_choice_segregator (choice_type, selected_position, kolor_t + 16, kolor_b + 16);

	   	if (key == '2' || key == 2 || key == 82)
   	   {
         	while (1)
            {
	         	if (y_offset == choice_amount - 1)
   	         {
      	      	y_offset = 0;
         	      selected_position = 1;
	            }
   	         else
      	      {
				   	y_offset += 1;
		      	   selected_position += 1;
	            }

					if (choice_variants [selected_position] == '1')
               	break;
            }
	      }
	   	else if (key == '8' || key == 3 || key == 83)
   	   {
         	while (1)
            {
	         	if (y_offset == 0)
   	         {
				   	y_offset = choice_amount - 1;
   	   		   selected_position = choice_amount;
               }
	            else
   	         {
				   	y_offset -= 1;
   	   		   selected_position -= 1;
            	}

					if (choice_variants [selected_position] == '1')
               	break;
            }
   	   }
      }
   }

	return choosen;
}
