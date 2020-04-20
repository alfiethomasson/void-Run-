#include "LevelUpRoom.h"
#include "Game.h"
#include "system_renderer.h"
#include "cmp_entityinfo.h"
#include "cmp_player.h"
#include "cmp_sprite.h"
#include "VoidRun.h"

LevelUpRoom::LevelUpRoom(std::shared_ptr <Entity> p)
	: Room(p) {};

void LevelUpRoom::Load() {

	auto a = player->GetCompatibleComponent<BasePlayerComponent>();
	p = a[0];

}	

void LevelUpRoom::Update(const double& dt) {

}

void LevelUpRoom::Render() {
	for (auto& e : cells)
	{
		Renderer::queue(&e);
	}

	if (!choicePicked)
	{
		Renderer::queue(&ability1);
		Renderer::queue(&ability2);
		Renderer::queue(&ability1Text);
		Renderer::queue(&ability2Text);
	}
}