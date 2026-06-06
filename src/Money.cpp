#include "Money.h"
#include "GameState.h"
#include "Utils.h"
#include "Cooking.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;

// ═══════════════════════════════════════════
//  Buy cooking ingredients (M_cok)
// ═══════════════════════════════════════════

static void M_notice() {
    if (gs < 0)       cout << "Please input again!\n";
    else if (gs == 0) cout << "You give up buying.\n";
}

void M_cok() {
    while (true) {
        notices::money_have();
        cout << "Cooking ingredients:\n"
             << "A) Sugar $ " << price_sug << " per gram\n"
             << "B) Salt $ 6~12 per gram\n"
             << "C) Soda $ " << price_sod << " per gram\n"
             << "D) Water $ " << price_wat << " per milliliter\n"
             << "E) Flour $ " << price_flo << " per gram\n"
             << "F) Air $ 20~900 per square meter\n"
             << "G) Quit this menu\n";
        key = getch();

        if (key == 'A' || key == 'a') {
            uglyprice = 8;
            cout << "Input the number of grams you want to buy:";
            cin >> gs; badint(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); turns--; break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[0] += gs;
                cout << "Bought " << gs << " g of sugar.\n"; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'B' || key == 'b') {
            uglyprice = r_events(123, 21 - 6, 6);
            cout << "Price: $" << uglyprice << "\n"; notices::still_buy();
            key = getch();
            if (YES_KEY) {
                cout << "Input grams:"; cin >> gs; badint(); if (isbadint) gs = 0;
                M_notice();
                if (gs == 0) { pausers::pause(); turns--; break; }
                if (money >= gs * uglyprice) {
                    money -= gs * uglyprice; storage[1] += gs;
                    cout << "Bought " << gs << " g of salt.\n"; pausers::pause(); break;
                } else { notices::money_not(); pausers::pause(); break; }
            }
        } else if (key == 'C' || key == 'c') {
            uglyprice = 9;
            cout << "Input grams:"; cin >> gs; badint(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); turns--; break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[2] += gs; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'D' || key == 'd') {
            cout << "Input milliliters:"; cin >> gs; badint(); if (isbadint) gs = 0;
            if (storage[3] + gs <= 1000) {
                storage[3] += gs; cout << "Bought " << gs << " ml of water.\n";
            } else {
                cout << "Sorry, you have enough water!\n";
            }
            pausers::pause(); break;
        } else if (key == 'E' || key == 'e') {
            uglyprice = 6;
            cout << "Input grams:"; cin >> gs; badint(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); turns--; break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[4] += gs; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'F' || key == 'f') {
            uglyprice = r_events(123, 900 - 20, 20);
            cout << "Price: $" << uglyprice << "\n"; notices::still_buy();
            key = getch();
            if (YES_KEY) {
                cout << "Input square meters:"; cin >> gs; badint(); if (isbadint) gs = 0;
                M_notice();
                if (gs == 0) { pausers::pause(); turns--; break; }
                if (money >= gs * uglyprice) {
                    money -= gs * uglyprice;
                    cout << "You bought " << gs << " m² of air...\n"; pausers::pause(); break;
                } else { notices::money_not(); pausers::pause(); break; }
            }
        } else if (key == 'G' || key == 'g') {
            hyphen(4); break;
        }
        clear_screen();
    }
}

// ═══════════════════════════════════════════
//  Buy props (M_stu)
// ═══════════════════════════════════════════

void M_stu() {
    while (true) {
        notices::money_have();
        cout << "Props:\n"
             << "A) Buttercup - a kind of plant (Sadness [-8]) $ " << price_pbutter << "\n"
             << "B) Buttercup - a kind of madness (Sadness [-15]) $ " << price_mbutter << "\n"
             << "C) Arsenic (investment success +50%) Price: (all money)/5 - random(1~money/20)\n"
             << "D) Diamond (investment will fail 100%) Price: (all money)*10\n"
             << "E) Quit this menu\n";
        key = getch();

        if (key == 'A' || key == 'a') {
            if (money >= 35) { money -= 35; sad -= 8; notices::bought_success(); }
            else notices::money_not();
            hyphen(4); break;
        } else if (key == 'B' || key == 'b') {
            if (money >= 50) { money -= 50; sad -= 15; notices::bought_success(); }
            else notices::money_not();
            hyphen(4); break;
        } else if (key == 'C' || key == 'c') {
            if (money <= 0) { cout << "You don't have any money!\n"; hyphen(4); break; }
            while (true) {
                cheatmoney = (money + Iinvest) / 5;
                if (money / 20 < 1)
                    cheatmoney -= r_events(131, 1, (money + Iinvest) / 20);
                else
                    cheatmoney -= r_events(131, (money + Iinvest) / 20, 1);
                if (cheatmoney > 0) break;
            }
            cout << "Price: $" << cheatmoney << "\n"; pausers::sure();
            key = getch();
            if (YES_KEY) {
                if (money >= cheatmoney) {
                    if (!invest) cout << "You don't have any investment!\n";
                    else if (cheat) cout << "Already bought this prop!\n";
                    else if (loser) cout << "Already bought another prop!\n";
                    else { money -= cheatmoney; cheat = true; notices::bought_success(); }
                } else notices::money_not();
            }
            clear_screen(); break;
        } else if (key == 'D' || key == 'd') {
            if (money <= 0) { cout << "No money!\n"; hyphen(4); break; }
            int cost = money * 10;
            cout << "Price: $" << cost << "\n"; notices::still_buy();
            key = getch();
            if (YES_KEY) {
                if (money >= cost) {
                    if (!invest) cout << "No investment!\n";
                    else if (loser) cout << "Already bought!\n";
                    else if (cheat) cout << "Already bought another prop!\n";
                    else { money -= cost; loser = true; notices::bought_success(); }
                } else notices::money_not();
            }
            clear_screen(); break;
        } else if (key == 'E' || key == 'e') {
            hyphen(4); break;
        }
    }
}

