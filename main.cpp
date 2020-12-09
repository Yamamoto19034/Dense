/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�������[�v

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

//########## �}�N����` ##########
#define GAME_WIDTH	960		//��ʂ̉��̑傫��
#define GAME_HEIGHT	660		//��ʂ̏c�̑傫��
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
#define IMAGE_HUMAN_PATH		TEXT(".\\IMAGE\\human.png")				//�l��(�q)�̕`��

//�}�b�v�`�b�v�֘A
#define GAME_MAP_TATE_MAX		11  //�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX		16  //�}�b�v�̉��̐�

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip.png")

#define MAP_DIV_WIDTH			60  //�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT			60  //�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE			10  //�摜���c�ɕ������鐔
#define MAP_DIV_YOKO			2   //�摜�����ɕ������鐔
#define MAP_DIV_NUM				MAP_DIV_TATE * MAP_DIV_YOKO  //�摜�𕪊����鑍��

//�G���[���b�Z�[�W
#define START_ERR_TITLE			TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION		TEXT("�X�^�[�g�ʒu�����܂��Ă܂���")

//�G���[���b�Z�[�W
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//���y�̃p�X
#define MUSIC_START_BGM_PATH	TEXT(".\\MUSIC\\waiting_room.mp3")		//�X�^�[�g��ʂ�BGM
#define MUSIC_PLAY_BGM_PATH		TEXT(".\\MUSIC\\Green_Life.mp3")		//�v���C��ʂ�BGM

//��������
#define TIMELIMIT				60 * 1000		//60�b��
#define EASY					5 * 1000

enum GAME_MAP_KIND
{
	n = -1,  //none
	t = 0,   //�ʘH
	w = 1,   //��
	s = 2,   //�X�^�[�g
};  //�}�b�v�̎��

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

//int�^��POINT�\����
typedef struct STRUCT_I_POINT
{
	int x = -1;		//���W��������
	int y = -1;		//���W��������
}iPOINT;

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
	//int CenterX;			//���SX
	//int CenterY;			//���SY

	//�f�o�b�O�p
	RECT coll;				//�����蔻��
	iPOINT collBeforePt;	//������O�̍��W
}CHARA;  //�L�����N�^�[�\����

typedef struct STRUCT_HUMAN
{
	IMAGE image;					//�C���[�W�\����
	BOOL IsDraw;					//�`��ł��邩�ۂ�

	RECT Human_Coll;				//�����蔻��
	iPOINT Human_CollBeforePt;		//������O�̍��W
}HUMAN;  //�ŏ��ɏo������p

typedef struct STRUCT_HUMAN_TIME
{
	IMAGE Humanimage;				//�C���[�W�\����
	BOOL IsDraw;					//�`��ł��邩�ۂ�

	RECT HumanCons_Coll;			//�����蔻��
	iPOINT HumanCons_CollBeforePt;	//������O�̍��W
}HUMAN_CONSTANT;  //���Ԍo�߂ŏo���p�̐l��

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];	//�p�X
	int handle;				//�n���h��
}MUSIC;  //���y�\����

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle[MAP_DIV_NUM];	//���������}�b�v�̉摜
	int width;					//��
	int height;					//����
}MAPCHIP;   //MAP_IMAGE�\����

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//�}�b�v�̎��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}MAP;   //MAP�\����

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
IMAGE ImageHuman;				//�l��(�q)�̕`��

HUMAN IMAGEHuman[5];			//�X�^�[�g���ɍŏ��̐l�Ԃ�`��(5�l����)
HUMAN_CONSTANT Human_Cons[20];	//��莞�Ԃ��Ƃɏo������p�̐l�Ԃ�z��ŊǗ�
int TimeDraw = 0;				//Human_Cons�̔z��̓Y����

CHARA player;					//�L�����N�^�[

//���y�֘A
MUSIC Start_BGM;				//�X�^�[�g��ʂ̔w�i
MUSIC Play_BGM;					//�v���C��ʂ̔w�i

