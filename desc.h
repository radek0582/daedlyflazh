#include "deklaracje.h"

char *quests_descriptions [] = {
/*00*/		"^nQuest.",
/*01*/		"^n Find the lost amulet.",
/*02*/      "^n Destroy all zombies in the graveyard.",
/*03*/      "^n Return to Father Grigori.",
/*04*/      "^n Deliver the package to Pink in Old Remo.",
/*05*/      "^n Return to Father Grigori with the amulet.",
/*06*/      "^n Solve the problem between Bob and Carl.",
/*07*/		"^n Help Carl with fixing the altar.",
/*08*/		"^n Return to Heisen.",
/*09*/		"^n Return to Flint Westwood.",
/*10*/		"^n Bring Bob, bartender some alloys.",
/*11*/		"^n Talk to Carl, the priest.",
/*12*/		"^n Slay the rat king.",
/*13*/		"^n Heal brother of Rayo.",
/*14*/		"^n Talk to Flint Westwood.",
/*15*/		"^n Put D'Morgan on the ground.",
/*16*/		"^n Talk to Helc.",
/*17*/		"^n Go to Old Remo and talk to Flint Westwood.",
/*18*/		"^n Fix water purifer in SHELTER TEC.",
/*19*/		"^n Return to Brenn McGuire."
/*20*/,		"^n Destroy core64 terminal."
/*21*/,		"^n Return to Pleasence, president of NYC."
/*22*/,		"^n Slay the president of NYC."
/*23*/,		"^n Fix the core64 terminal."
/*24*/,		"^n Talk to Shades in CLASS Corp."
/*25*/,		"^n Clean Puerto Zombico and find insane soldier."
/*26*/,		"^n Talk to Marston."
/*27*/,		"^n Talk to Bum."
/*28*/,		"^n Talk to Boolfrog about murders."
/*29*/,		"^n Retrun and talk to Bum."
/*30*/,		"^n Decide who is guilty for murder Oil Rig crew. Talk with father Grigori."
/*31*/,		"^n Bring father Grigori the proof of murder."
/*32*/,		"^n Kill Bum, who murdered the crew in AA."
/*33*/,		"^n Return and talk with Shades."
};

char *quests_names [] = {
/*00*/		"^n^07LOST CRUCIFIX."
/*01*/,		"^n^07CLEANSING."
/*02*/,		"^n^07TRANSACTION."
/*03*/,		"^n^07SOLVE FRIENDS ISSUE."
/*04*/,		"^n^07THE BROKEN ALTAR."
/*05*/,		"^n^07QUEST."
/*06*/,		"^n^07KILL RAT KING."
/*07*/,		"^n^07REMAINS UPON CROSS."
/*08*/,		"^n^07HUNT DOWN SERIAL KILLER."
/*09*/,		"^n^07WATER SUPPLY PROBLEM."
/*10*/,		"^n^07ANNIHILATE MACHINES."
/*11*/,		"^n^07BROKEN MAINFRAME."
/*12*/,		"^n^07NEW YORK CYBERDYNE."
/*13*/,		"^n^07REDEMPTION."
/*14*/,		"^n^07WHAT HAPPENS HERE?"
/*15*/,		"^n^07HUMAN OR MACHINE?"
/*16*/,		"^n^07BAD DOG HAS TO GO."
};

