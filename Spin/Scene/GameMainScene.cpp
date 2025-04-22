#include "GameMainScene.h"
#include "../Utility/Mouse.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include "Windows.h"

//入力制御のインスタンスを取得
Mouse* mouse = Mouse::GetInstance();

GameMainScene::GameMainScene()
	: Background(NULL)
	, button_images()
	, GameMainBGM(NULL)
	, coin_countSE()
	, coin_animation(false)
	, coin_animation_img()
	, count(0)
	, ccount(0)
	, tanimflg(false)
	, coin_a_time(50)
	, coin_num(0)
	, norma(5)
	, slot(nullptr)
	, rm(nullptr)
	, spin(0)
	, spinflg(false)
	, spin_time(0)
	, spin_SE(NULL)
	, scene_change(false)
	, countflg(false)
{

}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	slot = new Slot;

	slot->Initialize();

	rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	tmp = rm->GetImages("Resource/Images/framebg001b.png");
	button_images.push_back(tmp[0]);

	tmp = rm->GetImages("Resource/Images/frame003i.png");
	button_images.push_back(tmp[0]);

	Background = LoadGraph("Resource/images/sakaba0331_800b.jpg");

	LoadDivGraph("Resource/images/CoinAnimation/coinanimation3.png", 30, 3, 10, 1280, 480, coin_animation_img);

	font_path = "Resource/font/KH-Dot-Dougenzaka-16.ttf";
	if (AddFontResource(font_path) > 0) {
		PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	}
	else {

		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	ChangeFont("KH-ドット道玄坂16", DX_CHARSET_DEFAULT);

	GameMainBGM = LoadSoundMem("Resource/sounds/BGM.wav");

	spin_SE = LoadSoundMem("Resource/sounds/ルーレット.wav");

	coin_countSE[0] = LoadSoundMem("Resource/sounds/1コンボ.wav");
	coin_countSE[1] = LoadSoundMem("Resource/sounds/2コンボ.wav");
	coin_countSE[2] = LoadSoundMem("Resource/sounds/3コンボ.wav");
	coin_countSE[3] = LoadSoundMem("Resource/sounds/4コンボ.wav");
}

void GameMainScene::RestartGame()
{
	slot->RestartGame();

	norma = 5;

	spinflg = false;

	spin = 0;
}

eSceneType GameMainScene::Update()
{

	//入力機能：更新処理
	mouse->Update();

	if (CheckSoundMem(GameMainBGM) == 0) {
		PlaySoundMem(GameMainBGM, DX_PLAYTYPE_LOOP);
	}

	switch (current_scene)
	{
	case TITLE:
		UpdateTitle();
		break;
	case E_PLAYGAME:
		UpdateGamePlay();
		break;
	case E_RESULT:
		UpdateResult();
		break;

	}

	return E_MAIN;
}

