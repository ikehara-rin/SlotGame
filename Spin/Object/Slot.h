#pragma once
#include <vector>
#include "../Utility/common.h"

class Slot
{
public:
	int coin;							//コイン数
	std::vector<int> symbol_images;		//シンボル画像用
	std::vector<int> slot_images;		//スロット画像用
	std::vector<int> add_symbol_images;
	int symbol[SYMBOL + 1];				//所持シンボル
	bool add_symbolflg;					//シンボル追加フラグ
	int add_animationY;					//シンボル追加画面アニメーション用
	int addcoins_a_count;				//コイン加算アニメーション用
	int coin_a_cnt;
	int animation_num[SYMBOL + 1];
	int selectcardflg;
private:
	int slot_symbol[SLOT_X][SLOT_Y];	//スロット表示シンボル
	int add_symbol[2];					//シンボル追加用
	int symbolcpy[SYMBOL + 1];			//スロット抽選用
	int symbol_count;					//所持シンボル総数
	int slot_coins[SLOT_X][SLOT_Y];		//コイン表示用
	bool symbol_hit[SLOT_X][SLOT_Y];
	int hit_count;
	int coin_animation_img[30];
	int img_num;
	bool splash;
	int animation_time;
public:
	Slot();
	~Slot();

	// 初期化処理
	void Initialize();

	void RestartGame();

	// 更新処理
	void Update();

	// 描画処理
	void Draw() const;

	// 終了時処理
	void Finalize();

	// スロット回転処理
	void Spin();

	// 追加シンボル抽選処理
	void SetAddSymbol();

	// シンボル追加処理
	void AddSymbol(int i);

	// コイン加算処理
	void AddCoins();

	// コイン加算アニメーション
	void AddCoinsAnimation(int coin_num);

	void CoinSplash();
	// シンボル追加画面描画（アニメーション）
	void DrawAddSymbolAnimation();

	// 周りのシンボルを調べる
	int SearthSymbol(int slot_x, int slot_y, int symnol_num);

	// 生成コイン数保存初期化
	void InitCoins();

	bool GetCountFlg(bool countflg);

	void AnimationCount();
};