#include "Slot.h"
#include "DxLib.h"
#include "../Utility/UserTemplate.h"
#include "../Utility/ResourceManager.h"

Slot::Slot()
	: coin(0)
	, symbol_images()
	, slot_images()
	, symbol_count(0)
	, add_symbolflg(true)
	, add_animationY(720)
	, add_symbol_images()
	, slot_coins()
	, symbol_hit()
	, coin_a_cnt(5)
	, hit_count(0)
	, animation_num()
	, selectcardflg(0)
	, coin_animation_img()
	, img_num(0)
	, splash(false)
	, animation_time(50)
{
	
	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {
			slot_symbol[i][j] = 0;
		}
	}

}

Slot::~Slot() {
}

void Slot::Initialize() {

	// 画像読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;
	tmp = rm->GetImages("Resource/Images/Symbol/hexagon-60.png");
	symbol_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Symbol/hexagon-B60.png");
	symbol_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Symbol/hexagon-Black60.png");
	symbol_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/Symbol/hexagon-R60.png");
	symbol_images.push_back(tmp[0]);
	
	tmp = rm->GetImages("Resource/Images/coin.png");
	slot_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/frame001a.png");
	slot_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/framebg003g.png");
	slot_images.push_back(tmp[0]);

	tmp = rm->GetImages("Resource/Images/SymbolCard/symbol_card_blue.png");
	add_symbol_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/SymbolCard/symbol_card_black.png");
	add_symbol_images.push_back(tmp[0]);
	tmp = rm->GetImages("Resource/Images/SymbolCard/symbol_card_red.png");
	add_symbol_images.push_back(tmp[0]);

	LoadDivGraph("Resource/images/CoinAnimation/pipo-btleffect142.png", 30, 5, 6, 240, 240, coin_animation_img);

	// 初期所持シンボル
	symbol[0] = 0;
	symbol[1] = 1;
	symbol[2] = 1;
	symbol[3] = 1;
}

void Slot::RestartGame() {
	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {
			slot_symbol[i][j] = 0;
		}
	}
	symbol[0] = 0;
	symbol[1] = 1;
	symbol[2] = 1;
	symbol[3] = 1;
	
	coin = 0;

	add_symbolflg = true;
}

void Slot::Update() {
	
}

void Slot::Draw() const {
	//スロット表示
	DrawGraph(100, 20, slot_images[2], true);
	DrawGraph(40, 0, slot_images[1], true);
	//DrawBox(100, 20, 1180, 500, 0x00ff00, true);
	for (int i = 0; i < SYMBOL; i++){
		for (int j = 0; j < SYMBOL; j++) {
			switch (slot_symbol[i][j]) {
			case 0:
				DrawGraph(110 + 500 * i, 30 + 150 * j, symbol_images[0], true);
				break;
			case 1:
				DrawGraph(110 + 500 * i, 30 + 150 * j, symbol_images[1], true);
				break;
			case 2:
				DrawGraph(110 + 500 * i, 30 + 150 * j, symbol_images[2], true);
				break;
			case 3:
				DrawGraph(110 + 500 * i, 30 + 150 * j, symbol_images[3], true);
				break;
			}

		}
	}

	// コイン数表示
	DrawFormatString(100, 650, 0xffff00, "Coin : %d", coin);

	// 所持シンボル数
	DrawGraph(900, 500, symbol_images[1], true);
	DrawFormatString(920, 500, 0xffff00, "  %d", symbol[1]);
	DrawGraph(900, 550, symbol_images[2], true);
	DrawFormatString(920, 550, 0xffff00, "  %d", symbol[2]);
	DrawGraph(900, 600, symbol_images[3], true);
	DrawFormatString(920, 600, 0xffff00, "  %d", symbol[3]);

}

void Slot::Finalize() {

}

void Slot::Spin() {

	// symbolをコピー
	for (int i = 0; i <= SYMBOL; i++) {
		symbolcpy[i] = symbol[i];
	}

	// シンボル総数取得
	for (int i = 1; i <= SYMBOL; i++) {
		symbol_count = symbolcpy[i] + symbol_count;
	}

	// スロット初期化
	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {			
				slot_symbol[i][j] = 0;	
		}
	}

/*************************
シンボルランダム振り分け
**************************/
	int a, b, c;
	bool setflg = false;
	// シンボル数がスロットを超えたとき超えた分のシンボルをランダムで外す
	if (symbol_count > 9) {
		while (symbol_count > 9) {
			c = GetRand(SYMBOL);
			if (symbolcpy[c] > 0) {
				symbolcpy[c] = symbolcpy[c] - 1;
				symbol_count--;
			}
		}
	}

	// スロットにシンボルをランダムで振り分ける
	for (int i = 1; i <= SYMBOL; i++) {
		if (symbolcpy[i] != 0) {
			while (symbolcpy[i] != 0) {
				a = GetRand(2);
				b = GetRand(2);
				if (slot_symbol[a][b] == 0) {
					slot_symbol[a][b] = i;
					symbolcpy[i]--;
					symbol_count--;
				}
			}
		}
	}
}

