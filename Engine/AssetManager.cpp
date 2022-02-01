#include "AssetManager.h"

AssetManager& AssetManager::get_instance()
{
	static AssetManager instance;
	return instance;
}

void AssetManager::AddSprite(std::string name, GLib::Sprite* pSprite)
{
	m_sprites[name] = pSprite;
}

GLib::Sprite* AssetManager::FindSprite(std::string name)
{
	std::map<std::string, GLib::Sprite*>::iterator iter = m_sprites.find(name);

	if (iter != m_sprites.end())
	{
		return iter->second;
	}
	else return nullptr;
}

bool AssetManager::DeleteSprite(std::string name)
{
	std::map<std::string, GLib::Sprite*>::iterator iter = m_sprites.find(name);

	if (iter != m_sprites.end())
	{
		m_sprites.erase(iter);
		return true;
	}
	else return false;
}
