// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct Statistics
{
	int count;
	std::string word;
};

bool cmp(const Statistics &a, const Statistics &b);
std::string prepare(const std::string& s);


// Скрин с результатами частоты слов по книге "Harry Potter and Phylosofer's stone" приложен

int main()
{
	std::string s;
	std::string buff;
	std::map<std::string, int> dict;
	std::ifstream f("harry_potter.txt");
	if (f.is_open())
	{
		while (!f.eof())
		{
			f >> s;
			s = prepare(s);
			dict[s] += 1;
		}
	}

	
	struct Statistics st;
	std::vector<Statistics> vec;
	int i = 0;
	
	for (auto& [word, word_count] : dict)
	{
		st.count =  word_count;
		st.word = word;
		vec.push_back(st);
	}
	std::sort(vec.begin(), vec.end(), cmp);
	for (auto it : vec)
	{
		if (it.count > 30) //исключил слова, встечающиеся меньше 30 раз, так как они сильно тормрзят процесс, да и в сущности не важны
		{
			cout << it.word << " " << it.count << "\n";
		}
	}

	return 0;
}


bool cmp(const Statistics &a, const Statistics &b)
{
	if (a.count > b.count)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string prepare(const std::string& s)
{
	std::string result;
	result = s;
	std::transform(s.begin(), s.end(), result.begin(), ::tolower);
	if (result[result.length() - 1] == ',' or result[result.length() - 1] == '.')
	{
		result.pop_back();
	}
	return result;
}







// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
