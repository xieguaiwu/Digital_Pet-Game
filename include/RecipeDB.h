#ifndef DIGITALPET_RECIPEDB_H
#define DIGITALPET_RECIPEDB_H

#include "Types.h"
#include <cstddef>
#include <vector>

// ── Ingredient amounts (8 types) ──
struct IngredientReq {
    unsigned int sugar;
    unsigned int salt;
    unsigned int soda;
    unsigned int water;
    unsigned int flour;
    unsigned int milk;
    unsigned int eggs;
    unsigned int chocolate;
};

// ── Recipe definition ──
struct RecipeDef {
    const char*   name;           // display name
    MealType      dish;           // MealType enum value
    Taste         taste;          // taste profile
    IngredientReq req;            // required ingredient amounts (0 = not required)
    int           effect;         // EFFECT_* constant
    int           base_calories;  // base calorie count
};

// ── Ingredient display names (indexed by ING_*) ──
extern const char* ingredient_name[ING_COUNT];

// ── Recipe database ──
class RecipeDB {
public:
    static void init();                              // register all recipes
    static int  match(const IngredientReq& amt);     // match input → recipe index, or -1
    static const RecipeDef& get(int idx);            // get recipe by index
    static const std::vector<RecipeDef>& all();      // all registered recipes
    static size_t count();                           // number of recipes

private:
    static std::vector<RecipeDef> s_recipes;
    static bool is_all_zero(const IngredientReq& a);
    static bool exact_match(const IngredientReq& user, const IngredientReq& req);
    static bool loose_match(const IngredientReq& user, const IngredientReq& req);
};

#endif // DIGITALPET_RECIPEDB_H
