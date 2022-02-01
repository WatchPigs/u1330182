#pragma once
#include "GLib.h"
#include <map>
#include <string>

class AssetManager
{
public:
	static AssetManager& get_instance();
	void AddSprite(std::string name, GLib::Sprite* pSprite);
	GLib::Sprite* FindSprite(std::string name);
	bool DeleteSprite(std::string name);

private:
	AssetManager() = default;
	~AssetManager() = default;
	AssetManager(const AssetManager&) = delete;
	AssetManager(AssetManager&&) = delete;
	AssetManager& operator = (const AssetManager&) = delete;
	AssetManager& operator = (AssetManager&&) = delete;

	std::map<std::string, GLib::Sprite*> m_sprites;
};