//���Ԋ֘A
int StartTime = 0;				//�v���J�n����
int ElaTime = 0;				//�c�莞��
int CDTimeLimit = 0;			//�J�E���g�_�E���p�̐�������(CD = Count Down)
int TimeLimit = 0;				//��������
BOOL First_flg = TRUE;			//�Q�[���ɓ���ۂ̃J�E���g�_�E��������
BOOL CountDown = TRUE;			//�J�E���g�_�E��������ۂ̊���Ԃ��m�ۂ���
int ConstantTime = 0;
int StartTime2 = 0;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,	//0
		w,t,t,t,t,t,t,t,t,t,t,t,t,t,t,w,    //1
		w,t,t,t,t,t,t,t,t,t,t,t,t,t,t,w,    //2
		w,t,t,w,t,t,w,t,t,w,t,t,w,t,t,w,	//3
		w,t,t,w,t,t,w,t,t,w,t,t,w,t,t,w,	//4
		w,t,t,w,t,t,w,t,t,w,t,t,w,t,t,w,	//5
		w,t,t,w,t,t,w,t,t,w,t,t,w,t,t,w,	//6
		w,t,t,w,t,t,w,t,t,w,t,t,w,t,t,w,	//7
		w,s,t,t,t,t,t,t,t,t,t,t,t,t,t,w,	//8
		w,t,t,t,t,t,t,t,t,t,t,t,t,t,t,w,	//9
		w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,	//0
};   //�Q�[���̃}�b�v

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

