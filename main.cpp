/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//無限ループ

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_WIDTH				960		//画面の横の大きさ
#define GAME_HEIGHT				660		//画面の縦の大きさ
#define GAME_COLOR				32		//画面のカラービット

#define GAME_WINDOW_BAR			0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME		"GAME TITLE"	//ウィンドウのタイトル

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
#define IMAGE_HUMAN_PATH		TEXT(".\\IMAGE\\human.png")				//人間(客)の描画
#define IMAGE_CLEAR_PATH		TEXT(".\\IMAGE\\GameClear.png")			//ゲームクリアロゴ
#define IMAGE_OVER_PATH			TEXT(".\\IMAGE\\GameOver.png")			//ゲームオーバーロゴ

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
#define MUSIC_START_BGM_PATH	TEXT(".\\MUSIC\\waiting_room.mp3")		//スタート画面のBGM
#define MUSIC_PLAY_BGM_PATH		TEXT(".\\MUSIC\\Green_Life.mp3")		//プレイ画面のBGM
#define SOUND_EFFECT_MITU_PATH	TEXT(".\\MUSIC\\mitudesu.mp3")			//「密です」
#define MUSIC_CLEAR_BGM_PATH	TEXT(".\\MUSIC\\Breakfast.mp3")			//GameClear時のBGM
#define MUSIC_OVER_BGM_PATH		TEXT(".\\MUSIC\\枯葉色.mp3")			//GameOver時のBGM

//時間関連
#define TIMELIMIT				60 * 1000		//制限時間、60秒間
#define EASY					3 * 1000
#define CONTACT_TIME			10 * 1000		//接している時間、3秒間

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

FONT Nikkyou;
FONT CD_Nikkyou;				//最初のカウントダウン用

int GameScene;					//ゲームシーンを管理

//画像関連
IMAGE ImageBG;					//スタート画面・エンド画面の背景
IMAGE ImageTitle;				//タイトルロゴ
IMAGE ImagePushEnter;			//キー操作を促すボタン
IMAGE ImagePlayBG;				//プレイ画面の背景
IMAGE ImageHuman;				//人間(客)の描画
IMAGE ImageClear;				//ゲームクリアロゴ
IMAGE ImageOver;				//ゲームオーバーロゴ

HUMAN IMAGEHuman[5];			//スタート時に最初の人間を描画(5人から)
HUMAN_CONSTANT Human_Cons[20];	//一定時間ごとに出現する用の人間を配列で管理
int TimeDraw = 0;				//Human_Consの配列の添え字

CHARA player;					//キャラクター

//音楽関連
MUSIC Start_BGM;				//スタート画面の背景
MUSIC Play_BGM;					//プレイ画面の背景
MUSIC Mitu_SF;					//「密です」(SF = Sound Effect)
MUSIC Clear_BGM;				//GameClear時のBGM
MUSIC Over_BGM;					//GameOver時のBGM

//時間関連
int StartTime = 0;				//計測開始時間
int ElaTime = 0;				//残り時間
int CDTimeLimit = 0;			//カウントダウン用の制限時間(CD = Count Down)
int TimeLimit = 0;				//制限時間
BOOL First_flg = TRUE;			//ゲームに入る際のカウントダウンをする
BOOL CountDown = TRUE;			//カウントダウンをする際の基準時間を確保する
int AppeTime = 0;				//一定時間用の基準時間(出現 = Appearance)

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

//######プロトタイプ宣言######
VOID MY_FPS_UPDATE(VOID);					//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);						//FPS値を描画する
VOID MY_FPS_WAIT(VOID);						//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);			//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);						//キーを押しているか、キーコードで判断する
BOOL MY_KEY_DOWN_1SECOND(int);				//キーを押しているか(押しっぱなし回避パターン)

BOOL MY_FONT_INSTALL_ONCE(VOID);			//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);			//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);					//フォントを作成する
VOID MY_FONT_DELETE(VOID);					//フォントを削除する

