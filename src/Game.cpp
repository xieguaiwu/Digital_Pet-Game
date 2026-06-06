#include "GameState.h"
#include "Utils.h"
#include "Cooking.h"
#include "Events.h"
#include "EventConfig.h"
#include "RecipeDB.h"
#include "Money.h"
#include "Body.h"
#include "i18n.h"
#include "Games.h"
#include "Diary.h"

#include <iostream>
#include <cstdlib>
#include <string>

using std::cout;
using std::cin;

// ═══════════════════════════════════════════
//  Forward declarations
// ═══════════════════════════════════════════

static void o_days();
static void starter_notice();
static void death();
static void interact();
static void notice();
static void re_ini();
static void e_hap();
static void e_sad();
static void e_poo();
static void e_eat();
static void e_age();

// ═══════════════════════════════════════════
//  Emotion functions
// ═══════════════════════════════════════════

static void e_poo() {
    if (w_poo > 10) w_poo = 10;      // [FIX] was `==`, now assignment
    if (w_poo > 5) {
        if (w_poo < 8) {
            hap -= 3; sad += 2;
        } else {
            hap -= 5; sad += 4;
        }
    }
}

static void e_eat() {
    if (w_eat > 5) w_eat = 5;
    if (w_eat > 2) {
        if (w_eat < 4) {
            hap -= 3; sad += 3;
        } else {
            hap -= 5; sad += 5;
        }
    }
}

static void e_age() {
    if (days != 0 && days % 10 == 0) {
        ++age;
        notices::your_pet();
        cout << tr(StrId::PET_OLDER) << "\n";
    }
}

static void e_sad() {
    if (sad < 0) sad = 0;
    if (sad > max_sad) sad = max_sad;
    if (sad < max_sad) {
        if (sad > 25) {
            if (sad < 38) { sad += 2; hap -= 4; }
            else          { sad += 4; hap -= 7; }
        }
    } else {
        notices::your_pet();
        cout << tr(StrId::PET_DEPRESSED);
        refer(nomin);
        cout << tr(StrId::PET_SUICIDE) << "\n";
        death();
    }
}

static void e_hap() {
    if (hap < 0) hap = 0;
    if (hap > max_hap) hap = max_hap;
    if (hap < max_hap) {
        if (hap > 30 && hap < 51) {
            // Mild recovery zone: slow happiness gain, slight sadness reduction
            hap += 1; sad -= 1;
        } else if (hap > 50 && hap < 76) {
            // Moderate recovery zone
            hap += 3; sad -= 3;
        } else if (hap >= 76) {
            // High happiness zone
            hap += 4; sad -= 5;
            if (hap >= Lifespanhap && sad <= 15) {
                if ((turns == 2 || turns == 4 || turns == 6 || turns == 8)
                    && !Lifespanup_turns) {
                    cout << tr(StrId::LIFESPAN_INC_1) << "\n";
                    ++lifespan;
                    Lifespanup_turns = true;
                } else {
                    Lifespanup_turns = false;
                }
            }
        }
    } else {
        // Already at max happiness
        sad -= 5;
    }
}

// ═══════════════════════════════════════════
//  Death
// ═══════════════════════════════════════════

static void death() {
    hyphen();
    cout << "Your pet " << name << tr(StrId::PET_LIFE_OF)
         << age << tr(StrId::PET_YEARS_AND);
    refer(nomin);
    cout << tr(StrId::PET_HAD_THROUGH) << days << tr(StrId::PET_DAYS_PERIOD) << "\n";
    cout << tr(StrId::PET_WHEN_DIE) << name << tr(StrId::PET_GOING_TO_DIE);
    if (poo) { refer(nomin); cout << tr(StrId::PET_WANTED_DEFECATE) << "\n"; }
    if (eat) { refer(nomin); cout << tr(StrId::PET_STILL_HUNGRY) << "\n"; }
    cout << tr(StrId::PET_WHEN_DIE);
    refer(nomin);
    cout << tr(StrId::PET_GOING_TO_DIE) << name << " ";
    if (sad >= 38 && sad < 42 && hap < 50)
        cout << tr(StrId::PET_WAS_BIT_SAD) << "\n";
    else if (sad >= 42 && hap < 50)
        cout << tr(StrId::PET_WAS_VERY_DEPRESSED) << "\n";
    else if (hap >= 50 && hap < 76 && sad < 38)
        cout << tr(StrId::PET_WAS_QUITE_HAPPY) << "\n";
    else if (hap >= 76 && sad < 38)
        cout << tr(StrId::PET_WAS_VERY_HAPPY) << "\n";
    else if (hap >= 50 && sad >= 38)
        cout << tr(StrId::PET_WAS_CONFUSED) << "\n";
    died = true;
    pausers::pause(1);
}

