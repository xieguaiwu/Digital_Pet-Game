# Digital Pet 🐾

A personal C++ console-based virtual pet game for **Windows and Linux**, started in **May 2022**.

> **Note:** Most of the code was written when the author was just learning how to program. Updates happen on a random schedule.

---

## Table of Contents

- [Building & Running](#building--running)
- [Controls](#controls)
- [Core Stats](#core-stats)
- [Species & Lifespan](#species--lifespan)
- [Random Events](#random-events)
- [Loans](#loans)
- [Cooking System](#cooking-system)
  - [Ingredients](#ingredients)
  - [Food Recipes](#food-recipes)
  - [Flavor Profiles](#flavor-profiles)

---

## Building & Running

### Linux

```bash
g++ -o DigitalPet DigitalPet.cpp
./DigitalPet
```

### Windows

Compile with any C++ compiler (MinGW, MSVC):

```bash
g++ -o DigitalPet.exe DigitalPet.cpp
DigitalPet.exe
```

> Pre-built binaries (`DigitalPet` for Linux, `DigitalPet.exe` for Windows) are included in the repository.

---

## Controls

| Key | Action | Costs a Turn? |
|:---:|--------|:-------------:|
| (any action key) | Perform the selected action | ✅ Yes |
| `S` | Clear screen | ❌ No |
| `C` | Check pet status | ❌ No |
| `B` | View cooking ingredients | ✅ Yes |
| `M` | Enter money / loan / cooking interface | ✅ Yes |
| `O` | View stored cooked dishes | ✅ Yes |

Each day consists of **8 action turns**. Screen-clearing (`S`) and status-checking (`C`) are free actions.

> ⚠️ Switch to **English input method** before starting the game.

---

## Core Stats

| Stat | Range | Notes |
|:-----|:-----:|:------|
| **Happiness** | 0 – 100 | Decreases when the pet's needs (excretion / hunger) are ignored. |
| **Sadness** | 0 – 50 | Increases when needs are ignored. **If Sadness reaches 50, the pet dies.** |
| **Needs Excretion** | Yes / No | Each turn waited ↓ Happiness, ↑ Sadness. |
| **Needs Food** | Yes / No | Each turn waited ↓ Happiness, ↑ Sadness. |

The pet alternates between needing food and needing excretion — keeping both satisfied is the core loop.

---

## Species & Lifespan

There are two pet species, chosen at the start of the game:

| Species | Base Lifespan (days) |
|:--------|:--------------------:|
| **Cat** | Random between 730 (2 years) and 1460 (4 years) |
| **Dog** | Random between 548 (1.5 years) and 1825 (5 years) |

### Lifespan Extension

- At birth, the pet is assigned a **Happiness threshold** between **60 and 85**.
- This threshold **increases by 5 every day** until it can no longer rise.
- Whenever the pet's current **Happiness > threshold**, its lifespan **increases by 1 day**.
- Lifespan extension is checked only on **odd-numbered turns** (turn 1, 3, 5, 7) within the day's 8 turns.
- Days spent in the *"Pet's Avant-Garde Rock Band"* random event do **not** count toward the pet's aging.

---

## Random Events

Triggered on **Day ≥ 1** (version 0.1.1+):

| # | Event | Description |
|:-:|:------|:------------|
| ① | **Money Gift** | The pet brings you $0–35 (no trigger if $0). |
| ② | **Pet Investor** | Invest all your money → increases Happiness, decreases Sadness. Results appear after a random number of days. **25% success rate**, return 10%–50% profit. |
| ③ | **Product Promotion** | The pet promotes three product sets with probabilities 40%, 40%, and 20%. |
| ④ | **Rock Band** 🎸 | The pet forms an avant-garde rock band and earns you money! **One-time event** — triggers only once per save. |
| ⑤ | **Ingredient Gift** | The pet brings you 1 of 5 random cooking ingredients, quantity **1–35**. |

---

## Loans

- Press `M` to enter the money interface.
- **Loan limit:** Up to 10× your current money. Cannot take a loan if you have $0.
- **Interest:** Random rate between **1% and 10%**.
- **Repayment period:** Random number of days.
- **Overdue:** Each extra day adds the original interest rate to the debt.
- **Debt collection:** If collectors visit and you cannot pay, each occurrence **decreases Happiness** and **increases Sadness**.

---

## Cooking System

### Ingredients

There are **5 ingredients**:

| Ingredient | Notes |
|:-----------|:------|
| Sugar | Purchasable |
| Salt | Purchasable |
| Baking Soda | Purchasable |
| Water | **Free**, but capped at **1000 ml** |
| Flour | Purchasable |

> 🧠 *Air* is listed in the shop but has **no effect** — don't let shady merchants fool you.

Press `B` on the main screen to check your inventory.  
Press `M` to enter the shopping / cooking interface.

### Food Recipes

Quantities of each ingredient determine the resulting dish:

| # | Food | Recipe |
|:-:|:-----|:-------|
| ① | **Air** | All ingredients = 0 |
| ② | **Soda Water** | Water + Baking Soda (Water > Baking Soda), and doesn't match any other recipe |
| ③ | **Wet Baking Soda** | Same as Soda Water, but Baking Soda > Water |
| ④ | **Unnameable Object** | Ingredients don't satisfy any other recipe |
| ⑤ | **Batter** | Water + Flour, and doesn't match Bread or Cake |
| ⑥ | **Bread** | Water ≤ Baking Soda, Flour > 0, Water ≤ 20% of total, Flour > Baking Soda, Sugar ≤ all others |
| ⑦ | **Cake** | Same as Bread, but Sugar > all other ingredients |

### Flavor Profiles

11 flavors determined by ingredient composition:

| # | Flavor | Condition |
|:-:|:-------|:----------|
| ① | **Slightly Sweet** | Sugar is the largest component, and Sugar < 50% of total weight |
| ② | **Very Sweet** | Sugar is the largest component, and Sugar ≥ 50% of total weight |
| ③ | **Slightly Salty** | Salt is the largest component, and Salt < 50% of total weight |
| ④ | **Very Salty** | Salt is the largest component, and Salt ≥ 50% of total weight |
| ⑤ | **Slightly Moist** | Water is the largest component, and Water < 50% of total weight |
| ⑥ | **Very Moist** | Water is the largest component, and Water ≥ 50% of total weight |
| ⑦ | **Slightly Soft** | Flour ≤ Water, Flour > all others, and Flour < 50% of total weight |
| ⑧ | **Very Soft** | Flour ≤ Water, Flour > all others, and Flour ≥ 50% of total weight |
| ⑨ | **Gassy** | Baking Soda > all other ingredients |
| ⑩ | **Bland** | None of the above conditions are met |
| ⑪ | **Very Dry** | Flour > 0, Water = 0 |

> **Future plans:** Selling and using cooked dishes will be added in the next update. The current "Discard" function in the `O` interface is a test for the upcoming inventory system.

---

## License

This is a personal hobby project. No license specified — all rights reserved unless otherwise noted.
