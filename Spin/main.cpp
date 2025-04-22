#include "DxLib.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLive,
	_In_ int nShowCmd
)
{
	// ���[�J���ϐ���`
	int result = 0;
	try
	{
		//�V�[���}�l�[�W���[�@�\�̐���
		SceneManager manager;

		//�V�[���}�l�[�W���[�@�\�̏���������
		manager.Initialize();

		ResourceManager* rm = ResourceManager::GetInstance();

		//�V�[���}�l�[�W���[�@�\�̍X�V����
		manager.Update();

		//�V�[���}�l�[�W���[�@�\�̏I��������
		manager.Finalize();

	}
	catch (std::string error_log)
	{
		// Log.txt�ɃG���[���e���o�͂���
		OutputDebugString(error_log.c_str());
		// �I����Ԃ��ُ�ɐݒ肷��
		result = -1;
	}

	// Dx���C�u�����̎d�l���I������
	DxLib_End();

	// �I����Ԃ̒l��ԋp����
	return result;
}