// ═══════════════════════════════════════════
//  Notice / action menu
// ═══════════════════════════════════════════

static void notice() {
    cout << "\n" << tr(StrId::NOTICE_Q) << "\n"
         << tr(StrId::NOTICE_F) << "\n"
         << tr(StrId::NOTICE_I) << "\n"
         << tr(StrId::NOTICE_C) << "\n"
         << tr(StrId::NOTICE_S) << "\n"
         << tr(StrId::NOTICE_M) << "\n"
         << tr(StrId::NOTICE_B) << "\n"
         << tr(StrId::NOTICE_O) << "\n";
#ifdef _WIN32
    cout << tr(StrId::NOTICE_X) << "\n";
#endif
    cout << tr(StrId::GAMES_KEY_HINT) << "\n"
         << tr(StrId::DIARY_KEY_HINT) << "\n";
    if (invest) {
        cout << tr(StrId::NOTICE_V) << "\n";
        Vacheve = true;
    }
    cout << tr(StrId::TURNS_8_NOTICE) << "\n"
         << tr_f(StrId::TURNS_LEFT, 9 - turns) << "\n";
}

// ═══════════════════════════════════════════
//  Interaction handlers
// ═══════════════════════════════════════════

static void handle_quit_game() {
    cout << tr(StrId::ACT_QUIT_GAME) << "\n";
    pausers::pause(4);
}

static void handle_feed_pet() {
    cout << tr(StrId::ACT_FEED_PET) << "\n";
    w_eat = 0;
    if (eat) { hap += 2; notices::hap_plus(2); }
    eat = false;
    diary_add(tr(StrId::DIARY_ACT_FED));
    pausers::pause();
}

static void handle_defecate() {
    cout << tr_f(StrId::ACT_LET_PET, name.c_str()) << tr(StrId::ACT_DEFECATE_PERIOD) << "\n";
    w_poo = 0;
    if (poo) { ++hap; notices::hap_plus(1); }
    poo = false;
    diary_add(tr(StrId::DIARY_ACT_DEFECATED));
    pausers::pause();
}

static void handle_pat() {
    cout << tr_f(StrId::ACT_PAT_PET, name.c_str()) << ".\n";
    hap += 4; sad -= 3;
    notices::hap_plus(4); notices::sad_minus(3);
    diary_add(tr(StrId::DIARY_ACT_PATTED));
    pausers::pause();
}

static void handle_quit_interaction_menu() {
    hyphen(4);
    notice();
    key = getch();
    interact();
}

static void handle_interact_with() {
    cout << "\n\n" << tr(StrId::INT_MENU_TITLE) << "\n"
         << tr(StrId::INT_A_DEFECATE) << "\n"
         << tr(StrId::INT_B_PAT) << "\n"
         << tr(StrId::INT_C_QUIT) << "\n";
    key = getch();
    switch (key) {
    case 'A': case 'a': handle_defecate();        break;
    case 'B': case 'b': handle_pat();             break;
    case 'C': case 'c': handle_quit_interaction_menu(); break;
    default:  cout << "\n"; notices::choose_again(); break;
    }
    cout << "\n\n";
}

