#include "RecipeDB.h"
#include "i18n.h"
#include <cstring>

// ── Ingredient display names ──
const char* ingredient_name[ING_COUNT] = {
    "sugar",       // ING_SUGAR=0
    "salt",        // ING_SALT=1
    "soda",        // ING_SODA=2
    "water",       // ING_WATER=3
    "flour",       // ING_FLOUR=4
    "milk",        // ING_MILK=5
    "eggs",        // ING_EGGS=6
    "chocolate"    // ING_CHOCOLATE=7
};

// ── Static recipe storage ──
std::vector<RecipeDef> RecipeDB::s_recipes;

// ── Helper: all fields zero ──
bool RecipeDB::is_all_zero(const IngredientReq& a) {
    return a.sugar == 0 && a.salt == 0 && a.soda == 0 && a.water == 0
        && a.flour == 0 && a.milk == 0 && a.eggs == 0 && a.chocolate == 0;
}

// ── Helper: exact match ──
// User must provide exactly the required amounts for each ingredient.
// If recipe requires 0 of an ingredient, user must also provide 0 of it.
// If recipe requires N > 0, user must provide exactly N.
bool RecipeDB::exact_match(const IngredientReq& user, const IngredientReq& req) {
    if (user.sugar     != req.sugar)     return false;
    if (user.salt      != req.salt)      return false;
    if (user.soda      != req.soda)      return false;
    if (user.water     != req.water)     return false;
    if (user.flour     != req.flour)     return false;
    if (user.milk      != req.milk)      return false;
    if (user.eggs      != req.eggs)      return false;
    if (user.chocolate != req.chocolate) return false;
    return true;
}

// ── Helper: loose match ──
// User must provide at least the required amount for each ingredient the recipe needs.
// Extra ingredients (where req == 0) are tolerated.
bool RecipeDB::loose_match(const IngredientReq& user, const IngredientReq& req) {
    if (req.sugar     > 0 && user.sugar     < req.sugar)     return false;
    if (req.salt      > 0 && user.salt      < req.salt)      return false;
    if (req.soda      > 0 && user.soda      < req.soda)      return false;
    if (req.water     > 0 && user.water     < req.water)     return false;
    if (req.flour     > 0 && user.flour     < req.flour)     return false;
    if (req.milk      > 0 && user.milk      < req.milk)      return false;
    if (req.eggs      > 0 && user.eggs      < req.eggs)      return false;
    if (req.chocolate > 0 && user.chocolate < req.chocolate) return false;
    return true;
}

