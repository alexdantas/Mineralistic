#include "Menu.h"
#include <SFML\Graphics\RenderTarget.hpp>
#include "AudioSystem.h"

Menu::Menu() :
mFont(),
mPos(0, 0),
mCurrentIndex(-1),
mColorItem(sf::Color::White),
mColorItemHilite(sf::Color(69, 130, 196)),
mAssets(nullptr)
{

}

Menu::~Menu()
{

}

void Menu::setFont(sf::Font font)
{
	mFont = font;
}

void Menu::setPosition(float x, float y)
{
	mPos = sf::Vector2f(x, y);
}

void Menu::addItem(std::string text, int id)
{
	MenuItem newItem;
	newItem.mID = id;

	newItem.mText.setFont(mFont);
	newItem.mText.setString(text);
	newItem.mText.setColor(mColorItem);
	newItem.mText.setCharacterSize(40);

	// Will pull down this item depending on how much
	// items this Menu already have
	sf::Vector2f newPosition;
	newPosition.x = mPos.x;
	newPosition.y = mPos.y + (mItem.size() * newItem.mText.getLocalBounds().height);
	newItem.mText.setPosition(newPosition);

	mItem.push_back(newItem);

	// Setting colors on the items if it's highlighted
	if (mCurrentIndex == -1)
	{
		mCurrentIndex = 0;
		mItem.at(mCurrentIndex).mText.setColor(mColorItemHilite);
	}
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto item : mItem)
	{
		target.draw(item.mText);
	}
}

void Menu::update(float dt, thor::ActionMap<std::string> *pActionMap)
{
	if (pActionMap->isActive("Menu_Next"))
	{
		next();
	}
	if (pActionMap->isActive("Menu_Previous"))
	{
		previous();
	}
	if (pActionMap->isActive("Menu_First"))
	{
		first();
	}
	if (pActionMap->isActive("Menu_Last"))
	{
		last();
	}
}

int Menu::getCurrentID()
{
	if (mCurrentIndex == -1)
	{
		// No items added until now
		return -1;
	}
	return mItem.at(mCurrentIndex).mID;
}
void Menu::next()
{
	if (mCurrentIndex >= mItem.size() - 1)
	{
		first();
		return;
	}
	changeCurrentIndex(mCurrentIndex + 1);
}
void Menu::previous()
{
	if (mCurrentIndex <= 0)
	{
		last();
		return;
	}
	changeCurrentIndex(mCurrentIndex - 1);
}
void Menu::first()
{
	changeCurrentIndex(0);
}
void Menu::last()
{
	changeCurrentIndex(mItem.size() - 1);
}

void Menu::changeCurrentIndex(int newValue)
{
	mItem.at(mCurrentIndex).mText.setColor(mColorItem);
	mCurrentIndex = newValue;
	mItem.at(mCurrentIndex).mText.setColor(mColorItemHilite);

	// Play it again, Sam!
	if (mAssets != nullptr)
	{
		mAssets->audioSystem->playSound("Menu_Item", false);
	}
}

void Menu::setAssets(GameStateAsset* asset)
{
	mAssets = asset;
}
