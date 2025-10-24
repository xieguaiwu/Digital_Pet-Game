//#include "basicfunc.h"
#include "body.h"
#include "cooking.h"
#include "event_print.h"

unsigned int days = 1;
bool died = false;

unsigned int turns = 1;

string cheating;
const bool cheatable = false;
unsigned int Mopluse;
bool Bband = false; //have random event no.4 been finished or not

//random event no.2
bool cheat = false;
bool loser = false;
bool invest = false; //invest or not
unsigned int Iinvest;//money invested
unsigned int IINVEST;
unsigned int Dinvest;//days to wait
float Einvest;//rate of profit
//prices
const unsigned int price_mouse = 90, price_slipper = 20, price_lone = 10, price_heartsaver = 10000;
const unsigned int price_pbutter = 35, price_mbutter = 50, price_sug = 8, price_sod = 9, price_wat = 0, price_flo = 6;
//ingredient you have
unsigned int storage[5];

//ingredient added
unsigned int storageAdding[5];

unsigned int Cid = 0; //note id
vector<string> backpackmeal;//name
vector<int> backpackcalr;//energy
vector<int> backpackspend;//cost, will be used in latter versions
vector<int> backpackall;//total amount
vector<float> backpackeffect;//effect

void interact();

void cook_random_notice() {
	int Rcook = 1 + rand() % (3);
	if (Rcook == 1) {
		cout << "You throw a bunch of inorganic substance (except for the flour) into the pot. Few hours later, you find yourself very tasty. When cooking yourself, you find out that you have already cooked...";
	}
	if (Rcook == 2) {
		cout << "You carefully throw a bunch of materials into the pot, and cook them with strange approaches. A few minutes later, you find the turner very tasty. When trying to chew the turner, you find yourself successfully cooked...";
	}
	if (Rcook == 3) {
		cout << "After throwing a bunch of disgusting inorganic substance, you are chocked by the smoke for two whole hours, and you find yourself totally cooked. In the mean time, you successfully invented...";
	}
}

int cook(unsigned int Psug, unsigned int Psul, unsigned int Psod, unsigned int Pwat, unsigned int Pflo, bool CookOrCal = 0) {
	Msug = Psug;
	Msul = Psul;
	Msod = Psod;
	Mwat = Pwat;
	Mflo = Pflo;
	Camount = Psug + Psul + Psod + Pwat + Pflo;
	if (!CookOrCal) {
		if (Psug == 0 && Psul == 0 && Psod == 0 && Pwat == 0 && Pflo == 0) {
			cout << "After precisely controlling the invisible fire, consistly modifying the temperature of the non-existent frying pan, and the combination of the imaginary delicate seasonings, you successfully made a dish of...";
			Ncook = air;
			return Ncook;
		} else {
			cook_random_notice();
		}
	} else {
		Mcalr = Psug * 400;//sugar per gram: 400 kcal
		if (Pwat > Pflo)Mcalr = Mcalr + Pflo * 300;//wet flour per gram: 300 kcal
		else Mcalr = Mcalr + Pwat * 2 + (Pflo - Pwat) * 366;//dry flour per gram: 366 kcal
		return Mcalr;
	}
	return -1;
}

bool Vacheve = false;
void notice() {
	cout << "\nPRESS 'Q' TO QUIT\nPRESS 'F' TO FEED YOUR PET\nPRESS 'I' TO INTERACT WITH YOUR PET\nPRESS 'C' TO CHECK YOUR PET'S STATUS\n";
	cout << "PRESS 'S' TO CLEAR THE SCREEN\nPRESS 'M' TO [PURCHASE], [APPLY FOR LOAN] OR [COOK]\nPRESS 'B' TO CHECK THE [COOKING INGREDIENT] YOU ALREADY HAD\n";
	cout << "PRESS 'O' TO CHECK THE DISHES YOU ALREADY COOKED\n";
#ifdef _WIN32
	cout << "PRESS 'X' TO RESET THE THEME COLOR\n";
#endif
	//cout << "PRESS '?' TO CHECK THE INSTRUCTIONS\n";
	if (invest) {
		cout << "PRESS 'V' TO CHECK THE [STATUS OF INVESTMENT]\n";
		Vacheve = true;
	}
	cout << "There are 8 times to press the key.\nYou have " << 8 + 1 - turns << " times left\n";
}

//cooking functions
void Cpushback(string bloodyname, int bloodycalr, int bloodyspend, int bloodyall, float bloodyeffect) {//storage function
	backpackmeal.push_back(bloodyname);
	backpackcalr.push_back(bloodycalr);
	backpackspend.push_back(bloodyspend);
	backpackall.push_back(bloodyall);
	backpackeffect.push_back(bloodyeffect);
	++Cid;
}

unsigned int Crow;//for circulation
void Cclean() {//empty
	Crow = 1;
	while (1) {
		if (Crow >= Cid)break; //backpackmeal starts from 0
		backpackmeal[Crow - 1] = "";
		++Crow;
	}
	Cid = 0;
}

void Cdrop(int IDI) {//IDI=id of the dropped item
	backpackmeal[IDI] = "";
	Cid = Cid - 1;
	Crow = IDI;
	while (1) {
		if (Crow >= Cid)break;
		backpackmeal[Crow] = backpackmeal[Crow + 1];
		backpackcalr[Crow] = backpackcalr[Crow + 1];
		backpackspend[Crow] = backpackspend[Crow + 1];
		backpackall[Crow] = backpackall[Crow];
		++Crow;
	}
}

void Cfour() {
	unsigned char Cfour_rounder;
	for (Cfour_rounder = 0; Cfour_rounder < 5; Cfour_rounder ++) {
		if (storage[Cfour_rounder] <= 0)storage[Cfour_rounder] = 0;
	}
}

