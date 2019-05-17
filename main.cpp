#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Box2D\Box2D.h>
#include <string.h>
#include <math.h>
#include <vector>
#include "MyContactListener.h"

#define HEIGHT 1080
#define WIDTH 1920
#define SCALE 30.f
#define DEG 57.29577f


b2Vec2 gravity(0.0f, 9.8f);
b2World world(gravity);

void CreateGround();
b2Body* CreateBird(int x, int y, int real_flag, const char* colour);
void CreatePig(int x, int y);
void CreateBlock(int center_x, int center_y, const char* material, const char* orientation, const char* size);
void CreateMap();
void CreateBox(int center_x, int center_y);
void DestroyObjects(sf::Sound& woodhit, sf::Sound& icehit, sf::Sound& icedie, sf::Sound& wooddie, sf::Sound& pigdamage, sf::Sound& pigdestroyed,
	sf::Sound& rockdamage, sf::Sound& rockdestroyed, sf::Sound& birdhit, int* pig_counter, b2Body* bird_body);
void DrawSprites(sf::RenderWindow& window, sf::Sprite& redbirdSprite, sf::Sprite notredbirdSprite, sf::Sprite& yelbirdSprite, sf::Sprite notyelbirdSprite,
	sf::Sprite pigSprite2, sf::Sprite pigSprite1, sf::Sprite block_woodhorzsmal3, sf::Sprite block_woodhorzsmal2, sf::Sprite block_woodhorzsmal1,
	sf::Sprite block_icedhorzlong3, sf::Sprite block_icedhorzlong2, sf::Sprite block_icedhorzlong1, sf::Sprite box_ston3, sf::Sprite box_ston2, sf::Sprite box_ston1);
void DrawRope(int rope_flag, int bird_counter, sf::Vertex point2, sf::RenderWindow& window, int CX, int CY, int delta_x, int delta_y);

