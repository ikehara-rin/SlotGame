#include "Mouse.h"
#include "DxLib.h"

// 静的メンバ変数定義
Mouse* Mouse::instance = nullptr;		// クラスのインスタンスのポインタ

// 入力制御クラスのインスタンス取得をする処理
Mouse* Mouse::GetInstance()
{
	// インスタンスが無ければ、生成する
	if (instance == nullptr)
	{
		instance = new Mouse();
	}

	// 自分自身のポインタを返却する
	return instance;
}

// 入力制御クラスのインスタンス削除する処理
void Mouse::DeleteInstance()
{
	// インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Mouse::Update()
{
	// マウスの位置を取得
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
	// マウス
	DrawFormatString(0, 60, 0xffffff, "座標 x : %d y : %d", MouseX, MouseY);
}

bool Mouse::GetEndFlg()
{
	return false;
}

//ボタン取得：押した瞬間
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