bool Jcook = false, wrongtype;
void handle_putting() {
	wrongtype = false;
	cout << "(You can input 0 to quit this menu)\n";

	unsigned char rounder = 0;
	while (!wrongtype) {
		unsigned int inter_trans;
		if (rounder >= 5) break;
		cout << "How much ";
		if (rounder == 0)cout << "sugar";
		else if (rounder == 1)cout << "salt";
		else if (rounder == 2)cout << "sodium bicarbonate";
		else if (rounder == 3)cout << "water";
		else if (rounder == 4)cout << "flour";
		cout << " do you want to put in? Input the number of ";
		if (rounder == 3)cout << "milliliter";
		else cout << "grams";
		cout << " :";

		cin >> inter_trans;
		badint();
		if (isbadint || inter_trans <= 0) {
			wrongtype = true;
		} else if (!isbadint && (storageAdding[rounder] < 0 || storageAdding[rounder] > storage[rounder])) {
			cout << "You don't have any!\n";
		} else if (!isbadint && (storageAdding[rounder] > 0 && storageAdding[rounder] < storage[rounder])) {
			storage[rounder] = storage[rounder] - storageAdding[rounder];
			break;
		}
		++rounder;
	}

	cook(storageAdding[0], storageAdding[1], storageAdding[2], storageAdding[3], storageAdding[4], ck);
	Meal = Tmeal[meal_tas()] + meal[meal_nam()];
	cout << Meal << "!\n";
	calr = cook(storageAdding[0], storageAdding[1], storageAdding[2], storageAdding[3], storageAdding[4], cr);
	cout << "The energy of this dish is " << calr << " calories!\n";
	Cpushback(Meal, calr, storageAdding[0] * 8 + storageAdding[1] * 13 + storageAdding[2] * 9, meal_all(), meal_effect()); //the price of salt is $ 6~21, take 13 as the average value
}

void Cincook() {
	colorc(blue);
	cout << "You have " << storage[0] << " grams of sugar\nYou have " << storage[1] << " grams of salt\nYou have " << storage[2] << " grams of soda\nYou have " << storage[3] << " milliliter of water (1000 millilitter max)\nYou have " << storage[4] << " grams of flour\n";
	colorc(white);
	pausers::pause();
	cout << "Keep cooking? (Press Y to continue, press N to quit this menu)\n";
	while (1) {
		key = getch();
		if (yes) {
			Jcook = false;
			break;
		}
		if (no) {
			Jcook = true;
			break;
		}
	}
	if (!Jcook) {
		handle_putting();
	} else {
		Jcook = false;
	}
	hyphen(4);
}

//random event functions
void r1() {		//random event no.1
	randomnum = r_events(3, 35, 0);		//brings back $ 0~35
	if (randomnum != 0) {
		cout << "\n This day, you find that your pet disappered. Few hours later, your pet brings you back $" << randomnum << "!\nMoney increase!\n";
		money = money + randomnum;
		pausers::pause();
	}
}

void handle_investment_deposite() {
	cout << "You sign your name.\n";
	invest = true;
	while (1) {
		cout << "Input the money you want to invest - ";
		notices::money_have();
		cin >> Iinvest;
		badint();
		if (Iinvest > money)cout << "You don't have that much of money! All you have is $ " << money << "!\n\n";
		else if (!isbadint && Iinvest > 0) {
			break;
		} else if (!isbadint && (Iinvest == 0)) {
			cout << "You give up the investment when it is by a hair!\n";
			break;
		} else if (!isbadint && (Iinvest < 0)) {
			cout << "Failed to invest, please reenter!\n\n";
		}
	}
	if (Iinvest != 0) {
		cout << "You invest $ " << Iinvest << ".\n";
		if (Iinvest == money) {
			cout << "Your pet is very pleased when seeing you invested all your money.\n";
			notices::hap_plus(2);
			notices::sad_minus(3);
			hap += 2;
			sad -= 3;
		}
		money = money - Iinvest;
		IINVEST = Iinvest;
		Dinvest = r_events(3, 2, 1) + days;
		invest = true;
	} else {
		cout << "Your pet is looking at you as if you are a retard.\n";
		invest = false;
	}

}

void r2() {		//random event no.2: venture capital
	notices::your_pet();
	cout << "walks to you with a paper, which said:\nVENTURE INVESTMENT\nInvestor:" << name << "\nVoucher: You\nSignature:________\n";
	pausers::sure();
	key = getch();
	switch (key) {
	case 'Y':
	case 'y':
		handle_investment_deposite();
		break;
	case 'N':
	case 'n':
		invest = false;
		cout << "Your pet is looking at you as if you are a retard.\n";
		break;
	}
	cout << "\n\n";
}

bool Phouse = false; //having a house or not
bool Pmouse = false; //having a mouse or not
int Pmouse_plus;//the happiness increased by mouse
void handle_buy_10_dollars() {
	if (!(money < 10)) {
		money = money - 10;
		cout << "You spent $ 10 to but $ " << randomnum << ". ";
		if (randomnum > 10) {
			cout << "What a silly great deal!\n";
		}
		if (randomnum == 10) {
			cout << "What a balanced profit!\n";
		}
		if (randomnum < 10) {
			cout << "What a foolish decision!\n";
		}
		money += randomnum;
	} else {
		notices::money_not();
	}
}

void handle_opening_door() {
	cout << "You open the door, just to realize that";
	randomnum = r_events(114514, 5, 1);
	if (randomnum == 2) {
		cout << "your pet has already eated the window and entered the house.\n";
		poo = true;
	} else {
		cout << "your pet has already entered the house.\n";
	}
}

void handle_eating_door() {
	cout << "You pretend that your can't hear " << name << "'s knocking, so your pet eats up the door!\nYour pet feels refreshed.\n";
	notices::hap_plus(2);
	notices::sad_minus(3);
	hap += 2;
	sad -= 3;
	poo = true;

}