int main()
{
	sf::VideoMode mode = sf::VideoMode::getFullscreenModes()[0];
	sf::RenderWindow window(mode, "MyWindow", sf::Style::Fullscreen);

	window.setFramerateLimit(70);
	world.SetContactListener(new MyContactListener);
	
	//init sprites
	sf::Texture backgroundTexture, birds, blocks, buttons, skyTexture;
	backgroundTexture.loadFromFile("images/backgroundfull.jpg");
	skyTexture.loadFromFile("images/sky.jpg");
	birds.loadFromFile("images/INGAME_BIRDS_1.png");
	blocks.loadFromFile("images/INGAME_BLOCKS_1.png");
	buttons.loadFromFile("images/BUTTONS_SHEET_1.png");
	birds.setSmooth(1);
	blocks.setSmooth(1);
	buttons.setSmooth(1);

	sf::Sprite exit_button;
	exit_button.setTexture(buttons);
	exit_button.setTextureRect(sf::IntRect(472, 514, 100, 110));
	exit_button.setPosition(15, 965);

	sf::Sprite backgroundSprite1, backgroundSprite2, redbirdSprite, notredbirdSprite, pigSprite2, pigSprite1;
	sf::Sprite yelbirdSprite, notyelbirdSprite;
	sf::Sprite skySprite1, skySprite2;
	skySprite1.setTexture(skyTexture);
	skySprite1.setPosition(0, -HEIGHT);
	skySprite2.setTexture(skyTexture);
	skySprite2.setPosition(WIDTH, -HEIGHT);
	backgroundSprite1.setTexture(backgroundTexture);
	backgroundSprite2.setTexture(backgroundTexture);
	backgroundSprite2.setPosition(WIDTH, 0);
	redbirdSprite.setTexture(birds);
	redbirdSprite.setTextureRect(sf::IntRect(903, 797, 45, 45));
	redbirdSprite.setOrigin(22, 29);
	notredbirdSprite.setTexture(birds);
	notredbirdSprite.setTextureRect(sf::IntRect(903, 797, 45, 45));
	notredbirdSprite.setOrigin(22, 29);

	yelbirdSprite.setTexture(birds);
	yelbirdSprite.setTextureRect(sf::IntRect(667, 877, 60, 57));
	yelbirdSprite.setOrigin(25, 28);
	notyelbirdSprite.setTexture(birds);
	notyelbirdSprite.setTextureRect(sf::IntRect(667, 877, 60, 57));
	notyelbirdSprite.setOrigin(25, 28);

	pigSprite2.setTexture(birds);
	pigSprite2.setTextureRect(sf::IntRect(730, 856, 52, 48));
	pigSprite2.setOrigin(27, 24);
	pigSprite1.setTexture(birds);
	pigSprite1.setTextureRect(sf::IntRect(852, 798, 50, 46));
	pigSprite1.setOrigin(25, 23);

	int CX = 442, CY = 770;

	sf::Sprite right_catapult, left_catapult;
	right_catapult.setTexture(birds);
	right_catapult.setTextureRect(sf::IntRect(0, 0, 40, 200));
	right_catapult.setPosition(CX - 2, CY - 36);
	left_catapult.setTexture(birds);
	left_catapult.setTextureRect(sf::IntRect(832, 0, 44, 125));
	left_catapult.setPosition(CX - 29, CY - 40);

	sf::Sprite block_woodhorzsmal3;
	block_woodhorzsmal3.setTexture(blocks);
	block_woodhorzsmal3.setTextureRect(sf::IntRect(305, 531, 83, 41));
	block_woodhorzsmal3.setOrigin(41, 20);
	sf::Sprite block_woodhorzsmal2;
	block_woodhorzsmal2.setTexture(blocks);
	block_woodhorzsmal2.setTextureRect(sf::IntRect(305, 660, 83, 42));
	block_woodhorzsmal2.setOrigin(41, 21);
	sf::Sprite block_woodhorzsmal1;
	block_woodhorzsmal1.setTexture(blocks);
	block_woodhorzsmal1.setTextureRect(sf::IntRect(305, 788, 83, 42));
	block_woodhorzsmal1.setOrigin(41, 21);

	sf::Sprite block_icedhorzlong3;
	block_icedhorzlong3.setTexture(blocks);
	block_icedhorzlong3.setTextureRect(sf::IntRect(390, 623, 206, 22));
	block_icedhorzlong3.setOrigin(103, 11);
	sf::Sprite block_icedhorzlong2;
	block_icedhorzlong2.setTexture(blocks);
	block_icedhorzlong2.setTextureRect(sf::IntRect(804, 623, 206, 22));
	block_icedhorzlong2.setOrigin(103, 11);
	sf::Sprite block_icedhorzlong1;
	block_icedhorzlong1.setTexture(blocks);
	block_icedhorzlong1.setTextureRect(sf::IntRect(390, 645, 206, 22));
	block_icedhorzlong1.setOrigin(103, 11);

	sf::Sprite box_ston3;
	box_ston3.setTexture(blocks);
	box_ston3.setTextureRect(sf::IntRect(588, 200, 84, 84));
	box_ston3.setOrigin(42, 42);
	sf::Sprite box_ston2;
	box_ston2.setTexture(blocks);
	box_ston2.setTextureRect(sf::IntRect(420, 200, 84, 84));
	box_ston2.setOrigin(42, 42);
	sf::Sprite box_ston1;
	box_ston1.setTexture(blocks);
	box_ston1.setTextureRect(sf::IntRect(504, 200, 84, 84));
	box_ston1.setOrigin(42, 42);
	


	//init music
	sf::Music music;
	music.openFromFile("music/title_theme.ogg");
	music.setVolume(8);
	music.setLoop(1);
	music.play();

	sf::SoundBuffer woodhitbuff;
	woodhitbuff.loadFromFile("music/woodhit.ogg");
	sf::Sound woodhit(woodhitbuff);
	woodhit.setVolume(40);
	sf::SoundBuffer icehitbuff;
	icehitbuff.loadFromFile("music/icehit.ogg");
	sf::Sound icehit(icehitbuff);
	sf::SoundBuffer wooddiebuff;
	wooddiebuff.loadFromFile("music/wooddie.ogg");
	sf::Sound wooddie(wooddiebuff);
	wooddie.setVolume(40);
	sf::SoundBuffer icediebuff;
	icediebuff.loadFromFile("music/icedie.ogg");
	sf::Sound icedie(icediebuff);
	sf::SoundBuffer birdlaunchbuff;
	birdlaunchbuff.loadFromFile("music/birdlaunch.ogg");
	sf::Sound birdlaunch(birdlaunchbuff);
	birdlaunch.setVolume(40);
	sf::SoundBuffer birdhitbuff;
	birdhitbuff.loadFromFile("music/birdhit.ogg");
	sf::Sound birdhit(birdhitbuff);
	sf::SoundBuffer birddestroyedbuff;
	birddestroyedbuff.loadFromFile("music/birddestroyed.ogg");
	sf::Sound birddestroyed(birddestroyedbuff);
	sf::SoundBuffer pigdamagebuff;
	pigdamagebuff.loadFromFile("music/pigdamage.ogg");
	sf::Sound pigdamage(pigdamagebuff);
	sf::SoundBuffer pigdestroyedbuff;
	pigdestroyedbuff.loadFromFile("music/pigdestroyed.ogg");
	sf::Sound pigdestroyed(pigdestroyedbuff);
	sf::SoundBuffer rockdamagebuff;
	rockdamagebuff.loadFromFile("music/rockdamage.ogg");
	sf::Sound rockdamage(rockdamagebuff);
	sf::SoundBuffer rockdestroyedbuff;
	rockdestroyedbuff.loadFromFile("music/rockdestroyed.ogg");
	sf::Sound rockdestroyed(rockdestroyedbuff);
	sf::SoundBuffer levelclearbuff;
	levelclearbuff.loadFromFile("music/levelclear.ogg");
	sf::Sound levelclear(levelclearbuff);
	sf::SoundBuffer levelfailedbuff;
	levelfailedbuff.loadFromFile("music/levelfailed.ogg");
	sf::Sound levelfailed(levelfailedbuff);
	sf::SoundBuffer yelboostbuff;
	yelboostbuff.loadFromFile("music/yelboost.ogg");
	sf::Sound yelboost(yelboostbuff);



	CreateGround();

	int bird_counter = 5;
	int zero_delta = 20;
	int birds_delta = 50;
	int height = 850;
	std::vector<b2Body*>birds_arr;
	for (int i = 1; i < bird_counter + 1; i++)
	{
		b2Body *bird_body = CreateBird(CX - birds_delta * i - zero_delta, height, 0, "red");
		world.DestroyBody(bird_body);
		if (i % 2 == 0)
		{
			b2Body *bird_body = CreateBird(CX - birds_delta * i - zero_delta, height, 0, "red");
		}
		else
		{
			b2Body *bird_body = CreateBird(CX - birds_delta * i - zero_delta, height, 0, "yel");
		}
		
		birds_arr.push_back(bird_body);
	}
	b2Body *bird_body = CreateBird(CX, CY, 1, "red");
	
	int pig_counter = 4;
	bird_body->SetGravityScale(0);
	CreateMap();
	

	sf::View gameView(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	float cam_scale = 1.5f;
	sf::Vector2f cen = gameView.getCenter();
	gameView.setCenter(cen + sf::Vector2f(WIDTH / 4, -HEIGHT / 4));
	gameView.zoom(cam_scale);
	window.setView(gameView);
	sf::View initialView = gameView;
	

	int cir_rad = 100;
	int rel_flag = 0;  //is bird relised or not 
	int acting_flag = 0; //are we using mouse on bird
	int rope_flag = 0; //do need we to draw ropes or not 
	int level_end_flag = 0;
	int swap_flag = 0;  //swaps to level_end_mode
	int cur_bird_flag = 0; //0 - red, 1 - yel
	int yelboostflag = 0;

	//for events handling
	float red_scale_acceleration = 7.5;
	float yel_scale_acceleration = 2.5;
	int exit_button_delta = 70;

	//for pre-start bird contoling
	int x_cam_delta = 80;
	int access_round_rad = 150;
	int min_x_rope_boundaries = -20;
	int max_x_rope_boundaries = 30;
	int min_y_rope_boundaries = 40;

	sf::Clock clock;
	sf::Time start_dest = sf::seconds(1.5);


	
	while (window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();
		if (time > start_dest)
		{
			dest_flag = 1;
		}

		//events handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					if (rel_flag == 0 && acting_flag == 1)
					{
						birdlaunch.play();
						bird_body->ApplyLinearImpulseToCenter(b2Vec2((CX - bird_body->GetPosition().x * SCALE) * red_scale_acceleration, (CY - bird_body->GetPosition().y * SCALE) * red_scale_acceleration), 1);
						rel_flag = 1;
						acting_flag = 0;
						rope_flag = 0;
					}
					else if (rel_flag == 1 && cur_bird_flag == 1 && yelboostflag == 0)
					{
						yelboostflag = 1;
						yelboost.play();
						bird_body->SetLinearVelocity(b2Vec2(bird_body->GetLinearVelocity().x * yel_scale_acceleration, bird_body->GetLinearVelocity().y * yel_scale_acceleration));
						bird_body->SetGravityScale(0);
					}
					
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					if (sf::Mouse::getPosition(window).x < exit_button_delta && sf::Mouse::getPosition(window).y > HEIGHT - exit_button_delta)
					{
						window.close();
					}
				}
			}
		}


		//pre-start bird controllers
		b2Vec2 vel = bird_body->GetLinearVelocity();
		float angVel = bird_body->GetAngularVelocity();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			int cr_pos_x = ((int)sf::Mouse::getPosition(window).x + WIDTH / 4) / cam_scale - x_cam_delta;
			int cr_pos_y = ((int)sf::Mouse::getPosition(window).y + HEIGHT / 4) / cam_scale;
			if (((abs(cr_pos_x - CX) < access_round_rad && abs(cr_pos_y - CY) < access_round_rad) || (acting_flag == 1)) && (rel_flag == 0))
			{
				rope_flag = 1;
				int len = 0;
				float deq = 0;
				acting_flag = 1;


				if (abs(cr_pos_x - CX) > cir_rad || abs(cr_pos_y - CY) > cir_rad)
				{
					len = sqrt(pow(cr_pos_x - CX, 2) + pow(cr_pos_y - CY, 2));
					deq = cir_rad / len;
					if (cr_pos_x > CX)
					{
						cr_pos_x = CX + (cir_rad * (cr_pos_x - CX)) / len;
					}
					else
					{
						cr_pos_x = CX - (cir_rad * (CX - cr_pos_x)) / len;
					}

					if (cr_pos_y > CY)
					{
						cr_pos_y = CY + (cir_rad * (cr_pos_y - CY)) / len;
					}
					else
					{
						cr_pos_y = CY - (cir_rad * (CY - cr_pos_y)) / len;
					}



				}
				if ((cr_pos_x > CX + min_x_rope_boundaries) && (cr_pos_x < CX + max_x_rope_boundaries) && (cr_pos_y > CY + min_y_rope_boundaries))
				{
					cr_pos_y = CY + min_y_rope_boundaries;
				}
				world.DestroyBody(bird_body);
				if (cur_bird_flag == 0)
				{
					bird_body = CreateBird(cr_pos_x, cr_pos_y, 1, "red");
				}
				else if (cur_bird_flag == 1)
				{
					bird_body = CreateBird(cr_pos_x, cr_pos_y, 1, "yel");
				}
			}
		}
		
		
		//bird destruction handling
		float vel_min_limit = 0.4;
		if (bird_counter >= 0)
		{
			b2Vec2 veloc = bird_body->GetLinearVelocity();
			if ((abs(veloc.x) < vel_min_limit / SCALE) && (abs(veloc.y) < vel_min_limit / SCALE) && (rel_flag == 1))
			{
				world.DestroyBody(bird_body);
				yelboostflag = 0;
				if (bird_counter > 0)
				{
					if (birds_arr[bird_counter - 1]->GetUserData() == "notredbird")
					{
						cur_bird_flag = 0;
					}
					else if (birds_arr[bird_counter - 1]->GetUserData() == "notyelbird")
					{
						cur_bird_flag = 1;
					}
					world.DestroyBody(birds_arr[bird_counter - 1]);
				}
				bird_counter--;
				birddestroyed.play();
				if (cur_bird_flag == 0)
				{
					bird_body = CreateBird(CX, CY, 1, "red");
				}
				else if (cur_bird_flag == 1)
				{
					bird_body = CreateBird(CX, CY, 1, "yel");
				}

				bird_body->SetGravityScale(0);
				rel_flag = 0;
			}
			b2Vec2 pos = bird_body->GetPosition();
			if ((pos.x * SCALE) > 1.5 * WIDTH || (pos.x * SCALE < 0))
			{
				yelboostflag = 0;
				world.DestroyBody(bird_body);
				if (bird_counter > 0)
				{
					if (birds_arr[bird_counter - 1]->GetUserData() == "notredbird")
					{
						cur_bird_flag = 0;
					}
					else if (birds_arr[bird_counter - 1]->GetUserData() == "notyelbird")
					{
						cur_bird_flag = 1;
					}
					world.DestroyBody(birds_arr[bird_counter - 1]);

				}
				bird_counter--;
				birddestroyed.play();

				if (cur_bird_flag == 0)
				{
					bird_body = CreateBird(CX, CY, 1, "red");
				}
				else if (cur_bird_flag == 1)
				{
					bird_body = CreateBird(CX, CY, 1, "yel");
				}
				bird_body->SetGravityScale(0);
				rel_flag = 0;


			}
		}
		else if (bird_counter < 0)
		{
			world.DestroyBody(bird_body);
			bird_body = CreateBird(-100, 0, 1, "red");
		}


		//breaking and destruction for all objects
		DestroyObjects(woodhit, icehit, icedie, wooddie, pigdamage, pigdestroyed, rockdamage, rockdestroyed, birdhit, &pig_counter, bird_body);
		toDie.clear();


		//checking if we need to end the level
		if (bird_counter == -1 && swap_flag == 0)
		{
			swap_flag = 1;
			levelfailed.play();
			level_end_flag = 1;
		}
		if (level_end_flag == 1 && levelfailed.getStatus() == 0 && levelclear.getStatus() == 0)
		{
			window.close();
		}

		if (pig_counter == 0 && swap_flag == 0)
		{
			swap_flag = 1;
			levelclear.play();
			level_end_flag = 1;
		}
		if (level_end_flag == 1 && levelclear.getStatus() == 0 && levelfailed.getStatus() == 0)
		{
			window.close();
		}


		//drawing
		world.Step(1/60.f, 8, 3);
		window.clear();
		window.draw(backgroundSprite1);
		window.draw(backgroundSprite2);
		window.draw(skySprite1);
		window.draw(skySprite2);
		window.draw(right_catapult);

		sf::Vertex point2(sf::Vector2f(100, 100));
		if (cur_bird_flag == 0)
		{
			point2.position = sf::Vector2f(redbirdSprite.getPosition().x, redbirdSprite.getPosition().y);
		}
		else if (cur_bird_flag == 1)
		{
			point2.position = sf::Vector2f(yelbirdSprite.getPosition().x, yelbirdSprite.getPosition().y);
		}

		DrawRope(rope_flag, bird_counter, point2, window, CX, CY, 18, -13);
		
		DrawSprites(window, redbirdSprite, notredbirdSprite, yelbirdSprite, notyelbirdSprite, pigSprite2, pigSprite1, block_woodhorzsmal3, block_woodhorzsmal2, block_woodhorzsmal1,
			block_icedhorzlong3, block_icedhorzlong2, block_icedhorzlong1, box_ston3, box_ston2, box_ston1);

		DrawRope(rope_flag, bird_counter, point2, window, CX, CY, -25, -18);

		window.draw(left_catapult);
		window.draw(exit_button);
		window.display();
	}
		
		

	return 0;
}






