#include "Utils.h"
#include "Types.h"
#include "i18n.h"

#include <iostream>
#include <limits>
#include <cstdlib>

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

using std::cout;
using std::cin;

// ── getch for Linux ──
#ifndef _WIN32
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    if (ch == EOF) { return 'Q'; }
    return ch;
}
#endif

// ── Screen ──
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ── Input validation ──
void badint() {
    isbadint = false;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        isbadint = true;
    }
    if (cin.eof()) {
        cin.clear();  // clear EOF flag so subsequent reads don't loop
        isbadint = true;
    }
}

void badint_clear() {
    isbadint = false;
    if (cin.eof()) {
        cin.clear();  // clear EOF flag to prevent infinite loop
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        isbadint = true;
        return;
    }
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        isbadint = true;
    }
}

// ── Decorative lines ──
void hyphen(int shan) {
    if      (shan == 0)   cout << "----------------------------------------\n";
    else if (shan == 1)   cout << "****************************************\n";
    else if (shan == 2)   cout << "++++++++++++++++++++++++++++++++++++++++\n";
    else if (shan == 3)   cout << "========================================\n";
    else if (shan == 4)   cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    else if (shan == 5)   cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
    else if (shan == 250) cout << "---Cheating Line-Cheating Line-Cheating Line-Cheating Line-Cheating Line---\n";
}

// ── Console colour ──
void colorc(int x) {
    if (theme == Tdef) {
#ifdef _WIN32
        if (x == red)   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        if (x == green) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        if (x == blue)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        if (x == white) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
        // ANSI escape sequences for Linux
        if (x == red)   std::cout << "\033[31m";
        if (x == green) std::cout << "\033[32m";
        if (x == blue)  std::cout << "\033[34m";
        if (x == white) std::cout << "\033[0m";
#endif
    }
}

void colorc_ansi(int x) {
    // Always use ANSI escape sequences (platform-independent, no theme dependency)
    if (x == red)   std::cout << "\033[31m";
    if (x == green) std::cout << "\033[32m";
    if (x == blue)  std::cout << "\033[34m";
    if (x == white) std::cout << "\033[0m";
}

// ── Pronoun ──
void refer(int refertype) {
    if (g_language == cn) {
        // Chinese: no spaces, use 他/她
        if      (refertype == nomin)  cout << (gender == M ? "他" : "她");
        else if (refertype == object) cout << (gender == M ? "他" : "她");
        else if (refertype == posses) cout << (gender == M ? "他的" : "她的");
    } else {
        // English: with spaces for word separation
        cout << " ";
        if      (refertype == nomin)  cout << (gender == M ? "he" : "she");
        else if (refertype == object) cout << (gender == M ? "him" : "her");
        else if (refertype == posses) cout << (gender == M ? "his" : "her");
        cout << " ";
    }
}

// ── Random events ──

// [[deprecated]] — kept for backward compatibility; prefer the named functions below.
int r_events(int sss, int Mranding, int Lranding) {
    if (sss == 0) {
        return 1 + rand() % (events);                       // random event type
    } else if (sss == 1) {
        return rand() % (pers - 1);                         // personality
    } else if (sss == 2) {
        return rand() % (gens - 1);                         // gender
    } else {
        return Lranding + rand() % (Mranding);              // general range
    }
}

int rand_event_type() {
    return 1 + rand() % (events);
}

int rand_personality() {
    return rand() % pers;
}

int rand_gender() {
    return rand() % gens;
}

int rand_range(int min, int max) {
    // Returns a random integer in [min, max] inclusive.
    // Equivalent to the old r_events(_, range, min) where range = max - min + 1.
    return min + rand() % (max - min + 1);
}

// ═══════════════════════════════════════════
//  pausers
// ═══════════════════════════════════════════

void pausers::pause(int screen) {
    cout << tr(StrId::GEN_PRESS_ANY_KEY) << "\n";
    getch();
    if (screen == 1) clear_screen();
}

void pausers::sure(bool besure) {
    if (besure) cout << tr(StrId::GEN_ARE_YOU_SURE);
    cout << tr(StrId::GEN_YES_NO) << "\n";
}

// ═══════════════════════════════════════════
//  options
// ═══════════════════════════════════════════

void options::color_choose() {
    cout << "\n" << tr(StrId::THEME_CHOOSE) << "\n";
    while (true) {
        key = getch();
        auto confirm = [&]() {
            pausers::sure();
            while (true) {
                key = getch();
                if (YES_KEY) return true;
                if (NO_KEY)  return false;
            }
        };
        if (key == 'A' || key == 'a') {
#ifdef _WIN32
            system("color 07");
#endif
            if (confirm()) { theme = Tdef; break; }
        } else if (key == 'B' || key == 'b') {
#ifdef _WIN32
            system("color df");
#endif
            if (confirm()) { theme = Tadv; break; }
        } else if (key == 'C' || key == 'c') {
#ifdef _WIN32
            system("color 8f");
#endif
            if (confirm()) { theme = Tele; break; }
        } else if (key == 'D' || key == 'd') {
#ifdef _WIN32
            system("color 70");
#endif
            if (confirm()) { theme = Tnor; break; }
        }
    }
}

