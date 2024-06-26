#pragma once

#include "BaseState.h"
#include "Resources.h"
#include "entity/Player.h"
#include "guis/Gui.h"


class PokemonMenuState :public BaseState
{
public:
	PokemonMenuState(Stack<BaseState>& states,
					 std::shared_ptr<Player> player,
					 sf::Vector2f cameraCenter)
		: BaseState(states),
		  m_player(player),
		  m_cameraCenter(cameraCenter),
		  m_front(m_player->getStarterPokemon()->getFrontSprite())
	{
		SoundTon::getInstance().stopSound(soundNames::MENU_THEME);
		SoundTon::getInstance().playSound(soundNames::POKEMON);
		
		entry();
	}
	
	virtual ~PokemonMenuState()
	{
		SoundTon::getInstance().stopSound(soundNames::POKEMON);
		SoundTon::getInstance().playSound(soundNames::MENU_THEME);
	}

	void entry()
	{
		sf::Vector2f buttonSize = sf::Vector2f(m_windowSize.x, m_windowSize.y);
		sf::Font& font = Resources::getInstance().getFont();
		
		m_main = std::move(std::make_unique<Gui>(font, buttonSize, sf::Vector2f(m_cameraCenter.x - m_windowSize.x / 2, m_cameraCenter.y - m_windowSize.y / 2)));
		
		buttonSize = sf::Vector2f(300, 50);
		
		m_life = std::move(std::make_unique<Gui>(font, buttonSize, sf::Vector2f(m_cameraCenter.x, m_cameraCenter.y - m_windowSize.y / 2)));
		
		m_life->addProgressBar(m_life->getPosition().x - 10, m_life->getPosition().y - 10, buttonSize.x, buttonSize.y, sf::Color::Black, sf::Color::Green, m_player->getStarterPokemon()->getHpPercent());
		
		m_exp = std::move(std::make_unique<Gui>(font, buttonSize, sf::Vector2f(m_cameraCenter.x, m_cameraCenter.y - m_windowSize.y / 2 + 100)));
		
		m_exp->addProgressBar(m_exp->getPosition().x - 10, m_exp->getPosition().y - 10, buttonSize.x, buttonSize.y, sf::Color::Black, sf::Color::Blue, m_player->getStarterPokemon()->getCurrentExpPercent());
		
		setText();

		m_front.setPosition(m_cameraCenter.x, m_cameraCenter.y);
		m_front.setScale(sf::Vector2f(2.0f, 2.0f));
	}
	
	void setText()
	{
		m_main->setResetColor();
		std::ostringstream textStream;
		
		// { HPIncrease, attackIncrease, defenseIncrease, speedIncrease };
		textStream << "Level:" << m_player->getStarterPokemon()->getLevel() << "\n";
		
		textStream << "Current Hp:" << m_player->getStarterPokemon()->getCurrentHP() << "\n";
		
		textStream << "Hp:" << m_player->getStarterPokemon()->getHP() << "\n";
		
		textStream << "Attack:" << m_player->getStarterPokemon()->getAttack() << "\n";
		
		textStream << "Defense:" << m_player->getStarterPokemon()->getDefense() << "\n";
		
		textStream << "Speed:" << m_player->getStarterPokemon()->getSpeed() << "\n";
		
		textStream << "Exp for next level:" << m_player->getStarterPokemon()->getExpToLevel() - m_player->getStarterPokemon()->getCurrentExp() << "\n";
		
		textStream << "Current Exp:" << m_player->getStarterPokemon()->getCurrentExp() << "\n";
		
		textStream << "Speed:" << m_player->getStarterPokemon()->getSpeed() << "\n";
		
		textStream << "\n Press M again to go back to the Menu" << "\n";
		m_main->setText(textStream.str());
	}

	void exit() {}

	void update(sf::Time dt) {}

	void handleEvents(sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::M ||
				event.key.code == sf::Keyboard::Escape)
			{
				SoundTon::getInstance().playSound(soundNames::CLICK);
				setStatus(false);
			}
		}
	}
	
	void draw(sf::RenderWindow& window)
	{
		m_main->draw(window);
		m_life->draw(window);
		m_exp->draw(window);
		
		window.draw(m_front);
	}

private:
	std::shared_ptr<Player> m_player;

	sf::Sprite& m_front;
	sf::Vector2f m_cameraCenter;
	std::unique_ptr<Gui> m_main;
	std::unique_ptr<Gui> m_life;
	std::unique_ptr<Gui> m_exp;

	sf::Vector2i m_windowSize{ Resources::getInstance().getWindow().getSize() };
};
