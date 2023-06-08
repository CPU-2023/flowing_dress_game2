#include "flowing_dress_game.h"
#include "modules.h"

// ���� ���� ������
struct user
{
	char name[10];
	int score;
};

// ȭ��ǥ ��ġ ������
struct position
{
	int by, by_last;
	int cx, cy;
};

// ���� �� ���� ������
struct game_data
{
	int score, score_ptf;
	int diff, life;
	int begin_menu, menu_change, start_re;
	char diff_ch[5];
};

struct user _userData;

struct position cursor1 = { 17,17,12,18 };
//by(�� �����Ҷ� ȭ��ǥ y��) ,by_last,cx,cy


struct game_data game_info1 = { 0, 10,0,5,0,0,0,"�ʱ�" };
//score,score_ptf,diff,life,begin_menu,menu_change,start_re

//static int bx=16,by=17,by_last=17,cx=12,cy=18,score,life=5,begin_menu=0,menu_change=0,score_ptf=1000,diff=0;

/* ���� ���� */

// �÷��̾� ����
//test

char player[2] = "��";

// ���� Ȯ�� ����
int auth = 0;

int map[2][20][12] =
{ {
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1

},
{
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,2,0,0,0,0,0,0,0,1,
		1,0,2,0,2,0,2,2,2,0,2,1,
		1,0,0,0,0,0,0,0,2,0,2,1,
		1,2,2,2,2,2,2,2,2,0,2,1,
		1,0,0,0,0,0,2,0,0,0,2,1,
		1,0,0,2,0,0,2,2,2,0,2,1,
		1,0,2,0,2,0,0,0,0,0,2,1,
		1,0,0,2,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1
} };

MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;

char* d_server = "127.0.0.1";
char* d_user = "root";
char* d_password = "mirim";
char* d_database = "cpu";


int main()
{
	system("mode con cols=120 lines=30 | title Flowing Dress Game");

	CursorView();

	srand(time(NULL));

	while (1)
	{


		while (!game_info1.begin_menu)
		{
			system("cls");
			show_title();
			show_menu();

			conn = mysql_init(NULL);

			// MySQL ������ ����
			if (!mysql_real_connect(conn, d_server, d_user, d_password, d_database, 0, NULL, 0)) {
				fprintf(stderr, "%s\n", mysql_error(conn));
				exit(1);
			}

			// mysql ���� �� ���� ū score�� select�ϱ�
			show_weight(33, conn);

			// �޴� ����
			select_menu(76, 92, 23, 20, 17);

			// ��������
			if (game_info1.menu_change == 1) {
				select_map();
			}
			else if (game_info1.menu_change == 2) {
				show_rank();
			}

		}
		//���� �̸� �Է¹ޱ�
		set_user();

		// ���� ����
		game_start();
	}
	// ���� ����
	mysql_free_result(res);
	mysql_close(conn);
}

void select_map() {
	if (game_info1.menu_change == 1)
	{
		system("cls");
		show_map();
		gotoxy(80, 17);
		GRAY printf("   �ʱ�");
		gotoxy(80, 20);
		DARK_YELLOW printf("   �߱�");
		gotoxy(80, 23);
		BLOOD printf("   ���");
		WHITE cursor1.by = cursor1.by_last;
		gotoxy(76, cursor1.by);
		printf("��");
		gotoxy(92, cursor1.by);
		printf("��");

		// ���̵� ����
		while (1) {
			select_menu(76, 92, 23, 20, 17);
			if (game_info1.menu_change == 0) break;
		}

		cursor1.by_last = cursor1.by;
		cursor1.by = 20;

	}
}

