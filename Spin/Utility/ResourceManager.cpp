#include "ResourceManager.h"
#include "DxLib.h"

// 静的メンバ変数定義
ResourceManager* ResourceManager::instance = nullptr;	//クラスインスタンスのポインタ

// リソース管理クラスのインスタンス取得する処理
ResourceManager* ResourceManager::GetInstance()
{
	// インスタンスが泣けれは、生成する
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	// 自分自身のポインタを返却する
	return instance;
}

// リソース管理クラスのインスタンス削除する処理
void ResourceManager::DeleteInstance()
{
	// インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// 画像取得処理
const std::vector<int>& ResourceManager::GetImages(std::string file_path)
{
	// コンテナ内に画像が無ければ、画像を読み込む
	if (image_container.count(file_path) == NULL)
	{
		// 画像読み込み処理
		int handle = LoadGraph(file_path.c_str());

		// エラーチェック
		if (handle == -1)
		{
			throw(file_path + "の画像が読み込めませんでした\n");
		}

		// コンテナ内に画像を格納する
		image_container[file_path].push_back(handle);
	}

	// コンテナ内の画像データを返却
	return image_container[file_path];
}

// 画像取得処理（分割読込み対応）
const std::vector<int>& ResourceManager::GetImages(std::string file_path,
	int all_num, int x_num, int y_num, int x_size, int y_size)
{
	// コンテナ内に画像が無ければ、画像を読み込む
	if (image_container.count(file_path) == NULL)
	{
		// 動的配列の確保（分割枚数分のメモリを確保）
		int* handle = new int[all_num];

		// 画像の分割読込み
		int result = LoadDivGraph(file_path.c_str(), all_num,
			x_num, y_num, x_size, y_size, handle);

		//エラーチェック
		if (result == -1)
		{
			throw(file_path + "の画像が読み込めませんでした\n");
		}

		// コンテナ内に画像を格納する
		for (int i = 0; i < all_num; i++)
		{
			image_container[file_path].push_back(handle[i]);
		}

		// 動的メモリの開放
		delete[] handle;

	}

	// コンテナ内の画像データを返却
	return image_container[file_path];
}

// 読み込んだ画像の開放
void ResourceManager::DeleteImages()
{
	// コンテナ内にデータが無ければ、処理を終了する
	if (image_container.size() == NULL)
	{
		return;
	}

	// 文字列と画像ハンドルデータのセットでループを行う。
	for (std::pair<std::string, std::vector<int>> value : image_container)
	{
		// 読み込んだ画像の開放
		DeleteSharingGraph(value.second[0]);
		//動的配列の開放
		value.second.clear();
	}

	// 画像コンテナの開放
	image_container.clear();
}