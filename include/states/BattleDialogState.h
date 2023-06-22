#pragma once
#include "BaseState.h"
#include "../Resources.h"
#include <optional>
#include "guis/Gui.h"
const int BATTLE_OPTIONS = 2;
enum class BattleOptions
{
	Attack,
	Run
	//to be added
	
};
std::optional<BattleOptions> operator++(std::optional<BattleOptions> option)
{
	if (option)
	{
		*option = static_cast<BattleOptions>((static_cast<int>(*option) + 1) % BATTLE_OPTIONS);
	}

	return option;
}

std::optional<BattleOptions> operator--(std::optional<BattleOptions> option)
{
	if (option)
	{
		int value = static_cast<int>(*option) - 1;
		if (value < 0)
			value = BATTLE_OPTIONS - 1;
		*option = static_cast<BattleOptions>(value);
	}
	return option;
}

class BattleDialogState : public BaseState
{
public:
	BattleDialogState(Stack<BaseState>& states,sf::Vector2f position,sf::Vector2f size)
		: BaseState(states),m_position(position),m_size(size) {
		entry();
	}

	~BattleDialogState() = default;

	void entry() override {
		//Gui(const sf::Font & font, sf::Vector2f buttonSize, sf::Vector2f buttonPosition)
		m_position.x = m_position.x + (m_size.x / 2);
		m_size.x = m_size.x / 2;
		m_size.y = m_size.y / 2;

		for (int i = 0; i < BATTLE_OPTIONS; i++&&m_position.y+100)
		{
			m_menuSelection[i] = std::move(std::make_unique<Gui>(Resources::getInstance().getFont(), m_size, m_position));
		}
	
	}
	void exit() override {}
	void update(sf::Time dt) override {
		BattleOptions option = m_hover.value();

		for (int i = 0; i < BATTLE_OPTIONS; i++)
		{
			if (i == static_cast<int>(option))
			{
				m_menuSelection[i]->setHoverColor();
			}
			else
			{
				m_menuSelection[i]->setResetColor();
			}
		}
		if (m_choice != std::nullopt)
		{
			setStatus(false);
		}
	
	}
	void handleEvents(sf::Event event) override {
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				m_choice = m_hover;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				m_hover = ++m_hover;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				m_hover = --m_hover;
			}
		}
	}
	void draw(sf::RenderWindow& window) override {
	
		for (auto& gui: m_menuSelection)
		{
			gui->draw(window);
		}
	}

private:
	std::optional<BattleOptions> m_choice{ std::nullopt };
	std::optional<BattleOptions> m_hover {BattleOptions::Attack};

	sf::Vector2f m_position;
	sf::Vector2f m_size;

	std::array<std::unique_ptr<Gui>, BATTLE_OPTIONS> m_menuSelection {};
};
