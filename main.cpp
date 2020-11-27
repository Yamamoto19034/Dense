/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�������[�v

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

//########## �}�N����` ##########
#define GAME_WIDTH	1100	//��ʂ̉��̑傫��
#define GAME_HEIGHT	750		//��ʂ̏c�̑傫��
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS			60  //FPS�̐��l

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129

//�p�X�̒���
#define PATH_MAX				255

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�摜�̃p�X
#define IMAGE_START_BG_PATH		TEXT(".\\IMAGE\\BG_start.png")			//�X�^�[�g��ʂ̔w�i
#define IMAGE_TITLE_PATH		TEXT(".\\IMAGE\\title.png")				//�^�C�g�����S
#define IMAGE_PLAY_BG_PATH		TEXT(".\\IMAGE\\BG_play.png")			//�v���C��ʂ̔w�i
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\Player.png")			//�L�����N�^�[�̉摜

//�G���[���b�Z�[�W
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//���y�̃p�X
#define MUSIC_START_BGM_PATH	TEXT(".\\MUSIC\\waiting_room.mp3")		//�X�^�[�g��ʂ�BGM
#define MUSIC_PLAY_BGM_PATH		TEXT(".\\MUSIC\\Green_Life.mp3")		//�v���C��ʂ�BGM

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};  //�Q�[���̃V�[��

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGI = 3,
};  //�L�����N�^�[�̃X�s�[�h

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];	//�p�X
	int handle;				//�n���h��
	int x;					//X�ʒu
	int y;					//Y�ʒu
	int width;				//��
	int height;				//����
}IMAGE;  //�摜�\����

typedef struct STRUCT_CHARA
{
	IMAGE image;			//IMAGE�\����
	int speed;				//����
	int CenterX;			//���SX
	int CenterY;			//���SY
}CHARA;  //�L�����N�^�[�\����

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];	//�p�X
	int handle;				//�n���h��
}MUSIC;  //���y�\����

//######�O���[�o���ϐ�######
int StartTimeFps;					//����J�n����
int CountFps;					//�J�E���^
float CalcFps;					//�v�Z����
int SampleNumFps = GAME_FPS;	//���ς��Ƃ�T���v����

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[256] = { 0 };
char OldAllKeyState[256] = { 0 };

int GameScene;					//�Q�[���V�[�����Ǘ�

//�摜�֘A
IMAGE ImageStartBG;				//�X�^�[�g��ʂ̔w�i
IMAGE ImageTitle;				//�^�C�g�����S
IMAGE ImagePlayBG;				//�v���C��ʂ̔w�i

CHARA player;					//�L�����N�^�[

//���y�֘A
MUSIC Start_BGM;				//�X�^�[�g��ʂ̔w�i
MUSIC Play_BGM;					//�v���C��ʂ̔w�i

//######�v���g�^�C�v�錾######
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����

VOID MY_START(VOID);				//�X�^�[�g���
VOID MY_START_PROC(VOID);			//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);			//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);					//�v���C���
VOID MY_PLAY_PROC(VOID);			//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);			//�v���C��ʂ̕`��

VOID MY_END(VOID);					//�G���h���
VOID MY_END_PROC(VOID);				//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);				//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);			//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);			//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);			//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);			//���y���܂Ƃ߂č폜����֐�

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);		//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);						//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	int DrawX = 0;	//�\���ʒuX
	int DrawY = 0;	//�\���ʒuY

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_FPS_UPDATE();						//FPS�̏���(�X�V)

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_END:
			MY_END();
			break;
		}

		MY_FPS_DRAW();							//FPS�̏���(�`��)

		ScreenFlip();							//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();							//FPS�̏���(�҂�)
	}

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//���y�n���h����j��
	MY_DELETE_MUSIC();

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//########## FPS�l���v���A�X�V����֐� ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS�l��`�悷��֐� ##########
VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS�l���v�����A�҂֐� ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
	}
	return;
}

//########## �L�[�̓��͏�Ԃ��X�V����֐� ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];  //�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	//���O�̃L�[���͂�����Ă���
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);		//�S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)		//������Ă���L�[�̃L�[�R�[�h�̉����Ă���Ƃ�
		{
			AllKeyState[i]++;		//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;		//������Ă��Ȃ�
		}
	}

	return;
}

