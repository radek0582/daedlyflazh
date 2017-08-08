#ifndef __DEKLARACJE_H
#define __DEKLARACJE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include <dos.h>
#include <curses.h>
#include "names.h"
#include "desc.h"

#define _BACKSPACE		8
#define _ENTER				0xa
#define _ENTER2			-53
#define _ESC				27
#define _a					97
#define _h					104
#define _v					118

#define _A					1
#define _B					2
#define _C					3
#define _D					4
#define _E					5
#define _F					6
#define _G					7
#define _H					8
#define _I					9

#define FULL_LONG_INT	2147483647
#define X_WINDOW			60
#define Y_WINDOW			20
#define X_MAX_PL        300
#define Y_MAX_PL        100
#define X_MAX				50
#define Y_MAX				50
#define X_MATRIX			X_MAX * 2
#define Y_MATRIX			Y_MAX * 2
#define LB 					2				// left board planszy
#define UB					2				// upper board planszy
#define MAXMONSTERS		300
#define MAXITEMS			3000
#define M_BUFFOR			500
#define RESOLUTION		256				// dokladnosc generacji rownan liniowych view matrix
#define SPEED_ENV			5			// predkosc oddzialywania swiata np. przy 1000 postac bedzie glodniec 10x szybciej niz przy 100

#define _mapa				3

#define BLACK				0
#define RED					256				// 1
#define GREEN  			512   	      // 2
#define YELLOW		  		768	  			// 3
#define BLUE				1024   	   	// 4
#define MAGENTA			1280     	   // 5
#define CYAN				1536        	// 6
#define WHITE				1792    			// 7
#define GRAY				2048
#define DARK_GRAY			2304
#define DARK_RED			2560
#define DARK_GREEN		2816
#define DARK_BLUE			3072
#define BROWN				3328
#define VIOLET				3584
#define TURQUOISE			3840

#define COLOR_GRAY			8
#define COLOR_DARK_GRAY		9
#define COLOR_DARK_RED		10
#define COLOR_DARK_GREEN	11
#define COLOR_DARK_BLUE		12
#define COLOR_BROWN			13
#define COLOR_VIOLET			14
#define COLOR_OLIVE			15

#define _LIGHTNING_BALL			301

#define _RAT									1
#define _MUTATED_RAT							2
#define _MUTATED_RAT_LEADER				3
#define _RAT_KING								4
#define _SNAKE									20
#define _RED_ANT								50
#define _WOLF									60
#define _OLD_WOLF								61
#define _WILD_DOG								62
#define _JACKAL								63
#define _SPIDER								80
#define _KOBOLD								100
#define _ORC									110
#define _ISLAM_BASHER 						130
#define _TEMPLAR								131
#define _MILITIA     					  	132
#define _MILITIA_ARCHER					  	133
#define _MILITIA_CAPTAIN       			135
#define _MALE_CIVILIAN         			136
#define _FEMALE_CIVILIAN					137
#define _PRIEST               			138
#define _TEMPLAR_LEADER       			139
#define _FEMALE_CIVILIAN_OLD				140
#define _MALE_CIVILIAN_OLD         		141
#define _SOLDIER			     				142
#define _FEMALE_CITIZEN						143
#define _MALE_CITIZEN						144
#define _FEMALE_NOMAD						145
#define _MALE_NOMAD							146
#define _BANDIT	     					  	150
#define _SQUID									500
#define _SHARK									510
#define _BAYBARS								1000
#define _DOLGAR								1001
#define _CHARDASHKA							1002
#define _HASRINAXX							1003
#define _KREV									1004
#define _MOHAMMED_HALLASH					1005

#define _Bren_McGuire						1006
#define _Pleasence     						1008
#define _Flint_Westwood						1009
#define _Pinkman								1010
#define _vice_prezio   						1011
#define _Heisen								1013
#define _Bartender							1014
#define _Priest								1015
#define _Helc									1016
#define _Gina									1017
#define _Rayo									1018
#define _Father_Grigori						1020
#define _D_Morgan								1021
#define _Wise_Arse							1022
#define _Marston								1030
#define _Bum									1040

