#include "EventConfig.h"
#include "Events.h"     // r1 .. r5
#include "GameState.h"  // money, invest, Bband
#include "i18n.h"
#include <cstdlib>      // rand

std::vector<EventDef> EventConfig::s_events;

// ═══════════════════════════════════════════
//  EventCondition::evaluate
// ═══════════════════════════════════════════

bool EventCondition::evaluate() const {
    if (require_money_gt_0    && money <= 0)  return false;
    if (require_no_investment && invest)      return false;
    if (require_not_Bband     && Bband)       return false;
    if (once_only && once_flag && *once_flag) return false;
    if (custom_check && !custom_check())      return false;
    return true;
}

// ═══════════════════════════════════════════
//  EventConfig
// ═══════════════════════════════════════════

void EventConfig::init() {
    s_events.clear();

    // ── Event 1: money_gift ──
    // Unconditional; calls existing r1().
    s_events.push_back({"money_gift", 10, {}, r1});

    // ── Event 2: investment ──
    // Requires money > 0 and no active investment.
    {
        EventCondition c2;
        c2.require_money_gt_0    = true;
        c2.require_no_investment = true;
        s_events.push_back({"investment", 10, c2, r2});
    }

    // ── Event 3: product_promotion ──
    // Unconditional.
    s_events.push_back({"product_promotion", 10, {}, r3});

    // ── Event 4: rock_band ──
    // Requires !Bband; once_only (flag = &Bband, set to true inside r4).
    {
        EventCondition c4;
        c4.require_not_Bband = true;
        c4.once_only         = true;
        c4.once_flag         = &Bband;
        s_events.push_back({"rock_band", 10, c4, r4});
    }

    // ── Event 5: ingredient_gift ──
    // Unconditional.
    s_events.push_back({"ingredient_gift", 10, {}, r5});
}

int EventConfig::select_random_event() {
    // Gather eligible events and total weight
    int total_weight = 0;
    std::vector<int> eligible;
    for (size_t i = 0; i < s_events.size(); ++i) {
        if (s_events[i].condition.evaluate()) {
            eligible.push_back(static_cast<int>(i));
            total_weight += s_events[i].weight;
        }
    }
    if (eligible.empty()) return -1;

    // Weighted random selection
    int roll = rand() % total_weight;
    int cumulative = 0;
    for (int idx : eligible) {
        cumulative += s_events[idx].weight;
        if (roll < cumulative) return idx;
    }
    return eligible.back();  // safety fallback
}

const EventDef& EventConfig::get(int idx) {
    return s_events[static_cast<size_t>(idx)];
}

void EventConfig::register_event(const EventDef& ev) {
    s_events.push_back(ev);
}

size_t EventConfig::count() {
    return s_events.size();
}