//�}�b�v�̏ꏊ���Ǘ�
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�X�^�[�g�̈ʒu
iPOINT startPt{ -1,-1 };

//�}�b�v�̓����蔻��
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//######�v���g�^�C�v�錾######
VOID MY_FPS_UPDATE(VOID);				//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);					//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);					//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);		//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);					//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����

VOID MY_START(VOID);					//�X�^�[�g���
VOID MY_START_PROC(VOID);				//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);				//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);						//�v���C���
VOID MY_PLAY_PROC(VOID);				//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);				//�v���C��ʂ̕`��

VOID MY_END(VOID);						//�G���h���
VOID MY_END_PROC(VOID);					//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);					//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);				//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);				//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);				//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);				//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_MAP_PLAYER_COLL(RECT);	//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//�̈�̓����蔻�������֐�

int MY_CHECK_HUMAN_PLAYER_COLL(RECT);	//�}�b�v�ƃv���C���[�̓����蔻�������֐�
VOID COLLPROC(VOID);					//�}�b�v�ƃv���C���[�̓����蔻�������֐�				

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

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�X�^�[�g�ʒu��T��
			if (mapData[tate][yoko] == s)
			{
				//�X�^�[�g�ʒu���v�Z
				startPt.x = mapChip.width * yoko;	//���SX���W���擾
				startPt.y = mapChip.height * tate;	//���SY���W���擾
				break;
			}
		}
		//�X�^�[�g�ʒu�����܂��Ă���΁A���[�v�I��
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}
	//�X�^�[�g�ʒu�����܂��Ă��Ȃ����
	if (startPt.x == -1 && startPt.y == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);
		return -1;
	}

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

		//�v���C���[�̒��S�ʒu���v�Z����
		//player.CenterX = startPt.x;
		//player.CenterY = startPt.y;

		//�v���C���[�̉摜�̈ʒu��ݒ肷��
		player.image.x = startPt.x;
		player.image.y = startPt.y;

		//�v���C��ʂɌ����ď���
		TimeLimit = TIMELIMIT;			//�������Ԃ�ݒ�
		GameScene = GAME_SCENE_PLAY;	//�v���C�V�[���ֈړ�����

		//�����ŕ`��ʒu�����߂�(�ŏ��ɏo������p)
		for (int i = 0; i < 5; i++)
		{
			IMAGEHuman[i].image.x = MAP_DIV_WIDTH * GetRand(15);
			IMAGEHuman[i].image.y = MAP_DIV_HEIGHT * GetRand(10);

			IMAGEHuman[i].Human_Coll.left = IMAGEHuman[i].image.x + 1;
			IMAGEHuman[i].Human_Coll.top = IMAGEHuman[i].image.y + 1;
			IMAGEHuman[i].Human_Coll.right = IMAGEHuman[i].image.x + MAP_DIV_WIDTH - 1;
			IMAGEHuman[i].Human_Coll.bottom = IMAGEHuman[i].image.y + MAP_DIV_HEIGHT - 1;
		}
		//�����ŕ`��ʒu�����߂�(��莞�Ԃŏo������p)
		for (int i = 0; i < 15; i++)
		{
			Human_Cons[i].Humanimage.x = 60 * GetRand(15);
			Human_Cons[i].Humanimage.y = 60 * GetRand(10);
		}

		return;  //�����I�Ƀv���C�V�[���ֈړ�����
	}

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(Start_BGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, Start_BGM.handle);  //50%�̉��ʂɂ���
		PlaySoundMem(Start_BGM.handle, DX_PLAYTYPE_LOOP);		 //���[�v�Đ�
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
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(Play_BGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, Play_BGM.handle);  //50%�̉��ʂɂ���
		PlaySoundMem(Play_BGM.handle, DX_PLAYTYPE_LOOP);		//���[�v�Đ�
	}

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

	if (First_flg)  //�܂��̓J�E���g�_�E������X�^�[�g
	{
		if (CountDown)  //����Ԃ��擾
		{
			StartTime = GetNowCount();
			CountDown = FALSE;			//����ȍ~�A����if���͍s��Ȃ�
		}

		//���݂̎��Ԃ��擾
		int NowCount = GetNowCount();
		CDTimeLimit = 3 * 1000;		//�������Ԃ�ݒ�
		ElaTime = CDTimeLimit - (NowCount - StartTime);  //�J�E���g�_�E�����s��

		//�o�ߎ��Ԃ�0�b�ɂȂ�����(3,2,1 �ŏI�������邽�� <=)
		if (ElaTime <= 0)
		{
			StartTime = GetNowCount();		//�{�ԂɌ����Ċ���Ԃ��擾
			ConstantTime = GetNowCount();	//�{�ԂɌ����Ċ���Ԃ��擾
			First_flg = FALSE;				//����ȍ~�̓J�E���g�_�E�����s��Ȃ�
		}
	}
	else 
	{
		//���݂̎��Ԃ��擾
		int NowCount = GetNowCount();	//�������ԗp
		int NowCount2 = GetNowCount();	//��莞�Ԃŏo������p

		//��������(�~���Ŏ��ԕ\��) - (���݂̎��� - ��̎���) �� �~���b�P��
		ElaTime = TimeLimit - (NowCount - StartTime);

		//�o�ߎ��Ԃ�0�b�ɂȂ�����(�E�E�E3,2,1 �ŏI�������邽�� <=)
		if (ElaTime <= 0)
		{
			GameScene = GAME_SCENE_END;	//�G���h�V�[���ֈړ�����

			//BGM������Ă���Ȃ�
			if (CheckSoundMem(Play_BGM.handle) != 0)
			{
				StopSoundMem(Play_BGM.handle);		//BGM���~�߂�
			}

			//�����J�E���g�_�E�����s�����ߌ��ɖ߂�
			First_flg = TRUE;
			CountDown = TRUE;

			return;
		}

		//��莞�ԂŐl�Ԃ��o�������鏈��
		if (NowCount2 - ConstantTime >= EASY)
		{
			Human_Cons[TimeDraw].IsDraw = TRUE;		//�`��ł���
			TimeDraw++;								//���̔z���
			ConstantTime = GetNowCount();			//�ēx���Ԃ��擾���ă��Z�b�g
		}
		//�v���C���[�̃L�[����(4�����J�[�\���L�[�ōs��)
		if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)	  //��J�[�\���L�[
		{
			if (player.image.y >= 0)  //��ʊO�łȂ��Ȃ�
				player.image.y -= player.speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)  //���J�[�\���L�[
		{
			if (player.image.y + player.image.height <= GAME_HEIGHT) //��ʊO�łȂ��Ȃ�
				player.image.y += player.speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)  //���J�[�\���L�[
		{
			if (player.image.x >= 0)  //��ʊO�łȂ��Ȃ�
				player.image.x -= player.speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) //�E�J�[�\���L�[
		{
			if (player.image.x + player.image.width <= GAME_WIDTH)  //��ʊO�łȂ��Ȃ�
				player.image.x += player.speed;
		}

		//�����蔻��
		COLLPROC();
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImagePlayBG.x, ImagePlayBG.y, ImagePlayBG.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}
	
	DrawString(0, 0, "�v���C���(�X�y�[�X�L�[�������Ă�������)", GetColor(255, 255, 255));

	if (First_flg)  //�ŏ��̃J�E���g�_�E��
	{
		DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", (ElaTime / 1000) + 1);
	}
	else
	{
		//�������Ԃ̕\��
		//1000�Ŋ����āu�~���b�P�ʁv����u�b�P�ʁv��
		//0 ���o�Ă��Ă��܂��̂� +1����
		if ((ElaTime / 1000 + 1) <= 3)  //�c�� �b�͐Ԏ��ɂ���
			DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", (ElaTime / 1000) + 1);
		else
			DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", (ElaTime / 1000) + 1);

		//�����蔻��̕`��(�f�o�b�O�p)
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//�ǂȂ��
				if (mapData[tate][yoko] == w)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
				}
				//�ʘH�Ȃ��
				if (mapData[tate][yoko] == t)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 0, 255), FALSE);
				}
			}
		}

		//���l��(�q)�̕`�恫
		//�ŏ��ɏo������p
		for (int i = 0; i < 5; i++)
		{
			if(IMAGEHuman[i].IsDraw == TRUE)
				DrawGraph(IMAGEHuman[i].image.x, IMAGEHuman[i].image.y, IMAGEHuman[i].image.handle, TRUE);
		}
		//��莞�Ԃŏo������p
		for (int i = 0; i < 15; i++)
		{
			if (Human_Cons[i].IsDraw == TRUE)
				DrawGraph(Human_Cons[i].Humanimage.x, Human_Cons[i].Humanimage.y, Human_Cons[i].Humanimage.handle, TRUE);
		}

		//�v���C���[��`��
		DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

		//�v���C���[�̓����蔻���`��(�f�o�b�O�p)
		DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);
	}

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

	//�v���C���[�摜
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
	//player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	//player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��
	player.speed = CHARA_SPEED_MIDI;								//�X�s�[�h��ݒ�

	//���l��(�q)�̉摜��
	//�ŏ��ɏo������p
	for (int i = 0; i < 5; i++)  //�ǂݍ���
	{
		strcpy_s(IMAGEHuman[i].image.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 5; i++)
	{
		//�n���h���̎擾
		IMAGEHuman[i].image.handle = LoadGraph(IMAGEHuman[i].image.path);
		if (IMAGEHuman[i].image.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�傫���̎擾
		GetGraphSize(IMAGEHuman[i].image.handle, &IMAGEHuman[i].image.width, &IMAGEHuman[i].image.height);
		IMAGEHuman[i].IsDraw = TRUE;
	}
	//��莞�Ԃŕ`�悷��p
	for (int i = 0; i < 15; i++)  //�ǂݍ���
	{
		strcpy_s(Human_Cons[i].Humanimage.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 15; i++)
	{
		//�n���h���̎擾
		Human_Cons[i].Humanimage.handle = LoadGraph(Human_Cons[i].Humanimage.path);
		if (Human_Cons[i].Humanimage.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�傫���̎擾
		GetGraphSize(Human_Cons[i].Humanimage.handle, &Human_Cons[i].Humanimage.width, &Human_Cons[i].Humanimage.height);
		Human_Cons[i].IsDraw = FALSE;
	}

	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,								//�}�b�v�`�b�v�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,	//�������鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,				//�摜�𕪊����镝�ƍ���
		&mapChip.handle[0]);						//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map[tate][yoko].kind = mapData[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W���擾
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageStartBG.handle);		//�X�^�[�g��ʂ̔w�i
	DeleteGraph(ImageTitle.handle);			//�^�C�g�����S
	DeleteGraph(ImagePlayBG.handle);		//�v���C��ʂ̔w�i

	DeleteGraph(player.image.handle);		//�v���C���[�摜

	DeleteGraph(ImageHuman.handle);			//�l��(�q)�̍폜

	for (int i = 0; i < 5; i++)				//�ŏ��ɏo������p
	{
		DeleteGraph(IMAGEHuman[i].image.handle);
	}

	for (int i = 0; i < 15; i++)			//��莞�Ԃŏo������p
	{
		DeleteGraph(Human_Cons[i].Humanimage.handle);
	}

	//�}�b�v�`�b�v�̍폜
	for (int num = 0; num < MAP_DIV_NUM; num++)
	{
		DeleteGraph(mapChip.handle[num]);
	}

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

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_MAP_PLAYER_COLL(RECT player)
{
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
				if (map[tate][yoko].kind == w) { return TRUE; }
			}
		}
	}
	
	return FALSE;
}