void CreateGround()
{
	b2PolygonShape groundShape;
	groundShape.SetAsBox(WIDTH / SCALE, 70 / SCALE);
	b2FixtureDef fd;
	fd.shape = &groundShape;
	fd.friction = 0.75f;
	fd.density = 1;
	b2BodyDef grBodydef;
	grBodydef.position.Set(WIDTH / SCALE, 1010 / SCALE);
	b2Body *ground_body = world.CreateBody(&grBodydef);
	ground_body->CreateFixture(&fd);
	ground_body->SetUserData((void*)"ground");
}

b2Body* CreateBird(int x, int y, int real_flag, const char* colour)
{
	b2CircleShape cShape;
	if (strcmp(colour, "red") == 0)
	{
		cShape.m_radius = 16 / SCALE;
	}
	else if (strcmp(colour, "yel") == 0)
	{
		cShape.m_radius = 19 / SCALE;
	}

	b2FixtureDef fd;
	fd.shape = &cShape;
	fd.friction = 0.9f;
	fd.density = 26;
	b2BodyDef birdBodydef;
	birdBodydef.type = b2_dynamicBody;
	birdBodydef.position.Set(x / SCALE, y / SCALE);
	b2Body *bird_body = world.CreateBody(&birdBodydef);
	bird_body->CreateFixture(&fd);
	if (real_flag == 1 && strcmp(colour, "red") == 0)
	{
		bird_body->SetUserData((void*)("redbird"));
	}
	else if (real_flag == 0 && strcmp(colour, "red") == 0)
	{
		bird_body->SetUserData((void*)("notredbird"));
	}
	else if (real_flag == 1 && strcmp(colour, "yel") == 0)
	{
		bird_body->SetUserData((void*)("yelbird"));
	}
	else if (real_flag == 0 && strcmp(colour, "yel") == 0)
	{
		bird_body->SetUserData((void*)("notyelbird"));
	}

	bird_body->SetAngularDamping(2.f);
	return bird_body;
}

