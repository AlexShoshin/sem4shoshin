#include <iostream>
#include "Vector2.h"

int main()
{
	Vector2 vect;
	std::cin >> vect;
	std::cout << "vect: " << vect << "\n";
	Vector2 second(3, 4);
	std::cout << "second: " << second << "\n";
	Vector2 third = vect + second;
	std::cout << "third(+): " << third << "\n";
	third += second;
	std::cout << "third += second: " << third << "\n";
	third = vect - second;
	std::cout << "third = vect - second: " << third << "\n";
	third -= second;
	std::cout << "third -= second: " << third << "\n";
	int scal = third * vect;
	std::cout << "scal = third * vect: " << scal << "\n";
	int vec = third ^ vect;
	std::cout << "vec = third ^ vect: " << vec << "\n";
	vect = vect * 5;
	std::cout << "vect * 5: " << vect << "\n";
	vect = 3 * vect;
	std::cout << "3 * vect: " << vect << "\n";
	vect = vect / 15;
	std::cout << "vect / 15: " << vect << "\n";
	float len = second.len();
	std::cout << "len = second.len(): " << len << "\n";
	float squareLen = second.squareLen();
	std::cout << "squareLen = second.squareLen(): " << squareLen << "\n";
	Vector2 normed = second.norm();
	std::cout << "normed = second.norm(): " << normed << "\n";
	Vector2 perped = second.perpen();
	std::cout << "perped = second.perpen(): " << perped << "\n";
	Vector2 not_second = -second;
	std::cout << "not_second = -second: " << not_second << "\n";
	Vector2 rot(0, 5);
	Vector2 rotated = rot.getRotated(1.57);
	std::cout << "rotated = rot.getRotated(1.57): " << rotated << "\n";
	rot.rotate(1.57);
	std::cout << "rotated rot(0, 5) for pi/2: " << rot << "\n";
	
	system("pause");
	return 0;
}