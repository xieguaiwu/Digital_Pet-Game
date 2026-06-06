#include "Cooking.h"
#include "GameState.h"
#include "Utils.h"

#include <iostream>

using std::cout;
using std::cin;

// ── Populate dish-name map ──
void Mname() {
    meal[0] = "air";
    meal[1] = "soda water";
    meal[2] = "unnamable black item";
    meal[3] = "paste";
    meal[4] = "bread";
    meal[5] = "soda with water";
    meal[6] = "cake";
}

// ── Populate taste-name map ──
void Mname1() {
    Tmeal[10] = "a bit too sweet";
    Tmeal[11] = "a bit too salty";
    Tmeal[12] = "a bit too drippy";
    Tmeal[13] = "filled with gas";
    Tmeal[14] = "plain";
    Tmeal[15] = "soft";
    Tmeal[16] = "incredibly sweet";
    Tmeal[17] = "incredibly salty";
    Tmeal[18] = "incredibly drippy";
    Tmeal[19] = "incredibly soft";
    Tmeal[20] = "a bit dry";
}

// ── Populate effect-name map (using int keys from Types.h) ──
void Ename() {
    effects[EFFECT_LIFE_UP1]      = "Lifespan [+1]";
    effects[EFFECT_LIFE_UP2]      = "Lifespan [+2]";
    effects[EFFECT_LIFE_DOWN1]    = "Lifespan [-1]";
    effects[EFFECT_LIFE_DOWN2]    = "Lifespan [-2]";
    effects[EFFECT_HAP_UP10]      = "Happiness [+10]";
    effects[EFFECT_HAP_UP15]      = "Happiness [+15]";
    effects[EFFECT_HAP_DOWN10]    = "Happiness [-10]";
    effects[EFFECT_HAP_DOWN15]    = "Happiness [-15]";
    effects[EFFECT_MAXHAP_UP5]    = "Limit of happiness [+5]";
    effects[EFFECT_MAXHAP_UP15]   = "Limit of happiness [+15]";
    effects[EFFECT_MAXHAP_DOWN5]  = "Limit of happiness [-5]";
    effects[EFFECT_MAXHAP_DOWN15] = "Limit of happiness [-15]";
    effects[EFFECT_SAD_UP5]       = "Sadness [+5]";
    effects[EFFECT_SAD_UP8]       = "Sadness [+8]";
    effects[EFFECT_SAD_DOWN5]     = "Sadness [-5]";
    effects[EFFECT_SAD_DOWN8]     = "Sadness [-8]";
    effects[EFFECT_MAXSAD_UP5]    = "Limit of Sadness [+5]";
    effects[EFFECT_MAXSAD_UP10]   = "Limit of Sadness [+10]";
    effects[EFFECT_MAXSAD_DOWN5]  = "Limit of Sadness [-5]";
    effects[EFFECT_MAXSAD_DOWN10] = "Limit of Sadness [-10]";
    effects[EFFECT_NONE]          = "no effect";
}

// ── Cooking random notice ──
void cook_random_notice() {
    int Rcook = 1 + rand() % 3;
    if (Rcook == 1) {
        cout << "You throw a bunch of inorganic substance (except for the flour) into the pot. "
                "Few hours later, you find yourself very tasty. When cooking yourself, "
                "you find out that you have already cooked...";
    } else if (Rcook == 2) {
        cout << "You carefully throw a bunch of materials into the pot, and cook them with "
                "strange approaches. A few minutes later, you find the turner very tasty. "
                "When trying to chew the turner, you find yourself successfully cooked...";
    } else {
        cout << "After throwing a bunch of disgusting inorganic substance, you are choked by "
                "the smoke for two whole hours, and you find yourself totally cooked. "
                "In the mean time, you successfully invented...";
    }
}

// ── Cook (returns dish type index or calorie count) ──
int cook(unsigned int Psug, unsigned int Psul, unsigned int Psod,
         unsigned int Pwat, unsigned int Pflo, bool CookOrCal) {
    Msug = Psug; Msul = Psul; Msod = Psod; Mwat = Pwat; Mflo = Pflo;
    Camount = Psug + Psul + Psod + Pwat + Pflo;

    if (!CookOrCal) {
        if (Psug == 0 && Psul == 0 && Psod == 0 && Pwat == 0 && Pflo == 0) {
            cout << "After precisely controlling the invisible fire, consistly modifying the "
                    "temperature of the non-existent frying pan, and the combination of the "
                    "imaginary delicate seasonings, you successfully made a dish of...";
            Ncook = air;
            return Ncook;
        } else {
            cook_random_notice();
        }
    } else {
        Mcalr = Psug * 400;
        if (Pwat > Pflo)
            Mcalr = Mcalr + Pflo * 300;
        else
            Mcalr = Mcalr + Pwat * 2 + (Pflo - Pwat) * 366;
        return Mcalr;
    }
    return -1;
}

