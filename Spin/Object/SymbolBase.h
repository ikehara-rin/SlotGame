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

	virtual void Initialize() {}				//初期化処理
	//virtual void Draw(int x,int y) const;				//描画処理
	virtual void Finalize() {}				//終了時処理
	virtual void SymbolEffect() {}

};