#include "StatRoom.h"

StatRoom::StatRoom(std::shared_ptr<Entity> p)
	: Room(p) {};

void StatRoom::Update(const double& dt)
{

}

void StatRoom::Render()
{
	Renderer::queue(&stat1);
	Renderer::queue(&stat2);
	Renderer::queue(&stat3);
	Renderer::queue(&RewardsText);
//	Renderer::queue(&StrengthText);
	//Renderer::queue(&HealthText);
	Renderer::queue(&DexterityText);
}

void StatRoom::Load()
{
	Room::Load();
	if (!statUPTex.loadFromFile("res/Icons/Arrow.png"))
	{
		std::cout << "Couldnt load up arrow in stat room\n";
	}
	if (!font.loadFromFile("res/fonts/mandalore.ttf"))
	{
		std::cout << "Couldnt load mandalore font in statroom\n";
	}
	stat1.setTexture(statUPTex);
	stat2.setTexture(statUPTex);
	stat3.setTexture(statUPTex);
	stat1.setScale(0.3f, 0.3f);
	stat2.setScale(0.3f, 0.3f);
	stat3.setScale(0.3f, 0.3f);
	stat1.setRotation(90);
	stat2.setRotation(90);
	stat3.setRotation(90);
	stat1.setPosition(300.0f, 400.0f);
	stat2.setPosition(500.0f, 400.0f);
	stat3.setPosition(700.0f, 400.0f);

	RewardsText.setFont(font);
	StrengthText.setFont(font);
	HealthText.setFont(font);
	DexterityText.setFont(font);
	RewardsText.setCharacterSize(60);
	StrengthText.setCharacterSize(30);
	HealthText.setCharacterSize(30);
	DexterityText.setCharacterSize(30);
	RewardsText.setString("REWARDS");
	StrengthText.setString("Strength Up\n Current Strength - " + p->getStrength());
	HealthText.setString("Health Up\n Current Max Health - " + p->getMaxHealth());
	DexterityText.setString("Dexterity Up\n Current Dex - " + p->getDexterity());
	RewardsText.setPosition((Engine::getWindowSize().x / 2) - (RewardsText.getLocalBounds().width / 2), 100.0f);
	StrengthText.setPosition((Engine::getWindowSize().x / 4) - (StrengthText.getLocalBounds().width / 2), 300.0f);
	HealthText.setPosition(((Engine::getWindowSize().x / 4) * 2) - (HealthText.getLocalBounds().width / 2), 300.0f);
	DexterityText.setPosition(((Engine::getWindowSize().x / 34) * 3)- (DexterityText.getLocalBounds().width / 2), 300.0f);
}

