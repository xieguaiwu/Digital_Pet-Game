#include "Events.h"
#include "EventConfig.h"
#include "GameState.h"
#include "Utils.h"
#include "Cooking.h"
#include "i18n.h"
#include "Diary.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;

// ═══════════════════════════════════════════
//  TV ASCII art (moved from event_print.h)
// ═══════════════════════════════════════════

void Btv1() {
    cout << "        \\         /\n"
            "         \\       /\n"
            "__________________________\n"
            "|                        |\n"
            "|         __________     |\n"
            "|         |・|  |・|     |\n"
            "|         |   _    |     |\n"
            "|         |__|_|___|     |\n"
            "|            |  |        |\n"
            "|            |  |        |\n"
            "|____________|__|________|\n"
            "|________________________|\n"
            ""
            << tr(StrId::TV1_MAN_ROARING) << "\n";
}

void Btv2() {
    cout << "        \\         /\n"
            "         \\       /\n"
            "__________________________\n"
            "|             ____       |\n"
            "|         ____|__|___    |\n"
            "|         |___|  |___|   |\n"
            "|             |  |       |\n"
            "|         ____|__|__     |\n"
            "|         \\__/| \\__/     |\n"
            "|             |  |       |\n"
            "|_____________|__|_______|\n"
            "|________________________|\n"
            ""
            << tr(StrId::TV2_GLASSES_AD) << "\n";
}

void Btv3() {
    cout << "        \\         /\n"
            "         \\       /\n"
            "__________________________\n"
            "|                        |\n"
            "|         __________     |\n"
            "|         |_|  |_| |     |\n"
            "|         |        |     |\n"
            "|         |________|     |\n"
            "|        |          |    |\n"
            "|       |            |   |\n"
            "|_______|____________|___|\n"
            "|________________________|\n"
            ""
            << tr(StrId::TV3_OTHERS_HELL) << "\n";
}

void Btv4() {
    cout << "        \\         /\n"
            "         \\       /\n"
            "__________________________\n"
            "| ______        _________|\n"
            "||・||・|       |_|  |_| |\n"
            "||      |       |        |\n"
            "||______|     __|________|\n"
            "|_|___|__    |          ||\n"
            "|       |   |            |\n"
            "|_______|___|____________|\n"
            "|________________________|\n"
            ""
            << tr(StrId::TV4_FRENCH_DEBATE) << "\n";
}

// ═══════════════════════════════════════════
//  Random event #1 — money gift
// ═══════════════════════════════════════════

void r1() {
    randomnum = rand_range(0, 34);
    if (randomnum != 0) {
        cout << tr_f(StrId::EVT1_MONEY_FOUND, randomnum) << "\n";
        money += randomnum;
        pausers::pause();
        diary_add(tr(StrId::DIARY_ACT_EVENT1));
    }
}

// ═══════════════════════════════════════════
//  Random event #2 — investment
// ═══════════════════════════════════════════

void handle_investment_deposit() {
    cout << tr(StrId::EVT2_SIGN_NAME) << "\n";
    invest = true;
    while (true) {
        cout << tr(StrId::EVT2_INPUT_AMOUNT);
        notices::money_have();
        cin >> Iinvest;
        badint_clear();
        if (Iinvest > money) {
            cout << "You don't have that much money! All you have is $ "
                 << money << "!\n\n";
        } else if (!isbadint && Iinvest > 0) {
            break;
        } else if (!isbadint && Iinvest == 0) {
            cout << tr(StrId::EVT2_GIVE_UP_HAIR) << "\n";
            break;
        }
    }
    if (Iinvest != 0) {
        cout << tr_f(StrId::EVT2_INVESTED, Iinvest) << "\n";
        if (Iinvest == money) {
            cout << tr(StrId::EVT2_ALL_MONEY) << "\n";
            notices::hap_plus(2);
            notices::sad_minus(3);
            hap += 2;
            sad -= 3;
        }
        money -= Iinvest;
        IINVEST = Iinvest;
        Dinvest = rand_range(1, 2) + days;
        invest = true;
    } else {
        cout << tr(StrId::EVT2_RETARD) << "\n";
        invest = false;
    }
}

void r2() {
    notices::your_pet();
    cout << tr_f(StrId::EVT2_PAPER_TOP, name.c_str()) << "\n";
    pausers::sure();
    key = getch();
    if (YES_KEY) {
        handle_investment_deposit();
    } else {
        invest = false;
        cout << tr(StrId::EVT2_RETARD) << "\n";
    }
    diary_add(tr(StrId::DIARY_ACT_EVENT2));
    cout << "\n\n";
}

// ═══════════════════════════════════════════
//  Random event #3 — product promotion
// ═══════════════════════════════════════════

static void handle_buy_10_dollars() {
    if (money >= 10) {
        money -= 10;
        cout << tr_f(StrId::EVT3_BUY_10, randomnum);
        if (randomnum > 10)  cout << "What a silly great deal!\n";
        if (randomnum == 10) cout << "What a balanced profit!\n";
        if (randomnum < 10)  cout << "What a foolish decision!\n";
        money += randomnum;
    } else {
        notices::money_not();
    }
}

