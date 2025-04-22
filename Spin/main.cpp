#include "DxLib.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLive,
	_In_ int nShowCmd
)
{
	// ローカル変数定義
	int result = 0;
	try
	{
		//シーンマネージャー機能の生成
		SceneManager manager;

		//シーンマネージャー機能の初期化処理
		manager.Initialize();

		ResourceManager* rm = ResourceManager::GetInstance();

		//シーンマネージャー機能の更新処理
		manager.Update();

		//シーンマネージャー機能の終了時処理
		manager.Finalize();

	}
	catch (std::string error_log)
	{
		// Log.txtにエラー内容を出力する
		OutputDebugString(error_log.c_str());
		// 終了状態を異常に設定する
		result = -1;
	}

	// Dxライブラリの仕様を終了する
	DxLib_End();

	// 終了状態の値を返却する
	return result;
}