//��֮ǰ���Ҫ����Σ�
//�����ʹ�ù���ԱȨ�޴�vs�������иó���
// ����Ῠ�ڳ�ʼ�����޷��������ߵ��ƶ���
//��Ҳ��������Ϊ���Ŀ��������Լ���ȥ��...
//�������ߣ�����~�t(���أ���)
//���⣬��Ҫ���ٰ�������������Լ�ҧ�Լ���
//ps:�����ڲ�ͬ����֮�����ʾһ������δ����ntdll.pdb ���� �޿���Դ��
//ͦͷʹ�ģ���ʱ���У���ʱ��û�У����Ұٶȳ����Ľ���취Ҳ��ȫ��������
//�������bug��Ӱ����Ϸ�Ĺ��̣����������������ԣ�
//����֮�󵯳��������ùܣ�ֱ�ӵ���������оͺ�����
//�G�ٺٺٺ�~

#include<stdio.h>						//Ҫ��printf��QAQ  �����ۣ���ô�����˲������ͷ�ļ����أ�������
#include<graphics.h>					//�����ͳͳ����װeasyx��������
#include<mmsystem.h>					//����bgm�õ�ͷ�ļ�
#include<Windows.h>						//�����õ��ˣ�����û�õ������ˣ�������
#include<time.h>						//ҪŪ������������
#include<stdlib.h>						//������
#include<conio.h>						//�����󱿵���

#pragma comment(lib,"Winmm.lib")		//winmm���ӿ⣬�������bgm��QAQ

//#define _CRT_SECURE_NO_WARNINGS		//����λ��֮ǰ����Сbug��ʱ���հٶȵķ����ĵ�
//#undef UNICODE						//ʵ�����ְٶȵ��˸��򵥵İ취�����Ծ�ע�͵���
//#undef _UNICODE						//Ϊ�˼�����������⣬��������������QAQ

typedef struct pointxy{					//������Ȼ����Ҫ���������������QAQ
	int x;								//���������߻��ǺôεĶ���Ҫ�������š�
	int y;								//��ͼ�������ǻ�ȡһ����Ȼ������������չȻ�������ɫQAQ
}MYPOINT;								//�������ԣ������������Ҫ��

struct Snake{							//���߿ɰ���������
	int num;							//͵͵��һ���Լ���ߵ����ߺÿɰ��ģ�
	MYPOINT xy[100];					//��̫������岻�ã���������ֻ����100�ڡ�
	char postion;						//�����з������߷��ĳ壡
}snake;

struct Food{							//�ôε�ww
	MYPOINT fdxy;						//��ô��ֻ�������������꣬���ǺôεľͲ����������ˣ�
	int eatgrade;						//�÷ֽ������ٵ�һ�֣��ߺ���
	int flag;							//��ʱ�򣬵���Ҳ��Ҫ˼��ʳ�ﻹ�ڲ��ڳ���֮�ڡ�
}food;

HWND hwnd = NULL;						//Ū�������ȡ�

enum movPosition
{
	right = 77,							//ö����һ��QAQ
	left = 75,							//��Ҫ��ϲ��awsd������Ҳ�����Լ��޸�����ļ���ֵ��
	down = 80,
	up = 72,
	w = 33
};

void initSnake();						//��ʼ��һ�����ߡ�
void drawSnake();						//���߲�����~
void moveSnake();						//���ߵ�����ø�������
void keyDown();							//��һ�������ڰ�ʲô����QAQ
void initFood();						//��ô��ֻ�������߳�ʼ��ô��
void drawFood();						//�ôε�ҲҪ��������
void eatFood(int count);				//�ԳԳԳԳԳԳԳԳԣ����������Ҫ���ѶȻ�ȡ�÷ֱ�����
int snakeDie();							//�����أ������㣡����������www
void showGrade();						//�ߺߣ�ֻ����һ���˿��~
void pauseMoment();						//ͣͣͣ��û����ͣ����Ϸ���Ǻ���Ϸ��
void BGM();								//���б���ͼƬ�ˣ�������������ĺ���...

