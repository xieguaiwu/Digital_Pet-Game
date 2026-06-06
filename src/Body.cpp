#include "Body.h"
#include "i18n.h"
#include <iostream>

bool have_parts[all_parts];
bool parts_changed;

void have_body_ini() {
    for (int i = 0; i < all_parts; ++i)
        have_parts[i] = true;
}

void certain_body_give(bool CertainGiveWhich, int CertainStart, int CertainEnd) {
    for (int i = CertainStart; i < CertainEnd; ++i)
        have_parts[i] = CertainGiveWhich;
}

void TypesGive::face_type_give(bool w) {
    certain_body_give(w, body_pieces, body_pieces + face_pieces);
}
void TypesGive::arm_type_give(bool w) {
    certain_body_give(w, body_pieces + face_pieces,
                      body_pieces + face_pieces + arm_pieces);
}
void TypesGive::leg_type_give(bool w) {
    certain_body_give(w, body_pieces + face_pieces + arm_pieces,
                      body_pieces + face_pieces + arm_pieces + leg_pieces);
}

void have_body() {
    if (!have_parts[head])             TypesGive::face_type_give(false);
    if (!have_parts[neck])             { have_parts[head] = false; TypesGive::face_type_give(false); }
    if (!have_parts[torso])            { TypesGive::arm_type_give(false); TypesGive::leg_type_give(false); }
    if (!have_parts[left_arm])         certain_body_give(false, left_hand, left_hand_finger_nail + 1);
    if (!have_parts[right_arm])        certain_body_give(false, right_hand, right_hand_finger_nail + 1);
    if (!have_parts[left_hand])        certain_body_give(false, left_hand_finger, left_hand_finger_nail + 1);
    if (!have_parts[right_hand])       certain_body_give(false, right_hand_finger, right_hand_finger_nail + 1);
    if (!have_parts[left_hand_finger])  have_parts[left_hand_finger_nail] = false;
    if (!have_parts[right_hand_finger]) have_parts[right_hand_finger_nail] = false;
    if (!have_parts[left_leg])         certain_body_give(false, left_foot, left_foot_toes + 1);
    if (!have_parts[right_leg])        certain_body_give(false, right_foot, right_foot_toes + 1);
    if (!have_parts[left_foot])        have_parts[left_foot_toes] = false;
    if (!have_parts[right_foot])       have_parts[right_foot_toes] = false;
}

void body_describe() {
    if (parts_changed) have_body();
    // (placeholder — description logic incomplete in original code)
}