#define _Moom									1050
#define _Shades								1051
#define _CLASS_Cyborg						1052

#define _Salesman								1111
#define _Bavar									1112
#define _Doc         						1113
#define _Jack									1122

#define _zombie								200

#define _nomad_body							2146
#define _body									2900
#define _mutilated_body						2901

// head
#define _HOOD									1
#define _TURBAN								2
#define _CASQUE								3

// body
#define _RAGS  								20
#define _JACKET  								21
#define _CEVLAR								22
#define _COAT  								23
#define _M65  									24

// melee
#define _SHORT_SWORD							40
#define _DAGGER								41
#define _B_BAT 								42
#define _KNIFE									44
#define _AXE									45
#define _SHIV									46
#define _HAMMER								47
#define _SCIMITAR								48
#define _bloody_shiv							49

// ammo
#define _bullets_9mm							70
#define _granates								80
#define _357									90
#define _233									91

// sidearm
#define _2KRR  								10
#define _M119  								11
#define _6Wayne  								12

// prime
#define _NT9000								50
#define _Reza  								51
#define _16M   								52
#define _Panzor								53
#define _3GM3  								54

#define _STILETTO								43
#define _FALCHION								100
#define _SPEAR									105
#define _NIZAR_MAIL							130
#define _SHIRTS								131
#define _MILITIA_UNIFORM					132
#define _ASSASSIN_ROBE						133
#define _CRUSADER_PLATE_MAIL				134
#define _BOW									450
#define _XBOW									451
#define _SMALL_CROSSBOW						452
#define _SIEGE_BOW							453
#define _ARROW									480
#define _BOLT									495
#define _SHURIKEN								490
#define _BUCKLER								550
#define _PROTECTOR 							551
#define _LARGE_PAVISE						552
#define _STING									600
#define _KATAR									601
#define _NIZAR_SPINE							602
#define _RUNIC_TALON							603

#define _AMULET								200
#define _ALLOYS								201
#define _CRUSADER_ICON						202
#define _remains_from_droid				203
#define _MEDIKIT								940
#define _GCDC									992
#define _BAYBARS_COIN						997
#define _STATUE								1160
#define _GRAVE									1170
#define _boat_element_1						1181
#define _boat_element_2						1182
#define _boat_element_3 					1183
#define _boat_element_4						1184
#define _boat_element_5						1185
#define _boat_element_6						1186
#define _water_purifier 					1187
#define _core64_terminal					1190
#define _water_purifier_terminal			1195

#define _KEY									1300
#define _key_to_graveyard					1301
#define _key_to_president					1302
#define _key_to_Core64						1303
#define _key_to_mystuff						1304
#define _Sealed_package						1320
#define _tool_box								1321
#define _high_explosive						1330
#define _toxic_barrel						1400

#define _food									3003
#define _drug									3030

#define _WORLD							1999
#define _New_York_City				1200
#define _New_York_City_Warzone	1205
#define _Downtown						1210
#define _Downtown_Mayhem			1215
#define _Graveyard					1220
#define _Old_Remo						1230
#define _Mines							1240
#define _Marina_Harbour				1245
#define _CLASS_Corp					1250
#define _Shelter_Tec					1255
#define _Puerto_Zombico				1260
#define _Atlantic_Accelerator		1265
#define _Test							1290

#define _CLORA1						1351
#define _HASRINAXX1					1352
#define _HASRINAXX2					1353
#define _LUNE1							1300
#define _LUNE2							1301
#define _LUNE3							1302
#define _BASTION						1400
#define _OLIVES						1410
#define _PALACE_BASEMENT 			1420
#define _PALACE_1ST_FLOOR	      1430

#define _UPWARDS						1
#define _DOWNWARDS					2

#define _MELEE_SLOT				1
#define _SIDEARM_SLOT			2
#define _PRIME_SLOT				3
#define _BODY_SLOT				4

#define _POISONED					1
#define _DRUGGED					2
#define _MATTED					15
#define _DEAD						19

