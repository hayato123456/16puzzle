#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include <time.h>

int map[4][4] =
{ {1,2,3,4} ,
  {1,2,3,4} ,
  {1,2,3,4} ,
  {1,2,3,4} };

int _i = 3, _j = 3;

void shuffle() {//ランダムな数値の生成
	int array[16] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//使われた番号計測用
	int i = 16, j = 0, v = 0;
	time_t t = time(NULL);//時刻の取得
	while (i >= 1) {//16回ifに入るまで繰り返す
		int z = (rand() + t) % 16;//乱数の生成
		if (array[z] == -1) {
			array[z] = z;//配列を埋めていく
			if (i % 4 == 0)
				v++;
			map[j % 4][v - 1] = z + 1;//2次元配列の適当な場所に入れる
			i--;
			j++;
		}
	}
}


void swap(int y, int x) {//入れ替え//スワップ
	
	int swap;
	swap = map[x][y];
	map[x][y] = map[_j][_i];
	map[_j][_i] = swap;
}

int check(int y, int x,int _i,int _j) {//動かせるかチェック
	
	if ((map[x][y - 1] == 16 && y-1>= 0) || (map[x][y + 1] == 16 && y+1 <= 3) ||//空いてる空間からみて押した場所が上下左右だったらTRUE
		map[x + 1][y] == 16 || map[x - 1][y] == 16){
		//DrawFormatString(0, 0, GetColor(255, 255, 0), "1回目の座標x:%d y:%d ", _i, _j);
		//WaitKey();
		return 1;
	}
	else
		return 0;
}
// スタート
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{	

	int MouseX, MouseY;
	char str[66] = "";
	char buf[12];
	int test = 3;
	int PosY, PosX;
	shuffle();

	ChangeWindowMode(TRUE);
	SetGraphMode(384, 384, 32);
	//初期化
	if (DxLib_Init() == -1)return -1;
	SetMouseDispFlag(TRUE);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面消去
		//ClearDrawScreen();
		if (ProcessMessage() != 0)break; //プロセスの同期にエラーが起きたら終了
		GetMousePoint(&MouseX, &MouseY);//マウスの位置取得
		
		for (int i = 0; i < 4; i++) 
			for (int j = 0; j < 4; j++) {
				if(map[j][i] == 16)
					_i = i, _j = j;
				strcpy_s(str, 32, "texture/");
				sprintf(buf,  "%d", map[i][j]);
				strcat_s(str, 32, buf);
				strcat_s(str,32, ".png");
				LoadGraphScreen(64 * i + 64, 64 * j + 64, str, TRUE);
			}
		
		
		PosX = MouseX / 64 -1;
		PosY = MouseY  / 64 -1;
		//DrawFormatString(0, 0, GetColor(255, 255, 0), "1回目の座標x:%d y:%d _x:%d, _y:%d", PosX, PosY,_i,_j);
		// キー入力待ち
		//WaitKey();
		if (check(PosY, PosX,_i,_j)) {//チェックフラグがたったらスワップ{
			DrawFormatString(0, 0, GetColor(255, 255, 0), "%d",map[PosX][PosY + 1] );
			//DrawFormatString(0, 0, GetColor(255, 255, 0), "1回目の座標x:%d y:%d _x:%d, _y:%d", PosX, PosY, _i, _j);
			//WaitKey();
				//DrawFormatString(0, 0, GetColor(255, 255, 0), "1回目の座標x:%d y:%d _x:%d, _y:%d", PosX, PosY, _i, _j);
			swap(PosY, PosX);
			//WaitKey();
		}
		ClearDrawScreen();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (map[j][i] == 16)
					_i = i, _j = j;
				strcpy_s(str, 32, "texture/");
				sprintf(buf, "%d", map[i][j]);
				strcat_s(str, 32, buf);
				strcat_s(str, 32, ".png");
				LoadGraphScreen(64 * i + 64, 64 * j + 64, str, TRUE);
			}
		WaitKey();
	}
		
	// 終了処理
	DxLib_End();				
	return 0;				
}
