#include "deklaracje.h"

int rng (int x1, int x2)
{
	long int liczba;

   liczba = monte_carlo [monte_carlo_number] * (x2 + 1 - x1) / 16384 + x1;
   monte_carlo_number ++;

   if (monte_carlo_number == 1000)
   	monte_carlo_number = 0;

   return liczba;
}

int losuj (int n1, int n2)
{
	int wynik;

	wynik = rand () % (n2 - n1 + 1) + n1;

   return wynik;
}

int losuj_2 (int n1, int n2)
{
   if (rand () % 2)
   	return n2;

   return n1;
}

int losuj_3 (int n1, int n2, int n3)
{
	char a = rand () % 3;

   if (a == 2)
   	return n3;
   else if (a == 1)
   	return n2;

   return n1;
}

int losuj_4 (int n1, int n2, int n3, int n4)
{
	char a = rand () % 4;

   if (a == 3)
   	return n4;
   else if (a == 2)
   	return n3;
   else if (a == 1)
   	return n2;

   return n1;
}

int rzut (int kostka)
{
	int suma_oczek = 0;
   int liczba_kosci = kostka / 100;
   int liczba_scianek = kostka % 100;
   int i;

   for (i = 1; i <= liczba_kosci; i ++)
   	suma_oczek += losuj (1, liczba_scianek);

   return suma_oczek;
}

char luck_test (int rnd_range, int rnd_mod, int warunek)
{
	char check_luck = 0;

   if (rand () % rnd_range + rnd_mod > warunek)
   	check_luck = 1;

   return check_luck;
}

