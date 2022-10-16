#pragma once

namespace Mac {

	enum class EntityType
	{
			Base
		,	Enemy
		,	Player
	};

	enum class EntityState
	{
			Idle
		,	Walking
		,	Jumping
		,	Attacking
		,	Hurt
		,	Dying
	};

	// Forward Declaration
	struct TileInfo;

	struct CollisionElement
	{
		CollisionElement(
				float l_area
			,	TileInfo* l_info
			,	const sf::FloatRect& l_bounds
		)
			:	m_area(l_area)
			,	m_tile(l_info)
			,	m_tileBounds(l_bounds)
		{
		}

		float m_area;
		TileInfo* m_tile;
		sf::FloatRect m_tileBounds;
	};

	using Collisions = std::vector<CollisionElement>;

	
	bool SortCollisions(
		const CollisionElement& l_1
	,	const CollisionElement& l_2
	);
	
	// Forward Declaration
	struct EntityManager;

	struct EntityBase
	{
		EntityBase(EntityManager* l_entityManager);
		virtual ~EntityBase() = default;

		const sf::Vector2f& GetPosition() const;
		const sf::Vector2f& GetSize() const;
		EntityState GetState() const;
		std::string GetName() const;
		unsigned int GetID() const;
		EntityType GetType() const;

		void SetPosition(float l_X, float l_Y);
		void SetPosition(const sf::Vector2f& l_position);
		void SetSize(float l_X, float l_Y);
		void SetState(const EntityState& l_state);

		void Move(float l_X, float l_Y);
		void AddVelocity(float l_X, float l_Y);
		void Accelerate(float l_X, float l_Y);
		void SetAcceleration(float l_X, float l_Y);
		void ApplyFriction(float l_X, float l_Y);

		virtual void Update(float l_deltaTime);

		// Draw not implemented here yet
		virtual void Draw(sf::RenderWindow* l_window) = 0;
	protected:
		void UpdateAABB();
		void CheckCollisions();
		void ResolveCollisions();

		// OnEntityCollision not implemented here yet
		virtual void OnEntityCollision(EntityBase* l_collider, bool l_attack) = 0;

		std::string m_name;
		EntityType m_type;
		unsigned m_ID;
		sf::Vector2f m_position;
		sf::Vector2f m_positionOld;
		sf::Vector2f m_velocity;
		sf::Vector2f m_maxVelocity;
		sf::Vector2f m_speed;
		sf::Vector2f m_acceleration;
		sf::Vector2f m_friction;
		TileInfo* m_referenceTile;
		sf::Vector2f m_size;
		sf::FloatRect m_AABB;
		EntityState m_state;
		bool m_collidingOnX;
		bool m_collidingOnY;

		Collisions m_collisions;
		EntityManager* m_entityManager;
	private:
		friend struct EntityManager;
	};

}