// ── Determine dish name ──
int meal_nam() {
    if (Msod > 0 && Mwat > 0) {
        if (Mwat <= Msod && Mflo > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5
            && Mflo > Msod && Msug <= Msul && Msug <= Msod && Msug <= Mwat && Msug <= Mflo) {
            Ncook = bread;
        } else if (Mwat <= Msod && Mflo > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5
                   && Mflo > Msod && Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
            Ncook = cake;
        } else if (Mwat > Msod) {
            Ncook = soda;
        } else if (Msod > Mwat) {
            Ncook = bananas;
        } else {
            Ncook = indefine;
        }
    } else if (Mflo > 0 && Mwat > 0) {
        if (Mwat <= Msod && Msod > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5
            && Mflo > Msod && Msug <= Msul && Msug <= Msod && Msug <= Mwat && Msug <= Mflo) {
            Ncook = bread;
        } else if (Mwat <= Msod && Msod > 0 && Mwat <= (Msug + Msul + Msod + Mwat + Mflo) / 5
                   && Mflo > Msod && Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
            Ncook = cake;
        } else {
            Ncook = flor;
        }
    } else {
        Ncook = indefine;
    }
    return Ncook;
}

// ── Determine taste ──
int meal_tas() {
    if (Msug > Msul && Msug > Msod && Msug > Mwat && Msug > Mflo) {
        Tcook = (Msug >= (Msug + Msul + Msod + Mwat + Mflo) / 2) ? Vsweet : sweet;
    } else if (Msul > Msug && Msul > Msod && Msul > Mwat && Msul > Mflo) {
        Tcook = (Msul >= (Msug + Msul + Msod + Mwat + Mflo) / 2) ? Vsult : sult;
    } else if (Mwat > Msug && Mwat > Msod && Mwat > Msul && Mwat > Mflo) {
        Tcook = (Mwat >= (Msug + Msul + Msod + Mwat + Mflo) / 2) ? Vmois : mois;
    } else if (Msod > Msug && Msod > Mwat && Msod > Msul && Msod > Mflo) {
        Tcook = too_sod;
    } else if (Mflo > Msug && Mflo > Msod && Mflo > Msul && Mflo <= Mwat) {
        Tcook = (Mflo >= (Msug + Msul + Msod + Mwat + Mflo) / 2) ? Vfloy : floy;
    } else if (Mflo > 0 && Mwat == 0) {
        Tcook = dry;
    } else {
        Tcook = flat;
    }
    return Tcook;
}