void set_user()
{
	int setX = 14, setY = 9;
	system("cls");
	gotoxy_2x(setX, setY++); printf("����������������������������������������������������������������������������������������������������������������������������\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("��                                                            ��\n");
	gotoxy_2x(setX, setY++); printf("����������������������������������������������������������������������������������������������������������������������������");

	setY = 9;
	gotoxy_2x(setX + 5, setY + 4);
	printf("* �����ڴ� �̸��� ����� �Է����ּ���(5���̳�) *\n");
	gotoxy_2x(setX + 15, setY + 6);
	scanf("%s", _userData.name);

	// ����� ����Ȯ��
	auth = 1;

	system("cls");
	Sleep(300);
}

void show_rank()
{
	system("cls");


	conn = mysql_init(NULL);

	// MySQL ������ ����
	if (!mysql_real_connect(conn, d_server, d_user, d_password, d_database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}



	// �� insert �Ǿ� �Ǵ��� üũ
	if (auth) insert_data(conn);



	int x = 35, y = 4;
	WHITE

		gotoxy(x, y++); printf(",------.                 ,--.    ,--.                ");

	gotoxy(x, y++); printf("|  .--. ' ,--,--.,--,--, |  |,-. `--',--,--,  ,---.  ");
	gotoxy(x, y++); printf("|  '--'.'' ,-.  ||      \|     / ,--.|      \\| .-. | ");
	gotoxy(x, y++); printf("|  |\\  \\ \\ '-'  ||  ||  ||  \\  \\ |  ||  ||  |' '-' ' ");
	gotoxy(x, y++); printf("`--' '--' `--`--'`--''--'`--'`--'`--'`--''--'.`-  /  ");
	gotoxy(x, y++); printf("                                             `---'   ");


	x = 50, y = 14;

	// SELECT ���� ����
	if (mysql_query(conn, "SELECT * FROM flowing_dress ORDER BY score DESC")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	// ���� ��� ��������
	res = mysql_store_result(conn);

	// ��� ���
	gotoxy(x, y);
	int i = 1;
	int cnt = 0;
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (cnt > 7) break;
		gotoxy(x, y++);
		printf("%d\t %s   %s\n", i++, row[0], row[1]);
		cnt++;
	}

	// ���� ����
	mysql_free_result(res);
	mysql_close(conn);

	game_info1.menu_change = 0;
	auth = 0;

	// �Է¹����� ����ȭ������
	gotoxy(40, 25);
	printf("����ȭ������ ���ư����� �ƹ�Ű�� ��������");
	_getch();
}

void game_start() {
	int kb, kb1, n[20], ran[20], swit[19], sleep_num = 0;
	register int i, j;

	cursor1.by = 17, cursor1.cx = 12, cursor1.cy = 18, game_info1.score = 0, game_info1.life = 5, game_info1.start_re = 0, game_info1.begin_menu = 0;
	for (i = 0; i < 20; i++)
		n[i] = 1;
	for (i = 0; i < 19; i++)
		swit[i] = 0;

	gotoxy(0, 0);
	system("cls");

	map_ptf(0);//����� 

	gotoxy(cursor1.cx, cursor1.cy);
	BLUE_GREEN printf("%s", player);

	/*���� ����  �ʱ�ȭ*/
	for (i = 0; i < 20; i++)
	{
		do
		{
			ran[i] = rand() % 19 + 2;
		} while ((ran[i] % 2 == 0 ? 1 : 0) == 0);//Ȧ���� ������ �׸� �׵θ�ĭ�̶� ��ĭ�̶� ���� ������ ¦���� ���� 
	}

	// ���� ���� ����
	gotoxy(28, 2);
	PURPLE printf("���̵� : %s", game_info1.diff_ch);
	gotoxy(28, 6);
	LIGHT_GREEN printf("���� : ");
	gotoxy(28, 8);
	RED printf("��� : ");
	gotoxy(28, 9);
	BLUE printf("Ŭ���� ���� :");
	gotoxy(40, 9);
	printf("%d��", game_info1.score_ptf);
	gotoxy(28, 11);
	GRAY printf(" ����Ű");
	gotoxy(28, 13);
	printf(" ��  ��");

	if (game_info1.diff == 0)
		sleep_num = 22;
	else if (game_info1.diff == 1)
		sleep_num = 20;
	else if (game_info1.diff == 2)
		sleep_num = 10;

	int j_count = 0;

	// ���� �˰���
	for (i = 1; ; i++)
	{

		Sleep(sleep_num);

		if (_kbhit())
			move();

		if (i % 100 == 0)
		{
			j_count++;
		}

		if (_kbhit())
			move();

		for (j = 0; j <= j_count; j++)
		{
			food_data(&n[j], &ran[j]);
		}

		if (_kbhit())
			move();

		Sleep(sleep_num);

		if (_kbhit())
			move();

		for (j = 0; j < 20; j++)
		{
			int a;
			a = player_dead(&ran[j], &n[j]);
			if (a == 1)
			{
				if (game_info1.life == 0)
				{
					break;
				}
				else
				{
					game_info1.life--;
					game_info1.score -= 5;
				}
			}
		}

		if (_kbhit())
			move();

		Sleep(sleep_num);

		if (_kbhit())
			move();

		gotoxy(35, 6);
		LIGHT_GREEN printf("%-4d", game_info1.score);
		gotoxy(35, 8);
		RED printf("%d", game_info1.life);
		gotoxy(48, 26);

		if (_kbhit())
			move();

		Sleep(sleep_num);

		if (_kbhit())
			move();

		if (game_info1.score >= game_info1.score_ptf)//�¸����� 
			break;
		else if (game_info1.life == 0)//�й����� 
			break;
	}
	if (game_info1.score >= game_info1.score_ptf)//�¸����� 
	{
		_userData.score = game_info1.score;
		end_game("���� Ŭ����");
		show_rank();
	}
	else if (game_info1.life == 0 && game_info1.score <= game_info1.score_ptf)//�й����� 
	{
		_userData.score = game_info1.score;
		end_game("���� ����");
		show_rank();
	}

}

void end_game() {
	int input;

	gotoxy(5, 11);
	printf("ESC - ���ư���");
	do
	{
		input = _getch();
	} while (input != ESC);
	system("cls");
	game_info1.start_re = 1;
}

void show_menu()
{
	// ���
	int x = 17, y = 20;
	WHITE
		gotoxy(x, y++); printf("������ ����� ��ȥ�ĳ�~!");
	gotoxy(x, y++); printf("�������� ������ ���ؼ� �ź��� �巹����");
	gotoxy(x, y++); printf("�귯������ �ʰ� �ϼ���!");


	gotoxy(80, 17);
	if (game_info1.start_re == 0)
	{
		LIGHT_BLUE printf(" �����ϱ�");
	}
	else
	{
		RED printf(" �ٽ��ϱ�");
	}

	gotoxy(80, 20);
	BLUE printf(" ��������");
	gotoxy(80, 23);
	YELLOW printf(" ��ŷ����");
	WHITE
		gotoxy(76, cursor1.by);
	printf("��");
	gotoxy(92, cursor1.by);
	printf("��");
}

void show_map()
{
	int x = 17, y = 3;
	YELLOW
		gotoxy(x, y++); printf(" ________  __                       _    ");
	gotoxy(x, y++); printf("|_   __  |[  |                     (_)   ");
	gotoxy(x, y++); printf("  | |_ \\_| | |  .--.   _   _   __  __   _ .--.   .--./)  ");
	gotoxy(x, y++); printf("  |  _|    | |/ .'`\\ \\[ \\ [ \\ [  ][  | [ `.-. | / /'`\\;");
	gotoxy(x, y++); printf(" _| |_     | || \\__. | \\ \\/\\ \\/ /  | |  | | | | \\ \\._//");
	gotoxy(x, y++); printf("|_____|   [___]'.__.'   \\__/\\__/  [___][___||__].',__`");
	gotoxy(x, y++); printf("|_   _ `.                                      ( ( __))");
	gotoxy(x, y++); printf("  | | `. \\ _ .--.  .---.  .--.   .--.");
	gotoxy(x, y++); printf("  | |  | |[ `/'`\\]/ /__\\\\( (`\\] ( (`\\]");
	gotoxy(x, y++); printf(" _| |_.' / | |    | \\__., `'.'.  `'.'.");
	gotoxy(x, y++); printf("|______.' [___]    '.__.'[\\__) )[\\__) )");

}

void map_ptf(int k)
{
	int i, j;

	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 12; j++)
		{
			switch (map[k][i][j])
			{
			case 0:
				printf("  "); break;
			case 1:
				PLUM printf("��"); break;
			case 2:
				YELLOW printf("��"); break;

			}
		}
		putchar('\n');
	}
}

