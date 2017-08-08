#include "deklaracje.h"
#define Radius 10	/* convergence domain radius */
#define Cx 1.80	/* real coordinate of image center */
#define Cy 0	/*  imaginary coordinate of image center  */
#define Side 0.07	/* half side of the complex square domain */
#define M 40	/* number of pixels of each side of the image */
#define Num 255	/* max iteration number */

void create_flag ()
{
	char nazwa_pliku [12] = {""};
   char dlugosc_name = 0;
   char znak, znak_mon;
   int i, j, k, l;
   int x, killed_monsters_amount = 0;
	unsigned long int elapsed_days = (elapsed_time / 86400) % 7;
	unsigned long int elapsed_hours = (elapsed_time / 3600) % 24;
	unsigned long int elapsed_minutes = (elapsed_time / 60) % 60;

   for (x = 0; x < 2000; x ++)
   	if (killed_monsters [x])
			killed_monsters_amount += killed_monsters [x];

	for (i = 0; i < 7; i ++)
   {
		nazwa_pliku [i] = player_name [i];

      if (!player_name [i])
      	break;

   	dlugosc_name ++;
   }

	nazwa_pliku [dlugosc_name] = '.';
   nazwa_pliku [dlugosc_name + 1] = 'f';
   nazwa_pliku [dlugosc_name + 2] = 'l';
   nazwa_pliku [dlugosc_name + 3] = 'g';
	temp10 = fopen (nazwa_pliku, "w");

   for (i = 0; i < Y_WINDOW; i ++)
   {
   	for (j = 0; j < X_WINDOW; j ++)
      {
			if (h_pos_pl + j - h_pos >= 0 && v_pos_pl + i - v_pos >= 0 && v_pos_pl + i - v_pos < Y_WINDOW && h_pos_pl + j - h_pos < X_WINDOW)
			   znak = mem_planszy [j] [i];
      	else
         	znak = 32;

			monster_id = monsters_planszy [j] [i];

         if (monster_id >= 0 && check_own_visibility (j, i))
         	znak = monster [monster_id];
         else if (monster_id == -1)		// PC
         	znak = player;

		   putc (znak, temp10);

         if (j == X_WINDOW - 1)
         	putc ('\n', temp10);
      }
   }

  	putc ('\n', temp10);
	messages (player_name, 0, 80);
   messages (" (", 0, 80);
   enter_player (player_gender, 80);
   messages (")", 0, 80);

   if (death == 1)
   {
	   messages (" was killed by ", 0, 80);
      enter_monster (monster_code [killing_monster_id], 80, -1000, 0);
      kropka (80);
   }
   else if (play == -1)
	   messages (" saved the World.", 0, 80);
   else if (play == -2)
	   messages (" lead the CLASS Cyborgs to ruling the World.", 0, 80);

   j = 0;

   for (i = 0; i < 100; i ++)
   	if (quest [i] == -10)
      	j ++;

  	putc ('\n', temp10);
	messages (player_name, 0, 80);
   messages (" completed ^ quests.\n\n", j, 80);
	enter_gender (player_gender, 1, 0, 80);			// 1 = He/She; 0 = nie zmniejszaj litery
   messages (" survived for ^ days", elapsed_days, 80);
   messages (" ^ hours", elapsed_hours, 80);
   messages (" ^ minutes.", elapsed_minutes, 80);
   messages (" ^ turns passed.", turns_amount, 80);
   messages ("\n\nFollowing perks were gained during ", 0, 80);
	enter_gender (player_gender, 2, -1000, 80);
   messages (" adventure:\n", 0, 80);

   for (i = 1; i < 15; i ++)
   {
      if (abilities [i])
      {
      	putc ('\n', temp10);
      	enter_ability (i, 80);

	      if (abilities [i] < 4)
				messages (" - ", 0, 80);
      }

      if (abilities [i] == 1)
      	messages ("ADE", 0, 80);
      else if (abilities [i] == 2)
      	messages ("SCA", 0, 80);
      else if (abilities [i] == 3)
      	messages ("PRO", 0, 80);
   }


/*   messages ("\n\r^ monsters perished under his attacks.", 0, 80);
   messages ("\n\r^ monsters perished under his attacks.", 1, 80);
   messages ("\n\r^ monsters perished under his attacks.", -10, 80);
   messages ("\n\r^ monsters perished under his attacks.", -100, 80);
   messages ("\n\r^ monsters perished under his attacks.", -500, 80);
   messages ("\n\r^ monsters perished under his attacks.", -505, 80);
   messages ("\n\r^ monsters perished under his attacks.", 10, 80);
   messages ("\n\r^ monsters perished under his attacks.", 100, 80);
   messages ("\n\r^ monsters perished under his attacks.", 1000, 80);
   messages ("\n\r^ monsters perished under his attacks.", 1001, 80);
   messages ("\n\r^ monsters perished under his attacks.", 10001, 80);
   messages ("\n\r^ monsters perished under his attacks.", 20101, 80);
   messages ("\n\r^ monsters perished under his attacks.", 11100, 80);
   messages ("\n\r^ monsters perished under his attacks.", 909, 80);*/

//   fraktal ();
  	fclose (temp10);
}

void fraktal ()
{
	int p, q, n, w;	/* integer variables */
	double x, y, xx, yy, Incx, Incy;	/* double precision variables */

	/* altenrative values: Cx 1.8616, 1.8622; Side 0.0015, 0.000030; Num 400, 700 */
	/* declaration of variables */
	/* data file */
	//	FILE *fp;
	//	fp = fopen("Mand.raw","w");	/* open data file */

	/* scanning of the complex domain */
	for (p = 1; p <= M; p++)
	{
		Incy = Cy - Side + 2*Side/M*p;
//		printf("%i %%\n", p*100/M);	/* screen message */
		putc ('\n', temp10);

		for (q = 1; q <= M; q++)
		{
			Incx = Cx - Side + 2*Side/M*q;
			x = 0;
			y = 0;
			w = 200;	/* background color */

			/* escape method */
			for ( n = 1; n <= Num; ++n)
			{
				xx = x*x - y*y - Incx;
				yy = 2*x*y - Incy;
				x = xx;
				y = yy;

				if ( x*x + y*y > Radius )	/* divergence condition */
				{
					w = n;
					n = Num;
				}
			}

			w = w * 93 / 256;
         w += 33;
   	   putc  (w, temp10);	/* wrtie the escape speeds into the data file */
		}
	}
}