void r3() { //random event no.3
	cout << "Your pet runs out of the house.\nFew hours later, your pet " << name << " starts to knock on the door.\n";
	cout << "Open the door?\n";
	pausers::sure();
	key = getch();
	switch (key) {
	case 'Y':
	case 'y':
		handle_opening_door();
		break;
	case 'N':
	case 'n':
		handle_eating_door();
		break;
	}
	cout << "\n\n";
	cout << name << " showed you few items that";
	refer(nomin);
	cout << "found:\n";
	randomnum = r_events(250, 5, 1);
	if (randomnum == 1 || randomnum == 2) {
		cout << "A) ";
		randomnum = r_events(45, 50, 1);
		cout << "$ " << randomnum << " Price: $ 10\nB) Don't buy anything\n";
		key = getch();
		switch (key) {
		case 'A':
		case 'a':
			handle_buy_10_dollars();
			break;
		case 'B':
		case 'b':
			break;
		}
	}

	if (randomnum == 3 || randomnum == 4) {
		cout << "A) Toy mouse (happiness [+1]~[+5] each day) $ " << price_mouse << "\nB) Slipper (don't you want to buy a house for your pet?) $ " << price_slipper << "\n";
		cout << "C) Heart saver capsule $ " << price_heartsaver << "\nD) Don't buy anything\n";
	}
	while (1) {
		key = getch();
		if (key == 'A' || key == 'a') {
			if (!(money < 90) && !Pmouse) {
				money = money - 90;
				cout << "You have bought the toy mouse!\n";
				Pmouse = true;
			} else if (!(money < 90) && Pmouse) {
				cout << "Sorry, but your pet already have one!\n";
			} else {
				notices::money_not();
			}
			break;
		} else if (key == 'B' || key == 'b') {
			if (!(money < 20) && !Phouse) {
				money = money - 20;
				cout << "You have bought the slipper!\n";
				Phouse = true;
			} else if (!(money < 20) && Phouse) {
				cout << "Sorry, but your pet already have one!\n";
			} else {
				notices::money_not();
			}
			break;
		} else if (key == 'C' || key == 'c') {
			if (!(money < 10000)) {
				cout << "Sorry, buy you don't have enough money! Continue? (Press Y to continue and press N to quit)\n";
				money = money - 10000;
				while (1) {
					key = getch();
					if (yes) {
						cout << "MONSTER!\nHappiness = 0! Sadness maximumizes!\n";
						hap = 0;
						sad = max_sad;
						break;
					} else if (no) {
						cout << "You are scamed!\n";
						break;
					}
				}
			} else {
				notices::money_not();
			}
			break;
		} else if (key == 'D' || key == 'd') {
			break;
		}
	}

	if (randomnum == 5) {
		cout << "A) Lonliness (buy one when you are on your own) $ " << price_lone << "\nB) Don't buy anything\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				if (!(money < 10)) {
					money = money - 10;
					cout << "You have bought... lonliness...\n";
				} else {
					notices::money_not();
				}
				break;
			} else if (key == 'B' || key == 'b') {
				break;
			}
		}
	}
	hyphen(4);
}

int Bturns = 1;
int Bdays = 1;
bool back = false;
bool BFS = false; //BFS=BIG FUCKING STAR
int Msenting;
void Bback() {
	back = true;
	cout << "\"21st century schizoid pet!\"You see your pet is holding a electric guitar (being overwhelmed under the guitar), and the spotlight shines on its eyes.\n";
	pausers::pause();
	cout << "Tears run out your eyes. Few weeks later, your pet knocks on the door again, and";
	refer(nomin);
	cout << "tells you (don't ask me how) that this performance has made a great success.\n";
	randomnum = r_events(134, 5, 1);
	if (randomnum == 5) {
		BFS = true;
		randomnum = r_events(214, 3000, 200);
		cout << "Your pet becomes the next Michael Jackson in the world - in fact, hardly anybody still remembers Michael Jackson now. There are a lot of crazy fans come to send you money everyday after that performance, but your pet mysteriously refuses (don't ask me how) to go back to the business.\n";
	} else {
		randomnum = r_events(298, 2000, 100);
	}
	money = money + randomnum;
	cout << "The performance earns you $ " << randomnum << " in total. In order to show thankfulness, your pet hands you all the money.\n";
	pausers::pause();
	cout << "And so, the both of you come back to your ordinary life.\n";
	hyphen(4);
}

void Binteract() { //a function for random event no.4
	if (key == 'T' || key == 't') {
		cout << "You open the YV.\n";
		pausers::pausers::pause(1);
		randomnum = r_events(1874298, 2, 1);
		if (randomnum == 1)Btv1();
		else if (randomnum == 2)Btv2();
		else if (randomnum == 3)Btv3();
		else if (randomnum == 4)Btv4();
		randomnum = r_events(82734, 4, 1);
		if (randomnum == 2) {
			cout << "You are switching channels, and suddenly, you see...\n\nYour pet!\n";
			pausers::pause();
			Bback();
			return;
		} else {
			cout << "You keep changing the channels, but can't find any information about your pet...\n";
			pausers::pausers::pause(1);
		}
	} else {
		hyphen(3);
		cout << "\n";
		notices::choose_again();
		cout << "\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch();
		Binteract();
	}
}

void band_days() {	//a function for random event no.4
	hyphen(2);
	cout << "Day " << Bdays << "\n";
	while (1) {
		if (Bturns == 2)break;
		cout << "\n";
		notices::choose_again();
		cout << "\nPlease choose again!\nPress 't' to watch TV\nThere are 1 chance to watch TV everyday\nYou have " << 1 + 1 - Bturns << " time left\n";
		key = getch();
		Binteract();
		if (back)break;
		++Bturns;
	}
	++Bdays;
	Bturns = 1;
}

void r4() {//random event no.4: you pet's prog rock band
	Bband = true;
	cout << "For the past few days, your pet has been listening to some strange rock music.\nYou often hear some words like 'rape' from " << name << "'s mouse (don't ask me how)\n";
	pausers::pause();
	cout << "One day, your pet told you through a unimaginable way that";
	refer(nomin);
	cout << "is going to start a progressive rock band.\nBecause you have been such a good owner, this band won't cost you any money.\n";
	pausers::pause();
	eat = false;
	poo = false;
	cout << "Before";
	refer(nomin);
	cout << "left, you feed your pet for the last time, and let";
	refer(nomin);
	cout << "defecates for the last time.\nYou witness";
	refer(posses);
	cout << "leave...\n";
	pausers::pause();
	hyphen(4);
	while (1) {
		band_days();
		if (back)break;
	}
}