int MY_CHECK_HUMAN_PLAYER_COLL(RECT player)
{
	for (int i = 0; i < 5; i++)
	{
		if (MY_CHECK_RECT_COLL(player, IMAGEHuman[i].Human_Coll) == TRUE)
		{
			return 1;
		}
	}

	return 0;
}

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
}

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
VOID COLLPROC(VOID)
{
	//�v���C���[�̓����蔻��̐ݒ�
	player.coll.left = player.image.x;
	player.coll.top = player.image.y;
	player.coll.right = player.image.x + player.image.width;
	player.coll.bottom = player.image.y + player.image.height;

	//�v���C���[�ƕǂ��������Ă�����
	if (MY_CHECK_MAP_PLAYER_COLL(player.coll) == TRUE)
	{
		//�ʂ蔲���s��
		player.image.x = player.collBeforePt.x;		//������ꏊ��X���W����
		player.image.y = player.collBeforePt.y;		//������ꏊ��Y���W����
	}

	//�v���C���[�ƕǂ��������Ă�����
	if (MY_CHECK_HUMAN_PLAYER_COLL(player.coll) == 1)
	{
		//�ʂ蔲���s��
		player.image.x = player.collBeforePt.x;		//������ꏊ��X���W����
		player.image.y = player.collBeforePt.y;		//������ꏊ��Y���W����
	}

	//��ɍ��W���擾���Ă���
	player.collBeforePt.x = player.image.x;
	player.collBeforePt.y = player.image.y;

	return;
}