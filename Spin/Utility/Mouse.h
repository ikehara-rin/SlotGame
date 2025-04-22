#pragma once
class Mouse
{
private:
	// ���N���X�̃|�C���^�i�A�h���X��ɃC���X�^���X�𐶐�����j
	static Mouse* instance;

public:
	// �}�E�X���͒l
	int MouseX;
	int MouseY;
	int MouseInput;
	bool mouse_left;
	bool old_input;

private:
	// �R���X�g���N�^��private�ɂ��邱�ƂŁA
	// ���N���X�̃����o�֐��ł����C���X�^���X�𐶐��ł��Ȃ��悤�ɂ���
	Mouse() = default;

	// �R�s�[�K�[�h
	//�@�N���X�O�ŃC���X�^���X�������ēn�����Ƃ��o���Ȃ��悤�ɂ���
	Mouse(Mouse& v) = delete;
	Mouse& operator = (const Mouse& v) = delete;
	// ~�R�s�[�K�[�h

public:
	~Mouse() = default;

public:
	// �C���X�^���X���擾���鏈��
	static Mouse* GetInstance();
	// �C���X�^���X�폜���鏈��
	static void DeleteInstance();

public:
	// �R���g���[���[���͍X�V����
	void Update();

	void Draw();

	bool GetEndFlg();

	// �������u��
	bool GetButtonDown();

	// �����Ă����
	bool GetButton();

	// �������u��
	bool GetButtonUp();

	//int GetMouseX();

	//int GetMouseY();

	//bool GetLeft();

	//bool GetRight();

	//bool GetMiddle();

};