void food_data(int* n, int* ran)
{
	int rand_food = rand() % 2;

	if (*n < 19)
	{
		if (*n != 1)
		{
			gotoxy(*ran, *n - 1);
			printf("  ");
		}

		gotoxy(*ran, *n);
		if (rand_food) {
			YELLOW printf("��");
		}
		else {
			RED printf("��");
		}
		;

		(*n)++;
	}
	else
	{
		gotoxy(*ran, *n - 1);
		printf("  ");
		gotoxy(cursor1.cx, cursor1.cy);
		BLUE_GREEN printf("%s", player);//���İ� �÷��̾ ���� ��ġ�� ��ġ�ɰ�� ������� ���� ���� �Ƚ� 
		*n = 1;
		game_info1.score += 5;
		do
		{
			*ran = rand() % 19 + 2;
		} while (((*ran) % 2 == 0 ? 1 : 0) == 0);

	}
	gotoxy(48, 26);

}

void move()
{
	register int kb;

	kb = _getch();

	switch (kb)
	{
	case LEFT:
		if (map[0][cursor1.cy][cursor1.cx / 2 - 1] == 0)//�̵��� ��ġ�� �迭�� �ִ�.
													//�̵��� ��ġ = �迭���̴� �浹���ǵ�����. 
		{
			gotoxy(cursor1.cx, cursor1.cy);//���� ĳ���ͷ� Ŀ���̵� 
			printf("  ");//����� 
			cursor1.cx -= 2;//����Ű���� Ŀ�� �� ���� 
			gotoxy(cursor1.cx, cursor1.cy);//Ŀ�� �̵� 
			BLUE_GREEN printf("%s", player);//ĳ���� ��� 
			gotoxy(48, 26);//Ŀ�� �������� 
		}
		break;

	case RIGHT:
		if (map[0][cursor1.cy][cursor1.cx / 2 + 1] == 0)
		{
			gotoxy(cursor1.cx, cursor1.cy);
			printf("  ");
			cursor1.cx += 2;
			gotoxy(cursor1.cx, cursor1.cy);
			BLUE_GREEN printf("%s", player);
			gotoxy(48, 26);
		}
		break;
		/*case UP :
					gotoxy(cursor1.cx,cursor1.cy);
					BLUE_GREEN printf("%s", player);
					gotoxy(48,26);
					break;*/
					// �÷��� �߰��� ESC������ ����ȭ������ ���� �ϱ�
					//case ESC:
					//	break;
	}
}