void options::name_choose() {
    cout << "\n" << tr(StrId::NAME_PROMPT) << "\n";
    std::getline(cin, name);
    while (true) {
        if (name != "" && name != " " && name != "  " &&
            name != "   " && name != "    ") break;
        cout << tr(StrId::NAME_INPUT_AGAIN);
        std::getline(cin, name);
    }
    if (name == "毛茛" || name == "毛艮" || name == "morgan" || name == "Morgan")
        name = "比利";
    if (name == "Rick" || name == "Joker")
        name = "杀人犯";
    pausers::pause(1);
    cout << "'" << name << tr(StrId::NAME_YOU_THOUGHT) << "\n";
    if (name == "比利")                cout << tr(StrId::NAME_CRAZY) << "\n";
    else if (name == "杀人犯")         cout << tr(StrId::NAME_MURDEROUS) << "\n";
    else                               cout << tr(StrId::NAME_GOOD) << "\n";
}

// ═══════════════════════════════════════════
//  notices
// ═══════════════════════════════════════════

void notices::still_buy()          { cout << tr(StrId::NOTIF_STILL_BUY); pausers::sure(false); }
void notices::choose_again()       { cout << tr(StrId::GEN_CHOOSE_AGAIN) << "\n"; }
void notices::your_pet()           { cout << tr_f(StrId::GEN_YOUR_PET, name.c_str()); }
void notices::hap_plus(int hapin)    { colorc(green); cout << tr_f(StrId::NOTIF_HAP_PLUS, hapin) << "\n";  colorc(white); }
void notices::hap_minus(int hapout)  { colorc(red);   cout << tr_f(StrId::NOTIF_HAP_MINUS, hapout) << "\n"; colorc(white); }
void notices::lifespan_plus(int v)   { colorc(red);   cout << tr_f(StrId::NOTIF_LIFESPAN_PLUS, v) << "\n"; colorc(white); }
void notices::lifespan_minus(int v)  { colorc(green); cout << tr_f(StrId::NOTIF_LIFESPAN_MINUS, v) << "\n"; colorc(white); }
void notices::sad_plus(int v)        { colorc(red);   cout << tr_f(StrId::NOTIF_SAD_PLUS, v) << "\n";  colorc(white); }
void notices::sad_minus(int v)       { colorc(green); cout << tr_f(StrId::NOTIF_SAD_MINUS, v) << "\n";  colorc(white); }
void notices::money_plus(int v)      { colorc(green); cout << tr_f(StrId::NOTIF_MONEY_PLUS, v) << "\n";        colorc(white); }
void notices::money_minus(int v)     { colorc(red);   cout << tr_f(StrId::NOTIF_MONEY_MINUS, v) << "\n";        colorc(white); }
void notices::money_not()            { colorc(red);   cout << tr(StrId::NOTIF_MONEY_NOT) << "\n"; colorc(white); }
void notices::money_have()           { colorc(blue);  cout << tr_f(StrId::NOTIF_MONEY_HAVE, money) << "\n"; colorc(white); }
void notices::bought_success()       { colorc(blue);  cout << tr(StrId::NOTIF_BOUGHT_SUCCESS) << "\n";     colorc(white); }

// ═══════════════════════════════════════════
//  Pet initialisation
// ═══════════════════════════════════════════

void per() {
    cout << tr_f(StrId::PER_REMEMBER, name.c_str());
    randomnum = rand_personality();
    Pab = (randomnum != 0) ? cat : dog;
    if (Pab == dog) {
        cout << tr(StrId::PER_DOG_SCENE1);
        refer(posses);
        cout << tr(StrId::PER_DOG_SCENE2);
        refer(object);
        cout << tr(StrId::PER_DOG_SCENE3);
    } else {
        cout << tr(StrId::PER_CAT_SCENE1);
        refer(object);
        cout << tr(StrId::PER_CAT_SCENE2);
        refer(object);
        cout << tr(StrId::PER_CAT_SCENE3);
    }
    cout << tr(StrId::PER_NAMED);
    refer(object);
    cout << ".\n";
}

void r_lifespan() {
    if (Pab == cat)
        lifespan = 25 + rand() % (40 - 25);   // cat: 25-39
    else
        lifespan = 20 + rand() % (45 - 20);   // dog: 20-44
}
