#define _CRT_NONSTDC_NO_WARNINGS	//kbhit(), getch()���g�p���邽�߂̋L�q
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include<stdio.h>
#include<conio.h>//�L�[���͗p
#include<Windows.h>//sleep()���g������

//�}�b�v�f�[�^�̒�`
//#:�ǁAP:�v���C���[�AB:���AG:�S�[��
#define MAP_W 22
#define MAP_H 11
char map[MAP_H][MAP_W] = {
	//"####################",
	//"#        #     B G #",
	//"#   ##       ###   #",
	//"#G  #         #    #",
	//"#   #    B    # P  #",
	//"#   #         #    #",
	//"#   ##        #    #",
	//"#        #    G B  #",
	//"#        #  ##     #",
	//"#        #         #",
	//"####################",
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

//�}�b�v�̏�����Ԃ�ۊǂ���ϐ�
char tmp_map[MAP_H][MAP_W];

//�Q�[���ň����ϐ��̒�`
int player_x = 1, player_y = 1;


//�J�[�\���ʒu���w�肷��֐�
void cursor(int x, int y) {
	printf("\x1b[%d;%dH", y + 1, x + 1);
}

//�����╶����̐F���w�肷��֐�
enum { BLACK, RED, GREEN, YELLOW, MAGENTA, CYAN, WHITE };
void color(int col) {
	printf("\x1b[3%dm", col);
}

//�Q�[����ʂ�`���֐�
void draw_map(void) {
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			if (tmp_map[y][x] == 'G' && map[y][x] == ' ')map[y][x] = 'G';
			if (map[y][x] == '#') color(GREEN);
			if (map[y][x] == 'B') color(YELLOW);
			if (map[y][x] == 'G') color(WHITE);
			//if (map[y][x] == 'P') color(MAGENTA);
			cursor(x, y);
			printf("%c", map[y][x]);
		}
	}
}

//�v���C���[�̈ʒu�ϐ��ɑ������֐�
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

//�ړ��\���o
bool is_move_ok(int x, int y) {
	if (map[y][x] == '#')return FALSE;
	if (map[y][x] == 'B')return FALSE;
	return TRUE;
}

//�u���b�N�̈ړ�����
void move_block(int x, int y) {
	if (is_move_ok(x, y)) {

	}
}

//�Q�[���N���A����
//�S�Ă̔����S�[����ɏ���Ă��邱�Ƃ��`�F�b�N����
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

//main�֐�
int main(void) {
	//�����}�b�v���R�s�[���đޔ����Ă���
	for (int y = 0; y < MAP_H; y++) {
		for (int x = 0; x < MAP_W; x++) {
			tmp_map[y][x] = map[y][x];
		}
	}
	//�v���C���[�̌��ݒn�����߂�
	search_player_position();
	//�v���C���[�̏����ʒu�͍폜����
	map[player_y][player_x] = ' ';
	//�Q�[�����[�v
	while (1) {
		//�L�[���́A�v���C���[�̈ړ�
		int key = 0;
		if (kbhit())key = getch();
		//�ړ���
		if (key == KEY_UP && is_move_ok(player_x, player_y - 1)) {
			player_y--;
		} else if (key == KEY_UP && map[player_y - 1][player_x] == 'B' && is_move_ok(player_x, player_y - 2)) {
			//�u���b�N�ړ�����
			map[player_y - 1][player_x] = ' ';
			map[player_y - 2][player_x] = 'B';
			player_y--;
		}
		//�ړ���
		if (key == KEY_DOWN && is_move_ok(player_x, player_y + 1)) {
			player_y++;
		} else if (key == KEY_DOWN && map[player_y + 1][player_x] == 'B' && is_move_ok(player_x, player_y + 2)) {
			//�u���b�N�ړ�����
			map[player_y + 1][player_x] = ' ';
			map[player_y + 2][player_x] = 'B';
			player_y++;
		}
		//�ړ���
		if (key == KEY_LEFT && is_move_ok(player_x - 1, player_y)) {
			player_x--;
		} else if (key == KEY_LEFT && map[player_y][player_x - 1] == 'B' && is_move_ok(player_x - 2, player_y)) {
			//�u���b�N�ړ�����
			map[player_y][player_x - 1] = ' ';
			map[player_y][player_x - 2] = 'B';
			player_x--;
		}
		//�ړ��E
		if (key == KEY_RIGHT && is_move_ok(player_x + 1, player_y)) {
			player_x++;
		} else if (key == KEY_RIGHT && map[player_y][player_x + 1] == 'B' && is_move_ok(player_x + 2, player_y)) {
			//�u���b�N�ړ�����
			map[player_y][player_x + 1] = ' ';
				map[player_y][player_x + 2] = 'B';
				player_x++;
		}

		//�}�b�v�̍X�V
		draw_map();
		//�v���C���[�̈ʒu�̍X�V
		cursor(player_x, player_y);
		color(RED);
		printf("P");
		cursor(MAP_W, MAP_H);
		//�ҋ@����
		Sleep(50);
		//�Q�[���N���A����
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