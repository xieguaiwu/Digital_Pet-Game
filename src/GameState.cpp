#include "GameState.h"

// ── Core game state ──
unsigned int days    = 1;
bool         died    = false;
unsigned int turns   = 1;
std::string  cheating;
const bool   cheatable = false;
unsigned int Mopluse;
bool         Bband   = false;

// ── Investment ──
bool cheat  = false;
bool loser  = false;
bool invest = false;
unsigned int Iinvest;
unsigned int IINVEST;
unsigned int Dinvest;
float        Einvest;

// ── Prices ──
const unsigned int price_mouse      = 90;
const unsigned int price_slipper    = 20;
const unsigned int price_lone       = 10;
const unsigned int price_heartsaver = 10000;
const unsigned int price_pbutter    = 35;
const unsigned int price_mbutter    = 50;
const unsigned int price_sug        = 8;
const unsigned int price_sod        = 9;
const unsigned int price_wat        = 0;
const unsigned int price_flo        = 6;

// ── Ingredients ──
unsigned int storage[5]      = {0, 0, 0, 0, 0};
unsigned int storageAdding[5]= {0, 0, 0, 0, 0};

// ── Backpack ──
unsigned int Cid = 0;
std::vector<std::string> backpackmeal;
std::vector<int>         backpackcalr;
std::vector<int>         backpackspend;
std::vector<int>         backpackall;
std::vector<float>       backpackeffect;

// ── Pet stats ──
std::string   name    = "PET";
unsigned int  age     = 0;
unsigned int  hap     = 50;
unsigned int  max_hap = 100;
unsigned int  sad     = 0;
unsigned int  max_sad = 50;
bool          poo     = false;
unsigned char w_poo;
bool          eat     = false;
unsigned char w_eat;
bool          Pab;       // dog / cat
bool          gender;

unsigned int  lifespan;
unsigned int  Mlifespan;
unsigned int  Llifespan;
unsigned int  money    = 50;

const char    pers   = 2;
const char    gens   = 2;
const char    events = 6;

int    randomnum;
char   key;
bool   isbadint;

const std::string version = "0.2.3";
const std::string phase   = "alpha";

unsigned char theme;

// ── Event #3 helpers ──
bool Phouse = false;
bool Pmouse = false;
int  Pmouse_plus;

// ── Event #4 helpers ──
int  Bturns = 1;
int  Bdays  = 1;
bool back   = false;
bool BFS    = false;
int  Msenting;

// ── Investment UI ──
bool Vacheve = false;

// ── Cooking globals ──
unsigned int cs;
unsigned int Camount;
unsigned int Msug, Msul, Msod, Mwat, Mflo;
unsigned int Mcalr;
unsigned int calr;
unsigned short Ncook;
unsigned short Tcook;
float Ecook;
std::map<unsigned int, std::string> meal;
std::map<unsigned int, std::string> Tmeal;
std::map<int, std::string> effects;

// ── Loan ──
bool          det   = false;
int           Mdet;
int           Pdet;
float         Edet;
int           Ddet;
bool          Ldet  = false;

// ── Misc ──
bool Jcook       = false;
bool wrongtype;
bool Dgm         = false;
int  cheatmoney;
int  uglyprice;
int  gs;
int  CDSS        = 0;
unsigned int CTP;
bool  Lifespanup_turns = false;
int   Lifespanhap;     // initialised in starter_notice (60..85)
