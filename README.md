# Digital Pet 🐾

A personal C++ console-based virtual pet game for **Windows and Linux**, started in **May 2022**.

> **Note:** Most of the code was written when the author was just learning how to program. Updates happen on a random schedule.

---

## Installation via COPR (Fedora)

Available as an RPM for Fedora 42:

```bash
sudo dnf install dnf-plugins-core
sudo dnf copr enable xieguaiwu/DigitalPet
sudo dnf install DigitalPet
```

[COPR project page](https://copr.fedorainfracloud.org/coprs/xieguaiwu/DigitalPet/)

---

## Building from Source

### Linux

```bash
make
./DigitalPet
```

### Windows

```bash
g++ -std=c++11 -I include -o DigitalPet.exe src/*.cpp
DigitalPet.exe
```

---

## Project Structure

```
include/          # Headers (Types, GameState, Utils, Cooking, Body, Events, Money)
src/              # Source files
Makefile          # Build system (Linux)
packaging/        # Fedora COPR spec
```

---

## Table of Contents

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

---

## Species & Lifespan

| Species | Base Lifespan (days) |
|:--------|:--------------------:|
| **Cat** | Random between 730 (2 years) and 1460 (4 years) |
| **Dog** | Random between 548 (1.5 years) and 1825 (5 years) |

### Lifespan Extension

- Initial Happiness threshold: **60–85** (random).
- Threshold **increases by 5 every day** until it caps.
- If **Happiness > threshold**, lifespan increases by **1 day**.
- Checked only on **odd-numbered turns** (1, 3, 5, 7).
- Days in the *"Pet's Avant-Garde Rock Band"* event do **not** age the pet.

---

## Random Events

Triggered on **Day ≥ 1**:

| # | Event | Description |
|:-:|:------|:------------|
| ① | **Money Gift** | The pet brings you $0–35. |
| ② | **Pet Investor** | Invest all money → ↑Happiness, ↓Sadness. Results after random days. **25% success**, return 10–50%. |
| ③ | **Product Promotion** | Three product sets with probabilities 40%, 40%, 20%. |
| ④ | **Rock Band** 🎸 | Pet forms an avant-garde rock band. **One-time event.** |
| ⑤ | **Ingredient Gift** | Pet brings you 1 of 5 cooking ingredients, quantity **1–35**. |

---

## Loans

- Press `M` → Money interface.
- **Limit:** Up to 10× current money. Cannot loan if balance is $0.
- **Interest:** Random **1%–10%**.
- **Repayment:** Random number of days.
- **Overdue:** Debt increases by original interest rate each extra day.
- **Collection:** Each event ↓Happiness, ↑Sadness.

---

## Cooking System

### Ingredients

| Ingredient | Notes |
|:-----------|:------|
| Sugar | Purchasable |
| Salt | Purchasable |
| Baking Soda | Purchasable |
| Water | Free, capped at **1000 ml** |
| Flour | Purchasable |

### Food Recipes

| # | Food | Recipe |
|:-:|:-----|:-------|
| ① | **Air** | All ingredients = 0 |
| ② | **Soda Water** | Water + Soda (Water > Soda), doesn't match other recipes |
| ③ | **Wet Baking Soda** | Soda > Water |
| ④ | **Unnameable Object** | Doesn't satisfy any other recipe |
| ⑤ | **Batter** | Water + Flour, doesn't match Bread or Cake |
| ⑥ | **Bread** | Water ≤ Soda, Flour > 0, Water ≤ 20% total, Flour > Soda, Sugar ≤ all others |
| ⑦ | **Cake** | Same as Bread, but Sugar > all other ingredients |

### Flavor Profiles

| # | Flavor | Condition |
|:-:|:-------|:----------|
| ① | Slightly Sweet | Sugar largest, < 50% total |
| ② | Very Sweet | Sugar largest, ≥ 50% total |
| ③ | Slightly Salty | Salt largest, < 50% total |
| ④ | Very Salty | Salt largest, ≥ 50% total |
| ⑤ | Slightly Moist | Water largest, < 50% total |
| ⑥ | Very Moist | Water largest, ≥ 50% total |
| ⑦ | Slightly Soft | Flour ≤ Water, Flour > others, < 50% total |
| ⑧ | Very Soft | Flour ≤ Water, Flour > others, ≥ 50% total |
| ⑨ | Gassy | Soda > all others |
| ⑩ | Bland | None of the above |
| ⑪ | Very Dry | Flour > 0, Water = 0 |

---

## License

MIT License. See [LICENSE](LICENSE).
