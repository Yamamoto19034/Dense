#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_WIDTH				960		//画面の横の大きさ
#define GAME_HEIGHT				660		//画面の縦の大きさ
#define GAME_COLOR				32		//画面のカラービット

#define GAME_WINDOW_BAR			0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME		"密です！ 密接を防げ！"	//ウィンドウのタイトル

#define GAME_FPS				60  //FPSの数値

//マウスのボタン
#define MOUSE_BUTTON_CODE		129

//フォントのパスの長さ
#define FONT_PATH_MAX			255  //255文字まで

//フォント
#define FONT_NIKK_PATH			TEXT(".\\FONT\\NikkyouSans-B6aV.ttf")
#define FONT_NIKK_NAME			TEXT("Nikkyou Sans")

#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

//パスの長さ
#define PATH_MAX				255

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//画像のパス
#define IMAGE_BG_PATH			TEXT(".\\IMAGE\\BG.png")				//スタート画面・エンド画面の背景
#define IMAGE_TITLE_PATH		TEXT(".\\IMAGE\\title.png")				//タイトルロゴ
#define IMAGE_PUSH_ENTER_PATH	TEXT(".\\IMAGE\\pushenter.png")			//キー操作を促すボタン
#define IMAGE_PLAY_BG_PATH		TEXT(".\\IMAGE\\BG_play.png")			//プレイ画面の背景
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\Player.png")			//キャラクターの画像
#define IMAGE_MITUDESU_PATH		TEXT(".\\IMAGE\\mitudesu_pic.png")		//「密です」の画像
#define IMAGE_HUMAN_PATH		TEXT(".\\IMAGE\\human.png")				//人間(客)の描画
#define IMAGE_CLEAR_PATH		TEXT(".\\IMAGE\\GameClear.png")			//ゲームクリアロゴ
#define IMAGE_OVER_PATH			TEXT(".\\IMAGE\\GameOver.png")			//ゲームオーバーロゴ
#define IMAGE_GAME_EXP_PATH		TEXT(".\\IMAGE\\Game_Exp.png")			//ゲーム説明画像
#define IMAGE_EXP_BUTTON_PATH	TEXT(".\\IMAGE\\expButton.png")			//説明画面へ促すボタン
#define IMAGE_BACK_BUTTON_PATH	TEXT(".\\IMAGE\\backButton.png")		//戻るを促すボタン
#define IMAGE_EASY_BUTTON_PATH	TEXT(".\\IMAGE\\push1_easy.png")		//easyモードを促すボタン
#define IMAGE_HARD_BUTTON_PATH	TEXT(".\\IMAGE\\push2_hard.png")		//hardモードを促すボタン
#define IMAGE_HIGH_SCORE_PATH	TEXT(".\\IMAGE\\highscore.png")			//ハイスコアの画像
#define IMAGE_KEY_EXP_PATH		TEXT(".\\IMAGE\\Key_Exp.png")			//キー操作説明画像
#define IMAGE_KEY_BUTTON_PATH	TEXT(".\\IMAGE\\keyButton.png")			//キー操作説明画像へ促すボタン

//マップチップ関連
#define GAME_MAP_TATE_MAX		11  //マップの縦の数
#define GAME_MAP_YOKO_MAX		16  //マップの横の数

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip.png")

#define MAP_DIV_WIDTH			60  //画像を分割する幅サイズ
#define MAP_DIV_HEIGHT			60  //画像を分割する高さサイズ
#define MAP_DIV_TATE			10  //画像を縦に分割する数
#define MAP_DIV_YOKO			2   //画像を横に分割する数
#define MAP_DIV_NUM				MAP_DIV_TATE * MAP_DIV_YOKO  //画像を分割する総数

#define IMAGE_HUMAN_WIDTH		60	//人間の画像の幅の大きさ
#define IMAGE_HUMAN_HEIGHT		60	//人間の画像の高さの大きさ

//エラーメッセージ
#define START_ERR_TITLE			TEXT("スタート位置エラー")
#define START_ERR_CAPTION		TEXT("スタート位置が決まってません")

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//音楽のパス
#define MUSIC_START_BGM_PATH	 TEXT(".\\MUSIC\\waiting_room.mp3")		//スタート画面のBGM
#define MUSIC_PLAY_BGM_PATH		 TEXT(".\\MUSIC\\Green_Life.mp3")		//プレイ画面のBGM
#define SOUND_EFFECT_MITU_PATH	 TEXT(".\\MUSIC\\mitudesu.mp3")			//「密です」
#define MUSIC_CLEAR_BGM_PATH	 TEXT(".\\MUSIC\\Breakfast.mp3")		//GameClear時のBGM
#define MUSIC_OVER_BGM_PATH		 TEXT(".\\MUSIC\\枯葉色.mp3")			//GameOver時のBGM
#define SOUND_EFFECT_BUTTON_PATH TEXT(".\\MUSIC\\decision15.mp3")		//ボタンを押したときの効果音
#define SOUND_EFFECT_INFE_PATH	 TEXT(".\\MUSIC\\poison.mp3")			//感染したときの効果音

