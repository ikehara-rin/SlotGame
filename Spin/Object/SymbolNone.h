#pragma once
#include "SymbolBase.h"

class SymbolNone : public SymbolBase
{
public:
	SymbolNone();
	~SymbolNone();

	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void SymbolEffect() override;
};