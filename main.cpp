/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�������[�v

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

//########## �}�N����` ##########
#define GAME_WIDTH				960		//��ʂ̉��̑傫��
#define GAME_HEIGHT				660		//��ʂ̏c�̑傫��
#define GAME_COLOR				32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR			0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME		"GAME TITLE"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS				60  //FPS�̐��l

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE		129

//�t�H���g�̃p�X�̒���
#define FONT_PATH_MAX			255  //255�����܂�

//�t�H���g
#define FONT_NIKK_PATH			TEXT(".\\FONT\\NikkyouSans-B6aV.ttf")
#define FONT_NIKK_NAME			TEXT("Nikkyou Sans")

#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

//�p�X�̒���
#define PATH_MAX				255

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�摜�̃p�X
#define IMAGE_BG_PATH			TEXT(".\\IMAGE\\BG.png")				//�X�^�[�g��ʁE�G���h��ʂ̔w�i
#define IMAGE_TITLE_PATH		TEXT(".\\IMAGE\\title.png")				//�^�C�g�����S
#define IMAGE_PUSH_ENTER_PATH	TEXT(".\\IMAGE\\pushenter.png")			//�L�[����𑣂��{�^��
#define IMAGE_PLAY_BG_PATH		TEXT(".\\IMAGE\\BG_play.png")			//�v���C��ʂ̔w�i
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\Player.png")			//�L�����N�^�[�̉摜
#define IMAGE_HUMAN_PATH		TEXT(".\\IMAGE\\human.png")				//�l��(�q)�̕`��
#define IMAGE_CLEAR_PATH		TEXT(".\\IMAGE\\GameClear.png")			//�Q�[���N���A���S
#define IMAGE_OVER_PATH			TEXT(".\\IMAGE\\GameOver.png")			//�Q�[���I�[�o�[���S

//�}�b�v�`�b�v�֘A
#define GAME_MAP_TATE_MAX		11  //�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX		16  //�}�b�v�̉��̐�

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip.png")

#define MAP_DIV_WIDTH			60  //�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT			60  //�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE			10  //�摜���c�ɕ������鐔
#define MAP_DIV_YOKO			2   //�摜�����ɕ������鐔
#define MAP_DIV_NUM				MAP_DIV_TATE * MAP_DIV_YOKO  //�摜�𕪊����鑍��

#define IMAGE_HUMAN_WIDTH		60	//�l�Ԃ̉摜�̕��̑傫��
#define IMAGE_HUMAN_HEIGHT		60	//�l�Ԃ̉摜�̍����̑傫��

//�G���[���b�Z�[�W
#define START_ERR_TITLE			TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION		TEXT("�X�^�[�g�ʒu�����܂��Ă܂���")

//�G���[���b�Z�[�W
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//���y�̃p�X
#define MUSIC_START_BGM_PATH	TEXT(".\\MUSIC\\waiting_room.mp3")		//�X�^�[�g��ʂ�BGM
#define MUSIC_PLAY_BGM_PATH		TEXT(".\\MUSIC\\Green_Life.mp3")		//�v���C��ʂ�BGM
#define SOUND_EFFECT_MITU_PATH	TEXT(".\\MUSIC\\mitudesu.mp3")			//�u���ł��v
#define MUSIC_CLEAR_BGM_PATH	TEXT(".\\MUSIC\\Breakfast.mp3")			//GameClear����BGM
#define MUSIC_OVER_BGM_PATH		TEXT(".\\MUSIC\\�͗t�F.mp3")			//GameOver����BGM

//���Ԋ֘A
#define TIMELIMIT				60 * 1000		//�������ԁA60�b��
#define EASY					3 * 1000
#define CONTACT_TIME			10 * 1000		//�ڂ��Ă��鎞�ԁA3�b��

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
	CHARA_SPEED_MIDI = 4,
	CHARA_SPEED_HIGI = 3,
};  //�L�����N�^�[�̃X�s�[�h

enum GAME_JUDE {
	JUDE_CLEAR,  //����
	JUDE_OVER    //���s
};  //�N���A�����s��

//�t�H���g�\����
typedef struct STRUCT_FONT
{
	char path[FONT_PATH_MAX];	//�p�X
	char name[FONT_PATH_MAX];   //�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v
}FONT;

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

	BOOL IsContact;					//�ڂ��Ă��邩�ۂ�
}HUMAN;  //�ŏ��ɏo������p

typedef struct STRUCT_HUMAN_TIME
{
	IMAGE Humanimage;				//�C���[�W�\����
	BOOL IsDraw;					//�`��ł��邩�ۂ�

	RECT HumanCons_Coll;			//�����蔻��

	BOOL IsContact;					//�ڂ��Ă��邩�ۂ�

	int ContactTime = 0;			//�ڂ��Ă��鎞��

	int NowCount = 0;				//�l�ԓ��m�̐ڂ��Ă��鎞�ԗp

	BOOL Contact_First = TRUE;		//����Ԃ��擾����p
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

FONT Nikkyou;
FONT CD_Nikkyou;				//�ŏ��̃J�E���g�_�E���p

int GameScene;					//�Q�[���V�[�����Ǘ�

//�摜�֘A
IMAGE ImageBG;					//�X�^�[�g��ʁE�G���h��ʂ̔w�i
IMAGE ImageTitle;				//�^�C�g�����S
IMAGE ImagePushEnter;			//�L�[����𑣂��{�^��
IMAGE ImagePlayBG;				//�v���C��ʂ̔w�i
IMAGE ImageHuman;				//�l��(�q)�̕`��
IMAGE ImageClear;				//�Q�[���N���A���S
IMAGE ImageOver;				//�Q�[���I�[�o�[���S

HUMAN IMAGEHuman[5];			//�X�^�[�g���ɍŏ��̐l�Ԃ�`��(5�l����)
HUMAN_CONSTANT Human_Cons[20];	//��莞�Ԃ��Ƃɏo������p�̐l�Ԃ�z��ŊǗ�
int TimeDraw = 0;				//Human_Cons�̔z��̓Y����

CHARA player;					//�L�����N�^�[

//���y�֘A
MUSIC Start_BGM;				//�X�^�[�g��ʂ̔w�i
MUSIC Play_BGM;					//�v���C��ʂ̔w�i
MUSIC Mitu_SF;					//�u���ł��v(SF = Sound Effect)
MUSIC Clear_BGM;				//GameClear����BGM
MUSIC Over_BGM;					//GameOver����BGM

//���Ԋ֘A
int StartTime = 0;				//�v���J�n����
int ElaTime = 0;				//�c�莞��
int CDTimeLimit = 0;			//�J�E���g�_�E���p�̐�������(CD = Count Down)
int TimeLimit = 0;				//��������
BOOL First_flg = TRUE;			//�Q�[���ɓ���ۂ̃J�E���g�_�E��������
BOOL CountDown = TRUE;			//�J�E���g�_�E��������ۂ̊���Ԃ��m�ۂ���
int AppeTime = 0;				//��莞�ԗp�̊����(�o�� = Appearance)

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

//GameClear��GameOver�����肷��
int Jude;

//######�v���g�^�C�v�錾######
VOID MY_FPS_UPDATE(VOID);					//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);						//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);						//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);			//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);						//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_DOWN_1SECOND(int);				//�L�[�������Ă��邩(�������ςȂ�����p�^�[��)

BOOL MY_FONT_INSTALL_ONCE(VOID);			//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID);			//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
BOOL MY_FONT_CREATE(VOID);					//�t�H���g���쐬����
VOID MY_FONT_DELETE(VOID);					//�t�H���g���폜����

VOID MY_START(VOID);						//�X�^�[�g���
VOID MY_START_PROC(VOID);					//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);					//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);							//�v���C���
VOID MY_PLAY_PROC(VOID);					//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);					//�v���C��ʂ̕`��

VOID MY_END(VOID);							//�G���h���
VOID MY_END_PROC(VOID);						//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);						//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);					//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);					//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);					//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);					//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_MAP_PLAYER_COLL(RECT);		//�}�b�v�ƃv���C���[�̓����蔻�������֐�
int MY_CHECK_HUMAN_PLAYER_COLL(RECT);		//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_HUMAN_HUMAN_COLL(RECT, int);	//�l�ԓ��m�̓����蔻�������֐�
VOID MY_CHECK_INFEHUMAN_PLAYER_COLL(RECT);	//�������Ă���v���C���[�Ɛڂ��Ă��邩�𔻒肷��֐�
BOOL MY_CHECK_RECT_COLL(RECT, RECT);		//�̈�̓����蔻�������֐�
VOID COLLPROC(VOID);						//�����蔻�������֐�

VOID MY_INIT(VOID);							//����������֐�

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);		//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);						//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }

	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return - 1; }

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
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

	//�t�H���g�n���h����j��
	MY_FONT_DELETE();

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//�ꎞ�I�ɃC���X�g�[�������t�H���g���A���C���X�g�[��
	MY_FONT_UNINSTALL_ONCE();

	//���y�n���h����j��
	MY_DELETE_MUSIC();

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//FPS�l���v���A�X�V����֐�
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

