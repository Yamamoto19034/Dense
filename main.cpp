/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//無限ループ

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_WIDTH	960		//画面の横の大きさ
#define GAME_HEIGHT	660		//画面の縦の大きさ
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
#define IMAGE_HUMAN_PATH		TEXT(".\\IMAGE\\human.png")				//人間(客)の描画

//マップチップ関連
#define GAME_MAP_TATE_MAX		11  //マップの縦の数
#define GAME_MAP_YOKO_MAX		16  //マップの横の数

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip.png")

#define MAP_DIV_WIDTH			60  //画像を分割する幅サイズ
#define MAP_DIV_HEIGHT			60  //画像を分割する高さサイズ
#define MAP_DIV_TATE			10  //画像を縦に分割する数
#define MAP_DIV_YOKO			2   //画像を横に分割する数
#define MAP_DIV_NUM				MAP_DIV_TATE * MAP_DIV_YOKO  //画像を分割する総数

//エラーメッセージ
#define START_ERR_TITLE			TEXT("スタート位置エラー")
#define START_ERR_CAPTION		TEXT("スタート位置が決まってません")

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//音楽のパス
#define MUSIC_START_BGM_PATH	TEXT(".\\MUSIC\\waiting_room.mp3")		//スタート画面のBGM
#define MUSIC_PLAY_BGM_PATH		TEXT(".\\MUSIC\\Green_Life.mp3")		//プレイ画面のBGM

//制限時間
#define TIMELIMIT				60 * 1000		//60秒間
#define EASY					5 * 1000

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
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGI = 3,
};  //キャラクターのスピード

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
	iPOINT Human_CollBeforePt;		//当たる前の座標
}HUMAN;  //最初に出現する用

typedef struct STRUCT_HUMAN_TIME
{
	IMAGE Humanimage;				//イメージ構造体
	BOOL IsDraw;					//描画できるか否か

	RECT HumanCons_Coll;			//当たり判定
	iPOINT HumanCons_CollBeforePt;	//当たる前の座標
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

int GameScene;					//ゲームシーンを管理

//画像関連
IMAGE ImageStartBG;				//スタート画面の背景
IMAGE ImageTitle;				//タイトルロゴ
IMAGE ImagePlayBG;				//プレイ画面の背景
IMAGE ImageHuman;				//人間(客)の描画

HUMAN IMAGEHuman[5];			//スタート時に最初の人間を描画(5人から)
HUMAN_CONSTANT Human_Cons[20];	//一定時間ごとに出現する用の人間を配列で管理
int TimeDraw = 0;				//Human_Consの配列の添え字

CHARA player;					//キャラクター

//音楽関連
MUSIC Start_BGM;				//スタート画面の背景
MUSIC Play_BGM;					//プレイ画面の背景

//時間関連
int StartTime = 0;				//計測開始時間
int ElaTime = 0;				//残り時間
int CDTimeLimit = 0;			//カウントダウン用の制限時間(CD = Count Down)
int TimeLimit = 0;				//制限時間
BOOL First_flg = TRUE;			//ゲームに入る際のカウントダウンをする
BOOL CountDown = TRUE;			//カウントダウンをする際の基準時間を確保する
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

//######プロトタイプ宣言######
VOID MY_FPS_UPDATE(VOID);				//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);					//FPS値を描画する
VOID MY_FPS_WAIT(VOID);					//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);		//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);					//キーを押しているか、キーコードで判断する

VOID MY_START(VOID);					//スタート画面
VOID MY_START_PROC(VOID);				//スタート画面の処理
VOID MY_START_DRAW(VOID);				//スタート画面の描画

VOID MY_PLAY(VOID);						//プレイ画面
VOID MY_PLAY_PROC(VOID);				//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);				//プレイ画面の描画

VOID MY_END(VOID);						//エンド画面
VOID MY_END_PROC(VOID);					//エンド画面の処理
VOID MY_END_DRAW(VOID);					//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);				//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);				//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);				//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);				//音楽をまとめて削除する関数

BOOL MY_CHECK_MAP_PLAYER_COLL(RECT);	//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//領域の当たり判定をする関数

int MY_CHECK_HUMAN_PLAYER_COLL(RECT);	//マップとプレイヤーの当たり判定をする関数
VOID COLLPROC(VOID);					//マップとプレイヤーの当たり判定をする関数				

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

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//プレイヤーの最初の位置を、スタート位置にする
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
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

		//プレイヤーの中心位置を計算する
		//player.CenterX = startPt.x;
		//player.CenterY = startPt.y;

		//プレイヤーの画像の位置を設定する
		player.image.x = startPt.x;
		player.image.y = startPt.y;

		//プレイ画面に向けて準備
		TimeLimit = TIMELIMIT;			//制限時間を設定
		GameScene = GAME_SCENE_PLAY;	//プレイシーンへ移動する

		//ここで描画位置を決める(最初に出現する用)
		for (int i = 0; i < 5; i++)
		{
			IMAGEHuman[i].image.x = MAP_DIV_WIDTH * GetRand(15);
			IMAGEHuman[i].image.y = MAP_DIV_HEIGHT * GetRand(10);

			IMAGEHuman[i].Human_Coll.left = IMAGEHuman[i].image.x + 1;
			IMAGEHuman[i].Human_Coll.top = IMAGEHuman[i].image.y + 1;
			IMAGEHuman[i].Human_Coll.right = IMAGEHuman[i].image.x + MAP_DIV_WIDTH - 1;
			IMAGEHuman[i].Human_Coll.bottom = IMAGEHuman[i].image.y + MAP_DIV_HEIGHT - 1;
		}
		//ここで描画位置を決める(一定時間で出現する用)
		for (int i = 0; i < 15; i++)
		{
			Human_Cons[i].Humanimage.x = 60 * GetRand(15);
			Human_Cons[i].Humanimage.y = 60 * GetRand(10);
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
	//BGMが流れていないなら
	if (CheckSoundMem(Play_BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, Play_BGM.handle);  //50%の音量にする
		PlaySoundMem(Play_BGM.handle, DX_PLAYTYPE_LOOP);		//ループ再生
	}

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
			ConstantTime = GetNowCount();	//本番に向けて基準時間を取得
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

			//次もカウントダウンを行うため元に戻す
			First_flg = TRUE;
			CountDown = TRUE;

			return;
		}

		//一定時間で人間を出現させる処理
		if (NowCount2 - ConstantTime >= EASY)
		{
			Human_Cons[TimeDraw].IsDraw = TRUE;		//描画できる
			TimeDraw++;								//次の配列に
			ConstantTime = GetNowCount();			//再度時間を取得してリセット
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

		//当たり判定
		COLLPROC();
	}

	return;
}

