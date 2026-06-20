/*
이 파일에는 사용자의 입출력을 담당하는 함수들을 저장한다.
*/
#ifndef CONSOLE_UTIL_H
#define CONSOLE_UTIL_H

#include <string>

namespace ConsoleUtil {

void clear_screen();
bool get_player_confirm(std::string question_message);
void press_enter();

// 구분선을 반환하는 함수
std::string get_divider();

}

#endif