VOID MY_START(VOID);						//スタート画面
VOID MY_START_PROC(VOID);					//スタート画面の処理
VOID MY_START_DRAW(VOID);					//スタート画面の描画

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

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);		//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);						//非アクティブでも実行する

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }

	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return - 1; }

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//プレイヤーの最初の位置を、スタート位置にする
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			//スタート位置を探す
			if (mapData[tate][yoko] == s)
			{
				//スタート位置を計算
				startPt.x = mapChip.width * yoko;	//中心X座標を取得
				startPt.y = mapChip.height * tate;	//中心Y座標を取得
				break;
			}
		}
		//スタート位置が決まっていれば、ループ終了
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}
	//スタート位置が決まっていなければ
	if (startPt.x == -1 && startPt.y == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);
		return -1;
	}

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_FPS_UPDATE();						//FPSの処理(更新)

		//シーンごとに処理を行う
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

		MY_FPS_DRAW();							//FPSの処理(描画)

		ScreenFlip();							//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();							//FPSの処理(待つ)
	}

	//フォントハンドルを破棄
	MY_FONT_DELETE();

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//一時的にインストールしたフォントをアンインストール
	MY_FONT_UNINSTALL_ONCE();

	//音楽ハンドルを破棄
	MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//FPS値を計測、更新する関数
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//FPS値を描画する関数
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//FPS値を計測し、待つ関数
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//キーの入力状態を更新する関数
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];  //一時的に、現在のキーの入力状態を格納する

	//直前のキー入力を取っておく
	for (int i = 0; i < 256; ++i)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);		//全てのキーの入力状態を得る

	for (int i = 0; i < 256; ++i)
	{
		if (TempKey[i] != 0)		//押されているキーのキーコードの押しているとき
		{
			AllKeyState[i]++;		//押されている
		}
		else
		{
			AllKeyState[i] = 0;		//押されていない
		}
	}

	return;
}

//キーを押しているか、キーコードで判断する
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押しているか(押しっぱなし回避パターン)
BOOL MY_KEY_DOWN_1SECOND(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] == 1)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//フォントをこのソフト用に、一時的にインストール
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_NIKK_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_NIKK_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//フォントをこのソフト用に、一時的にアンインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_NIKK_PATH, FR_PRIVATE, NULL);

	return;
}

