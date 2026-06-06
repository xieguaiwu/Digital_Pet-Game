#ifndef DIGITALPET_TYPES_H
#define DIGITALPET_TYPES_H

// ── Language ──
enum Language { cn, en };

// ── Personality (pet species) ──
enum Personality { dog, cat };

// ── Gender ──
enum GenderType { M, F };

// ── Reference pronoun type ──
enum ReferType { nomin, object, posses };

// ── Key codes (Linux arrow keys) ──
enum KeyCode { up = 'H', down = 'P' };

// ── Console colours ──
enum Color { red, green, blue, white = 6 };

// ── Theme ──
enum ThemeType { Tdef, Tadv, Tele, Tnor };

// ── Cooking mode ──
enum CookType { ck, cr };

// ── Dish names ──
enum MealType { air, soda, indefine, flor, bread, bananas, cake, pizza, cookie, pancake, omelette, pudding };

// ── Taste profiles ──
enum Taste {
    sweet,     // 0  slightly sweet
    sult,      // 1  slightly salty
    mois,      // 2  slightly moist
    too_sod,   // 3  gassy
    flat,      // 4  bland
    floy,      // 5  slightly soft
    Vsweet,    // 6  very sweet
    Vsult,     // 7  very salty
    Vmois,     // 8  very moist
    Vfloy,     // 9  very soft
    dry        // 10 very dry
};

// ── Computer opponent gender (RPS minigame) ──
enum { male, female };

// ── Rock-paper-scissors ──
enum { rock, paper, scis };

// ── Body part hierarchy ──
enum BodyType { head, neck, torso };                     // 0..2
const unsigned char body_pieces = 3;

enum FaceType {
    left_eye  = body_pieces,
    right_eye,
    nose,
    mouth,
    face                                             // 3..7
};
const unsigned char face_pieces = 5;

enum ArmType {
    left_arm               = body_pieces + face_pieces,
    right_arm,
    left_hand,
    left_hand_finger,
    left_hand_finger_nail,
    right_hand,
    right_hand_finger,
    right_hand_finger_nail                           // 8..15
};
const unsigned char arm_pieces = 8;

enum LegType {
    left_leg               = body_pieces + face_pieces + arm_pieces,
    left_foot,
    left_foot_toes,
    right_leg,
    right_foot,
    right_foot_toes                                 // 16..21
};
const unsigned char leg_pieces = 6;

const unsigned char all_parts = body_pieces + face_pieces + arm_pieces + leg_pieces;  // 22

// ── Dish effect constants (encoded as integers * 100 to avoid float keys) ──
// Format: [type][value] where type: 0=life, 1=hap, 2=max_hap, 3=sad, 4=max_sad, 5=none
constexpr int EFFECT_LIFE_UP1      =   1;   // lifespan +1
constexpr int EFFECT_LIFE_UP2      =   2;   // lifespan +2
constexpr int EFFECT_LIFE_DOWN1    =  -1;   // lifespan -1
constexpr int EFFECT_LIFE_DOWN2    =  -2;   // lifespan -2

constexpr int EFFECT_HAP_UP10      = 110;   // happiness +10
constexpr int EFFECT_HAP_UP15      = 115;   // happiness +15
constexpr int EFFECT_HAP_DOWN10    = -110;  // happiness -10
constexpr int EFFECT_HAP_DOWN15    = -115;  // happiness -15

constexpr int EFFECT_MAXHAP_UP5    = 205;   // max happiness +5
constexpr int EFFECT_MAXHAP_UP15   = 215;   // max happiness +15
constexpr int EFFECT_MAXHAP_DOWN5  = -205;  // max happiness -5
constexpr int EFFECT_MAXHAP_DOWN15 = -215;  // max happiness -15

constexpr int EFFECT_SAD_UP5       = 305;   // sadness +5
constexpr int EFFECT_SAD_UP8       = 308;   // sadness +8
constexpr int EFFECT_SAD_DOWN5     = -305;  // sadness -5
constexpr int EFFECT_SAD_DOWN8     = -308;  // sadness -8

constexpr int EFFECT_MAXSAD_UP5    = 405;   // max sadness +5
constexpr int EFFECT_MAXSAD_UP10   = 410;   // max sadness +10
constexpr int EFFECT_MAXSAD_DOWN5  = -405;  // max sadness -5
constexpr int EFFECT_MAXSAD_DOWN10 = -410;  // max sadness -10

constexpr int EFFECT_NONE          = 500;   // no effect

// ── Additional effect constants (Plan A) ──
constexpr int EFFECT_LIFE_UP3      =   3;   // lifespan +3
constexpr int EFFECT_HAP_UP20      = 120;   // happiness +20
constexpr int EFFECT_SAD_DOWN10    = -310;  // sadness -10
constexpr int EFFECT_MAXSAD_DOWN15 = -415;  // max sadness -15

// ── Ingredient indices (Plan A) ──
constexpr int ING_SUGAR    = 0;
constexpr int ING_SALT     = 1;
constexpr int ING_SODA     = 2;
constexpr int ING_WATER    = 3;
constexpr int ING_FLOUR    = 4;
constexpr int ING_MILK     = 5;
constexpr int ING_EGGS     = 6;
constexpr int ING_CHOCOLATE = 7;
constexpr int ING_COUNT    = 8;

// ── Salt price range (Plan A) ──
constexpr int SALT_PRICE_MIN   = 6;
constexpr int SALT_PRICE_MAX   = 20;
constexpr int SALT_PRICE_RANGE = SALT_PRICE_MAX - SALT_PRICE_MIN;

// ── Yes / No key macros ──
#define YES_KEY key == 'Y' || key == 'y'
#define NO_KEY  key == 'N' || key == 'n'

#endif // DIGITALPET_TYPES_H