void CreatePig(int x, int y)
{
	b2CircleShape cShape;
	cShape.m_radius = 21 / SCALE;
	b2FixtureDef fd;
	fd.shape = &cShape;
	fd.friction = 0.9f;
	fd.density = 7;
	b2BodyDef pigBodydef;
	pigBodydef.type = b2_dynamicBody;
	pigBodydef.position.Set(x / SCALE, y / SCALE);
	b2Body *pig_body = world.CreateBody(&pigBodydef);
	pig_body->CreateFixture(&fd);
	pig_body->SetUserData((void*)("pig2"));
	pig_body->SetAngularDamping(2.f);
}

void CreateBox(int center_x, int center_y)
{
	b2PolygonShape boxShape;
	boxShape.SetAsBox(42 / SCALE, 42 / SCALE);
	b2FixtureDef fd;
	fd.shape = &boxShape;
	fd.friction = 0.4f;
	fd.density = 10;
	b2BodyDef boxBodydef;
	boxBodydef.type = b2_dynamicBody;
	boxBodydef.position.Set(center_x / SCALE, center_y / SCALE);
	b2Body *box_body = world.CreateBody(&boxBodydef);
	box_body->CreateFixture(&fd);
	box_body->SetUserData((void*)"box3");

}

void CreateBlock(int center_x, int center_y, const char* material, const char* orientation, const char* size)
{
	b2PolygonShape blockShape;
	if (strcmp(size, "smal") == 0)
	{
		if (strcmp(orientation, "vert") == 0)
		{
			blockShape.SetAsBox(21 / SCALE, 42 / SCALE);
		}
		else
		{
			blockShape.SetAsBox(42 / SCALE, 21 / SCALE);
		}

	}
	else
	{
		if (strcmp(orientation, "vert") == 0)
		{
			blockShape.SetAsBox(11 / SCALE, 103 / SCALE);
		}
		else
		{
			blockShape.SetAsBox(103 / SCALE, 11 / SCALE);
		}
	}

	b2FixtureDef fd;
	fd.shape = &blockShape;
	fd.friction = 0.4f;
	fd.density = 8;
	b2BodyDef block1Bodydef;
	block1Bodydef.type = b2_dynamicBody;
	block1Bodydef.position.Set(center_x / SCALE, center_y / SCALE);
	b2Body *block1_body = world.CreateBody(&block1Bodydef);
	block1_body->CreateFixture(&fd);
	if (strcmp(material, "wood") == 0)
	{
		if (strcmp(orientation, "vert") == 0)
		{
			if (strcmp(size, "smal") == 0)
			{
				block1_body->SetUserData((void*)"woodvertsmal3");
			}
			else
			{
				block1_body->SetUserData((void*)"woodvertlong");
			}
		}
		else
		{
			if (strcmp(size, "smal") == 0)
			{
				block1_body->SetUserData((void*)"woodhorzsmal");
			}
			else
			{
				block1_body->SetUserData((void*)"woodhorzlong");
			}
		}
	}
	else if (strcmp(material, "iced") == 0)
	{
		if (strcmp(orientation, "vert") == 0)
		{
			if (strcmp(size, "smal") == 0)
			{
				block1_body->SetUserData((void*)"icedvertsmal");
			}
			else
			{
				block1_body->SetUserData((void*)"icedvertlong");
			}
		}
		else
		{
			if (strcmp(size, "smal") == 0)
			{
				block1_body->SetUserData((void*)"icedhorzsmal");
			}
			else
			{
				block1_body->SetUserData((void*)"icedhorzlong3");
			}
		}
	}
}