// 追加するシンボルを抽選
void Slot::SetAddSymbol() {
	bool addflg = false;

	for (int i = 0; i < 2; i++)
	{
		addflg = false;

		while (addflg == false)
		{
			add_symbol[i] = GetRand(SYMBOL);
			if (i == 1) 
			{
				if (add_symbol[i] != 0 && add_symbol[i] != add_symbol[0])
				{
					addflg = true;
				}
			}
			else
			{
				if (add_symbol[i] != 0)
				{
					addflg = true;
				}
			}
			
		}
	}
	
}

// シンボル追加
void Slot::AddSymbol(int i)
{
	symbol[add_symbol[i]]++;
	add_symbolflg = true;
}

// シンボル追加画面表示（アニメーション）
void Slot::DrawAddSymbolAnimation()
{
	DrawGraph(256, add_animationY + 10, add_symbol_images[add_symbol[0] - 1], true);
	DrawGraph(768, add_animationY + 10, add_symbol_images[add_symbol[1] - 1], true);

	switch (selectcardflg) {
	case 0:

		break;
	case 1:
		DrawBox(256 - 3, add_animationY + 13, 517, add_animationY + 9 + 408, 0xff00ff, false);
		DrawBox(256 - 2, add_animationY + 12, 516, add_animationY + 8 + 408, 0xff00ff, false);
		DrawBox(256 - 1, add_animationY + 11, 515,  add_animationY + 7 + 408, 0xff00ff, false);
		DrawBox(256, add_animationY + 10, 514, add_animationY + 6 + 408, 0xff00ff, false);
		break;
	case 2:
		DrawBox(768 - 3, add_animationY + 13, 1029, add_animationY + 9 + 408, 0xff00ff, false);
		DrawBox(768 - 2, add_animationY + 12, 1028, add_animationY + 8 + 408, 0xff00ff, false);
		DrawBox(768 - 1, add_animationY + 11, 1027, add_animationY + 7 + 408, 0xff00ff, false);
		DrawBox(768, add_animationY + 10, 1026, add_animationY + 6 + 408, 0xff00ff, false);
		break;
	}
}

// コイン生成＆加算処理
void Slot::AddCoins()
{
	int add_coin = 0;

	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {
			switch (slot_symbol[i][j]) {
			case 0:	//白	:効果なし
				hit_count = SearthSymbol(i, j, 2);
				if (hit_count != 0) {
					coin += hit_count;
					add_coin += hit_count;
					slot_coins[i][j] = hit_count;
					animation_num[0] = 1;
				}
				hit_count = 0;
				break;
			case 1:	//青	:+周りの青の数
				hit_count = SearthSymbol(i, j, 1);
				if (hit_count != 0) {
					coin += hit_count;
					add_coin += hit_count;
					slot_coins[i][j] = hit_count;
					animation_num[1] = 1;
				}
				hit_count = 0;
				break;
			case 2:	//黒	:周りの白のコイン生成+2
				coin += 2;
				add_coin += 2;
				slot_coins[i][j] = 2;
				animation_num[2] = 1;
				break;
			case 3:	//赤	:1回出ると消える
				coin += 5;
				add_coin += 5;
				slot_coins[i][j] = 5;
				symbol[3] -= 1;
				animation_num[3] = 1;
				break;
			}
		}
	}

	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {
			symbol_hit[i][j] = false;
		}
	}

	if (add_coin >= 1) {
		splash = true;
	}
}

// コイン加算アニメーション
void Slot::AddCoinsAnimation(int coin_num)
{
	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {
			if (slot_symbol[i][j] == coin_num) {
				if (animation_num[coin_num] == 1) {
					if (coin_num == 0) {
						if (slot_coins[i][j] != 0) {
							DrawGraph((500 * i) + 100, (150 * j) + coin_a_cnt, slot_images[0], true);
							DrawFormatString((500 * i) + 150, (150 * j) + coin_a_cnt, 0xffff00, "%d", slot_coins[i][j]);
						}
					}
					else {
						DrawGraph((500 * i) + 100, (150 * j) + coin_a_cnt, slot_images[0], true);
						DrawFormatString((500 * i) + 150, (150 * j) + coin_a_cnt, 0xffff00, "%d", slot_coins[i][j]);
					}
				}
			}
		}
	}

	/*if (splash == true) {
		while(img_num >= 30) {
			CoinSplash();
		}
		if (img_num >= 30) {
			splash = false;
			img_num = 0;
		}
	}*/
}

void Slot::CoinSplash()
{
	DrawGraph(2, 300, coin_animation_img[img_num], true);
}

