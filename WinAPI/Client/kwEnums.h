#pragma once

enum class eSceneType
{
	Title,
	Play,
	Ending,
	Max,
};

enum class eLayerType
{
	BG,
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
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	End,
};