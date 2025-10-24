#include"includes.h"
#include"basicfunc.h"

int rounds;

struct player.choice {
	unsigned char choice, life;
} player;

struct Computer {
	unsigned char choice, sex, ran_choice, ran_choice0, life;
} computer;

void Computer() {//男性倾向出拳，女性倾向出剪刀；有一定概率不变动上局的判断
	computer.ran_choice0 = 1 + rand() % (10);
	computer.ran_choice = 1 + rand() % (computer.ran_choice0);
	if (computer.ran_choice == 1 == false || computer == 0) {
		computer.ran_choice = 1 + rand() % (3);
		if (computer.ran_choice == 2) {
			if (computer.sex == male) computer.choice = rock;
			else computer.choice = scis;
		} else computer.choice = 1 + rand() % (3);
	}
}

bool square;
void game1() {
	computer.sex = rand() % (2);
	rounds = 1;
	player.life = 2;
	computer.life = 2;
	cout << "游戏是猜拳，三局两胜！（按任意键继续）";
	getch();
	clear_screen();
	while (1) {
		if (player.life == 0) {
			cout << "死神的血盆大口露出狞笑，尖牙利齿闪烁着光芒……（按任意键继续）";
			getch();
			cout << "\n";
			cout << "“输掉了这场游戏你便一无所有！”\n";
			Quit = true;
			break;
		} else if (computer.life == 0) {
			cout << "无数条小径接连着无数个花园；花园又延伸出无数条分岔的小径……（按任意键继续）";
			getch();
			cout << "\n";
			cout << "余准离开死神，顺着其中的一条重返人间。他还背负着骄傲和自负，也背负着最终会降临在他身上的绝望的孤独\n";
			Php = Max_hp / 2;
			break;
		}
		cout << "-第" << rounds << "局！-\n余准：" << player.life << "条命\n死神：" << computer.life << "条命\n";
		if (rounds == 1 && (!square)) {
			cout << "男性更倾向出石头进攻，女性更倾向出剪刀，但你并不能从死神的骷髅头上看到任何性别特征……只能选择其中的一种可能孤注一掷了！（按任意键继续）\n";
			getch();
		}
		cout << "----------------------------------------\n";
		cout << "出什么？\nA.剪刀\nB.石头\nC.布\n";
		while (1) {
			key = getch();
			if (key == 'a' || key == 'A') {
				player.choice = scis;
				cout << "余准出剪刀！\n";
				break;
			} else if (key == 'b' || key == 'B') {
				player.choice = rock;
				cout << "余准出石头！\n";
				break;
			} else if (key == 'c' || key == 'C') {
				player.choice = paper;
				cout << "余准出布！\n";
				break;
			}
		}
		Computer();
		//
		cout << computer << "\n";
		if (computer == scis) cout << "死神出剪刀！\n";
		else if (computer == rock) cout << "死神出石头！\n";
		else if (computer == paper) cout << "死神出布！\n";
		//
		if (player.choice == computer) {
			cout << "平局！\n";
			rounds -= 1;
			square = true;
		} else if (player.choice == rock) {
			square = false;
			if (computer.choice == scis) {
				cout << "死神输一局！\n";
				computer.life -= 1;
			}
			if (computer.choice == paper) {
				cout << "死神赢一局！\n";
				player.life -= 1;
			}
		} else if (player.choice == scis) {
			square = false;
			if (computer.choice == paper) {
				cout << "死神输一局！\n";
				computer.life -= 1;
			}
			if (computer.choice == rock) {
				cout << "死神赢一局！\n";
				player.life -= 1;
			}
		} else if (player.choice == paper) {
			square = false;
			if (computer.choice == rock) {
				cout << "死神输一局！\n";
				computer.life -= 1;
			}
			if (computer.choice == scis) {
				cout << "死神赢一局！\n";
				player.life -= 1;
			}
		}
		++rounds;
		cout << "（按下任意键继续……）\n";
		getch();
		clear_screen();
	}
}
