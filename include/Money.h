#ifndef DIGITALPET_MONEY_H
#define DIGITALPET_MONEY_H

// ── Money / shop / loan ──
void M_cok();   // buy cooking ingredients
void M_stu();   // buy props
void M_det();   // apply for loan
void M_();      // handle loan repayment ticks
void check_cooking_ingredient();

// ── Loan helpers ──
void handle_pay_back_in_arrears();
void handle_pay_back_out_arrears();

#endif // DIGITALPET_MONEY_H
