/*
Server는 프로그램의 중추 관리 클래스로, AccountManager, 재고, 상품 카테고리 등
모든 하위 객체를 소유하고 비즈니스 로직을 총괄한다.
main()에서는 Server 객체 하나만 생성하여 모든 작업을 처리한다.

담당 기능:
- 로그인 / 로그아웃
- 회원가입 (AccountManager에 위임)
- 옷 구매 (구매 처리 및 포인트 적립)
- 옷 환불 (환불 처리 및 포인트 회수)
- 포인트 적립 (구매 가격 5만원마다 적립금 1,000원)
*/
#ifndef SERVER_H
#define SERVER_H
#include "Account.h"
#include "AccountManager.h"
#include "ClothStock.h"

class Server {
private:
	// 로그인한 계정. 로그인하지 않은 상태인 경우, 반드시 nullptr가 할당된 상태여야 함.
	Account* logged_in_account;
	AccountManager account_manager;
	std::vector<ClothStock> stock_list;
public:
	// 생성자

	Server();
	
	// 기타 함수들
	
	void signup();
	void login();
	void logout();
	void show_logged_in_id();
	void purchase();
	void refund();
	void login_by_id(const std::string& id);
	
	// getter 함수들
	
	Account* get_logged_in_account();
	AccountManager& get_account_manager();
};

#endif
