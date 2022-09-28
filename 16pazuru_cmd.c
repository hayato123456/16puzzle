//完成
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
int _i = 3, _j = 3;
int num[4][4];

int result(int y, int x) {//終了判定
	int count = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (i == (num[i][j] - 1) / 4 && j == ((num[i][j] - 1) % 4)) //数値を4で割った商と余りが一致してたらTrue
				count++;
		}
	}
	printf("\n正しい位置にある数:%d", count);
	if (count == 16)
		return 1;
	else
		return 0;
}

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
			num[j % 4][v - 1] = z + 1;//2次元配列の適当な場所に入れる
			i--;
			j++;
		}
	}
}

void swap(int y, int x) {//入れ替え//スワップ
	int swap;
	swap = num[x][y];
	num[x][y] = num[_i][_j];
	num[_i][_j] = swap;
}

int check(int y, int x) {//動かせるかチェック
	if (num[x][y - 1] == 16 || num[x][y + 1] == 16 ||//空いてる空間からみて押した場所が上下左右だったらTRUE
		num[x + 1][y] == 16 || num[x - 1][y] == 16)
		return 1;
	else
		return 0;
}

int main() {//メイン処理
	int x = 0;
	int player_x = 0, player_y = 0;
	printf("キーを押してください！");
	shuffle();//ランダムに並び替え
	while (x != 1) {
		switch (_getch()) {//キー操作
		case('s'):
			if (player_x < 3)
				player_x++;
			break;
		case('w'):
			if (player_x > 0)
				player_x--;
			break;
		case('d'):
			if (player_y < 3)
				player_y++;
			break;
		case('a'):
			if (player_y > 0)
				player_y--;
			break;
		case('v'):
			x = 1;//処理を抜ける
			break;
		case('k'):
			if (check(player_y, player_x))//チェックフラグがたったらスワップ
				swap(player_y, player_x);
			break;
		}
		system("cls");//画面リセット
		printf("操作方法\n");
		printf("A:左に移動 D:右に移動 W:上に移動 S:下に移動 K:動かす V:ゲームを終了\n\n");
		printf("--------------\n");
		//*****************描画****************************
		for (int i = 0; i <= 4; i++) {
			for (int j = 0; j <= 4; j++) {
				if (i == 4) {
					if (j == player_y)
						printf("↑");
					else
						printf("　 ");
				}

				else if (j == 4) {
					if (i == player_x)
						printf("← ");
					else
						printf(" 　");
				}
				else if (j == player_y && i == player_x) {
					if (num[i][j] / 10 == 0)
						printf("\x1b[31m %d \x1b[m", num[i][j]);//出力の色を変える
					else if (num[i][j] == 16)
						printf("\x1b[31m□ \x1b[m");//出力の色を変える
					else
						printf("\x1b[31m%d \x1b[m", num[i][j]);//出力の色を変える
				}
				else if (num[i][j] == 16) {
					_i = i, _j = j;
					printf("　 ");
				}
				else {
					if (num[i][j] / 10 == 0)
						printf(" %d ", num[i][j]);
					else
						printf("%d ", num[i][j]);
				}
			}
			printf("\n");
		}
		printf("--------------\n");
		//****************************************************
		if (result(player_x, player_y)) {//終了処理
			system("cls");//画面リセット
			printf("クリア！！");//リザルト画面
			x = 1;
		}
	}
}

