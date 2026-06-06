#include "Events.h"
#include "GameState.h"
#include "Utils.h"
#include "Cooking.h"

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
            "There is a man with a little moustache roaring on TV...\n";
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
            "A glasses commercial is showing on TV...\n";
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
            "There is a play called OTHERS ARE HELL showing on TV...\n";
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
            "There are two French men debating on the meaning of life, "
            "but the host keeps emphasizing that they are standing on "
            "the wrong position...\n";
}

// ═══════════════════════════════════════════
//  Random event #1 — money gift
// ═══════════════════════════════════════════

void r1() {
    randomnum = r_events(3, 35, 0);
    if (randomnum != 0) {
        cout << "\nThis day, you find that your pet disappeared. Few hours later, "
                "your pet brings you back $" << randomnum << "!\nMoney increase!\n";
        money += randomnum;
        pausers::pause();
    }
}

// ═══════════════════════════════════════════
//  Random event #2 — investment
// ═══════════════════════════════════════════

void handle_investment_deposit() {
    cout << "You sign your name.\n";
    invest = true;
    while (true) {
        cout << "Input the money you want to invest - ";
        notices::money_have();
        cin >> Iinvest;
        badint();
        if (Iinvest > money) {
            cout << "You don't have that much money! All you have is $ "
                 << money << "!\n\n";
        } else if (!isbadint && Iinvest > 0) {
            break;
        } else if (!isbadint && Iinvest == 0) {
            cout << "You give up the investment when it is by a hair!\n";
            break;
        }
    }
    if (Iinvest != 0) {
        cout << "You invest $ " << Iinvest << ".\n";
        if (Iinvest == money) {
            cout << "Your pet is very pleased when seeing you invested all your money.\n";
            notices::hap_plus(2);
            notices::sad_minus(3);
            hap += 2;
            sad -= 3;
        }
        money -= Iinvest;
        IINVEST = Iinvest;
        Dinvest = r_events(3, 2, 1) + days;
        invest = true;
    } else {
        cout << "Your pet is looking at you as if you are a retard.\n";
        invest = false;
    }
}