//フォントを読み込む関数
BOOL MY_FONT_CREATE(VOID)
{
	//フォントデータを作成
	strcpy_s(Nikkyou.path, sizeof(Nikkyou.path), FONT_NIKK_PATH);	//パスをコピー
	strcpy_s(Nikkyou.name, sizeof(Nikkyou.name), FONT_NIKK_NAME);	//フォント名をコピー
	Nikkyou.handle = -1;							//ハンドルを初期化
	Nikkyou.size = 50;								//サイズ: 50
	Nikkyou.bold = 1;								//太さ: 1
	Nikkyou.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	Nikkyou.handle = CreateFontToHandle(Nikkyou.name, Nikkyou.size, Nikkyou.bold, Nikkyou.type);
	//フォントハンドル作成できないとき、エラー
	if (Nikkyou.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_NIKK_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }


	//フォントデータを作成(カウントダウン用)
	strcpy_s(CD_Nikkyou.path, sizeof(CD_Nikkyou.path), FONT_NIKK_PATH);	//パスをコピー
	strcpy_s(CD_Nikkyou.name, sizeof(CD_Nikkyou.name), FONT_NIKK_NAME);	//フォント名をコピー
	CD_Nikkyou.handle = -1;								//ハンドルを初期化
	CD_Nikkyou.size = 300;								//サイズ: 300
	CD_Nikkyou.bold = 5;								//太さ: 5
	CD_Nikkyou.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	CD_Nikkyou.handle = CreateFontToHandle(CD_Nikkyou.name, CD_Nikkyou.size, CD_Nikkyou.bold, CD_Nikkyou.type);
	//フォントハンドル作成できないとき、エラー
	if (CD_Nikkyou.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_NIKK_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	return TRUE;
}

//フォントを削除する関数
VOID MY_FONT_DELETE(VOID)
{
	//フォントデータを削除
	DeleteFontToHandle(CD_Nikkyou.handle);	//フォントのハンドルを削除

	return;
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//エンターキー押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(Start_BGM.handle) != 0)
		{
			StopSoundMem(Start_BGM.handle);  //BGMを止める
		}

		//プレイヤーの画像の位置を設定する
		player.image.x = startPt.x;
		player.image.y = startPt.y;

		//プレイ画面に向けて準備
		TimeLimit = TIMELIMIT;			//制限時間を設定
		GameScene = GAME_SCENE_PLAY;	//プレイシーンへ移動する

		//最初に出現する用
		//for (int i = 0; i < 5; ++i)
		//{
		//	//ここで描画位置を決める
		//	int x = GetRand(15);
		//	int y = GetRand(10);

		//	//座標位置が通路なら(壁とスタート位置には描画しない)
		//	if (mapData[x][y] == t)
		//	{
		//		IMAGEHuman[i].IsDraw = TRUE;					//表示OK
		//		IMAGEHuman[i].image.x = IMAGE_HUMAN_WIDTH * x;
		//		IMAGEHuman[i].image.y = IMAGE_HUMAN_HEIGHT * y;

		//		//ここで当たり判定の設定をする
		//		IMAGEHuman[i].Human_Coll.left = IMAGEHuman[i].image.x + 1;
		//		IMAGEHuman[i].Human_Coll.top = IMAGEHuman[i].image.y + 1;
		//		IMAGEHuman[i].Human_Coll.right = IMAGEHuman[i].image.x + IMAGE_HUMAN_WIDTH - 1;
		//		IMAGEHuman[i].Human_Coll.bottom = IMAGEHuman[i].image.y + IMAGE_HUMAN_HEIGHT - 1;
		//	}
		//}
		//ここで描画位置を決める(一定時間で出現する用)
		for (int i = 0; i < 20; ++i)
		{
			int x = GetRand(15);
			int y = GetRand(10);

			Human_Cons[i].Humanimage.x = IMAGE_HUMAN_WIDTH * x;
			Human_Cons[i].Humanimage.y = IMAGE_HUMAN_HEIGHT * y;
		}

		return;  //強制的にプレイシーンへ移動する
	}

	//BGMが流れていないなら
	if (CheckSoundMem(Start_BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, Start_BGM.handle);  //50%の音量にする
		PlaySoundMem(Start_BGM.handle, DX_PLAYTYPE_LOOP);		 //ループ再生
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//背景・タイトルを描画
	DrawGraph(ImageBG.x, ImageBG.y, ImageBG.handle, TRUE);
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);
	DrawGraph(ImagePushEnter.x, ImagePushEnter.y, ImagePushEnter.handle, TRUE);
	//DrawString(0, 0, "スタート画面(エンターキーを押してください)", GetColor(255, 255, 255));

	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//スタート画面の処理
	MY_PLAY_DRAW();	//スタート画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(Play_BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, Play_BGM.handle);  //50%の音量にする
		PlaySoundMem(Play_BGM.handle, DX_PLAYTYPE_LOOP);		//ループ再生
	}

	//スペースキー押したら、エンドシーンへ移動する(デバッグ用)
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(Play_BGM.handle) != 0)
		{
			StopSoundMem(Play_BGM.handle);  //BGMを止める
		}

		MY_INIT();
		Jude = JUDE_CLEAR;

		//エンドシーンへ移動する
		GameScene = GAME_SCENE_END;

		return;  //強制的にエンドシーンへ移動する
	}

	if (First_flg)  //まずはカウントダウンからスタート
	{
		if (CountDown)  //基準時間を取得
		{
			StartTime = GetNowCount();
			CountDown = FALSE;			//これ以降、このif文は行わない
		}

		//現在の時間を取得
		int NowCount = GetNowCount();
		CDTimeLimit = 3 * 1000;		//制限時間を設定
		ElaTime = CDTimeLimit - (NowCount - StartTime);  //カウントダウンを行う

		//経過時間が0秒になったら(3,2,1 で終了させるため <=)
		if (ElaTime <= 0)
		{
			StartTime = GetNowCount();		//本番に向けて基準時間を取得
			AppeTime = GetNowCount();		//本番に向けて基準時間を取得
			First_flg = FALSE;				//これ以降はカウントダウンを行わない
		}
	}
	else 
	{
		//現在の時間を取得
		int NowCount = GetNowCount();	//制限時間用
		int NowCount2 = GetNowCount();	//一定時間で出現する用

		//制限時間(降順で時間表示) - (現在の時間 - 基準の時間) ← ミリ秒単位
		ElaTime = TimeLimit - (NowCount - StartTime);

		//経過時間が0秒になったら(・・・3,2,1 で終了させるため <=)
		if (ElaTime <= 0)
		{
			GameScene = GAME_SCENE_END;	//エンドシーンへ移動する

			//BGMが流れているなら
			if (CheckSoundMem(Play_BGM.handle) != 0)
			{
				StopSoundMem(Play_BGM.handle);		//BGMを止める
			}

			//初期化する
			MY_INIT();
			Jude = JUDE_CLEAR;

			return;
		}

		//一定時間で人間を出現させる処理
		if (NowCount2 - AppeTime >= EASY)
		{
			Human_Cons[TimeDraw].IsDraw = TRUE;		//描画できる

			//当たり判定を設定する
			Human_Cons[TimeDraw].HumanCons_Coll.left = Human_Cons[TimeDraw].Humanimage.x - 5;
			Human_Cons[TimeDraw].HumanCons_Coll.top = Human_Cons[TimeDraw].Humanimage.y - 5;
			Human_Cons[TimeDraw].HumanCons_Coll.right = Human_Cons[TimeDraw].Humanimage.x + IMAGE_HUMAN_WIDTH + 5;
			Human_Cons[TimeDraw].HumanCons_Coll.bottom = Human_Cons[TimeDraw].Humanimage.y + IMAGE_HUMAN_HEIGHT + 5;

			TimeDraw++;								//次の配列に
			AppeTime = GetNowCount();			//再度時間を取得してリセット
		}
		//プレイヤーのキー操作(4方向カーソルキーで行う)
		if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)	  //上カーソルキー
		{
			if (player.image.y >= 0)  //画面外でないなら
				player.image.y -= player.speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)  //下カーソルキー
		{
			if (player.image.y + player.image.height <= GAME_HEIGHT) //画面外でないなら
				player.image.y += player.speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)  //左カーソルキー
		{
			if (player.image.x >= 0)  //画面外でないなら
				player.image.x -= player.speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) //右カーソルキー
		{
			if (player.image.x + player.image.width <= GAME_WIDTH)  //画面外でないなら
				player.image.x += player.speed;
		}

		//プレイヤーの攻撃
		if (MY_KEY_DOWN_1SECOND(KEY_INPUT_RETURN) == TRUE)
		{
			//効果音が流れていないなら
			if (CheckSoundMem(Mitu_SF.handle) == 0)
			{
				//効果音の音量を下げる
				ChangeVolumeSoundMem(255 * 80 / 100, Mitu_SF.handle);  //50%の音量にする
				PlaySoundMem(Mitu_SF.handle, DX_PLAYTYPE_BACK);		   //バックグラウンド再生
			}

			//接してるか確認
			MY_CHECK_INFEHUMAN_PLAYER_COLL(player.coll);
		}

		//当たり判定
		COLLPROC();

		//GAME OVER条件
		for (int i = 0; i < 20; ++i)
		{
			//接しているなら 且つ 表示されているなら
			if (Human_Cons[i].IsContact == TRUE && Human_Cons[i].IsDraw == TRUE)
			{
				//それぞれで時間を取得する
				Human_Cons[i].NowCount = GetNowCount();

				if (Human_Cons[i].Contact_First)
				{
					//ここでは基準時間を取得
					Human_Cons[i].ContactTime = GetNowCount();
					Human_Cons[i].Contact_First = FALSE;	//この処理は1回だけ
				}
				
				//人間同士が一定時間、接していたら
				if ((Human_Cons[i].NowCount - Human_Cons[i].ContactTime) >= CONTACT_TIME)
				{
					//BGMが流れているなら
					if (CheckSoundMem(Play_BGM.handle) != 0)
					{
						StopSoundMem(Play_BGM.handle);		//BGMを止める
					}

					//初期化する
					MY_INIT();
					Jude = JUDE_OVER;

					//エンドシーンへ移動する
					GameScene = GAME_SCENE_END;
				}
			}
		}
	}

	return;
}

