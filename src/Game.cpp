#include "GameState.h"
#include "Utils.h"
#include "Cooking.h"
#include "Events.h"
#include "Money.h"
#include "Body.h"

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
            hap -= 5; sad += 3;
        } else {
            hap -= 8; sad += 6;
        }
    }
}

static void e_eat() {
    if (w_eat > 5) w_eat = 5;
    if (w_eat > 2) {
        if (w_eat < 4) {
            hap -= 4; sad += 5;
        } else {
            hap -= 8; sad += 7;
        }
    }
}

static void e_age() {
    if (days != 0 && days % 10 == 0) {
        ++age;
        notices::your_pet();
        cout << "is 1 year older!\n";
    }
}

static void e_sad() {
    if (sad < 0) sad = 0;
    if (sad > max_sad) sad = max_sad;
    if (sad < max_sad) {
        if (sad > 25) {
            if (sad < 38) { sad += 3; hap -= 6; }
            else          { sad += 6; hap -= 10; }
        }
    } else {
        notices::your_pet();
        cout << "is so depressed that";
        refer(nomin);
        cout << "committed suicide.\n";
        death();
    }
}

static void e_hap() {
    if (hap < 0) hap = 0;
    if (hap > max_hap) hap = max_hap;
    if (hap < max_hap) {
        if (hap > 50 && hap < 76) {
            hap += 3; sad -= 3;
        } else if (hap >= 76) {
            hap += 4; sad -= 5;
            if (hap >= Lifespanhap && sad <= 15) {
                if ((turns == 2 || turns == 4 || turns == 6 || turns == 8)
                    && !Lifespanup_turns) {
                    cout << "Your pet's lifespan increased by 1 day!\n";
                    ++lifespan;
                    Lifespanup_turns = true;
                } else {
                    Lifespanup_turns = false;
                }
            }
        }
    } else {
        sad -= 5;
    }
}

// ═══════════════════════════════════════════
//  Death
// ═══════════════════════════════════════════

static void death() {
    hyphen();
    cout << "Your pet " << name << " had been through a life of "
         << age << " years, and ";
    refer(nomin);
    cout << "had been through " << days << " days.\n";
    cout << "When " << name << " was going to die, ";
    if (poo) { refer(nomin); cout << "still wanted to defecate.\n"; }
    if (eat) { refer(nomin); cout << "is still very hungry.\n"; }
    cout << "When";
    refer(nomin);
    cout << "was going to die, " << name << " ";
    if (sad >= 38 && sad < 42 && hap < 50)
        cout << "was a bit sad.\n";
    else if (sad >= 42 && hap < 50)
        cout << "was very depressed.\n";
    else if (hap >= 50 && hap < 76 && sad < 38)
        cout << "was quite happy.\n";
    else if (hap >= 76 && sad < 38)
        cout << "was very happy.\n";
    else if (hap >= 50 && sad >= 38)
        cout << "was confused.\n";
    died = true;
    pausers::pause(1);
}

// ═══════════════════════════════════════════
//  Notice / action menu
// ═══════════════════════════════════════════

static void notice() {
    cout << "\nPRESS 'Q' TO QUIT\n"
            "PRESS 'F' TO FEED YOUR PET\n"
            "PRESS 'I' TO INTERACT WITH YOUR PET\n"
            "PRESS 'C' TO CHECK YOUR PET'S STATUS\n"
            "PRESS 'S' TO CLEAR THE SCREEN\n"
            "PRESS 'M' TO [PURCHASE], [APPLY FOR LOAN] OR [COOK]\n"
            "PRESS 'B' TO CHECK THE [COOKING INGREDIENT] YOU ALREADY HAVE\n"
            "PRESS 'O' TO CHECK THE DISHES YOU ALREADY COOKED\n";
#ifdef _WIN32
    cout << "PRESS 'X' TO RESET THE THEME COLOR\n";
#endif
    if (invest) {
        cout << "PRESS 'V' TO CHECK THE [STATUS OF INVESTMENT]\n";
        Vacheve = true;
    }
    cout << "There are 8 times to press the key.\n"
         << "You have " << 9 - turns << " times left\n";
}

// ═══════════════════════════════════════════
//  Interaction handlers
// ═══════════════════════════════════════════