// ── Initialise recipe database ──
void RecipeDB::init() {
    s_recipes.clear();

    // Use minimal requirement of 1 unit for each key ingredient.
    // For old recipes, simplified representative requirements.
    // Order matches MealType enum: air=0, soda=1, indefine=2, flor=3,
    //   bread=4, bananas=5, cake=6, pizza=7, cookie=8, pancake=9,
    //   omelette=10, pudding=11.

    // 0: air
    s_recipes.push_back({
        "air", air, flat,
        {0,0,0,0,0,0,0,0},      // req: all zero
        EFFECT_NONE, 0
    });

    // 1: soda water
    s_recipes.push_back({
        "soda water", soda, too_sod,
        {0,0,1,1,0,0,0,0},      // req: soda=1, water=1
        EFFECT_NONE, 50
    });

    // 2: unnamable black item (indefine — catch-all, placed early but low priority)
    s_recipes.push_back({
        "unnamable black item", indefine, flat,
        {0,0,0,0,0,0,0,0},      // req: minimal — matched only as last resort
        EFFECT_NONE, 0
    });

    // 3: paste (flor)
    s_recipes.push_back({
        "paste", flor, floy,
        {0,0,0,1,1,0,0,0},      // req: water=1, flour=1
        EFFECT_NONE, 200
    });

    // 4: bread
    s_recipes.push_back({
        "bread", bread, sult,
        {0,0,0,0,1,0,0,0},      // req: flour=1 (simplified)
        EFFECT_LIFE_UP2, 400
    });

    // 5: soda with water (bananas)
    s_recipes.push_back({
        "soda with water", bananas, too_sod,
        {0,0,1,0,0,0,0,0},      // req: soda=1 (simplified)
        EFFECT_HAP_UP10, 100
    });

    // 6: cake
    s_recipes.push_back({
        "cake", cake, sweet,
        {1,0,0,0,1,0,0,0},      // req: sugar=1, flour=1
        EFFECT_LIFE_UP1, 500
    });

    // ══════════════════  NEW RECIPES (Plan B) ══════════════════

    // 7: pizza — 面粉+鸡蛋+巧克力, 效果=LIFE_UP2, 热量=1200, 咸味
    s_recipes.push_back({
        "pizza", pizza, sult,
        {0,0,0,0,1,0,1,1},      // req: flour=1, eggs=1, chocolate=1
        EFFECT_LIFE_UP2, 1200
    });

    // 8: cookie — 面粉+巧克力+糖, 效果=HAP_UP15, 热量=800, 甜味
    s_recipes.push_back({
        "cookie", cookie, sweet,
        {1,0,0,0,1,0,0,1},      // req: sugar=1, flour=1, chocolate=1
        EFFECT_HAP_UP15, 800
    });

    // 9: pancake — 面粉+鸡蛋+牛奶, 效果=MAXHAP_UP5, 热量=600, 微甜
    s_recipes.push_back({
        "pancake", pancake, sweet,
        {0,0,0,0,1,1,1,0},      // req: flour=1, milk=1, eggs=1
        EFFECT_MAXHAP_UP5, 600
    });

    // 10: omelette — 鸡蛋+牛奶, 效果=SAD_DOWN8, 热量=500, 微咸
    s_recipes.push_back({
        "omelette", omelette, sult,
        {0,0,0,0,0,1,1,0},      // req: milk=1, eggs=1
        EFFECT_SAD_DOWN8, 500
    });

    // 11: pudding — 牛奶+鸡蛋+巧克力+糖, 效果=HAP_UP20, 热量=900, 很甜
    s_recipes.push_back({
        "pudding", pudding, Vsweet,
        {1,0,0,0,0,1,1,1},      // req: sugar=1, milk=1, eggs=1, chocolate=1
        EFFECT_HAP_UP20, 900
    });
}

// ── Match user's ingredient amounts to a recipe ──
// Priority: air (all zero) → exact match → loose match (best fit) → -1 fallback
int RecipeDB::match(const IngredientReq& amt) {
    // 0. All zero → air (index 0)
    if (is_all_zero(amt))
        return 0;

    // 1. Exact match — try all recipes (except air which we already handled)
    for (size_t i = 1; i < s_recipes.size(); ++i) {
        if (exact_match(amt, s_recipes[i].req))
            return static_cast<int>(i);
    }

    // 2. Loose match — find the best-fitting recipe
    // "Best" = recipe with the most non-zero requirements (most specific)
    int best_idx = -1;
    size_t best_specificity = 0;
    for (size_t i = 1; i < s_recipes.size(); ++i) {
        if (!loose_match(amt, s_recipes[i].req))
            continue;
        // Count how many ingredients this recipe requires
        size_t spec = 0;
        const IngredientReq& r = s_recipes[i].req;
        if (r.sugar > 0)     ++spec;
        if (r.salt > 0)      ++spec;
        if (r.soda > 0)      ++spec;
        if (r.water > 0)     ++spec;
        if (r.flour > 0)     ++spec;
        if (r.milk > 0)      ++spec;
        if (r.eggs > 0)      ++spec;
        if (r.chocolate > 0) ++spec;
        if (spec > best_specificity) {
            best_specificity = spec;
            best_idx = static_cast<int>(i);
        }
    }
    return best_idx;  // may be -1 if nothing matched
}

// ── Accessors ──
const RecipeDef& RecipeDB::get(int idx) {
    return s_recipes[static_cast<size_t>(idx)];
}

const std::vector<RecipeDef>& RecipeDB::all() {
    return s_recipes;
}

size_t RecipeDB::count() {
    return s_recipes.size();
}
