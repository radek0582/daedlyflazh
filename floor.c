#include "deklaracje.h"

void convert_floor (int j, int i)
{
	switch (floor_planszy [j] [i])
   {
   	case 0:
      case 1000:
      	plansza [j] [i] = 46 + BROWN;	// wooden floor
         break;
   	case 1:
      case 1001:		// brzeg planszy (na wyjscie)
      case 2001:		// burning grass
			plansza [j] [i] = 46 + GREEN;	// grass
      	break;
      case 2:
      case 102:		// pow. sklepu (stone)
      case 112:		// pow. sklepu 2 (stone)
      case 1002:		// brzeg
      case 2002:		// burning
			plansza [j] [i] = 46 + GRAY;	// stone floor
      	break;
      case 3:
      case 1003:		// brzeg
			plansza [j] [i] = 46 + DARK_GRAY;	// platform
      	break;
      case 4:
      case 1004:		// brzeg
			plansza [j] [i] = 46 + YELLOW;	// sand
      	break;
      case 5:
      case 1005:
      	plansza [j] [i] = '%' + GREEN;	// bushes
         break;
      case 6:
      case 1006:
      	plansza [j] [i] = '&' + DARK_GREEN;	// light green tree
         break;
		case 7:
      case 1007:
         plansza [j] [i] = '&' + GREEN;
			break;
		case 8:
      case 1008:
      	plansza [j] [i] = '%' + GREEN;		// grapewine
         break;
      case 9:
      case 1009:
   		plansza [j] [i] = '&' + DARK_GREEN;  	// olive tree
			break;
      case 10:
      case 1010:
         plansza [j] [i] = '&' + GREEN;	// almond tree
         break;
		case 11:
      case 1011:
      	plansza [j] [i] = '#' + BROWN + 8192;	// wooden wall
         break;
      case 12:
      case 1012: 											// nie do przebicia
        	plansza [j] [i] = '#' + DARK_GRAY + 8192;	// stone wall
         break;
      case 2012:											// burning wall
        	plansza [j] [i] = '#' + RED + 8192;
         break;
      case 13:
      case 1013:
      	plansza [j] [i] = '#' + BROWN + 8192;	// clay wall
         break;
      case 14:
      case 1014:
      	plansza [j] [i] = '#' + YELLOW + 8192;	// sand wall
         break;
      case 15:
      case 1015:		// brzeg
			plansza [j] [i] = 46 + 2304;	// water floor
      	break;
      case 19:
      case 1019:
			plansza [j] [i] = '\'' + YELLOW;	// farm
      	break;
      case 20:			// low wall
      case 1020:
        	plansza [j] [i] = 'X' + DARK_GRAY;
         break;
      case 2020:											// burning lower wall
        	plansza [j] [i] = 'X' + RED;
         break;
      case 21:
      case 1021:		// brzeg
			plansza [j] [i] = 61 + BLUE;	// water
      	break;
      case 22:
      case 1022:		// brzeg
			plansza [j] [i] = 61 + WHITE;	// frozen water
      	break;
      case 23:
      case 1023:		// brzeg
			plansza [j] [i] = 61 + RED;	// lava
      	break;
      case 24:
      case 1024:		// brzeg
			plansza [j] [i] = 61 + BLUE;	// ocean
      	break;
      case 25:
      case 1025:
			plansza [j] [i] = 94 + WHITE + 8192;	// extremaly high and bold mountain
      	break;
      case 26:
      case 1026:		// brzeg
			plansza [j] [i] = 94 + GRAY;			// mountains
      	break;
      case 27:
      case 1027:		// brzeg
			plansza [j] [i] = 94 + WHITE;			// ice mountains
      	break;
      case _street:			// od 28 do 48 plaskie nawierzchnie
      case 1028:		// brzeg
			plansza [j] [i] = '"' + GRAY;			// street
      	break;
      case _helipad:
      case 1029:		// brzeg
			plansza [j] [i] = '"' + WHITE;			
      	break;
      case 40:
   	case 1040:		// brzeg
			plansza [j] [i] = 46 + WHITE;			// ice earth
      	break;
      case 49:
      case 1049:
			plansza [j] [i] = 94 + GRAY;			// very high mountains
      	break;
      case 41:
      case 1041:
			plansza [j] [i] = 94 + DARK_RED + 8192;	// extremally lava mountains
      	break;
      case 42:
      case 1042:		// brzeg
			plansza [j] [i] = 94 + RED;			// lava mountains
      	break;
		case 150:	// morze
		case 1150:
      	plansza [j] [i] = '=' + DARK_BLUE;
      	break;
		case 151:	// high mountains
		case 1151:	// high mountains
      	plansza [j] [i] = '^' + WHITE + 8192;
      	break;
		case 152:	// mountains
		case 1152:	// mountains
      	plansza [j] [i] = '^' + DARK_GRAY + 8192;
      	break;
		case 153:
		case 1153:
      	plansza [j] [i] = '=' + WHITE;
      	break;
		case 154:	// water (lake or river)
		case 1154:	// water (lake or river)
      	plansza [j] [i] = '=' + BLUE;
      	break;
		case 155:	// ice mountains
		case 1155:	// ice mountains
      	plansza [j] [i] = '^' + WHITE;
      	break;
		case 156:
		case 1156:
      	plansza [j] [i] = '.' + YELLOW;
      	break;
		case 157:
		case 1157:
      	plansza [j] [i] = '.' + WHITE;
      	break;
		case 158:
		case 1158:
      	plansza [j] [i] = '~' + YELLOW;
      	break;
		case 159:
		case 1159:
      	plansza [j] [i] = '&' + DARK_GREEN;
      	break;
		case 160:
		case 1160:
      	plansza [j] [i] = '~' + WHITE;
      	break;
		case 161:
		case 1161:
      	plansza [j] [i] = '^' + RED + 8192;
      	break;
		case 162:
		case 1162:
      	plansza [j] [i] = '^' + DARK_RED;
      	break;
		case 163:
		case 1163:
      	plansza [j] [i] = '=' + DARK_RED;
      	break;
		case 164:
		case 1164:
      	plansza [j] [i] = '.' + YELLOW;
      	break;
		case 180:
		case 1180:
      	plansza [j] [i] = 'o' + GRAY;
      	break;
		case 181:
		case 1181:
      	plansza [j] [i] = 'o' + YELLOW;
      	break;
		case 182:
		case 1182:
      	plansza [j] [i] = 'o' + CYAN;
      	break;
		case 183:
		case 1183:
      	plansza [j] [i] = 'o' + BLUE;
      	break;
		case 184:		// CLASS Corp
		case 1184:
      	plansza [j] [i] = 'o' + DARK_GRAY;
      	break;
		case 185:
		case 1185:
      	plansza [j] [i] = 'o' + DARK_GREEN;
      	break;
		case 186:
		case 1186:
      	plansza [j] [i] = 'o' + GRAY;
      	break;
		case 187:
		case 1187:
      	plansza [j] [i] = 'o' + YELLOW;
      	break;
		case 188:
		case 1188:
      	plansza [j] [i] = 'o' + DARK_GRAY;
      	break;
		case 189:
		case 1189:
      	plansza [j] [i] = 'o' + DARK_GRAY;
      	break;
		case 190:
		case 1190:
      	plansza [j] [i] = 'o' + VIOLET;
      	break;
		case 191:
		case 1191:
      	plansza [j] [i] = '*' + RED;
		case 193:		// GARDEN OF EDEN
		case 1193:
      	plansza [j] [i] = '&' + RED;
      	break;
      default:
      	plansza [j] [i] = 'X' + VIOLET;
      	break;
   }
}