static void handle_quit_game() {
    cout << "You quit the game.\n";
    pausers::pause(4);
}

static void handle_feed_pet() {
    cout << "You feed your pet.\n";
    w_eat = 0;
    if (eat) { hap += 2; notices::hap_plus(2); }
    eat = false;
    pausers::pause();
}

static void handle_defecate() {
    cout << "You let your pet " << name << " defecate.\n";
    w_poo = 0;
    if (poo) { ++hap; notices::hap_plus(1); }
    poo = false;
    pausers::pause();
}

static void handle_pat() {
    cout << "You pat your pet " << name << ".\n";
    hap += 4; sad -= 3;
    notices::hap_plus(4); notices::sad_minus(3);
    pausers::pause();
}

static void handle_quit_interaction_menu() {
    hyphen(4);
    notice();
    key = getch();
    interact();
}

static void handle_interact_with() {
    cout << "\n\nINTERACTIONS:\n"
            "A) Let your pet defecate\n"
            "B) Pat your pet\n"
            "C) Quit this menu\n";
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
    cout << "---LIFESPAN---\n";
    notices::your_pet();
    cout << (Pab == cat ? "is a cat.\n" : "is a dog.\n");
    notices::your_pet();
    cout << "is " << age << " years old now.\n";
    notices::your_pet();
    cout << "can still live for " << lifespan - days + 1 << " days.\n";
    notices::your_pet();
    cout << "needs to reach at least [Happiness: " << Lifespanhap
         << "] to prolong lifespan.\n";
    cout << "---EMOTION---\n"
         << "[Happiness: " << hap << "/" << max_hap << "]\n"
         << "[Sadness: " << sad << "/" << max_sad << "]\n";
    cout << "---PHYSIOLOGY---\n"
         << "Wants to defecate: " << (poo ? "[YES]\n" : "[NO]\n")
         << "Wants to eat: " << (eat ? "[YES]\n" : "[NO]\n");
    turns--;
    pausers::pause();
}

static void handle_clear_screen() {
    clear_screen();
    turns--;   // original decrements turns — preserved despite S being "free"
}

static void handle_buying() {
    cout << "You have $ " << money << "\n"
            "What do you want to do next?\n"
            "A) Buy items\n"
            "B) Buy [cooking ingredients]\n"
            "C) Apply for loan\n"
            "D) Start cooking\n"
            "E) Quit this menu\n";
    key = getch();
    switch (key) {
    case 'A': case 'a': hyphen(); M_stu(); break;
    case 'B': case 'b': hyphen(); M_cok(); break;
    case 'C': case 'c': hyphen(); M_det(); break;
    case 'D': case 'd': Cincook();         break;
    case 'E': case 'e':                    break;
    default:  cout << "\n"; notices::choose_again(); break;
    }
}

static void handle_investment_info() {
    if (Vacheve) {
        turns--;
        Vacheve = false;
        hyphen(5);
        cout << "Money invested: $" << Iinvest << "\n"
             << "Wait: " << Dinvest - days << " days.\n";
    } else {
        hyphen(3);
        cout << "\nPlease choose again!\n";
        notice();
        key = getch();
        interact();
    }
}

static void handle_color_change() {
    options::color_choose();
    turns--;
}

// ── Backpack ──

static void sub_handle_backpack_item_display() {
    for (int i = 0; i < static_cast<int>(Cid); ++i) {
        cout << i << ". " << backpackmeal[i]
             << " | Energy: " << backpackcalr[i]
             << " | Effect: " << backpackeffect[i]
             << " | Amount: " << backpackall[i] << "\n";
    }
    pausers::pause();
}

static void sub_handle_backpack_item_interaction() {
    hyphen(4);
    cout << "A) Sell this dish\n"
            "B) Feed this dish to your pet\n"
            "C) Dump this dish\n"
            "D) Quit this menu\n";
    while (true) {
        key = getch();
        if (key == 'C' || key == 'c') {
            cout << "Item #" << CTP << " dropped.\n";
            Cdrop(CTP);
            break;
        } else if (key == 'D' || key == 'd') {
            break;
        } else {
            break;  // sell/feed not yet implemented
        }
    }
}