#define _MIGHT  			1
#define _CONDITION      2
#define _MELEE_ATTACK 	3
#define _SIDEARMS       4
#define _PRIME          5
#define _SCIENCE        6
#define _TRADE          7

#define _MALE				1
#define _FEMALE			2

#define _LIGHTNING_BALL			301

#define _grass				1
#define _floor				2
#define _platform			3
#define _water				21
#define _sea				24
#define _street			28
#define _helipad			29

#define _NORMALCURSOR 1
#define _NOCURSOR 0
#define KOLOR1 1

#define _UPPER_LEFT			7
#define _UP						8
#define _UPPER_RIGHT			9
#define _LEFT					4
#define _RIGHT					6
#define _DOWN_LEFT			1
#define _DOWN					2
#define _DOWN_RIGHT			3

#define _ARMED_NOMAD	     					151
#define _JUNKIE		     					152
#define _SCUMM			     					153
#define _HENCHMEN		     					154


void ekran_powitalny ();
void inicjuj_kolory ();
void intro ();
void achievements ();
void gain_achievement (int);
void load_achievements ();
void save_achievements ();
void count_achievement (int, int, int);
void ekran_wyboru ();
void rysuj_ekran ();
void klawiszologia ();
void instructions ();
void display_progress ();
void display_monsters ();
void make_view_matrix ();
FILE *temp00, *temp01, *temp02, *temp03, *temp10;
char view_matrix (int, int);
char view_matrix_table [X_MATRIX] [Y_MATRIX];
char visited_locations [2000];				// index'y od 0 - 1199 lokacje mapy glownej, 1200... - reszta, 0 not visited, 1 visited
int visible_monsters [MAXMONSTERS];			// potwory do wyrzucenia przy zmianie polozenia postaci
int cl_id;			// current location ID
int tl_id;			// target location ID (przy zmianie poziomu)
int current_weapon;
int view_range;