char *monsters_descriptions [] = {
/*00*/								" No infromation about this monster."
/*01 BAYBARS*/,					" A well-built man in his fifties. Clean-shaved and grizzled with some wrinkles around his focused and sagacious eyes. "
										"He slowly strolls down the streets of the village enjoying another peaceful day. "
										"Don't let his kind-hearted look fool you – he may be an old man but he can move when he has to. "
                              "In this case with age came experience - he's certainly seen and conquered in the name of Allah more than you, your friends AND "
                              "your family combined. This desert fox always has an ace up his sleeve."
/*02 MILITIA*/,					" A member of the local population enlisted as a militiaman for maintaining order. "
										"Dressed in standard-issue leather armour and helmet. They carry different weapons from swords to spears. "
        			 			   	"Not especially well-trained, not really courageous, but still a formidable force when in large numbers."
/*03 FEM_CIVILIAN*/,				" Can't really tell if she's beautiful or terribly ugly since she's almost completely covered by tunic and hijab. "
										"She avoids eye contact with you and tries to get out of your way."
/*04 FEM_CIVILIAN_OLD*/,		" Middle-age, wrinkled woman who won't be intimidated by your looks. She scans you with a mixture of curiosity and contempt."
/*05 MALE_CIVILIAN*/, 			" Young, slender and active man in his early twenties. Stares at your armour and weapons with great envy wishing he could some day embark on a trip full of adventures and treasures, "
										"just like in the tales his granddad used to tell him."
/*06 MALE_CIVILIAN_OLD*/, 		" Scorched by sun and tired with life, this man enjoys spending afternoons sipping tea and discussing latest developments in politics."
/*07 MILITIA_CAPTAIN*/,			" Being a militia captain in such a place is not easy and it left a mark on Sharif's appearance. "
										"Bags under the eyes, tired look and slightly humped back all prove how many hardships this man endured during his lifetime. "
                              "Short height and skinny body  don't really make him look terribly intimidating but for some strange reason all his militiamen and village inhabitants treat him with great respect, "
                              "as if there was something more to this man than it's visible at first glance."
/*08 BANDIT*/,						" Masked man carrying a long and sharp knife that could slice you in half. "
										"Watery eyes that show absolutely no emotion try to judge what would be the most painful way to slaughter you. Either run away or prepare for a fight to the death for these men are serious about what they do. "
/*09 WILD_DOG*/,					" The poor creature must have been starving recently cause it looks terrible. Although it seems that this wild dog is going to change it's dietary habits and the first dish on his list is YOU. Served with olives, if possible, bon appetit. "
/*10 HEISEN*/,						" Eldery bald,man. Dressed entirely in black.Jacket, hat, sunglasses and uniforms reminiscent of the old Memphis Blues musicians. It doesn't look that his health was in order, stubborn cough already at first sight you will notice."
/*11 Bren*/,						" \"Soldierish\" looking guy. Possible ex military. He has a lit cigarette in his mouth that only extinguishes when he dies. He's wielding the Assault Rifle, probably to complement his back story."
/*12 Pleasence*/,	 				" A swarthy man, slightly concerned. Dressed in a black suit season he looks classy - you can see that even today, is a gentelman. Deep wrinkles, complete bald and fairly \"hard\" glasses, lead to believe that man is in his middle ages."
/*13 Rayo*/,						" Short, grey hair guest, with little smile on the face. He's got tiny black eyes... well, this is not heralds anything good."
/*14 rat king*/, 					" Giant rat, looking vicious. Possible it's for rabies or radiation influence. Sharp teeth and claws seems major treat. Thick looking skin and fur, looks like great cover."
/*15 Pink*/,						" Mid twenty, student looking guy. Black jacket and red tee, compose with black \"tribal\" tattoo on left hand. Requesting behavior, probably dependent on drugs. At first the plan, bloody eyeballs and neurological tricks."
/*16 Bum*/,							" A hobo is a term which is often applied to a migratory worker or homeless vagabond, often penniless. The term originated in the Western (probably Northwestern) United States during the last decade of the 19th century. Unlike 'tramps', who work only when they are forced to, and 'bums', who do not work at all, 'hobos' are workers who wander. This man looks like textbook example of \"hobo\"."
};

