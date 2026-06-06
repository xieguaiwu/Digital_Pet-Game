#ifndef DIGITALPET_EVENTS_H
#define DIGITALPET_EVENTS_H

// ── Random event entry point ──
void r_e();

// ── Individual events ──
void r1();   // money gift
void r2();   // investment
void r3();   // product promotion
void r4();   // rock band
void r5();   // ingredient gift

// ── Event #4 helpers ──
void Binteract();
void band_days();
void Bback();

// ── TV ASCII-art functions (declared in event_print.h, used here) ──
void Btv1();
void Btv2();
void Btv3();
void Btv4();

#endif // DIGITALPET_EVENTS_H
