#pragma once

#include "SceneBase.h"
#include "../Object/Slot.h"
#include <vector>
#include "Windows.h"
#include "../Utility/ResourceManager.h"

enum eGameSceneType
{
	TITLE,
	E_PLAYGAME,
	E_RESULT
};

class GameMainScene : public SceneBase
{
private:
	int spin;
	int spinflg;
	int spin_time;
	int spin_SE;
	int Background;
	int GameMainBGM;
	int coin_a_time;
	bool coin_animation;
	int coin_animation_img[30];
	int count;
	int ccount;
	bool countflg;
	bool tanimflg;
	int coin_num;
	int coin_countSE[SYMBOL + 1];
	Slot* slot;
	int norma;
	eGameSceneType current_scene;
	bool scene_change;
	ResourceManager* rm;
	std::vector<int> button_images;
	LPCSTR font_path;

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	void UpdateTitle();
	void UpdateGamePlay();
	void UpdateResult();
	void RestartGame();
	void CoinAnimation(int ccount);

	virtual eSceneType GetNowScene() const override;
};
