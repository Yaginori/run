//-----------------------------------------------------------------------------
// @brief  ƒƒCƒ“ˆ—.
//-----------------------------------------------------------------------------

#pragma once

class Enemy;
class Player;

class HitChecker
{
public:
	static void Check(Player& player, Enemy& enemy);
};