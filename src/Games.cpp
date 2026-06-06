#include "Games.h"
#include "GameState.h"
#include "Utils.h"
#include "i18n.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;

// ───────────────────────────────────────────
//  Internal helpers (forward declarations)
// ───────────────────────────────────────────

static void play_dice();
static void play_guess_number();
static void play_slot_machine();

// ───────────────────────────────────────────
//  Mini-game menu
// ───────────────────────────────────────────

void handle_minigames() {
    while (true) {
        hyphen(4);
        cout << tr(StrId::GAMES_TITLE) << "\n"
             << tr(StrId::GAMES_A_DICE) << "\n"
             << tr(StrId::GAMES_B_GUESS) << "\n"
             << tr(StrId::GAMES_C_SLOT) << "\n"
             << tr(StrId::GAMES_D_QUIT) << "\n";

        char gkey = getch();
        switch (gkey) {
        case 'A': case 'a': hyphen(); play_dice(); break;
        case 'B': case 'b': hyphen(); play_guess_number(); break;
        case 'C': case 'c': hyphen(); play_slot_machine(); break;
        case 'D': case 'd': return;
        default: cout << "\n"; notices::choose_again(); break;
        }
    }
}

// ───────────────────────────────────────────
//  1.  Dice game — roll 2d6, bet 1-50
// ───────────────────────────────────────────

static void play_dice() {
    int bet = 0;
    cout << tr_f(StrId::GAMES_BET_PROMPT, 50);
    cin >> bet; badint_clear();
    if (isbadint || bet < 1 || bet > 50) {
        cout << tr(StrId::GAMES_NO_MONEY) << "\n";
        pausers::pause();
        return;
    }
    if (bet > money) {
        cout << tr(StrId::GAMES_NO_MONEY) << "\n";
        pausers::pause();
        return;
    }

    money -= bet;

    int d1 = 1 + rand() % 6;
    int d2 = 1 + rand() % 6;
    int total = d1 + d2;

    cout << tr_f(StrId::GAMES_DICE_RESULT, d1, d2, total) << "\n";

    if (total > 7) {
        int win = bet * 2;
        money += win;
        cout << tr_f(StrId::GAMES_DICE_WIN, win) << "\n";
        hap += 2;
    } else if (total < 7) {
        cout << tr_f(StrId::GAMES_DICE_LOSE, bet) << "\n";
        sad += 1;
    } else {
        // total == 7 — push, refund the bet
        money += bet;
        cout << tr(StrId::GAMES_DICE_PUSH) << "\n";
    }

    pausers::pause();
}

// ───────────────────────────────────────────
//  2.  Guess the number (1-10), bet 1-30
// ───────────────────────────────────────────

static void play_guess_number() {
    int bet = 0;
    cout << tr_f(StrId::GAMES_BET_PROMPT, 30);
    cin >> bet; badint_clear();
    if (isbadint || bet < 1 || bet > 30) {
        cout << tr(StrId::GAMES_NO_MONEY) << "\n";
        pausers::pause();
        return;
    }
    if (bet > money) {
        cout << tr(StrId::GAMES_NO_MONEY) << "\n";
        pausers::pause();
        return;
    }

    money -= bet;

    int guess = 0;
    cout << tr(StrId::GAMES_GUESS_PROMPT);
    cin >> guess; badint_clear();
    if (isbadint || guess < 1 || guess > 10) { guess = 0; }

    int computer = 1 + rand() % 10;
    cout << tr_f(StrId::GAMES_GUESS_RESULT, computer) << "\n";

    if (guess == computer) {
        int win = bet * 5;
        money += win;
        cout << tr_f(StrId::GAMES_GUESS_WIN, win) << "\n";
        hap += 2;
    } else {
        cout << tr_f(StrId::GAMES_GUESS_LOSE, bet) << "\n";
        sad += 1;
    }

    pausers::pause();
}

// ───────────────────────────────────────────
//  3.  Slot machine, bet 1-20
// ───────────────────────────────────────────

static void play_slot_machine() {
    int bet = 0;
    cout << tr_f(StrId::GAMES_BET_PROMPT, 20);
    cin >> bet; badint_clear();
    if (isbadint || bet < 1 || bet > 20) {
        cout << tr(StrId::GAMES_NO_MONEY) << "\n";
        pausers::pause();
        return;
    }
    if (bet > money) {
        cout << tr(StrId::GAMES_NO_MONEY) << "\n";
        pausers::pause();
        return;
    }

    money -= bet;

    const char* symbols[] = {"Cherry", "Bell", "Seven", "Diamond", "BAR"};
    int r1 = rand() % 5;
    int r2 = rand() % 5;
    int r3 = rand() % 5;

    cout << tr_f(StrId::GAMES_SLOT_RESULT, symbols[r1], symbols[r2], symbols[r3]) << "\n";

    if (r1 == r2 && r2 == r3) {
        // All three match — jackpot
        int win = bet * 10;
        money += win;
        cout << tr_f(StrId::GAMES_SLOT_JACKPOT, win) << "\n";
        hap += 5;
    } else if (r1 == r2 || r2 == r3 || r1 == r3) {
        // Two match — small win
        int win = bet * 2;
        money += win;
        cout << tr_f(StrId::GAMES_SLOT_PAIR, win) << "\n";
        hap += 1;
    } else {
        cout << tr_f(StrId::GAMES_SLOT_LOSE, bet) << "\n";
        sad += 2;
    }

    pausers::pause();
}
