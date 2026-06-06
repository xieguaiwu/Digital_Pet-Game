#ifndef DIGITALPET_EVENTCONFIG_H
#define DIGITALPET_EVENTCONFIG_H

#include <cstddef>   // size_t
#include <vector>

// ── Trigger condition (bit-field flags + once_only + custom check) ──
struct EventCondition {
    bool require_money_gt_0    = false;   // money > 0
    bool require_no_investment = false;   // !invest
    bool require_not_Bband     = false;   // !Bband
    bool once_only             = false;   // fire at most once

    // Pointer to the flag that once_only mutates (e.g. &Bband).
    // When once_only is true, this flag is checked before firing
    // and set to true by the event handler.
    bool* once_flag = nullptr;

    // Optional custom condition callback (return true = eligible)
    bool (*custom_check)() = nullptr;

    // Evaluate all conditions; returns true if the event may fire.
    bool evaluate() const;
};

// ── Event handler signature ──
typedef void (*EventHandler)();

// ── Event definition ──
struct EventDef {
    const char*    name;         // debug / display name
    int            weight;       // relative weight (higher = more frequent)
    EventCondition condition;    // trigger conditions
    EventHandler   execute;      // handler callback
};

// ── Event configuration manager ──
class EventConfig {
public:
    // Register the 5 built-in events.
    static void init();

    // Weighted random selection among all eligible events.
    // Returns index into s_events, or -1 when nothing is eligible.
    static int select_random_event();

    // Access a registered event by index.
    static const EventDef& get(int idx);

    // Dynamically register a new event (extension point).
    static void register_event(const EventDef& ev);

    // Number of registered events.
    static size_t count();

private:
    static std::vector<EventDef> s_events;
};

#endif // DIGITALPET_EVENTCONFIG_H
