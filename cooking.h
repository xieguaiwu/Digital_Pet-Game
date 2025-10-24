#include<iostream>
using namespace std;

unsigned int cs;
//所有食材总量
unsigned int Camount;
//原料
unsigned int Msug;//糖
unsigned int Msul;//盐
unsigned int Msod;//苏打
unsigned int Mwat;//水
unsigned int Mflo;//面粉

//热量
unsigned int Mcalr;

unsigned short Ncook;//菜品名称
unsigned short Tcook;//菜品口味
float Ecook;//菜品效果

void Mname() {
	meal[0] = "air";
	meal[1] = "soda water";
	meal[2] = "unnamable black item";
	meal[3] = "paste";
	meal[4] = "bread";
	meal[5] = "soda with water";
	meal[6] = "cake";
}

void Mname1() {
	Tmeal[10] = "a bit too sweet";
	Tmeal[11] = "a bit too salty";
	Tmeal[12] = "a bit too drippy";
	Tmeal[13] = "filled with gas";
	Tmeal[14] = "plain";
	Tmeal[15] = "soft";
	Tmeal[16] = "incredibly sweet";
	Tmeal[17] = "incredibly salty";
	Tmeal[18] = "incredibly drippy";
	Tmeal[19] = "incredibly soft";
	Tmeal[20] = "a bit dry";
}

void Ename() {	//菜品效果名称
	//寿命
	effects[0.1] = "Lifespan [+1]";
	effects[0.2] = "Lifespan [+2]";
	effects[-0.1] = "Lifespan [-1]";
	effects[-0.2] = "Lifespan [-2]";
	//生命值
	effects[1.10] = "Happiness [+10]";
	effects[1.15] = "Happiness [+15]";
	effects[-1.10] = "Happiness [-10]";
	effects[-1.15] = "Happiness [-15]";
	effects[2.5] = "Limit of happiness [+5]";
	effects[2.15] = "Limit of happiness [+15]";
	effects[-2.5] = "Limit of happiness [-5]";
	effects[-2.15] = "Limit of happiness [-15]";
	//悲伤值
	effects[3.5] = "Sadness [+5]";
	effects[3.8] = "Sadness [+8]";
	effects[-3.5] = "Sadness [-5]";
	effects[-3.8] = "Sadness [-8]";
	effects[4.5] = "Limit of Sadness [+5]";
	effects[4.10] = "Limit of Sadness [+10]";
	effects[-4.5] = "Limit of Sadness [-5]";
	effects[-4.10] = "Limit of Sadness [-10]";
	//平淡的
	effects[5.0] = "no effect";
}

