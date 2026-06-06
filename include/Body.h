#ifndef DIGITALPET_BODY_H
#define DIGITALPET_BODY_H

#include "Types.h"

extern bool have_parts[all_parts];
extern bool parts_changed;

void have_body_ini();
void certain_body_give(bool CertainGiveWhich, int CertainStart, int CertainEnd);
void have_body();
void body_describe();

class TypesGive {
public:
    static void face_type_give(bool FaceGiveWhich);
    static void arm_type_give(bool ArmGiveWhich);
    static void leg_type_give(bool LegGiveWhich);
};

#endif // DIGITALPET_BODY_H
