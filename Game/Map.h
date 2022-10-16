#pragma once

#include "Utilities.h"
#include "SharedContext.h"
#include "BaseState.h"

namespace Mac {

	enum Sheet
	{
			Tile_Size = 32
		,	Sheet_Width = 256
		,	Sheet_Height = 256
	};

	using TileID = unsigned;

	struct TileInfo
	{
		TileInfo(
				SharedContext* l_context
			,	const std::string& l_texture = ""
			,	TileID l_id = 0
		)
			:	m_context(l_context)
			,	m_ID(0)
			,	m_deadly(false)

		{
		}

		~TileInfo()
		{
			if (m_texture == "")
				return;

			m_context->m_textureManager->ReleaseResource(m_texture);
		}

		sf::Sprite m_sprite;

		TileID m_ID;
		std::string m_name;
		sf::Vector2f m_friction;
		bool m_deadly;

		SharedContext* m_context;
		std::string m_texture;
	};

	struct Tile
	{
		TileInfo* m_properties;
		bool m_warp;
	};

	using TileMap = std::unordered_map<TileID, Tile*>;
	using TileSet = std::unordered_map<TileID, TileInfo*>;


	struct Map
	{
		Map(SharedContext* l_context, BaseState* l_currentState);
		~Map();

		Tile* GetTile(unsigned l_X, unsigned l_Y);
		TileInfo* GetDefaultTile();

		float GetGravity() const;
		unsigned GetTileSize() const;
		const sf::Vector2u& GetMapSize() const;
		const sf::Vector2f& GetPlayerStart() const;

		void LoadMap(const std::string& l_path);
		void LoadNext();

		void Update(float l_deltaTime);
		void Draw();
	private:
		unsigned ConvertCoords(unsigned l_X, unsigned l_Y);
		void LoadTiles(const std::string& l_path);
		void PurgeMap();
		void PurgeTileSet();

		TileSet m_tileSet;
		TileMap m_tileMap;
		sf::Sprite m_background;
		TileInfo m_defaultTile;
		sf::Vector2u m_maxMapSize;
		sf::Vector2f m_playerStart;
		unsigned m_tileCount;
		unsigned m_tileSetCount;
		float m_mapGravity;
		std::string m_nextMap;
		bool m_loadNextMap;
		std::string m_backgroundTexture;
		BaseState* m_currentState;
		SharedContext* m_context;
	};
}