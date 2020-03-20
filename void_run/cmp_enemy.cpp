#include "cmp_enemy.h"
#include "cmp_entityinfo.h"
#include "VoidRun.h"
#include "Scene.h"
#include "ecm.h"
#include <string>
#include <iostream>

/*using namespace sf;
using namespace std;
std::vector<std::shared_ptr<EntityInfo>> enemyInfo;
std::vector<std::shared_ptr<EntityInfo>> playerInfo;

//bool playerTurn = true;
//Clock clock;

BaseEnemyComponent::BaseEnemyComponent(Entity* p)
	: enemyDamage(3.0f), Component(p) {}
	
int TEMP = 1;

void BaseEnemyComponent::update(double dt) {
	//float Time = Clock.GetElapsedTime();
	//Clock.Reset();

/*	do {
		if(playerTurn == false)
		{
			int enemyAI = rand() % 2; //Random number from 0-1. 0 is attack, 1 is pass.
			if (enemyAI == 0){
				cout << "The enemy attacks!";
				attackEnemy(enemyDamage);
				playerTurn = true;
			}
			else if (enemyAI == 1){
				cout << "The enemy passes its turn!";
				playerTurn = true;
			}
		}
	} while (TEMP == 1);
}

void BaseEnemyComponent::attackEnemy(float damage)
{
	playerInfo[0]->takeDamage(damage);
}*/