void r5() {//random event no.5
	randomnum = r_events(123, 5, 1);
	cout << "\nToday, you can't find your pet anywhere. Few hours later, your pet brings you back ";
	if (randomnum == 1) { //sugar
		randomnum = r_events(1234, 35, 1);
		cout << randomnum << " grams of sugar!\n";
		storage[0] += randomnum;
	} else if (randomnum == 2) { //salt
		randomnum = r_events(1234, 35, 1);
		cout << randomnum << " grams of salt!\n";
		storage[1] += randomnum;
	} else if (randomnum == 3) { //soda
		randomnum = r_events(1234, 35, 1);
		cout << randomnum << " grams of soda!\n";
		storage[2] += randomnum;
	} else if (randomnum == 4) { //water
		randomnum = r_events(1234, 35, 1);
		cout << randomnum << " milliliters of water!\n";
		if (storage[3] + randomnum <= 1000)storage[3] += randomnum;
	} else if (randomnum == 5) { //flour
		randomnum = r_events(1234, 35, 1);
		cout << randomnum << " grams of flour!\n";
		storage[4] += randomnum;
	}
	pausers::pause();
}

void r_e() {
	if (days >= 1) {
		randomnum = r_events();
		if (!(randomnum > events)) {
			if (randomnum == 1) r1();
			else if (randomnum == 2) {
				if (!invest && money > 0)r2();
			} else if (randomnum == 3) r3();
			else if (randomnum == 4) {
				if (!Bband)r4();
			} else if (randomnum == 5) r5();
		}
	}
}

void death() {
	hyphen();
	cout << "Your pet " << name << " had been through a life of " << age << " years, and ";
	refer(nomin);
	cout << "had been through " << days << " days.\n";
	cout << "When " << name << " was going to die, ";
	if (poo) {
		refer(nomin);
		cout << "still wants to defecate.\n";
	}
	if (eat) {
		refer(nomin);
		cout << "is still very hungry.\n";
	}
	cout << "When";
	refer(nomin);
	cout << "was going to die, " << name << " ";
	if (sad >= 38 && sad < 42 && hap < 50) {
		cout << "was a bit sad.\n";
	}
	if (sad >= 42 && hap < 50) {
		cout << "was very depressed.\n";
	}
	if (hap >= 50 && hap < 76 && sad < 38) {
		cout << "was quite happy.\n";
	}
	if (hap >= 76 && sad < 38) {
		cout << "was very happy.\n";
	}
	if (hap >= 50 && sad >= 38) {
		cout << "was confused.\n";
	}
	died = true;
	pausers::pausers::pause(1);
}

//emotion function
void e_poo() {
	if (w_poo > 10) {
		w_poo == 10;
	} else {
		if (w_poo > 5) {
			if (w_poo < 8) {
				hap -= 5;
				sad += 3;
			}
			if (w_poo >= 8) {
				hap -= 8;
				sad += 6;
			}
		}
	}
}

void e_eat() {
	if (w_eat > 5) {
		w_eat == 5;
	} else {
		if (w_eat > 2) {
			if (w_eat < 4) {
				hap -= 4;
				sad += 5;
			}
			if (w_eat >= 4) {
				hap -= 8;
				sad += 7;
			}
		}
	}
}

void e_age() {
	if (days != 0 && days % 10 == 0) {
		++age;
		notices::your_pet();
		cout << "is 1 year older!\n";
	}
}

void e_sad() {
	if (sad < 0)sad = 0;
	if (sad > max_sad)sad = max_sad;
	if (!(sad >= max_sad)) {
		if (sad > 25) {
			if (sad < 38) {
				sad += 3;
				hap = hap - 6;
			}
			if (sad >= 38) {
				sad += 6;
				hap = hap - 10;
			}
		}
	} else {
		notices::your_pet();
		cout << "is so depressed that";
		refer(nomin);
		cout << "committed suicide.\n";
		death();
	}
}

bool Lifespanup_turns = false; //lifespan increased within a single turn or not
int Lifespanhap;//the hapiness needed to increase lifespan is initially between 60~85
void e_hap() {
	if (hap < 0)hap = 0;
	if (hap > max_hap)hap = max_hap;
	if (!(hap >= max_hap)) {
		if (hap > 50 && hap < 76) {
			hap += 3;
			sad = sad - 3;
		} else if (hap >= 76) {
			hap += 4;
			sad = sad - 5;
			if (hap >= Lifespanhap && sad <= 15) { //condition to increase lifespan
				if ((turns == 2 || turns == 4 || turns == 6 || turns == 8) && !Lifespanup_turns) {
					cout << "Your pet's lifespan increace by 1 day!\n";
					++lifespan;
					Lifespanup_turns = true;
				} else {
					Lifespanup_turns = false;
				}
			}
		}
	} else {
		sad = sad - 5;
	}
}

int cheatmoney;
int uglyprice;//random price
int gs;//grams to but
void M_notice() {
	if (gs < 0) {
		cout << "Please input again!\n";
	} else if (gs == 0) {
		cout << "You give up to buy.\n";
	}
}

