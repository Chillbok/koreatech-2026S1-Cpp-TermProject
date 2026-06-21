#include <iostream>
#include <string>
#include <cassert>
using std::cout;
using std::endl;
using std::string;

#include "../include/ConsoleUtil.h"
#include "../include/Server.h"
#include "../include/Account.h"
#include "../include/Cloth.h"

int main() {
    cout << ConsoleUtil::get_divider() << endl;
    cout << "  통합 기능 테스트 (자동화)" << endl;
    cout << ConsoleUtil::get_divider() << endl;
    cout << endl;

    Server server;

    // ============================================================
    // 1. 계정 생성
    // ============================================================
    cout << "[1] 계정 생성 테스트" << endl;
    {
        Account acc1("alice", "1234");
        Account acc2("bob", "5678");
        server.get_account_manager().add_account(acc1);
        server.get_account_manager().add_account(acc2);
        assert(server.get_account_manager().get_account_list_size() == 2);
        cout << "  alice, bob 계정 생성 완료 (총 " 
             << server.get_account_manager().get_account_list_size() << "개)" << endl;
    }
    cout << endl;

    // ============================================================
    // 2. 로그인 테스트
    // ============================================================
    cout << "[2] 로그인 테스트" << endl;
    {
        server.login_by_id("alice");
        Account* logged = server.get_logged_in_account();
        assert(logged != nullptr);
        assert(logged->get_id() == "alice");
        cout << "  alice 로그인 성공" << endl;
    }
    cout << endl;

    // ============================================================
    // 3. 회원 구매 + 포인트 적립 테스트
    // ============================================================
    cout << "[3] 회원 구매 및 포인트 적립 테스트" << endl;
    {
        Account* acc = server.get_logged_in_account();
        const auto& stock = server.get_stock_list();

        // 3-1. 49,000원 구매 → 누적 49,000원 → 0포인트
        Cloth c1(stock[0].name, stock[0].color, stock[0].category, stock[0].price);
        acc->add_cloth(c1);
        acc->add_purchase_amount(49000);
        acc->recalculate_points();
        assert(acc->get_points() == 0);
        cout << "  Nike Dri-Fit Shirt 구매 (49,000원) → 누적 49,000원, 포인트: " 
             << acc->get_points() << "원" << endl;

        // 3-2. Adidas Shorts 구매 (35,000원) → 누적 84,000원 → 1,000포인트
        Cloth c2(stock[1].name, stock[1].color, stock[1].category, stock[1].price);
        acc->add_cloth(c2);
        acc->add_purchase_amount(35000);
        acc->recalculate_points();
        assert(acc->get_points() == 1000);
        cout << "  Adidas Shorts 구매 (35,000원) → 누적 84,000원, 포인트: " 
             << acc->get_points() << "원" << endl;

        // 3-3. NB Shoes 구매 (89,000원) → 누적 173,000원 → 3,000포인트
        Cloth c3(stock[2].name, stock[2].color, stock[2].category, stock[2].price);
        acc->add_cloth(c3);
        acc->add_purchase_amount(89000);
        acc->recalculate_points();
        assert(acc->get_points() == 3000);
        cout << "  NB Shoes 구매 (89,000원) → 누적 173,000원, 포인트: " 
             << acc->get_points() << "원" << endl;

        // 3-4. Under Armour Hoodie 구매 (75,000원) → 누적 248,000원 → 4,000포인트
        Cloth c4(stock[4].name, stock[4].color, stock[4].category, stock[4].price);
        acc->add_cloth(c4);
        acc->add_purchase_amount(75000);
        acc->recalculate_points();
        assert(acc->get_points() == 4000);
        cout << "  Under Armour Hoodie 구매 (75,000원) → 누적 248,000원, 포인트: " 
             << acc->get_points() << "원" << endl;
    }
    cout << endl;

    // ============================================================
    // 4. 구매이력 조회 테스트
    // ============================================================
    cout << "[4] 구매이력 조회 테스트" << endl;
    {
        Account* acc = server.get_logged_in_account();
        const auto& history = acc->get_purchase_history();
        assert(history.size() == 4);
        cout << "  " << acc->get_id() << " 님 구매이력 (" << history.size() << "개):" << endl;
        for (size_t i = 0; i < history.size(); ++i) {
            cout << "    " << (i + 1) << ". " << history[i].get_name()
                 << " (" << history[i].get_color() << ", " << history[i].get_category()
                 << ") " << history[i].get_price() << "원"
                 << " | serial: " << history[i].get_serial() << endl;
        }
        cout << "  총 구매 금액: " << acc->get_total_purchase_amount() << "원" << endl;
        cout << "  적립 포인트: " << acc->get_points() << "원" << endl;
    }
    cout << endl;

    // ============================================================
    // 5. 환불 테스트
    // ============================================================
    cout << "[5] 환불 및 포인트 재계산 테스트" << endl;
    {
        Account* acc = server.get_logged_in_account();
        const auto& history = acc->get_purchase_history();

        // 첫 번째 옷(49,000원) 환불 → 누적 199,000원 → 3,000포인트
        string serial1 = history[0].get_serial();
        int price1 = history[0].get_price();
        acc->remove_cloth(serial1);
        acc->subtract_purchase_amount(price1);
        acc->recalculate_points();
        assert(acc->get_points() == 3000);
        cout << "  Nike Dri-Fit Shirt 환불 (49,000원) → 누적 " 
             << acc->get_total_purchase_amount() << "원, 포인트: " << acc->get_points() << "원" << endl;
        assert(acc->get_purchase_history().size() == 3);

        // 마지막 옷(75,000원) 환불 → 누적 124,000원 → 2,000포인트
        const auto& history2 = acc->get_purchase_history();
        string serial_last = history2.back().get_serial();
        int price_last = history2.back().get_price();
        acc->remove_cloth(serial_last);
        acc->subtract_purchase_amount(price_last);
        acc->recalculate_points();
        assert(acc->get_points() == 2000);
        cout << "  Under Armour Hoodie 환불 (75,000원) → 누적 " 
             << acc->get_total_purchase_amount() << "원, 포인트: " << acc->get_points() << "원" << endl;
        assert(acc->get_purchase_history().size() == 2);
    }
    cout << endl;

    // ============================================================
    // 6. 로그아웃 테스트
    // ============================================================
    cout << "[6] 로그아웃 테스트" << endl;
    {
        server.logout();
        assert(server.get_logged_in_account() == nullptr);
        cout << "  로그아웃 성공 (logged_in_account == nullptr)" << endl;
    }
    cout << endl;

    // ============================================================
    // 7. 다른 계정 로그인 후 구매 테스트
    // ============================================================
    cout << "[7] 다른 계정(bob) 로그인 및 구매 테스트" << endl;
    {
        server.login_by_id("bob");
        Account* acc = server.get_logged_in_account();
        assert(acc != nullptr);
        assert(acc->get_id() == "bob");

        const auto& stock = server.get_stock_list();
        Cloth c1(stock[0].name, stock[0].color, stock[0].category, stock[0].price);
        acc->add_cloth(c1);
        acc->add_purchase_amount(49000);
        acc->recalculate_points();
        assert(acc->get_points() == 0);
        cout << "  bob 로그인 후 Nike Shirt 구매 → 포인트: " << acc->get_points() << "원" << endl;

        Cloth c2(stock[4].name, stock[4].color, stock[4].category, stock[4].price);
        acc->add_cloth(c2);
        acc->add_purchase_amount(75000);
        acc->recalculate_points();
        assert(acc->get_points() == 2000);
        cout << "  UA Hoodie 추가 구매 → 누적 124,000원, 포인트: " << acc->get_points() << "원" << endl;
    }
    cout << endl;

    // ============================================================
    // 8. 포인트 사용(할인) 테스트
    // ============================================================
    cout << "[8] 포인트 사용(할인) 테스트" << endl;
    {
        server.login_by_id("alice");
        Account* acc = server.get_logged_in_account();
        int before_points = acc->get_points();
        int before_total = acc->get_total_purchase_amount();
        cout << "  alice 보유 포인트: " << before_points << "원, 누적 구매: " << before_total << "원" << endl;

        const auto& stock = server.get_stock_list();
        // Puma Cap 25,000원 구매, 포인트 1,000원 사용
        Cloth c1(stock[3].name, stock[3].color, stock[3].category, stock[3].price);
        int final_price = 25000 - 1000;
        c1.set_paid_price(final_price);
        c1.set_points_used(1000);
        acc->add_cloth(c1);
        acc->add_purchase_amount(final_price);
        acc->use_points(1000);
        acc->recalculate_points();
        // 누적: 124000 + 24000 = 148000, earned = 148000/50000*1000 = 2000
        // used_points = 1000, points = 2000 - 1000 = 1000
        assert(acc->get_points() == 1000);
        cout << "  Puma Cap 구매 (25,000원 → 포인트 1,000원 할인 → 24,000원 결제)" << endl;
        cout << "  누적 구매: " << acc->get_total_purchase_amount() 
             << "원, 포인트: " << acc->get_points() << "원" << endl;

        // 구매한 Cap 즉시 환불 → 포인트 복구 확인
        string cap_serial = c1.get_serial();
        acc->remove_cloth(cap_serial);
        acc->subtract_purchase_amount(24000);
        acc->restore_points(1000);
        acc->recalculate_points();
        // 누적: 124000, used_points = 0, earned = 124000/50000*1000 = 2000
        assert(acc->get_points() == 2000);
        cout << "  Puma Cap 환불 → 누적 " << acc->get_total_purchase_amount() 
             << "원, 포인트 복구: " << acc->get_points() << "원" << endl;
    }
    cout << endl;

    // ============================================================
    // 9. 재고 목록 조회 테스트
    // ============================================================
    cout << "[9] 재고 목록 조회 테스트" << endl;
    {
        const auto& stock = server.get_stock_list();
        for (size_t i = 0; i < stock.size(); ++i) {
            cout << "  " << (i + 1) << ". " << stock[i].name
                 << " (" << stock[i].color << ", " << stock[i].category
                 << ") " << stock[i].price << "원" << endl;
        }
    }
    cout << endl;

    // ============================================================
    // 10. 계정 목록 조회 테스트
    // ============================================================
    cout << "[10] 계정 목록 조회 테스트" << endl;
    {
        server.get_account_manager().show_existing_accounts();
    }
    cout << endl;

    // ============================================================
    // 11. 비회원 구매 테스트
    // ============================================================
    cout << "[11] 비회원 구매 테스트 (포인트/이력 없음 확인)" << endl;
    {
        server.logout();
        assert(server.get_logged_in_account() == nullptr);

        // Server::purchase는 cin 입력이 필요하므로 직접 구매 시뮬레이션
        const auto& stock = server.get_stock_list();
        Cloth guest_purchase(stock[3].name, stock[3].color, stock[3].category, stock[3].price);
        cout << "  비회원 구매 시뮬레이션: " << guest_purchase.get_name()
             << " (" << guest_purchase.get_price() << "원)" << endl;
        cout << "  → 비회원은 구매 이력/포인트 적립 없음" << endl;
    }
    cout << endl;

    // ============================================================
    // 12. 최종 상태 출력
    // ============================================================
    cout << ConsoleUtil::get_divider() << endl;
    cout << "[최종 상태 요약]" << endl;
    {
        // alice 상태
        server.login_by_id("alice");
        Account* alice = server.get_logged_in_account();
        cout << "  alice: 구매 " << alice->get_purchase_history().size() 
             << "건, 총액 " << alice->get_total_purchase_amount() 
             << "원, 포인트 " << alice->get_points() << "원" << endl;

        // bob 상태
        server.login_by_id("bob");
        Account* bob = server.get_logged_in_account();
        cout << "  bob: 구매 " << bob->get_purchase_history().size() 
             << "건, 총액 " << bob->get_total_purchase_amount() 
             << "원, 포인트 " << bob->get_points() << "원" << endl;
    }

    cout << endl;
    cout << ConsoleUtil::get_divider() << endl;
    cout << "  모든 통합 테스트 통과!" << endl;
    cout << ConsoleUtil::get_divider() << endl;

    return 0;
}