// ── Determine food effect ──
// Returns an int constant (EFFECT_* from Types.h)
int meal_effect() {
    if (Tcook == sweet) {
        switch (Ncook) {
        default:       Ecook = static_cast<float>(EFFECT_MAXHAP_UP5);  break;
        case soda:     Ecook = static_cast<float>(EFFECT_HAP_UP15);   break;
        case flor:     Ecook = static_cast<float>(EFFECT_SAD_UP5);    break;
        case cake:     Ecook = static_cast<float>(EFFECT_LIFE_UP1);   break;
        case indefine: Ecook = static_cast<float>(EFFECT_MAXSAD_UP5); break;
        case bananas:  Ecook = static_cast<float>(EFFECT_SAD_DOWN5);  break;
        }
    } else if (Tcook == Vsweet) {
        switch (Ncook) {
        default:       Ecook = static_cast<float>(EFFECT_MAXSAD_UP5);  break;
        case soda:     Ecook = static_cast<float>(EFFECT_LIFE_DOWN1);  break;
        case flor:     Ecook = static_cast<float>(EFFECT_SAD_UP8);     break;
        case cake:     Ecook = static_cast<float>(EFFECT_MAXHAP_UP15); break;
        case indefine: Ecook = static_cast<float>(EFFECT_SAD_UP8);     break;
        case bananas:  Ecook = static_cast<float>(EFFECT_SAD_DOWN8);   break;
        }
    } else if (Tcook == sult) {
        switch (Ncook) {
        default:       Ecook = static_cast<float>(EFFECT_MAXHAP_DOWN5);  break;
        case soda:     Ecook = static_cast<float>(EFFECT_MAXHAP_UP15);   break;
        case indefine: Ecook = static_cast<float>(EFFECT_MAXSAD_UP10);   break;
        case flor:     Ecook = static_cast<float>(EFFECT_HAP_UP10);      break;
        case bread:    Ecook = static_cast<float>(EFFECT_LIFE_UP2);      break;
        case bananas:  Ecook = static_cast<float>(EFFECT_SAD_UP8);       break;
        case cake:     Ecook = static_cast<float>(EFFECT_SAD_UP5);       break;
        }
    } else if (Tcook == Vsult) {
        switch (Ncook) {
        default:       Ecook = static_cast<float>(EFFECT_MAXHAP_DOWN15); break;
        case soda:     Ecook = static_cast<float>(EFFECT_LIFE_UP1);      break;
        case flor:     Ecook = static_cast<float>(EFFECT_MAXSAD_UP10);   break;
        case bread:    Ecook = static_cast<float>(EFFECT_MAXHAP_UP15);   break;
        case bananas:  Ecook = static_cast<float>(EFFECT_LIFE_DOWN1);    break;
        case cake:     Ecook = static_cast<float>(EFFECT_SAD_UP8);       break;
        }
    } else if (Tcook == mois) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_NONE           : static_cast<float>(EFFECT_MAXHAP_UP5);
        else if (Ncook == flor)    Ecook = EFFECT_NONE;
        else if (Ncook == bread)   Ecook = (Pab == cat) ? EFFECT_HAP_UP10       : static_cast<float>(EFFECT_SAD_UP5);
        else if (Ncook == bananas) Ecook = EFFECT_NONE;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_HAP_UP15       : static_cast<float>(EFFECT_SAD_DOWN5);
        else                       Ecook = (Pab == cat) ? EFFECT_SAD_DOWN5      : static_cast<float>(EFFECT_SAD_UP5);
    } else if (Tcook == Vmois) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_NONE           : static_cast<float>(EFFECT_MAXHAP_UP5);
        else if (Ncook == flor)    Ecook = (Pab == cat) ? EFFECT_NONE           : static_cast<float>(EFFECT_SAD_UP5);
        else if (Ncook == bread)   Ecook = (Pab == cat) ? EFFECT_HAP_UP15       : static_cast<float>(EFFECT_SAD_UP5);
        else if (Ncook == bananas) Ecook = EFFECT_NONE;
        else if (Ncook == cake)    Ecook = EFFECT_MAXHAP_UP15;
        else                       Ecook = (Pab == cat) ? EFFECT_SAD_DOWN8      : static_cast<float>(EFFECT_SAD_UP8);
    } else if (Tcook == too_sod) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_MAXHAP_DOWN5   : static_cast<float>(EFFECT_NONE);
        else if (Ncook == flor)    Ecook = (Pab == cat) ? EFFECT_SAD_UP5        : static_cast<float>(EFFECT_NONE);
        else if (Ncook == bread)   Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP15    : static_cast<float>(EFFECT_HAP_UP15);
        else if (Ncook == bananas) Ecook = EFFECT_NONE;
        else if (Ncook == cake)    Ecook = EFFECT_SAD_DOWN8;
        else                       Ecook = EFFECT_NONE;
    } else if (Tcook == floy) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_HAP_UP10       : static_cast<float>(EFFECT_MAXHAP_UP5);
        else if (Ncook == flor)    Ecook = EFFECT_HAP_UP10;
        else if (Ncook == bread)   Ecook = EFFECT_MAXHAP_UP15;
        else if (Ncook == bananas) Ecook = EFFECT_SAD_UP8;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_HAP_UP10       : static_cast<float>(EFFECT_HAP_UP15);
        else                       Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP5     : static_cast<float>(EFFECT_NONE);
    } else if (Tcook == Vfloy) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_HAP_UP15       : static_cast<float>(EFFECT_MAXHAP_UP15);
        else if (Ncook == flor)    Ecook = EFFECT_HAP_UP15;
        else if (Ncook == bread)   Ecook = EFFECT_SAD_UP5;
        else if (Ncook == bananas) Ecook = EFFECT_MAXSAD_UP5;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_HAP_UP15       : static_cast<float>(EFFECT_MAXHAP_UP15);
        else                       Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP15    : static_cast<float>(EFFECT_HAP_UP10);
    } else if (Tcook == dry) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP5     : static_cast<float>(EFFECT_SAD_UP8);
        else if (Ncook == flor)    Ecook = EFFECT_MAXSAD_UP10;
        else if (Ncook == bread)   Ecook = EFFECT_MAXHAP_UP5;
        else if (Ncook == bananas) Ecook = EFFECT_MAXSAD_UP10;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_SAD_UP8        : static_cast<float>(EFFECT_HAP_UP10);
        else                       Ecook = EFFECT_NONE;
    } else {
        Ecook = EFFECT_NONE;
    }
    return static_cast<int>(Ecook);
}

