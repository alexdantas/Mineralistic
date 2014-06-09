#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include "ObjectManager.h"
#include "ObjectGroup.h"
#include "GameObject.h"
#include "World.h"
#include "Chunk.h"

WindowManager::WindowManager(std::string pTitle, sf::Vector2i pWindowSize)
{
	mWindow = new sf::RenderWindow(sf::VideoMode(pWindowSize.x, pWindowSize.y), pTitle);
	mWindow->setVerticalSyncEnabled(true);
}

WindowManager::~WindowManager()
{
	delete mWindow;
	mWindow = nullptr;
}

sf::RenderWindow *WindowManager::getWindow()
{
	return mWindow;
}

void WindowManager::drawObjectManager(ObjectManager *pObjectManager)
{
	// TODO: z-order
	for (auto &group : pObjectManager->getGroups())
	{
		for (auto &object : group->getObjects())
		{
			mWindow->draw(*object);
		}
	}

	for (auto &object : pObjectManager->getObjects())
	{
		mWindow->draw(*object);
	}
}

void WindowManager::drawWorld(World *pWorld)
{
	for (auto &chunk : pWorld->getLoadedChunks())
	{
		mWindow->draw(*chunk);
	}
}