static void handle_opening_door() {
    cout << "You open the door, just to realize that";
    randomnum = rand_range(1, 5);
    if (randomnum == 2) {
        cout << tr(StrId::EVT3_ATE_WINDOW) << "\n";
    } else {
        cout << tr(StrId::EVT3_ENTERED) << "\n";
    }
    poo = true;
}

static void handle_eating_door() {
    cout << tr_f(StrId::EVT3_EATS_DOOR, name.c_str()) << "\n";
    notices::hap_plus(2);
    notices::sad_minus(3);
    hap += 2;
    sad -= 3;
    poo = true;
}

void r3() {
    cout << tr(StrId::EVT3_RAN_OUT) << "\n"
         << tr_f(StrId::EVT3_KNOCKING, name.c_str()) << "\n";
    cout << tr(StrId::EVT3_OPEN_DOOR_Q) << "\n";
    pausers::sure();
    key = getch();
    if (YES_KEY) handle_opening_door();
    else         handle_eating_door();
    cout << "\n\n" << name << tr(StrId::EVT3_FOUND_ITEMS);
    refer(nomin);
    cout << "found:\n";

    // BUG C7: save scenario in local var so nested rand_range doesn't overwrite it
    int scenario = rand_range(1, 5);
    if (scenario == 1 || scenario == 2) {
        cout << "A) ";
        // BUG C7: use local var; BUG H6: cap range at 1-18 (EV ≈ -$0.5, slight house edge)
        int money_amount = rand_range(1, 18);
        randomnum = money_amount;  // for handle_buy_10_dollars() which reads global randomnum
        cout << "$ " << money_amount << " Price: $10\nB) Don't buy anything\n";
        key = getch();
        if (key == 'A' || key == 'a') handle_buy_10_dollars();
    }
    else if (scenario == 3 || scenario == 4) {
        cout << tr_f(StrId::EVT3_TOY_MOUSE_LABEL, price_mouse) << "\n"
             << tr_f(StrId::EVT3_SLIPPER_LABEL, price_slipper) << "\n"
             << tr_f(StrId::EVT3_HEART_SAVER, price_heartsaver) << "\n"
             << tr(StrId::EVT3_DONT_BUY) << "\n";
        while (true) {
            key = getch();
            if (key == 'A' || key == 'a') {
                if (money >= 90 && !Pmouse) {
                    money -= 90;
                    cout << tr(StrId::EVT3_BOUGHT_MOUSE) << "\n";
                    Pmouse = true;
                } else if (money >= 90 && Pmouse) {
                    cout << tr(StrId::EVT3_ALREADY_MOUSE) << "\n";
                } else {
                    notices::money_not();
                }
                break;
            } else if (key == 'B' || key == 'b') {
                if (money >= 20 && !Phouse) {
                    money -= 20;
                    cout << tr(StrId::EVT3_BOUGHT_SLIPPER) << "\n";
                    Phouse = true;
                } else if (money >= 20 && Phouse) {
                    cout << tr(StrId::EVT3_ALREADY_SLIPPER) << "\n";
                } else {
                    notices::money_not();
                }
                break;
            } else if (key == 'C' || key == 'c') {
                if (money >= 10000) {
                    money -= 10000;
                    pausers::sure();
                    key = getch();
                    if (YES_KEY) {
                        cout << tr(StrId::EVT3_MONSTER) << "\n";
                        hap = 0;
                        sad = max_sad;
                    } else {
                        cout << tr(StrId::EVT3_SCAMMED) << "\n";
                    }
                } else {
                    notices::money_not();
                }
                break;
            } else if (key == 'D' || key == 'd') {
                break;
            }
        }
    }
    else if (scenario == 5) {
        cout << tr_f(StrId::EVT3_LONELINESS, price_lone) << "\n"
             << tr(StrId::EVT3_DONT_BUY) << "\n";
        while (true) {
            key = getch();
            if (key == 'A' || key == 'a') {
                if (money >= 10) {
                    money -= 10;
                    cout << tr(StrId::EVT3_BOUGHT_LONE) << "\n";
                } else {
                    notices::money_not();
                }
                break;
            } else if (key == 'B' || key == 'b') {
                break;
            }
        }
    }
    diary_add(tr(StrId::DIARY_ACT_EVENT3));
    hyphen(4);
}

// ═══════════════════════════════════════════
//  Random event #4 — rock band
// ═══════════════════════════════════════════

void Bback() {
    back = true;
    cout << tr(StrId::EVT4_PERFORMANCE) << "\n";
    pausers::pause();
    cout << "Tears run out your eyes. Few weeks later, your pet knocks on the door again, and";
    refer(nomin);
    cout << tr(StrId::EVT4_GREAT_PERF) << "\n";
    randomnum = rand_range(1, 5);
    if (randomnum == 5) {
        BFS = true;
        BFS_days = 0;  // BUG H7: reset expiration counter when BFS activates
        randomnum = rand_range(200, 3199);
        cout << tr(StrId::EVT4_GREAT_PERF) << "\n";
    } else {
        randomnum = rand_range(100, 2099);
    }
    money += randomnum;
    cout << tr_f(StrId::EVT4_EARNED, randomnum) << "\n";
    pausers::pause();
    cout << tr(StrId::EVT4_BACK_LIFE) << "\n";
    hyphen(4);
}