int main(void)
{
	printf("�����ϣ�����������д��̰������Ϸ�����¼�ͷ�����������ߵ��ƶ�����QAQ\n");
	printf("������Ϸһ���������Ѷȣ��Ѷ�Խ�ߣ��ߵ��ƶ��ٶ�Խ�죬���ҵ÷�Ч�ʻ�Խ�ߡ�\n");
	printf("��Ȼ��ʵ���ϻ����������Ի�ȽϺõ�����~\n");
	printf("�����߻����ŵ�ʱ����԰��¿ո������ʱ��ͣ��Ϸ����ô������������ƺ����Ի��ɣ�\n");
	printf("ps����Ϸ��һ��Сbug���м��͵ĸ���ˢ����ʳ�����ֻ���ؿ��������أ�\n");
	printf("ps2:����һ��bug��������ٰ���������Ҳ�ᵼ������ֱ����ɰ������\n");
	printf("���ڣ���������Ҫѡ���ģʽ������1��Ϊ��;ģʽ������2��Ϊר��ģʽ������3���Ǵ���ģʽ~\n");
	int number = 0;												//������һ�ֲ���ʼ���ͻ����Ĳ���
	for (;;)
	{
		scanf_s("%d", &number);									//Ϊʲô��������scanf������������
		if (number == 1 || number == 2 || number == 3)			//����������������~
		{
			break;
		}
		else
		{
			printf("����������ȷ���Ѷȷּ���������\n");			//ħ��һ�ɣ�С�ӣ�
		}
	}
	int grade = 0, count = 0;									//����sleep�����Ĳ����͵÷ֱ����Ķ���QAQ
	if( number == 1 )
	{
		grade = 50;
		count = 1;
	}
	else if ( number == 2 )
	{
		grade = 35;
		count = 2;
	}
	else if( number == 3 )
	{
		grade = 15;
		count = 3;
	}

	IMAGE background;
	loadimage(&background, "./Image.jpg", 680, 480, 1);
																//�������ص�ͼƬ�ȣ�
																//������Ǹ�����ݴ�����ˣ����������ע�͵�
																//��Ϊ���ָ��Ŀ¼�����ڣ�������������޸�QAQ
																//ֱ��ע�͵��Ļ�setbkcolor����Ч�������ǰ�ɫ����
	putimage(0, 0, &background);

	srand((unsigned int)time(NULL));							//���������ʲô�ġ�
	hwnd = initgraph(680, 480);	
																//���������ʾ������Ҫ114514��ֻҪ1919��
	setbkcolor(WHITE);											//����ɫ�ǰ�ɫ����ȻҲ������ͼƬ
	BGM();
	initSnake();												//��������Ҫ��ʼ������
	while (1)
	{
		cleardevice();											//����һ�����߻�Ӱ�ݵġ�
		putimage(0, 0, &background);
		if( food.flag == 0 )									//�ж�һ�£�ûʳ���Ͷιһ����
		{
			initFood();
		}
		BeginBatchDraw();										//˫�����װ��������Ҳ���õ�����Ļ������ȥ����
		drawFood();												//����ʳ�ﻹ�������ߣ�
		drawSnake();											//������������ʳ�����ţ�û��ϵ�����߿ɰ���win��
		if (snakeDie())											//����Ҫ�����˾Ͳ�������
		{
			break;
		}
		eatFood(count);											//�ԳԳ�
		showGrade();
		EndBatchDraw();
		moveSnake();
		while (_kbhit())										//������������ʱ׼���ж���
		{
			pauseMoment();
			keyDown();
		}
		Sleep(grade);											//˯��û�����˵���㣬��ô�����������ɣ�
	}
	mciSendString(_T("close bkmusic"), NULL, 0, NULL);			//���ֽ�����
	int a = getchar();											//getchar��Ȼ��Ҫ����ֵ��vs�㻵��������
	closegraph();												//�ˣ��Ͷ��������ˣ��ͱ��棡
	printf("game over !��ӭ�´�ʹ�ã�QAQ\n");	
	system("pause");
	return 0;													//������~
}

void initSnake(void)
{
	snake.xy[2].x = 0;											//�ȳ�ʼ��һ���̶�������λ�á�
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;												//Ĭ���ʼ��3�ڣ���Ȼ��Ҳ���ԸĶ�㣬���ǻ�װ������Ļ��
	snake.postion = right;										//Ĭ�Ϸ��������ҡ�

	food.flag = 0;												//���µ����~��û��ʳ��~
	food.eatgrade = 0;											//��Ȼ~Ҳû�з���~
}

void drawSnake(void)
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);									//�������߷��鵥Ԫ�߿���ɫ���Ǻ�ɫ��
		setfillcolor(RGB(rand()%255,rand()%255,rand()%255));	//��ɫ���ߣ����죡
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
																//���ߵķ����������Σ�+10���ܴ�һ�������󵽳������ˡ�
	}
}

void moveSnake(void)
{
																//���˵�һ�ڣ�����ÿһ�ڶ���ǰһ�ڵ����ꡣ
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
																//��һ����Ҫ��������
	switch (snake.postion)										//ʵ������ʵ�Ǹ���������õĵ����������ߵķ����
	{															//������ɣ������ǣһ����ȫ���ߺߣ�
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:
		break;
	}
}