//プレイ画面の描画
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
	
	DrawString(0, 0, "プレイ画面(スペースキーを押してください)", GetColor(255, 255, 255));

	if (First_flg)  //最初のカウントダウン
	{
		DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", (ElaTime / 1000) + 1);
	}
	else
	{
		//制限時間の表示
		//1000で割って「ミリ秒単位」から「秒単位」に
		//0 が出てきてしまうので +1する
		if ((ElaTime / 1000 + 1) <= 3)  //残り 秒は赤字にする
			DrawFormatString(0, 0, GetColor(255, 0, 0), "%d", (ElaTime / 1000) + 1);
		else
			DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", (ElaTime / 1000) + 1);

		//当たり判定の描画(デバッグ用)
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
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
		for (int i = 0; i < 5; i++)
		{
			if(IMAGEHuman[i].IsDraw == TRUE)
				DrawGraph(IMAGEHuman[i].image.x, IMAGEHuman[i].image.y, IMAGEHuman[i].image.handle, TRUE);
		}
		//一定時間で出現する用
		for (int i = 0; i < 15; i++)
		{
			if (Human_Cons[i].IsDraw == TRUE)
				DrawGraph(Human_Cons[i].Humanimage.x, Human_Cons[i].Humanimage.y, Human_Cons[i].Humanimage.handle, TRUE);
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
	//player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_MIDI;								//スピードを設定

	//↓人間(客)の画像↓
	//最初に出現する用
	for (int i = 0; i < 5; i++)  //読み込み
	{
		strcpy_s(IMAGEHuman[i].image.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 5; i++)
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
		IMAGEHuman[i].IsDraw = TRUE;
	}
	//一定時間で描画する用
	for (int i = 0; i < 15; i++)  //読み込み
	{
		strcpy_s(Human_Cons[i].Humanimage.path, IMAGE_HUMAN_PATH);
	}
	for (int i = 0; i < 15; i++)
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
		Human_Cons[i].IsDraw = FALSE;
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

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
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
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageStartBG.handle);		//スタート画面の背景
	DeleteGraph(ImageTitle.handle);			//タイトルロゴ
	DeleteGraph(ImagePlayBG.handle);		//プレイ画面の背景

	DeleteGraph(player.image.handle);		//プレイヤー画像

	DeleteGraph(ImageHuman.handle);			//人間(客)の削除

	for (int i = 0; i < 5; i++)				//最初に出現する用
	{
		DeleteGraph(IMAGEHuman[i].image.handle);
	}

	for (int i = 0; i < 15; i++)			//一定時間で出現する用
	{
		DeleteGraph(Human_Cons[i].Humanimage.handle);
	}

	//マップチップの削除
	for (int num = 0; num < MAP_DIV_NUM; num++)
	{
		DeleteGraph(mapChip.handle[num]);
	}

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

//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_MAP_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
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

//マップとプレイヤーの当たり判定をする関数
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

	//プレイヤーと壁が当たっていたら
	if (MY_CHECK_HUMAN_PLAYER_COLL(player.coll) == 1)
	{
		//通り抜け不可
		player.image.x = player.collBeforePt.x;		//今いる場所のX座標を代入
		player.image.y = player.collBeforePt.y;		//今いる場所のY座標を代入
	}

	//常に座標を取得しておく
	player.collBeforePt.x = player.image.x;
	player.collBeforePt.y = player.image.y;

	return;
}