static void handle_status_display() {
    cout << tr(StrId::STAT_LIFESPAN_LABEL) << "\n";
    cout << "Your pet " << name << " "
         << (Pab == cat ? tr(StrId::STAT_IS_CAT) : tr(StrId::STAT_IS_DOG)) << "\n";
    cout << "Your pet " << name << tr(StrId::STAT_IS_AGE)
         << age << tr(StrId::STAT_YEARS_OLD_NOW) << "\n";
    cout << "Your pet " << name << " "
         << tr(StrId::STAT_CAN_LIVE) << lifespan - days + 1 << tr(StrId::PET_DAYS_PERIOD) << "\n";
    cout << "Your pet " << name << " "
         << tr(StrId::STAT_NEEDS_HAP) << Lifespanhap
         << tr(StrId::STAT_TO_PROLONG) << "\n";
    cout << tr(StrId::STAT_EMOTION_LABEL) << "\n"
         << tr(StrId::STAT_HAPPINESS_LABEL) << hap << "/" << max_hap << "]\n"
         << tr(StrId::STAT_SADNESS_LABEL) << sad << "/" << max_sad << "]\n";
    cout << tr(StrId::STAT_PHYSIO_LABEL) << "\n"
         << tr(StrId::STAT_WANTS_DEFECATE) << (poo ? tr(StrId::STAT_YES) : tr(StrId::STAT_NO)) << "\n"
         << tr(StrId::STAT_WANTS_EAT) << (eat ? tr(StrId::STAT_YES) : tr(StrId::STAT_NO)) << "\n";
    pausers::pause();
}

static void handle_clear_screen() {
    clear_screen();
    turns--;
}

static void handle_buying() {
    cout << tr_f(StrId::BUY_HAVE_MONEY, money) << "\n"
         << tr(StrId::BUY_WHAT_NEXT) << "\n"
         << tr(StrId::BUY_A_ITEMS) << "\n"
         << tr(StrId::BUY_B_INGREDIENTS) << "\n"
         << tr(StrId::BUY_C_LOAN) << "\n"
         << tr(StrId::BUY_D_COOK) << "\n"
         << tr(StrId::BUY_E_QUIT) << "\n";
    key = getch();
    switch (key) {
    case 'A': case 'a': hyphen(); M_stu(); break;
    case 'B': case 'b': hyphen(); M_cok(); break;
    case 'C': case 'c': hyphen(); M_det(); break;
    case 'D': case 'd': Cincook_v2();      break;
    case 'E': case 'e':                    break;
    default:  cout << "\n"; notices::choose_again(); break;
    }
}

static void handle_investment_info() {
    if (Vacheve) {
        Vacheve = false;
        hyphen(5);
        cout << tr_f(StrId::INV_MONEY_INVESTED, Iinvest) << "\n"
             << tr_f(StrId::INV_WAIT_DAYS, Dinvest - days) << "\n";
    } else {
        hyphen(3);
        cout << "\n" << tr(StrId::INV_PLEASE_AGAIN) << "\n";
        notice();
        key = getch();
        interact();
    }
}

#ifdef _WIN32
static void handle_color_change() {
    options::color_choose();
    turns--;
}
#endif

// ── Backpack ──

static void sub_handle_backpack_item_display() {
    for (int i = 0; i < Cid; ++i) {
        cout << i << ". " << backpackmeal[i]
             << " | " << tr(StrId::BP_ENERGY) << ": " << backpackcalr[i]
             << " | " << tr(StrId::BP_EFFECT) << ": " << backpackeffect[i]
             << " | " << tr(StrId::BP_AMOUNT) << ": " << backpackall[i] << "\n";
    }
    pausers::pause();
}