void M_cok() {  //buying cooking ingredients
	while (1) {
		notices::money_have();
		cout << "Cooking ingredients:\nA) Sugar $ " << price_sug << " per gram\nB) Salt $ 6~12 per gram\nC) Soda $ " << price_sod << " per gram\n";
		cout << "D) Water $ " << price_wat << " per milliliter\nE) Flour $ " << price_flo << " per gram\nF.Air $ 20~900 per square meter\nG.Quit this menu\n";
		key = getch();
		if (key == 'A' || key == 'a') {
			uglyprice = 8;
			while (1) {
				cout << "Input the number of grams you want to buy:";
				cin >> gs;
				badint();
				if (isbadint)gs = 0;
				M_notice();
				if (gs == 0) {
					pausers::pause();
					turns--;
					break;
				} else if (money >= gs * uglyprice) {
					cout << "You have successfully bought " << gs << " grams of sugar!\n";
					money = money - gs * uglyprice;
					storage[0] += gs;
					pausers::pause();
					break;
				} else {
					notices::money_not();
					pausers::pause();
					break;

				}
			}
			clear_screen();
		} else if (key == 'B' || key == 'b') {
			uglyprice = r_events(123, 21 - 6, 6);
			cout << "Price: $ " << uglyprice << "\n";
			notices::still_buy();
			while (1) {
				key = getch();
				if (yes) {
					while (1) {
						cout << "Input the number of grams you want to buy:";
						cin >> gs;
						badint();
						if (isbadint)gs = 0;
						M_notice();
						if (gs == 0) {
							pausers::pause();
							turns--;
							break;
						} else {
							if (money >= gs * uglyprice) {
								cout << "You have successfully bought " << gs << " grams of salt!\n";
								money = money - gs * uglyprice;
								storage[1] += gs;
								pausers::pause();
								break;
							} else {
								notices::money_not();
								pausers::pause();
								break;
							}
						}
					}
					clear_screen();
					break;
				} else if (no) {
					clear_screen();
					break;
				}
			}
		} else if (key == 'C' || key == 'c') {
			uglyprice = 9;
			while (1) {
				cout << "Input the number of grams you want to buy:";
				cin >> gs;
				badint();
				if (isbadint)gs = 0;
				M_notice();
				if (gs == 0) {
					pausers::pause();
					turns--;
					break;
				} else {
					if (money >= gs * uglyprice) {
						cout << "You have successfully bought " << gs << " grams of soda!\n";
						money = money - gs * uglyprice;
						storage[2] += gs;
						pausers::pause();
						break;
					} else {
						notices::money_not();
						pausers::pause();
						break;
					}
				}
			}
			clear_screen();
		} else if (key == 'D' || key == 'd') {
			while (1) {
				cout << "Input the number of milliliters you want to buy:";
				cin >> gs;
				badint();
				if (isbadint)gs = 0;
				if (storage[3] < 1000 && storage[3] + gs <= 1000) {
					storage[3] += gs;
					cout << "You have successfully bought " << gs << " milliliters of water!\n";
					hyphen(4);
					break;
				} else {
					cout << "Sorry, but you have had enough water!\n";
					hyphen(4);
					break;
				}
			}
			pausers::pause();
			clear_screen();
		} else if (key == 'E' || key == 'e') {
			uglyprice = 6;
			while (1) {
				cout << "Input the number of grams you want to buy:";
				cin >> gs;
				M_notice();
				if (gs == 0) {
					pausers::pause();
					turns--;
					break;
				} else {
					if (money >= gs * uglyprice) {
						cout << "You have successfully bought " << gs << " grams of flour!\n";
						money = money - gs * uglyprice;
						storage[4] += gs;
						pausers::pause();
						break;
					} else {
						notices::money_not();
						pausers::pause();
						break;
					}
				}
			}
			clear_screen();
		} else if (key == 'F' || key == 'f') {
			uglyprice = r_events(123, 900 - 20, 20);
			cout << "Price: $ " << uglyprice << "\n";
			notices::still_buy();
			while (1) {
				key = getch();
				if (yes) {
					while (1) {
						cout << "Input the number of milliliters you want to buy:";
						cin >> gs;
						badint();
						if (isbadint)gs = 0;
						M_notice();
						if (gs == 0) {
							pausers::pause();
							turns--;
							break;
						} else {
							if (money >= gs * uglyprice) {
								cout << "You have successfully bought " << gs << " square meters of air!\n";
								money = money - gs * uglyprice;
								pausers::pause();
								break;
							} else {
								notices::money_not();
								pausers::pause();
								break;
							}
						}
					}
					clear_screen();
					break;
				} else if (no) {
					clear_screen();
					break;
				}
			}
		} else if (key == 'G' || key == 'g') {
			hyphen(4);
			break;
		}
	}
}

void M_stu() {	//buying props
	while (1) {
		notices::money_have();
		cout << "Props:\nA) Buttercup - a kind of plant (Sadness [-8]) $ " << price_pbutter << "\nB) Buttercup - a kind of madness (Sadness [-15]) $ " << price_mbutter << "\n";
		cout << "C) Arsenic (Use it when investing. Rate of success [+50]%) Price: (all the money you have, including money for investment)/5, then minus a random number (1~(money you have)/20)";
		cout << "\nD) Diamond (use it when investing, so the [investment will fail 100%]) Price: (all the money you have, including money for investment)*10\nE) Quit this menu\n";
		key = getch();
		if (key == 'A' || key == 'a') {
			if (!(money < 35)) {
				money = money - 35;
				sad = sad - 8;
				notices::bought_success();
				notices::sad_minus(8);
				hyphen(4);
				break;
			} else {
				notices::money_not();
				hyphen(4);
			}
		} else if (key == 'B' || key == 'b') {
			if (!(money < 50)) {
				money = money - 50;
				sad = sad - 15;
				notices::bought_success();
				notices::sad_minus(15);
				hyphen(4);
				break;
			} else {
				notices::money_not();
				hyphen(4);
			}
		} else if (key == 'C' || key == 'c') {
			if (!(money <= 0)) {
				while (1) {
					cheatmoney = (money + Iinvest) / 5;
					if (money / 20 < 1)cheatmoney = cheatmoney - r_events(131, 1, (money + Iinvest) / 20);
					else cheatmoney = cheatmoney - r_events(131, (money + Iinvest) / 20, 1);
					if (!(cheatmoney <= 0))break;
				}
				cout << "This time the price is $ " << cheatmoney << "\n";
				pausers::sure();
				while (1) {
					key = getch();
					if (yes) {
						if (!(money < cheatmoney)) {
							if (!invest) {
								cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (cheat) {
									cout << "Sorry, buy you have already bought this prop!\n";
								} else if (loser) {
									cout << "Sorry, but you have already bought another prop...\n";
								} else {
									money = money - cheatmoney;
									notices::bought_success();
									cheat = true;
								}
							}
							pausers::pause();
						} else {
							notices::money_not();
							pausers::pause();
						}
						clear_screen();
						break;
					}
					if (no) {
						clear_screen();
						break;
					}
				}
			} else {
				cout << "You don't have any money at all!\n";
				hyphen(4);
				hyphen(4);
			}
		} else if (key == 'D' || key == 'd') {
			if (!(money <= 0)) {
				cout << "This time the price is $ " << money * 10 << "\n";
				notices::still_buy();
				while (1) {
					key = getch();
					if (yes) {
						if (!(money < money * 10)) {
							cout << "What the hell have you done to the code?!\n";
							hyphen(250);
							if (!invest) {
								cout << "Sorry, but you don't have any investment!\n";
							} else {
								if (loser) {
									cout << "Sorry, buy you have already bought this prop!\n";
								} else if (cheat) {
									cout << "Sorry, but you have already bought another prop...\n";
								} else {
									money = money - money * 10;
									notices::bought_success();
									loser = true;
								}
							}
							pausers::pausers::pause(1);
						} else {
							notices::money_not();
							pausers::pausers::pause(1);
						}
						break;
					}
					if (no) {
						clear_screen();
						break;
					}
				}
			} else {
				cout << "You don't have any money at all!\n";
				hyphen(4);
				hyphen(4);
			}

		} else if (key == 'E' || key == 'e') {
			hyphen(4);
			break;
		}
	}
}

