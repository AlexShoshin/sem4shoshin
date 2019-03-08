#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <math.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1200
#define RADIUS 7
#define DELTA 5.0f
#define FORCE_CONST 1000000


//Нажимая правую кнопку мыши - создаешь положительный заряд
//Среднюю - отрицательный
//ЛКМ - нарисовать линию для созданной конфигурации зарядов


void CreateChargePositive(sf::RenderWindow& window, std::vector<sf::Vertex>& centres, std::vector<sf::CircleShape>& charges_array);
void CreateChargeNegative(sf::RenderWindow& window, std::vector<sf::Vertex>& centres, std::vector<sf::CircleShape>& charges_array);
void CreateForceLine(sf::RenderWindow& window, std::vector<sf::Vertex>& dots_forward, std::vector<sf::Vertex>& dots_back, std::vector<sf::Vertex>& centres_positive, std::vector<sf::Vertex>& centres_negative);
void CalculateForce(sf::Vector2f& force, std::vector<sf::Vertex>& centres_positive, std::vector<sf::Vertex>& centres_negative, sf::Vertex& dot);
void DrawForwardLine(sf::RenderWindow& window, std::vector<sf::Vertex>& dots_forward);
void DrawBackwardLine(sf::RenderWindow& window, std::vector<sf::Vertex>& dots_back);

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "ForceFields");

	std::vector<sf::CircleShape> charges_positive_array;
	std::vector<sf::CircleShape> charges_negative_array;
	std::vector<sf::Vertex> dots_forward;
	std::vector<sf::Vertex> dots_back;
	std::vector<sf::Vertex> centres_positive;
	std::vector<sf::Vertex> centres_negative;
	unsigned int i;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right) 
				{
					CreateChargePositive(window, centres_positive, charges_positive_array);
				}	
				else if (event.mouseButton.button == sf::Mouse::Left) 
				{
					CreateForceLine(window, dots_forward, dots_back, centres_positive, centres_negative);
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
				{
					CreateChargeNegative(window, centres_negative, charges_negative_array);
				}
				break;
			}
		}
		
		window.clear();
		for (auto it : charges_positive_array)
		{
			window.draw(it);
		}
		for (auto it : charges_negative_array)
		{
			window.draw(it);
		}
		DrawForwardLine(window, dots_forward); //Ðèñóåò ïåðâóþ ÷àñòü òî÷åê - "íà áåñêîíå÷íîñòü" îò òî÷êè êëèêà
		DrawBackwardLine(window, dots_back); //Ðèñóåò âòîðóþ ÷àñòü òî÷åê - ê çàðÿäó îò òî÷êè êëèêà
		window.display();
	}
	return 0;
}



void CreateChargePositive(sf::RenderWindow& window, std::vector<sf::Vertex>& centres, std::vector<sf::CircleShape>& charges_array)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::CircleShape circle(RADIUS);
	circle.setPosition(mousePosition.x - RADIUS, mousePosition.y - RADIUS);  //Ïîìåùàåì çàðÿä â òî÷êó êëèêà
	sf::Vertex centre;
	centre.position.x = mousePosition.x;
	centre.position.y = mousePosition.y;
	centres.push_back(centre);   //Çàíîñèì öåíòð çàðÿäà â ìàññèâ - äëÿ ðàññ÷åòîâ
	circle.setFillColor(sf::Color::Red);
	charges_array.push_back(circle); //Çàíîñèì çàðÿä â ìàññèâ äëÿ çàðèñîâêè
}

void CreateChargeNegative(sf::RenderWindow& window, std::vector<sf::Vertex>& centres, std::vector<sf::CircleShape>& charges_array)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::CircleShape circle(RADIUS);
	circle.setPosition(mousePosition.x - RADIUS, mousePosition.y - RADIUS);  //Ïîìåùàåì çàðÿä â òî÷êó êëèêà
	sf::Vertex centre;
	centre.position.x = mousePosition.x;
	centre.position.y = mousePosition.y;
	centres.push_back(centre);   //Çàíîñèì öåíòð çàðÿäà â ìàññèâ - äëÿ ðàññ÷åòîâ
	circle.setFillColor(sf::Color::Blue);
	charges_array.push_back(circle); //Çàíîñèì çàðÿä â ìàññèâ äëÿ çàðèñîâêè
}

