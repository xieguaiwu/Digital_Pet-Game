#include "Diary.h"
#include "GameState.h"
#include "Utils.h"
#include "i18n.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::cin;

std::vector<std::string> diary;

void diary_new_day(unsigned int day) {
    diary_add("--- Day " + std::to_string(day) + " ---");
}

void diary_add(const std::string& entry) {
    diary.push_back(entry);
}

void diary_view() {
    hyphen(4);
    cout << tr(StrId::DIARY_TITLE) << "\n";
    if (diary.empty()) {
        cout << tr(StrId::DIARY_EMPTY) << "\n";
    } else {
        for (const auto& entry : diary) {
            cout << entry << "\n";
        }
    }
    hyphen(4);
    pausers::pause();
}