static void sub_handle_backpack_item_interaction() {
    hyphen(4);
    cout << tr(StrId::BP_SELL_FEED_DUMP) << "\n";
    while (true) {
        key = getch();
        if (key == 'A' || key == 'a') {
            // Sell: half the spend cost
            int price = backpackspend[CTP] / 2;
            if (price < 1) price = 1;
            money += price;
            cout << "Sold for $" << price << "!\n";
            Cdrop(static_cast<int>(CTP));
            pausers::pause();
            break;
        } else if (key == 'B' || key == 'b') {
            // Feed: apply the dish effect
            int effect = backpackeffect[CTP];
            int abs_val = (effect < 0) ? -effect : effect;
            int type = abs_val / 100;
            int value = (effect < 0) ? -(abs_val % 100) : (abs_val % 100);
            
            cout << "You fed " << backpackmeal[CTP] << " to " << name << ".\n";
            
            if (type == 0) {        // lifespan
                if (value > 0) lifespan += value;
                else if (lifespan > -value) lifespan -= -value; else lifespan = 1;
                cout << "Lifespan changed by " << value << ".\n";
            } else if (type == 1) { // happiness
                if (value > 0) { hap += value; if (hap > max_hap) hap = max_hap; }
                else { if (hap > -value) hap -= -value; else hap = 0; }
                notices::hap_plus(value);
            } else if (type == 2) { // max happiness
                if (value > 0) max_hap += value;
                else if (max_hap > -value) max_hap -= -value; else max_hap = 1;
            } else if (type == 3) { // sadness
                if (value > 0) { sad += value; if (sad > max_sad) sad = max_sad; }
                else { if (sad > -value) sad -= -value; else sad = 0; }
                notices::sad_minus(-value);
            } else if (type == 4) { // max sadness
                if (value > 0) max_sad += value;
                else if (max_sad > -value) max_sad -= -value; else max_sad = 1;
            }
            // type == 5: no effect
            
            cout << "Happiness: " << hap << "/" << max_hap
                 << " | Sadness: " << sad << "/" << max_sad << "\n";
            
            // Reset hunger timer - the pet just ate!
            w_eat = 0;
            eat = false;
            
            diary_add(tr(StrId::DIARY_ACT_COOKED));
            Cdrop(static_cast<int>(CTP));
            pausers::pause();
            break;
        } else if (key == 'C' || key == 'c') {
            cout << tr_f(StrId::BP_ITEM_DROPPED, CTP) << "\n";
            Cdrop(static_cast<int>(CTP));
            break;
        } else if (key == 'D' || key == 'd') {
            break;
        } else {
            break;
        }
    }
}

static void handle_backpacking() {
    hyphen(4);
    if (Cid != 0) {
        sub_handle_backpack_item_display();
        while (true) {
            cout << tr(StrId::BP_INPUT_NUM);
            cin >> CTP; badint_clear();
            if (isbadint || CTP >= Cid) break;
            sub_handle_backpack_item_interaction();
        }
    } else {
        cout << tr(StrId::BP_NO_DISHES) << "\n";
        pausers::pause();
    }
    hyphen(4);
}

// ── Cheating ──

static void handle_cheating() {
    hyphen(250);
    cout << tr(StrId::CHEAT_PROMPT);
    cin >> cheating;
    cout << "\n";
    if      (cheating == "Gmoney")       { cin >> Mopluse; money += Mopluse; }
    else if (cheating == "Clean")        { hap = 50; sad = 0; poo = false; eat = false; }
    else if (cheating == "Turns")        { turns = 1; }
    else if (cheating == "Smoney")       { cin >> Mopluse; money = Mopluse; }
    else if (cheating == "Suicide")      { hap = 0; sad = 10; }
    else if (cheating == "Days")         { cin >> Mopluse; days = Mopluse; }
    else if (cheating == "r1")           r1();
    else if (cheating == "r2")           r2();
    else if (cheating == "r3")           r3();
    else if (cheating == "r4")           r4();
    else if (cheating == "r5")           r5();
    else if (cheating == "Bdays")        { while (true) { band_days(); if (back) break; } }
    else if (cheating == "Btv1")         Btv1();
    else if (cheating == "Btv2")         Btv2();
    else if (cheating == "Btv3")         Btv3();
    else if (cheating == "Btv4")         Btv4();
    else if (cheating == "storage[0]")   { cin >> Mopluse; storage[0] = Mopluse; }
    else if (cheating == "storage[1]")   { cin >> Mopluse; storage[1] = Mopluse; }
    else if (cheating == "storage[2]")   { cin >> Mopluse; storage[2] = Mopluse; }
    else if (cheating == "storage[3]")   { cin >> Mopluse; storage[3] = Mopluse; }
    else if (cheating == "storage[4]")   { cin >> Mopluse; storage[4] = Mopluse; }
    else if (cheating == "Cooking")      { storage[0]=100;storage[1]=100;storage[2]=100;storage[3]=100;storage[4]=100; }
    cout << "\n";
    hyphen(250);
}