void r2() {
    notices::your_pet();
    cout << "walks to you with a paper, which said:\n"
            "VENTURE INVESTMENT\nInvestor: " << name
         << "\nVoucher: You\nSignature:________\n";
    pausers::sure();
    key = getch();
    if (YES_KEY) {
        handle_investment_deposit();
    } else {
        invest = false;
        cout << "Your pet is looking at you as if you are a retard.\n";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════
//  Random event #3 — product promotion
// ═══════════════════════════════════════════

static void handle_buy_10_dollars() {
    if (money >= 10) {
        money -= 10;
        cout << "You spent $10 to buy $" << randomnum << ". ";
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
    randomnum = r_events(114514, 5, 1);
    if (randomnum == 2) {
        cout << " your pet has already eaten the window and entered the house.\n";
    } else {
        cout << " your pet has already entered the house.\n";
    }
    poo = true;
}

static void handle_eating_door() {
    cout << "You pretend that you can't hear " << name
         << "'s knocking, so your pet eats up the door!\n"
            "Your pet feels refreshed.\n";
    notices::hap_plus(2);
    notices::sad_minus(3);
    hap += 2;
    sad -= 3;
    poo = true;
}

void r3() {
    cout << "Your pet runs out of the house.\n"
         << "Few hours later, your pet " << name << " starts to knock on the door.\n";
    cout << "Open the door?\n";
    pausers::sure();
    key = getch();
    if (YES_KEY) handle_opening_door();
    else         handle_eating_door();
    cout << "\n\n" << name << " showed you few items that";
    refer(nomin);
    cout << "found:\n";

    randomnum = r_events(250, 5, 1);
    if (randomnum == 1 || randomnum == 2) {
        cout << "A) ";
        randomnum = r_events(45, 50, 1);
        cout << "$ " << randomnum << " Price: $10\nB) Don't buy anything\n";
        key = getch();
        if (key == 'A' || key == 'a') handle_buy_10_dollars();
    }

    if (randomnum == 3 || randomnum == 4) {
        cout << "A) Toy mouse (happiness [+1]~[+5] each day) $ " << price_mouse << "\n"
             << "B) Slipper (don't you want to buy a house for your pet?) $ " << price_slipper << "\n"
             << "C) Heart saver capsule $ " << price_heartsaver << "\n"
             << "D) Don't buy anything\n";
        while (true) {
            key = getch();
            if (key == 'A' || key == 'a') {
                if (money >= 90 && !Pmouse) {
                    money -= 90;
                    cout << "You have bought the toy mouse!\n";
                    Pmouse = true;
                } else if (money >= 90 && Pmouse) {
                    cout << "Sorry, but your pet already has one!\n";
                } else {
                    notices::money_not();
                }
                break;
            } else if (key == 'B' || key == 'b') {
                if (money >= 20 && !Phouse) {
                    money -= 20;
                    cout << "You have bought the slipper!\n";
                    Phouse = true;
                } else if (money >= 20 && Phouse) {
                    cout << "Sorry, but your pet already has one!\n";
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
                        cout << "MONSTER!\nHappiness = 0! Sadness maximized!\n";
                        hap = 0;
                        sad = max_sad;
                    } else {
                        cout << "You are scammed!\n";
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

    if (randomnum == 5) {
        cout << "A) Loneliness (buy one when you are on your own) $ " << price_lone << "\n"
             << "B) Don't buy anything\n";
        while (true) {
            key = getch();
            if (key == 'A' || key == 'a') {
                if (money >= 10) {
                    money -= 10;
                    cout << "You have bought... loneliness...\n";
                } else {
                    notices::money_not();
                }
                break;
            } else if (key == 'B' || key == 'b') {
                break;
            }
        }
    }
    hyphen(4);
}

// ═══════════════════════════════════════════
//  Random event #4 — rock band
// ═══════════════════════════════════════════

void Bback() {
    back = true;
    cout << "\"21st century schizoid pet!\" You see your pet is holding an electric guitar "
            "(being overwhelmed under the guitar), and the spotlight shines on its eyes.\n";
    pausers::pause();
    cout << "Tears run out your eyes. Few weeks later, your pet knocks on the door again, and";
    refer(nomin);
    cout << "tells you (don't ask me how) that this performance has made a great success.\n";
    randomnum = r_events(134, 5, 1);
    if (randomnum == 5) {
        BFS = true;
        randomnum = r_events(214, 3000, 200);
        cout << "Your pet becomes the next Michael Jackson in the world — in fact, "
                "hardly anybody still remembers Michael Jackson now.\n";
    } else {
        randomnum = r_events(298, 2000, 100);
    }
    money += randomnum;
    cout << "The performance earns you $" << randomnum << " in total.\n";
    pausers::pause();
    cout << "And so, the both of you come back to your ordinary life.\n";
    hyphen(4);
}

void Binteract() {
    if (key == 'T' || key == 't') {
        cout << "You open the TV.\n";
        pausers::pause(1);
        randomnum = r_events(1874298, 2, 1);
        if      (randomnum == 1) Btv1();
        else if (randomnum == 2) Btv2();
        else if (randomnum == 3) Btv3();
        else if (randomnum == 4) Btv4();

        randomnum = r_events(82734, 4, 1);
        if (randomnum == 2) {
            cout << "You are switching channels, and suddenly, you see...\n\nYour pet!\n";
            pausers::pause();
            Bback();
            return;
        } else {
            cout << "You keep changing the channels, but can't find any information "
                    "about your pet...\n";
            pausers::pause(1);
        }
    } else {
        hyphen(3);
        cout << "\n";
        notices::choose_again();
        cout << "\nPress 't' to watch TV.\nThere is 1 chance to watch TV every day.\n"
             << "You have " << 2 - Bturns << " time left.\n";
        key = getch();
        Binteract();
    }
}

void band_days() {
    hyphen(2);
    cout << "Day " << Bdays << "\n";
    while (Bturns < 2) {
        cout << "\n";
        notices::choose_again();
        cout << "\nPlease choose again!\n"
                "Press 't' to watch TV.\n"
             << "You have " << 2 - Bturns << " time left.\n";
        key = getch();
        Binteract();
        if (back) break;
        ++Bturns;
    }
    ++Bdays;
    Bturns = 1;
}

void r4() {
    Bband = true;
    cout << "For the past few days, your pet has been listening to some "
            "strange rock music.\n"
         << "You often hear some words like 'rape' from " << name
         << "'s mouse (don't ask me how)\n";
    pausers::pause();
    cout << "One day, your pet told you through an unimaginable way that";
    refer(nomin);
    cout << "is going to start a progressive rock band.\n"
            "Because you have been such a good owner, this band won't cost you any money.\n";
    pausers::pause();
    eat = false;
    poo = false;
    cout << "Before";
    refer(nomin);
    cout << "left, you feed your pet for the last time, and let";
    refer(nomin);
    cout << "defecate for the last time.\nYou witness";
    refer(posses);
    cout << "leave...\n";
    pausers::pause();
    hyphen(4);
    while (true) {
        band_days();
        if (back) break;
    }
}

// ═══════════════════════════════════════════
//  Random event #5 — ingredient gift
// ═══════════════════════════════════════════

void r5() {
    randomnum = r_events(123, 5, 1);
    cout << "\nToday, you can't find your pet anywhere. Few hours later, "
            "your pet brings you back ";
    int qty = r_events(1234, 35, 1);
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
}

// ═══════════════════════════════════════════
//  Random event dispatcher
// ═══════════════════════════════════════════

void r_e() {
    if (days < 1) return;
    randomnum = r_events();
    if (randomnum > events) return;
    if      (randomnum == 1)                                 r1();
    else if (randomnum == 2) { if (!invest && money > 0)     r2(); }
    else if (randomnum == 3)                                 r3();
    else if (randomnum == 4) { if (!Bband)                   r4(); }
    else if (randomnum == 5)                                 r5();
}
