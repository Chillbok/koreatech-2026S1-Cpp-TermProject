#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/Cloth.h"
#include "../include/ClothStock.h"

int main() {
	cout << ConsoleUtil::get_divider() << endl;
	cout << "[Cloth / ClothStock 기능 테스트]" << endl;
	cout << ConsoleUtil::get_divider() << endl;

	ClothStock stock1{"Nike Dri-Fit Shirt", "black", "top", 49000};
	ClothStock stock2{"Adidas Shorts", "red", "bottom", 35000};
	ClothStock stock3{"New Balance Shoes", "white", "shoes", 89000};

	cout << "[재고 목록]" << endl;
	cout << "  stock1: " << stock1.name << ", " << stock1.color
		 << ", " << stock1.category << ", " << stock1.price << "원" << endl;
	cout << "  stock2: " << stock2.name << ", " << stock2.color
		 << ", " << stock2.category << ", " << stock2.price << "원" << endl;
	cout << "  stock3: " << stock3.name << ", " << stock3.color
		 << ", " << stock3.category << ", " << stock3.price << "원" << endl;

	cout << endl << "[Cloth 구매 시뮬레이션 (serial 자동 생성)]" << endl;
	Cloth cloth1(stock1.name, stock1.color, stock1.category, stock1.price);
	Cloth cloth2(stock2.name, stock2.color, stock2.category, stock2.price);
	Cloth cloth3(stock3.name, stock3.color, stock3.category, stock3.price);

	cout << "  cloth1: " << cloth1.get_name() << ", " << cloth1.get_color()
		 << ", " << cloth1.get_category() << ", " << cloth1.get_price()
		 << "원, serial=" << cloth1.get_serial() << endl;
	cout << "  cloth2: " << cloth2.get_name() << ", " << cloth2.get_color()
		 << ", " << cloth2.get_category() << ", " << cloth2.get_price()
		 << "원, serial=" << cloth2.get_serial() << endl;
	cout << "  cloth3: " << cloth3.get_name() << ", " << cloth3.get_color()
		 << ", " << cloth3.get_category() << ", " << cloth3.get_price()
		 << "원, serial=" << cloth3.get_serial() << endl;

	cout << endl << "[기본 생성자 + setter 테스트]" << endl;
	Cloth cloth4;
	cloth4.set_name("Puma Jacket");
	cloth4.set_color("green");
	cloth4.set_category("top");
	cloth4.set_price(120000);

	cout << "  cloth4: " << cloth4.get_name() << ", " << cloth4.get_color()
		 << ", " << cloth4.get_category() << ", " << cloth4.get_price()
		 << "원, serial=" << cloth4.get_serial() << endl;

	cout << endl << "[generate_random_hash() 직접 호출]" << endl;
	cout << "  해시1: " << generate_random_hash() << endl;
	cout << "  해시2: " << generate_random_hash() << endl;
	cout << "  해시3: " << generate_random_hash() << endl;

	cout << endl << "[set_serial() 테스트 (환불 복원 시나리오)]" << endl;
	std::string saved_serial = cloth1.get_serial();
	cout << "  cloth1 원본 serial: " << saved_serial << endl;

	Cloth restored_cloth(cloth1.get_name(), cloth1.get_color(),
	                     cloth1.get_category(), cloth1.get_price());
	restored_cloth.set_serial(saved_serial);
	cout << "  복원된 cloth serial: " << restored_cloth.get_serial() << endl;
	cout << "  serial 일치 여부: " << (saved_serial == restored_cloth.get_serial() ? "true" : "false") << endl;

	cout << endl << ConsoleUtil::get_divider() << endl;
	cout << "테스트 종료." << endl;

	return 0;
}
