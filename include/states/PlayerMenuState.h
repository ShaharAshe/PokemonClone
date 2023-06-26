#pragma once
#include "BaseState.h"
#include "guis/Gui.h"

class PlayState;

enum PlayerMenuOptions
{
	Pokemons,
	SaveGame,
	QuitGame

};
const int PlayerMenuSize = 3;
std::optional<PlayerMenuOptions> operator++(std::optional<PlayerMenuOptions> option)
{
	if (option)
	{
		*option = static_cast<PlayerMenuOptions>((static_cast<int>(*option) + 1) % PlayerMenuSize);
	}

	return option;
}

std::optional<PlayerMenuOptions> operator--(std::optional<PlayerMenuOptions> option)
{
	if (option)
	{
		int value = static_cast<int>(*option) - 1;
		if (value < 0)
			value = PlayerMenuSize - 1;
		*option = static_cast<PlayerMenuOptions>(value);
	}
	return option;
}


class PlayerMenuState : public BaseState
{
public:
	PlayerMenuState(Stack<BaseState>& states,PlayState& state,sf::Vector2f cameraCenter): BaseState(states),
		m_playState(state),m_cameraCenter(cameraCenter) { 
		entry();
	};
	~PlayerMenuState() {};


	 void entry(){
		 
		 sf::Vector2f buttonSize = sf::Vector2f(m_windowSize.x / 3, m_windowSize.y / 3);
		// float x = (static_cast<float>(m_cameraCenter.x ) - (buttonSize.x / 2));

		 for (size_t i = 0; i < PlayerMenuSize; i++)
		 {
			 m_menuSelection[i] = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), buttonSize,
																  sf::Vector2f(m_cameraCenter.x+m_windowSize.x/2-buttonSize.x,m_cameraCenter.y-m_windowSize.y/2+50*i)));
		 }

		 resetText();
	 }
	 void resetText()
	 {
		 m_menuSelection[PlayerMenuOptions::Pokemons]->setText("Pokemons");
		 m_menuSelection[PlayerMenuOptions::SaveGame]->setText("SaveGame");
		 m_menuSelection[PlayerMenuOptions::QuitGame]->setText("QuitGame");
	 }
	 void exit(){
	 
	 }
	 void update(sf::Time dt){
		 PlayerMenuOptions option = m_hover.value();

		 for (int i = 0; i < PlayerMenuSize; i++)
		 {
			 if (i == option)
			 {
				 m_menuSelection[i]->setHoverColor();
			 }
			 else
			 {
				 m_menuSelection[i]->setResetColor();
			 }
		 }
		//if not null,switch case what to do
	 }
	 void handleEvents(sf::Event event){
		 if (event.type == sf::Event::KeyPressed)
		 {
			 if (event.key.code == sf::Keyboard::Enter)
			 {
				 m_selection = m_hover;
			 }
			 if (event.key.code == sf::Keyboard::Down)
			 {
				 m_hover = ++m_hover;
			 }
			 if (event.key.code == sf::Keyboard::Up)
			 {
				 m_hover = --m_hover;
			 }
			 if (event.key.code == sf::Keyboard::M)
			 {
				 setStatus(false);
			 }
			
		 }
	 }
	 void draw(sf::RenderWindow& window){
		 for (auto& gui : m_menuSelection)
		 {
			 gui->draw(window);
		 }
	 }
private:

	bool m_finish {false};
	
	std::array<std::unique_ptr<Gui>, PlayerMenuSize> m_menuSelection {};

	std::optional<PlayerMenuOptions> m_selection{ std::nullopt };
	std::optional<PlayerMenuOptions> m_hover{ Pokemons };
	
	PlayState& m_playState;

	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
	sf::Vector2f m_cameraCenter;
};