//プレイ画面の描画
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
	
	DrawString(0, 0, "プレイ画面(スペースキーを押してください)", GetColor(255, 255, 255));

	if (First_flg)  //最初のカウントダウン
	{
		DrawFormatStringToHandle(GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2 - 125, GetColor(255, 0, 0), CD_Nikkyou.handle, "%d", (ElaTime / 1000) + 1);
	}
	else
	{
		//制限時間の表示
		//1000で割って「ミリ秒単位」から「秒単位」に
		//0 が出てきてしまうので +1する
		if ((ElaTime / 1000 + 1) <= 3)  //残り3秒は赤字にする
			DrawFormatStringToHandle(GAME_WIDTH - 70, 0, GetColor(255, 0, 0), Nikkyou.handle, "%d", (ElaTime / 1000) + 1);
		else
			DrawFormatStringToHandle(GAME_WIDTH - 70, 0, GetColor(255, 255, 255),  Nikkyou.handle,"%d", (ElaTime / 1000) + 1);

		//当たり判定の描画(デバッグ用)
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
			{
				//壁ならば
				if (mapData[tate][yoko] == w)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
				}
				//通路ならば
				if (mapData[tate][yoko] == t)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 0, 255), FALSE);
				}
			}
		}

		//↓人間(客)の描画↓
		//最初に出現する用
		//for (int i = 0; i < 5; ++i)
		//{
		//	if (IMAGEHuman[i].IsDraw == TRUE)  //描画できるなら
		//	{
		//		if (IMAGEHuman[i].IsContact == TRUE)  //接しているなら
		//			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);  //色を反転させて表示
		//		DrawGraph(IMAGEHuman[i].image.x, IMAGEHuman[i].image.y, IMAGEHuman[i].image.handle, TRUE);
		//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		 //元に戻す
		//	}
		//}
		//一定時間で出現する用
		for (int i = 0; i < 20; ++i)
		{
			if (Human_Cons[i].IsDraw == TRUE)  //描画できるなら
			{
				if(Human_Cons[i].IsContact == TRUE)  //接しているなら
					SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);  //色を反転させて表示
				DrawGraph(Human_Cons[i].Humanimage.x, Human_Cons[i].Humanimage.y, Human_Cons[i].Humanimage.handle, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		 //元に戻す
			}
		}

		//プレイヤーを描画
		DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

		//プレイヤーの当たり判定を描画(デバッグ用)
		DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);
	}

	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//スタート画面の処理
	MY_END_DRAW();	//スタート画面の描画

	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	switch (Jude)
	{
	case JUDE_CLEAR:  //クリアパターン
		//BGMが流れていないなら
		if (CheckSoundMem(Clear_BGM.handle) == 0)
		{
			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 50 / 100, Clear_BGM.handle);  //50%の音量にする
			PlaySoundMem(Clear_BGM.handle, DX_PLAYTYPE_LOOP);		 //バックグラウンド再生
		}
		break;

	case JUDE_OVER:  //失敗パターン
		//BGMが流れていないなら
		if (CheckSoundMem(Over_BGM.handle) == 0)
		{
			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 50 / 100, Over_BGM.handle);  //50%の音量にする
			PlaySoundMem(Over_BGM.handle, DX_PLAYTYPE_LOOP);		//バックグラウンド再生
		}
		break;
	}

	//エスケープキー押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;

		//BGMが流れているなら(GameClear)
		if (CheckSoundMem(Clear_BGM.handle) != 0)
		{
			StopSoundMem(Clear_BGM.handle);		//BGMを止める
		}
		//BGMが流れているなら(GameOver)
		if (CheckSoundMem(Over_BGM.handle) != 0)
		{
			StopSoundMem(Over_BGM.handle);   //BGMを止める
		}
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);
	DrawString(0, 0, "エンド画面(エスケープキーを押してください)", GetColor(255, 255, 255));

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

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//スタート画面・エンド画面の背景
	strcpy_s(ImageBG.path, IMAGE_BG_PATH);		//パスの設定
	ImageBG.handle = LoadGraph(ImageBG.path);		//読み込み
	if (ImageBG.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBG.handle, &ImageBG.width, &ImageBG.height);	//画像の幅と高さを取得
	ImageBG.x = GAME_WIDTH / 2 - ImageBG.width / 2;			//X位置を決める
	ImageBG.y = GAME_HEIGHT / 2 - ImageBG.height / 2;		//Y位置を決める

	//タイトルの画像
	strcpy_s(ImageTitle.path, IMAGE_TITLE_PATH);		//パスの設定
	ImageTitle.handle = LoadGraph(ImageTitle.path);		//読み込み
	if (ImageTitle.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitle.handle, &ImageTitle.width, &ImageTitle.height);	//画像の幅と高さを取得
	ImageTitle.x = GAME_WIDTH / 2 - ImageTitle.width / 2;			//X位置を決める
	ImageTitle.y = GAME_HEIGHT / 2 - ImageTitle.height / 2;			//Y位置を決める

	//キー操作を促すボタン(Push Enter Key)
	strcpy_s(ImagePushEnter.path, IMAGE_PUSH_ENTER_PATH);		//パスの設定
	ImagePushEnter.handle = LoadGraph(ImagePushEnter.path);		//読み込み
	if (ImagePushEnter.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PUSH_ENTER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePushEnter.handle, &ImagePushEnter.width, &ImagePushEnter.height);	//画像の幅と高さを取得
	ImagePushEnter.x = GAME_WIDTH / 2 - ImagePushEnter.width / 2;			//X位置を決める
	ImagePushEnter.y = ImageTitle.y + ImageTitle.height;					//Y位置を決める

	//プレイ画面の背景画像
	strcpy_s(ImagePlayBG.path, IMAGE_PLAY_BG_PATH);		//パスの設定
	ImagePlayBG.handle = LoadGraph(ImagePlayBG.path);		//読み込み
	if (ImagePlayBG.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePlayBG.handle, &ImagePlayBG.width, &ImagePlayBG.height);	//画像の幅と高さを取得
	ImagePlayBG.x = GAME_WIDTH / 2 - ImagePlayBG.width / 2;			//X位置を決める
	ImagePlayBG.y = GAME_HEIGHT / 2 - ImagePlayBG.height / 2;		//Y位置を決める

	//プレイヤー画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);		//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//X位置を決める
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//Y位置を決める
	//player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	//player.CenterY = player.image.y + player.image.height / 2;	//画像の縦の中心を探す
	player.speed = CHARA_SPEED_MIDI;								//スピードを設定

	//↓人間(客)の画像↓
	//最初に出現する用
	for (int i = 0; i < 5; ++i)  //読み込み
	{
		strcpy_s(IMAGEHuman[i].image.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 5; ++i)
	{
		//ハンドルの取得
		IMAGEHuman[i].image.handle = LoadGraph(IMAGEHuman[i].image.path);
		if (IMAGEHuman[i].image.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//大きさの取得
		GetGraphSize(IMAGEHuman[i].image.handle, &IMAGEHuman[i].image.width, &IMAGEHuman[i].image.height);
		IMAGEHuman[i].IsDraw = FALSE;				//最初は描画しない
		IMAGEHuman[i].IsContact = FALSE;			//接してない
	}

	//一定時間で描画する用
	for (int i = 0; i < 20; ++i)  //読み込み
	{
		strcpy_s(Human_Cons[i].Humanimage.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 20; ++i)
	{
		//ハンドルの取得
		Human_Cons[i].Humanimage.handle = LoadGraph(Human_Cons[i].Humanimage.path);
		if (Human_Cons[i].Humanimage.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//大きさの取得
		GetGraphSize(Human_Cons[i].Humanimage.handle, &Human_Cons[i].Humanimage.width, &Human_Cons[i].Humanimage.height);
		Human_Cons[i].IsDraw = FALSE;				//最初は描画しない
		Human_Cons[i].IsContact = FALSE;			//接してない
	}

	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,								//マップチップのパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,	//分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,				//画像を分割する幅と高さ
		&mapChip.handle[0]);						//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//マップの種類をコピー
			map[tate][yoko].kind = mapData[tate][yoko];

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を取得
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//ゲームクリアロゴ
	strcpy_s(ImageClear.path, IMAGE_CLEAR_PATH);		//パスの設定
	ImageClear.handle = LoadGraph(ImageClear.path);		//読み込み
	if (ImageClear.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_CLEAR_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageClear.handle, &ImageClear.width, &ImageClear.height);	//画像の幅と高さを取得
	ImageClear.x = GAME_WIDTH / 2 - ImageClear.width / 2;			//X位置を決める
	ImageClear.y = GAME_HEIGHT / 2 - ImageClear.height / 2;			//Y位置を決める

	//ゲームオーバーロゴ
	strcpy_s(ImageOver.path, IMAGE_OVER_PATH);			//パスの設定
	ImageOver.handle = LoadGraph(ImageOver.path);		//読み込み
	if (ImageOver.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_OVER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageOver.handle, &ImageOver.width, &ImageOver.height);	//画像の幅と高さを取得
	ImageOver.x = GAME_WIDTH / 2 - ImageOver.width / 2;				//X位置を決める
	ImageOver.y = GAME_HEIGHT / 2 - ImageOver.height / 2;			//Y位置を決める

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageBG.handle);			//スタート画面・エンド画面の背景

	DeleteGraph(ImageTitle.handle);			//タイトルロゴ
	DeleteGraph(ImagePushEnter.handle);		//キー操作を促すボタン
	DeleteGraph(ImagePlayBG.handle);		//プレイ画面の背景

	DeleteGraph(player.image.handle);		//プレイヤー画像

	DeleteGraph(ImageHuman.handle);			//人間(客)の削除

	for (int i = 0; i < 5; ++i)				//最初に出現する用
	{
		DeleteGraph(IMAGEHuman[i].image.handle);
	}

	for (int i = 0; i < 20; ++i)			//一定時間で出現する用
	{
		DeleteGraph(Human_Cons[i].Humanimage.handle);
	}

	//マップチップの削除
	for (int num = 0; num < MAP_DIV_NUM; ++num)
	{
		DeleteGraph(mapChip.handle[num]);
	}

	DeleteGraph(ImageClear.handle);			//ゲームクリアロゴ
	DeleteGraph(ImageOver.handle);

	return;
}

//音楽をまとめて読み込む関数
BOOL MY_LOAD_MUSIC(VOID)
{
	//スタート画面の背景音楽
	strcpy_s(Start_BGM.path, MUSIC_START_BGM_PATH);
	Start_BGM.handle = LoadSoundMem(Start_BGM.path);
	if (Start_BGM.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_START_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイ画面の背景音楽
	strcpy_s(Play_BGM.path, MUSIC_PLAY_BGM_PATH);
	Play_BGM.handle = LoadSoundMem(Play_BGM.path);
	if (Play_BGM.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//効果音「密です」
	strcpy_s(Mitu_SF.path, SOUND_EFFECT_MITU_PATH);
	Mitu_SF.handle = LoadSoundMem(Mitu_SF.path);
	if (Mitu_SF.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), SOUND_EFFECT_MITU_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(Clear_BGM.path, MUSIC_CLEAR_BGM_PATH);
	Clear_BGM.handle = LoadSoundMem(Clear_BGM.path);
	if (Clear_BGM.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_CLEAR_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(Over_BGM.path, MUSIC_OVER_BGM_PATH);
	Over_BGM.handle = LoadSoundMem(Over_BGM.path);
	if (Over_BGM.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_OVER_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(Start_BGM.handle);
	DeleteSoundMem(Play_BGM.handle);
	DeleteSoundMem(Mitu_SF.handle);
	DeleteSoundMem(Clear_BGM.handle);
	DeleteSoundMem(Over_BGM.handle);

	return;
}

//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_MAP_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (map[tate][yoko].kind == w) { return TRUE; }
			}
		}
	}
	
	return FALSE;
}

//人間とプレイヤーの当たり判定
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

//人間同士の当たり判定
BOOL MY_CHECK_HUMAN_HUMAN_COLL(RECT Human, int order)
{
	//一定時間で出現する vs 一定時間で出現する
	for (int i = 0; i < 20; ++i)
	{
		if (i != order)  //同じものは当たり判定のチェックをしない
		{
			if (MY_CHECK_RECT_COLL(Human, Human_Cons[i].HumanCons_Coll) == TRUE)
			{
				if(Human_Cons[i].IsDraw == TRUE)   //描画されているなら
					return TRUE;
			}
		}
	}

	//最初に出現する vs 一定時間で出現する
	for (int i = 0; i < 5; ++i)
	{
		if (MY_CHECK_RECT_COLL(Human, IMAGEHuman[i].Human_Coll) == TRUE)
		{
			if (IMAGEHuman[i].IsDraw == TRUE)       //描画されているなら
			{
				IMAGEHuman[i].IsContact = TRUE;		//接している
				return TRUE;
			}
		}
	}

	return FALSE;
}

//感染しているプレイヤーと接しているかを判定する関数
VOID MY_CHECK_INFEHUMAN_PLAYER_COLL(RECT player)
{
	for (int i = 0; i < 20; ++i)
	{
		if (MY_CHECK_RECT_COLL(player, Human_Cons[i].HumanCons_Coll) == TRUE)
		{
			//接しているなら且つ描画されているなら
			if (Human_Cons[i].IsContact == TRUE && Human_Cons[i].IsDraw == TRUE)
			{
				//画面から消す
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


//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}

//当たり判定をする関数
VOID COLLPROC(VOID)
{
	//プレイヤーの当たり判定の設定
	player.coll.left = player.image.x;
	player.coll.top = player.image.y;
	player.coll.right = player.image.x + player.image.width;
	player.coll.bottom = player.image.y + player.image.height;

	//プレイヤーと壁が当たっていたら
	if (MY_CHECK_MAP_PLAYER_COLL(player.coll) == TRUE)
	{
		//通り抜け不可
		player.image.x = player.collBeforePt.x;		//今いる場所のX座標を代入
		player.image.y = player.collBeforePt.y;		//今いる場所のY座標を代入
	}

	//プレイヤーと人間が当たっていたら
	if (MY_CHECK_HUMAN_PLAYER_COLL(player.coll) == 1)
	{
		//通り抜け不可
		player.image.x = player.collBeforePt.x;		//今いる場所のX座標を代入
		player.image.y = player.collBeforePt.y;		//今いる場所のY座標を代入
	}

	//常に座標を取得しておく
	player.collBeforePt.x = player.image.x;
	player.collBeforePt.y = player.image.y;

	for (int i = 0; i < 20; ++i)
	{
		//人間同士が当たっていたら
		if (MY_CHECK_HUMAN_HUMAN_COLL(Human_Cons[i].HumanCons_Coll, i) == TRUE)
		{
			if(Human_Cons[i].IsDraw == TRUE)     //描画されているなら
				Human_Cons[i].IsContact = TRUE;  //接してる
		}
	}

	return;
}

//初期化する関数
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
		//全て非表示に
		Human_Cons[i].IsContact = FALSE;
		Human_Cons[i].IsDraw = FALSE;
	}

	TimeDraw = 0;

	First_flg = TRUE;
	CountDown = TRUE;

	return;
}