void keyDown(void)
{
	char userKey = 0;											//��������һ�ֲ���ʼ���ͻ������Ĳ���
	userKey = _getch();											//��ȡ���̰��µİ�ť��ʵ���Ͼ��ǻ���㰴�¼��̵��������ҡ�
	switch (userKey)
	{															//������Ŷ��ֻ��һ�飡
	case right:													//�ı䷽��Ӧ����ѭ���������飺����͵�ǰ����һ�£���Ӧ�����κθĶ�
		if (snake.postion != left)								//���߲���ֱ��ת���෴�ķ��������ڻ�ȡ�˼��̵ķ���֮��Ҫ���ж��ǲ����෴����
			snake.postion = right;								//�Ͼ�������������ߣ��ٰ���Ҳû��ʲô����...>v<
		break;
	case left:
		if (snake.postion != right)
			snake.postion = left;
		break;
	case down:
		if (snake.postion != up)
			snake.postion = down;
		break;
	case up:
		if (snake.postion != down)
			snake.postion = up;
		break;
	default:
		break;
	}
	
}

void initFood(void)
{
	food.fdxy.x = rand() % 65 * 10;								//Сֻ���ɣ�ֱ����������п����ܶ�̫�����Կ���������ȡ��С�������ȡ������
	food.fdxy.y = rand() % 48 * 10;								//ͬ���
	food.flag = 1;												//��ʼ��ʳ��֮��ʵ���Ͼ��Ѿ�����ʳ���ˣ�Ѧ���̵�ʳ��QAQ��
	for (int i = 0; i > snake.num; i++)
	{
		if(food.fdxy.x == snake.xy[i].x && food.fdxy.x == snake.xy[i].x)
		{
			food.fdxy.x = rand() % 65 * 10;						//bug����Դ�����ø��ˣ����ɵ�ʳ����������ߵ�����غϾͻ���������һ�Ρ�
			food.fdxy.y = rand() % 48 * 10;						//����...������غ�����QAQ����μ�����ÿ��٣�������㣡
		}
	}
}

void drawFood(void)
{
	setlinecolor(BLACK);										//ʳ��߿����ɫҲ�Ǻ�ɫ��QAQ
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));//ʳ��Ͳ����ǲ�ɫ���������㣡
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
																//ʳ�����ʵҲ��ȷ�����Ͻǵĵ�֮��+10չ���ġ�
}

void eatFood(int count)											//�����count���������÷ֱ�������ġ�
{
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y)
	{															//����ʵ���ж������ͷ�������ʳ��������غ��˾��൱�ڳԵ���ʳ�
		snake.num++;											//�����غ�֮�����߻Ḳ�ǵ�ʳ�ﲻ��Ҫ������գ�����ֱ�������ߵĳ��ȱ߳��Ϳ����ˡ�
		food.eatgrade += 10*count;								//�÷֣�
		food.flag = 0;											//�����ˣ�������Ͷ����QAQ
	}
}

int snakeDie()
{
	if (snake.xy[0].x > 680 || snake.xy[0].x < 0 || snake.xy[0].y>480 || snake.xy[0].y < 0)
	{															//������ߵ������ͬ�ڱ߽����꣬��˵�������˱߽磬ϵ���������ء�
		outtextxy(200,200,"baka��ײǽ��Ŷ��");					//�Ǻ������Ƶ�һ�仰��
		MessageBox(hwnd, "����������ˣ�", "ײǽ����", MB_OK);	//Ū����һ���´�����˵������������ԣ�
		return 1;												//����1��ֵ����Ϊif�ж�true����Ҫ�������ֵ�QAQ
	}
	for (int i = 1; i < snake.num; i++)							//�����ÿһ����Ҫ���һ���أ�
	{															//������ߵ������ͬ���κ�һ����ڵ����꣬��˵��ҧ�����Լ���
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(200, 200, "baka��ҧ���Լ�����");			//�Ծ��Ǻ������Ƶ����ԣ�
			MessageBox(hwnd, "����������ˣ�", "ҧ�Լ�����", MB_OK);
			return 1;
		}
	}
	return 0;													//��������ó��ں�����bug�����������������ˣ���
}

void showGrade()												//"�������"
{
	char grade[100] = "";										//�����ַ������ӷ���һЩ��...
	sprintf_s(grade, "%d", food.eatgrade);						//������sp��ӡ������������vs��Ҫ�Ӹ�  _s  
	setbkmode(TRANSPARENT);										//�����ı���ʽ����ô�о���css�е���QAQ
	settextcolor(LIGHTBLUE);
	outtextxy(580,20,"������");									//+20��ʵ��͵�������˾���λ��233333
	outtextxy(580 + 50, 20, grade);
}

void pauseMoment()												//������ͣ����Ϸ���Ǻ���Ϸ��
{
	if ((char)_getch() == ' ' )									//������Զ����˿ո�ͻ�ͣ������
	{
		MessageBox(hwnd, "��������ͣ��~", "��ͣ~", MB_OK);		//���ҷų���һ��������ʾ�Ѿ���ͣ�Ĵ��ڡ�
		while ((char)_getch() != ' ' );							//ֱ����һ���ո���롣
	}
}


void BGM()
{	
	mciSendString("open ./bgm.mp3 alias bgm", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
}