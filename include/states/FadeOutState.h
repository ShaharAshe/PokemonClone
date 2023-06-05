#pragma once

#include "BaseState.h"


class FadeOutState :public BaseState
{
public:
	FadeOutState(Stack<BaseState>& states,sf::Color color)
		: BaseState(states)
	{
		m_fadeShape.setSize(sf::Vector2f(getWindowSize()));
		m_fadeShape.setFillColor(color);
	}

	~FadeOutState() = default;
	
	void entry() override {}
	void exit() override {}
	
	void update(sf::Time dt)
	override {
		 sf::Time decrement = 255.0f / 1.0f * dt; // Adjust the fade-out speed as needed

		 m_progress -= static_cast<sf::Uint8>(decrement.asSeconds());

		 if (m_progress <= 0)
		 {
			 m_progress = 0;
			 setStatus(false); // Set the status to false to indicate that the fade-out is complete
		 }	
	 }
	
	void handleEvents(sf::Event event) override {}
	void draw(sf::RenderWindow& window) override
	{
		window.draw(m_fadeShape);
	}

private:	
	sf::RectangleShape m_fadeShape;
	sf::Uint8 m_progress {255};
};
