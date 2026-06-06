#include "Cooking.h"
#include "GameState.h"
#include "Utils.h"
#include "i18n.h"

#include <iostream>

using std::cout;
using std::cin;

// ── Populate dish-name map ──
void Mname() {
    meal[0]  = "air";
    meal[1]  = "soda water";
    meal[2]  = "unnamable black item";
    meal[3]  = "paste";
    meal[4]  = "bread";
    meal[5]  = "soda with water";
    meal[6]  = "cake";
    meal[7]  = "pizza";
    meal[8]  = "cookie";
    meal[9]  = "pancake";
    meal[10] = "omelette";
    meal[11] = "pudding";
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
    effects[EFFECT_LIFE_UP3]      = "Lifespan [+3]";
    effects[EFFECT_HAP_UP20]      = "Happiness [+20]";
    effects[EFFECT_SAD_DOWN10]    = "Sadness [-10]";
    effects[EFFECT_MAXSAD_DOWN15] = "Limit of Sadness [-15]";
}

// ── Cooking random notice ──
void cook_random_notice() {
    int Rcook = 1 + rand() % 3;
    if (Rcook == 1) {
        cout << tr(StrId::COOK_NOTICE_1);
    } else if (Rcook == 2) {
        cout << tr(StrId::COOK_NOTICE_2);
    } else {
        cout << tr(StrId::COOK_NOTICE_3);
    }
}

