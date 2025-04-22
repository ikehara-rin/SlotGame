#pragma once

#include <map>
#include <string>
#include <vector>

class ResourceManager
{
private:
	// 自クラスのポインタ（アドレスの先にインスタンスを生成する）
	static ResourceManager* instance;

	// 画像格納コンテナ
	std::map<std::string, std::vector<int>> image_container;

private:
	// コンストラクタをprivateにすることで、
	// 自クラスのメンバ関数でしかインスタンスを生成できないようにする
	ResourceManager() = default;

	// コピーガード
	// クラス外でインスタンスを生成して渡すことが出来ないようにする
	ResourceManager(ResourceManager& v) = delete;
	ResourceManager& operator = (const ResourceManager& v) = delete;
	// ~コピーガード

public:
	~ResourceManager() = default;

public:
	// インスタンス取得する処理
	static ResourceManager* GetInstance();
	// インスタンス削除する処理
	static void DeleteInstance();

public:
	/// <summary>
	/// 画像取得処理
	/// </summary>
	/// <param name="file_path">画像のファイルパス</param>
	/// <returns>分かつ画像の配列データ</returns>
	const std::vector<int>& GetImages(std::string file_path);

	/// <summary>
	/// 画像取得処理
	/// </summary>
	/// <param name="file_path">画像のファイルパス</param>
	/// <param name="all_num">分割総枚数</param>
	/// <param name="x_num">横方向の分割数</param>
	/// <param name="y_num">縦方向の分割数</param>
	/// <param name="x_size">分割画像1枚当たりのピクセル数（横）</param>
	/// <param name="y_size">分割画像1枚当たりのピクセル数（縦）</param>
	/// <returns>分割画像の配列データ</returns>
	const std::vector<int>& GetImages(std::string file_path, int all_num,
		int x_num, int y_num, int x_size, int y_size);

	// 読み込んだ画像の開放
	void DeleteImages();
};