int player_dead(int* ran, int* n)
{
	if (*ran == cursor1.cx && *n == 19)
	{
		gotoxy(cursor1.cx, cursor1.cy);
		RED printf("\a��");
		Sleep(300);
		return 1;
	}
	else
		return 0;
}

void select_menu(int left_key, int right_key, int key1, int key2, int key3)
{
	int kb1 = _getch();

	switch (kb1)
	{
	case DOWN:
		if (cursor1.by + 3 <= key1)
		{
			gotoxy(left_key, cursor1.by);
			printf("  ");
			gotoxy(right_key, cursor1.by);
			printf("  ");
			cursor1.by += 3;
			gotoxy(left_key, cursor1.by);
			printf("��");
			gotoxy(right_key, cursor1.by);
			printf("��");
		}
		break;
	case UP:
		if (cursor1.by - 3 >= key3)
		{
			gotoxy(left_key, cursor1.by);
			printf("  ");
			gotoxy(right_key, cursor1.by);
			printf("  ");
			cursor1.by -= 3;
			gotoxy(left_key, cursor1.by);
			printf("��");
			gotoxy(right_key, cursor1.by);
			printf("��");
		}
		break;
	case ENTER:
		// ���� ���� ����
		if (game_info1.menu_change == 0 && cursor1.by == key3)
			game_info1.begin_menu = 1;

		// ���̵� ���� ����
		else if (game_info1.menu_change == 0 && cursor1.by == key2)
		{
			//system("cls");
			game_info1.menu_change = 1;
		}

		// ��ŷ ����
		else if (game_info1.menu_change == 0 && cursor1.by == key1)
			game_info1.menu_change = 2;

		/* ���̵� ���� */

		// �ʱ� ���� ������ ������ �Է�
		else if (game_info1.menu_change == 1 && cursor1.by == key3)
		{
			// ���� ��ǥ����, ����, �޴� ����, �ܰ� ������ �Է�
			game_info1.score_ptf = 1000;
			game_info1.diff = 0;
			game_info1.menu_change = 0;
			game_info1.begin_menu = 1;
			strcpy(game_info1.diff_ch, "�ʱ�");
		}
		else if (game_info1.menu_change == 1 && cursor1.by == key2)
		{
			game_info1.score_ptf = 3000;
			game_info1.diff = 1;
			game_info1.menu_change = 0;
			game_info1.begin_menu = 1;
			strcpy(game_info1.diff_ch, "�߱�");
		}
		else if (game_info1.menu_change == 1 && cursor1.by == 23)
		{
			game_info1.score_ptf = 6000;
			game_info1.diff = 2;
			game_info1.menu_change = 0;
			game_info1.begin_menu = 1;
			strcpy(game_info1.diff_ch, "���");
		}
		break;

	case ESC:
		exit(1);
		break;

	}
}

