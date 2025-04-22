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

	virtual void Initialize() {}				//����������
	//virtual void Draw(int x,int y) const;				//�`�揈��
	virtual void Finalize() {}				//�I��������
	virtual void SymbolEffect() {}

};