//FPS�l��`�悷��֐�
VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//FPS�l���v�����A�҂֐�
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

//�L�[�̓��͏�Ԃ��X�V����֐�
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];  //�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	//���O�̃L�[���͂�����Ă���
	for (int i = 0; i < 256; ++i)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);		//�S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; ++i)
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

//�L�[�������Ă��邩(�������ςȂ�����p�^�[��)
BOOL MY_KEY_DOWN_1SECOND(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] == 1)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_NIKK_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_NIKK_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_NIKK_PATH, FR_PRIVATE, NULL);

	return;
}

//�t�H���g��ǂݍ��ފ֐�
BOOL MY_FONT_CREATE(VOID)
{
	//�t�H���g�f�[�^���쐬
	strcpy_s(Nikkyou.path, sizeof(Nikkyou.path), FONT_NIKK_PATH);	//�p�X���R�s�[
	strcpy_s(Nikkyou.name, sizeof(Nikkyou.name), FONT_NIKK_NAME);	//�t�H���g�����R�s�[
	Nikkyou.handle = -1;							//�n���h����������
	Nikkyou.size = 50;								//�T�C�Y: 50
	Nikkyou.bold = 1;								//����: 1
	Nikkyou.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//�A���`�G�C���A�V���O�t���̃t�H���g

	//�t�H���g�n���h���쐬
	Nikkyou.handle = CreateFontToHandle(Nikkyou.name, Nikkyou.size, Nikkyou.bold, Nikkyou.type);
	//�t�H���g�n���h���쐬�ł��Ȃ��Ƃ��A�G���[
	if (Nikkyou.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_NIKK_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }


	//�t�H���g�f�[�^���쐬(�J�E���g�_�E���p)
	strcpy_s(CD_Nikkyou.path, sizeof(CD_Nikkyou.path), FONT_NIKK_PATH);	//�p�X���R�s�[
	strcpy_s(CD_Nikkyou.name, sizeof(CD_Nikkyou.name), FONT_NIKK_NAME);	//�t�H���g�����R�s�[
	CD_Nikkyou.handle = -1;								//�n���h����������
	CD_Nikkyou.size = 300;								//�T�C�Y: 300
	CD_Nikkyou.bold = 5;								//����: 5
	CD_Nikkyou.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//�A���`�G�C���A�V���O�t���̃t�H���g

	//�t�H���g�n���h���쐬
	CD_Nikkyou.handle = CreateFontToHandle(CD_Nikkyou.name, CD_Nikkyou.size, CD_Nikkyou.bold, CD_Nikkyou.type);
	//�t�H���g�n���h���쐬�ł��Ȃ��Ƃ��A�G���[
	if (CD_Nikkyou.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_NIKK_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	return TRUE;
}

//�t�H���g���폜����֐�
VOID MY_FONT_DELETE(VOID)
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(CD_Nikkyou.handle);	//�t�H���g�̃n���h�����폜

	return;
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

		//�v���C���[�̉摜�̈ʒu��ݒ肷��
		player.image.x = startPt.x;
		player.image.y = startPt.y;

		//�v���C��ʂɌ����ď���
		TimeLimit = TIMELIMIT;			//�������Ԃ�ݒ�
		GameScene = GAME_SCENE_PLAY;	//�v���C�V�[���ֈړ�����

		//�ŏ��ɏo������p
		//for (int i = 0; i < 5; ++i)
		//{
		//	//�����ŕ`��ʒu�����߂�
		//	int x = GetRand(15);
		//	int y = GetRand(10);

		//	//���W�ʒu���ʘH�Ȃ�(�ǂƃX�^�[�g�ʒu�ɂ͕`�悵�Ȃ�)
		//	if (mapData[x][y] == t)
		//	{
		//		IMAGEHuman[i].IsDraw = TRUE;					//�\��OK
		//		IMAGEHuman[i].image.x = IMAGE_HUMAN_WIDTH * x;
		//		IMAGEHuman[i].image.y = IMAGE_HUMAN_HEIGHT * y;

		//		//�����œ����蔻��̐ݒ������
		//		IMAGEHuman[i].Human_Coll.left = IMAGEHuman[i].image.x + 1;
		//		IMAGEHuman[i].Human_Coll.top = IMAGEHuman[i].image.y + 1;
		//		IMAGEHuman[i].Human_Coll.right = IMAGEHuman[i].image.x + IMAGE_HUMAN_WIDTH - 1;
		//		IMAGEHuman[i].Human_Coll.bottom = IMAGEHuman[i].image.y + IMAGE_HUMAN_HEIGHT - 1;
		//	}
		//}
		//�����ŕ`��ʒu�����߂�(��莞�Ԃŏo������p)
		for (int i = 0; i < 20; ++i)
		{
			int x = GetRand(15);
			int y = GetRand(10);

			Human_Cons[i].Humanimage.x = IMAGE_HUMAN_WIDTH * x;
			Human_Cons[i].Humanimage.y = IMAGE_HUMAN_HEIGHT * y;
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
	DrawGraph(ImageBG.x, ImageBG.y, ImageBG.handle, TRUE);
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);
	DrawGraph(ImagePushEnter.x, ImagePushEnter.y, ImagePushEnter.handle, TRUE);
	//DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������Ă�������)", GetColor(255, 255, 255));

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

	//�X�y�[�X�L�[��������A�G���h�V�[���ֈړ�����(�f�o�b�O�p)
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(Play_BGM.handle) != 0)
		{
			StopSoundMem(Play_BGM.handle);  //BGM���~�߂�
		}

		MY_INIT();
		Jude = JUDE_CLEAR;

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
			AppeTime = GetNowCount();		//�{�ԂɌ����Ċ���Ԃ��擾
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

			//����������
			MY_INIT();
			Jude = JUDE_CLEAR;

			return;
		}

		//��莞�ԂŐl�Ԃ��o�������鏈��
		if (NowCount2 - AppeTime >= EASY)
		{
			Human_Cons[TimeDraw].IsDraw = TRUE;		//�`��ł���

			//�����蔻���ݒ肷��
			Human_Cons[TimeDraw].HumanCons_Coll.left = Human_Cons[TimeDraw].Humanimage.x - 5;
			Human_Cons[TimeDraw].HumanCons_Coll.top = Human_Cons[TimeDraw].Humanimage.y - 5;
			Human_Cons[TimeDraw].HumanCons_Coll.right = Human_Cons[TimeDraw].Humanimage.x + IMAGE_HUMAN_WIDTH + 5;
			Human_Cons[TimeDraw].HumanCons_Coll.bottom = Human_Cons[TimeDraw].Humanimage.y + IMAGE_HUMAN_HEIGHT + 5;

			TimeDraw++;								//���̔z���
			AppeTime = GetNowCount();			//�ēx���Ԃ��擾���ă��Z�b�g
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

		//�v���C���[�̍U��
		if (MY_KEY_DOWN_1SECOND(KEY_INPUT_RETURN) == TRUE)
		{
			//���ʉ�������Ă��Ȃ��Ȃ�
			if (CheckSoundMem(Mitu_SF.handle) == 0)
			{
				//���ʉ��̉��ʂ�������
				ChangeVolumeSoundMem(255 * 80 / 100, Mitu_SF.handle);  //50%�̉��ʂɂ���
				PlaySoundMem(Mitu_SF.handle, DX_PLAYTYPE_BACK);		   //�o�b�N�O���E���h�Đ�
			}

			//�ڂ��Ă邩�m�F
			MY_CHECK_INFEHUMAN_PLAYER_COLL(player.coll);
		}

		//�����蔻��
		COLLPROC();

		//GAME OVER����
		for (int i = 0; i < 20; ++i)
		{
			//�ڂ��Ă���Ȃ� ���� �\������Ă���Ȃ�
			if (Human_Cons[i].IsContact == TRUE && Human_Cons[i].IsDraw == TRUE)
			{
				//���ꂼ��Ŏ��Ԃ��擾����
				Human_Cons[i].NowCount = GetNowCount();

				if (Human_Cons[i].Contact_First)
				{
					//�����ł͊���Ԃ��擾
					Human_Cons[i].ContactTime = GetNowCount();
					Human_Cons[i].Contact_First = FALSE;	//���̏�����1�񂾂�
				}
				
				//�l�ԓ��m����莞�ԁA�ڂ��Ă�����
				if ((Human_Cons[i].NowCount - Human_Cons[i].ContactTime) >= CONTACT_TIME)
				{
					//BGM������Ă���Ȃ�
					if (CheckSoundMem(Play_BGM.handle) != 0)
					{
						StopSoundMem(Play_BGM.handle);		//BGM���~�߂�
					}

					//����������
					MY_INIT();
					Jude = JUDE_OVER;

					//�G���h�V�[���ֈړ�����
					GameScene = GAME_SCENE_END;
				}
			}
		}
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImagePlayBG.x, ImagePlayBG.y, ImagePlayBG.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
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
		DrawFormatStringToHandle(GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2 - 125, GetColor(255, 0, 0), CD_Nikkyou.handle, "%d", (ElaTime / 1000) + 1);
	}
	else
	{
		//�������Ԃ̕\��
		//1000�Ŋ����āu�~���b�P�ʁv����u�b�P�ʁv��
		//0 ���o�Ă��Ă��܂��̂� +1����
		if ((ElaTime / 1000 + 1) <= 3)  //�c��3�b�͐Ԏ��ɂ���
			DrawFormatStringToHandle(GAME_WIDTH - 70, 0, GetColor(255, 0, 0), Nikkyou.handle, "%d", (ElaTime / 1000) + 1);
		else
			DrawFormatStringToHandle(GAME_WIDTH - 70, 0, GetColor(255, 255, 255),  Nikkyou.handle,"%d", (ElaTime / 1000) + 1);

		//�����蔻��̕`��(�f�o�b�O�p)
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
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
		//for (int i = 0; i < 5; ++i)
		//{
		//	if (IMAGEHuman[i].IsDraw == TRUE)  //�`��ł���Ȃ�
		//	{
		//		if (IMAGEHuman[i].IsContact == TRUE)  //�ڂ��Ă���Ȃ�
		//			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);  //�F�𔽓]�����ĕ\��
		//		DrawGraph(IMAGEHuman[i].image.x, IMAGEHuman[i].image.y, IMAGEHuman[i].image.handle, TRUE);
		//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		 //���ɖ߂�
		//	}
		//}
		//��莞�Ԃŏo������p
		for (int i = 0; i < 20; ++i)
		{
			if (Human_Cons[i].IsDraw == TRUE)  //�`��ł���Ȃ�
			{
				if(Human_Cons[i].IsContact == TRUE)  //�ڂ��Ă���Ȃ�
					SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);  //�F�𔽓]�����ĕ\��
				DrawGraph(Human_Cons[i].Humanimage.x, Human_Cons[i].Humanimage.y, Human_Cons[i].Humanimage.handle, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		 //���ɖ߂�
			}
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
	switch (Jude)
	{
	case JUDE_CLEAR:  //�N���A�p�^�[��
		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(Clear_BGM.handle) == 0)
		{
			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 50 / 100, Clear_BGM.handle);  //50%�̉��ʂɂ���
			PlaySoundMem(Clear_BGM.handle, DX_PLAYTYPE_LOOP);		 //�o�b�N�O���E���h�Đ�
		}
		break;

	case JUDE_OVER:  //���s�p�^�[��
		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(Over_BGM.handle) == 0)
		{
			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 50 / 100, Over_BGM.handle);  //50%�̉��ʂɂ���
			PlaySoundMem(Over_BGM.handle, DX_PLAYTYPE_LOOP);		//�o�b�N�O���E���h�Đ�
		}
		break;
	}

	//�G�X�P�[�v�L�[��������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;

		//BGM������Ă���Ȃ�(GameClear)
		if (CheckSoundMem(Clear_BGM.handle) != 0)
		{
			StopSoundMem(Clear_BGM.handle);		//BGM���~�߂�
		}
		//BGM������Ă���Ȃ�(GameOver)
		if (CheckSoundMem(Over_BGM.handle) != 0)
		{
			StopSoundMem(Over_BGM.handle);   //BGM���~�߂�
		}
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	//DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);
	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������Ă�������)", GetColor(255, 255, 255));

	DrawGraph(ImageBG.x, ImageBG.y, ImageBG.handle, TRUE);

	switch (Jude)
	{
	case JUDE_CLEAR:
		DrawGraph(ImageClear.x, ImageClear.y, ImageClear.handle, TRUE);
		break;
	case JUDE_OVER:
		DrawGraph(ImageOver.x, ImageOver.y, ImageOver.handle, TRUE);
		break;
	}

	return;
}