int meal_all() { return Camount; }

// ── Backpack helpers ──
void Cpushback(const std::string& bloodyname, int bloodycalr,
               int bloodyspend, int bloodyall, float bloodyeffect) {
    backpackmeal.push_back(bloodyname);
    backpackcalr.push_back(bloodycalr);
    backpackspend.push_back(bloodyspend);
    backpackall.push_back(bloodyall);
    backpackeffect.push_back(bloodyeffect);
    ++Cid;
}

void Cclean() {
    for (unsigned int i = 1; i < Cid; ++i)
        backpackmeal[i - 1] = "";
    Cid = 0;
}

void Cdrop(int IDI) {
    backpackmeal[IDI] = "";
    Cid = Cid - 1;
    for (unsigned int i = IDI; i < Cid; ++i) {
        backpackmeal[i]  = backpackmeal[i + 1];
        backpackcalr[i]  = backpackcalr[i + 1];
        backpackspend[i] = backpackspend[i + 1];
        backpackall[i]   = backpackall[i];  // bug preserved: should be [i+1]
    }
}

void Cfour() {
    for (int i = 0; i < 5; ++i) {
        if (storage[i] <= 0)
            storage[i] = 0;
    }
}

// ── Cooking UI ──
// Fixes original bug where `inter_trans` input was ignored; now properly assigns
// user input to `storageAdding[rounder]` so the cooking system actually works.
void handle_putting() {
    wrongtype = false;
    cout << "(You can input 0 to quit this menu)\n";

    // Reset storageAdding
    for (int i = 0; i < 5; ++i) storageAdding[i] = 0;

    for (int rounder = 0; rounder < 5; ++rounder) {
        unsigned int inter_trans;
        cout << "How much ";
        if      (rounder == 0) cout << "sugar";
        else if (rounder == 1) cout << "salt";
        else if (rounder == 2) cout << "sodium bicarbonate";
        else if (rounder == 3) cout << "water";
        else                   cout << "flour";
        cout << " do you want to put in? Input the number of ";
        cout << (rounder == 3 ? "milliliter" : "grams") << " :";

        cin >> inter_trans;
        badint();
        if (isbadint || inter_trans <= 0) {
            wrongtype = true;
            break;
        }
        if (inter_trans > storage[rounder]) {
            cout << "You don't have enough! You only have "
                 << storage[rounder] << ".\n";
            break;
        }
        storageAdding[rounder] = inter_trans;
        storage[rounder] -= inter_trans;
    }

    cook(storageAdding[0], storageAdding[1], storageAdding[2],
         storageAdding[3], storageAdding[4], false);

    // Build meal name from taste + name
    std::string Meal = Tmeal[10 + meal_tas()] + " " + meal[meal_nam()];
    cout << Meal << "!\n";
    calr = cook(storageAdding[0], storageAdding[1], storageAdding[2],
                storageAdding[3], storageAdding[4], true);
    cout << "The energy of this dish is " << calr << " calories!\n";
    Cpushback(Meal, calr,
              storageAdding[0] * 8 + storageAdding[1] * 13 + storageAdding[2] * 9,
              meal_all(), static_cast<float>(meal_effect()));
}

void Cincook() {
    colorc(blue);
    cout << "You have " << storage[0] << " grams of sugar\n"
         << "You have " << storage[1] << " grams of salt\n"
         << "You have " << storage[2] << " grams of soda\n"
         << "You have " << storage[3] << " milliliter of water (1000 ml max)\n"
         << "You have " << storage[4] << " grams of flour\n";
    colorc(white);
    pausers::pause();

    cout << "Keep cooking? (Press Y to continue, press N to quit this menu)\n";
    while (true) {
        key = getch();
        if (YES_KEY) { Jcook = false; break; }
        if (NO_KEY)  { Jcook = true;  break; }
    }
    if (!Jcook) handle_putting();
    else        Jcook = false;
    hyphen(4);
}
