#ifndef DIGITALPET_GAMESTATE_H
#define DIGITALPET_GAMESTATE_H

#include <string>
#include <vector>
#include <map>

#include "Types.h"

// ── Global game state ──
// Declared extern here; defined in src/GameState.cpp

extern unsigned int days;
extern bool         died;
extern unsigned int turns;

extern std::string  cheating;
extern const bool   cheatable;
extern unsigned int Mopluse;
extern bool         Bband;         // random event #4 completed?

// ── Random event #2: investment ──
extern bool cheat;
extern bool loser;
extern bool invest;
extern unsigned int Iinvest;
extern unsigned int IINVEST;
extern unsigned int Dinvest;
extern float        Einvest;

// ── Prices ──
extern const unsigned int price_mouse;
extern const unsigned int price_slipper;
extern const unsigned int price_lone;
extern const unsigned int price_heartsaver;
extern const unsigned int price_pbutter;
extern const unsigned int price_mbutter;
extern const unsigned int price_sug;
extern const unsigned int price_sod;
extern const unsigned int price_wat;
extern const unsigned int price_flo;

// ── Ingredients ──
extern unsigned int storage[5];        // sugar, salt, soda, water, flour
extern unsigned int storageAdding[5];

// ── Backpack / cooked dishes ──
extern unsigned int Cid;
extern std::vector<std::string> backpackmeal;
extern std::vector<int>         backpackcalr;
extern std::vector<int>         backpackspend;
extern std::vector<int>         backpackall;
extern std::vector<float>       backpackeffect;

// ── Pet stats ──
extern std::string   name;
extern unsigned int  age;
extern unsigned int  hap;
extern unsigned int  max_hap;
extern unsigned int  sad;
extern unsigned int  max_sad;
extern bool          poo;
extern unsigned char w_poo;
extern bool          eat;
extern unsigned char w_eat;
extern bool          Pab;        // personality (dog / cat)
extern bool          gender;

extern unsigned int  lifespan;
extern unsigned int  Mlifespan;
extern unsigned int  Llifespan;
extern unsigned int  money;

// ── Derived constants ──
extern const char    pers;
extern const char    gens;
extern const char    events;

// ── Runtime vars ──
extern int           randomnum;
extern char          key;
extern bool          isbadint;

// ── Version ──
extern const std::string version;
extern const std::string phase;

// ── Theme ──
extern unsigned char theme;

// ─── Event #3 helpers ──
extern bool Phouse;
extern bool Pmouse;
extern int  Pmouse_plus;

// ─── Event #4 helpers ──
extern int  Bturns;
extern int  Bdays;
extern bool back;
extern bool BFS;
extern int  Msenting;

// ─── Investment UI ──
extern bool Vacheve;

// ─── Cooking globals ──
extern unsigned int cs;
extern unsigned int Camount;
extern unsigned int Msug, Msul, Msod, Mwat, Mflo;
extern unsigned int Mcalr;
extern unsigned int calr;
extern unsigned short Ncook;
extern unsigned short Tcook;
extern float Ecook;
extern std::map<unsigned int, std::string> meal;
extern std::map<unsigned int, std::string> Tmeal;
extern std::map<int, std::string> effects;

// ─── Borrowing / loan ──
extern bool          det;
extern int           Mdet;
extern int           Pdet;
extern float         Edet;
extern int           Ddet;
extern bool          Ldet;

// ─── Misc ──
extern bool Jcook;
extern bool wrongtype;
extern bool Dgm;
extern int  cheatmoney;
extern int  uglyprice;
extern int  gs;
extern int  CDSS;
extern unsigned int CTP;
extern bool  Lifespanup_turns;
extern int   Lifespanhap;

#endif // DIGITALPET_GAMESTATE_H