int meal_effect() {//菜品效果
	if (Tcook == sweet) {
		switch (Ncook) {
		default://其他：快乐值上限【+5】
			Ecook = Hapup5;
			break;
		case soda://口味是甜的，菜品是苏打水，快乐+15
			Ecook = hapup15;
			break;
		case flor://口味是甜的，菜品是面糊，悲伤+5
			Ecook = sadup5;
			break;
		case cake://口味是甜的，菜品是蛋糕，寿命【+1】
			Ecook = lifeup1;
			break;
		case indefine://口味是甜的，菜品是不可名状物体，悲伤值上限【+5】
			Ecook = Sadup5;
			break;
		case bananas://口味是甜的，菜品是带水的苏打，悲伤值【-5】
			Ecook = sadlow5;
			break;
		}
	} else if (Tcook == Vsweet) {
		switch (Ncook) {
		default:
			Ecook = Sadup5;
			break;
		case soda:
			Ecook = sadlow8; //口味是非常甜的，菜品是苏打水，寿命【-1】
			break;
		case flor:
			Ecook = sadup8; //口味是非常甜的，菜品是面糊，悲伤值+8
			break;
		case cake:
			Ecook = lifeup2; //口味是非常甜的，菜品是蛋糕，生命值上限+15
			break;
		case indefine:
			Ecook = sadup8; //口味是非常甜的，菜品是不可名状物体，悲伤值+8
			break;
		case bananas:
			Ecook = sadlow8; //口味是非常甜的，菜品是带水的苏打，生命值【-8】
			break;
		}
	} else if (Tcook == sult) {
		switch (Ncook) {
		default:
			Ecook = Haplow5; //快乐值上限【-5】
			break;
		case soda:
			Ecook = Hapup15; //口味是咸的，菜品是苏打水，快乐值上限【+15】
			break;
		case indefine:
			Ecook = Sadup10; //口味是咸的，菜品是不可名状物体，悲伤值上限【+10】
			break;
		case flor:
			Ecook = hapup10; //口味是咸的，菜品是面糊，快乐值【+10】
			break;
		case bread:
			Ecook = lifeup2; //口味是咸的，菜品是面包，寿命【+2】
			break;
		case bananas:
			Ecook = sadup8; //口味是咸的，菜品是带水的苏打，悲伤值【+8】
			break;
		case cake:
			Ecook = sadup5; //口味是咸的，菜品是蛋糕，悲伤值【+5】
			break;
		}
	} else if (Tcook == Vsult) {
		switch (Ncook) {
		default:
			Ecook = Haplow15; //不可名状物体-快乐值上限【-15】
			break;
		case soda:
			Ecook = lifeup1; //口味是非常咸的，菜品是苏打水，寿命【+1】
			break;
		case flor:
			Ecook = Sadup10; //口味是非常咸的，菜品是面糊，悲伤值上限【+15】
			break;
		case bread:
			Ecook = Hapup15; //口味是咸的，菜品是面包，快乐值上限【+15】
			break;
		case bananas:
			Ecook = lifelow1; //口味是咸的，菜品是带水的苏打，寿命【-1】
			break;
		case cake:
			Ecook = sadup8; //口味是咸的，菜品是蛋糕，悲伤值【-8】
			break;
		}
	} else if (Tcook == mois) {
		if (Ncook == soda) Pab == cat ? Ecook = none : Ecook = Hapup5;
		else if (Ncook == flor)Ecook = none;
		else if (Ncook == bread) Pab == cat ? Ecook = hapup10 : Ecook = sadup5;
		else if (Ncook == bananas)Ecook = none;
		else if (Ncook == cake) Pab == cat ? Ecook = hapup15 : Ecook = sadlow5;
		else Pab == cat ? Ecook = sadlow5 : Ecook = sadup5;
	} else if (Tcook == Vmois) {
		if (Ncook == soda) Pab == cat ? Ecook = none : Ecook = Hapup5;
		else if (Ncook == flor) Pab == cat ? Ecook = none : Ecook = sadup5;
		else if (Ncook == bread) Pab == cat ? Ecook = hapup15 : Ecook = sadup5;
		else if (Ncook == bananas)Ecook = none;
		else if (Ncook == cake) Ecook = Hapup15;
		else Pab == cat ? Ecook = sadlow8 : Ecook = sadup8;
	} else if (Tcook == too_sod) {
		if (Ncook == soda)Pab == cat ? Ecook = Haplow5 : Ecook = none;
		else if (Ncook == flor)Pab == cat ? Ecook = sadup5 : Ecook = none;
		else if (Ncook == bread) Pab == cat ? Ecook = Hapup15 : Ecook = hapup15;
		else if (Ncook == bananas)Ecook = none;
		else if (Ncook == cake)Ecook = sadlow8;
		else Ecook = none;
	} else if (Tcook == floy) {
		if (Ncook == soda) Pab == cat ? Ecook = hapup10 : Ecook = Hapup5;
		else if (Ncook == flor)Ecook = hapup10;
		else if (Ncook == bread)Ecook = Hapup15;
		else if (Ncook == bananas)Ecook = sadup8;
		else if (Ncook == cake)Pab == cat ? Ecook = hapup10 : Ecook = hapup15;
		else Pab == cat ? Ecook = Hapup5 : Ecook = none;
	} else if (Tcook == Vfloy) {
		if (Ncook == soda) Pab == cat ? Ecook = hapup15 : Ecook = Hapup15;
		else if (Ncook == flor)Ecook = hapup15;
		else if (Ncook == bread)Ecook = sadup5;
		else if (Ncook == bananas)Ecook = Sadup5;
		else if (Ncook == cake)Pab == cat ? Ecook = hapup15 : Ecook = Hapup15;
		else Pab == cat ? Ecook = Hapup15 : Ecook = hapup10;
	} else if (Tcook == dry) {
		if (Ncook == soda)Pab == cat ? Ecook = Hapup5 : Ecook = sadup8;
		else if (Ncook == flor)Ecook = Sadup10;
		else if (Ncook == bread)Ecook = Hapup5;
		else if (Ncook == bananas)Ecook = Sadup10;
		else if (Ncook == cake)Pab == cat ? Ecook = sadup8 : Ecook = hapup10;
		else Ecook = none;
	} else Ecook = none;
	return Ecook;
}

