#pragma once
class Mouse
{
private:
	// 自クラスのポインタ（アドレス先にインスタンスを生成する）
	static Mouse* instance;

public:
	// マウス入力値
	int MouseX;
	int MouseY;
	int MouseInput;
	bool mouse_left;
	bool old_input;

private:
	// コンストラクタをprivateにすることで、
	// 自クラスのメンバ関数でしかインスタンスを生成できないようにする
	Mouse() = default;

	// コピーガード
	//　クラス外でインスタンス生成して渡すことが出来ないようにする
	Mouse(Mouse& v) = delete;
	Mouse& operator = (const Mouse& v) = delete;
	// ~コピーガード

public:
	~Mouse() = default;

public:
	// インスタンスを取得する処理
	static Mouse* GetInstance();
	// インスタンス削除する処理
	static void DeleteInstance();

public:
	// コントローラー入力更新処理
	void Update();

	void Draw();

	bool GetEndFlg();

	// 押した瞬間
	bool GetButtonDown();

	// 押している間
	bool GetButton();

	// 離した瞬間
	bool GetButtonUp();

	//int GetMouseX();

	//int GetMouseY();

	//bool GetLeft();

	//bool GetRight();

	//bool GetMiddle();

};