void CreateForceLine(sf::RenderWindow& window, std::vector<sf::Vertex>& dots_forward, std::vector<sf::Vertex>& dots_back, std::vector<sf::Vertex>& centres_positive, std::vector<sf::Vertex>& centres_negative)
{
	sf::Vector2i dot_position;
	sf::Vector2f force;
	sf::Vertex click;
	sf::Vertex dot;
	sf::Vertex next;
	unsigned int i;
	int flag = 0;

	next.position.x = 0;   
	next.position.y = 0;
	dots_forward.push_back(next);  //Çàíîñèì "ïóñòóþ" òî÷êó, ÷òîáû â ìàññèâå îòäåëÿòü îäíó ñèëîâóþ ëèíèþ îò äðóãîé
	dot_position = sf::Mouse::getPosition(window);
	click.position.x = dot_position.x;   //Ñîçðàíÿåì ìåñòîïîëîæåíèå òî÷êè êëèêà
	click.position.y = dot_position.y;

	dot.position.x = dot_position.x;   //Ïåðâàÿ ðàáî÷àÿ òî÷êà - òî÷êà êëèêà
	dot.position.y = dot_position.y;
	dots_forward.push_back(click);
	
	//Ñëåäóþùåå óñëîâèå  íåîáõîäèìî äëÿ òîãî, ÷òîáû ëèíèÿ ñîçäàâàëàñü òîëüêî äî êðàÿ îêíà
	while ((dot.position.x > 0) && (dot.position.x < SCREEN_WIDTH) && (dot.position.y > 0) && (dot.position.y < SCREEN_HEIGHT) && (flag == 0))
	{
		CalculateForce(force, centres_positive, centres_negative, dot);
		next.position.x = dot.position.x + force.x * DELTA;  // Ñìåùàåìñÿ îò òåêóùåé òî÷êå ÷óòü äàëüøå âäîëü ñèëîâûõ ëèíèé
		next.position.y = dot.position.y + force.y * DELTA;
		dots_forward.push_back(next);   //Çàíîñèì òåêóùóþ òî÷êó â ìàññèâ
		dot.position.x = next.position.x;   //Ñìåíÿåì ðàáî÷óþ òî÷êó íà ñëåäóþùóþ ïî ïîðÿäêó
		dot.position.y = next.position.y;

		for (i = 0; i < centres_positive.size(); i++)
		{
			//Ñëåäóþùåå óñëîâèå - ïðîâåðêà íà íàõîæäåíèå â êðóæêå çàðÿäà
			if (abs(next.position.x - centres_positive[i].position.x) < RADIUS && abs(next.position.y - centres_positive[i].position.y) < RADIUS)
			{
				flag = 1;
				break;
			}
		}
		for (i = 0; i < centres_negative.size(); i++)
		{
			//Ñëåäóþùåå óñëîâèå - ïðîâåðêà íà íàõîæäåíèå â êðóæêå çàðÿäà
			if (abs(next.position.x - centres_negative[i].position.x) < RADIUS && abs(next.position.y - centres_negative[i].position.y) < RADIUS)
			{
				flag = 1;
				break;
			}
		}
	}

	flag = 0;
	next.position.x = 0;     //Çäåñü íà÷èíàåòñÿ ñîçäàíèå òî÷åê "ê çàðÿäó"
	next.position.y = 0;
	dots_back.push_back(next);
	dot.position.x = click.position.x;
	dot.position.y = click.position.y;
	dots_back.push_back(click);

	while ((dot.position.x > 0) && (dot.position.x < SCREEN_WIDTH) && (dot.position.y > 0) && (dot.position.y < SCREEN_HEIGHT) && flag == 0)  //ôëàã ïîäíèìàåòñÿ, êîãäà ëèíèÿ çàõîäèò â êðóæîê çàðÿäà
	{
		CalculateForce(force, centres_positive, centres_negative, dot);
		next.position.x = dot.position.x - force.x * DELTA;  // Ñìåùàåìñÿ îò òåêóùåé òî÷êå ÷óòü äàëüøå âäîëü ñèëîâûõ ëèíèé
		next.position.y = dot.position.y - force.y * DELTA;
		dots_back.push_back(next);   //Çàíîñèì òåêóùóþ òî÷êó â ìàññèâ
		dot.position.x = next.position.x;   //Ñìåíÿåì ðàáî÷óþ òî÷êó íà ñëåäóþùóþ ïî ïîðÿäêó
		dot.position.y = next.position.y;

		for (i = 0; i < centres_positive.size(); i++)
		{
			//Ñëåäóþùåå óñëîâèå - ïðîâåðêà íà íàõîæäåíèå â êðóæêå çàðÿäà
			if (abs(next.position.x - centres_positive[i].position.x) < RADIUS && abs(next.position.y - centres_positive[i].position.y) < RADIUS)
			{
				flag = 1;
				break;
			}
		}
		for (i = 0; i < centres_negative.size(); i++)
		{
			//Ñëåäóþùåå óñëîâèå - ïðîâåðêà íà íàõîæäåíèå â êðóæêå çàðÿäà
			if (abs(next.position.x - centres_negative[i].position.x) < RADIUS && abs(next.position.y - centres_negative[i].position.y) < RADIUS)
			{
				flag = 1;
				break;
			}
		}
	}
}

