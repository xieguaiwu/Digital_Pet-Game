#ifndef DIGITALPET_COOKING_H
#define DIGITALPET_COOKING_H

#include "Types.h"
#include "RecipeDB.h"
#include <string>

// ── Cooking functions ──
int cook(unsigned int Psug, unsigned int Psul, unsigned int Psod,
         unsigned int Pwat, unsigned int Pflo, bool CookOrCal = false);
int cook_v2(const IngredientReq& amt, bool CookOrCal = false);
int meal_nam();    // determine dish name
int meal_tas();    // determine taste
int meal_effect(); // determine effect
int meal_all();    // total amount

void Mname();      // populate dish-name map
void Mname1();     // populate taste-name map
void Ename();      // populate effect-name map

// ── Backpack helpers ──
void Cpushback(const std::string& bloodyname, int bloodycalr,
               int bloodyspend, int bloodyall, int bloodyeffect);
void Cclean();
void Cdrop(int IDI);
void Cfour();

// ── Cooking UI ──
void handle_putting();
void handle_putting_v2();
void Cincook();
void Cincook_v2();
void cook_random_notice();

#endif // DIGITALPET_COOKING_H