static void handle_backpacking() {
    hyphen(4);
    if (Cid != 0) {
        sub_handle_backpack_item_display();
        while (true) {
            cout << "Input item number (negative to quit):";
            cin >> CTP; badint();
            if (isbadint || CTP >= Cid || CTP < 0) break;
            sub_handle_backpack_item_interaction();
        }
    } else {
        cout << "You don't have any dish!\n";
        pausers::pause();
    }
    turns--;
    hyphen(4);
}

// ── Cheating ──

static void handle_cheating() {
    hyphen(250);
    cout << "Insert cheating code: ";
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
    turns--;
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
    cout << "DAY " << days << " .\n";
    if (det && Ldet) Dgm = true;
    if (eat) cout << "Your pet " << name << " is hungry.\n";
    if (poo) cout << "Your pet " << name << " wants to defecate.\n\n";
    if (Pmouse) {
        Pmouse_plus = r_events(1784, 5, 1);
        cout << "Your pet is playing with the toy mouse.\n";
        notices::hap_plus(Pmouse_plus);
        hap += Pmouse_plus;
    }
    if (BFS) {
        Msenting = r_events(1321, 500, 20);
        cout << "Some fans want " << name << " to keep performing, so they put $"
             << Msenting << ".\n";
        notices::money_plus(Msenting);
        money += Msenting;
    }
    if (lifespan < 0) lifespan = 0;
    if (days == lifespan)
        cout << "If nothing goes wrong, this is the last day of your pet.\n";
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
        re_ini();
        if (died) break;
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
        if (eat) { notices::your_pet(); cout << "is hungry.\n"; }
        if (poo) { notices::your_pet(); cout << "wants to defecate.\n\n\n"; }
        hyphen(1);
        cout << "\n\n";
        if (turns == 9) break;
    }

    // Investment return
    if (invest && days == Dinvest) {
        invest = false;
        Dinvest = 0;
        randomnum = r_events(3, 4, 1);
        Einvest = static_cast<float>(r_events(3, 50, 10));
        if (!cheat && !loser && randomnum == 2) {
            notices::your_pet();
            cout << "has made a successful investment!\nRate of profit: " << Einvest << "%!\n";
            float profit = IINVEST + Einvest / 100.0f * IINVEST;
            money += static_cast<unsigned int>(profit);
            hap += 2;
            notices::money_plus(static_cast<int>(profit));
            notices::hap_plus(2);
        } else if (!cheat && !loser) {
            notices::your_pet();
            cout << "has failed the investment!\n";
            hap -= 1; sad += 2;
            notices::hap_minus(1); notices::sad_plus(2);
        } else if (loser) {
            loser = false;
        } else if (cheat && randomnum != 1) {
            notices::your_pet();
            cout << "has made a successful investment! Profit rate: "
                 << Einvest << "%!\n";
            float profit = IINVEST + Einvest / 100.0f * IINVEST;
            money += static_cast<unsigned int>(profit);
            hap += 2; cheat = false;
            notices::money_plus(static_cast<int>(profit));
            notices::hap_plus(2);
        } else if (cheat && randomnum == 1) {
            notices::your_pet();
            cout << "has failed the investment!\n";
            hap -= 1; sad += 2; cheat = false;
            notices::hap_minus(1); notices::sad_plus(2);
        }
        Iinvest = IINVEST = 0;
        Einvest = 0;
        hyphen();
        pausers::pause();
        cout << "\n\n";
    }

    if (key != 'Q' && key != 'q') r_e();
    turns = 1;
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
    Mname();
    Mname1();
    Ename();
    have_body_ini();
    per();
    pausers::pause();
    cout << "You will have a great time together, won't you?\n"
            "You look at your pet, then suddenly realize that";
    refer(nomin);
    cout << "might become the next Michael Jackson.\n";
    pausers::pause(1);
    r_lifespan();
    Lifespanhap = r_events(1242, 85 - 60, 60);
}

// ═══════════════════════════════════════════
//  Entry point
// ═══════════════════════════════════════════

int main() {
    cout << "Digital Pet\n" << version << " " << phase;
    if (cheatable) cout << "*";
    cout << "\n";
    hyphen(4);

    starter_notice();

    while (true) {
        o_days();
        if (key == 'Q' || key == 'q') break;
        if (died) break;
    }
    return 0;
}
