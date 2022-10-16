#pragma once

#include "TextureManager.h"
#include "Anim_Directional.h"

namespace Mac{

	using Animations = std::unordered_map<std::string, Anim_Base*>;

	struct SpriteSheet {
		SpriteSheet(TextureManager* l_textMgr);
		~SpriteSheet();

		void CropSprite(const sf::IntRect& l_rect);
		sf::Vector2i GetSpriteSize()const;
		sf::Vector2f GetSpritePosition()const;
		void SetSpriteSize(const sf::Vector2i& l_size);
		void SetSpritePosition(const sf::Vector2f& l_pos);

		void SetDirection(const Direction& l_dir);
		Direction GetDirection()const;

		bool LoadSheet(const std::string& l_file);
		void ReleaseSheet();

		Anim_Base* GetCurrentAnim();
		bool SetAnimation(const std::string& l_name,
			const bool& l_play = false,
			const bool& l_loop = false);

		void Update(const float& l_deltaTime);
		void Draw(sf::RenderWindow* l_window);
	private:
		std::string m_texture;
		sf::Sprite m_sprite;
		sf::Vector2i m_spriteSize;
		sf::Vector2f m_spriteScale;
		Direction m_direction;

		std::string m_animType;
		Animations m_animations;
		Anim_Base* m_animationCurrent;

		TextureManager* m_textureManager;
	};

}