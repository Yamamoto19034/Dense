/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//無限ループ

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_WIDTH	1100	//画面の横の大きさ
#define GAME_HEIGHT	750		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル

#define GAME_FPS			60  //FPSの数値

//マウスのボタン
#define MOUSE_BUTTON_CODE	129

//パスの長さ
#define PATH_MAX				255

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//画像のパス
#define IMAGE_START_BG_PATH		TEXT(".\\IMAGE\\BG_start.png")			//スタート画面の背景
#define IMAGE_TITLE_PATH		TEXT(".\\IMAGE\\title.png")				//タイトルロゴ
#define IMAGE_PLAY_BG_PATH		TEXT(".\\IMAGE\\BG_play.png")			//プレイ画面の背景
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\Player.png")			//キャラクターの画像

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//音楽のパス
#define MUSIC_START_BGM_PATH	TEXT(".\\MUSIC\\waiting_room.mp3")		//スタート画面のBGM
#define MUSIC_PLAY_BGM_PATH		TEXT(".\\MUSIC\\Green_Life.mp3")		//プレイ画面のBGM

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};  //ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGI = 3,
};  //キャラクターのスピード

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
	int CenterX;			//中心X
	int CenterY;			//中心Y
}CHARA;  //キャラクター構造体

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];	//パス
	int handle;				//ハンドル
}MUSIC;  //音楽構造体

//######グローバル変数######
int StartTimeFps;					//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均をとるサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { 0 };
char OldAllKeyState[256] = { 0 };

int GameScene;					//ゲームシーンを管理

//画像関連
IMAGE ImageStartBG;				//スタート画面の背景
IMAGE ImageTitle;				//タイトルロゴ
IMAGE ImagePlayBG;				//プレイ画面の背景

CHARA player;					//キャラクター

//音楽関連
MUSIC Start_BGM;				//スタート画面の背景
MUSIC Play_BGM;					//プレイ画面の背景

//######プロトタイプ宣言######
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する

VOID MY_START(VOID);				//スタート画面
VOID MY_START_PROC(VOID);			//スタート画面の処理
VOID MY_START_DRAW(VOID);			//スタート画面の描画

VOID MY_PLAY(VOID);					//プレイ画面
VOID MY_PLAY_PROC(VOID);			//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);			//プレイ画面の描画

VOID MY_END(VOID);					//エンド画面
VOID MY_END_PROC(VOID);				//エンド画面の処理
VOID MY_END_DRAW(VOID);				//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);			//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);			//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);			//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);			//音楽をまとめて削除する関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);		//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);						//非アクティブでも実行する

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	int DrawX = 0;	//表示位置X
	int DrawY = 0;	//表示位置Y

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

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

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//音楽ハンドルを破棄
	MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
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

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
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

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];  //一時的に、現在のキーの入力状態を格納する

	//直前のキー入力を取っておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);		//全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
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

		//プレイシーンへ移動する
		GameScene = GAME_SCENE_PLAY;

		return;  //強制的にプレイシーンへ移動する
	}

	//BGMが流れていないなら
	if (CheckSoundMem(Start_BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, Start_BGM.handle);  //50%の音量にする
		PlaySoundMem(Start_BGM.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//背景・タイトルを描画
	DrawGraph(ImageStartBG.x, ImageStartBG.y, ImageStartBG.handle, TRUE);
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);
	DrawString(0, 0, "スタート画面(エンターキーを押してください)", GetColor(255, 255, 255));

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
	//スペースキー押したら、エンドシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(Play_BGM.handle) != 0)
		{
			StopSoundMem(Play_BGM.handle);  //BGMを止める
		}

		//エンドシーンへ移動する
		GameScene = GAME_SCENE_END;

		return;  //強制的にエンドシーンへ移動する
	}

	//BGMが流れていないなら
	if (CheckSoundMem(Play_BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, Play_BGM.handle);  //50%の音量にする
		PlaySoundMem(Play_BGM.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImagePlayBG.x, ImagePlayBG.y, ImagePlayBG.handle, TRUE);
	DrawString(0, 0, "プレイ画面(スペースキーを押してください)", GetColor(255, 255, 255));

	//プレイヤーを描画
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

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
	//エスケープキー押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);
	DrawString(0, 0, "エンド画面(エスケープキーを押してください)", GetColor(255, 255, 255));

	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//スタート画面の背景画像
	strcpy_s(ImageStartBG.path, IMAGE_START_BG_PATH);		//パスの設定
	ImageStartBG.handle = LoadGraph(ImageStartBG.path);		//読み込み
	if (ImageStartBG.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_BG_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageStartBG.handle, &ImageStartBG.width, &ImageStartBG.height);	//画像の幅と高さを取得
	ImageStartBG.x = GAME_WIDTH / 2 - ImageStartBG.width / 2;		//X位置を決める
	ImageStartBG.y = GAME_HEIGHT / 2 - ImageStartBG.height / 2;		//Y位置を決める

	//タイトルロゴ画像
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

	//プレイ画面の背景画像
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
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_MIDI;								//スピードを設定

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageStartBG.handle);
	DeleteGraph(ImageTitle.handle);
	DeleteGraph(ImagePlayBG.handle);

	DeleteGraph(player.image.handle);

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

	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(Start_BGM.handle);
	DeleteSoundMem(Play_BGM.handle);

	return;
}