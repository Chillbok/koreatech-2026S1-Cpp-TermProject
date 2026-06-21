#include <iostream>
#include <string>
#include <vector>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;

#include "../include/Account.h"
#include "../include/Cloth.h"
#include "../include/ClothStock.h"
#include "../include/ConsoleUtil.h"
#include "../include/Server.h"

void show_account_info(const Account& acc) {
	cout << ConsoleUtil::get_divider() << endl;
	cout << "  ID: " << acc.get_id() << endl;
	cout << "  포인트: " << acc.get_points() << "원" << endl;
	cout << "  총 구매 금액: " << acc.get_total_purchase_amount() << "원" << endl;
	cout << "  구매한 옷 수: " << acc.get_purchase_history().size() << "개" << endl;

	const auto& history = acc.get_purchase_history();
	for (size_t i = 0; i < history.size(); ++i) {
		cout << "    [" << i + 1 << "] " << history[i].get_name()
			 << " (" << history[i].get_color() << ", " << history[i].get_category()
			 << ") " << history[i].get_price() << "원"
			 << " serial=" << history[i].get_serial() << endl;
	}
}

int main() {
	Server server;
	Account* acc_ptr = nullptr;

	while (true) {
		cout << ConsoleUtil::get_divider() << endl;
		cout << "[Account 테스트 메뉴]" << endl;
		cout << "  1. 계정 생성" << endl;
		cout << "  2. 계정 정보 보기" << endl;
		cout << "  3. 포인트 추가" << endl;
		cout << "  4. 포인트 설정" << endl;
		cout << "  5. 구매 금액 추가" << endl;
		cout << "  6. 구매 금액 설정" << endl;
		cout << "  7. 옷 구매 (재고에서 선택)" << endl;
		cout << "  8. 옷 환불 (serial 입력)" << endl;
		cout << "  0. 종료" << endl;
		cout << "선택: ";

		int choice;
		cin >> choice;

		if (cin.eof()) {
			cout << endl << "테스트 종료." << endl;
			break;
		}
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "숫자를 입력하세요." << endl;
			continue;
		}

		if (choice == 0) {
			cout << "테스트 종료." << endl;
			break;
		}

		if (choice == 1) {
			string id, pw;
			cout << "ID: ";
			cin >> id;
			cout << "Password: ";
			cin >> pw;
			{
				Account new_acc(id, pw);
				server.get_account_manager().add_account(new_acc);
			}
			server.login_by_id(id);
			acc_ptr = server.get_logged_in_account();
			cout << "계정 생성 및 로그인 완료: " << id << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
			continue;
		}

		if (acc_ptr == nullptr && choice != 7) {
			cout << "먼저 계정을 생성하세요 (1번)." << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
			continue;
		}

		if (choice == 2) {
			show_account_info(*acc_ptr);
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else if (choice == 3) {
			int points;
			cout << "추가할 포인트: ";
			cin >> points;
			acc_ptr->add_points(points);
			cout << "현재 포인트: " << acc_ptr->get_points() << "원" << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else if (choice == 4) {
			int points;
			cout << "설정할 포인트: ";
			cin >> points;
			acc_ptr->set_points(points);
			cout << "현재 포인트: " << acc_ptr->get_points() << "원" << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else if (choice == 5) {
			int amount;
			cout << "추가할 구매 금액: ";
			cin >> amount;
			acc_ptr->add_purchase_amount(amount);
			cout << "현재 총 구매 금액: " << acc_ptr->get_total_purchase_amount() << "원" << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else if (choice == 6) {
			int amount;
			cout << "설정할 구매 금액: ";
			cin >> amount;
			acc_ptr->set_total_purchase_amount(amount);
			cout << "현재 총 구매 금액: " << acc_ptr->get_total_purchase_amount() << "원" << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else if (choice == 7) {
			server.purchase();
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else if (choice == 8) {
			server.refund();
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
		else {
			cout << "잘못된 선택입니다." << endl;
			ConsoleUtil::press_enter();
			ConsoleUtil::clear_screen();
		}
	}

	return 0;
}
