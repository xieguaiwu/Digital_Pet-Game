#include"includes.h"
//定义：语言
enum Language {cn, en};
//定义：性格
enum Personality {cat, dog};
//定义：性别
enum GenderType {M, F};
//定义：refertype
enum ReferType {nomin, object, posses};
//定义：按键
enum KeyCode {up = 'H', down = 'P'};
//定义：颜色
enum Color {red, green, blue, white = 6};
//定义：主题
enum ThemeType {Tdef, Tadv, Tele, Tnor};
//定义：用于烹饪头文件
enum CookType {ck, cr};
//定义-菜品
enum MealType {air, soda, indefine, flor, bread, bananas, cake};
//定义宏-菜品口味
enum Taste {sweet, sult, mois, too_sod, flat, floy, Vsweet, Vsult, Vmois, Vfloy, dry};
//0甜腻1咸的2湿乎乎的3充满气体的4平淡的5软绵绵的6非常甜的7非常咸的8非常湿的9非常软绵绵的10很干的

//机器人性别偏向
enum {male, female};
//石头剪刀布
enum {rock, paper, scis};

//定义：身体
enum BodyType {
	head,
	neck,
	torso
};//0~body_pieces-1

const unsigned char body_pieces = 3;

enum FaceType {
	left_eye = body_pieces,
	right_eye,
	nose,
	mouth,
	face
};//body_pieces~body_pieces+face_pieces-1

const unsigned char face_pieces = 5;

enum ArmType {
	left_arm = body_pieces + face_pieces,
	right_arm,
	left_hand,
	left_hand_finger,
	left_hand_finger_nail,
	right_hand,
	right_hand_finger,
	right_hand_finger_nail
};//body_pieces+face_pieces~body_pieces+face_pieces+arm_pieces-1

const unsigned char arm_pieces = 8;

enum LegType {
	left_leg = body_pieces + face_pieces + arm_pieces,
	left_foot,
	left_foot_toes,
	right_leg,
	right_foot,
	right_foot_toes
};

const unsigned char leg_pieces = 6;

const unsigned char all_parts = body_pieces + face_pieces + arm_pieces + leg_pieces;

//定义宏-菜品效果
#define lifeup1 0.1 //寿命【+1】 
#define lifeup2 0.2 //寿命【+2】
#define lifelow1 -0.1//寿命【-1】
#define lifelow2 -0.2//寿命【-2】

#define hapup10 1.10//快乐值【+10】
#define hapup15 1.15//快乐值【+15】
#define haplow10 -1.10//快乐值【-10】
#define haplow15 -1.15//快乐值【-15】
#define Hapup5 2.5 //快乐值上限【+5】
#define Hapup15 2.15//快乐值上限+15
#define Haplow5 -2.5//快乐值上限【-5】
#define Haplow15 -2.15//快乐值上限【-15】 

#define sadup5 3.5//悲伤值+5
#define sadup8 3.8//悲伤值+8
#define sadlow5 -3.5//悲伤值【-5】
#define sadlow8 -3.8//悲伤值【-8】
#define Sadup5 4.5//悲伤值上限【+5】
#define Sadup10 4.10//悲伤值上限+10
#define Sadlow5 -4.5//悲伤值上限【-5】
#define Sadlow10 -4.10//悲伤值上限【-10】 

#define none 5.0//无效果-口味平淡 

#define yes key=='Y'||key=='y'
#define no key=='N'||key=='n'

//bool language;
unsigned char theme;

string name = "PET"; //宠物名称
//宠物指标
unsigned int age = 0; //年龄 10天增加1
unsigned int hap = 50; //快乐值 初始100-满
unsigned int max_hap = 100; //初始最大值
unsigned int sad = 0; //悲伤值 初始50-满
unsigned int max_sad = 50; //初始最大值
bool poo = false; //排泄
unsigned char w_poo;//排泄忍耐时间 10-满
bool eat = false; //进食 5-满
unsigned char w_eat;//进食忍耐时间
bool Pab;//宠物性格
bool gender;

