/*
 * [인터넷 쇼핑몰(스포츠 의류) 관리 프로그램 - main.cpp]
 *
 * C++ Term Project - CLI 쇼핑몰 메인 진입점
 *
 * 필수기능1: 회원/비회원 구분
 *   - Menu::start_menu()에서 Server::get_logged_in_account()로 구분
 *   - 회원: purchase(), refund(), 포인트 적립/사용 가능
 *   - 비회원: purchase()만 가능 (이력/포인트 없음)
 *
 * 필수기능2: 구매이력 기반 포인트/Advantage 기능
 *   - Server::purchase() -> Account::add_purchase_amount() -> Account::recalculate_points()
 *   - 5만원마다 1,000포인트 적립, 포인트 사용으로 할인 가능
 *
 * 필수기능3: 상품 구매 후 환불 기능
 *   - Server::refund() -> Account::remove_cloth(serial) -> 포인트 복구 및 재계산
 */
#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/Menu.h"
#include "../include/AccountManager.h"
#include "../include/Server.h"

int main() {
	// 1. 프로그램 오프닝 (작성자 정보 출력)
	Menu::opening();

	// 2. 서버 생성 및 초기화 (재고 하드코딩)
	Server main_server = Menu::setup_server();

	// 3. 메인 메뉴 실행
	//    - 로그인 상태: 회원 메뉴 (구매, 환불, 이력 조회, 포인트 확인)
	//    - 미로그인 상태: 비회원 메뉴 (로그인, 회원가입, 비회원 구매)
	Menu::start_menu(main_server);

	return 0;
}