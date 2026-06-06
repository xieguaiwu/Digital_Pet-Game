#ifndef DIGITALPET_UTILS_H
#define DIGITALPET_UTILS_H

#include <string>
#include "GameState.h"

// ── Platform-specific input ──
#ifdef _WIN32
#include <conio.h>
#else
int getch();
#endif

// ── Screen ──
void clear_screen();

// ── Input validation ──
void badint();

// ── Decorative lines ──
void hyphen(int shan = 0);

// ── Coloured console output ──
void colorc(int x);

// ── Pronoun helper ──
void refer(int refertype);

// ── Random event generator ──
int r_events(int sss = 0, int Mranding = 0, int Lranding = 0);

// ── Utility classes ──

class pausers {
public:
    static void pause(int screen = 0);
    static void sure(bool besure = true);
};

class options {
public:
    static void color_choose();
    static void name_choose();
};

class notices {
public:
    static void still_buy();
    static void choose_again();
    static void your_pet();
    static void hap_plus(int hapin);
    static void hap_minus(int hapout);
    static void lifespan_plus(int lifespanin);
    static void lifespan_minus(int lifespanout);
    static void sad_plus(int sadin);
    static void sad_minus(int sadout);
    static void money_plus(int monin);
    static void money_minus(int monout);
    static void money_not();
    static void money_have();
    static void bought_success();
};

// ── Pet initialisation ──
void per();
void r_lifespan();

#endif // DIGITALPET_UTILS_H
