#include <iostream>
#include <string>
#include <cassert>

#include "../include/Account.h"
#include "../include/Cloth.h"

using std::cout;
using std::endl;

int main() {
    cout << "=== 포인트 적립/환불 테스트 ===" << endl << endl;

    // 테스트 1: 누적 구매금액 기반 포인트 계산 검증
    cout << "[테스트 1] 구매 후 포인트 적립 검증" << endl;
    {
        Account acc("test1", "pw1");
        assert(acc.get_points() == 0);
        assert(acc.get_total_purchase_amount() == 0);

        // 49,000원 구매 (50,000 미만 → 0포인트)
        Cloth c1("Nike Shirt", "black", "top", 49000);
        acc.add_cloth(c1);
        acc.add_purchase_amount(49000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 0);
        cout << "  49,000원 구매 → 포인트: " << acc.get_points() << "원 (예상: 0) ✅" << endl;

        // 35,000원 추가 구매 (누적 84,000 → 1,000포인트)
        Cloth c2("Adidas Shorts", "red", "bottom", 35000);
        acc.add_cloth(c2);
        acc.add_purchase_amount(35000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 1000);
        cout << "  +35,000원 구매 → 누적 84,000원 → 포인트: " << acc.get_points() << "원 (예상: 1000) ✅" << endl;

        // 89,000원 추가 구매 (누적 173,000 → 3,000포인트)
        Cloth c3("NB Shoes", "white", "shoes", 89000);
        acc.add_cloth(c3);
        acc.add_purchase_amount(89000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 3000);
        cout << "  +89,000원 구매 → 누적 173,000원 → 포인트: " << acc.get_points() << "원 (예상: 3000) ✅" << endl;
    }

    // 테스트 2: 환불 후 포인트 재계산 검증
    cout << endl << "[테스트 2] 환불 후 포인트 재계산 검증" << endl;
    {
        Account acc("test2", "pw2");

        // 3개 구매: 49,000 + 35,000 + 89,000 = 173,000
        Cloth c1("Nike Shirt", "black", "top", 49000);
        Cloth c2("Adidas Shorts", "red", "bottom", 35000);
        Cloth c3("NB Shoes", "white", "shoes", 89000);

        acc.add_cloth(c1);
        acc.add_purchase_amount(49000);
        acc.add_cloth(c2);
        acc.add_purchase_amount(35000);
        acc.add_cloth(c3);
        acc.add_purchase_amount(89000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 3000);
        cout << "  3개 구매 (173,000원) → 포인트: " << acc.get_points() << "원 (예상: 3000) ✅" << endl;

        // 첫 번째 옷(49,000원) 환불 → 누적 124,000원 → 2,000포인트
        acc.remove_cloth(c1.get_serial());
        acc.subtract_purchase_amount(49000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 2000);
        cout << "  49,000원 환불 → 누적 124,000원 → 포인트: " << acc.get_points() << "원 (예상: 2000) ✅" << endl;

        // 두 번째 옷(35,000원) 환불 → 누적 89,000원 → 1,000포인트
        // (remove_cloth로 c2 찾기 위해 serial 필요. 순서가 바뀌었으니 purchase_history에서 찾음)
        const auto& history = acc.get_purchase_history();
        for (size_t i = 0; i < history.size(); ++i) {
            if (history[i].get_price() == 35000) {
                acc.remove_cloth(history[i].get_serial());
                break;
            }
        }
        acc.subtract_purchase_amount(35000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 1000);
        cout << "  35,000원 환불 → 누적 89,000원 → 포인트: " << acc.get_points() << "원 (예상: 1000) ✅" << endl;

        // 마지막 옷(89,000원) 환불 → 누적 0원 → 0포인트
        const auto& history2 = acc.get_purchase_history();
        acc.remove_cloth(history2[0].get_serial());
        acc.subtract_purchase_amount(89000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 0);
        cout << "  89,000원 환불 → 누적 0원 → 포인트: " << acc.get_points() << "원 (예상: 0) ✅" << endl;
    }

    // 테스트 3: 비회원 구매 시 포인트 미적립 (Server 검증은 별도)
    cout << endl << "[테스트 3] 경계값 테스트" << endl;
    {
        Account acc("test3", "pw3");

        // 정확히 50,000원 → 1,000포인트
        Cloth c1("Test Item", "red", "top", 50000);
        acc.add_cloth(c1);
        acc.add_purchase_amount(50000);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 1000);
        cout << "  50,000원 → 포인트: " << acc.get_points() << "원 (예상: 1000) ✅" << endl;

        // 99,999원 → 1,000포인트 (1구간)
        Cloth c2("Test Item2", "blue", "bottom", 49999);
        acc.add_cloth(c2);
        acc.add_purchase_amount(49999);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 1000);
        cout << "  +49,999원 → 누적 99,999원 → 포인트: " << acc.get_points() << "원 (예상: 1000) ✅" << endl;

        // 1원 추가 → 100,000원 → 2,000포인트
        Cloth c3("Test Item3", "green", "accessory", 1);
        acc.add_cloth(c3);
        acc.add_purchase_amount(1);
        acc.set_points(acc.get_total_purchase_amount() / 50000 * 1000);
        assert(acc.get_points() == 2000);
        cout << "  +1원 → 누적 100,000원 → 포인트: " << acc.get_points() << "원 (예상: 2000) ✅" << endl;
    }

    cout << endl << "=== 모든 테스트 통과! ===" << endl;
    return 0;
}
