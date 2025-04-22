#include "Mouse.h"
#include "DxLib.h"

// �ÓI�����o�ϐ���`
Mouse* Mouse::instance = nullptr;		// �N���X�̃C���X�^���X�̃|�C���^

// ���͐���N���X�̃C���X�^���X�擾�����鏈��
Mouse* Mouse::GetInstance()
{
	// �C���X�^���X��������΁A��������
	if (instance == nullptr)
	{
		instance = new Mouse();
	}

	// �������g�̃|�C���^��ԋp����
	return instance;
}

// ���͐���N���X�̃C���X�^���X�폜���鏈��
void Mouse::DeleteInstance()
{
	// �C���X�^���X�����݂��Ă���΁A�폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Mouse::Update()
{
	// �}�E�X�̈ʒu���擾
	GetMousePoint(&MouseX, &MouseY);

	MouseInput = GetMouseInput();

	old_input = mouse_left;

	if ((MouseInput & MOUSE_INPUT_LEFT) == 0)
	{
		mouse_left = false;
	}
	else {
		mouse_left = true;
	}

}

void Mouse::Draw()
{
	// �}�E�X
	DrawFormatString(0, 60, 0xffffff, "���W x : %d y : %d", MouseX, MouseY);
}

bool Mouse::GetEndFlg()
{
	return false;
}

//�{�^���擾�F�������u��
bool Mouse::GetButtonDown()
{
	if ((MouseInput & MOUSE_INPUT_LEFT) == 1)
	{
		if (old_input == false) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	
}

bool Mouse::GetButton()
{
	if ((MouseInput & MOUSE_INPUT_LEFT) == 1)
	{
		if (old_input == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

bool Mouse::GetButtonUp()
{
	if ((MouseInput & MOUSE_INPUT_LEFT) == 0)
	{
		if (old_input == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

//int Mouse::GetMouseX() {
//	return MouseX;
//}
//
//int Mouse::GetMouseY() {
//	return MouseY;
//}
//
//bool Mouse::GetLeft() {
//	return MouseLeft;
//}
//
//bool Mouse::GetMiddle() {
//	return MouseMiddle;
//}
//
//bool Mouse::GetRight() {
//	return MouseRight;
//}