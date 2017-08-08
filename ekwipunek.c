#include "deklaracje.h"

void ekwipunek (int kod_przedmiotu, int item_owner_id, char kod_miejsca)
{
	item_id = items_amount;
   item_owner [item_id] = item_owner_id;
   item [item_id] = kod_miejsca;

	switch (kod_przedmiotu)
	{
   // melee
		case _B_BAT:				//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga  val/mater  amnt   stan
			item_stats ('}' + GRAY, 	1, 	1, 	0, 	0, 	101, 		4, 	1, 	1, 	0, 	0, 	600, 	  	201, 	1, 	0);              //
			break;
		case _AXE:	   			//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga     mater  amnt   stan
			item_stats ('}' + GRAY, 	1, 	2, 	0, 	0, 	101, 		6, 	1, 	1, 	0, 	0, 	600, 	  	901, 	1, 	0);              //
			break;
		case _SHIV: 				//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga     mater  amnt   stan
			item_stats ('}' + GRAY, 	1, 	3, 	0, 	0, 	101, 		2, 	1, 	1, 	0, 	0, 	600, 	  	101, 	1, 	0);              //
			break;
		case _HAMMER:  			//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga     mater  amnt   stan
			item_stats ('}' + GRAY, 	1, 	4, 	0, 	0, 	101, 		5, 	1, 	1, 	0, 	0, 	600, 	  	301, 	1, 	0);              //
			break;
		case _KNIFE: 	 			//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga  val/mater  amnt   stan
			item_stats ('}' + GRAY, 	1, 	5, 	0, 	0, 	101, 		3, 	1, 	1, 	0, 	0, 	600, 	  	701, 	1, 	0);              //
			break;
		case _bloody_shiv:  		//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga     mater  amnt   stan
			item_stats ('}' + GRAY, 	1, 	6, 	0, 	0, 	101, 		2, 	1, 	1, 	0, 	0, 	600, 	  	121, 	1, 	0);              //
			break;

	// sidearm
		case _2KRR:                                                 // * //
			item_stats ('}' + GRAY, 	2, 	1, 	24, 	0, 	101, 		2, 	3, 	1,    3,    24, 	600, 		1101, 	1, 	0);              //
			break;
		case _M119:
			item_stats ('}' + GRAY, 	2, 	2, 	7, 	0, 	101, 		4, 	1, 	1,    3,    7, 	600, 		901, 		1, 	0);              //
			break;
		case _6Wayne:
			item_stats ('}' + GRAY, 	2, 	3, 	6, 	0, 	101, 		3, 	1, 	2,    3,    6, 	600, 		601, 	1, 	0);              //
			break;
         
	// prime
		case _NT9000:
			item_stats ('}' + GRAY,    3, 	1, 	1, 	0, 	101, 	  25, 	1, 	101, 	6, 	1, 	600, 		4001, 	1, 	0);              //
			break;
		case _Reza:
			item_stats ('}' + BROWN,   3, 	2, 	20, 	0, 	101, 	   3, 	2, 	1, 	8, 	20, 	600, 		1701, 	1, 	0);              //
			break;
		case _16M:
			item_stats ('}' + GRAY,    3, 	3, 	30, 	0, 	101, 	   4, 	3, 	3, 	5, 	30, 	600, 		2001, 	1, 	0);              //
			break;
		case _Panzor:
			item_stats ('}' + GRAY,    3, 	4, 	15, 	0, 	101, 	  15, 	1, 	4, 	2, 	15, 	600, 		2001, 	1, 	0);              //
			break;
		case _3GM3:
			item_stats ('}' + GRAY,    3, 	5, 	100, 	0, 	101, 	  13, 	10, 	5, 	4, 	100, 	600, 		2701, 	1, 	0);              //
			break;

	// body
		case _RAGS:
			item_stats ('}' + GRAY,    4, 	1,    1,    0,    101,     0,    1,    1, 	0, 	0, 	200, 		301,    1,    0);					//
			break;
		case _JACKET:
			item_stats ('}' + GRAY,    4, 	2,    2,    0,    101,     0,    1,    1, 	0, 	0, 	200, 		1001,    1,    0);					//
			break;
		case _CEVLAR:
			item_stats ('}' + GRAY,    4, 	3,    5,    0,    101,     0,    1,    1, 	0, 	0, 	200, 		4001,    1,    0);					//
			break;
		case _COAT:
			item_stats ('}' + GRAY,    4, 	4,    3,    0,    101,     0,    1,    1, 	0, 	0, 	200, 		2001,    1,    0);					//
			break;
		case _M65:
			item_stats ('}' + DARK_GREEN,   4, 	5,    2,    0,    101,     0,    1,    1, 	0, 	0, 	200, 		2001,    1,    0);					//
			break;

		case _AMULET:
			item_stats ('\'' + GRAY, 29, 2, 0, 1, 410, 0, 1, 0, 0, 0, 600, 2001, 1, 0);					// amulet
			break;
		case _ALLOYS:
			item_stats ('\'' + GRAY, 29, 3, 0, 1, 410, 0, 1, 1, 0, 0, 600, 2001, 1, 0);					// alloys
			break;
		case _remains_from_droid:
			item_stats ('\'' + BLUE, 29, 4, 0, 1, 410, 0, 1, 1, 0, 0, 600, 2001, 1, 0);				
			break;

		case _bullets_9mm:
			item_stats ('*' + GRAY, 	25, 	1, 	0, 	1, 	1, 		0, 	1, 	1, 	0, 	0, 	600, 		201, 	1, 	0);					// bullets
			break;
		case _357:
			item_stats ('*' + YELLOW, 	25, 	2, 	0, 	1, 	1, 		0, 	1, 	1, 	0, 	0, 	600, 		201, 	1, 	0);					// bullets
			break;
		case _233:
			item_stats ('*' + RED, 	25, 	3, 	0, 	1, 	1, 		0, 	1, 	1, 	0, 	0, 	600, 		201, 	1, 	0);					// bullets
			break;
		case _granates:
			item_stats ('*' + DARK_GRAY, 	25, 	101, 	0, 	1, 	1, 		0, 	1, 	1, 	0, 	0, 	600, 		1001, 	1, 	0);					// bullets
			break;

		case 100:
			item_stats (')' + GRAY, 5, 11, 0, 6, 614, 10, 1, 1, 0, 0, 1200, 2001, 1, 0); 				// falchion
			break;
		case 105:
			item_stats (')' + GRAY, 5, 12, 0, 4, 108, 0, 1, 0, 0, 0, 800, 2001, 1, 0);					// steel spear
			break;
		case 260:
			item_stats ('!' + BLUE, 23, 1, 0, 0, 101, 0, 1, 0, 0, 0, 25, 200, 1, 0);						// ! of water
			break;
		case 330:
			item_stats (34 + 512, 14, 401, 0, 0, 101, 0, 1, 0, 500, 0, 500, 500, 1, 0);					// " of Ligth
			break;
		case 331:
			item_stats (34 + 512, 14, 402, 0, 0, 101, 0, 1, 0, 500, 0, 500, 500, 1, 0);					// " of Web
			break;
		case 420:
			item_stats (42 + 1024, 16, 1, 0, 0, 101, 0, 1, 0, 0, 0, 2, 100, 1, 0);						// * a piece of glass
			break;
      case 450:
      	item_stats (41 + 1536, _PRIME_SLOT, 1, 0, 0, 103, 0, 1, 0, 100, 0, 200, 2000, 1, 0);					// bow - specials1 / range increasing
         break;
      case 451:
      	item_stats (41 + 1536, _PRIME_SLOT, 2, 0, 0, 204, 0, 1, 0, 100, 0, 300, 2000, 1, 0);					// xbow - specials1 / range increasing
         break;
      case 452:
      	item_stats (41 + 1536, _PRIME_SLOT, 3, 0, 0, 102, 0, 1, 0, 100, 0, 200, 2000, 1, 0);					// small crossbow - specials1 / 100: range increasing
         break;
      case 453:
      	item_stats (41 + 1536, _PRIME_SLOT, 4, 0, 0, 308, 0, 1, 0, 100, 0, 300, 2000, 1, 0);					// siege bow - specials1 / 100: range increasing
         break;
      case 480:
      	item_stats (47 + GRAY, _PRIME_SLOT, 21, 0, 0, 102, 0, 1, 0, 100, 30, 10, 1003, 1, 0);					// arrow - specials1 (range increase), specials2 (max amount in stock)
         break;
      case _SHURIKEN:
			item_stats (42 + GRAY, _PRIME_SLOT, 22, 0, 1, 203, 0, 1, 0, 100, 10, 5, 1001, 1, 0);						// shaken (hira shuriken)
			break;
      case 495:
      	item_stats (47 + GRAY, _PRIME_SLOT, 23, 0, 0, 104, 0, 1, 0, 100, 50, 20, 1003, 1, 0);					// bolt
         break;
      case 500:
      	item_stats (92 + 3584, 21, 401, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of light - specials / 3: charges
         break;
      case 501:
      	item_stats (92 + 3584, 21, 1, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of lightning ray - specials / 3: charges
         break;
      case 511:
      	item_stats (92 + 3584, 21, _LIGHTNING_BALL, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of lightning ball - specials / 3: charges
         break;
      case 521:
      	item_stats (92 + WHITE, 21, 201, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of webbing - specials / 3: charges
         break;
      case 525:
      	item_stats (92 + DARK_GRAY, 21, 403, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of darkness - specials / 3: charges
         break;
      case 530:
      	item_stats (92 + DARK_GRAY, 21, 501, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of door creation - specials / 3: charges
         break;
      case 535:
      	item_stats (92 + DARK_GRAY, 21, 502, 0, 0, 101, 0, 1, 0, 3, 0, 5, 5000, 1, 0);						// wand of trap creation - specials / 3: charges
         break;
		case _BUCKLER:
			item_stats (']' + GRAY, 20, 1, 2, 1, 103, 0, 1, 0, 2, 0, 1000, 2003, 1, 0);								//
			break;
		case _PROTECTOR:
			item_stats (']' + GRAY, 20, 2, 4, 1, 103, 0, 1, 0, 3, 0, 1500, 2001, 1, 0);							//
			break;
		case _LARGE_PAVISE:
			item_stats (']' + GRAY, 20, 2, 6, 1, 103, 0, 1, 0, 4, 0, 1500, 2001, 1, 0);							//
			break;
		case _STING:
			item_stats ('I' + WHITE, 6, 1, 0, 0, 814, 0, 1, 0, 0, 0, 100, 2001, 1, 0);							// sting
			break;
		case _KATAR:
			item_stats ('I' + WHITE, 6, 2, 0, 0, 816, 0, 1, 0, 0, 0, 100, 2001, 1, 0);							// katar
			break;
		case _NIZAR_SPINE:
			item_stats ('I' + WHITE, 6, 3, 0, 0, 1016, 0, 1, 0, 0, 0, 200, 2001, 1, 0); 						// nizar spine
			break;
		case _RUNIC_TALON:
			item_stats ('I' + WHITE, 6, 4, 0, 0, 1020, 0, 1, 0, 0, 0, 200, 2001, 1, 0); 						// runic talon
			break;
		case _CRUSADER_ICON:
			item_stats ('=' + VIOLET, 29, 1, 0, 0, 102, 0, 1, 0, 0, 0, 200, 2001, 1, 0);
			break;
      case 906:
      	item_stats (91 + 1536, 22, 1, 0, 1, 206, 0, 1, 0, 6, 0, 5000, 1003, 1, 0);					// oak log, specials 6: oak
         break;
      case 907:
      	item_stats (91 + 1536, 22, 1, 0, 1, 206, 0, 1, 0, 7, 0, 5000, 1003, 1, 0);					// hornbeam log
         break;
      case 908:
      	item_stats (91 + 1536, 22, 1, 0, 1, 206, 0, 1, 0, 8, 0, 5000, 1003, 1, 0);					// larch log
         break;
      case 909:
      	item_stats (91 + 1536, 22, 1, 0, 1, 206, 0, 1, 0, 9, 0, 5000, 1003, 1, 0);					// pine log
         break;
      case 910:
      	item_stats (91 + 1536, 22, 1, 0, 1, 206, 0, 1, 0, 10, 0, 5000, 1003, 1, 0);				// birch log
         break;

      case 925:
      	item_stats (91 + 1536, 15, 1, 0, 0, 101, 0, 1, 0, 1000, 0, 200, 1003, 1, 0);	  			// torch
         break;
      case 920:
      	item_stats (91 + 1536, 15, 2, 0, 0, 101, 0, 1, 0, 1000, 0, 250, 1000, 1, 0);				// hatchet
         break;
      case 930:
      	item_stats (91 + 1536, 15, 3, 0, 0, 101, 0, 1, 0, 1000, 0, 1000, 1000, 1, 0);				// climbing set
         break;
      case _MEDIKIT:
      	item_stats ('+' + WHITE, 15, 4, 0, 0, 101, 0, 1, 0, 0, 0, 100, 1503, 1, 0);	  			// MEDIKIT
         break;
		case _Sealed_package:
			item_stats ('%' + DARK_BLUE, 	 15, 	5, 	0,  	0, 	102, 	0, 	1, 	0, 	0, 	101, 		200, 		2001, 	1, 	0);
			break;
		case _tool_box:
			item_stats ('%' + BROWN, 15, 	6, 	0, 	0, 	102,  0, 	1, 	0, 	0, 	102, 		200, 		2001, 	1, 	0);
			break;
		case _high_explosive:
			item_stats ('"' + RED, 15, 	7, 	0, 	0, 	102,  0, 	1, 	0, 	10, 	0, 		200, 		3001, 	1, 	0);
			break;

		case 990:
			item_stats ('$' + GRAY, 17, 1, 0, 0, 101, 0, 1, 1, 0, 0, 1, 106, 1, 0);								// silver coin
			break;
		case 991:
			item_stats ('$' + YELLOW, 17, 2, 0, 0, 101, 0, 1, 1, 0, 0, 1, 105, 1, 0);								// gold coin
			break;
		case _GCDC:
			item_stats ('$' + DARK_GREEN, 17, 3, 0, 0, 101, 0, 1, 1, 0, 0, 1, 105, 1, 0);								// GCDC
			break;
		case _BAYBARS_COIN:
			item_stats ('$' + RED, 17, 7, 0, 0, 101, 0, 1, 1, 0, 0, 1, 105, 1, 0);								// Baybars coin
			break;

      case 1000:
      	item_stats (46 + kolor_floor, 51, 1, 0, 0, 0, 101, 0, 0, 0, 0, 1000, 0, 1, 0);			// water trap
         break;
      case 1100:									//  group  type   AV    hit   dices  dmgBon stat  ident spec1 spec2  waga  val/mater  amnt   stan
      	item_stats (43 + BROWN + 8192,  			52, 	1, 	0,    0, 	0, 		101, 	0, 	0, 	0, 	0, 	1000, 20003, 		1, 	0);  	// wooden door - type: 1 - closed, 2 - opened; specials: trapped
         break;
      case 1101:
      	item_stats (43 + DARK_GRAY + 8192,		52, 	1, 	0, 	0, 	0, 		101, 	0, 	0, 	0, 	0, 	1000, 20001, 		1,    0);  	// steel door - type: 1 - closed, 2 - opened, 3 - locked; specials: trapped; specials2: type of lock
         break;
      case 1102:
      	item_stats (43 + DARK_GRAY + 8192, 		52,   3, 	0, 	0, 	0, 		101, 	0,    0, 	0, 	0, 	1000, 20001, 		1, 	0);  	// closed steel door - type: 1 - closed, 2 - opened, 3 - locked; specials: trapped; specials2: type of lock
         break;
      case 1103:
      	item_stats ('/' + BROWN, 					52, 	2,    0, 	0,    0, 		101,  0, 	0, 	0, 	0, 	1000, 20003, 		1, 	0);  	// wooden door - type: 1 - closed, 2 - opened; specials: trapped
         break;
      case 1104:		// wooden locked burning door
      	item_stats ('+' + RED + 8192,  			52, 	3, 	0,    0, 	0, 		101, 	0, 	0, 	0, 	0, 	1000, 20003, 		1, 	1);  	// wooden door - type: 1 - closed, 2 - opened; specials: trapped
         break;
      case 1105:
      	item_stats (43 + DARK_GRAY, 				54, 	1, 	0, 	0, 	0, 		101, 	0, 	0, 	0, 	0, 	1000, 20001, 		1, 	0);  	// kraty - type: 1 - closed, 2 - opened; specials1: trapped, specials2: rodzaj zamka
         break;
      case 1106:
      	item_stats (43 + DARK_GRAY, 				54, 	3, 	0, 	0, 	0, 		101, 	0, 	0, 	0, 	10, 	1000, 20001, 		1, 	0);  	// kraty - type: 1 - closed, 2 - opened, 3 - locked; specials1: trapped
         break;
      case 1107:
      	item_stats ('|' + DARK_GRAY + 8192, 54, 3, 0, 0, 0, 101, 0, 0, 0, 101, 1000, 20001, 1, 0);  	// brama - type: 1 - closed, 2 - opened, 3 - locked; specials1: trapped
         break;
      case 1110:
      	item_stats (60 + kolor_wall, 50, _UPWARDS, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);  	// stairs; type upwards, specials: identity number
         break;
      case 1111:
      	item_stats (62 + kolor_wall, 50, _DOWNWARDS, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);  	// stairs; type downwards
         break;
      case 1150:
      	item_stats (95 + GRAY, 53, 1, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);  	// altar, type 1: christian
         break;
      case 1151:
      	item_stats (95 + GRAY, 53, 2, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);  	// altar, type 2: muslim
         break;
      case 1152:
      	item_stats (95 + GRAY, 53, 3, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);  	// altar, type 3: jewish
         break;
      case _GRAVE:
      	item_stats ('+' + BROWN, 55, 1, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);  	// grave
         break;
      case _STATUE:
      	item_stats ('8' + GRAY, 60, 1, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _toxic_barrel:
      	item_stats ('X' + DARK_GREEN, 63, 1, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _core64_terminal:
      	item_stats ('6' + DARK_GREEN, 64, 1, 0, 0, 0, 101, 0, 0, -1, 0, 0, 0, 1, 0);
         break;

      case _boat_element_1:
      	item_stats ('^' + GRAY, 61, 1, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _boat_element_2:
      	item_stats ('I' + GRAY, 61, 2, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _boat_element_3:
      	item_stats ('V' + GRAY, 61, 3, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _boat_element_4:
      	item_stats ('/' + GRAY, 61, 4, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _boat_element_5:
      	item_stats ('\\' + GRAY, 61, 5, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _boat_element_6:
      	item_stats ('o' + GRAY, 61, 6, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _water_purifier:
      	item_stats ('o' + BLUE, 62, 1, 0, 0, 0, 101, 0, 0, 1, 0, 0, 0, 1, 0);
         break;
      case _water_purifier_terminal:
      	item_stats ('o' + BLUE, 62, 2, 0, 0, 0, 101, 0, 0, -1, 0, 0, 0, 1, 0);
         break;
      case 1200:
      	item_stats ('|' + WHITE, 70, 1, 0, 0, 0, 101, 0, 0, 1, 100, 0, 0, 1, 0);  	// coverer: web
         break;
		case _key_to_graveyard:
			item_stats ('=' + VIOLET, 	 	24, 1, 0, 0, 0, 0, 1, 0, 0, 101, 200, 2001, 1, 0);
			break;
		case _key_to_president:
			item_stats ('=' + DARK_RED, 	24, 2, 0, 0, 0, 0, 1, 0, 0, 201, 200, 2001, 1, 0);
			break;
		case _key_to_Core64:
			item_stats ('=' + YELLOW, 	 	24, 3, 0, 0, 0, 0, 1, 0, 0, 202, 200, 2001, 1, 0);
			break;
		case _key_to_mystuff:
			item_stats ('=' + GRAY, 	 	24, 13, 0, 0, 0, 0, 1, 0, 0, 13, 200, 2001, 1, 0);
			break;
		case _KEY:
			item_stats ('=' + GRAY, 		24, 10, 0, 0, 0, 0, 1, 0, 0, 10, 200, 2001, 1, 0);
			break;

      case 2001:		// ciala potworow, item_type = monster_code
      	item_stats (38 + 2048, 19, 1, 0, 0, 101, 0, 1, 0, 2000, 0, 100, 500, 1, 0);	// rat corpse, specials1: turns to rot
         break;
      case 2003:
      	item_stats (38 + 2560, 19, 3, 0, 0, 101, 0, 1, 0, 10000, 0, 2500, 500, 1, 0);	// mutated rat leader corpse, specials: turns to rot
         break;
      case 2004:
      	item_stats (38 + 2560, 19, 4, 0, 0, 101, 0, 1, 0, 0, 0, 2500, 500, 1, 0);	// rat king
         break;
      case 2060:
      	item_stats (38 + 2048, 19, 60, 0, 0, 101, 0, 1, 0, 2000, 0, 2500, 500, 1, 0);	// wolf corpse, specials: turns to rot
         break;
      case 2080:
      	item_stats (38 + 1024, 19, 80, 0, 0, 101, 0, 1, 0, 2000, 0, 500, 100, 1, 0);	// spider corpse
         break;
      case 2100:
      	item_stats (38 + 512, 19, 100, 0, 0, 101, 0, 1, 0, 2000, 0, 4000, 500, 1, 0);	// kobold corpse, specials: turns to rot
         break;
      case 2110:
      	item_stats (38 + 512, 19, 110, 0, 0, 101, 0, 1, 0, 2000, 0, 10000, 100, 1, 0);	// orc corpse
         break;
      case _nomad_body:
      	item_stats (38 + 512, 19, 146, 0, 0, 101, 0, 1, 0, -1, 0, 10000, 100, 1, 0);	// nomad body
         break;
      case _body:
      	item_stats (38 + 512, 19, 900, 0, 0, 101, 0, 1, 0, -1, 0, 10000, 100, 1, 0);	// body
         break;
      case _mutilated_body:
      	item_stats (38 + RED, 19, 901, 0, 0, 101, 0, 1, 0, -1, 0, 10000, 100, 1, 0);	// body
         break;

      case 3001:
      	item_stats (38 + WHITE, 19, 1001, 0, 0, 101, 0, 1, 0, 2000, 0, 10, 100, 1, 0);		// elven waffer
         break;
      case 3002:
      	item_stats (38 + YELLOW, 19, 1002, 0, 0, 101, 0, 1, 0, 2000, 1500, 100, 100, 1, 0);	// iron ration
         break;
      case _food:
      	item_stats (38 + YELLOW, 19, 1003, 0, 0, 101, 0, 1, 0, 2000, 1500, 100, 700, 1, 0);
         break;
      case 3020:
      	item_stats (38 + VIOLET, 19, 1020, 0, 0, 101, 0, 1, 0, 2000, 100, 7, 100, 1, 0);	// hallucinogen mushroom
         break;
      case _drug:
      	item_stats (38 + GREEN, 19, 1030, 0, 0, 101, 0, 1, 0, 2000, 100, 7, 500, 1, 0);	// drug
         break;
      default:
  			item_stats ('{' + GRAY, 1, 1, 1, 0, 101, 0, 1, 0, 0, 0, 100, 1010, 1, 0);				// hood
			break;
	}

//   if (item_owner_id == -1)
//   	action_item (-1, h_pos, v_pos, 10, item_id);		// 5 = do plecaka
}

void item_stats (int item_ico, char item_grupa, int item_typ, int item_def,
	char hit, int item_dmg_val1, char item_dmg_val2, char item_stat, char ident,
   int item_specs1, int item_specs2, int item_waga, int item_mater, int amount, char stan)
{
	int k, j;

	item_icon [item_id] = item_ico;
	item_group [item_id] = item_grupa;
	item_type [item_id] = item_typ;
	item_dv [item_id] = item_def;
	item_hit [item_id] = hit;
	item_dices [item_id] = item_dmg_val1;
	item_dmg_bonus [item_id] = item_dmg_val2;
	item_status [item_id] = item_stat;
   item_ident [item_id] = ident;
	item_specials1 [item_id] = item_specs1;
	item_specials2 [item_id] = item_specs2;
	item_weight [item_id] = item_waga;
	item_value_material [item_id] = item_mater;
   item_amount [item_id] = amount;
   item_state [item_id] = stan;

	if (item_grupa == 3)	// czy grupa weapons
	{
//		item_hit [item_id] += rand () % 7 - 2;
//		item_dmg_bonus [item_id] += 100;
	}
   else if (item_grupa == 19)		// foods
   {
//   	if (item_typ < 1000)			// cialka
//      	item_specials1 [item_id] += rand () % 30 - 15;
   }

   working_items [item_id] = 0;

  	k = item_group [item_id];
   j = item_type [item_id];

	if (k == 19 && j < 1000 && item_specials1 [item_id] > 0)		// gnijace jedzenie
   	working_items [item_id] = 1;
   else if (k == 15 && j == 1 && item_specials2 [item_id])		// pochodnia plonaca
   	working_items [item_id] = 1;
   else if (item [item_id] == 5 && item_state [item_id] == 1)	// burning obstacle
   	working_items [item_id] = 1;

	items_amount ++;
}

void add_item (int kod_przedmiotu, int x_pos, int y_pos, int kod_pl)
{
	ekwipunek (kod_przedmiotu, -5, kod_pl);
   h_pos_item [item_id] = x_pos;
   v_pos_item [item_id] = y_pos;
//   put_item (item_id);
}

void przedmiot_na_mapie (int nr_elementu, int kod_p, int kod_f, int kod_typ, int amount)
{
   item_floor [nr_elementu] [0] = kod_p;
   item_floor [nr_elementu] [1] = kod_f;
   item_floor [nr_elementu] [2] = kod_typ;
   item_floor [nr_elementu] [3] = amount;
}
