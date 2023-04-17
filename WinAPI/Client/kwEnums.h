#pragma once

enum class eSceneType
{
	Title,
	OverWorld,
	Change,
	Play,
	Ending,
	Tool,
	Max,
};

enum class eLayerType
{
	PixelMap,
	BG,
	Tile,
	Entrance,
	Ground,
	Monster,
	AttackObject,
	Player,
	FrontBG,
	Bullet,
	Effect,
	UI,
	SceneEffect,
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