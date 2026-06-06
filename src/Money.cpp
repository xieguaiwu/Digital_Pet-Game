#include "Money.h"
#include "GameState.h"
#include "Utils.h"
#include "Cooking.h"
#include "i18n.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;

// ═══════════════════════════════════════════
//  Buy cooking ingredients (M_cok)
// ═══════════════════════════════════════════

static void M_notice() {
    if (gs < 0)       cout << tr(StrId::SHOP_PLEASE_AGAIN) << "\n";
    else if (gs == 0) cout << tr(StrId::SHOP_GIVE_UP) << "\n";
}

void M_cok() {
    while (true) {
        notices::money_have();
        cout << tr(StrId::SHOP_TITLE_ING) << "\n"
             << tr_f(StrId::SHOP_ING_A, price_sug) << "\n"
             << tr(StrId::SHOP_ING_B) << "\n"
             << tr_f(StrId::SHOP_ING_C, price_sod) << "\n"
             << tr_f(StrId::SHOP_ING_D, price_wat) << "\n"
             << tr_f(StrId::SHOP_ING_E, price_flo) << "\n"
             << tr(StrId::SHOP_ING_F) << "\n"
             << tr_f(StrId::SHOP_ING_G, price_milk) << "\n"
             << tr_f(StrId::SHOP_ING_H, price_eggs) << "\n"
             << tr_f(StrId::SHOP_ING_I, price_chocolate) << "\n"
             << tr(StrId::SHOP_ING_J) << "\n";
        key = getch();

        if (key == 'A' || key == 'a') {
            uglyprice = 8;
            cout << tr(StrId::SHOP_INPUT_GRAMS);
            cin >> gs; badint_clear(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[0] += gs;
                cout << tr_f(StrId::SHOP_BOUGHT_SUGAR, gs) << "\n"; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'B' || key == 'b') {
            uglyprice = rand_range(6, 20);
            cout << tr_f(StrId::SHOP_PRICE, uglyprice) << "\n"; notices::still_buy();
            key = getch();
            if (YES_KEY) {
                cout << tr(StrId::SHOP_INPUT_GRAMS); cin >> gs; badint_clear(); if (isbadint) gs = 0;
                M_notice();
                if (gs == 0) { pausers::pause(); break; }
                if (money >= gs * uglyprice) {
                    money -= gs * uglyprice; storage[1] += gs;
                    cout << tr_f(StrId::SHOP_BOUGHT_SALT, gs) << "\n"; pausers::pause(); break;
                } else { notices::money_not(); pausers::pause(); break; }
            }
        } else if (key == 'C' || key == 'c') {
            uglyprice = 9;
            cout << tr(StrId::SHOP_INPUT_GRAMS); cin >> gs; badint_clear(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[2] += gs; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'D' || key == 'd') {
            cout << tr(StrId::SHOP_INPUT_ML); cin >> gs; badint_clear(); if (isbadint) gs = 0;
            if (gs > 0) {
                if (storage[3] + gs <= 1000) {
                    storage[3] += gs; cout << tr_f(StrId::SHOP_BOUGHT_WATER, gs) << "\n";
                } else {
                    cout << tr(StrId::SHOP_WATER_FULL) << "\n";
                }
            }
            pausers::pause(); break;
        } else if (key == 'E' || key == 'e') {
            uglyprice = 6;
            cout << tr(StrId::SHOP_INPUT_GRAMS); cin >> gs; badint_clear(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[4] += gs; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'F' || key == 'f') {
            uglyprice = rand_range(20, 899);
            cout << tr_f(StrId::SHOP_PRICE, uglyprice) << "\n"; notices::still_buy();
            key = getch();
            if (YES_KEY) {
                cout << tr(StrId::SHOP_INPUT_SQM); cin >> gs; badint_clear(); if (isbadint) gs = 0;
                M_notice();
                if (gs == 0) { pausers::pause(); break; }
                if (money >= gs * uglyprice) {
                    money -= gs * uglyprice;
                    cout << tr_f(StrId::SHOP_BOUGHT_AIR, gs) << "\n"; pausers::pause(); break;
                } else { notices::money_not(); pausers::pause(); break; }
            }
        } else if (key == 'G' || key == 'g') {
            uglyprice = 12;
            cout << tr(StrId::SHOP_INPUT_100ML);
            cin >> gs; badint_clear(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[ING_MILK] += gs;
                cout << tr_f(StrId::SHOP_BOUGHT_MILK, gs) << "\n"; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'H' || key == 'h') {
            uglyprice = 15;
            cout << tr(StrId::SHOP_INPUT_EGGS);
            cin >> gs; badint_clear(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[ING_EGGS] += gs;
                cout << tr_f(StrId::SHOP_BOUGHT_EGGS, gs) << "\n"; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'I' || key == 'i') {
            uglyprice = 20;
            cout << tr(StrId::SHOP_INPUT_100G);
            cin >> gs; badint_clear(); if (isbadint) gs = 0;
            M_notice();
            if (gs == 0) { pausers::pause(); break; }
            if (money >= gs * uglyprice) {
                money -= gs * uglyprice; storage[ING_CHOCOLATE] += gs;
                cout << tr_f(StrId::SHOP_BOUGHT_CHOCOLATE, gs) << "\n"; pausers::pause(); break;
            } else { notices::money_not(); pausers::pause(); break; }
        } else if (key == 'J' || key == 'j') {
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
        cout << tr(StrId::SHOP_TITLE_PROPS) << "\n"
             << tr_f(StrId::SHOP_PROP_A, price_pbutter) << "\n"
             << tr_f(StrId::SHOP_PROP_B, price_mbutter) << "\n"
             << tr(StrId::SHOP_PROP_C) << "\n"
             << tr(StrId::SHOP_PROP_D) << "\n"
             << tr(StrId::SHOP_PROP_E) << "\n";
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
            if (money <= 0) { cout << tr(StrId::SHOP_NO_MONEY) << "\n"; hyphen(4); break; }
            while (true) {
                cheatmoney = (money + Iinvest) / 5;
                if (money / 20 < 1)
                    cheatmoney -= rand_range((money + Iinvest) / 20, (money + Iinvest) / 20);
                else
                    cheatmoney -= rand_range(1, (money + Iinvest) / 20);
                if (cheatmoney > 0) break;
            }
            cout << tr_f(StrId::SHOP_PRICE, cheatmoney) << "\n"; pausers::sure();
            key = getch();
            if (YES_KEY) {
                if (money >= cheatmoney) {
                    if (!invest) cout << tr(StrId::SHOP_NO_INVESTMENT) << "\n";
                    else if (cheat) cout << tr(StrId::SHOP_ALREADY) << "\n";
                    else if (loser) cout << tr(StrId::SHOP_ALREADY_OTHER) << "\n";
                    else { money -= cheatmoney; cheat = true; notices::bought_success(); }
                } else notices::money_not();
            }
            clear_screen(); break;
        } else if (key == 'D' || key == 'd') {
            if (money <= 0) { cout << tr(StrId::SHOP_NO_MONEY) << "\n"; hyphen(4); break; }
            int cost = money * 10;
            cout << tr_f(StrId::SHOP_PRICE, cost) << "\n"; notices::still_buy();
            key = getch();
            if (YES_KEY) {
                if (money >= cost) {
                    if (!invest) cout << tr(StrId::SHOP_NO_INVESTMENT) << "\n";
                    else if (loser) cout << tr(StrId::SHOP_ALREADY) << "\n";
                    else if (cheat) cout << tr(StrId::SHOP_ALREADY_OTHER) << "\n";
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
        cout << tr(StrId::LOAN_ALREADY) << "\n"; hyphen(4); return;
    }
    while (true) {
        cout << tr(StrId::LOAN_PROMPT) << "\n";
        cin >> Mdet; badint_clear();
        if (isbadint) gs = 0;
        if (Mdet <= 0) {
            if (Mdet == 0) { cout << tr(StrId::LOAN_GIVE_UP) << "\n"; turns--; break; }
            cout << tr(StrId::LOAN_WRONG_NUM) << "\n"; hyphen(4); continue;
        }
        if (Mdet > 10 * money || money == 0) {
            if (money == 0)
                cout << tr(StrId::LOAN_NO_DIME) << "\n";
            else
                cout << tr(StrId::LOAN_MORE_THAN10) << "\n";
            turns--; break;
        }
        Ddet = rand_range(1, 10);
        Edet = static_cast<float>(rand_range(1, 10));
        cout << tr_f(StrId::LOAN_CONTRACT, Mdet, static_cast<int>(Edet), Ddet, static_cast<int>(Edet));
        pausers::sure();
        key = getch();
        if (YES_KEY) {
            money += Mdet;
            Ddet += days;
            Pdet = Mdet;
            det = true;
            Edet /= 100.0f;
        } else {
            cout << tr(StrId::LOAN_GIVE_UP_CONTRACT) << "\n";
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
    cout << tr_f(StrId::LOAN_OWE, Pdet) << "\n";
    while (true) {
        key = getch();
        if (YES_KEY) {
            if (money >= Pdet) {
                money -= Pdet; det = false; Pdet = 0; Ldet = false; Edet = 0;
                cout << tr(StrId::LOAN_PAID) << "\n";
            } else {
                cout << tr(StrId::LOAN_SCOLD) << "\n";
                hap -= 10; sad += 15;
                notices::sad_plus(15); notices::hap_minus(10);
            }
            break;
        } else if (NO_KEY) {
            cout << tr(StrId::LOAN_REFUSE_DEBT) << "\n";
            hap -= 10; sad += 15;
            notices::sad_plus(15); notices::hap_minus(10);
            break;
        }
    }
    hyphen(3); Dgm = false;
}

void handle_pay_back_out_arrears() {
    Pdet = Pdet + static_cast<int>(Edet * Pdet);
    cout << tr_f(StrId::LOAN_PAY_PROMPT, Pdet) << "\n";
    while (true) {
        key = getch();
        if (YES_KEY) {
            if (money >= Pdet) {
                money -= Pdet;
                hap += 2; sad -= 1;
                notices::hap_plus(2); notices::sad_minus(1);
                det = false; Pdet = 0; Mdet = 0; Edet = 0; Ddet = 0;
                cout << tr(StrId::LOAN_PAID) << "\n";
            } else {
                cout << tr(StrId::LOAN_NOT_ENOUGH_DEBT) << "\n";
                Mdet = 0; Ddet = 0; Ldet = true;
            }
            break;
        } else if (NO_KEY) {
            cout << tr(StrId::LOAN_REFUSE_DEBT) << "\n";
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
    // Clamp to zero — money is now int (signed), so negative values are possible
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
    colorc_ansi(blue);
    cout << tr_f(StrId::CHECK_ING_SUGAR, storage[0]) << "\n"
         << tr_f(StrId::CHECK_ING_SALT, storage[1]) << "\n"
         << tr_f(StrId::CHECK_ING_SODA, storage[2]) << "\n"
         << tr_f(StrId::CHECK_ING_WATER, storage[3]) << "\n"
         << tr_f(StrId::CHECK_ING_FLOUR, storage[4]) << "\n"
         << tr_f(StrId::CHECK_ING_MILK, storage[ING_MILK]) << "\n"
         << tr_f(StrId::CHECK_ING_EGGS, storage[ING_EGGS]) << "\n"
         << tr_f(StrId::CHECK_ING_CHOCOLATE, storage[ING_CHOCOLATE]) << "\n";
    colorc_ansi(white);
    pausers::pause(1);
    turns--;
    hyphen(4);
}