void klawisze ();
void gotoxy (int, int);
void _setcursortype (int);
void textcolor (int);
int choice (int, char [], char, char, char, char, char, int, int, char, char, char);
void rysuj_plansze ();
void put_monsters ();
void rysuj_view_range ();
void ekwipunek (int, int, char);
void generuj_ekwipunek ();
void statystyki (char);
void messages (char [], int, int);
void msg (char []);
void msg_reset ();
void inventory_message (char []);
void kropka (char);
void message_buffor ();
void oblicz_stats ();
int weapon_damage (char, int);
int weapon_hit (char, int);
void update_weapon_level (char);
void targeting (int, char, int);			// -1: gracz, monster_id: 0...
int osemka (int, int, int, int);
void reputation_change (int);
void cast (int, char, int);								// cast a spell
void create_a_ball (int, int, int, int, char, int);
void change_character_state (char);
void do_character_state (char);
void drain_health (int, char);				// typ odjecia zycia
void reset_inv_globals ();
void inventory ();
void inventory_to_backpack (int, int, char);
void backpack ();
//void wear ();
void inventory_selector (int, int, int);
void action_inventory (int);
void list_item ();
void sub_messages (int, int, int);
void enter_floor (int, int, int);
void enter_item (int, int);			// 0: do message box'a, 1: inventory
void enter_one_item (int);
void enter_monster (int, char, int, char);
void enter_player (char, int);
char* names (char);
void kopia (char*, char*);
void add_kopia (char*, char*);
void enter_hand (char, int);
void enter_age (char, int);
void enter_achievement (int, int);
void enter_choice_segregator (char, char, int, int);
void enter_ability (int, int);
void enter_material (int, int, char);
void enter_ammo (int, int);
void enter_body_part (char, int);
void write_params_prefix (int, char);
void write_params_postfix (int, char);
void display_quests ();
void display_abilities ();
void display_character ();
void gear_menu ();
void enter_char (int, int, int);
int put_char (int, int, int);
void put_char_on_cursor_shoot (int, int, int, int);
void change_color (int, int, int);
int select_a_tool ();
int select_item_to_pay ();
void use_a_tool (int);
void pay (int);
void mechanical_blade ();
void listening (int, int, int);
void select_a_wand ();
void eat ();
void zjadaj (int);
void move_area ();
void look ();
void chat ();
void trap (int, int);
void door (int, int);
void speed_star (int);
void action_coverer (int, int, int, char);
void action_floor (int, int, int);
void save ();
int load ();
void create_flag ();
void fraktal ();
void turn ();
void teleport (int, int, int);
void change_position (char);
void change_monster_position (int, int, int);
void change_location (char);
void check_map_secret ();
void ustaw_gracza ();
void ustaw_kursor ();
void refresh_view_monsters ();
void count_target_location ();
void zapisz_temp ();
void odczytaj_temp ();
void hexy (char, int);			// zamienia char'a lub int'a na 3 zanki szesnastkowe
void hexy_save (int);
int hexy_load ();
void generuj_floor (int, int, char []);
void generuj_floor_main (int, int, char []);
void generuj_world_map ();
void generuj_plansze (int);
void generuj_plansze_wilderness (int, int, int, int, int, int, int, int, int);
void generuj_dungeon (int, char, char);			// 2 - stone floor; 0 - poziom z zejsciem i wyjsciem, 1 - tylko wyjscie; 0 - losowa liczba pokoi
void generuj_water_dungeon ();
void generuj_New_York_City ();
void generuj_Downtown ();
void generuj_New_York_City_Warzone ();
void generuj_Downtown_Mayhem ();
void generuj_Graveyard ();
void generuj_Marina_Harbour ();
void generuj_Atlantic_Accelerator ();
void generuj_outlaws_village ();
void generuj_Old_Remo ();
void generuj_CLASS_Corp ();
void generuj_Shelter_Tec ();
void generuj_Test ();
void generuj_Mines ();
void generuj_potwory (int, int, int, int, int);
void generuj_potwory_extra ();
void generuj_items (int);
void generuj_triangle ();
void generuj_elipse ();
void plansza_xy (int, int, int);
void convert_floor (int, int);
void convert_area ();
int convert_coverer (int, int);
int rzut (int);
int losuj (int, int);
int losuj_2 (int, int);
int losuj_3 (int, int, int);
int losuj_4 (int, int, int, int);
int rng (int, int);
void AI ();
char monster_decision (int, int);
char find_road (int, int);
void move_monster (int, int);
char check_visibility (int, int);
char check_own_visibility (int, int);
void check_visible_monsters ();
void move_visible_monsters ();
void verify_visible_monsters ();
void action_pickup (int, int, int);
void action_drop ();
void action_item (int, int, int, char, int);			// int: -1 - gracz, 0... - potwor; int: x_pos; int: y_pos; char: 1 - drop, 2 - pickup; int - item_id
int attack (int, int, char, int);							// char: 0 - wrecz, 1 - missile
int monster_attack (int, int, int, char, int);		// char: 0 - wrecz, 1 - missile
void level_upgrade ();
void gain_experience (long int);
void monster_drop (int, int, int);
void monster_drops_item (int, int);
void aktualizuj_pole (int, int);
void put_item (int);
void remove_item (int, int, int);
void delete_item (int);
void convert_plansza (int, int);
void delete_monster (int, int, int);
void divide_items (int, int);			// przy rozdzielaniu grup tych samych item'ow
void ujmij_item (int, int);
void przedmiot_na_mapie (int, int, int, int, int);
void monster_na_mapie (int, int, int, int);
void create_item (int, int, int, int, int);			// kod (z ekwipunku); item [x]; x_pos; y_pos; amount
void take_new_item (int, int, int);
void add_item (int, int, int, int);				// add an item on map (stosowac tylko przy generacji lokacji)
void event_cost (int, int);			// liczy koszt zuzycia energii
void event_tool (int, char, int, int);
void event_blade (int, char, int, int);
void event (int, int);
void move_xy (int, int);
void event_obstacle (char, int);
char event_monster (int, int, int);
char event_throw (int, char, int, int, int, int, int, int, int);
void monster_stats (int, int, int, int, int, int, int, int, int, char);
void item_stats (int, char, int, int, char, int, char, char, char, int, int, int, int, int, char);
void make_window (char, char, int, int, char, char, int, char [], char, char);
void monster_description (int);
void item_description (int);
void area_description (int);
void clear_area (char, char, char, char);			// czysci pole o podanych wspolrzednych
char create_window (char [], char, char [], char, char [], char, char [], char, char [], char, char [], char, char [], char, char [], char, char);
char exit_location (char);
char answer ();
char luck_test (int, int, int);
void key_direction ();
int search_item (int, int);
int searsh_key (int);
int search_identical_item (int, int);
int search_identical_item_on_map (int, int, int);
int search_stairs (int, int, int);
int search_obstacle (int, int);
int find_npc (int);
void bestiariusz (int, int, int, int);
void wait (int);
void debug_info ();
void debug (int, int, int, int);
void klawisz ();
int x_planszy, y_planszy;
int h_cur, v_cur;