// ── Cook (returns dish type index or calorie count) ──
int cook(unsigned int Psug, unsigned int Psul, unsigned int Psod,
         unsigned int Pwat, unsigned int Pflo, bool CookOrCal) {
    Msug = Psug; Msul = Psul; Msod = Psod; Mwat = Pwat; Mflo = Pflo;
    Camount = Psug + Psul + Psod + Pwat + Pflo;

    if (!CookOrCal) {
        if (Psug == 0 && Psul == 0 && Psod == 0 && Pwat == 0 && Pflo == 0) {
            cout << tr(StrId::COOK_EMPTY_POT);
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
// All EFFECT_* are int; Ecook is now int — no float casts needed.
int meal_effect() {
    if (Tcook == sweet) {
        switch (Ncook) {
        default:       Ecook = EFFECT_MAXHAP_UP5;  break;
        case soda:     Ecook = EFFECT_HAP_UP15;   break;
        case flor:     Ecook = EFFECT_SAD_UP5;    break;
        case cake:     Ecook = EFFECT_LIFE_UP1;   break;
        case indefine: Ecook = EFFECT_MAXSAD_UP5; break;
        case bananas:  Ecook = EFFECT_SAD_DOWN5;  break;
        }
    } else if (Tcook == Vsweet) {
        switch (Ncook) {
        default:       Ecook = EFFECT_MAXSAD_UP5;  break;
        case soda:     Ecook = EFFECT_LIFE_DOWN1;  break;
        case flor:     Ecook = EFFECT_SAD_UP8;     break;
        case cake:     Ecook = EFFECT_MAXHAP_UP15; break;
        case indefine: Ecook = EFFECT_SAD_UP8;     break;
        case bananas:  Ecook = EFFECT_SAD_DOWN8;   break;
        }
    } else if (Tcook == sult) {
        switch (Ncook) {
        default:       Ecook = EFFECT_MAXHAP_DOWN5;  break;
        case soda:     Ecook = EFFECT_MAXHAP_UP15;   break;
        case indefine: Ecook = EFFECT_MAXSAD_UP10;   break;
        case flor:     Ecook = EFFECT_HAP_UP10;      break;
        case bread:    Ecook = EFFECT_LIFE_UP2;      break;
        case bananas:  Ecook = EFFECT_SAD_UP8;       break;
        case cake:     Ecook = EFFECT_SAD_UP5;       break;
        }
    } else if (Tcook == Vsult) {
        switch (Ncook) {
        default:       Ecook = EFFECT_MAXHAP_DOWN15; break;
        case soda:     Ecook = EFFECT_LIFE_UP1;      break;
        case flor:     Ecook = EFFECT_MAXSAD_UP10;   break;
        case bread:    Ecook = EFFECT_MAXHAP_UP15;   break;
        case bananas:  Ecook = EFFECT_LIFE_DOWN1;    break;
        case cake:     Ecook = EFFECT_SAD_UP8;       break;
        }
    } else if (Tcook == mois) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_NONE        : EFFECT_MAXHAP_UP5;
        else if (Ncook == flor)    Ecook = EFFECT_NONE;
        else if (Ncook == bread)   Ecook = (Pab == cat) ? EFFECT_HAP_UP10    : EFFECT_SAD_UP5;
        else if (Ncook == bananas) Ecook = EFFECT_NONE;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_HAP_UP15    : EFFECT_SAD_DOWN5;
        else                       Ecook = (Pab == cat) ? EFFECT_SAD_DOWN5   : EFFECT_SAD_UP5;
    } else if (Tcook == Vmois) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_NONE        : EFFECT_MAXHAP_UP5;
        else if (Ncook == flor)    Ecook = (Pab == cat) ? EFFECT_NONE        : EFFECT_SAD_UP5;
        else if (Ncook == bread)   Ecook = (Pab == cat) ? EFFECT_HAP_UP15    : EFFECT_SAD_UP5;
        else if (Ncook == bananas) Ecook = EFFECT_NONE;
        else if (Ncook == cake)    Ecook = EFFECT_MAXHAP_UP15;
        else                       Ecook = (Pab == cat) ? EFFECT_SAD_DOWN8   : EFFECT_SAD_UP8;
    } else if (Tcook == too_sod) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_MAXHAP_DOWN5 : EFFECT_NONE;
        else if (Ncook == flor)    Ecook = (Pab == cat) ? EFFECT_SAD_UP5      : EFFECT_NONE;
        else if (Ncook == bread)   Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP15  : EFFECT_HAP_UP15;
        else if (Ncook == bananas) Ecook = EFFECT_NONE;
        else if (Ncook == cake)    Ecook = EFFECT_SAD_DOWN8;
        else                       Ecook = EFFECT_NONE;
    } else if (Tcook == floy) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_HAP_UP10    : EFFECT_MAXHAP_UP5;
        else if (Ncook == flor)    Ecook = EFFECT_HAP_UP10;
        else if (Ncook == bread)   Ecook = EFFECT_MAXHAP_UP15;
        else if (Ncook == bananas) Ecook = EFFECT_SAD_UP8;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_HAP_UP10    : EFFECT_HAP_UP15;
        else                       Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP5  : EFFECT_NONE;
    } else if (Tcook == Vfloy) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_HAP_UP15    : EFFECT_MAXHAP_UP15;
        else if (Ncook == flor)    Ecook = EFFECT_HAP_UP15;
        else if (Ncook == bread)   Ecook = EFFECT_SAD_UP5;
        else if (Ncook == bananas) Ecook = EFFECT_MAXSAD_UP5;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_HAP_UP15    : EFFECT_MAXHAP_UP15;
        else                       Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP15 : EFFECT_HAP_UP10;
    } else if (Tcook == dry) {
        if      (Ncook == soda)    Ecook = (Pab == cat) ? EFFECT_MAXHAP_UP5  : EFFECT_SAD_UP8;
        else if (Ncook == flor)    Ecook = EFFECT_MAXSAD_UP10;
        else if (Ncook == bread)   Ecook = EFFECT_MAXHAP_UP5;
        else if (Ncook == bananas) Ecook = EFFECT_MAXSAD_UP10;
        else if (Ncook == cake)    Ecook = (Pab == cat) ? EFFECT_SAD_UP8     : EFFECT_HAP_UP10;
        else                       Ecook = EFFECT_NONE;
    } else {
        Ecook = EFFECT_NONE;
    }
    return Ecook;
}

int meal_all() { return Camount; }

// ── Backpack helpers ──
void Cpushback(const std::string& bloodyname, int bloodycalr,
               int bloodyspend, int bloodyall, int bloodyeffect) {
    backpackmeal.push_back(bloodyname);
    backpackcalr.push_back(bloodycalr);
    backpackspend.push_back(bloodyspend);
    backpackall.push_back(bloodyall);
    backpackeffect.push_back(bloodyeffect);
    ++Cid;
}