static void handle_default() {
    hyphen(3); cout << "\n";
    notices::choose_again();
    notice();
    key = getch();
    interact();
}

// ═══════════════════════════════════════════
//  interact() — main input dispatcher
// ═══════════════════════════════════════════

static void interact() {
    cout << "\n";
    switch (key) {
    default:                       handle_default();        break;
    case 'Q': case 'q':            handle_quit_game();      break;
    case 'F': case 'f':            handle_feed_pet();       break;
    case 'I': case 'i':            handle_interact_with();  break;
    case 'C': case 'c':            handle_status_display(); break;
    case 'S': case 's':            handle_clear_screen();   break;
    case 'M': case 'm':            handle_buying();         break;
    case 'V': case 'v':            handle_investment_info();break;
    case 'B': case 'b':            check_cooking_ingredient(); break;
    case 'O': case 'o':            handle_backpacking();    break;
#ifdef _WIN32
    case 'X': case 'x':            handle_color_change();   break;
#endif
    case 'G': case 'g':            handle_minigames();       break;
    case 'D': case 'd':            diary_view(); --turns;    break;
    case 'L': case 'l':            handle_cheating();       break;
    }
}

// ═══════════════════════════════════════════
//  Re-init per frame
// ═══════════════════════════════════════════

static void re_ini() {
    e_hap();
    e_sad();
    e_poo();
    e_eat();
    Cfour();
    M_();
}

// ═══════════════════════════════════════════
//  Day start
// ═══════════════════════════════════════════

static void o_days_pre_notice() {
    re_ini();
    e_age();
    if (cheatable) cout << "*";
    diary_new_day(days);
    cout << tr_f(StrId::DAY_LABEL, days) << "\n";
    if (det && Ldet) Dgm = true;
    if (eat) cout << "Your pet " << name << tr(StrId::DAY_HUNGRY) << "\n";
    if (poo) cout << "Your pet " << name << tr(StrId::DAY_WANTS_DEFECATE);
    if (Pmouse) {
        Pmouse_plus = rand_range(1, 5);
        cout << tr(StrId::DAY_PLAYING_MOUSE) << "\n";
        notices::hap_plus(Pmouse_plus);
        hap += Pmouse_plus;
    }
    // BUG H7: BFS passive income with expiration after 30 days
    if (BFS) {
        ++BFS_days;
        if (BFS_days > 30) {
            BFS = false;
            BFS_days = 0;
            cout << name << "'s fans have moved on. The rock band days are over.\n";
        } else {
            Msenting = rand_range(20, 519);
            cout << tr_f(StrId::DAY_FANS_WANT, name.c_str()) << tr(StrId::DAY_KEEP_PERFORMING)
                 << Msenting << tr(StrId::DAY_DOLLAR) << "\n";
            notices::money_plus(Msenting);
            money += Msenting;
        }
    }
    if (lifespan < 0) lifespan = 0;
    if (days == lifespan)
        cout << tr(StrId::LIFESPAN_LAST_DAY) << "\n";
    hyphen(2);
    if (Lifespanhap + 5 <= max_hap && days != 1) {
        notices::your_pet();
        notices::lifespan_plus(5);
        Lifespanhap += 5;
    } else if (days != 1 && Lifespanhap != max_hap) {
        notices::your_pet();
        notices::lifespan_plus(max_hap - Lifespanhap);
        Lifespanhap = max_hap;
    }
}

// ═══════════════════════════════════════════
//  Main game loop — a single day
// ═══════════════════════════════════════════

