#pragma once
#include "SymbolBase.h"

class HexBlue : public SymbolBase
{
public:

	int coins;
public:

	HexBlue();
	~HexBlue();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void SymbolEffect() override;
};