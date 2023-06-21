#pragma once

enum class eSceneType
{
	Title,
	Tutorial,
	OverWorld,
	Change,
	Play,
	Carnation,
	Dragon,
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
	MeteorEffect,
	ParryObject,
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