//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	//�G���^�[�L�[��������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(Start_BGM.handle) != 0)
		{
			StopSoundMem(Start_BGM.handle);  //BGM���~�߂�
		}

		//�v���C�V�[���ֈړ�����
		GameScene = GAME_SCENE_PLAY;

		return;  //�����I�Ƀv���C�V�[���ֈړ�����
	}

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(Start_BGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, Start_BGM.handle);  //50%�̉��ʂɂ���
		PlaySoundMem(Start_BGM.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	//�w�i�E�^�C�g����`��
	DrawGraph(ImageStartBG.x, ImageStartBG.y, ImageStartBG.handle, TRUE);
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);
	DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������Ă�������)", GetColor(255, 255, 255));

	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�X�^�[�g��ʂ̏���
	MY_PLAY_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	//�X�y�[�X�L�[��������A�G���h�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(Play_BGM.handle) != 0)
		{
			StopSoundMem(Play_BGM.handle);  //BGM���~�߂�
		}

		//�G���h�V�[���ֈړ�����
		GameScene = GAME_SCENE_END;

		return;  //�����I�ɃG���h�V�[���ֈړ�����
	}

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(Play_BGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, Play_BGM.handle);  //50%�̉��ʂɂ���
		PlaySoundMem(Play_BGM.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImagePlayBG.x, ImagePlayBG.y, ImagePlayBG.handle, TRUE);
	DrawString(0, 0, "�v���C���(�X�y�[�X�L�[�������Ă�������)", GetColor(255, 255, 255));

	//�v���C���[��`��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�X�^�[�g��ʂ̏���
	MY_END_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	//�G�X�P�[�v�L�[��������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);
	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������Ă�������)", GetColor(255, 255, 255));

	return;
}

//�摜���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_IMAGE(VOID)
{
	//�X�^�[�g��ʂ̔w�i�摜
	strcpy_s(ImageStartBG.path, IMAGE_START_BG_PATH);		//�p�X�̐ݒ�
	ImageStartBG.handle = LoadGraph(ImageStartBG.path);		//�ǂݍ���
	if (ImageStartBG.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageStartBG.handle, &ImageStartBG.width, &ImageStartBG.height);	//�摜�̕��ƍ������擾
	ImageStartBG.x = GAME_WIDTH / 2 - ImageStartBG.width / 2;		//X�ʒu�����߂�
	ImageStartBG.y = GAME_HEIGHT / 2 - ImageStartBG.height / 2;		//Y�ʒu�����߂�

	//�^�C�g�����S�摜
	strcpy_s(ImageTitle.path, IMAGE_TITLE_PATH);		//�p�X�̐ݒ�
	ImageTitle.handle = LoadGraph(ImageTitle.path);		//�ǂݍ���
	if (ImageTitle.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitle.handle, &ImageTitle.width, &ImageTitle.height);	//�摜�̕��ƍ������擾
	ImageTitle.x = GAME_WIDTH / 2 - ImageTitle.width / 2;			//X�ʒu�����߂�
	ImageTitle.y = GAME_HEIGHT / 2 - ImageTitle.height / 2;			//Y�ʒu�����߂�

	//�v���C��ʂ̔w�i�摜
	strcpy_s(ImagePlayBG.path, IMAGE_PLAY_BG_PATH);		//�p�X�̐ݒ�
	ImagePlayBG.handle = LoadGraph(ImagePlayBG.path);		//�ǂݍ���
	if (ImagePlayBG.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePlayBG.handle, &ImagePlayBG.width, &ImagePlayBG.height);	//�摜�̕��ƍ������擾
	ImagePlayBG.x = GAME_WIDTH / 2 - ImagePlayBG.width / 2;			//X�ʒu�����߂�
	ImagePlayBG.y = GAME_HEIGHT / 2 - ImagePlayBG.height / 2;		//Y�ʒu�����߂�

	//�v���C��ʂ̔w�i�摜
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//�p�X�̐ݒ�
	player.image.handle = LoadGraph(player.image.path);		//�ǂݍ���
	if (player.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//�摜�̕��ƍ������擾
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//X�ʒu�����߂�
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//Y�ʒu�����߂�
	player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��
	player.speed = CHARA_SPEED_MIDI;								//�X�s�[�h��ݒ�

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageStartBG.handle);
	DeleteGraph(ImageTitle.handle);
	DeleteGraph(ImagePlayBG.handle);

	DeleteGraph(player.image.handle);

	return;
}

//���y���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_MUSIC(VOID)
{
	//�X�^�[�g��ʂ̔w�i���y
	strcpy_s(Start_BGM.path, MUSIC_START_BGM_PATH);
	Start_BGM.handle = LoadSoundMem(Start_BGM.path);
	if (Start_BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_START_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�v���C��ʂ̔w�i���y
	strcpy_s(Play_BGM.path, MUSIC_PLAY_BGM_PATH);
	Play_BGM.handle = LoadSoundMem(Play_BGM.path);
	if (Play_BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(Start_BGM.handle);
	DeleteSoundMem(Play_BGM.handle);

	return;
}