// ═══════════════════════════════════════════
//  Loan (M_det)
// ═══════════════════════════════════════════

void M_det() {
    hyphen();
    if (det) {
        cout << "Sorry, you have already applied for a loan!\n"; hyphen(4); return;
    }
    while (true) {
        cout << "Input the amount of loan you want to apply for "
                "(no more than (all your money)*10):\n";
        cin >> Mdet; badint();
        if (isbadint) gs = 0;
        if (Mdet <= 0) {
            if (Mdet == 0) { cout << "You give up the loan.\n"; turns--; break; }
            cout << "Wrong number, please input again!\n"; hyphen(4); continue;
        }
        if (Mdet > 10 * money || money == 0) {
            if (money == 0)
                cout << "The bank won't trust someone without a dime!\n";
            else
                cout << "More than ten times your money!\n";
            turns--; break;
        }
        Ddet = r_events(3, 10, 1);
        Edet = static_cast<float>(r_events(3, 10, 1));
        cout << "Loan $" << Mdet << " / Interest " << Edet
             << "% / Term " << Ddet << " days\n"
             << "Each day overdue [+" << Edet << "%]!\n";
        pausers::sure();
        key = getch();
        if (YES_KEY) {
            money += Mdet;
            Ddet += days;
            Pdet = Mdet;
            det = true;
            Edet /= 100.0f;
        } else {
            cout << "You give up the contract.\n";
            Mdet = 0; Edet = 0; Ddet = 0;
        }
        hyphen(4); break;
    }
}

// ═══════════════════════════════════════════
//  Loan repayment handlers
// ═══════════════════════════════════════════

void handle_pay_back_in_arrears() {
    Pdet = Pdet + static_cast<int>(Edet * Pdet);
    cout << "\nYou need to pay $" << Pdet
         << ". Pay? (Y/N)\n";
    while (true) {
        key = getch();
        if (YES_KEY) {
            if (money >= Pdet) {
                money -= Pdet; det = false; Pdet = 0; Ldet = false; Edet = 0;
                cout << "Loan paid off.\n";
            } else {
                cout << "Not enough money! Bank clerks scold you.\n";
                hap -= 10; sad += 15;
                notices::sad_plus(15); notices::hap_minus(10);
            }
            break;
        } else if (NO_KEY) {
            cout << "You refuse to pay. Bank clerks scold you.\n";
            hap -= 10; sad += 15;
            notices::sad_plus(15); notices::hap_minus(10);
            break;
        }
    }
    hyphen(3); Dgm = false;
}

void handle_pay_back_out_arrears() {
    Pdet = Pdet + static_cast<int>(Edet * Pdet);
    cout << "\nTime to pay back. You owe $" << Pdet << ". Pay? (Y/N)\n";
    while (true) {
        key = getch();
        if (YES_KEY) {
            if (money >= Pdet) {
                money -= Pdet;
                hap += 2; sad -= 1;
                notices::hap_plus(2); notices::sad_minus(1);
                det = false; Pdet = 0; Mdet = 0; Edet = 0; Ddet = 0;
                cout << "Loan paid off.\n";
            } else {
                cout << "Not enough! Debt increases each day.\n";
                Mdet = 0; Ddet = 0; Ldet = true;
            }
            break;
        } else if (NO_KEY) {
            cout << "Refused! Debt increases each day.\n";
            Ldet = true; Mdet = 0; Ddet = 0;
            break;
        }
    }
    hyphen(3);
}

// ═══════════════════════════════════════════
//  Loan daily tick (M_)
// ═══════════════════════════════════════════

void M_() {
    if (money < 0) money = 0;
    if (!det) return;
    if (Ldet && Dgm) {
        handle_pay_back_in_arrears();
    } else if (!Ldet && days == Ddet) {
        handle_pay_back_out_arrears();
    }
}

// ═══════════════════════════════════════════
//  Check ingredients
// ═══════════════════════════════════════════

void check_cooking_ingredient() {
    colorc(blue);
    cout << "You have " << storage[0] << " grams of sugar\n"
         << "You have " << storage[1] << " grams of salt\n"
         << "You have " << storage[2] << " grams of soda\n"
         << "You have " << storage[3] << " ml of water (1000 ml max)\n"
         << "You have " << storage[4] << " grams of flour\n";
    colorc(white);
    pausers::pause(1);
    turns--;
    hyphen(4);
}
