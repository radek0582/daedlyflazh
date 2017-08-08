#include "deklaracje.h"

void chat ()
{
	int x_pos, y_pos, choice, near_monster = 0, place = 0;
   int chat_mon = 0, i, kod_p, kod_mon;

   msg_reset ();

	for (y_pos = v_pos - 1; y_pos <= v_pos + 1; y_pos ++)
   	for (x_pos = h_pos - 1; x_pos <= h_pos + 1; x_pos ++)
      	if ((i = monsters_planszy [x_pos] [y_pos]) >= 0)
         {
	         chat_mon = i;
        		near_monster ++;
	   	}

   if (!near_monster)
   {
   	if (health > max_health / 2)
   		msg ("<You feel quite good.");
      else
   		msg ("<You feel rather exhausted.");
   }
   else
   {
   	if (near_monster > 1)
      {
      	msg ("<Choose a monster you want to talk with... ");
         key_direction ();

	      if (chat_mon == -2)
	   		msg ("<You talk to yourself. ");

	      chat_mon = monsters_planszy [temp1] [temp2];
      }

      if (chat_mon >= 0)
      {
      	kod_mon = monster_code [chat_mon];

      	if (monster_aim [chat_mon] == -1 && monster_code [chat_mon] != _zombie)
         {
	         enter_monster (monster_code [chat_mon], COLOR_GRAY, -0, 0);
				messages (" grunts in anger! ", 0, COLOR_GRAY);
         }
         else
         {
				msg ("<You talk to ");
   	      enter_monster (monster_code [chat_mon], COLOR_GRAY, -1000, 0);
				messages (".|", 0, COLOR_GRAY);

		   	if (monster_code [chat_mon] == _Father_Grigori)
		      {
		         if (!quest [0])
      		   {
		         	quest [0] = 1;
						msg ("-Find the lost amulet and I will reward You. ");

		            i = losuj_3 (1, 2, 3);

						if (i == 1)
      		      {
		            	x_pos = 19;
	   		         y_pos = 18;
		            }
		            else if (i == 2)
      		      {
		            	x_pos = 18;
	   		         y_pos = 7;
		            }
      		      else if (i == 3)
		            {
      		      	x_pos = 43;
	         		   y_pos = 6;
		            }

					   create_item (_AMULET, 0, x_pos, y_pos, 1);
		         }

      		   if (quest [0] == 1)
		         {
      		   	kod_p = search_item (29, 2);

		            if (kod_p >= 0)
      		      {
							msg ("-Thank You for this amulet I have lost it few days ago... ");
		              	ujmij_item (kod_p, 1);
      		        	quest [0] = -10;
                     max_health = total_max_health += 2;
                     statystyki (11);
		            }
      		   }
		         else if (quest [0] == -10)
      		   {
		         	if (!quest [1])
      		      {
							msg ("-I want You to clean the graveyard... Here is the key to a gate. Be careful of nasty enemies. ");
	   		         take_new_item (_key_to_graveyard, 1, 1);
		            	quest [1] = 1;
		            }

         		   if (quest [1] == -1)
		            {
							msg ("-Good work my son. As a reward I will give you some gold. ");
						   take_new_item (_GCDC, 10, 1);
		            	quest [1] = -10;
      		      }
		         }

               if (quest [15] == 1)
               {
               	quest [15] = 2;
               	msg ("-Such horrible news from my friend Bum I hear! Terrible time has come to us again. Humanity has to face another evil. Heh... I want you to bring me some proof of that massacre, some tool or weapon of that murders. We will analyze them. ");
               }
               else if (quest [15] == 2)
               {
			        	kod_p = search_item (1, 6);

                  if (kod_p >= 0)
                  {
	               	msg ("-It can't be... I can't believe what happened to Bum! But the bloody axe proofs definetly he has lost his mind and killed the crew in Atlantic Accelerator! ");
                  	quest [15] = -10;
                     quest [16] = 1;
                  }
                  else
	               	msg ("-Bring the real proof of murders in AA. ");
               }
               else if (quest [15] == -10)
               {
	               if (quest [16] == -1 || killed_monsters [_Bum] && quest [16] != -10)
   	            {
      	         	quest [16] = -10;
         	      	msg ("- You proved your goodness to humanity and now the soul of Bum will be judged by the mightest one. ");
						   take_new_item (_GCDC, 20, 1);
                     gain_achievement (27);
               	}
	               else if (quest [16] == 1)
   	            	msg ("- Return to me when you complete the mission in AA. That lost soul of Bum has to leave realm before it hurts himself or (God, protect us) someone else... ");
               }
		      }
		   	else if (monster_code [chat_mon] == _zombie)
					msg ("-Uuuuuuuurgh... ");
		   	else if (kod_mon == _FEMALE_CITIZEN || kod_mon == _FEMALE_NOMAD)
            {
					msg ("-I am not allowed to talk to strangers, go away. ");

               achievement_temp [9 * 50] = 1;
               achievement_temp [9 * 50 + 1] = cl_id;
            }
		   	else if (monster_code [chat_mon] == _Heisen)
      		{
		      	if (!quest [2])
      		   {
		         	quest [2] = 1;
						msg ("-Deliver this package to Pink in Old Remo. ");
   	      		ekwipunek (_Sealed_package, -1, 1);
		         }
		         else if (quest [2] == 1)
      		   {
						msg ("-I am waiting for news from my friend Pink. ");
      		   }
		         else if (quest [2] == -1)
		         {
		         	quest [2] = -10;
						msg ("-Good news. Take this gold as a reward. ");
					   take_new_item (_GCDC, 20, 1);
                  gain_achievement (32);
		         }
		      }
   			else if (monster_code [chat_mon] == _Flint_Westwood)
		      {
		      	if (!quest [3])
      		   {
		         	quest [3] = 1;
						msg ("-Talk to Bob and Carl. I have a headache coz of their problem. ");
		         }
      		   else if (quest [3] >= 1)
		         {
						msg ("-Solve problem between Bob and Carl. ");
		         }
		         else if (quest [3] == -1)
		         {
      		   	quest [3] = -10;
						msg ("-Thank You. Take this nice gun as a reward. ");
					   take_new_item (_6Wayne, 1, 1);
		         }
		         else if (quest [3] == -10 && quest [8] == 1)
		         {
      		   	msg ("-Yeah I known this son of a bitch, its D'Morgan a fellow citizen, please put him on the ground. ");
            		quest [8] = 2;
		         }
      		   else if (quest [8] == 2)
		         {
      		   	msg ("-Return to me when you complete your mission. ");
		         }

      		   if (quest [8] == -1 && quest [3] == -10)
		         {
      		   	quest [8] = -10;
						msg ("-Take this gold as a reward for killing D'Morgan. ");
					   take_new_item (_GCDC, 30, 1);
			      	gain_achievement (2);
		         }
		      }
   			else if (monster_code [chat_mon] == _Bartender)
		      {
		      	if (quest [3] == 1)
      		   {
		         	if (!quest [4] || quest [4] == 1)
      		      {
            			quest [4] = 2;
							msg ("-Bring me some alloys and I will fix the altar. ");
      		      }
            		else if (quest [4] == 2)
		            {
				        	kod_p = search_item (29, 3);

		               if (kod_p >= 0)
      		         {
//	         		     	quest [5] = -10;
		                  quest [4] = -1;
								msg ("-These alloys could solve problem with altar... ");
            		      ujmij_item (kod_p, 1);
	   	            }
                     else
								msg ("-Come here when you find some alloys. ");
   	   	      }
   		      }
		      }
		   	else if (monster_code [chat_mon] == _Priest)
		      {
      			if (quest [3] == 1)
		         {
      		   	if (quest [4] >= 0)
            		{
                  	if (!quest [4])
                     	quest [4] = 1; 

							msg ("-I need Bob, bartender to fix the altar. ");
            		}
		            else if (quest [4] <= -1)
      		      {
            			quest [4] = -10;
		               quest [3] = -1;
							msg ("-Thank You! I have told Flint about your help! ");
	           		}
   		      }
		      }
		   	else if (monster_code [chat_mon] == _Wise_Arse)
      		{
		      	if (quest [9] >= 0)
      		   {
						msg ("-Could you fix our purifer ? We need it... ");
      		   }
		      }
		   	else if (monster_code [chat_mon] == _Rayo)
      		{
		      	if (!quest [6])
      		   {
		         	quest [6] = 1;
						msg ("-Slay the rat king. That animal hurt my brother. [sniff] ");
		         }
					else if (quest [6] == 1)
		         {
						msg ("-Hurry! As a proof bring me it's flesh. ");

		            kod_p = search_item (19, 4);

   		         if (kod_p >= 0)
		            {
	   		      	quest [6] = -10;
   	      		   quest [7] = 1;

							msg ("-Rat is killed... Could You heal my brother with this medikit? ");
	   		            take_new_item (_MEDIKIT, 1, 1);
		         	}
		         }
      		}
		   	else if (monster_code [chat_mon] == _Helc)
      		{
		         if (quest [7] == 1)
      		   {
         			msg ("-Can You help me brother? ");
		         }
      		   else if (quest [7] == -1)
		         {
      		   	quest [7] = -10;
            		msg ("-That was NOT rat king which hurt me so badly... Tha was... Young man called himself, somethin' like \"Di Lore Gan\". Last thing i remeber he says \"soon you ground on oceans bottom\". ");

		            if (quest [8] > -10)
	   		         quest [8] = 1;

   		      	create_item (_AXE, 0, h_pos, v_pos, 1);
                  gain_achievement (12);
		         }
      		}
		   	else if (monster_code [chat_mon] == _Pinkman)
      		{
		        	kod_p = search_item (15, 5);

		      	if (kod_p >= 0)
      		   {
		         	quest [2] = -1;
						msg ("-Thanks man. Big thanks to Heisen and take a reward from him. ");
   	      		ujmij_item (kod_p, 1);
		         }
      		}
		   	else if (monster_code [chat_mon] == _D_Morgan)
      		{
		      	if (quest [8] == 2)
      		   {
						msg ("-That looser Flynt sent you?! Die!!! ");
		            monster_aim [chat_mon] = -1;
      		   }
		         else
						msg ("-Leave me alone, a need to fix my boat. ");
		      }
		   	else if (monster_code [chat_mon] == _Marston)
      		{
		      	if (quest [13] == -1)
      		   {
               	quest [13] = -10;
						msg ("-Thank you brother for your help with cleaning this mess... As a reward I will give you the key to armory and some money. ");
                  take_new_item (_GCDC, 10, 1);
                  take_new_item (_key_to_mystuff, 1, 1);
      		   }
		      }
		   	else if (monster_code [chat_mon] == _Bren_McGuire)
		      {
      			if (!quest [9])
		         {
      		     	quest [9] = 1;
						msg ("-We have a problem with radioactive water. I want you to go to Shelter TEC and solve our problem.");
					   take_new_item (_tool_box, 1, 1);
		         }
		         else if (quest [9] == -1)			// done
      		   {
						msg ("-Well done... Thanks for your good job and saving our people. Here is the key to president's quarter. Go and talk to him.");
      		   	quest [9] = -10;
			   		take_new_item (_GCDC, 30, 1);
					   take_new_item (_key_to_president, 1, 1);
//                 	gain_achievement (30); 
      		   }
		      }
   			else if (monster_code [chat_mon] == _Pleasence)
		      {
		      	if (achievement_temp [33 * 50])
               {
               	msg ("-Damn what a mess and terror you bring with you! From these days the society will call you \"LOBO\". _");
                  gain_achievement (33);
               }

      			if (quest [9] == -10)
		         {
      		   	if	(!quest [10])
		            {
      		      	quest [10] = 1;
							msg ("-Excelent work with purifer. Please do one more thing to mankind...Destroy core64 terminal in CLASS Corp. location. This little thing could help you finishing this job. ");
		            	take_new_item (_high_explosive, 1, 1);
      		         map_secret [0] = 1;
		         	}
      		   }

		         if (quest [10] == -1)
      		   {
		           	quest [10] = -10;
      		      msg ("-You have just saved the world!_");
            		play = -1;
                 	gain_achievement (18);
		         }
      		}
		   	else if (monster_code [chat_mon] == _Shades)
      		{
		      	kod_p = search_obstacle (64, 1);

					if (!quest [12])
               {
	      		   if (item_specials1 [kod_p] == 1)		// fixed
			         {
      	         	quest [12] = 1;
         	         quest [11] = -10;
      		         map_secret [1] = 1;
            	   	msg ("-Now slay president. Go to New York City and join our extermination. ");
                     goody_reputation [_New_York_City_Warzone] = -10;
                     badass_reputation [_New_York_City_Warzone] = 10;
                     goody_reputation [_Downtown_Mayhem] = -10;
                     badass_reputation [_Downtown_Mayhem] = 10;
      		   	}
			         else if (item_specials1 [kod_p] == -1)					// broken
			         {
				      	if (!quest [11])
   	   			   {
			   	        	quest [11] = 1;
								msg ("-Fix the core64 terminal. ");
           					take_new_item (_tool_box, 1, 1);
		      		   }
   	   		   }
               }
               else if (quest [12] == -1)
               {
		           	quest [12] = -12;
      		      msg ("After you killed Pleasence, the president of New York City the World changed for tousands of years. The era of humanoid robots has began._");
            		play = -2;
               	gain_achievement (19);
               }
		      }
		   	else if (monster_code [chat_mon] == _Bum)
      		{
		      	if (quest [14] == 1)
  	   		   {
						msg ("- Are you the one who can help us at last? I hope so... Some terrible things happened here days ago. Cyborgs slayed our crew and now they are hiding somewhere here. ");
		           	quest [14] = 2;
      		   }
		      	else if (quest [14] == 3)
  	   		   {
						msg ("- You talked to him? Don't trust machines. If you are a true human trust human and kill that cyborg which murdered our crew. ");
        				take_new_item (_GCDC, 5, 1);
		           	quest [14] = -10;
						quest [15] = 1;
      		   }
		      	else if (quest [15] == -1)
  	   		   {
						msg ("-. ");
      		   }
		      }
		   	else if (monster_code [chat_mon] == _CLASS_Cyborg)
      		{
		      	if (quest [14] == 2)
  	   		   {
						msg ("- Don't disturb me, I am working... I saw many bodies here. I think a murder is somewhere here. ");
		           	quest [14] = 3;
      		   }
               else
						msg ("- Don't disturb me, I am working here. ");
		      }
		   }
      }
   }
}