char *items_descriptions [] = {
/*00*/ 								"-"
/*01*/ ,								"-"
/*02 info*/ ,						"Striking distance: 1^nBase damage: 4"
/*03 desc*/ ,	               "It frequently used in Amiericas favourite game."
/*04 info*/ ,						"Striking distance: 3^nBase damage: 2(x3)=6^nFire 3 rounds burst.^nContains 24 rounds magazine.^nAmmo: 9mm"
/*05 desc*/ ,						"Some say this silenced personal defence weapon is one of favorite among this game developers. Fully automatic descrete gun have total lack of power but recompensate in high mobility, silencer and massive rate of fire."
/*06 info*/ ,						"Striking distance: 5^nBase damage: 20^n^nGranate luncher, single shoot.^nAmmo: granate"
/*07 desc*/ ,						"Masive damage but lack of mobility."
/*08 info*/ ,						"Contains 20 rounds mag.^n2 rounds burts.^nStriking distance: 6^nBase damage: 4 (x2) = 8^nAmmo: 9mm"
/*09 desc*/ ,						"Russian \"Snaiperskaya Special\" fullautomatic silenced sniper rifle. Giving his operator extreme stealth at the cost of accuracy and damage."
/*10 info*/ ,						"Contains 30 rounds mag.^n3 round burst.^nStriking distance: 5^nBase damage : 4 (x3) = 12^nAmmo: .233"
/*11 desc*/ ,						"Modern America most belowed rifle. This gun wipe out comunists from Nam."
/*12 info*/ ,						"Spining drum (magazine) contains 15 rounds. Single shoot.^nStriking distance = 3^nBase damage : 10^nAmmo: gauge shells"
/*13 desc*/ ,						"Semi automatic shotgun ideal in tight spaces. Limited range but exceptional deadly power."
/*14 info*/ ,						"Contains 100 round belt. 10 round burst.^nStriking distance = 4^nBase damage: 1 (x10) = 10^nAmmo: 7,63mm"
/*15 desc*/ ,						"They say, \"there was a time when Nazi invades Poland...\". This German lead spitting hellfire beast, puts incredible amount of rounds on target."
/*16 info*/ ,						"Contains 7 rounds magazine^nStriking distance = 3^nBase damage : 4^nAmmo: 9mm"
/*17 desc*/ ,						"Favorite sidearm among taekwondo monks, like Steven Seegul. This semi automatic pistol fire lethal doze of lead into opponent."
/*18 info*/ ,						"Noble 6 rounds drum.^nStriking distance = 3^nBase damage : 3^nAmmo: .357"
/*19 desc*/ ,						"Magnum revolver with notable firepower. Old \"Wild West\" design slightly reminds times when sherrifs rulez the World."
/*20 info*/ ,						"Striking distance = 1^nBase damage : 6"
/*21 desc*/ ,						"Axes are made of copper, bronze, iron or steel. They generally consist of an axe head blade with a handle."
/*22 info*/ ,						"Striking distance = 1^nBase damage : 2"
/*23 desc*/ ,						"Home made knife, with formed blade from alloys and handle made from duck tape. It's very popular toy among prisoners all over the World."
/*24 info*/ ,						"Striking distance = 1^nBase damage : 5"
/*25 desc*/ ,						"This tool has only one purpose. Deliver impact to any object. Mostly uses for fitting parts, driving nails...or crush peoples skulls."
/*26 info*/ ,						"A torn inferior piece of textile. Torso protection made of jacket remains, wires and corrupted alloys. Delivers minor protection from any kind of interact."
/*27 desc*/ ,						"Designed for protective use. Heavier, thicker, and often equipped with armor, thus becoming a very practical item of clothing regardless of the symbolism invested in them by popular culture. Leather surface covers by fractures and flaws."
/*28 info*/ ,						"Torso wear vest, thats absorb firearm and explosions impact. Regalias and tags on it, reminds America Army. This personal armor inculde metal or ceramic plates, several pockets and fiber components."
/*29 desc*/ ,						"Protects from cold, dust and acid rains. Brown one like this one, were using by \"Independents individuals\", who could stand that all humans need to (or should) be under the control of one 'great' government, and they fought till last breath against republic authorities. For some rednecks still may affect, as red flag to a bull."
/*30 info*/ ,						"A military coat designed for and used in Vietnam War. Later used in another conflicts and wars too in many army resorts as well it was very popular and legendary in ciliv world. Made from cotton and nylon in 50/50 proportions in olive colour. Windproof and warm protects its user well. Light and comfortable."
};