void convert_area ()
{
	int x, y;

	for (x = 0; x < x_planszy; x ++)
   {
   	for (y = 0; y < y_planszy; y ++)
      {
      	if (floor_planszy [x] [y] < 1000 && (x == 0 || x == x_planszy - 1 || y == 0 || y == y_planszy - 1))
         	floor_planszy [x] [y] += 1000;

      	convert_floor (x, y);
      }
   }
}

int convert_coverer (int x_pos, int y_pos)
{
	char coverers_amount = coverers_planszy [x_pos] [y_pos] [0], i;
   int plansza_icon = -1, coverers_temp [15], color_coverer;

   color_coverer = item_icon [coverers_planszy [x_pos] [y_pos] [1]] / 256;
   color_coverer *= 256;

	for (i = 1; i < coverers_amount; i ++)
		if (item_type [coverers_planszy [x_pos] [y_pos] [i]] == 2)		// darkness
      	color_coverer = 8192;

   if (stan_planszy [x_pos] [y_pos] == 3)
		plansza_icon = item_icon [coverers_planszy [x_pos] [y_pos] [1]];
   else if (stan_planszy [x_pos] [y_pos] == 5)
		plansza_icon = item_icon [items_planszy [x_pos] [y_pos]] % 256 + color_coverer;
   else if (stan_planszy [x_pos] [y_pos] == 6)
		plansza_icon = item_icon [obstacles_planszy [x_pos] [y_pos]] % 256 + color_coverer;
   else if (stan_planszy [x_pos] [y_pos] == 7)
		plansza_icon = item_icon [items_planszy [x_pos] [y_pos]] % 256 + color_coverer;
   else if (stan_planszy [x_pos] [y_pos] >= 10)
		plansza_icon = 37 + color_coverer;

	return plansza_icon;
}