//時間関連
#define TIMELIMIT				60 * 1000		//制限時間、60秒間
#define EASY_APPE_TIME			3 * 1000		//人間を出現させる時間間隔(Easy)
#define HARD_APPE_TIME			2 * 1000		//人間を出現させる時間間隔(Hard)
#define EASY_CONTACT_TIME		8 * 1000		//接している時間、8秒間(Easy)
#define HARD_CONTACT_TIME		10 * 1000		//接している時間、10秒間(Hard)
#define DRAW_TIME				0.75 * 1000		//描画する時間

enum GAME_MAP_KIND
{
	n = -1,  //none
	t = 0,   //通路
	w = 1,   //壁
	s = 2,   //スタート
};  //マップの種類

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_EXP,
	GAME_SCENE_KEY,
};  //ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 4,
	CHARA_SPEED_HIGI = 3,
};  //キャラクターのスピード

enum GAME_JUDE {
	JUDE_CLEAR,  //成功
	JUDE_OVER    //失敗
};  //クリアか失敗か

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[FONT_PATH_MAX];	//パス
	char name[FONT_PATH_MAX];   //フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ
}FONT;

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;		//座標を初期化
	int y = -1;		//座標を初期化
}iPOINT;

typedef struct STRUCT_MOUSE 
{
	int InputValue = 0;		//GetMouseInputの値を入れる
	iPOINT Point;			//マウスの座標が入る
	iPOINT OldPoint;		//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };   //マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };		//マウスのボタン入力が入る
}MOUSE;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];	//パス
	int handle;				//ハンドル
	int x;					//X位置
	int y;					//Y位置
	int width;				//幅
	int height;				//高さ
}IMAGE;  //画像構造体

typedef struct STRUCT_CHARA
{
	IMAGE image;			//IMAGE構造体
	int speed;				//速さ
	//int CenterX;			//中心X
	//int CenterY;			//中心Y

	//デバッグ用
	RECT coll;				//当たり判定
	iPOINT collBeforePt;	//当たる前の座標
}CHARA;  //キャラクター構造体

typedef struct STRUCT_HUMAN
{
	IMAGE image;					//イメージ構造体
	BOOL IsDraw;					//描画できるか否か

	RECT Human_Coll;				//当たり判定

	BOOL IsContact;					//接しているか否か
}HUMAN;  //最初に出現する用

typedef struct STRUCT_HUMAN_TIME
{
	IMAGE Humanimage;				//イメージ構造体
	BOOL IsDraw;					//描画できるか否か

	RECT HumanCons_Coll;			//当たり判定

	BOOL IsContact;					//接しているか否か

	int ContactTime = 0;			//接している時間

	int NowCount = 0;				//人間同士の接している時間用

	BOOL Contact_First = TRUE;		//基準時間を取得する用
}HUMAN_CONSTANT;  //時間経過で出す用の人間

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];	//パス
	int handle;				//ハンドル
}MUSIC;  //音楽構造体

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle[MAP_DIV_NUM];	//分割したマップの画像
	int width;					//幅
	int height;					//高さ
}MAPCHIP;   //MAP_IMAGE構造体

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//マップの種類
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}MAP;   //MAP構造体

//######グローバル変数######
int StartTimeFps;					//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均をとるサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { 0 };
char OldAllKeyState[256] = { 0 };

//マウスの座標を取得
MOUSE mouse;

FONT Nikkyou;					//タイマー用
FONT CD_Nikkyou;				//最初のカウントダウン用
FONT SCORE_Nikkyou;				//スコア表示用

int GameScene;					//ゲームシーンを管理

//画像関連
IMAGE ImageBG;					//スタート画面・エンド画面の背景
IMAGE ImageTitle;				//タイトルロゴ
IMAGE ImagePushEnter;			//キー操作を促すボタン
IMAGE ImagePlayBG;				//プレイ画面の背景
IMAGE ImageMitudesu;			//「密です」の画像
IMAGE ImageHuman;				//人間(客)の描画
IMAGE ImageClear;				//ゲームクリアロゴ
IMAGE ImageOver;				//ゲームオーバーロゴ
IMAGE ImageGameExp;				//ゲーム説明画像
IMAGE ImageExpButton;			//説明画面へ促すボタン
IMAGE ImageBackButton;			//戻るを促すボタン
IMAGE ImageEasyButton;			//easyモードを促すボタン
IMAGE ImageHardButton;			//hardモードを促すボタン
IMAGE ImageHighScore;			//ハイスコアの画像
IMAGE ImageKeyExp;				//キー操作説明画像
IMAGE ImageKeyButton;			//キー操作説明画像へ促すボタン

HUMAN IMAGEHuman[5];			//スタート時に最初の人間を描画(5人から)
HUMAN_CONSTANT Human_Cons[30];	//一定時間ごとに出現する用の人間を配列で管理
int TimeDraw = 0;				//Human_Consの配列の添え字

CHARA player;					//プレイヤー

BOOL Mitudesu_Ent = FALSE;		//描画できるか否か

