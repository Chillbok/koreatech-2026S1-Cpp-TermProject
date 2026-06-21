#include "../include/Server.h"
#include "../include/Account.h"
#include "../include/ConsoleUtil.h"
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;
#include <algorithm>
#include <limits>

Server::Server() : logged_in_account(nullptr), account_manager(), stock_list() {
	stock_list.push_back({"Nike Dri-Fit Shirt", "black", "top", 49000});
	stock_list.push_back({"Adidas Shorts", "red", "bottom", 35000});
	stock_list.push_back({"New Balance Shoes", "white", "shoes", 89000});
	stock_list.push_back({"Puma Cap", "blue", "accessory", 25000});
	stock_list.push_back({"Under Armour Hoodie", "gray", "top", 75000});
	cout << "서버 생성 및 변수 초기화 완료" << endl;
}

void Server::signup() {
	account_manager.add_account_on_list();
}

void Server::login() {
	cout << endl;
	cout << "로그인" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	string input;

	// 아이디 입력 단계
	while(true) {
		cout << "아이디(종료하려면 'q' 입력): ";
		cin >> input;

		if (input == "q") {
			cout << "로그인을 취소합니다." << endl;
			logged_in_account = nullptr;
			return;
		}

		if (account_manager.define_id_exists(input) == false) {
			cerr << "[Error] 아이디 없음. 다시 입력하세요." << endl;
			continue;
		}
		
		logged_in_account = account_manager.get_account_by_id(input);
		break;
	}
	
	while(true) {
		cout << "비밀번호(종료하려면 'q' 입력): ";
		cin >> input;

		if (input == "q") {
			cout << "로그인을 취소합니다." << endl;
			logged_in_account = nullptr;
			return;
		}
		
		if (logged_in_account->check_password_correct(input) == false) {
			cerr << "[Error] 비밀번호가 틀립니다. 다시 입력하세요." << endl;
			continue;
		}
		
		cout << "로그인 성공!" << endl;
		break;
	}
}

void Server::logout() {
	cout << endl;
	
	if (logged_in_account == nullptr) {
		cerr << "[Error] 로그인된 계정 없음. 로그아웃 불가능." << endl;
		return;
	}

	cout << "# 로그아웃 절차 시작" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	logged_in_account = nullptr;
	cout << "로그아웃 되었습니다." << endl;
}

void Server::show_logged_in_id() {
	if (logged_in_account == nullptr) {
		cerr << "[Error] 로그인된 계정 없음." << endl;
		return;
	}
	cout << "현재 로그인된 계정: " << logged_in_account->get_id() << endl;
}

void Server::purchase() {
	cout << endl;
	cout << "# 구매" << endl;
	cout << ConsoleUtil::get_divider() << endl;

	for (size_t i = 0; i < stock_list.size(); ++i) {
		cout << "  " << (i + 1) << ". " << stock_list[i].name
			 << " (" << stock_list[i].color << ", " << stock_list[i].category
			 << ") " << stock_list[i].price << "원" << endl;
	}

	cout << "구매할 옷 번호 (0: 취소): ";
	int sel;
	cin >> sel;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "잘못된 입력. 구매 취소." << endl;
		return;
	}
	if (sel < 1 || sel > static_cast<int>(stock_list.size())) {
		cout << "구매 취소." << endl;
		return;
	}

	Cloth purchased(stock_list[sel - 1].name, stock_list[sel - 1].color,
	                stock_list[sel - 1].category, stock_list[sel - 1].price);

	if (logged_in_account != nullptr) {
		int original_price = stock_list[sel - 1].price;
		int final_price = original_price;
		int available_points = logged_in_account->get_points();

		if (available_points > 0) {
			cout << "보유 포인트: " << available_points << "원" << endl;
			cout << "포인트를 사용하시겠습니까? (y/n): ";
			string use;
			cin >> use;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				use = "n";
			}

			if (use == "y" || use == "Y") {
				while (true) {
					cout << "사용할 포인트 입력 (최대 " << available_points << "원, 0: 취소): ";
					int use_pts;
					cin >> use_pts;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cout << "잘못된 입력입니다." << endl;
						continue;
					}
					if (use_pts == 0) {
						cout << "포인트 사용을 취소합니다." << endl;
						break;
					}
					if (use_pts < 0 || use_pts > available_points) {
						cout << "보유 포인트 범위 내에서 입력하세요." << endl;
						continue;
					}
					if (use_pts > original_price) {
						cout << "구매 금액(" << original_price << "원)을 초과할 수 없습니다." << endl;
						continue;
					}

					logged_in_account->use_points(use_pts);
					final_price = original_price - use_pts;
					purchased.set_points_used(use_pts);
					cout << "포인트 " << use_pts << "원 사용. 결제 금액: "
						 << final_price << "원" << endl;
					break;
				}
			}
		}

		purchased.set_paid_price(final_price);
		logged_in_account->add_cloth(purchased);
		logged_in_account->add_purchase_amount(final_price);
		logged_in_account->recalculate_points();

		cout << "구매 완료! (serial: " << purchased.get_serial()
			 << ", 결제 금액: " << final_price << "원"
			 << ", 현재 포인트: " << logged_in_account->get_points() << "원)" << endl;
	} else {
		cout << "비회원 구매 완료. (포인트 적립 및 구매 이력 없음)" << endl;
	}
}

void Server::refund() {
	cout << endl;
	cout << "# 환불" << endl;
	cout << ConsoleUtil::get_divider() << endl;

	if (logged_in_account == nullptr) {
		cerr << "[Error] 로그인된 계정 없음. 환불 불가능." << endl;
		return;
	}

	const auto& history = logged_in_account->get_purchase_history();
	if (history.empty()) {
		cout << "구매한 옷이 없습니다." << endl;
		return;
	}

	cout << "[구매한 옷 목록]" << endl;
	for (size_t i = 0; i < history.size(); ++i) {
		cout << "  " << (i + 1) << ". " << history[i].get_name()
			 << " (" << history[i].get_color() << ", " << history[i].get_category()
			 << ") " << history[i].get_price() << "원"
			 << " | serial: " << history[i].get_serial() << endl;
	}

	cout << "환불할 serial 입력 (0: 취소): ";
	string serial;
	cin >> serial;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "잘못된 입력. 환불 취소." << endl;
		return;
	}
	if (serial == "0") {
		cout << "환불 취소." << endl;
		return;
	}

	auto it = std::find_if(history.begin(), history.end(),
		[&serial](const Cloth& c) { return c.get_serial() == serial; });

	if (it == history.end()) {
		cout << "해당 serial의 옷을 찾을 수 없습니다." << endl;
		return;
	}

	int refund_price = it->get_paid_price();
	int points_to_restore = it->get_points_used();

	if (logged_in_account->remove_cloth(serial)) {
		logged_in_account->subtract_purchase_amount(refund_price);
		if (points_to_restore > 0) {
			logged_in_account->restore_points(points_to_restore);
		}
		logged_in_account->recalculate_points();

		cout << "환불 완료. (" << refund_price << "원 환불"
			 << ", 현재 포인트: " << logged_in_account->get_points() << "원)" << endl;
	}
}

void Server::login_by_id(const std::string& id) {
	logged_in_account = account_manager.get_account_by_id(id);
}

Account* Server::get_logged_in_account() { 
	if (logged_in_account == nullptr) return nullptr;
	return logged_in_account;
}
AccountManager& Server::get_account_manager() { return account_manager; }
const std::vector<ClothStock>& Server::get_stock_list() const { return stock_list; }