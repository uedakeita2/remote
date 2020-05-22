#pragma once

enum class LAYER // debuglayer‚Í“Æ—§‚µ‚Ä‚¢‚é‚©‚ç‚¢‚ê‚È‚¢
{
	BG,
	CHAR,
	UI,
	EX,	// “ÁŽêŒø‰Ê—p
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);