void Binteract() {
    // BUG C5: while loop replaces recursion to prevent stack overflow
    while (true) {
        // BUG C6: allow Q to quit the band event
        if (key == 'Q' || key == 'q') {
            back = true;
            return;
        }
        if (key == 'T' || key == 't') {
            cout << tr(StrId::EVT4_OPEN_TV) << "\n";
            pausers::pause(1);
            // BUG H2: changed from rand_range(1,2) to (1,4) so Btv3/Btv4 are reachable
            randomnum = rand_range(1, 4);
            if      (randomnum == 1) Btv1();
            else if (randomnum == 2) Btv2();
            else if (randomnum == 3) Btv3();
            else if (randomnum == 4) Btv4();

            randomnum = rand_range(1, 4);
            if (randomnum == 2) {
                cout << tr(StrId::EVT4_SWITCHING) << "\n";
                pausers::pause();
                Bback();
            } else {
                cout << tr(StrId::EVT4_NO_INFO) << "\n";
                pausers::pause(1);
            }
            return;  // exit loop after watching TV
        }
        hyphen(3);
        cout << "\n";
        notices::choose_again();
        cout << tr_f(StrId::EVT4_WATCH_TV_HINT, 2 - Bturns) << "\n";
        key = getch();
    }
}

void band_days() {
    hyphen(2);
    cout << tr_f(StrId::EVT4_BAND_DAY, Bdays) << "\n";
    while (Bturns < 2) {
        cout << "\n";
        notices::choose_again();
        cout << tr_f(StrId::EVT4_WATCH_TV_HINT, 2 - Bturns) << "\n";
        key = getch();
        // BUG C6: allow Q to quit the band event
        if (key == 'Q' || key == 'q') { back = true; break; }
        Binteract();
        if (back) break;
        ++Bturns;
    }
    ++Bdays;
    Bturns = 1;
}

void r4() {
    // BUG C6: Bband moved to AFTER the event completes (was prematurely at function start)
    cout << tr(StrId::EVT4_ROCK_DAYS) << "\n"
         << "You often hear some words like 'rape' from " << name
         << "'s mouse (don't ask me how)\n";
    pausers::pause();
    cout << "One day, your pet told you through an unimaginable way that";
    refer(nomin);
    cout << tr(StrId::EVT4_BAND_START) << "\n";
    pausers::pause();
    eat = false;
    poo = false;
    cout << "Before";
    refer(nomin);
    cout << tr(StrId::EVT4_LAST_FEED1);
    refer(nomin);
    cout << tr(StrId::EVT4_LAST_FEED2);
    refer(posses);
    cout << tr(StrId::EVT4_LEAVE) << "\n";
    pausers::pause();
    hyphen(4);
    while (true) {
        // BUG C6: allow Q to quit and escape the band event loop
        if (key == 'Q' || key == 'q') { back = true; break; }
        band_days();
        if (back) break;
    }
    Bband = true;  // BUG C6: only mark complete after event finishes (not softlocked)
    diary_add(tr(StrId::DIARY_ACT_EVENT4));
}

// ═══════════════════════════════════════════
//  Random event #5 — ingredient gift
// ═══════════════════════════════════════════

void r5() {
    randomnum = rand_range(1, 5);
    cout << tr(StrId::EVT5_BROUGHT_BACK);
    int qty = rand_range(1, 35);
    if (randomnum == 1) {
        cout << qty << " grams of sugar!\n";
        storage[0] += qty;
    } else if (randomnum == 2) {
        cout << qty << " grams of salt!\n";
        storage[1] += qty;
    } else if (randomnum == 3) {
        cout << qty << " grams of soda!\n";
        storage[2] += qty;
    } else if (randomnum == 4) {
        cout << qty << " milliliters of water!\n";
        if (storage[3] + qty <= 1000) storage[3] += qty;
    } else if (randomnum == 5) {
        cout << qty << " grams of flour!\n";
        storage[4] += qty;
    }
    pausers::pause();
    diary_add(tr(StrId::DIARY_ACT_EVENT5));
}

// ═══════════════════════════════════════════
//  Random event dispatcher
// ═══════════════════════════════════════════

void r_e() {
    if (days < 1) return;
    randomnum = rand_event_type();
    if (randomnum > events) return;
    if      (randomnum == 1)                                 r1();
    else if (randomnum == 2) { if (!invest && money > 0)     r2(); }
    else if (randomnum == 3)                                 r3();
    else if (randomnum == 4) { if (!Bband)                   r4(); }
    else if (randomnum == 5)                                 r5();
}

// ── New config-based dispatcher ──
void r_e_v2() {
    if (days < 1) return;
    int idx = EventConfig::select_random_event();
    if (idx < 0) return;
    EventConfig::get(idx).execute();
}