//音楽関連
MUSIC Start_BGM;				//スタート画面の背景
MUSIC Play_BGM;					//プレイ画面の背景
MUSIC Mitu_SF;					//「密です」(SF = Sound Effect)
MUSIC Clear_BGM;				//GameClear時のBGM
MUSIC Over_BGM;					//GameOver時のBGM
MUSIC Button_SF;				//ボタンを押したときの効果音
MUSIC Infe_SF;					//感染したときの効果音

//時間関連
int StartTime = 0;				//計測開始時間
int ElaTime = 0;				//残り時間
int CDTimeLimit = 0;			//カウントダウン用の制限時間(CD = Count Down)
int TimeLimit = 0;				//制限時間
BOOL First_flg = TRUE;			//ゲームに入る際のカウントダウンをする
BOOL CountDown = TRUE;			//カウントダウンをする際の基準時間を確保する
int Crit_AppeTime = 0;			//一定時間用の基準時間(出現 = Appearance)
int AppeTime = 0;				//何秒で出現させるかを格納する
double DrawTime = 0;			//描画用の基準時間
int ContactTime = 0;			//人間同士が接する時間

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
};   //ゲームのマップ

//ゲームマップの初期化
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };

//マップの当たり判定
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//GameClearかGameOverか判定する
int Jude;

//スコア関連
int Score = 0;						//スコア
int HighScore_Easy = -999;			//Easyモードのハイスコアを格納
int HighScore_Hard = -999;			//Hardモードのハイスコアを格納
BOOL PushEasyMode = FALSE;			//Easyモードを選択したか
BOOL PushHardMode = FALSE;			//Hardモードを選択したか
BOOL Update_EasyScore = FALSE;		//Easyモードのハイスコアが更新されたか
BOOL Update_HardScore = FALSE;		//Hardモードのハイスコアが更新されたか

//######プロトタイプ宣言######
VOID MY_FPS_UPDATE(VOID);					//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);						//FPS値を描画する
VOID MY_FPS_WAIT(VOID);						//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);			//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);						//キーを押しているか、キーコードで判断する
BOOL MY_KEY_DOWN_1SECOND(int);				//キーを押しているか(押しっぱなし回避パターン)

VOID MY_MOUSE_UPDATE(VOID);					//マウスの入力情報を更新する
BOOL MY_MOUSE_DOWN(int);					//ボタンを押しているか、マウスコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);			//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);			//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);					//フォントを作成する
VOID MY_FONT_DELETE(VOID);					//フォントを削除する

VOID MY_START(VOID);						//スタート画面
VOID MY_START_PROC(VOID);					//スタート画面の処理
VOID MY_START_DRAW(VOID);					//スタート画面の描画

VOID MY_EXP(VOID);							//説明画面
VOID MY_EXP_PROC(VOID);						//説明画面の処理
VOID MY_EXP_DRAW(VOID);						//説明画面の描画

VOID MY_KEY_EXP(VOID);						//キー操作説明画面
VOID MY_KEY_EXP_PROC(VOID);					//キー操作説明画面の処理
VOID MY_KEY_EXP_DRAW(VOID);					//キー操作説明画面の描画

VOID MY_PLAY(VOID);							//プレイ画面
VOID MY_PLAY_PROC(VOID);					//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);					//プレイ画面の描画

VOID MY_END(VOID);							//エンド画面
VOID MY_END_PROC(VOID);						//エンド画面の処理
VOID MY_END_DRAW(VOID);						//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);					//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);					//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);					//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);					//音楽をまとめて削除する関数

BOOL MY_CHECK_MAP_PLAYER_COLL(RECT);		//マップとプレイヤーの当たり判定をする関数
int MY_CHECK_HUMAN_PLAYER_COLL(RECT);		//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_HUMAN_HUMAN_COLL(RECT, int);	//人間同士の当たり判定をする関数
VOID MY_CHECK_INFEHUMAN_PLAYER_COLL(RECT);	//感染しているプレイヤーと接しているかを判定する関数
BOOL MY_CHECK_RECT_COLL(RECT, RECT);		//領域の当たり判定をする関数
VOID COLLPROC(VOID);						//当たり判定をする関数

VOID MY_INIT(VOID);							//初期化する関数

VOID GOTO_PLAY(VOID);						//プレイ画面に行く際の準備
VOID GOTO_EASY_MODE(VOID);					//Easyモードへ行く際の準備
VOID GOTO_HARD_MODE(VOID);					//Hardモードへ行く際の準備
VOID GOTO_START(VOID);						//スタート画面に行く際の処理
VOID GOTO_START_EXP(VOID);					//スタート画面に行く際の処理(説明画面から)

VOID PLAYER_ATTACK(VOID);					//プレイヤーの攻撃に関する関数
VOID PLAYER_MOVE(VOID);						//プレイヤーの移動に関する関数

VOID GAMECLEAR_IF(VOID);					//ゲームクリアに関する関数
VOID GAMEOVER_IF(VOID);						//ゲームオーバーに関する関数