bool det = false; //applied for loan or not
int Mdet;//applied for
int Pdet;//pay back
float Edet;//interest
int Ddet;//terms
bool Ldet = false;//be in arrears or not
void M_det() {//loan
	hyphen();
	if (!det) {
		while (1) {
			cout << "Input the amount of loan you want to apply for (no more than (all the money you have)*10):\n";
			cin >> Mdet;
			badint();
			if (isbadint)gs = 0;
			if (!(Mdet <= 0)) {
				if (!(Mdet > 10 * money) && money != 0) {
					Ddet = r_events(3, 10, 1);
					Edet = r_events(3, 10, 1);
					cout << "Loan $ " << Mdet << "/Total interest " << Edet << "%/On the terms of " << Ddet << " days\n";
					cout << "Each day after that [+" << Edet << "]%!\n";
					pausers::sure();
					while (1) {
						key = getch();
						if (yes) {
							notices::money_plus(Mdet);
							money = money + Mdet;
							Ddet = Ddet + days;
							Pdet = Mdet;
							det = true;
							Edet = Edet / 100;
							break;
						}
						if (no) {
							cout << "You give up the contract.\n";
							Mdet = 0;
							Edet = 0;
							Ddet = 0;
							break;
						}
					}
				} else {
					if (money == 0) {
						cout << "Sorry if this is offensive (obviously this is), but the bank won't trust a nut who don't even have a dime!\n";
					} else {
						cout << "Sorry, but this is obviously more than ten times of all the money you have!\n";
					}
					turns--;
				}
				hyphen(4);
				break;
			} else {
				if (Mdet == 0) {
					cout << "You give up the loan\n";
					turns--;
					break;
				}
				if (Mdet < 0) {
					cout << "The number is wrong, please input again!\n";
					hyphen(4);
				}
			}
		}
		hyphen(4);
	} else {
		cout << "Sorry, but you have already appied for a loan!\n";
		hyphen(4);
	}
}


bool Dgm = false;
void handle_pay_back_in_arrears() {
	Pdet = Pdet + Edet * Pdet;
	cout << "\n\nYou need to pay the bank $ " << Pdet << ", are you going to pay? (Press Y to confirm, and press N to refuse)\n";
	while (1) {
		key = getch();
		if (yes) {
			if (money >= Pdet) {
				cout << "You have pay off the loan.\n";
				det = false;
				Pdet = 0;
				Ldet = false;
				Edet = 0;
				money = money - Pdet;
			} else {
				cout << "Sorry, but you don't have enough money to pay!\nA few bank clerks are scolding you and your pet at your front door.\n";
				notices::sad_plus(15);
				notices::hap_minus(10);
				hap = hap - 10;
				sad += 15;
			}
			hyphen(3);
			Dgm = false;
			break;
		}
		if (no) {
			cout << "You refuse to pay.\nA few bank clerks are scolding you and your pet at your front door.\n";
			notices::sad_plus(15);
			notices::hap_minus(10);
			sad += 15;
			hap = hap - 10;
			hyphen(3);
			Dgm = false;
			break;
		}
	}
}

void handle_pay_back_out_arrears() {
	Pdet = Pdet + Edet * Pdet;
	cout << "\n\nIt's time for you to pay back. You need to pay the bank $ " << Pdet << ", are you going to pay? (Press Y to confirm, and press N to refuse)\n";
	while (1) {
		key = getch();
		if (yes) {
			if (money >= Pdet) {
				cout << "You pay off the load. Because of your honesty,\n";
				notices::hap_plus(2);
				notices::sad_minus(1);
				hap += 2;
				sad -= 1;
				money -= Pdet;
				Pdet = 0;
				det = false;
				Mdet = 0;
				Edet = 0;
				Ddet = 0;
			} else {
				cout << "Sorry, but You don't have enough money to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
				Mdet = 0;
				Ddet = 0;
				Ldet = true;
			}
			hyphen(3);
			break;
		}
		if (no) {
			cout << "You refuse to pay!\nEach day after this, your debt [+" << Edet << "]%!\n";
			Ldet = true;
			Mdet = 0;
			Ddet = 0;
			hyphen(3);
			break;
		}
	}
}

void M_() {
	if (money < 0) {
		money = 0;
	}
	if (det) {
		if (Ldet && Dgm) {
			handle_pay_back_in_arrears();
		} else if (!Ldet && days == Ddet) {
			handle_pay_back_out_arrears();
		}
	}
}

void check_cooking_ingredient() {
	colorc(blue);
	cout << "You have " << storage[0] << " grams of sugar\nYou have " << storage[1] << " grams of salt\nYou have " << storage[2] << " grams of soda\nYou have " << storage[3] << " milliliter of water (1000 milliliter max)\nYou have " << storage[4] << " grams of flour\n";
	colorc(white);
	pausers::pausers::pause(1);
	turns--;
	hyphen(4);
}

void handle_quit_game() {
	cout << "You quit the game.\n";
	pausers::pausers::pause(4);
}

void handle_feed_pet() {
	cout << "You feed your pet.\n";
	w_eat = 0;
	if (eat) {
		hap += 2;
		notices::hap_plus(2);
	}
	eat = false;
	pausers::pause();
}

void handle_defecate() {
	cout << "You let your pet " << name << " defecates\n";
	w_poo = 0;
	if (poo) {
		notices::hap_plus(1);
		++hap;
	}
	poo = false;
	pausers::pause();
}

void handle_pat() {
	cout << "You pat your pet " << name << "\n";
	hap += 4;
	sad = sad - 3;
	notices::hap_plus(4);
	notices::sad_minus(3);
	pausers::pause();
}

void handle_quit_interaction_menu() {
	hyphen(4);
	notice();
	key = getch();
	interact();
}

