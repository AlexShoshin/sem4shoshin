#pragma once
#include <Box2D\Box2D.h>
#include <vector>

#define WITH_BIRD_IMPULSE 60
#define DEFAULT_IMPULSE 130
#define WITH_PIG_IMPULSE 40
#define STONE_IMPULSE 320
#define WOOD_IMPULSE 160


int dest_flag = 0;
std::vector<b2Body*> toDie;
class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact)
	{ /* handle begin event */
	}
	void EndContact(b2Contact* contact)
	{ /* handle end event */
	}
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		/* handle pre-solve event */
	}
	int dflag = 0;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		if (dest_flag == 1)
		{
			/* handle post-solve event */
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();
			if (((bodyA->GetUserData() == "redbird" || bodyB->GetUserData() == "redbird") && (impulse->normalImpulses[0] > WITH_BIRD_IMPULSE))
				|| ((bodyA->GetUserData() == "yelbird" || bodyB->GetUserData() == "yelbird") && (impulse->normalImpulses[0] > WITH_BIRD_IMPULSE))
				|| (impulse->normalImpulses[0] > DEFAULT_IMPULSE)
				|| ((bodyA->GetUserData() == "pig2" || bodyB->GetUserData() == "pig2" || bodyA->GetUserData() == "pig1" || bodyB->GetUserData() == "pig1") && (impulse->normalImpulses[0] > WITH_PIG_IMPULSE)))
			{
				for (int i = 0; i < toDie.size(); i++)
				{
					if (toDie[i] == bodyA)
					{
						dflag = 1;
						break;
					}
				}
				if (dflag == 0)
				{
					if ((bodyA->GetUserData() == "box3" || bodyA->GetUserData() == "box2" || bodyA->GetUserData() == "box1"))
					{
						if (impulse->normalImpulses[0] > STONE_IMPULSE)
						{
							toDie.push_back(bodyA);
						}
					}
					else if ((bodyA->GetUserData() == "woodvertsmal3" || bodyA->GetUserData() == "woodvertsmal2" || bodyA->GetUserData() == "woodvertsmal1"))
					{
						if (impulse->normalImpulses[0] > WOOD_IMPULSE)
						{
							toDie.push_back(bodyA);
						}
					}
					else
					{
						toDie.push_back(bodyA);
					}

				}
				dflag = 0;
				for (int i = 0; i < toDie.size(); i++)
				{
					if (toDie[i] == bodyB)
					{
						dflag = 1;
						break;
					}
				}
				if (dflag == 0)
				{
					if ((bodyB->GetUserData() == "box3" || bodyB->GetUserData() == "box2" || bodyB->GetUserData() == "box1"))
					{
						if (impulse->normalImpulses[0] > STONE_IMPULSE)
						{
							toDie.push_back(bodyB);
						}
					}
					else if ((bodyB->GetUserData() == "woodvertsmal3" || bodyB->GetUserData() == "woodvertsmal2" || bodyB->GetUserData() == "woodvertsmal1"))
					{
						if (impulse->normalImpulses[0] > WOOD_IMPULSE)
						{
							toDie.push_back(bodyB);
						}
					}
					else
					{
						toDie.push_back(bodyB);
					}
				}
				dflag = 0;
			}
		}
	}
};