void CreateMap()
{
	CreateBox(1600, 850);
	CreateBox(1685, 850);
	CreateBox(1800, 850);
	CreateBox(1885, 850);
	CreateBox(2000, 850);
	CreateBox(2085, 850);

	CreateBlock(1600, 760, "wood", "vert", "smal");
	CreateBlock(1800, 760, "wood", "vert", "smal");
	CreateBlock(1885, 760, "wood", "vert", "smal");
	CreateBlock(2085, 760, "wood", "vert", "smal");

	CreateBlock(1700, 700, "iced", "horz", "long");
	CreateBlock(1985, 700, "iced", "horz", "long");

	CreateBox(1640, 620);
	CreateBox(1640, 510);
	CreateBox(2045, 620);
	CreateBox(2045, 510);

	CreateBlock(1750, 620, "wood", "vert", "smal");
	CreateBlock(1930, 620, "wood", "vert", "smal");
	CreateBlock(1840, 560, "iced", "horz", "long");

	CreateBlock(1619, 420, "wood", "vert", "smal");
	CreateBlock(1661, 420, "wood", "vert", "smal");
	CreateBlock(1619, 330, "wood", "vert", "smal");
	CreateBlock(1661, 330, "wood", "vert", "smal");

	CreateBlock(2024, 420, "wood", "vert", "smal");
	CreateBlock(2066, 420, "wood", "vert", "smal");
	CreateBlock(2024, 330, "wood", "vert", "smal");
	CreateBlock(2066, 330, "wood", "vert", "smal");

	CreateBlock(1640, 280, "iced", "horz", "long");
	CreateBlock(2045, 280, "iced", "horz", "long");

	CreateBlock(1590, 230, "wood", "vert", "smal");
	CreateBlock(1690, 230, "wood", "vert", "smal");
	CreateBlock(1995, 230, "wood", "vert", "smal");
	CreateBlock(2095, 230, "wood", "vert", "smal");

	CreateBox(2300, 850);

	CreatePig(2300, 780);
	CreatePig(1640, 240);
	CreatePig(1840, 590);
	CreatePig(1680, 760);
}