unsigned int lifespan;//宠物寿命天数，可增加！
unsigned int Mlifespan;//极限最大寿命
unsigned int Llifespan;//最短寿命

unsigned int money = 50;		//金钱

const char pers = 2; //性格随机数
const char gens = 2; //性别个数
const char events = 6; //随机事件的个数

int randomnum;//随机数的返回值
char key;//按键
bool isbadint;

const string version = "0.2.3";
const string phase = "alpha";

//烹饪变量
unsigned int calr;//热量
string Meal;//烹饪品总名称（口味+名称）
map<unsigned int, string> meal;//烹饪品名称
map<unsigned int, string> Tmeal;//烹饪品口味
map<float, string>effects;

#ifdef _WIN32
#include <conio.h>
#else
int getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

int r_events(int sss = 0, int Mranding = 0, int Lranding = 0) { //随机数生成，用于随机事件和随机性格等
	if (sss == 0) {
		return 1 + rand() % (events); //生成 随机事件
	}
	else if (sss == 1) {
		return rand() % (pers - 1); //生成 随机性格
	}
	else if (sss == 2) {
		return rand() % (gens - 1);
	}
	else {
		//if(Mranding<Lranding)cout <<"随机数生成错误！\n";
		return Lranding + rand() % (Mranding); //其余的生成
	}
}

void badint() {
	isbadint = false;
	if (!cin.fail())isbadint = false;
	else {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		isbadint = true;
	}
}

void clear_screen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void hyphen(int shan = 0) {
	if (shan == 0)cout << "----------------------------------------\n";
	else if (shan == 1)cout << "****************************************\n";
	else if (shan == 2)cout << "++++++++++++++++++++++++++++++++++++++++\n";
	else if (shan == 3)cout << "========================================\n";
	else if (shan == 4)cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	else if (shan == 5)cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	else if (shan == 250)cout << "---Cheating Line-Cheating Line-Cheating Line-Cheating Line-Cheating Line---\n";
}

void refer(int refertype) {
	cout << " ";
	if (refertype == nomin)gender == M ? cout << "he" : cout << "she";
	else if (refertype == object)gender == M ? cout << "him" : cout << "her";
	else if (refertype == posses)gender == M ? cout << "his" : cout << "her";
	cout << " ";
}

void colorc(int x) { //0.红 1.绿 2.蓝
	if (theme == Tdef) {
#ifdef _WIN32
		if (x == red)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		if (x == green)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		if (x == blue)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		if (x == white)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
	}
}

class pausers {
public:
	static void pause(int screen = 0) {
		cout << " (Press any key to continue...)\n";
		getch();
		if (screen == 1)clear_screen();
	}

	static void sure(bool besure = true) {
		if (besure)cout << "Are you sure?";
		cout << " (Press Y to confirm, and press N to refuse)\n";
	}
};

//选择设置
class options {
public:
	static void color_choose() {
		cout << "\nChoose your theme color:\nA.Defalut theme (balck background+white words)\nB.Adventure theme (pureple background+white words)\n";
		cout << "C.Elegent theme (grey background+light white words)\nD.Normal theme (white background+black words)\n";
		while (1) {
			key = getch();
			if (key == 'A' || key == 'a') {
				system("color 07");
				pausers::sure();
				while (1) {
					key = getch();
					if (yes) {
						theme = Tdef;
						break;
					}
					else if (no) {
						color_choose();
						break;
					}
				}
				break;
			}
			else if (key == 'B' || key == 'b') {
				system("color df");
				pausers::sure();
				while (1) {
					key = getch();
					if (yes) {
						theme = Tadv;
						break;
					}
					else if (no) {
						color_choose();
						break;
					}
				}
				break;
			}
			else if (key == 'C' || key == 'c') {
				system("color 8f");
				pausers::sure();
				while (1) {
					key = getch();
					if (yes) {
						theme = Tele;
						break;
					}
					else if (no) {
						color_choose();
						break;
					}
				}
				break;
			}
			else if (key == 'D' || key == 'd') {
				system("color 70");
				pausers::sure();
				while (1) {
					key = getch();
					if (yes) {
						theme = Tnor;
						break;
					}
					else if (no) {
						color_choose();
						break;
					}
				}
				break;
			}
		}
	}

