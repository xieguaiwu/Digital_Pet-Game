# DigitalPet 改造架构设计

> 设计日期：2026-06-07  
> 目标：4 个独立架构方案，最小化文件冲突，支持并行实施

---

## 目录

1. [Bug 清单（逐条分析）](#1-bug-清单逐条分析)
2. [Plan A：Bug 修复 + 代码精进](#plan-abug-修复--代码精进)
3. [Plan B：新菜谱 + 新原料](#plan-b新菜谱--新原料)
4. [Plan C：多语言系统 (i18n)](#plan-c多语言系统-i18n)
5. [Plan D：配置式随机事件](#plan-d配置式随机事件)
6. [文件冲突矩阵 & 并行策略](#6-文件冲突矩阵--并行策略)
7. [实施顺序建议](#7-实施顺序建议)

---

## 1. Bug 清单（逐条分析）

### Bug #1 — Cdrop() 自赋值
**文件**: `src/Cooking.cpp:178`
```cpp
backpackall[i]   = backpackall[i];   // BUG: 应为 backpackall[i+1]
```
**缺失**：`backpackspend` 和 `backpackeffect` 完全没有参与 shift 循环，导致删除 dish 后这两个向量出现空洞。

### Bug #2 — 盐价格显示与实际不一致
**文件**: `src/Money.cpp:78`
- 显示：`"Salt $ 6~12 per gram"`
- 实际：`r_events(123, 21-6, 6)` → `6 + rand() % 15` → 范围 **6~20**

### Bug #3 — badint() EOF 处理
**文件**: `src/Utils.cpp:28-33`
- `cin.fail()` 检测后 `cin.ignore(..., '\n')`，但未检测 `cin.eof()`。
- 若用户按 Ctrl+D，每次调用 badint() 都会重复触发 fail，产生无限循环风险。

### Bug #4 — Ecook 类型错误（float → int）
**文件**: `include/GameState.h`, `src/Cooking.cpp`
- `Ecook` 声明为 `float`，`backpackeffect` 为 `std::vector<float>`。
- 但所有 EFFECT_* 常量都是整数（10, 20, 110, …），`meal_effect()` 中对每个 EFFECT_* 做 `static_cast<float>()`，最后又 `static_cast<int>(Ecook)` 返回。
- 应全程使用 `int`，消除 20+ 处无意义 cast。

### Bug #5 — Cclean() 用循环替代 clear()
**文件**: `src/Cooking.cpp:160-163`
```cpp
void Cclean() {
    for (unsigned int i = 1; i < Cid; ++i)
        backpackmeal[i - 1] = "";   // 仅清空字符串，其他向量未动
    Cid = 0;
}
```
- 循环只处理 `backpackmeal`，`calr/spend/all/effect` 向量完全未清理。
- 应使用 `.clear()` 清空全部 5 个向量。

### Bug #6 — ANSI 颜色支持缺失（Linux）
**文件**: `src/Utils.cpp colorc()`
- 整个函数体被 `#ifdef _WIN32` 包裹，Linux 下是空函数。
- 需为 Linux 添加 ANSI escape 序列（`\033[31m` 等）。

### Bug #7 — bool Pab → Personality 枚举
**文件**: `include/GameState.h`
- `Pab` 声明为 `bool`，但与 `dog`/`cat`（`Personality` 枚举值）比较。
- 应改为 `Personality Pab;`。

### Bug #8 — bool gender → GenderType 枚举
**文件**: `include/GameState.h`
- `gender` 声明为 `bool`，但与 `M`/`F`（`GenderType` 枚举值）比较。
- 应改为 `GenderType gender;`。

### Bug #9 — r_events() 职责过载
**文件**: `src/Utils.cpp`
- 一个函数通过 `sss` 参数实现 4 种不同语义：
  - `sss=0`：事件类型随机
  - `sss=1`：性格随机
  - `sss=2`：性别随机
  - `sss≥3`：通用范围随机
- 应拆分为 4 个命名函数。

### Bug #10 — S 键消耗 turn
**文件**: `src/Game.cpp handle_clear_screen()`
- 清屏不应消耗行动次数，但当前 `turns--`。
- 移除该语句。

### Bug #11 — handle_putting() 退出时原料丢失
**文件**: `src/Cooking.cpp:217-234`
- `storage[rounder] -= inter_trans` 在前，`break` 在后。
- 若用户在第 2 种原料输入 0 退出，第 1 种原料已从 storage 扣除但未使用。
- 应先在 `storageAdding` 累积，全部确认后再统一扣除。

---

## 2. Plan A：Bug 修复 + 代码精进

### 2.1 总览

| 属性 | 值 |
|:-----|:---|
| 新增文件 | **0** |
| 修改文件 | 10（见下表） |
| 新建类型 | 无 |
| 风险 | 低（机械性修改为主） |

### 2.2 修改文件清单

| 文件 | 修改内容 | 冲突等级 |
|:-----|:---------|:--------|
| `include/Types.h` | 新增 `SALT_PRICE_MIN/MAX/RANGE` constexpr | 低（追加尾部） |
| `include/GameState.h` | `bool Pab` → `Personality Pab`；`bool gender` → `GenderType gender`；`float Ecook` → `int Ecook`；`vector<float> backpackeffect` → `vector<int> backpackeffect` | **中**（类型变更影响引用处） |
| `include/Utils.h` | 拆 `r_events()` → `rand_event_type()` / `rand_personality()` / `rand_gender()` / `rand_range(int min, int max)`；新增 `colorc_ansi(int x)`；`badint()` 改为 `badint_clear()` 加强 EOF 处理 | **中**（多处调用点需更新） |
| `include/Cooking.h` | `Cpushback(..., float)` → `Cpushback(..., int)`；`Ecook` 类型变更签名跟随 | 低 |
| `src/GameState.cpp` | 类型变更同步 | 低 |
| `src/Utils.cpp` | 实现 ANSI 颜色；实现拆分后的随机函数；修复 badint EOF；更新 `r_events()` 调用点 | **中** |
| `src/Cooking.cpp` | 修复 Cdrop 3 向量 shift；Cclean → `.clear()`；meal_effect 去 float cast；handle_putting 原料退回 | **高**（改动物理逻辑） |
| `src/Game.cpp` | S 键移除 `turns--` | 低 |
| `src/Money.cpp` | 盐价格显示 6~12 → 6~20 | 低 |
| `src/Events.cpp` | `r_events()` 调用点更新为新函数名 | 低 |

### 2.3 关键函数签名变更

```cpp
// ── Utils.h 新增 ──
int  rand_event_type();                     // 原 r_events() sss=0
int  rand_personality();                    // 原 r_events() sss=1
int  rand_gender();                         // 原 r_events() sss=2
int  rand_range(int min, int max);          // 原 r_events(_, range, min)
void colorc_ansi(int x);                    // ANSI 颜色输出
void badint_clear();                        // 增强 badint（处理 EOF）

// ── Utils.h 保留（兼容期） ──
int  r_events(int sss = 0, int Mranding = 0, int Lranding = 0);  // 标记 [[deprecated]]

// ── Cooking.h 变更 ──
void Cpushback(const std::string& bloodyname, int bloodycalr,
               int bloodyspend, int bloodyall, int bloodyeffect);
//                                               ^^^ was float

// ── GameState.h 变更 ──
extern Personality  Pab;           // was bool
extern GenderType   gender;        // was bool
extern int          Ecook;         // was float
extern std::vector<int> backpackeffect;  // was vector<float>
```

### 2.4 数据流

```
rand_event_type() ──→ 返回 1~6 ──→ r_e() dispatcher
rand_personality() ──→ 返回 0~1 ──→ per() 初始化
rand_gender()      ──→ 返回 0~1 ──→ (预留)
rand_range(a,b)    ──→ 返回 [a, a+b) ──→ 各处随机数量生成

colorc_ansi(red) ──→ 输出 "\033[31m" ──→ 终端渲染红色
```

---

## 3. Plan B：新菜谱 + 新原料

### 3.1 总览

| 属性 | 值 |
|:-----|:---|
| 新增文件 | 2（`include/RecipeDB.h` + `src/RecipeDB.cpp`） |
| 修改文件 | 6（Types.h, GameState.h/.cpp, Cooking.h/.cpp, Money.cpp） |
| 新建类型 | `RecipeDef` 结构体, `RecipeDB` 类 |
| 风险 | 中（扩展数据结构，需保持向后兼容） |

### 3.2 新原料（3 种）

| 索引 | 名称 | 英文 | 价格 | 说明 |
|:-----|:-----|:-----|:-----|:-----|
| 5 | 牛奶 | milk | $12/100ml | 乳制品，含脂肪 |
| 6 | 鸡蛋 | eggs | $15/个 | 蛋白质来源 |
| 7 | 巧克力 | chocolate | $20/100g | 甜味剂，高热量 |

### 3.3 新菜品（5 种）

| MealType 值 | 名称 | 英文 | 所需关键原料 | 推荐搭配 | 热量 | 效果 |
|:------------|:-----|:-----|:-----------|:--------|:-----|:-----|
| 7 | 披萨 | pizza | 面粉+鸡蛋+巧克力 | 糖+盐+苏打 | 1200 | EFFECT_LIFE_UP2 |
| 8 | 曲奇 | cookie | 面粉+巧克力+糖 | 鸡蛋+盐 | 800 | EFFECT_HAP_UP15 |
| 9 | 松饼 | pancake | 面粉+鸡蛋+牛奶 | 糖 | 600 | EFFECT_MAXHAP_UP5 |
| 10 | 煎蛋卷 | omelette | 鸡蛋+牛奶 | 盐+面粉 | 500 | EFFECT_SAD_DOWN8 |
| 11 | 布丁 | pudding | 牛奶+鸡蛋+巧克力+糖 | 面粉 | 900 | EFFECT_HAP_UP20 |

### 3.4 新增类型

```cpp
// ── include/RecipeDB.h ──

// 原料需求描述
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

// 菜谱条目
struct RecipeDef {
    const char*   name;          // 显示名称
    MealType      dish;          // MealType 枚举值
    Taste         taste;         // 味道类型
    IngredientReq req;           // 所需原料量（0 表示不要求）
    int           effect;        // EFFECT_* 常量
    int           base_calories; // 基础热量
};

// 菜谱数据库
class RecipeDB {
public:
    static void init();                          // 注册所有菜谱
    static int  match(const IngredientReq& amt); // 匹配菜谱，返回索引或 -1
    static const RecipeDef& get(int idx);        // 获取菜谱
    static const std::vector<RecipeDef>& all();  // 全部菜谱
    static size_t count();                       // 菜谱数量
private:
    static std::vector<RecipeDef> s_recipes;
};
```

### 3.5 Types.h 变更

```cpp
// ── MealType 枚举扩展（追加在 cake=6 之后）──
enum MealType {
    air, soda, indefine, flor, bread, bananas, cake,
    pizza, cookie, pancake, omelette, pudding  // 新增 5 种
};

// ── 新增 EFFECT 常量 ──
constexpr int EFFECT_LIFE_UP3      =  30;   // 新：寿命 +3
constexpr int EFFECT_HAP_UP20      = 120;   // 新：快乐 +20
constexpr int EFFECT_SAD_DOWN10    = -310;  // 新：悲伤 -10
constexpr int EFFECT_MAXSAD_DOWN15 = -415;  // 新：最大悲伤 -15

// ── 原料索引常量（替代魔法数字）──
constexpr int ING_SUGAR     = 0;
constexpr int ING_SALT      = 1;
constexpr int ING_SODA      = 2;
constexpr int ING_WATER     = 3;
constexpr int ING_FLOUR     = 4;
constexpr int ING_MILK      = 5;
constexpr int ING_EGGS      = 6;
constexpr int ING_CHOCOLATE = 7;
constexpr int ING_COUNT     = 8;
```

### 3.6 GameState.h/.cpp 变更

```cpp
// ── 原料存储从 5 扩展到 8 ──
extern unsigned int storage[ING_COUNT];         // was storage[5]
extern unsigned int storageAdding[ING_COUNT];   // was storageAdding[5]

// ── 新原料价格 ──
extern const unsigned int price_milk;
extern const unsigned int price_eggs;
extern const unsigned int price_chocolate;
```

### 3.7 Cooking.h/.cpp 变更

```cpp
// ── 新函数（保留旧函数作为兼容）──
int  cook_v2(const IngredientReq& amt, bool CookOrCal);
void handle_putting_v2();                       // 8 种原料版
void Cincook_v2();                              // 8 种原料版

// ── Mname() 扩展 ──
// meal[7]="pizza"; meal[8]="cookie"; meal[9]="pancake";
// meal[10]="omelette"; meal[11]="pudding";

// ── Ename() 扩展 ──
// 注册 EFFECT_LIFE_UP3 / EFFECT_HAP_UP20 等新效果名
```

### 3.8 Money.cpp 变更

```cpp
// M_cok() 菜单新增：
//   G) Milk $12 per 100ml
//   H) Eggs $15 per piece
//   I) Chocolate $20 per 100g
//   J) Quit this menu  (原来的 G 顺延)

// check_cooking_ingredient() 显示 8 种原料
```

### 3.9 数据流

```
handle_putting_v2()
  ├── 用户输入 8 种原料量 → IngredientReq amt
  ├── storage[0..7] -= amt.*    (统一扣减)
  ├── RecipeDB::match(amt)
  │     ├── 精确匹配 → RecipeDef 索引
  │     └── 无匹配 → -1 → 回退到启发式 meal_nam()/meal_tas()
  ├── meal_effect() 计算效果
  └── Cpushback(名称, 热量, 成本, 总量, 效果)
```

### 3.10 菜谱匹配算法

```cpp
int RecipeDB::match(const IngredientReq& amt) {
    // 1. 所有原料为 0 → air
    if (all_zero(amt)) return AIR_INDEX;
    
    // 2. 精确匹配（每种原料恰好 >= req 且无多余） 
    for (size_t i = 0; i < s_recipes.size(); ++i) {
        if (exact_match(amt, s_recipes[i].req))
            return static_cast<int>(i);
    }
    
    // 3. 宽松匹配（关键原料满足即可）
    for (size_t i = 0; i < s_recipes.size(); ++i) {
        if (key_ingredients_match(amt, s_recipes[i].req))
            return static_cast<int>(i);
    }
    
    // 4. 回退：启发式（旧 meal_nam 逻辑）
    return -1;  // 调用方回退
}
```

---

## 4. Plan C：多语言系统 (i18n)

### 4.1 总览

| 属性 | 值 |
|:-----|:---|
| 新增文件 | 2（`include/i18n.h` + `src/i18n.cpp`） |
| 修改文件 | 6（GameState, Game, Cooking, Events, Money, Utils） |
| 新建类型 | `enum class StrId`, `tr()` / `tr_f()` 函数 |
| 风险 | 中（字符串替换面广，但为机械性替换） |

### 4.2 架构设计

```
┌──────────────────────────────────────────┐
│              调用方                       │
│  cout << tr(StrId::ACT_FEED) << name;    │
│  cout << tr_f(StrId::DAY, day_num);      │
└──────────────┬───────────────────────────┘
               │
               ▼
┌──────────────────────────────────────────┐
│            i18n.h / i18n.cpp              │
│                                           │
│  Language g_lang = cn;  // 运行时切换     │
│                                           │
│  const char* tr(StrId id) {               │
│    return g_lang==cn ? table_cn[id]       │
│                      : table_en[id];      │
│  }                                        │
│                                           │
│  std::string tr_f(StrId id, ...) {        │
│    // vsnprintf 格式化                    │
│    const char* fmt = tr(id);              │
│    char buf[512];                         │
│    vsnprintf(buf, 512, fmt, args);        │
│    return buf;                            │
│  }                                        │
└──────────────────────────────────────────┘
```

### 4.3 新增类型

```cpp
// ── include/i18n.h ──

#ifndef DIGITALPET_I18N_H
#define DIGITALPET_I18N_H

#include "Types.h"
#include <string>

// ── 字符串资源 ID 枚举 ──
enum class StrId : unsigned short {
    // 启动
    NAME_PROMPT,
    NAME_CONFIRM,
    NAME_GOOD,
    NAME_CRAZY,
    NAME_MURDEROUS,

    // 宠物描述
    PET_IS_DOG,
    PET_IS_CAT,
    PET_MET_DOG,
    PET_MET_CAT,
    PET_NAMED,
    PET_YEARS_OLD,
    PET_LIFESPAN_REMAIN,
    PET_LIFESPAN_NEED_HAP,
    PET_IS_HUNGRY,
    PET_WANTS_DEFECATE,
    PET_COMMITTED_SUICIDE,
    PET_LAST_DAY,

    // 天
    DAY_LABEL,
    DAY_LAST_WARNING,

    // 状态
    STAT_LIFESPAN,
    STAT_EMOTION,
    STAT_HAPPINESS,
    STAT_SADNESS,
    STAT_PHYSIOLOGY,
    STAT_DEFECATE_YES,
    STAT_DEFECATE_NO,
    STAT_EAT_YES,
    STAT_EAT_NO,

    // 操作菜单
    NOTICE_ACTIONS,
    NOTICE_TURNS_REMAIN,
    ACT_FEED,
    ACT_INTERACT,
    ACT_CHECK_STATUS,
    ACT_CLEAR_SCREEN,
    ACT_BUY_COOK,
    ACT_CHECK_INGREDIENTS,
    ACT_CHECK_DISHES,
    ACT_QUIT,
    ACT_COLOR_CHANGE,

    // 互动
    INT_MENU,
    INT_DEFECATE,
    INT_PAT,
    INT_QUIT_MENU,
    INT_PAT_MSG,

    // 购买
    BUY_MENU,
    BUY_ITEMS,
    BUY_INGREDIENTS,
    BUY_LOAN,
    BUY_COOKING,
    BUY_QUIT,

    // 烹饪
    COOK_NO_DISHES,
    COOK_INPUT_NUMBER,
    COOK_HOW_MUCH,
    COOK_GRAMS,
    COOK_MILLILITER,
    COOK_NOT_ENOUGH,
    COOK_KEEP_COOKING,
    COOK_INGREDIENT_SUGAR,
    COOK_INGREDIENT_SALT,
    COOK_INGREDIENT_SODA,
    COOK_INGREDIENT_WATER,
    COOK_INGREDIENT_FLOUR,
    COOK_INGREDIENT_MILK,
    COOK_INGREDIENT_EGGS,
    COOK_INGREDIENT_CHOCOLATE,
    COOK_ENERGY,
    COOK_NOTICE_1,
    COOK_NOTICE_2,
    COOK_NOTICE_3,
    COOK_EMPTY_POT,

    // 背包
    BP_ITEM_NUMBER,
    BP_SELL_FEED_DUMP,
    BP_DROPPED,
    BP_ITEM_FORMAT,

    // 商店 - 原料
    SHOP_ING_LIST,
    SHOP_AIR,
    SHOP_INPUT_GRAMS,
    SHOP_BOUGHT_N,
    SHOP_PRICE_LABEL,

    // 商店 - 道具
    SHOP_PROPS_LIST,
    SHOP_BUTTERCUP,
    SHOP_MADNESS,
    SHOP_ARSENIC,
    SHOP_DIAMOND,
    SHOP_BOUGHT_SUCCESS,

    // 贷款
    LOAN_PROMPT,
    LOAN_TOO_MUCH,
    LOAN_ZERO_MONEY,
    LOAN_CONTRACT,
    LOAN_GIVE_UP,
    LOAN_PAID,
    LOAN_NOT_ENOUGH,
    LOAN_REFUSE,

    // 事件 r1
    EVT1_MONEY_FOUND,

    // 事件 r2
    EVT2_INVESTMENT_PAPER,
    EVT2_SIGN,
    EVT2_INPUT_AMOUNT,
    EVT2_INVESTED,
    EVT2_ALL_MONEY,
    EVT2_LOOK_RETARD,
    EVT2_SUCCESS,
    EVT2_FAILED,

    // 事件 r3
    EVT3_RAN_OUT,
    EVT3_KNOCKING,
    EVT3_OPEN_DOOR,
    EVT3_ATE_DOOR,
    EVT3_FOUND_ITEMS,
    EVT3_BUY_10,
    EVT3_TOY_MOUSE,
    EVT3_SLIPPER,
    EVT3_HEART_SAVER,
    EVT3_LONELINESS,
    EVT3_MONSTER,
    EVT3_SCAMMED,

    // 事件 r4
    EVT4_ROCK_MUSIC,
    EVT4_BAND_START,
    EVT4_LAST_FEED,
    EVT4_LEAVE,
    EVT4_OPEN_TV,
    EVT4_CHANNELS,
    EVT4_FOUND_PET,
    EVT4_PERFORMANCE,
    EVT4_EARNED,
    EVT4_BACK_LIFE,

    // 事件 r5
    EVT5_BROUGHT_BACK,

    // 通用
    GEN_CHOOSE_AGAIN,
    GEN_ARE_YOU_SURE,
    GEN_YES_NO,
    GEN_PRESS_ANY_KEY,
    GEN_QUIT_GAME,
    GEN_MONEY_NOT_ENOUGH,
    GEN_MONEY_HAVE,
    GEN_CONTINUE_BUY,

    // 通知
    NOTIF_HAP_PLUS,
    NOTIF_HAP_MINUS,
    NOTIF_SAD_PLUS,
    NOTIF_SAD_MINUS,
    NOTIF_MONEY_PLUS,
    NOTIF_MONEY_MINUS,
    NOTIF_LIFESPAN_PLUS,
    NOTIF_LIFESPAN_MINUS,
    NOTIF_LIFESPAN_NEED_INC,
    NOTIF_LIFESPAN_NEED_DEC,

    // 作弊
    CHEAT_PROMPT,

    // 总数
    STR_COUNT
};

// ── 全局语言设置 ──
extern Language g_language;

// ── 初始化 ──
void i18n_init();

// ── 翻译函数 ──
const char* tr(StrId id);                       // 简单查找
std::string tr_f(StrId id, ...);                // 格式化字符串（printf 风格）

// ── 便捷函数 ──
void set_language(Language lang);

#endif
```

### 4.4 i18n.cpp 实现要点

```cpp
#include "i18n.h"
#include <map>
#include <cstdarg>
#include <cstdio>

Language g_language = cn;  // 默认中文

// ── 英文字符串表 ──
static const std::map<StrId, const char*> table_en = {
    {StrId::NAME_PROMPT,        "Input the name of your digital pet:"},
    {StrId::ACT_FEED,           "You feed your pet."},
    {StrId::DAY_LABEL,          "DAY %d ."},
    {StrId::NOTICE_TURNS_REMAIN,"You have %d times left"},
    // ... 全部 ~150 条
};

// ── 中文字符串表 ──
static const std::map<StrId, const char*> table_cn = {
    {StrId::NAME_PROMPT,        "请输入你的电子宠物的名字："},
    {StrId::ACT_FEED,           "你喂了你的宠物。"},
    {StrId::DAY_LABEL,          "第 %d 天。"},
    {StrId::NOTICE_TURNS_REMAIN,"你还剩 %d 次操作机会"},
    // ... 全部 ~150 条
};

const char* tr(StrId id) {
    const auto& table = (g_language == cn) ? table_cn : table_en;
    auto it = table.find(id);
    if (it != table.end()) return it->second;
    return "???";  // 缺失翻译的占位符
}

std::string tr_f(StrId id, ...) {
    const char* fmt = tr(id);
    char buf[1024];
    va_list args;
    va_start(args, id);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    return std::string(buf);
}
```

### 4.5 集成方式

**旧代码**：
```cpp
cout << "You feed your pet.\n";
cout << "DAY " << days << " .\n";
```

**新代码**：
```cpp
cout << tr(StrId::ACT_FEED) << "\n";
cout << tr_f(StrId::DAY_LABEL, days) << "\n";
```

### 4.6 语言切换

在 `main()` 中解析命令行参数：
```cpp
int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--en")
        g_language = en;
    i18n_init();
    // ...
}
```

---

## 5. Plan D：配置式随机事件

### 5.1 总览

| 属性 | 值 |
|:-----|:---|
| 新增文件 | 2（`include/EventConfig.h` + `src/EventConfig.cpp`） |
| 修改文件 | 3（Events.h/.cpp, Game.cpp, Utils.h/.cpp） |
| 新建类型 | `EventCondition`, `EventDef`, `EventConfig` 类 |
| 风险 | 中（重构事件调度逻辑） |

### 5.2 架构设计

```
┌──────────────────────────────────────────────┐
│           EventConfig::init()                 │
│  注册 5+ 事件定义（EventDef 数组）             │
│  - 名称、权重、触发条件、执行回调               │
└──────────────────┬───────────────────────────┘
                   │
                   ▼
┌──────────────────────────────────────────────┐
│         EventConfig::select_random()          │
│  1. 遍历事件，检查触发条件                      │
│  2. 计算合格事件权重总和                        │
│  3. 加权随机选择一个                           │
│  4. 返回索引（-1 = 无事件触发）                  │
└──────────────────┬───────────────────────────┘
                   │ idx >= 0
                   ▼
┌──────────────────────────────────────────────┐
│     s_events[idx].execute()                   │
│  调用事件处理函数（r1~r5 或其 lambda 替代）       │
└──────────────────────────────────────────────┘
```

### 5.3 新增类型

```cpp
// ── include/EventConfig.h ──

#ifndef DIGITALPET_EVENTCONFIG_H
#define DIGITALPET_EVENTCONFIG_H

#include <string>
#include <vector>

// ── 触发条件（位域 + 回调）──
struct EventCondition {
    // 位域标志
    bool require_money_gt_0    : 1 = false;  // money > 0
    bool require_no_investment : 1 = false;  // !invest
    bool require_not_Bband     : 1 = false;  // !Bband
    bool once_only             : 1 = false;  // 仅触发一次

    // once_only 对应的标志变量指针
    bool* once_flag = nullptr;

    // 自定义条件函数（可选，处理复杂条件）
    bool (*custom_check)() = nullptr;

    // 评估所有条件
    bool evaluate() const;
};

// ── 事件处理函数类型 ──
// 返回 true = 事件实际触发了；false = 被玩家取消或其他原因未生效
typedef bool (*EventHandler)();

// ── 事件定义 ──
struct EventDef {
    const char*    name;          // 事件名（调试用）
    int            weight;        // 相对权重（越大越频繁）
    EventCondition condition;     // 触发条件
    EventHandler   execute;       // 执行回调
};

// ── 事件配置管理器 ──
class EventConfig {
public:
    // 注册所有默认事件
    static void init();

    // 加权随机选择一个可触发的事件
    // 返回索引或 -1（无事件触发）
    static int select_random_event();

    // 获取事件定义
    static const EventDef& get(int idx);

    // 动态注册新事件（扩展接口）
    static void register_event(const EventDef& ev);

    // 获取总事件数
    static size_t count();

private:
    static std::vector<EventDef> s_events;
};

#endif
```

### 5.4 EventConfig.cpp 事件表

```cpp
#include "EventConfig.h"
#include "Events.h"    // r1~r5 函数声明
#include "GameState.h"
#include "Utils.h"
#include <cstdlib>

std::vector<EventDef> EventConfig::s_events;

void EventConfig::init() {
    s_events.clear();

    // ── Event 1: 金钱礼物 ──
    s_events.push_back({
        "money_gift", 10,  // weight
        {},                // 无条件
        []() -> bool {
            int amount = rand_range(0, 35);  // 原 r_events(3,35,0)
            if (amount != 0) {
                cout << tr_f(StrId::EVT1_MONEY_FOUND, amount);
                money += amount;
                pausers::pause();
                return true;
            }
            return false;
        }
    });

    // ── Event 2: 投资 ──
    s_events.push_back({
        "investment", 10,
        EventCondition{
            .require_money_gt_0    = true,
            .require_no_investment = true
        },
        r2  // 复用现有函数
    });

    // ── Event 3: 产品促销 ──
    s_events.push_back({
        "product_promotion", 10,
        {},  // 无条件
        r3
    });

    // ── Event 4: 摇滚乐队 ──
    s_events.push_back({
        "rock_band", 10,
        EventCondition{
            .require_not_Bband = true,
            .once_only         = true,
            .once_flag         = &Bband
        },
        r4
    });

    // ── Event 5: 原料礼物 ──
    s_events.push_back({
        "ingredient_gift", 10,
        {},  // 无条件
        r5
    });
}

int EventConfig::select_random_event() {
    // 计算合格事件的总权重
    int total_weight = 0;
    std::vector<int> eligible;  // 合格事件索引
    for (size_t i = 0; i < s_events.size(); ++i) {
        if (s_events[i].condition.evaluate()) {
            eligible.push_back(static_cast<int>(i));
            total_weight += s_events[i].weight;
        }
    }
    if (eligible.empty()) return -1;

    // 加权随机
    int roll = rand() % total_weight;
    int cumulative = 0;
    for (int idx : eligible) {
        cumulative += s_events[idx].weight;
        if (roll < cumulative) return idx;
    }
    return eligible.back();  // 保险
}
```

### 5.5 Events.h 变更

```cpp
// ── 新增 ──
void r_e_v2();  // 新版调度器（使用 EventConfig）

// ── 保留（作为回调函数）──
void r1(); void r2(); void r3(); void r4(); void r5();
// 以上函数可以改为内部静态，但保持公开以兼容作弊系统
```

### 5.6 Events.cpp 变更

```cpp
// 旧 r_e() 保留，新增 r_e_v2()：
void r_e_v2() {
    if (days < 1) return;
    int idx = EventConfig::select_random_event();
    if (idx < 0) return;
    EventConfig::get(idx).execute();
}

// r1~r5 函数保持不变（作为 EventHandler 回调）
```

### 5.7 Game.cpp 变更

```cpp
static void starter_notice() {
    // ... 现有代码 ...
    srand(static_cast<unsigned>(time(nullptr)));
    EventConfig::init();    // ← 新增：注册事件表
    // ...
}

// o_days() 末尾：
//   if (key != 'Q' && key != 'q') r_e_v2();  // 使用新版
//   (或保持 r_e()，逐步迁移)
```

### 5.8 Utils.h 变更

```cpp
// ── 新增（配合 EventConfig）──
bool evaluate_condition(const EventCondition& cond);
```

---

## 6. 文件冲突矩阵 & 并行策略

### 6.1 完整冲突矩阵

| 文件 | Plan A | Plan B | Plan C | Plan D | 冲突数 |
|:-----|:------:|:------:|:------:|:------:|:------:|
| **include/Types.h** | ✓ | ✓ | – | – | 2 |
| **include/GameState.h** | ✓ | ✓ | ✓ | – | **3** |
| **include/Utils.h** | ✓ | – | – | ✓ | 2 |
| **include/Cooking.h** | ✓ | ✓ | – | – | 2 |
| **include/Events.h** | – | – | – | ✓ | 1 |
| include/Body.h | – | – | – | – | 0 |
| include/Money.h | – | – | – | – | 0 |
| **include/RecipeDB.h** | – | **NEW** | – | – | 0 |
| **include/i18n.h** | – | – | **NEW** | – | 0 |
| **include/EventConfig.h** | – | – | – | **NEW** | 0 |
| **src/GameState.cpp** | ✓ | ✓ | ✓ | – | **3** |
| **src/Utils.cpp** | ✓ | – | ✓ | ✓ | **3** |
| **src/Cooking.cpp** | ✓ | ✓ | ✓ | – | **3** |
| **src/Events.cpp** | ✓ | – | ✓ | ✓ | **3** |
| **src/Game.cpp** | ✓ | – | ✓ | ✓ | **3** |
| **src/Money.cpp** | ✓ | ✓ | ✓ | – | **3** |
| src/Body.cpp | – | – | – | – | 0 |
| **src/RecipeDB.cpp** | – | **NEW** | – | – | 0 |
| **src/i18n.cpp** | – | – | **NEW** | – | 0 |
| **src/EventConfig.cpp** | – | – | – | **NEW** | 0 |

**0-conflict 文件（可完全并行）**：9 个（3 个 untouched + 6 个全新文件）

**需协调的共享文件**：10 个（其中 5 个被 3 个 Plan 同时触及）

### 6.2 冲突类型分析

| 文件 | 冲突类型 | 解决方案 |
|:-----|:---------|:---------|
| Types.h | A 加 constexpr，B 加枚举值 | 追加在不同区域（A 在文件尾，B 在枚举体中部）— 无冲突 |
| GameState.h | A 改类型，B 扩数组，C 加 g_language | A 改动最小（改类型签名），B 在 storage 数组区域，C 在文件尾加 extern — 可独立编辑 |
| GameState.cpp | 同上 | 同上 |
| Cooking.cpp | A 改逻辑，B 改函数，C 改字符串 | A 是 bugfix（函数内部），B 加新函数，C 是字符串替换 — 不同行无冲突 |
| Utils.cpp | A 改函数实现，C 改 notices 字符串，D 加 check_condition | A 在 r_events/colorc/badint 区域，C 在 notices 方法内，D 在文件尾加新函数 — 无冲突 |
| Events.cpp | A 改调用点，C 改字符串，D 改调度器 | D 加新函数 r_e_v2() 不删旧 r_e()，C 改字符串（不同行），A 改调用点 — 无冲突 |
| Game.cpp | A 删 turns--，C 换字符串，D 加 init 调用 | A 删 1 行，C 换字符串，D 在 starter_notice 加 1 行 — 无冲突 |
| Money.cpp | A 改显示文本，B 加菜单项，C 换字符串 | 三者都是文本修改（不同行）— 无冲突 |

**结论：所有冲突均为逻辑冲突（概念层面理解差异），无物理冲突（同文件同行的 git merge conflict）。4 个 Plan 实际上可完全并行实施！**

### 6.3 并行实施的分段边界

为确保无 merge conflict，每个 Plan 在共享文件中的修改定位如下：

```
// ═══════════════════════════════════════════
//  Plan A: Type fixes
// ═══════════════════════════════════════════
// (修改现有声明/定义行)

// ═══════════════════════════════════════════
//  Plan B: Extended recipes
// ═══════════════════════════════════════════
// (在现有代码块之后追加)

// ═══════════════════════════════════════════
//  Plan C: i18n strings
// ═══════════════════════════════════════════
// (替换现有字符串字面量，不改变逻辑结构)

// ═══════════════════════════════════════════
//  Plan D: Event config
// ═══════════════════════════════════════════
// (在事件函数附近追加新调度器，不动旧函数体)
```

---

## 7. 实施顺序建议

### 推荐路线（串并结合）

```
Phase 0: 分支准备
  ├── git branch plan-a  (从 main)
  ├── git branch plan-b  (从 main，等 plan-a 合并后 rebase)
  ├── git branch plan-c  (从 main，等 plan-a 合并后 rebase)
  └── git branch plan-d  (从 main，等 plan-a 合并后 rebase)

Phase 1: Plan A 独立实施 (~2h)
  ├── 所有 bug 修复
  ├── 类型清理
  ├── 编译验证 (make clean && make)
  └── 合并到 main

Phase 2: Plan B + Plan D 并行 (~3h)
  ├── Worker 1: Plan B (新菜谱)
  │   ├── 创建 RecipeDB.h/.cpp
  │   ├── 扩展 Types.h 枚举
  │   ├── 扩展 GameState storage
  │   └── 更新 Cooking/Money
  └── Worker 2: Plan D (事件配置化)
      ├── 创建 EventConfig.h/.cpp
      ├── 更新 Events.h/.cpp
      └── 更新 Game.cpp 启动

Phase 3: Plan C 收尾 (~3h)
  ├── 创建 i18n.h/.cpp
  ├── 批量替换所有源文件中的字符串 → tr()
  └── 包含 Phase 2 新增的 Plan B/D 字符串

Phase 4: 集成验证 (~1h)
  ├── 全量编译
  ├── 运行时测试
  └── 中英文切换测试
```

### 备选路线（全并行 + 一次合并）

如果团队有 4 人可同时工作：

1. 所有 4 个 Plan 从同一个 `main` 分支各自创建 feature 分支
2. 每个 Plan 按上述分段边界修改共享文件（确保无冲突）
3. 按 A → B → D → C 顺序合并（Plan C 最后因为它需要包裹其他 Plan 新增的字符串）
4. 每次合并后做一次编译验证

### 最小可行路线（一次只做一个）

```
Plan A (必须最先) → Plan B (独立性强) → Plan C (覆盖面广) → Plan D (独立性强)
```

---

## 附录 A：Makefile 兼容性

所有 4 个 Plan 均不需要修改 Makefile（当前 `SRCS := $(wildcard $(SRCDIR)/*.cpp)` 自动包含新增的 .cpp 文件；`INCLUDES := -I include` 自动包含新增的 .h 文件）。

---

## 附录 B：完整新文件列表

| 文件 | 所属 Plan | 行数估计 |
|:-----|:---------|:--------|
| `include/RecipeDB.h` | B | ~50 |
| `src/RecipeDB.cpp` | B | ~200 |
| `include/i18n.h` | C | ~150 |
| `src/i18n.cpp` | C | ~400 |
| `include/EventConfig.h` | D | ~70 |
| `src/EventConfig.cpp` | D | ~150 |
| **总计** | | **~1020 行** |

---

## 附录 C：风险与缓解

| 风险 | 影响 | 缓解 |
|:-----|:-----|:-----|
| Plan A 类型变更导致编译错误传播 | 中 | 全部 EFFECT_* 常量已在 Types.h 集中定义，修改 Ecook 类型影响范围可控（~5 文件） |
| Plan B storage 从 5→8 的边界条件 | 中 | `Cfour()` 等函数使用常量 `ING_COUNT` 而非魔法数字 5 |
| Plan C 字符串遗漏 | 低 | 未翻译的字符串保留英文原文，tr() 返回 "???" 作为可视化标记 |
| Plan D 事件权重调优 | 低 | 权重可在 EventConfig.cpp 中直接修改，无需重新编译其他文件 |