// 周りのシンボルを調べる
int Slot::SearthSymbol(int slot_x, int slot_y, int symbol_num)
{
	int x = 0;
	int y = 0;
	int c = 0;

	int hit = 0;

	// 縦を調べる
	switch (slot_x) {
	case 0:
		x = 1;
		break;
	case 1:
		x = 0;
		break;
	case 2:
		x = -1;
		break;
	}

	// 横を調べる
	switch (slot_y) {
	case 0:
		y = 1;
		break;
	case 1:
		y = 0;
		break;
	case 2:
		y = -1;
		break;
	}

	if (x != 0) {
		if (y != 0) {
			//■□■
			//□□□
			//■□■
			if (slot_symbol[slot_x + x][slot_y] == symbol_num) {
				symbol_hit[slot_x + x][slot_y] = true;
				hit++;
			}
			if (slot_symbol[slot_x][slot_y + y] == symbol_num) {
				symbol_hit[slot_x][slot_y + y] = true;
				hit++;
			}
			if (slot_symbol[slot_x + x][slot_y + y] == symbol_num) {
				symbol_hit[slot_x + x][slot_y + y] = true;
				hit++;
			}
		}
		else {
			//□□□
			//■□■
			//□□□
			if (slot_symbol[slot_x][slot_y + 1] == symbol_num) {
				symbol_hit[slot_x][slot_y + 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x][slot_y - 1] == symbol_num) {
				symbol_hit[slot_x][slot_y - 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x + x][slot_y] == symbol_num) {
				symbol_hit[slot_x + x][slot_y] = true;
				hit++;
			}
			if (slot_symbol[slot_x + x][slot_y + 1] == symbol_num) {
				symbol_hit[slot_x + x][slot_y + 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x + x][slot_y - 1] == symbol_num) {
				symbol_hit[slot_x + x][slot_y - 1] = true;
				hit++;
			}
			
		}
	}
	else {
		if (y != 0) {
			//□■□
			//□□□
			//□■□
			if (slot_symbol[slot_x - 1][slot_y] == symbol_num) {
				symbol_hit[slot_x - 1][slot_y] = true; 
				hit++;
			}
			if (slot_symbol[slot_x - 1][slot_y + y] == symbol_num) {
				symbol_hit[slot_x - 1][slot_y + y] = true;
				hit++;
			}
			if (slot_symbol[slot_x + 1][slot_y] == symbol_num) {
				symbol_hit[slot_x + 1][slot_y] = true;
				hit++;
			}
			if (slot_symbol[slot_x + 1][slot_y + y] == symbol_num) {
				symbol_hit[slot_x + 1][slot_y + y] = true;
				hit++;
			}
			if (slot_symbol[slot_x][slot_y + y] == symbol_num) {
				symbol_hit[slot_x][slot_y + y] = true;
				hit++;
			}
		}
		else {
			//□□□
			//□■□
			//□□□
			if (slot_symbol[slot_x + 1][slot_y] == symbol_num) {		// 上
				symbol_hit[slot_x + 1][slot_y] = true;
				hit++;
			}
			if (slot_symbol[slot_x - 1][slot_y] == symbol_num) {		// 下
				symbol_hit[slot_x - 1][slot_y] = true;
				hit++;
			}
			if (slot_symbol[slot_x + 1][slot_y + 1] == symbol_num) {	// 右上
				symbol_hit[slot_x + 1][slot_y + 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x - 1][slot_y - 1] == symbol_num) {	// 左下
				symbol_hit[slot_x - 1][slot_y - 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x - 1][slot_y + 1] == symbol_num) {	// 右下
				symbol_hit[slot_x - 1][slot_y + 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x + 1][slot_y - 1] == symbol_num) {	// 左上
				symbol_hit[slot_x + 1][slot_y - 1] = true;
				hit++;
			}			
			if (slot_symbol[slot_x][slot_y + 1] == symbol_num) {		// 右
				symbol_hit[slot_x][slot_y + 1] = true;
				hit++;
			}
			if (slot_symbol[slot_x - 1][slot_y] == symbol_num) {		// 左
				symbol_hit[slot_x - 1][slot_y] = true;
				hit++;
			}
		}
	}

	return hit;
}

// 生成コイン数保存初期化
void Slot::InitCoins() {
	for (int i = 0; i < SYMBOL; i++) {
		for (int j = 0; j < SYMBOL; j++) {
			slot_coins[i][j] = 0;
		}
	}

	for (int i = 0; i <= SYMBOL; i++) {
		animation_num[i] = 0;
	}

	splash = false;
}

bool Slot::GetCountFlg(bool countflg)
{
	return countflg;
}

void Slot::AnimationCount()
{
	/*animation_time--;
	if (animation_time/2 == 0) {	
		img_num++;
	}
	else if (animation_time <= 0) {
		animation_time = 50;
		img_num = 0;
	}*/
}