	/*static void language_choose() {
		cout << "选择语言(Choose language)：按↑选择中文，按↓选择英文(Press Y to choose Chinese and press N to choose English)\n";
		while (1) {
			key = getch();
			if (yes) {
				language = cn;
				break;
			}
			else if (key == 'N'|| key == 'n') {
				language = en;
				break;
			}
		}
	}*/

	static void name_choose() {
		cout << "\nInput the name of your digital pet:\n";
		getline(cin, name);
		while (1) {
			if (name != "" && name != " " && name != "  " && name != "   " && name != "    ")break;
			else {
				cout << "Please input again:";
				getline(cin, name);
			}
		}
		if (name == "毛茛" || name == "毛艮" || name == "morgan" || name == "Morgan") name = "比利";
		if (name == "Rick" || name == "Joker") name = "杀人犯";
		pausers::pause(1);
		cout << "'" << name << "' you thought.";
		if (name == "比利")cout << "What a crazy name.\n";
		else if (name == "杀人犯")cout << "This sounds murderous.\n";
		else {
			cout << "What a good name this is.\n";
		}
	}
};


//宠物性格生成
void per() {	//随机生成宠物的性格
	cout << "You remember the day you met " << name << ":";
	randomnum = r_events(1); //生成随机数
	Pab = randomnum;
	if (Pab == dog) {
		cout << "You saw a puppy at a pet store. You liked";
		refer(posses);
		cout << " mad look, so you took";
		refer(object);
		cout << "home.";
	}
	else if (Pab == cat) {
		cout << "You saw a snoring pussy in a carton. After giving";
		refer(object);
		cout << "some saussages, you took";
		refer(object);
		cout << "home.";
	}
	cout << "And now you have named";
	refer(object);
	cout << ".\n";
}

void r_lifespan() { //随机寿命
	if (Pab == cat) lifespan = 20 + rand() % (40 - 20); //猫的寿命：2~4岁天（可增加）
	else if (Pab == dog) lifespan = 15 + rand() % (50 - 15); //狗的寿命：1岁半到5岁（可增加）
}

//提示
class notices {
public:
	static void still_buy() {
		cout << "Continue to buy?";
		pausers::sure(false);
	}

	static void choose_again() {
		cout << "Please choose again!\n";
	}

	static void your_pet() {
		cout << "Your pet ";
		cout << name;
		//if (language == en)
		cout << " ";
	}

	static void hap_plus(int hapin) {
		colorc(green);
		cout << "Happiness [+" << hapin << "]!\n";
		colorc(white);
	}

	static void hap_minus(int hapout) {
		colorc(red);
		cout << "Happiness [-" << hapout << "]!\n";
		colorc(white);
	}

	static void lifespan_plus(int lifespanin) {
		colorc(red);
		cout << "Happiness needed to increase lifespan [+" << lifespanin << "]!\n";
		colorc(white);
	}

	static void lifespan_minus(int lifespanout) {
		colorc(green);
		cout << "Happiness needed to increase lifespan [-" << lifespanout << "]!\n";
		colorc(white);
	}

	static void sad_plus(int sadin) {
		colorc(red);
		cout << "Sadness [+" << sadin << "]!\n";
		colorc(white);
	}

	static void sad_minus(int sadout) {
		colorc(green);
		cout << "Sadness [-" << sadout << "]!\n";
		colorc(white);
	}

	static void money_plus(int monin) {
		colorc(green);
		cout << "$ [+" << monin << "]!\n";
		colorc(white);
	}

	static void money_minus(int monout) {
		colorc(red);
		cout << "$ [-" << monout << "]!\n";
		colorc(white);
	}

	static void money_not() {
		colorc(red);
		cout << "Sorry, but you don't have enough money!\n";
		colorc(white);
	}

	static void money_have() {
		colorc(blue);
		cout << "You have $ " << money << " !\n";
		colorc(white);
	}

	static void bought_success() {
		colorc(blue);
		cout << "Bought successfully!\n";
		colorc(white);
	}
};
