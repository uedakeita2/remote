#pragma once

enum class LAYER // debuglayerは独立しているからいれない
{
	BG,
	CHAR,
	UI,
	EX,	// 特殊効果用
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);