void GameMainScene::Draw() const
{
	ChangeFont("KHドット道玄坂16");

	if (slot->add_animationY < 720 && coin_animation == false) {
		// アルファブレンドの設定する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}
	
	if (current_scene == E_RESULT || current_scene == TITLE) {
		// アルファブレンドの設定する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}

	DrawGraph(0, 0, Background, true);

	slot->Draw();

	DrawBox(540, 550, 740, 650, 0xff0000, true);
	//DrawGraph(540, 550, button_images[0], true);
	DrawGraph(540, 550, button_images[1], true);
	SetFontSize(64);
	DrawString(575, 565, "Push", 0x0000ff);
	DrawFormatString(100, 550, 0xffff00, "Norma : %d", norma);
	DrawFormatString(900, 650, 0xffff00, "Spin : %d/5", spin);

	// アルファブレンドの設定を解除する
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (coin_animation == true)
	{
		slot->AddCoinsAnimation(coin_num);
	}

	if (tanimflg == true) {
		DrawGraph(2, 300, coin_animation_img[ccount], true);
	}

	if (slot->add_animationY < 720 && coin_animation == false && tanimflg == false) {
		slot->DrawAddSymbolAnimation();
	}
	
	if (current_scene == TITLE)
	{
		SetFontSize(128);
		DrawString(400, 130, "CardSlot", 0xff0000);
		SetFontSize(50);
		DrawBox(540, 550, 740, 650, 0xff0000, true);
		DrawGraph(540, 550, button_images[1], true);
		DrawString(580, 570, "Start", 0x0000ff);
		SetFontSize(64);
		/*if (tanimflg == true) {
			DrawGraph(2, 300, coin_animation_img[ccount], true);
		}*/
	}

	if (current_scene == E_RESULT)
	{
		SetFontSize(128);
		DrawString(400, 330, "GameOver", 0xff0000);
		SetFontSize(50);
		DrawBox(540, 550, 740, 650, 0xff0000, true);
		DrawGraph(540, 550, button_images[1], true);
		DrawString(555, 565, "Restart", 0x0000ff);
		SetFontSize(64);

	}

}

void GameMainScene::Finalize()
{
	slot->Finalize();
	delete slot;
	slot = nullptr;
}

void GameMainScene::UpdateTitle()
{
	if (mouse->MouseX > 540 && mouse->MouseX < 740 && mouse->MouseY>550 && mouse->MouseY < 650)
	{
		if (mouse->GetButton() == true)
		{
			RestartGame();
			current_scene = E_PLAYGAME;
		}
		
		/*tanimflg = true;*/
		/*count++;
		if (count >= 3) {
			if (ccount >= 30) {
				ccount = 0;
			}
			ccount++;
			count = 0;
		}*/
	}
	else {
		/*tanimflg = false;*/
	}
}

void GameMainScene::UpdateGamePlay()
{

	if (spinflg == false)
	{
		slot->Update();

		if (slot->add_animationY >= 720)
		{
			if (mouse->MouseX > 540 && mouse->MouseX < 740 && mouse->MouseY>550 && mouse->MouseY < 650 || spin_time != 0)
			{
				if (mouse->GetButton() == true || spin_time != 0 && spin_time < 100)
					{
						if (CheckSoundMem(spin_SE) == 0) {
							PlaySoundMem(spin_SE, DX_PLAYTYPE_BACK);
						}
						slot->Spin();
						spin_time++;
					}
				else if (spin_time >= 100 || mouse->GetButtonUp() == true)
				{
					slot->selectcardflg = 0;

					spin++;

					spinflg = true;

					coin_animation = true;

					slot->AddCoins();

					slot->SetAddSymbol();
					slot->add_symbolflg = false;
					spin_time = 0;
				}
			}
		}
		else if (slot->add_animationY < 720)
		{
			slot->add_animationY = slot->add_animationY + 10;
		}
	}

	if (spinflg == true)
	{
		if (slot->add_symbolflg == false)
		{
			if (coin_animation == false) {
				if (slot->add_animationY <= 100)
				{
					if (mouse->MouseX > 256 && mouse->MouseX < 512 && mouse->MouseY>110 && mouse->MouseY < 510)
					{
						slot->selectcardflg = 1;
						if (mouse->GetButtonDown() == true)
						{
							slot->AddSymbol(0);
						}
					}
					else if (mouse->MouseX > 768 && mouse->MouseX < 1024 && mouse->MouseY>110 && mouse->MouseY < 510)
					{
						slot->selectcardflg = 2;
						if (mouse->GetButtonDown() == true)
						{
							slot->AddSymbol(1);
						}
					}
					else
					{
						slot->selectcardflg = 0;
					}
				}
				else if (slot->add_animationY > 100)
				{
					slot->add_animationY = slot->add_animationY - 10;
				}
			}
		}
		
		if (slot->add_symbolflg == true)
		{
			if (slot->add_animationY < 720) {
				spinflg = false;
			}
		}

		

	}

	if (coin_animation == true) {

		coin_a_time -= 1;

		if (slot->animation_num[coin_num] != 1) {
			slot->coin_a_cnt = 0;
		}
		if (slot->coin_a_cnt == 5 && coin_a_time == 49) {
			PlaySoundMem(coin_countSE[coin_num], DX_PLAYTYPE_BACK);
		}
		if (slot->coin_a_cnt > 0) {
			if (coin_a_time % 10 == 0) {
				slot->coin_a_cnt -= 1;
			}
		}

		if (slot->coin_a_cnt <= 0) {
			if (coin_num >= SYMBOL) {
				
				coin_animation = false;

				/*if (ccount == 0) {
					tanimflg = true;
				}*/

				// コインアニメーション
				//if (tanimflg == true) {
				//	count++;
				//	if (count >= 3) {
				//		/*if (ccount >= 30) {
				//			ccount = 0;
				//		}*/
				//		ccount++;
				//		count = 0;
				//	}
				//	else if (ccount >= 30) {
				//		ccount = 0;
				//		tanimflg = false;
				//	}
				//}

				coin_num = 0;
				slot->InitCoins();

				if (spin >= 5)
				{
					if (slot->coin > norma)
					{
						slot->coin -= norma;
						norma = norma + (norma / 2) + 10;
						spin = 0;
					}
					else if (slot->coin < norma)
					{
						current_scene = E_RESULT;
					}
				}


			}
			else {
				coin_num++;
			}
			coin_a_time = 50;
			slot->coin_a_cnt = 5;
		}
	}
}

void GameMainScene::UpdateResult()
{
	if (mouse->MouseX > 540 && mouse->MouseX < 740 && mouse->MouseY>550 && mouse->MouseY < 650)
	{
		if (mouse->GetButton() == true)
		{
			current_scene = TITLE;
		}
	}
}

void GameMainScene::CoinAnimation(int ccount)
{
}