int h_pos, v_pos;			// pozycja gracza pozioma i pionowa
int h_pos_world, v_pos_world;
int h_pos_pl, v_pos_pl;
int strength, knowledge, toughness, mind, dexterity, perception, charisma, mana;
int health, max_health, power, max_power, air, max_air, speed, armor, GCDC, exp_lev, experience, exp_next, luck = 5;
int 	total_strength, total_knowledge, total_toughness, total_mind,
		total_dexterity, total_perception, total_charisma, total_mana,
		total_max_health, total_max_air, total_max_power, total_speed, total_armor;
int health_bonus, power_bonus;
int hit_r, hit_l, hit_m, damage_r, damage_l, damage_m, total_damage;
int action_cost = 128;
int action_type;
int autoswap = 1;				// automatyczne wymijanie neutralnych NPC
unsigned int satiation;
unsigned int weight;
int resistance [10];
unsigned long int elapsed_time;
int left_poison_turns [7];		// zaleznie od rodzaju zaaplikowanej trucizny ([0] - very lekka, [1] - lekka...)
int drugs [7];
char attacks, hand, player_gender, player_age;
char plik;
int turn_to_do;
char death;
int killing_monster_id = -2;
int kolor_floor = 512, kolor_wall = 2048;
char exit_ability;
char key;
int items_amount;
int monsters_amount;
int litera;
char kolumna;
unsigned int buffor_counter;
unsigned int turns_amount_;
unsigned int moves_env, bonus_env;
int coverers [10];
int item_floor [10] [10];
int monster_floor [10] [10];
int temp, temp1, temp2, i_y;
char chosen_hand;				// do inventory/backpack'a/oblicz_stats
int inv [20];									// temp do inventory
char wybierz_item;
int grupa_items;
char alfabet = 97;
int page_items;
int prev_id;
char enter_perm;
char play = 1;
char map_secret [20];		// 1 dla odkrytego miejsca na mapie: [0] - small cave...
int quest [128];				// 1 dla wzietego questa, 2 dla skonczonego, 3 dla "wynagrodzonego" : [0] - Lune...
char message [M_BUFFOR];
int achievement [101];
int abilities [50];			// specjalne zdolnosci
int abilities_pot [50];		// potencjal specjalnych zdolnosci
char weapon_level [30];		// poziom wyszkolenia w broniach: [1] - swords, [2] - daggers...
int weapon_marks [30];		// punkty wyszkolenia jw.
char character_state [20];
int player;
char player_name [20];
int achievement_temp [5051];
int goody_reputation [2000];
int badass_reputation [2000];

int item_id;
int monster_id, current_monster_id;
unsigned int turns_amount;		// liczba tur gry
int killed_monsters [2000];
int working_items [MAXITEMS];
int unpaid_items [MAXITEMS];
int monte_carlo [1000];
int monte_carlo_number;
unsigned int working_items_amount;
unsigned int unpaid_items_amount;
char passed_event_turns;		// ilosc tur od ostatniego zdarzenia w wilderness
char exit_list;
int znak1, znak2, znak3;