void DrawSprites(sf::RenderWindow& window, sf::Sprite& redbirdSprite, sf::Sprite notredbirdSprite, sf::Sprite& yelbirdSprite, sf::Sprite notyelbirdSprite,
	sf::Sprite pigSprite2, sf::Sprite pigSprite1, sf::Sprite block_woodhorzsmal3, sf::Sprite block_woodhorzsmal2, sf::Sprite block_woodhorzsmal1,
	sf::Sprite block_icedhorzlong3, sf::Sprite block_icedhorzlong2, sf::Sprite block_icedhorzlong1, sf::Sprite box_ston3, sf::Sprite box_ston2, sf::Sprite box_ston1)
{
	for (b2Body* it = world.GetBodyList(); it != 0; it = it->GetNext())
	{
		if (it->GetUserData() == "redbird")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			redbirdSprite.setPosition(position.x * SCALE, position.y * SCALE);
			redbirdSprite.setRotation(angle * DEG);
			window.draw(redbirdSprite);
		}
		else if (it->GetUserData() == "notredbird")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			notredbirdSprite.setPosition(position.x * SCALE, position.y * SCALE);
			notredbirdSprite.setRotation(angle * DEG);
			window.draw(notredbirdSprite);
		}
		else if (it->GetUserData() == "yelbird")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			yelbirdSprite.setPosition(position.x * SCALE, position.y * SCALE);
			yelbirdSprite.setRotation(angle * DEG);
			window.draw(yelbirdSprite);
		}
		else if (it->GetUserData() == "notyelbird")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			notyelbirdSprite.setPosition(position.x * SCALE, position.y * SCALE);
			notyelbirdSprite.setRotation(angle * DEG);
			window.draw(notyelbirdSprite);
		}
		else if (it->GetUserData() == "pig2")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			pigSprite2.setPosition(position.x * SCALE, position.y * SCALE);
			pigSprite2.setRotation(angle * DEG);
			window.draw(pigSprite2);
		}
		else if (it->GetUserData() == "pig1")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			pigSprite1.setPosition(position.x * SCALE, position.y * SCALE);
			pigSprite1.setRotation(angle * DEG);
			window.draw(pigSprite1);
		}
		else if (it->GetUserData() == "woodvertsmal3")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			block_woodhorzsmal3.setPosition(position.x * SCALE, position.y * SCALE);
			block_woodhorzsmal3.setRotation((angle + 1.57) * DEG);
			window.draw(block_woodhorzsmal3);
		}
		else if (it->GetUserData() == "woodvertsmal2")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			block_woodhorzsmal2.setPosition(position.x * SCALE, position.y * SCALE);
			block_woodhorzsmal2.setRotation((angle + 1.57) * DEG);
			window.draw(block_woodhorzsmal2);
		}
		else if (it->GetUserData() == "woodvertsmal1")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			block_woodhorzsmal1.setPosition(position.x * SCALE, position.y * SCALE);
			block_woodhorzsmal1.setRotation((angle + 1.57) * DEG);
			window.draw(block_woodhorzsmal1);
		}
		else if (it->GetUserData() == "icedhorzlong3")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			block_icedhorzlong3.setPosition(position.x * SCALE, position.y * SCALE);
			block_icedhorzlong3.setRotation(angle * DEG);
			window.draw(block_icedhorzlong3);
		}
		else if (it->GetUserData() == "icedhorzlong2")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			block_icedhorzlong2.setPosition(position.x * SCALE, position.y * SCALE);
			block_icedhorzlong2.setRotation(angle * DEG);
			window.draw(block_icedhorzlong2);

		}
		else if (it->GetUserData() == "icedhorzlong1")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			block_icedhorzlong1.setPosition(position.x * SCALE, position.y * SCALE);
			block_icedhorzlong1.setRotation(angle * DEG);
			window.draw(block_icedhorzlong1);
		}
		else if (it->GetUserData() == "box3")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			box_ston3.setPosition(position.x * SCALE, position.y * SCALE);
			box_ston3.setRotation(angle * DEG);
			window.draw(box_ston3);
		}
		else if (it->GetUserData() == "box2")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			box_ston2.setPosition(position.x * SCALE, position.y * SCALE);
			box_ston2.setRotation(angle * DEG);
			window.draw(box_ston2);
		}
		else if (it->GetUserData() == "box1")
		{
			b2Vec2 position = it->GetPosition();
			float angle = it->GetAngle();
			box_ston1.setPosition(position.x * SCALE, position.y * SCALE);
			box_ston1.setRotation(angle * DEG);
			window.draw(box_ston1);
		}
	}
}

