#include "Utils.h"
#include "Types.h"

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
#endif
    }
}

// ── Pronoun ──
void refer(int refertype) {
    cout << " ";
    if (refertype == nomin)  gender == M ? cout << "he" : cout << "she";
    else if (refertype == object) gender == M ? cout << "him" : cout << "her";
    else if (refertype == posses) gender == M ? cout << "his" : cout << "her";
    cout << " ";
}

// ── Random events ──
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

// ═══════════════════════════════════════════
//  pausers
// ═══════════════════════════════════════════

void pausers::pause(int screen) {
    cout << " (Press any key to continue...)\n";
    getch();
    if (screen == 1) clear_screen();
}

void pausers::sure(bool besure) {
    if (besure) cout << "Are you sure?";
    cout << " (Press Y to confirm, and press N to refuse)\n";
}

// ═══════════════════════════════════════════
//  options
// ═══════════════════════════════════════════

void options::color_choose() {
    cout << "\nChoose your theme color:\n"
            "A. Default theme (black background + white words)\n"
            "B. Adventure theme (purple background + white words)\n"
            "C. Elegant theme (grey background + light white words)\n"
            "D. Normal theme (white background + black words)\n";
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
            system("color 07");
            if (confirm()) { theme = Tdef; break; }
        } else if (key == 'B' || key == 'b') {
            system("color df");
            if (confirm()) { theme = Tadv; break; }
        } else if (key == 'C' || key == 'c') {
            system("color 8f");
            if (confirm()) { theme = Tele; break; }
        } else if (key == 'D' || key == 'd') {
            system("color 70");
            if (confirm()) { theme = Tnor; break; }
        }
    }
}

void options::name_choose() {
    cout << "\nInput the name of your digital pet:\n";
    std::getline(cin, name);
    while (true) {
        if (name != "" && name != " " && name != "  " &&
            name != "   " && name != "    ") break;
        cout << "Please input again:";
        std::getline(cin, name);
    }
    if (name == "毛茛" || name == "毛艮" || name == "morgan" || name == "Morgan")
        name = "比利";
    if (name == "Rick" || name == "Joker")
        name = "杀人犯";
    pausers::pause(1);
    cout << "'" << name << "' you thought.";
    if (name == "比利")                cout << "What a crazy name.\n";
    else if (name == "杀人犯")         cout << "This sounds murderous.\n";
    else                               cout << "What a good name this is.\n";
}

// ═══════════════════════════════════════════
//  notices
// ═══════════════════════════════════════════

void notices::still_buy()          { cout << "Continue to buy?"; pausers::sure(false); }
void notices::choose_again()       { cout << "Please choose again!\n"; }
void notices::your_pet()           { cout << "Your pet " << name << " "; }
void notices::hap_plus(int hapin)    { colorc(green); cout << "Happiness [+" << hapin << "]!\n";  colorc(white); }
void notices::hap_minus(int hapout)  { colorc(red);   cout << "Happiness [-" << hapout << "]!\n"; colorc(white); }
void notices::lifespan_plus(int v)   { colorc(red);   cout << "Happiness needed to increase lifespan [+" << v << "]!\n"; colorc(white); }
void notices::lifespan_minus(int v)  { colorc(green); cout << "Happiness needed to increase lifespan [-" << v << "]!\n"; colorc(white); }
void notices::sad_plus(int v)        { colorc(red);   cout << "Sadness [+" << v << "]!\n";  colorc(white); }
void notices::sad_minus(int v)       { colorc(green); cout << "Sadness [-" << v << "]!\n";  colorc(white); }
void notices::money_plus(int v)      { colorc(green); cout << "$ [+" << v << "]!\n";        colorc(white); }
void notices::money_minus(int v)     { colorc(red);   cout << "$ [-" << v << "]!\n";        colorc(white); }
void notices::money_not()            { colorc(red);   cout << "Sorry, but you don't have enough money!\n"; colorc(white); }
void notices::money_have()           { colorc(blue);  cout << "You have $ " << money << " !\n"; colorc(white); }
void notices::bought_success()       { colorc(blue);  cout << "Bought successfully!\n";     colorc(white); }

// ═══════════════════════════════════════════
//  Pet initialisation
// ═══════════════════════════════════════════

void per() {
    cout << "You remember the day you met " << name << ":";
    randomnum = r_events(1);
    Pab = (randomnum != 0);
    if (Pab == dog) {
        cout << "You saw a puppy at a pet store. You liked";
        refer(posses);
        cout << " mad look, so you took";
        refer(object);
        cout << "home.";
    } else {
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

void r_lifespan() {
    if (Pab == cat)
        lifespan = 20 + rand() % (40 - 20);   // cat: 2–4 years (converted to days)
    else
        lifespan = 15 + rand() % (50 - 15);   // dog: 1.5–5 years
}