int h_pos_mon [MAXMONSTERS], v_pos_mon [MAXMONSTERS];		// pozycje potworow poziome i pionowe
char monster_char [MAXMONSTERS];		// charakter potwora od -4 do 4: -4: CE, -3: CN, -2: CG, -1: NE, 0: N, 1: NG, 2: LE, 3: LN, 4: LG
int monster [MAXMONSTERS];				// ascii potwora (w tym info o kolorze)
int monster_speed [MAXMONSTERS];
int monster_code [MAXMONSTERS];
int monster_health [MAXMONSTERS];
int monster_dv [MAXMONSTERS];
int monster_damage [MAXMONSTERS];	// damage
int monster_hit [MAXMONSTERS];		// hit bonus
int monster_exp [MAXMONSTERS];		// exp potwora
int monster_aim [MAXMONSTERS];		// tymczasowy cel ataku potwora -1 - gracz, -5 - neutralny, -6 - stoi w miejscu, >0 - inny monster
int monster_pp [MAXMONSTERS];			//
int monster_hp [MAXMONSTERS];			//
char monster_state [MAXMONSTERS] [10];
int monster_alignment [MAXMONSTERS];
int monster_left_poison [MAXMONSTERS] [7];
int monster_body [MAXMONSTERS] [10];  			// items wielded by a monster
int monster_backpack [MAXMONSTERS] [10];		// items owned by a monster
int moves [MAXMONSTERS];
int bonus [MAXMONSTERS];
int current_way [MAXMONSTERS];

int h_pos_item [MAXITEMS], v_pos_item [MAXITEMS];		// pozycje itemow poz. i pion.
char item [MAXITEMS];				// miejsce item'a: 0 - brak, 1 - backpack, 2 - potwor, 3 - mapa, 4 - inventory, 5 - obstacle, 6 - monster's backpack, 7 - coverer
int item_icon [MAXITEMS];			// kod ascii itema pokazywany na mapie
char item_group [MAXITEMS];		// grupa: 1 - helmets, 2 - necklackes...
int item_type [MAXITEMS];			// podgrupa: np. spellbook of 1 - light, 2 - darkness...
int item_dv [MAXITEMS];			   // dv/pv value
char item_hit [MAXITEMS];			// hit value
int item_dices [MAXITEMS];			// dice type
char item_dmg_bonus [MAXITEMS];		// damege bonus
char item_state [MAXITEMS];			// state: 1- broken, 2- rust, 3- broken + rust
char item_status [MAXITEMS];			// 1 = uncursed, 2 = cursed, 3 = blessed,
char item_ident [MAXITEMS];			// 0 - niezident., 1 - zident. czesciowo..., 2 - znany status (cursed...)
int item_amount [MAXITEMS];			// ilosc danego itema
int item_specials1 [MAXITEMS];				// 1 = brak mocy spec., 2 = daje odp. na ogien... (rozny format w zal. od grupy przedmiotu)
int item_specials2 [MAXITEMS];				// 1 = brak mocy spec., 2 = daje odp. na ogien... (rozny format w zal. od grupy przedmiotu)
int item_weight [MAXITEMS];				// eg.: 10027 = 100 kg 27 dag 	/ 100
int item_value_material [MAXITEMS];		// eg.: 10301 % 100 = 01 - stalowy, 103 value
int item_owner [MAXITEMS];					// -1 - gracz, 0... - monster_id
int item_body [20];							// zalozony na: [1] - glowie, [2] - szyi, [3] - body...

char stan_planszy [X_MAX_PL] [Y_MAX_PL];
int floor_planszy [X_MAX_PL] [Y_MAX_PL];
int plansza [X_MAX_PL] [Y_MAX_PL];
int mem_planszy [X_MAX_PL] [Y_MAX_PL];
int items_planszy [X_MAX_PL] [Y_MAX_PL];
int obstacles_planszy [X_MAX_PL] [Y_MAX_PL];
int coverers_planszy [X_MAX_PL] [Y_MAX_PL] [15];
int monsters_planszy [X_MAX_PL] [Y_MAX_PL];

int display_area [X_WINDOW] [Y_WINDOW];

#endif
