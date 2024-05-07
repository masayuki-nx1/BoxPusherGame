#define _CRT_NONSTDC_NO_WARNINGS	//kbhit(), getch()を使用するための記述
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include<stdio.h>
#include<conio.h>//キー入力用
#include<Windows.h>//sleep()を使うため

//マップデータの定義
//#:壁、P:プレイヤー、B:箱、G:ゴール
#define MAP_W 22
#define MAP_H 11
char map[MAP_H][MAP_W] = {
	"    #####        ",
	"    #   #        ",
	"    #B  #        ",
	"  ###  B###      ",
	"  #  B  B #      ",
	"### # ### #######",
	"#   # ### ##  GG#",
	"# B  B      P GG#",
	"##### #### #  GG#",
	"    #      ######",
	"    ########     ",

};

//マップの初期状態を保管する変数
char tmp_map[MAP_H][MAP_W];

//ゲームで扱う変数の定義
int player_x = 1, player_y = 1;

// 関数のプロトタイプ宣言
void cursor(int x, int y);
void color(int col);
void draw_map(void);
void search_player_position(void);
bool is_move_ok(int x, int y);
void move_block(int x, int y);
bool is_game_clear(void);
void move(int x, int y, int move_x, int move_y);

//カーソル位置を指定する関数
void cursor(int x, int y) {
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//文字や文字列の色を指定する関数
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };
void color(int col) {
	printf("\x1b[3%dm", col);
}

//ゲーム画面を描く関数
void draw_map(void) {
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			if (tmp_map[y][x] == 'G' && map[y][x] == ' ')map[y][x] = 'G';
			if (map[y][x] == '#') color(GREEN);
			if (map[y][x] == 'B') color(YELLOW);
			if (map[y][x] == 'G') color(WHITE);
			if (map[y][x] == 'P') color(RED);
			cursor(x, y);
			printf("%c", map[y][x]);
		}
	}
}

//プレイヤーの位置変数に代入する関数
void search_player_position(void) {
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			if (map[y][x] == 'P') {
				player_x = x;
				player_y = y;
			}
		}
	}
}

//移動可能検出
bool is_move_ok(int x, int y) {
	if (map[y][x] == '#')return FALSE;
	if (map[y][x] == 'B')return FALSE;
	return TRUE;
}

//ブロックの移動処理
void move_block(int x, int y) {
	if (is_move_ok(x, y)) {

	}
}

//ゲームクリア判定
//全ての箱がゴール上に乗っていることをチェックする
bool is_game_clear() {
	bool f = TRUE;
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			if (tmp_map[y][x] == 'G') {
				if (map[y][x] != 'B')f = FALSE;
			}
		}
	}
	return f;
}

void move(int x, int y, int move_x, int move_y) {
	if (is_move_ok(x + move_x, y + move_y)) {
		map[y][x] = ' ';
		map[y + move_y][x + move_x] = 'P';
	}
	else if (map[y + move_y][x + move_x] == 'B' && is_move_ok(x + move_x * 2, y + move_y * 2)) { //2歩先が移動可能か調べる、*2すれば2歩先が調べれれる
		map[y][x] = ' ';
		map[y + move_y][x + move_x] = 'P';
		map[y + move_y * 2][x + move_x * 2] = 'B';
	}
}

//main関数
int main(void) {
	//初期マップをコピーして退避しておく
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			tmp_map[y][x] = map[y][x];
		}
	}

	//ゲームループ
	while (1) {
		//プレイヤーの現在地を求める
		search_player_position();
		//キー入力、プレイヤーの移動
		int key = 0;
		if (kbhit())key = getch();
		//移動上
		if (key == KEY_UP) move(player_x, player_y, 0, -1);
		//移動下
		if (key == KEY_DOWN)move(player_x, player_y, 0, 1);
		//移動左
		if (key == KEY_LEFT)move(player_x, player_y, -1, 0);
		//移動右
		if (key == KEY_RIGHT)move(player_x, player_y, 1, 0);


		//マップの更新
		draw_map();

		//待機する
		Sleep(50);
		//ゲームクリア処理
		if (is_game_clear()) {
			color(RED);
			cursor(MAP_W / 2 - 5, MAP_H / 2);
			printf("GAME CLEAR");
			cursor(0, MAP_H + 1);
			Sleep(1000);
			return 0;
		}
	}
}