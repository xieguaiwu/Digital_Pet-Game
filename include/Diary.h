#ifndef DIGITALPET_DIARY_H
#define DIGITALPET_DIARY_H

#include <string>
#include <vector>

extern std::vector<std::string> diary;

void diary_new_day(unsigned int day);
void diary_add(const std::string& entry);
void diary_view();

#endif