int meal_all() { //总量
	return Camount;
}

int meal_nam() {	//菜名
	//cout <<"sod"<<Msod<<"|sul"<<Msul<<"|sug"<<Msug<<"|wat"<<Mwat<<"\n";//-调试用
	if (Msod > 0 && Mwat > 0) {
		if (Mwat <= Msod && Mflo > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug <= Msul && Msug <= Msod && Msug <= Mwat && Msug <= Mflo) {
			Ncook = bread; //面包：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量小于等于其他全部
		} else if (Mwat <= Msod && Mflo > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
			Ncook = cake; //蛋糕：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量大于其他全部成分
		} else if (Mwat > Msod) {
			Ncook = soda; //苏打水：水含量大于苏打含量
		} else if (Msod > Mwat) {
			Ncook = bananas; //带水的苏打 ：苏打含量大于水含量
		} else  Ncook = indefine; //不可名状
	} else if (Mflo > 0 && Mwat > 0) {
		if (Mwat <= Msod && Msod > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug <= Msul && Msug <= Msod && Msug <= Mwat && Msug <= Mflo) {
			Ncook = bread; //面包：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量小于等于其他全部
		} else if (Mwat <= Msod && Msod > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5 && Mflo > Msod && Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
			Ncook = cake; //蛋糕：水含量小于等于苏打含量、面粉含量大于零、水含量小于等于20% 、面粉含量大于小苏打含量、糖分含量大于其他全部成分
		} else Ncook = flor; //面糊：面粉含量和水含量都大于零
	} else {
		Ncook = indefine; //不可名状
	}
	return Ncook;
}

int meal_tas() { //菜品口味
	if (Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) { //糖分含量大于其他全部成分
		if (Msug >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vsweet; //当糖分含量大于全体50%时，口味过甜
		else Tcook = sweet;
	} else if (Msul > Msug && Msul > Msod && Msul > Mwat && Msul > Mflo) { //盐分含量大于其他全部成分
		if (Msul >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vsult; //当盐分含量大于全体50%时，口味过咸
		else Tcook = sult;
	} else if (Mwat > Msug && Mwat > Msod && Mwat > Msul && Mwat > Mflo) { //水分含量大于其他全部成分
		if (Mwat >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vmois; //当水分含量大于全体50%时，口味过湿
		else Tcook = mois;
	} else if (Msod > Msug && Msod > Mwat && Msod > Msul && Msod > Mflo) { //苏打含量大于其他全部成分
		Tcook = too_sod;
	} else if (Mflo > Msug && Mflo > Msod && Mflo > Msul && Mflo <= Mwat) { //面粉含量大于其他全部成分，且小于等于水分含量
		if (Mflo >= (Msug + Msul + Msod + Mwat + Mflo) / 2)Tcook = Vfloy; //当面粉含量大于全体50%时，口味过软
		else Tcook = floy;
	} else if (Mflo > 0 && Mwat == 0) { //面粉含量大于零，水含量等于0
		Tcook = dry;
	} else {
		Tcook = flat; //平淡
	}
	return Tcook;
}
