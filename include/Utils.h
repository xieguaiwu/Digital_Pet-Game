#ifndef DIGITALPET_UTILS_H
#define DIGITALPET_UTILS_H

#include <string>
#include "GameState.h"

// ── Platform detection ──
//   _WIN32   → Windows (conio.h + system("color"))
//   __APPLE__ → macOS (termios + ANSI escape codes)
//   else     → Linux (termios + ANSI escape codes)
//
// ── Platform-specific input ──
#ifdef _WIN32
#include <conio.h>
#else
int getch();
#endif

// ── Screen ──
void clear_screen();

// ── Input validation ──
void badint();        // legacy; prefer badint_clear()
void badint_clear();  // handles EOF correctly

// ── Decorative lines ──
void hyphen(int shan = 0);

// ── Coloured console output ──
void colorc(int x);

// ── Pronoun helper ──
void refer(int refertype);

// ── Random event generators ──
int r_events(int sss = 0, int Mranding = 0, int Lranding = 0);  // [[deprecated]]  use named functions below
int rand_event_type();                     // sss=0: random event 1..6
int rand_personality();                    // sss=1: dog / cat
int rand_gender();                         // sss=2: M / F
int rand_range(int min, int max);          // sss>=3: random int in [min, max] inclusive

// ── Console colour (ANSI, always available) ──
void colorc_ansi(int x);

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
