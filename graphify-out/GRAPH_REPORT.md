# Graph Report - .  (2026-07-29)

## Corpus Check
- cluster-only mode — file stats not available

## Summary
- 257 nodes · 597 edges · 14 communities
- Extraction: 60% EXTRACTED · 40% INFERRED · 0% AMBIGUOUS · INFERRED: 236 edges (avg confidence: 0.8)
- Token cost: 653 input · 879 output

## Graph Freshness
- Built from commit: `0bbae8de`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Game Input & Language
- Cooking Ingredients
- Diary & Cheating
- Event Conditions
- Internationalization & Notices
- Game State Notices
- Cooking Mechanics
- Bug Reports & Architecture
- Body Part Types
- Minigames

## God Nodes (most connected - your core abstractions)
1. `tr()` - 62 edges
2. `tr_f()` - 44 edges
3. `hyphen()` - 28 edges
4. `getch()` - 23 edges
5. `interact()` - 17 edges
6. `IngredientReq` - 15 edges
7. `notices` - 15 edges
8. `handle_cheating()` - 14 edges
9. `starter_notice()` - 14 edges
10. `rand_range()` - 14 edges

## Surprising Connections (you probably didn't know these)
- `starter_notice()` --calls--> `init`  [EXTRACTED]
  src/Game.cpp → include/EventConfig.h
- `starter_notice()` --calls--> `init`  [EXTRACTED]
  src/Game.cpp → include/RecipeDB.h
- `RecipeDB::match()` --calls--> `is_all_zero`  [INFERRED]
  src/RecipeDB.cpp → include/RecipeDB.h
- `RecipeDB::match()` --calls--> `exact_match`  [INFERRED]
  src/RecipeDB.cpp → include/RecipeDB.h
- `RecipeDB::match()` --calls--> `loose_match`  [INFERRED]
  src/RecipeDB.cpp → include/RecipeDB.h

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Bugs fixed by Plan A** — architecture_bug1, architecture_bug2, architecture_bug3, architecture_bug4, architecture_bug5, architecture_bug6, architecture_bug7, architecture_bug8, architecture_bug9, architecture_bug10, architecture_bug11 [INFERRED 0.80]
- **Four Architecture Plans** — architecture_plan_a, architecture_plan_b, architecture_plan_c, architecture_plan_d [EXTRACTED 1.00]

## Communities (14 total, 0 thin omitted)

### Community 0 - "Game Input & Language"
Cohesion: 0.12
Nodes (43): Language, Cdrop(), Cincook_v2(), choose_language(), death(), e_age(), e_eat(), e_hap() (+35 more)

### Community 1 - "Cooking Ingredients"
Cohesion: 0.07
Nodes (30): vector, IngredientReq, chocolate, eggs, flour, milk, salt, soda (+22 more)

### Community 2 - "Diary & Cheating"
Cohesion: 0.19
Nodes (28): string, diary_add(), diary_new_day(), diary_view(), band_days(), Bback(), Binteract(), Btv1() (+20 more)

### Community 3 - "Event Conditions"
Cohesion: 0.08
Nodes (22): EventHandler, EventCondition, evaluate, once_flag, once_only, require_money_gt_0, require_no_investment, require_not_Bband (+14 more)

### Community 4 - "Internationalization & Notices"
Cohesion: 0.13
Nodes (23): string, tr_f(), colorc(), notices::bought_success(), notices::choose_again(), notices::hap_minus(), notices::hap_plus(), notices::lifespan_minus() (+15 more)

### Community 5 - "Game State Notices"
Cohesion: 0.09
Nodes (21): notices, bought_success, choose_again, hap_minus, hap_plus, lifespan_minus, lifespan_plus, money_have (+13 more)

### Community 6 - "Cooking Mechanics"
Cohesion: 0.16
Nodes (20): match, Cfour(), Cincook(), cook(), cook_random_notice(), cook_v2(), string, Cpushback() (+12 more)

### Community 7 - "Bug Reports & Architecture"
Cohesion: 0.16
Nodes (16): Bug 1: Cdrop self-assignment, Bug 10: S key consumes turn, Bug 11: handle_putting material loss, Bug 2: Salt price display mismatch, Bug 3: badint EOF infinite loop, Bug 4: Ecook type float->int, Bug 5: Cclean incomplete clear, Bug 6: ANSI color missing on Linux (+8 more)

### Community 8 - "Body Part Types"
Cohesion: 0.27
Nodes (11): TypesGive, arm_type_give, face_type_give, leg_type_give, body_describe(), certain_body_give(), have_body(), have_body_ini() (+3 more)

### Community 9 - "Minigames"
Cohesion: 0.67
Nodes (5): handle_minigames(), play_dice(), play_guess_number(), play_slot_machine(), badint_clear()

## Knowledge Gaps
- **50 isolated node(s):** `require_money_gt_0`, `require_no_investment`, `require_not_Bband`, `once_only`, `once_flag` (+45 more)
  These have ≤1 connection - possible missing edges or undocumented components.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `tr()` connect `Diary & Cheating` to `Game Input & Language`, `Minigames`, `Internationalization & Notices`, `Cooking Mechanics`?**
  _High betweenness centrality (0.198) - this node is a cross-community bridge._
- **Why does `starter_notice()` connect `Cooking Mechanics` to `Game Input & Language`, `Cooking Ingredients`, `Diary & Cheating`, `Event Conditions`, `Internationalization & Notices`, `Body Part Types`?**
  _High betweenness centrality (0.118) - this node is a cross-community bridge._
- **Are the 59 inferred relationships involving `tr()` (e.g. with `Cincook()` and `Cincook_v2()`) actually correct?**
  _`tr()` has 59 INFERRED edges - model-reasoned connections that need verification._
- **Are the 40 inferred relationships involving `tr_f()` (e.g. with `Cincook()` and `Cincook_v2()`) actually correct?**
  _`tr_f()` has 40 INFERRED edges - model-reasoned connections that need verification._
- **Are the 27 inferred relationships involving `hyphen()` (e.g. with `Cincook()` and `Cincook_v2()`) actually correct?**
  _`hyphen()` has 27 INFERRED edges - model-reasoned connections that need verification._
- **Are the 20 inferred relationships involving `getch()` (e.g. with `Cincook()` and `Cincook_v2()`) actually correct?**
  _`getch()` has 20 INFERRED edges - model-reasoned connections that need verification._
- **Are the 3 inferred relationships involving `interact()` (e.g. with `diary_view()` and `handle_minigames()`) actually correct?**
  _`interact()` has 3 INFERRED edges - model-reasoned connections that need verification._