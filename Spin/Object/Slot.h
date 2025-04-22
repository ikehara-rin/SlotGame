#pragma once
#include <vector>
#include "../Utility/common.h"

class Slot
{
public:
	int coin;							//�R�C����
	std::vector<int> symbol_images;		//�V���{���摜�p
	std::vector<int> slot_images;		//�X���b�g�摜�p
	std::vector<int> add_symbol_images;
	int symbol[SYMBOL + 1];				//�����V���{��
	bool add_symbolflg;					//�V���{���ǉ��t���O
	int add_animationY;					//�V���{���ǉ���ʃA�j���[�V�����p
	int addcoins_a_count;				//�R�C�����Z�A�j���[�V�����p
	int coin_a_cnt;
	int animation_num[SYMBOL + 1];
	int selectcardflg;
private:
	int slot_symbol[SLOT_X][SLOT_Y];	//�X���b�g�\���V���{��
	int add_symbol[2];					//�V���{���ǉ��p
	int symbolcpy[SYMBOL + 1];			//�X���b�g���I�p
	int symbol_count;					//�����V���{������
	int slot_coins[SLOT_X][SLOT_Y];		//�R�C���\���p
	bool symbol_hit[SLOT_X][SLOT_Y];
	int hit_count;
	int coin_animation_img[30];
	int img_num;
	bool splash;
	int animation_time;
public:
	Slot();
	~Slot();

	// ����������
	void Initialize();

	void RestartGame();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw() const;

	// �I��������
	void Finalize();

	// �X���b�g��]����
	void Spin();

	// �ǉ��V���{�����I����
	void SetAddSymbol();

	// �V���{���ǉ�����
	void AddSymbol(int i);

	// �R�C�����Z����
	void AddCoins();

	// �R�C�����Z�A�j���[�V����
	void AddCoinsAnimation(int coin_num);

	void CoinSplash();
	// �V���{���ǉ���ʕ`��i�A�j���[�V�����j
	void DrawAddSymbolAnimation();

	// ����̃V���{���𒲂ׂ�
	int SearthSymbol(int slot_x, int slot_y, int symnol_num);

	// �����R�C�����ۑ�������
	void InitCoins();

	bool GetCountFlg(bool countflg);

	void AnimationCount();
};