void handle_interact_with() {
	cout << "\n\nINTERACTIONS:\nA) Let your pet to defecate\nB) Pat your pet\nC) Quit this menu\n";
	key = getch();
	switch (key) {
	case 'A':
	case 'a':
		handle_defecate();
		break;
	case 'B':
	case'b':
			handle_pat();
		break;
	case 'C':
	case 'c':
		handle_quit_interaction_menu();
		break;
	default:
		cout << "\n";
		notices::choose_again();
		break;
	}
	cout << "\n\n";
}

void handle_status_display() {
	cout << "---LIFESPAN---\n";
	notices::your_pet();
	Pab == cat ? cout << "is a cat.\n" : cout << "is a dog.\n";
	notices::your_pet();
	cout << "is " << age << " years old now\n";
	notices::your_pet();
	cout << "can still live for " << lifespan - days + 1 << " days\n";
	notices::your_pet();
	cout << "need to have at least reach to [Happiness: " << Lifespanhap << "] to prolong lifespan\n";
	cout << "---EMOTION---\n";
	cout << "[Happiness: " << hap << "/" << max_hap << "]\n[Sadness: " << sad << "/" << max_sad << "]\n";
	cout << "---PHYSIOLOGY---\n";
	cout << "Wants to defecate:";
	poo == true ? cout << "[YES]\n" : cout << "[NO]\n";
	cout << "Wants to eat:";
	eat == true ? cout << "[YES]\n" : cout << "[NO]\n";
	turns--;
	pausers::pause();
}

void handle_clear_screen() {
	clear_screen();
	turns--;
}

void handle_buying() {
	cout << "You have $ " << money << "\nWhat do you want to do next?\nA) Buy items\nB) Buy [cooking ingredients]\nC) Apply for loan\nD) Start cooking\nE) Quit this menu\n";
	key = getch();
	switch (key) {
	case 'A':
	case 'a' :
		hyphen();
		M_stu();
		break;
	case 'B':
	case 'b':
		hyphen();
		M_cok();
		break;
	case 'C':
	case 'c':
		hyphen();
		M_det();
		break;
	case 'D':
	case 'd':
		Cincook();
		break;
	case 'E':
	case 'e':
		//hyphen();
		//notice();
		//key = getch();
		//interact();
		break;
	default :
		cout << "\n";
		notices::choose_again();
	}
}

void handle_investment_info() {
	if (Vacheve) {
		turns--;
		Vacheve = false;
		hyphen(5);
		cout << "Money you have invested: $ " << Iinvest << "\nYou need to wait for: " << Dinvest - days << "days\n";
	} else {
		hyphen(3);
		cout << "\nPlease choose again!\n";
		notice();
		key = getch();
		interact();
	}
}

void handle_color_change() {
	options::color_choose();
	turns --;
}

int CDSS = 0;
void sub_handle_backpack_item_display() {
	while (1) {
		if (CDSS == Cid)break;
		cout << CDSS << "." << backpackmeal[CDSS] << "|Energy: " << backpackcalr[CDSS] << "|Effect: " << backpackeffect[CDSS] << "|";
		cout << "Amount: " << backpackall[CDSS] << "\n";
		++CDSS;
	}
	pausers::pause();
}

unsigned int CTP;//for circulation
void sub_handle_backpack_item_interaction() {//waiting to update
	hyphen(4);
	cout << "A) Sell this dish\nB) Feed this dish to your pet\nC) Dump this dish\nD) Quit this menu\n";
	while (1) {
		key = getch();
		if (key == 'A' || key == 'a') {

			break;
		} else if (key == 'B' || key == 'b') {

			break;
		} else if (key == 'C' || key == 'c') {
			cout << "Item NO. " << CTP << " has been dropped\n";
			Cdrop(CTP);
			break;
		} else if (key == 'D' || key == 'd') {
			break;
		}
	}
}

void handle_backpacking() {
	hyphen(4);
	if (Cid != 0) {
		sub_handle_backpack_item_display();
		while (1) {
			cout << "Input the number of item you want to choose (insert negative number to quit this menu):";
			cin >> CTP;
			badint();
			if (isbadint || (CTP >= Cid || CTP < 0)) {
				break;
			} else {
				sub_handle_backpack_item_interaction();
			}
		}
	} else {
		cout << "You don't have any dish!\n";
		pausers::pause();
	}
	turns--;
	hyphen(4);
}

void handle_cheating() {
	hyphen(250);
	cout << "Insert cheating coide: ";
	cin >> cheating;
	cout << "\n";
	if (cheating == "Gmoney") {
		cin >> Mopluse;
		money += Mopluse;
	} else if (cheating == "Clean") {
		hap = 50;
		sad = 0;
		poo = false;
		eat = false;
	} else if (cheating == "Turns") {
		turns = 1;
	} else if (cheating == "Smoney") {
		cin >> Mopluse;
		money = Mopluse;
	} else if (cheating == "Suicide") {
		hap = 0;
		sad = 10;
	} else if (cheating == "Days") {
		cin >> Mopluse;
		days = Mopluse;
	} else if (cheating == "r1")r1();
	else if (cheating == "r2")r2();
	else if (cheating == "r3")r3();
	else if (cheating == "r4")r4();
	else if (cheating == "r5")r5();
	else if (cheating == "Bdays")band_days();
	else if (cheating == "Btv1")Btv1();
	else if (cheating == "Btv2")Btv2();
	else if (cheating == "Btv3")Btv3();
	else if (cheating == "Btv4")Btv4();
	else if (cheating == "storage[0]") {
		cin >> Mopluse;
		storage[0] = Mopluse;
	} else if (cheating == "storage[1]") {
		cin >> Mopluse;
		storage[1] = Mopluse;
	} else if (cheating == "storage[2]") {
		cin >> Mopluse;
		storage[2] = Mopluse;
	} else if (cheating == "storage[3]") {
		cin >> Mopluse;
		storage[3] = Mopluse;
	} else if (cheating == "storage[4]") {
		cin >> Mopluse;
		storage[4] = Mopluse;
	}
	/*
	else if (cheating == "Walk") {
		clear_screen();
		start();
	}
	*/
	else if (cheating == "Cooking") {
		storage[3] = 100;
		storage[0] = 100;
		storage[1] = 100;
		storage[2] = 100;
		storage[4] = 100;
	}
	cout << "\n";
	hyphen(250);
	turns--;
}

