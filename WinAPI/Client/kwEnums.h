#pragma once

enum class eSceneType
{
	Title,
	Play,
	Ending,
	Tool,
	Max,
};

enum class eLayerType
{
	BG,
	Tile,
	Ground,
	Monster,
	Player,
	Bullet,
	Effect,
	UI,
	End,
};

enum class eComponentType
{
	Transform,
	Rigidbody,
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	End,
};