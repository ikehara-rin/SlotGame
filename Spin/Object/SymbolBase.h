#pragma once
#include "../Utility/common.h"

enum SymbolType
{
	NONE,
	HEX_BLUE,
	HEX_BLACK,
	HEX_RED
};

class SymbolBase
{
public:
	int coins;

public:
	SymbolBase() {}
	virtual ~SymbolBase() {}

	virtual void Initialize() {}				//‰Šú‰»ˆ—
	//virtual void Draw(int x,int y) const;				//•`‰æˆ—
	virtual void Finalize() {}				//I—¹ˆ—
	virtual void SymbolEffect() {}

};