void handle_default() {
	hyphen(3);
	cout << "\n";
	notices::choose_again();
	notice();
	key = getch();
	interact();
}

void interact() {
	cout << "\n";

	switch (key) {
	default:
		handle_default();
		break;
	case 'Q':
	case 'q':
		handle_quit_game();
		break;
	case 'F':
	case 'f':
		handle_feed_pet();
		break;
	case 'I':
	case 'i':
		handle_interact_with();
		break;
	case 'C':
	case 'c':
		handle_status_display();
		break;
	case 'S':
	case 's':
		handle_clear_screen();
		break;
	case 'M':
	case 'm':
		handle_buying();
		break;
	case 'V':
	case 'v':
		handle_investment_info();
		break;
	case 'B':
	case 'b':
		check_cooking_ingredient();
		break;
	case 'O':
	case 'o':
		handle_backpacking();
		break;
#ifdef _WIN32
	case 'X':
	case 'x':
		handle_color_change();
		break;
#endif
	case 'L':
	case 'l':
		handle_cheating();
		break;
	}
}

void re_ini() {
	e_hap();
	e_sad();
	e_poo();
	e_eat();
	Cfour();
	M_();
}

void o_days_pre_notice() {
	re_ini();
	e_age();
	if (cheatable)cout << "*";
	cout << "DAY " << days << " .\n";
	if (det  && Ldet)Dgm = true;
	if (eat) {
		cout << "Your pet " << name << " is hungry\n";
	}
	if (poo) {
		cout << "Your pet " << name << " wants to defecate\n\n";
	}
	if (Pmouse) {
		Pmouse_plus = r_events(1784, 5, 1);
		cout << "Your pet is playing with the toy mouse.\n";
		notices::hap_plus(Pmouse_plus);
		hap += Pmouse_plus;
	}
	if (BFS) {
		Msenting = r_events(1321, 500, 20);
		cout << "Some fans want " << name << " to keep performing, so they put $ " << Msenting << " .\n";
		notices::money_plus(Msenting);
		money = money + Msenting;
	}
	if (lifespan < 0)lifespan = 0;
	if (days == lifespan) {
		cout << "If nothing goes wrong, this is the last day of your pet.\n";
	}
	hyphen(2);
	if (Lifespanhap + 5 <= max_hap && days != 1) {
		notices::your_pet();
		notices::lifespan_plus(5);
		Lifespanhap += 5;
	} else if (days != 1 && Lifespanhap != max_hap) {
		notices::your_pet();
		notices::lifespan_plus(max_hap - Lifespanhap);
		Lifespanhap = max_hap;
	}
}

void o_days() {
	o_days_pre_notice();
	while (1) {
		if (lifespan < 0)lifespan = 0;
		if (days >= lifespan + 1) {
			death();
			died = true;
		}
		re_ini();
		if (died) break;
		notice();
		key = getch();
		interact();
		if (key == 'Q' || key == 'q') break; //quit
		++turns;
		++w_eat;
		if (days != 1) {
			++w_poo;
		}
		if (w_eat > 2)eat = true;
		if (w_poo > 4)poo = true;
		cout << "\n\n";
		if (eat) {
			notices::your_pet();
			cout << "is hungry\n";
		}
		if (poo) {
			notices::your_pet();
			cout << "wants to defecate\n\n\n";
		}
		hyphen(1);
		cout << "\n\n";
		if (turns == 9) {
			break;
			hyphen();
		}
	}
	if (invest  && days == Dinvest) { //random event no.2
		invest = false;
		Dinvest = 0;
		randomnum = r_events(3, 4, 1);
		Einvest = r_events(3, 50, 10);
		if (!cheat) {
			if (!loser && randomnum == 2) {
				notices::your_pet();
				cout << "has made a successful investment!\nRate of profit " << Einvest << "%!\n";
				notices::money_plus(IINVEST + Einvest / 100 * IINVEST);
				notices::hap_plus(2);
				money = money + IINVEST + Einvest / 100 * IINVEST;
				hap += 2;
			} else if (!loser && randomnum != 2) {
				notices::your_pet();
				cout << "has failed the investment!\n";
				notices::hap_minus(1);
				notices::sad_plus(2);
				hap -= 1;
				sad += 2;
			} else if (loser) {
				randomnum = 114514;
				loser = false;
			}
		} else if (cheat && randomnum != 1) {
			notices::your_pet();
			cout << "has made a successful investment!\nRate of profit: " << Einvest << "!\n";
			float profit_rate = Einvest / 100.0f;
			notices::money_plus(IINVEST + profit_rate * IINVEST);
			notices::hap_plus(2);
			money = money + IINVEST + profit_rate * IINVEST;
			hap += 2;
			cheat = false;
		} else if (cheat && randomnum == 1) {
			notices::your_pet();
			cout << "has failed in the investment!\n";
			notices::hap_minus(1);
			notices::sad_plus(2);
			hap -= 1;
			sad += 2;
			cheat = false;
		}
		Iinvest = 0;
		IINVEST = 0;
		Einvest = 0;
		hyphen();
		pausers::pause();
		cout << "\n\n";
	}
	if (key != 'Q' && key != 'q')r_e();
	turns = 1;
	++days;
}

void starter_notice() {
	pausers::pause();
#ifdef _WIN32
	options::color_choose();
#endif
	options::name_choose();
	srand(time(NULL));
	Mname();
	Mname1();
	have_body_ini();
	per();
	pausers::pause();
	cout << "You will have a great time together, won't you?\nYou look at your pet, then suddenly realize that";
	refer(nomin);
	cout << "might become the next Michael Jackson.\n";
	pausers::pausers::pause(1);
	r_lifespan();
	Lifespanhap = r_events(1242, 85 - 60, 60);
}

int main() {
	//ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cout << "Digital Pet\n" << version << " " << phase;
	if (cheatable)cout << "*";
	cout << "\n";
	hyphen(4);

	starter_notice();

	while (1) {
		o_days();
		if (key == 'Q' || key == 'q')break;
		if (died)break;
	}
	return 0;
}