void Cclean() {
    backpackmeal.clear();
    backpackcalr.clear();
    backpackspend.clear();
    backpackall.clear();
    backpackeffect.clear();
    Cid = 0;
}

void Cdrop(int IDI) {
    if (Cid <= 0 || IDI < 0 || IDI >= Cid) return;
    backpackmeal[IDI] = "";
    Cid = Cid - 1;
    for (int i = IDI; i < Cid; ++i) {
        backpackmeal[i]   = backpackmeal[i + 1];
        backpackcalr[i]   = backpackcalr[i + 1];
        backpackspend[i]  = backpackspend[i + 1];
        backpackall[i]    = backpackall[i + 1];
        backpackeffect[i] = backpackeffect[i + 1];
    }
    // Trim the now-duplicate last elements
    backpackmeal.pop_back();
    backpackcalr.pop_back();
    backpackspend.pop_back();
    backpackall.pop_back();
    backpackeffect.pop_back();
}

void Cfour() {
    for (int i = 0; i < ING_COUNT; ++i) {
        if (storage[i] == 0)
            storage[i] = 0;
    }
}

// ── Cooking UI ──
// Bug #11 fix: accumulate all ingredients in storageAdding first,
// then deduct from storage atomically after confirmation — prevents
// ingredient loss when user aborts mid-input.
void handle_putting() {
    wrongtype = false;
    cout << tr(StrId::COOK_QUIT_HINT) << "\n";

    // Reset storageAdding
    for (int i = 0; i < ING_COUNT; ++i) storageAdding[i] = 0;

    for (int rounder = 0; rounder < 5; ++rounder) {
        unsigned int inter_trans;
        cout << tr(StrId::COOK_HOW_MUCH);
        if      (rounder == 0) cout << tr(StrId::COOK_ING_SUGAR);
        else if (rounder == 1) cout << tr(StrId::COOK_ING_SALT);
        else if (rounder == 2) cout << tr(StrId::COOK_ING_SODA);
        else if (rounder == 3) cout << tr(StrId::COOK_ING_WATER);
        else                   cout << tr(StrId::COOK_ING_FLOUR);
        cout << tr(StrId::COOK_PUT_IN);
        cout << (rounder == 3 ? tr(StrId::COOK_MILLILITER) : tr(StrId::COOK_GRAMS));
        cout << tr(StrId::COOK_COLON);

        cin >> inter_trans;
        badint_clear();
        if (isbadint || inter_trans <= 0) {
            wrongtype = true;
            break;
        }
        if (inter_trans > storage[rounder]) {
            cout << tr_f(StrId::COOK_NOT_ENOUGH, storage[rounder]) << "\n";
            wrongtype = true;
            break;
        }
        storageAdding[rounder] = inter_trans;
        // Defer deduction — do NOT subtract from storage here (Bug #11)
    }

    // Only deduct and cook if all inputs were valid (no early break)
    if (wrongtype) return;

    // Atomically deduct all ingredients from storage
    for (int i = 0; i < ING_COUNT; ++i)
        storage[i] -= storageAdding[i];

    cook(storageAdding[0], storageAdding[1], storageAdding[2],
         storageAdding[3], storageAdding[4], false);

    // Build meal name from taste + name
    std::string Meal = Tmeal[10 + meal_tas()] + " " + meal[meal_nam()];
    cout << Meal << "!\n";
    calr = cook(storageAdding[0], storageAdding[1], storageAdding[2],
                storageAdding[3], storageAdding[4], true);
    cout << tr_f(StrId::COOK_ENERGY, calr) << "\n";
    Cpushback(Meal, calr,
              storageAdding[0] * 8 + storageAdding[1] * 13 + storageAdding[2] * 9,
              meal_all(), meal_effect());
}

