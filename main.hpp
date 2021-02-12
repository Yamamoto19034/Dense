#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

//########## �}�N����` ##########
#define GAME_WIDTH				960		//��ʂ̉��̑傫��
#define GAME_HEIGHT				660		//��ʂ̏c�̑傫��
#define GAME_COLOR				32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR			0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME		"���ł��I ���ڂ�h���I"	//�E�B���h�E�̃^�C�g��

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
#define IMAGE_MITUDESU_PATH		TEXT(".\\IMAGE\\mitudesu_pic.png")		//�u���ł��v�̉摜
#define IMAGE_HUMAN_PATH		TEXT(".\\IMAGE\\human.png")				//�l��(�q)�̕`��
#define IMAGE_CLEAR_PATH		TEXT(".\\IMAGE\\GameClear.png")			//�Q�[���N���A���S
#define IMAGE_OVER_PATH			TEXT(".\\IMAGE\\GameOver.png")			//�Q�[���I�[�o�[���S
#define IMAGE_GAME_EXP_PATH		TEXT(".\\IMAGE\\Game_Exp.png")			//�Q�[�������摜
#define IMAGE_EXP_BUTTON_PATH	TEXT(".\\IMAGE\\expButton.png")			//������ʂ֑����{�^��
#define IMAGE_BACK_BUTTON_PATH	TEXT(".\\IMAGE\\backButton.png")		//�߂�𑣂��{�^��
#define IMAGE_EASY_BUTTON_PATH	TEXT(".\\IMAGE\\push1_easy.png")		//easy���[�h�𑣂��{�^��
#define IMAGE_HARD_BUTTON_PATH	TEXT(".\\IMAGE\\push2_hard.png")		//hard���[�h�𑣂��{�^��
#define IMAGE_HIGH_SCORE_PATH	TEXT(".\\IMAGE\\highscore.png")			//�n�C�X�R�A�̉摜
#define IMAGE_KEY_EXP_PATH		TEXT(".\\IMAGE\\Key_Exp.png")			//�L�[��������摜
#define IMAGE_KEY_BUTTON_PATH	TEXT(".\\IMAGE\\keyButton.png")			//�L�[��������摜�֑����{�^��

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
#define MUSIC_START_BGM_PATH	 TEXT(".\\MUSIC\\waiting_room.mp3")		//�X�^�[�g��ʂ�BGM
#define MUSIC_PLAY_BGM_PATH		 TEXT(".\\MUSIC\\Green_Life.mp3")		//�v���C��ʂ�BGM
#define SOUND_EFFECT_MITU_PATH	 TEXT(".\\MUSIC\\mitudesu.mp3")			//�u���ł��v
#define MUSIC_CLEAR_BGM_PATH	 TEXT(".\\MUSIC\\Breakfast.mp3")		//GameClear����BGM
#define MUSIC_OVER_BGM_PATH		 TEXT(".\\MUSIC\\�͗t�F.mp3")			//GameOver����BGM
#define SOUND_EFFECT_BUTTON_PATH TEXT(".\\MUSIC\\decision15.mp3")		//�{�^�����������Ƃ��̌��ʉ�
#define SOUND_EFFECT_INFE_PATH	 TEXT(".\\MUSIC\\poison.mp3")			//���������Ƃ��̌��ʉ�

//���Ԋ֘A
#define TIMELIMIT				60 * 1000		//�������ԁA60�b��
#define EASY_APPE_TIME			3 * 1000		//�l�Ԃ��o�������鎞�ԊԊu(Easy)
#define HARD_APPE_TIME			2 * 1000		//�l�Ԃ��o�������鎞�ԊԊu(Hard)
#define EASY_CONTACT_TIME		8 * 1000		//�ڂ��Ă��鎞�ԁA8�b��(Easy)
#define HARD_CONTACT_TIME		10 * 1000		//�ڂ��Ă��鎞�ԁA10�b��(Hard)
#define DRAW_TIME				0.75 * 1000		//�`�悷�鎞��

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
	GAME_SCENE_EXP,
	GAME_SCENE_KEY,
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

typedef struct STRUCT_MOUSE 
{
	int InputValue = 0;		//GetMouseInput�̒l������
	iPOINT Point;			//�}�E�X�̍��W������
	iPOINT OldPoint;		//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };   //�}�E�X�̃{�^������(���O)������
	int Button[MOUSE_BUTTON_CODE] = { 0 };		//�}�E�X�̃{�^�����͂�����
}MOUSE;

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

//�}�E�X�̍��W���擾
MOUSE mouse;

FONT Nikkyou;					//�^�C�}�[�p
FONT CD_Nikkyou;				//�ŏ��̃J�E���g�_�E���p
FONT SCORE_Nikkyou;				//�X�R�A�\���p

int GameScene;					//�Q�[���V�[�����Ǘ�

//�摜�֘A
IMAGE ImageBG;					//�X�^�[�g��ʁE�G���h��ʂ̔w�i
IMAGE ImageTitle;				//�^�C�g�����S
IMAGE ImagePushEnter;			//�L�[����𑣂��{�^��
IMAGE ImagePlayBG;				//�v���C��ʂ̔w�i
IMAGE ImageMitudesu;			//�u���ł��v�̉摜
IMAGE ImageHuman;				//�l��(�q)�̕`��
IMAGE ImageClear;				//�Q�[���N���A���S
IMAGE ImageOver;				//�Q�[���I�[�o�[���S
IMAGE ImageGameExp;				//�Q�[�������摜
IMAGE ImageExpButton;			//������ʂ֑����{�^��
IMAGE ImageBackButton;			//�߂�𑣂��{�^��
IMAGE ImageEasyButton;			//easy���[�h�𑣂��{�^��
IMAGE ImageHardButton;			//hard���[�h�𑣂��{�^��
IMAGE ImageHighScore;			//�n�C�X�R�A�̉摜
IMAGE ImageKeyExp;				//�L�[��������摜
IMAGE ImageKeyButton;			//�L�[��������摜�֑����{�^��

HUMAN IMAGEHuman[5];			//�X�^�[�g���ɍŏ��̐l�Ԃ�`��(5�l����)
HUMAN_CONSTANT Human_Cons[30];	//��莞�Ԃ��Ƃɏo������p�̐l�Ԃ�z��ŊǗ�
int TimeDraw = 0;				//Human_Cons�̔z��̓Y����

CHARA player;					//�v���C���[

BOOL Mitudesu_Ent = FALSE;		//�`��ł��邩�ۂ�

//���y�֘A
MUSIC Start_BGM;				//�X�^�[�g��ʂ̔w�i
MUSIC Play_BGM;					//�v���C��ʂ̔w�i
MUSIC Mitu_SF;					//�u���ł��v(SF = Sound Effect)
MUSIC Clear_BGM;				//GameClear����BGM
MUSIC Over_BGM;					//GameOver����BGM
MUSIC Button_SF;				//�{�^�����������Ƃ��̌��ʉ�
MUSIC Infe_SF;					//���������Ƃ��̌��ʉ�

//���Ԋ֘A
int StartTime = 0;				//�v���J�n����
int ElaTime = 0;				//�c�莞��
int CDTimeLimit = 0;			//�J�E���g�_�E���p�̐�������(CD = Count Down)
int TimeLimit = 0;				//��������
BOOL First_flg = TRUE;			//�Q�[���ɓ���ۂ̃J�E���g�_�E��������
BOOL CountDown = TRUE;			//�J�E���g�_�E��������ۂ̊���Ԃ��m�ۂ���
int Crit_AppeTime = 0;			//��莞�ԗp�̊����(�o�� = Appearance)
int AppeTime = 0;				//���b�ŏo�������邩���i�[����
double DrawTime = 0;			//�`��p�̊����
int ContactTime = 0;			//�l�ԓ��m���ڂ��鎞��

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

//�X�R�A�֘A
int Score = 0;						//�X�R�A
int HighScore_Easy = -999;			//Easy���[�h�̃n�C�X�R�A���i�[
int HighScore_Hard = -999;			//Hard���[�h�̃n�C�X�R�A���i�[
BOOL PushEasyMode = FALSE;			//Easy���[�h��I��������
BOOL PushHardMode = FALSE;			//Hard���[�h��I��������
BOOL Update_EasyScore = FALSE;		//Easy���[�h�̃n�C�X�R�A���X�V���ꂽ��
BOOL Update_HardScore = FALSE;		//Hard���[�h�̃n�C�X�R�A���X�V���ꂽ��

//######�v���g�^�C�v�錾######
VOID MY_FPS_UPDATE(VOID);					//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);						//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);						//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);			//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);						//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_DOWN_1SECOND(int);				//�L�[�������Ă��邩(�������ςȂ�����p�^�[��)

VOID MY_MOUSE_UPDATE(VOID);					//�}�E�X�̓��͏����X�V����
BOOL MY_MOUSE_DOWN(int);					//�{�^���������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����

BOOL MY_FONT_INSTALL_ONCE(VOID);			//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID);			//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
BOOL MY_FONT_CREATE(VOID);					//�t�H���g���쐬����
VOID MY_FONT_DELETE(VOID);					//�t�H���g���폜����

VOID MY_START(VOID);						//�X�^�[�g���
VOID MY_START_PROC(VOID);					//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);					//�X�^�[�g��ʂ̕`��

VOID MY_EXP(VOID);							//�������
VOID MY_EXP_PROC(VOID);						//������ʂ̏���
VOID MY_EXP_DRAW(VOID);						//������ʂ̕`��

VOID MY_KEY_EXP(VOID);						//�L�[����������
VOID MY_KEY_EXP_PROC(VOID);					//�L�[���������ʂ̏���
VOID MY_KEY_EXP_DRAW(VOID);					//�L�[���������ʂ̕`��

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

VOID GOTO_PLAY(VOID);						//�v���C��ʂɍs���ۂ̏���
VOID GOTO_EASY_MODE(VOID);					//Easy���[�h�֍s���ۂ̏���
VOID GOTO_HARD_MODE(VOID);					//Hard���[�h�֍s���ۂ̏���
VOID GOTO_START(VOID);						//�X�^�[�g��ʂɍs���ۂ̏���
VOID GOTO_START_EXP(VOID);					//�X�^�[�g��ʂɍs���ۂ̏���(������ʂ���)

VOID PLAYER_ATTACK(VOID);					//�v���C���[�̍U���Ɋւ���֐�
VOID PLAYER_MOVE(VOID);						//�v���C���[�̈ړ��Ɋւ���֐�

VOID GAMECLEAR_IF(VOID);					//�Q�[���N���A�Ɋւ���֐�
VOID GAMEOVER_IF(VOID);						//�Q�[���I�[�o�[�Ɋւ���֐