//�摜���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_IMAGE(VOID)
{
	//�X�^�[�g��ʁE�G���h��ʂ̔w�i
	strcpy_s(ImageBG.path, IMAGE_BG_PATH);		//�p�X�̐ݒ�
	ImageBG.handle = LoadGraph(ImageBG.path);		//�ǂݍ���
	if (ImageBG.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBG.handle, &ImageBG.width, &ImageBG.height);	//�摜�̕��ƍ������擾
	ImageBG.x = GAME_WIDTH / 2 - ImageBG.width / 2;			//X�ʒu�����߂�
	ImageBG.y = GAME_HEIGHT / 2 - ImageBG.height / 2;		//Y�ʒu�����߂�

	//�^�C�g���̉摜
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

	//�L�[����𑣂��{�^��(Push Enter Key)
	strcpy_s(ImagePushEnter.path, IMAGE_PUSH_ENTER_PATH);		//�p�X�̐ݒ�
	ImagePushEnter.handle = LoadGraph(ImagePushEnter.path);		//�ǂݍ���
	if (ImagePushEnter.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PUSH_ENTER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePushEnter.handle, &ImagePushEnter.width, &ImagePushEnter.height);	//�摜�̕��ƍ������擾
	ImagePushEnter.x = GAME_WIDTH / 2 - ImagePushEnter.width / 2;			//X�ʒu�����߂�
	ImagePushEnter.y = ImageTitle.y + ImageTitle.height;					//Y�ʒu�����߂�

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
	//player.CenterY = player.image.y + player.image.height / 2;	//�摜�̏c�̒��S��T��
	player.speed = CHARA_SPEED_MIDI;								//�X�s�[�h��ݒ�

	//���l��(�q)�̉摜��
	//�ŏ��ɏo������p
	for (int i = 0; i < 5; ++i)  //�ǂݍ���
	{
		strcpy_s(IMAGEHuman[i].image.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 5; ++i)
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
		IMAGEHuman[i].IsDraw = FALSE;				//�ŏ��͕`�悵�Ȃ�
		IMAGEHuman[i].IsContact = FALSE;			//�ڂ��ĂȂ�
	}

	//��莞�Ԃŕ`�悷��p
	for (int i = 0; i < 20; ++i)  //�ǂݍ���
	{
		strcpy_s(Human_Cons[i].Humanimage.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 20; ++i)
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
		Human_Cons[i].IsDraw = FALSE;				//�ŏ��͕`�悵�Ȃ�
		Human_Cons[i].IsContact = FALSE;			//�ڂ��ĂȂ�
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

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
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
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//�Q�[���N���A���S
	strcpy_s(ImageClear.path, IMAGE_CLEAR_PATH);		//�p�X�̐ݒ�
	ImageClear.handle = LoadGraph(ImageClear.path);		//�ǂݍ���
	if (ImageClear.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_CLEAR_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageClear.handle, &ImageClear.width, &ImageClear.height);	//�摜�̕��ƍ������擾
	ImageClear.x = GAME_WIDTH / 2 - ImageClear.width / 2;			//X�ʒu�����߂�
	ImageClear.y = GAME_HEIGHT / 2 - ImageClear.height / 2;			//Y�ʒu�����߂�

	//�Q�[���I�[�o�[���S
	strcpy_s(ImageOver.path, IMAGE_OVER_PATH);			//�p�X�̐ݒ�
	ImageOver.handle = LoadGraph(ImageOver.path);		//�ǂݍ���
	if (ImageOver.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_OVER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageOver.handle, &ImageOver.width, &ImageOver.height);	//�摜�̕��ƍ������擾
	ImageOver.x = GAME_WIDTH / 2 - ImageOver.width / 2;				//X�ʒu�����߂�
	ImageOver.y = GAME_HEIGHT / 2 - ImageOver.height / 2;			//Y�ʒu�����߂�

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageBG.handle);			//�X�^�[�g��ʁE�G���h��ʂ̔w�i

	DeleteGraph(ImageTitle.handle);			//�^�C�g�����S
	DeleteGraph(ImagePushEnter.handle);		//�L�[����𑣂��{�^��
	DeleteGraph(ImagePlayBG.handle);		//�v���C��ʂ̔w�i

	DeleteGraph(player.image.handle);		//�v���C���[�摜

	DeleteGraph(ImageHuman.handle);			//�l��(�q)�̍폜

	for (int i = 0; i < 5; ++i)				//�ŏ��ɏo������p
	{
		DeleteGraph(IMAGEHuman[i].image.handle);
	}

	for (int i = 0; i < 20; ++i)			//��莞�Ԃŏo������p
	{
		DeleteGraph(Human_Cons[i].Humanimage.handle);
	}

	//�}�b�v�`�b�v�̍폜
	for (int num = 0; num < MAP_DIV_NUM; ++num)
	{
		DeleteGraph(mapChip.handle[num]);
	}

	DeleteGraph(ImageClear.handle);			//�Q�[���N���A���S
	DeleteGraph(ImageOver.handle);

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

	//���ʉ��u���ł��v
	strcpy_s(Mitu_SF.path, SOUND_EFFECT_MITU_PATH);
	Mitu_SF.handle = LoadSoundMem(Mitu_SF.path);
	if (Mitu_SF.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), SOUND_EFFECT_MITU_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(Clear_BGM.path, MUSIC_CLEAR_BGM_PATH);
	Clear_BGM.handle = LoadSoundMem(Clear_BGM.path);
	if (Clear_BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_CLEAR_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(Over_BGM.path, MUSIC_OVER_BGM_PATH);
	Over_BGM.handle = LoadSoundMem(Over_BGM.path);
	if (Over_BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_OVER_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(Start_BGM.handle);
	DeleteSoundMem(Play_BGM.handle);
	DeleteSoundMem(Mitu_SF.handle);
	DeleteSoundMem(Clear_BGM.handle);
	DeleteSoundMem(Over_BGM.handle);

	return;
}

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_MAP_PLAYER_COLL(RECT player)
{
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
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

//�l�Ԃƃv���C���[�̓����蔻��
int MY_CHECK_HUMAN_PLAYER_COLL(RECT player)
{
	for (int i = 0; i < 5; ++i)
	{
		if (MY_CHECK_RECT_COLL(player, IMAGEHuman[i].Human_Coll) == TRUE)
		{
			return 1;
		}
	}

	return 0;
}

//�l�ԓ��m�̓����蔻��
BOOL MY_CHECK_HUMAN_HUMAN_COLL(RECT Human, int order)
{
	//��莞�Ԃŏo������ vs ��莞�Ԃŏo������
	for (int i = 0; i < 20; ++i)
	{
		if (i != order)  //�������͓̂����蔻��̃`�F�b�N�����Ȃ�
		{
			if (MY_CHECK_RECT_COLL(Human, Human_Cons[i].HumanCons_Coll) == TRUE)
			{
				if(Human_Cons[i].IsDraw == TRUE)   //�`�悳��Ă���Ȃ�
					return TRUE;
			}
		}
	}

	//�ŏ��ɏo������ vs ��莞�Ԃŏo������
	for (int i = 0; i < 5; ++i)
	{
		if (MY_CHECK_RECT_COLL(Human, IMAGEHuman[i].Human_Coll) == TRUE)
		{
			if (IMAGEHuman[i].IsDraw == TRUE)       //�`�悳��Ă���Ȃ�
			{
				IMAGEHuman[i].IsContact = TRUE;		//�ڂ��Ă���
				return TRUE;
			}
		}
	}

	return FALSE;
}

//�������Ă���v���C���[�Ɛڂ��Ă��邩�𔻒肷��֐�
VOID MY_CHECK_INFEHUMAN_PLAYER_COLL(RECT player)
{
	for (int i = 0; i < 20; ++i)
	{
		if (MY_CHECK_RECT_COLL(player, Human_Cons[i].HumanCons_Coll) == TRUE)
		{
			//�ڂ��Ă���Ȃ犎�`�悳��Ă���Ȃ�
			if (Human_Cons[i].IsContact == TRUE && Human_Cons[i].IsDraw == TRUE)
			{
				//��ʂ������
				Human_Cons[i].IsContact = FALSE;
				Human_Cons[i].IsDraw = FALSE;
			}
		}
	}

	/*for (int i = 0; i < 5; ++i)
	{
		if (MY_CHECK_RECT_COLL(player, IMAGEHuman[i].Human_Coll) == TRUE)
		{
			if (IMAGEHuman[i].IsContact == TRUE && IMAGEHuman[i].IsDraw == TRUE)
			{
				IMAGEHuman[i].IsContact = FALSE;
				IMAGEHuman[i].IsDraw = FALSE;
			}
		}
	}*/

	return;
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

//�����蔻�������֐�
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

	//�v���C���[�Ɛl�Ԃ��������Ă�����
	if (MY_CHECK_HUMAN_PLAYER_COLL(player.coll) == 1)
	{
		//�ʂ蔲���s��
		player.image.x = player.collBeforePt.x;		//������ꏊ��X���W����
		player.image.y = player.collBeforePt.y;		//������ꏊ��Y���W����
	}

	//��ɍ��W���擾���Ă���
	player.collBeforePt.x = player.image.x;
	player.collBeforePt.y = player.image.y;

	for (int i = 0; i < 20; ++i)
	{
		//�l�ԓ��m���������Ă�����
		if (MY_CHECK_HUMAN_HUMAN_COLL(Human_Cons[i].HumanCons_Coll, i) == TRUE)
		{
			if(Human_Cons[i].IsDraw == TRUE)     //�`�悳��Ă���Ȃ�
				Human_Cons[i].IsContact = TRUE;  //�ڂ��Ă�
		}
	}

	return;
}

//����������֐�
VOID MY_INIT(VOID)
{
	/*for (int i = 0; i < 5; ++i)
	{
		IMAGEHuman[i].IsContact = FALSE;
		IMAGEHuman[i].IsDraw = FALSE;
		IMAGEHuman[i].Human_Coll.left = 0;
		IMAGEHuman[i].Human_Coll.top = 0;
		IMAGEHuman[i].Human_Coll.right = 0;
		IMAGEHuman[i].Human_Coll.bottom = 0;
	}*/

	for (int i = 0; i < 20; ++i) 
	{
		Human_Cons[i].Contact_First = TRUE;
		//�S�Ĕ�\����
		Human_Cons[i].IsContact = FALSE;
		Human_Cons[i].IsDraw = FALSE;
	}

	TimeDraw = 0;

	First_flg = TRUE;
	CountDown = TRUE;

	return;
}