void Cincook() {
    colorc(blue);
    cout << tr_f(StrId::COOK_DISPLAY_SUGAR, storage[0]) << "\n"
         << tr_f(StrId::COOK_DISPLAY_SALT, storage[1]) << "\n"
         << tr_f(StrId::COOK_DISPLAY_SODA, storage[2]) << "\n"
         << tr_f(StrId::COOK_DISPLAY_WATER, storage[3]) << "\n"
         << tr_f(StrId::COOK_DISPLAY_FLOUR, storage[4]) << "\n";
    colorc(white);
    pausers::pause();

    cout << tr(StrId::COOK_KEEP_COOKING) << "\n";
    while (true) {
        key = getch();
        if (YES_KEY) { Jcook = false; break; }
        if (NO_KEY)  { Jcook = true;  break; }
    }
    if (!Jcook) handle_putting();
    else        Jcook = false;
    hyphen(4);
}

// ═══════════════════════════════════════════
//  Plan B: v2 cooking functions (8 ingredients, RecipeDB)
// ═══════════════════════════════════════════

// ── cook_v2: handle 8 ingredients, use RecipeDB for matching ──
int cook_v2(const IngredientReq& amt, bool CookOrCal) {
    // Populate old globals for heuristic fallback
    Msug = amt.sugar; Msul = amt.salt; Msod = amt.soda;
    Mwat = amt.water; Mflo = amt.flour;
    Camount = amt.sugar + amt.salt + amt.soda + amt.water + amt.flour
            + amt.milk + amt.eggs + amt.chocolate;

    if (!CookOrCal) {
        // Determine dish
        int recipe_idx = RecipeDB::match(amt);

        if (recipe_idx >= 0) {
            Ncook = RecipeDB::get(recipe_idx).dish;
        } else {
            // Fallback to heuristic (old 5-ingredient logic)
            Ncook = static_cast<MealType>(meal_nam());
        }
        return static_cast<int>(Ncook);
    } else {
        // Calculate calories
        int recipe_idx = RecipeDB::match(amt);
        if (recipe_idx >= 0) {
            // Use recipe's base calories
            Mcalr = static_cast<unsigned int>(RecipeDB::get(recipe_idx).base_calories);
        } else {
            // Old formula for 5 base ingredients
            Mcalr = amt.sugar * 400;
            if (amt.water > amt.flour)
                Mcalr += amt.flour * 300;
            else
                Mcalr += amt.water * 2 + (amt.flour - amt.water) * 366;
            // New ingredient calories
            Mcalr += amt.milk      * 60;
            Mcalr += amt.eggs      * 70;
            Mcalr += amt.chocolate * 500;
        }
        return static_cast<int>(Mcalr);
    }
}