void DrawRope(int rope_flag, int bird_counter, sf::Vertex point2, sf::RenderWindow& window, int CX, int CY, int delta_x, int delta_y)
{
	if (rope_flag == 1 && bird_counter != -1)
	{
		sf::Vertex line3[] =
		{
			sf::Vertex(sf::Vector2f(CX + delta_x, CY + delta_y)),
			point2
		};
		line3[0].color = sf::Color(0x83, 0x4D, 0x18);
		line3[1].color = sf::Color(0x83, 0x4D, 0x18);
		sf::Vertex line4[] =
		{
			sf::Vertex(sf::Vector2f(CX + 18, CY + 7)),
			point2
		};
		line4[0].color = sf::Color(0x83, 0x4D, 0x18);
		line4[1].color = sf::Color(0x83, 0x4D, 0x18);
		window.draw(line3, 2, sf::Lines);
		window.draw(line4, 2, sf::Lines);
	}
}

void DestroyObjects(sf::Sound& woodhit, sf::Sound& icehit, sf::Sound& icedie, sf::Sound& wooddie, sf::Sound& pigdamage, sf::Sound& pigdestroyed,
	sf::Sound& rockdamage, sf::Sound& rockdestroyed, sf::Sound& birdhit, int* pig_counter, b2Body* bird_body)
{
	for (int i = 0; i < toDie.size(); i++)
	{
		if (toDie[i]->GetUserData() != "redbird" && toDie[i]->GetUserData() != "ground" && toDie[i]->GetUserData() != "yelbird")
		{
			if (toDie[i]->GetUserData() == "woodvertsmal3")
			{
				woodhit.play();
				toDie[i]->SetUserData((void*)"woodvertsmal2");
			}
			else if (toDie[i]->GetUserData() == "woodvertsmal2")
			{
				woodhit.play();
				toDie[i]->SetUserData((void*)"woodvertsmal1");
			}
			else if (toDie[i]->GetUserData() == "icedhorzlong3")
			{
				icehit.play();
				toDie[i]->SetUserData((void*)"icedhorzlong2");
			}
			else if (toDie[i]->GetUserData() == "icedhorzlong2")
			{
				icehit.play();
				toDie[i]->SetUserData((void*)"icedhorzlong1");
			}
			else if (toDie[i]->GetUserData() == "icedhorzlong1")
			{
				icedie.play();
				world.DestroyBody(toDie[i]);
			}
			else if (toDie[i]->GetUserData() == "woodvertsmal1")
			{
				wooddie.play();
				world.DestroyBody(toDie[i]);
			}
			else if (toDie[i]->GetUserData() == "pig2")
			{
				pigdamage.play();
				toDie[i]->SetUserData((void*)"pig1");
			}
			else if (toDie[i]->GetUserData() == "pig1")
			{
				pig_counter--;
				pigdestroyed.play();
				world.DestroyBody(toDie[i]);
			}
			else if (toDie[i]->GetUserData() == "box3")
			{
				rockdamage.play();
				toDie[i]->SetUserData((void*)"box2");
			}
			else if (toDie[i]->GetUserData() == "box2")
			{
				rockdamage.play();
				toDie[i]->SetUserData((void*)"box1");
			}
			else if (toDie[i]->GetUserData() == "box1")
			{
				rockdestroyed.play();
				world.DestroyBody(toDie[i]);
			}
			else
			{
				world.DestroyBody(toDie[i]);
			}

		}
		else if (toDie[i]->GetUserData() == "redbird")
		{
			birdhit.play();
		}
		else if (toDie[i]->GetUserData() == "yelbird")
		{
			bird_body->SetGravityScale(1);
			birdhit.play();
		}

	}
}