void show_title()
{

	int x = 17, y = 3;
	YELLOW
		gotoxy(x, y++); printf(",------.,--.                  ,--.                ");
	gotoxy(x, y++); printf("|  .---'|  | ,---. ,--.   ,--.`--',--,--,  ,---.  ");
	gotoxy(x, y++); printf("|  `--, |  || .-. ||  |.'.|  |,--.|      \\| .-. | ");
	gotoxy(x, y++); printf("|  |`   |  |' '-' '|   .'.   ||  ||  ||  |' '-' ' ");
	gotoxy(x, y++); printf("`--'    `--' `---' '--'   '--'`--'`--''--'.`-  /  ");
	gotoxy(x, y++); printf(",------.                                  `---'   ");
	gotoxy(x, y++); printf("|  .-.  \\ ,--.--. ,---.  ,---.  ,---.             ");
	gotoxy(x, y++); printf("|  |  \\  :|  .--'| .-. :(  .-' (  .-'             ");
	gotoxy(x, y++); printf("|  '--'  /|  |   \\   --..-'  `).-'  `)            ");
	gotoxy(x, y++); printf("`-------' `--'    `----'`----' `----'             ");


}

void show_weight()
{
	int x = 80, y = 3;

	// SELECT ���� ����
	if (mysql_query(conn, "SELECT MAX(score) FROM flowing_dress")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	// ���� ��� ��������
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	// ��� ���


	// �ְ� ������
	gotoxy(x, y++);  printf("  �ְ� ����");
	gotoxy(x, y++); printf("---------------------");
	gotoxy(x, y++); printf("|                    |");
	gotoxy(x, y++); printf("|       %s��       |", row[0]);
	gotoxy(x, y++); printf("|                    |");
	gotoxy(x, y++); printf("---------------------");
}

void insert_data(MYSQL* con) {
	char query[100];

	sprintf(query, "INSERT INTO flowing_dress (name, score) VALUES('%s', %d)", _userData.name, _userData.score);

	if (mysql_query(con, query)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

}