static void o_days() {
    o_days_pre_notice();
    while (true) {
        if (lifespan < 0) lifespan = 0;
        if (days >= lifespan + 1) { death(); died = true; }
        if (died) break;
        re_ini();
        notice();
        key = getch();
        interact();
        if (key == 'Q' || key == 'q') break;
        ++turns;
        ++w_eat;
        if (days != 1) ++w_poo;
        if (w_eat > 2) eat = true;
        if (w_poo > 4) poo = true;
        cout << "\n\n";
        if (eat) { cout << "Your pet " << name << tr(StrId::DAY_HUNGRY) << "\n"; }
        if (poo) { cout << "Your pet " << name << tr(StrId::DAY_WANTS_DEFECATE); }
        hyphen(1);
        cout << "\n\n";
        if (turns == 9) break;
    }

    // If the pet died during this day, skip all day-end logic
    if (died) return;

    // Investment return
    if (invest && days == Dinvest) {
        invest = false;
        Dinvest = 0;
        randomnum = rand_range(1, 4);
        Einvest = static_cast<float>(rand_range(10, 59));
        if (!cheat && !loser && randomnum == 2) {
            notices::your_pet();
            cout << tr(StrId::INV_SUCCESS) << "\n";
            float profit = IINVEST + Einvest / 100.0f * IINVEST;
            money += static_cast<int>(profit);
            hap += 2;
            notices::money_plus(static_cast<int>(profit));
            notices::hap_plus(2);
        } else if (!cheat && !loser) {
            notices::your_pet();
            cout << tr(StrId::INV_FAILED) << "\n";
            hap -= 1; sad += 2;
            notices::hap_minus(1); notices::sad_plus(2);
        } else if (loser) {
            loser = false;
        } else if (cheat && randomnum != 1) {
            notices::your_pet();
            cout << tr(StrId::INV_SUCCESS) << "\n";
            float profit = IINVEST + Einvest / 100.0f * IINVEST;
            money += static_cast<int>(profit);
            hap += 2; cheat = false;
            notices::money_plus(static_cast<int>(profit));
            notices::hap_plus(2);
        } else if (cheat && randomnum == 1) {
            notices::your_pet();
            cout << tr(StrId::INV_FAILED) << "\n";
            hap -= 1; sad += 2; cheat = false;
            notices::hap_minus(1); notices::sad_plus(2);
        }
        Iinvest = IINVEST = 0;
        Einvest = 0;
        hyphen();
        pausers::pause();
        cout << "\n\n";
    }

    if (key != 'Q' && key != 'q') r_e_v2();
    turns = 1;
    diary_add("  $ " + std::to_string(money) + " | Hap: " + std::to_string(hap) + "/" + std::to_string(max_hap) + " Sad: " + std::to_string(sad) + "/" + std::to_string(max_sad));
    ++days;
}

// ═══════════════════════════════════════════
//  Game start
// ═══════════════════════════════════════════

static void starter_notice() {
    pausers::pause();
#ifdef _WIN32
    options::color_choose();
#endif
    options::name_choose();
    srand(static_cast<unsigned>(time(nullptr)));
    EventConfig::init();
    RecipeDB::init();
    Mname();
    Mname1();
    Ename();
    have_body_ini();
    per();
    gender = (rand_gender() != 0) ? F : M;
    pausers::pause();
    cout << tr(StrId::PET_INTRO_TOGETHER);
    refer(nomin);
    cout << tr(StrId::PET_INTRO_MJ) << "\n";
    pausers::pause(1);
    r_lifespan();
    Lifespanhap = rand_range(60, 84);
}

// ═══════════════════════════════════════════
//  Language selection at startup
// ═══════════════════════════════════════════

static void choose_language() {
    hyphen(4);
    cout << "Language / 语言\n\n"
         << "1)  English\n"
         << "2)  中文\n\n"
         << "Press 1 or 2 / 按 1 或 2: ";
    char lang_key = getch();
    cout << "\n";
    if (lang_key == '1') {
        set_language(en);
        cout << "Language set to English.\n";
    } else {
        set_language(cn);
        cout << "语言设置为中文。\n";
    }
    hyphen(4);
}

// ═══════════════════════════════════════════
//  Entry point
// ═══════════════════════════════════════════

int main(int argc, char* argv[]) {
    cout << "Digital Pet\n" << version << " " << phase;
    if (cheatable) cout << "*";
    cout << "\n";

    // Check for command-line language override first
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--en" || arg == "-e") {
            set_language(en);
            hyphen(4);
        } else if (arg == "--cn" || arg == "-c") {
            set_language(cn);
            hyphen(4);
        } else {
            choose_language();
        }
    } else {
        choose_language();
    }

    starter_notice();

    while (true) {
        o_days();
        if (key == 'Q' || key == 'q') break;
        if (died) break;
    }
    return 0;
}