void generuj_floor (int horizontal, int vertical, char kod_floor [])
{
	int x, v = 0, y = 0, string_length = 0, floor_code;
   int kod_f;

	while ((x = kod_floor [string_length]) != '\0')
   	string_length ++;

	for (x = 0; x < string_length; x ++)
   {
			if (kod_floor [x] == '%')			// wall
				floor_code = 12;
			else if (kod_floor [x] == '*')  	// lower wall
				floor_code = 20;
			else if (kod_floor [x] == '#')  	// hard wall
				floor_code = 1012;
			else if (kod_floor [x] == '{')  	// burning wall
				floor_code = 2012;
			else if (kod_floor [x] == '}')  	// burning lower wall
				floor_code = 2020;
			else if (kod_floor [x] == '$')  	// pow. sklepu = 102
				floor_code = 102;
			else if (kod_floor [x] == '!')  	// pow. sklepu 2 = 112
				floor_code = 112;
		   else if (kod_floor [x] == '\'')	// farm
   			floor_code = 19;
		   else if (kod_floor [x] == '-')	// street
   			floor_code = _street;
		   else if (kod_floor [x] == ',')	// floor
   			floor_code = _floor;
		   else if (kod_floor [x] == ':')	// platform
   			floor_code = _platform;
		   else if (kod_floor [x] == '_')	// helipad
   			floor_code = _helipad;
		   else if (kod_floor [x] == '`')	// burning floor
   			floor_code = 2002;
		   else if (kod_floor [x] == '^')	// mountains
   			floor_code = 49;
	   	else if (kod_floor [x] == '=')	// water
	   		floor_code = 21;
	   	else if (kod_floor [x] == '~')	// sea
	   		floor_code = 24;
		   else if (kod_floor [x] == 'a')	// almond tree
   			floor_code = 10;
		   else if (kod_floor [x] == '&')	// tree
   			floor_code = 6;
		   else if (kod_floor [x] == 'o')	// olive tree
   			floor_code = 9;
 		   else if (kod_floor [x] == ';')	// grapewine
   			floor_code = 8;
      	else if (kod_floor [x] == '|')	// nowy wiersz
	      {
   	   	y ++;
      	   v = -1;
         	kod_floor [x] = '0';
	      }
   	   else if (kod_floor [x] == ' ' || kod_floor [x] == '.')		// bez zmian
      	   kod_floor [x] = '0';
         else if (kod_floor [x] >= '1' && kod_floor [x] <= '9')
         {
         	floor_code = item_floor [kod_floor [x] - 48] [1];
            add_item (item_floor [kod_floor [x] - 48] [0], horizontal + v, vertical + y, item_floor [kod_floor [x] - 48] [2]);
            item_amount [item_id] = item_floor [kod_floor [x] - 48] [3];

            if (floor_code >= 100 && floor_code < 130 && item [item_id] == 3)					  // pow. sklepu
            	item_value_material [item_id] += 50;							// unpaid
         }
         else if (kod_floor [x] >= 'A' && kod_floor [x] <= 'I')
         {
         	floor_code = monster_floor [kod_floor [x] - 64] [1];
				bestiariusz (monster_floor [kod_floor [x] - 64] [0], horizontal + v, vertical + y, monster_floor [kod_floor [x] - 64] [2]);
         }

		if (kod_floor [x] != '0' && horizontal + v < x_planszy && vertical + y < y_planszy)
		   floor_planszy [horizontal + v] [vertical + y] = floor_code;

      v ++;
   }
}

void generuj_floor_main (int horizontal, int vertical, char kod_floor [])
{
	int x, v = 0, y = 0, string_length = 0, floor_code;

	while ((x = kod_floor [string_length]) != '\0')
   	string_length ++;

	for (x = 0; x < string_length; x ++)
   {
		   if (kod_floor [x] == '~')	// morze (mapa)
   			floor_code = 150;
		   else if (kod_floor [x] == 'w')	// water - lake or river (mapa)
   			floor_code = 154;
	   	else if (kod_floor [x] == '^')	// mountains (mapa)
	   		floor_code = 152;
		   else if (kod_floor [x] == '&')	// forest (mapa)
   			floor_code = 159;
		   else if (kod_floor [x] == '.')	// pustynia (mapa)
   			floor_code = 164;
	   	else if (kod_floor [x] == '1')	// NY City
	   		floor_code = 180;
		   else if (kod_floor [x] == '2')	// Graveyard
   			floor_code = 181;
		   else if (kod_floor [x] == '3')	// Old_Remo (mapa)
   			floor_code = 182;
		   else if (kod_floor [x] == '4')	// Test plansza
   			floor_code = 200;
		   else if (kod_floor [x] == '5')	// Marina Harbour 
   			floor_code = 183;
		   else if (kod_floor [x] == '6')	// Puerto Zombico
   			floor_code = 186;
		   else if (kod_floor [x] == '7')	// Shelter Tec
   			floor_code = 185;
		   else if (kod_floor [x] == '8')	// Atlantic Accelerator
   			floor_code = 187;
      	else if (kod_floor [x] == '|')	// nowy wiersz
	      {
   	   	y ++;
      	   v = -1;
         	kod_floor [x] = '0';
	      }
   	   else if (kod_floor [x] == ' ')  	// 32 = bez zmian
      	   kod_floor [x] = '0';

		if (kod_floor [x] != '0')
		   floor_planszy [horizontal + v] [vertical + y] = floor_code;

      v ++;
   }
}