// ── handle_putting_v2: 8-ingredient input loop with RecipeDB matching ──
void handle_putting_v2() {
    wrongtype = false;
    cout << tr(StrId::COOK_QUIT_HINT) << "\n";

    // StrId lookup for ingredient names indexed by rounder
    static const StrId ing_str_ids[ING_COUNT] = {
        StrId::COOK_ING_SUGAR,
        StrId::COOK_ING_SALT,
        StrId::COOK_ING_SODA,
        StrId::COOK_ING_WATER,
        StrId::COOK_ING_FLOUR,
        StrId::COOK_ING_MILK,
        StrId::COOK_ING_EGGS,
        StrId::COOK_ING_CHOCOLATE
    };

    // Reset storageAdding
    for (int i = 0; i < ING_COUNT; ++i) storageAdding[i] = 0;

    // 8 rounds of input
    for (int rounder = 0; rounder < ING_COUNT; ++rounder) {
        unsigned int inter_trans;
        cout << tr(StrId::COOK_HOW_MUCH) << tr(ing_str_ids[rounder]);
        cout << tr(StrId::COOK_PUT_IN);
        // water (index 3) and milk (index 5) use milliliters; others use grams
        if (rounder == ING_WATER || rounder == ING_MILK)
            cout << tr(StrId::COOK_MILLILITER);
        else if (rounder == ING_EGGS)
            cout << tr(StrId::COOK_PIECE);
        else if (rounder == ING_CHOCOLATE)
            cout << tr(StrId::COOK_HUNDRED_GRAM);
        else
            cout << tr(StrId::COOK_GRAMS);
        cout << tr(StrId::COOK_COLON);

        cin >> inter_trans;
        badint_clear();
        if (isbadint || inter_trans <= 0) {
            // 0 or bad input = quit
            wrongtype = true;
            break;
        }
        if (inter_trans > storage[rounder]) {
            cout << tr_f(StrId::COOK_NOT_ENOUGH, storage[rounder]) << "\n";
            wrongtype = true;
            break;
        }
        storageAdding[rounder] = inter_trans;
    }

    if (wrongtype) return;

    // Atomically deduct all ingredients
    for (int i = 0; i < ING_COUNT; ++i)
        storage[i] -= storageAdding[i];

    // Build IngredientReq from storageAdding
    IngredientReq amt;
    amt.sugar     = storageAdding[ING_SUGAR];
    amt.salt      = storageAdding[ING_SALT];
    amt.soda      = storageAdding[ING_SODA];
    amt.water     = storageAdding[ING_WATER];
    amt.flour     = storageAdding[ING_FLOUR];
    amt.milk      = storageAdding[ING_MILK];
    amt.eggs      = storageAdding[ING_EGGS];
    amt.chocolate = storageAdding[ING_CHOCOLATE];

    // Try RecipeDB matching
    int recipe_idx = RecipeDB::match(amt);

    std::string Meal;
    int effect_val;

    if (recipe_idx >= 0 && recipe_idx != 2) {  // skip indefine (index 2) as catch-all
        // RecipeDB matched — use recipe data directly
        const RecipeDef& rec = RecipeDB::get(recipe_idx);
        Meal       = Tmeal[10 + rec.taste] + " " + rec.name;
        effect_val = rec.effect;
        // Set Ncook/Tcook for compatibility
        Ncook = rec.dish;
        Tcook = rec.taste;
        cook_v2(amt, false);  // sets Ncook
    } else {
        // Fallback to heuristic
        cook_v2(amt, false);
        Meal       = Tmeal[10 + meal_tas()] + " " + meal[meal_nam()];
        effect_val = meal_effect();
    }

    cout << Meal << "!\n";
    calr = cook_v2(amt, true);
    cout << tr_f(StrId::COOK_ENERGY, calr) << "\n";

    // Calculate cost: sugar=8/salt=13(avg)/soda=9/water=0/flour=6/milk=12/eggs=15/chocolate=20
    int spend = static_cast<int>(
        storageAdding[ING_SUGAR]     * 8  +
        storageAdding[ING_SALT]      * 13 +
        storageAdding[ING_SODA]      * 9  +
        storageAdding[ING_WATER]     * 0  +
        storageAdding[ING_FLOUR]     * 6  +
        storageAdding[ING_MILK]      * 12 +
        storageAdding[ING_EGGS]      * 15 +
        storageAdding[ING_CHOCOLATE] * 20);
    Cpushback(Meal, calr, spend, Camount, effect_val);
}

// ── Cincook_v2: display all 8 ingredients ──
void Cincook_v2() {
    colorc_ansi(blue);
    cout << tr_f(StrId::COOK_DISPLAY_SUGAR,     storage[ING_SUGAR])     << "\n"
         << tr_f(StrId::COOK_DISPLAY_SALT,      storage[ING_SALT])      << "\n"
         << tr_f(StrId::COOK_DISPLAY_SODA,      storage[ING_SODA])      << "\n"
         << tr_f(StrId::COOK_DISPLAY_WATER,     storage[ING_WATER])     << "\n"
         << tr_f(StrId::COOK_DISPLAY_FLOUR,     storage[ING_FLOUR])     << "\n"
         << tr_f(StrId::COOK_DISPLAY_MILK,      storage[ING_MILK])      << "\n"
         << tr_f(StrId::COOK_DISPLAY_EGGS,      storage[ING_EGGS])      << "\n"
         << tr_f(StrId::COOK_DISPLAY_CHOCOLATE, storage[ING_CHOCOLATE]) << "\n";
    colorc_ansi(white);
    pausers::pause();

    cout << tr(StrId::COOK_KEEP_COOKING) << "\n";
    while (true) {
        key = getch();
        if (YES_KEY) { Jcook = false; break; }
        if (NO_KEY)  { Jcook = true;  break; }
    }
    if (!Jcook) handle_putting_v2();
    else        Jcook = false;
    hyphen(4);
}