void CalculateForce(sf::Vector2f& force, std::vector<sf::Vertex>& centres_positive, std::vector<sf::Vertex>& centres_negative, sf::Vertex& dot)
{
	float len;
	force.x = 0;
	force.y = 0;
	for (auto it : centres_positive) //Áåæèì ïî ìàññèâó çàðÿäîâ, ñóììèðóÿ èõ âêëàäû â ïîëå
	{
		len = sqrt(pow((dot.position.x - it.position.x), 2) + pow((dot.position.y - it.position.y), 2));
		//Äîáàâëÿåì ê ñèëå êîìïîíåíòû âåêòîðîâ ñèëîâûõ ïîëåé (E = C/(r^2))
		force.x += FORCE_CONST * (dot.position.x - it.position.x) / (len * len);
		force.y += FORCE_CONST * (dot.position.y - it.position.y) / (len * len);

	}
	for (auto it : centres_negative) //Áåæèì ïî ìàññèâó çàðÿäîâ, ñóììèðóÿ èõ âêëàäû â ïîëå
	{
		len = sqrt(pow((dot.position.x - it.position.x), 2) + pow((dot.position.y - it.position.y), 2));
		//Äîáàâëÿåì ê ñèëå êîìïîíåíòû âåêòîðîâ ñèëîâûõ ïîëåé (E = C/(r^2))
		force.x -= FORCE_CONST * (dot.position.x - it.position.x) / (len * len);
		force.y -= FORCE_CONST * (dot.position.y - it.position.y) / (len * len);

	}
	len = sqrt(pow(force.x, 2) + pow(force.y, 2));  //Íîðìèðóåì ñèëó, ò.ê. õîòèì, ÷òîáû ñìåùåíèå îò òî÷êè ê òî÷êå íå çàâèñåëî îò åå âåëè÷èíû
	force.x /= len;
	force.y /= len;
}



void DrawForwardLine(sf::RenderWindow& window, std::vector<sf::Vertex>& dots_forward)
{
	unsigned int i;
	if (dots_forward.size() != 0)
	{
		for (i = 0; i < dots_forward.size() - 1; i++)
		{
			//Ñëåäóþùåå óñëîâèå íåîáõîäèìî, ÷òîáû íå ñîåäèíÿëèñü ìåæäó ñîáîé òî÷êè ðàçíûõ ñèëîâûõ ëèíèé
			if ((dots_forward[i].position.x > 0 && dots_forward[i + 1].position.x > 0) && (dots_forward[i].position.y > 0 && dots_forward[i + 1].position.y > 0) &&
				(dots_forward[i].position.x < SCREEN_WIDTH && dots_forward[i + 1].position.x < SCREEN_WIDTH) && (dots_forward[i].position.y < SCREEN_HEIGHT && dots_forward[i + 1].position.y < SCREEN_HEIGHT))
			{
				sf::Vertex line[] =
				{
					sf::Vertex(dots_forward[i].position),
					sf::Vertex(dots_forward[i + 1].position)
				};
				window.draw(line, 2, sf::Lines);
			}

		}
	}
}

void DrawBackwardLine(sf::RenderWindow& window, std::vector<sf::Vertex>& dots_back)
{
	unsigned int i;
	if (dots_back.size() != 0)
	{
		for (i = 0; i < dots_back.size() - 1; i++)
		{
			//Ñëåäóþùåå óñëîâèå íåîáõîäèìî, ÷òîáû íå ñîåäèíÿëèñü ìåæäó ñîáîé òî÷êè ðàçíûõ ñèëîâûõ ëèíèé
			if (dots_back[i].position.x != 0 && dots_back[i + 1].position.x != 0)
			{
				sf::Vertex line[] =
				{
					sf::Vertex(dots_back[i].position),
					sf::Vertex(dots_back[i + 1].position)
				};
				window.draw(line, 2, sf::Lines);
			}

		}
	}
}
