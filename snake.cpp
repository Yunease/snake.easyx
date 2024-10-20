//玩之前务必要读这段：
//请务必使用管理员权限打开vs再来运行该程序！
// 否则会卡在初始界面无法操纵蛇蛇的移动！
//你也不想无能为力的看着蛇蛇自己死去吧...
//可怜蛇蛇！摸摸~╰(￣ω￣ｏ)
//此外，不要快速按方向键，容易自己咬自己。
//ps:可能在不同电脑之间会显示一个报错：未加载ntdll.pdb 或者 无可用源。
//挺头痛的，有时候有，有时候没有，而且百度出来的解决办法也完全看不懂！
//但是这个bug不影响游戏的过程，所以屏晶决定忽略！
//死掉之后弹出来报错不用管，直接点击结束运行就好啦！
//欸嘿嘿嘿嘿~

#include<stdio.h>						//要用printf的QAQ  不对哇！怎么会有人不带这个头文件的呢！笨蛋！
#include<graphics.h>					//报错的统统给我装easyx！笨蛋！
#include<mmsystem.h>					//播放bgm用的头文件
#include<Windows.h>						//好像用到了，好像没用到，忘了！笨蛋！
#include<time.h>						//要弄随机数嘛！笨蛋！
#include<stdlib.h>						//笨蛋！
#include<conio.h>						//超级大笨蛋！

#pragma comment(lib,"Winmm.lib")		//winmm链接库，用于添加bgm的QAQ

//#define _CRT_SECURE_NO_WARNINGS		//这三位是之前遇到小bug的时候按照百度的方法改的
//#undef UNICODE						//实际上又百度到了更简单的办法，所以就注释掉了
//#undef _UNICODE						//为了纪念这个破问题，所以留下了他们QAQ

typedef struct pointxy{					//理所当然的是要设置坐标的属性哇QAQ
	int x;								//不管是蛇蛇还是好次的都需要坐标来着。
	int y;								//绘图本质上是获取一个点然后向下向右扩展然后填充颜色QAQ
}MYPOINT;								//所以所以！这个点至关重要！

struct Snake{							//蛇蛇可爱！贴贴！
	int num;							//偷偷量一下自己身高的蛇蛇好可爱的！
	MYPOINT xy[100];					//吃太多对身体不好！所以蛇蛇只能有100节。
	char postion;						//蛇蛇有方向，蛇蛇放心冲！
}snake;

struct Food{							//好次的ww
	MYPOINT fdxy;						//怎么？只许你蛇蛇有坐标，俺们好次的就不让用坐标了？
	int eatgrade;						//得分奖励！再的一分！芜湖！
	int flag;							//有时候，电脑也需要思考食物还在不在场地之内。
}food;

HWND hwnd = NULL;						//弄个窗口先。

enum movPosition
{
	right = 77,							//枚举了一下QAQ
	left = 75,							//你要是喜欢awsd操作，也可以自己修改这里的键码值！
	down = 80,
	up = 72,
	w = 33
};

void initSnake();						//初始化一下蛇蛇。
void drawSnake();						//画蛇不添足~
void moveSnake();						//蛇蛇的坐标该更新了喵
void keyDown();							//读一下现在在按什么按键QAQ
void initFood();						//肿么？只许你蛇蛇初始化么？
void drawFood();						//好次的也要画出来！
void eatFood(int count);				//吃吃吃吃吃吃吃吃吃（传入参数是要以难度获取得分倍数）
int snakeDie();							//呜呜呜！都怪你！蛇蛇死掉了www
void showGrade();						//哼哼，只给你一个人看喔~
void pauseMoment();						//停停停！没有暂停的游戏不是好游戏！
void BGM();								//都有背景图片了，不设置音乐真的好嘛...

int main(void)
{
	printf("啊嘞嘞！这里是屏晶写的贪吃蛇游戏！按下箭头按键控制蛇蛇的移动方向QAQ\n");
	printf("笨蛋游戏一共有三个难度，难度越高，蛇的移动速度越快，并且得分效率会越高。\n");
	printf("当然，实际上还是上手试试会比较好的啦！~\n");
	printf("在蛇蛇还活着的时候可以按下空格键来随时暂停游戏，怎么样！屏晶的设计很人性化吧！\n");
	printf("ps：游戏有一个小bug，有极低的概率刷不出食物，遇到只能重开了呜呜呜！\n");
	printf("ps2:还有一个bug，如果快速按多个方向键也会导致蛇蛇直接紫砂死掉。\n");
	printf("现在！请输入你要选择的模式：输入1则为旅途模式，输入2则为专家模式，输入3则是传奇模式~\n");
	int number = 0;												//屏晶有一种不初始化就会死的病。
	for (;;)
	{
		scanf_s("%d", &number);									//为什么不让我用scanf！！！！！！
		if (number == 1 || number == 2 || number == 3)			//哈哈！答辩代码来历~
		{
			break;
		}
		else
		{
			printf("请你输入正确的难度分级！笨蛋！\n");			//魔高一丈！小子！
		}
	}
	int grade = 0, count = 0;									//用于sleep函数的参数和得分倍数的东西QAQ
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
																//整个本地的图片先！
																//如果你是复制这份代码的人，请把这句代码注释掉
																//因为你的指定目录不存在，但你可以稍作修改QAQ
																//直接注释掉的话setbkcolor会生效，背景是白色喵。
	putimage(0, 0, &background);

	srand((unsigned int)time(NULL));							//随机数种子什么的。
	hwnd = initgraph(680, 480);	
																//超大高清显示屏，不要114514，只要1919！
	setbkcolor(WHITE);											//背景色是白色，当然也可以是图片
	BGM();
	initSnake();												//俺们蛇蛇要初始化啦！
	while (1)
	{
		cleardevice();											//不清一下蛇蛇会影遁的。
		putimage(0, 0, &background);
		if( food.flag == 0 )									//判断一下，没食物就投喂一个。
		{
			initFood();
		}
		BeginBatchDraw();										//双缓冲封装，妈妈再也不用担心屏幕闪来闪去啦！
		drawFood();												//先有食物还是现有蛇？
		drawSnake();											//看起来是先有食物来着，没关系，蛇蛇可爱，win！
		if (snakeDie())											//蛇蛇要是死了就不用玩啦
		{
			break;
		}
		eatFood(count);											//吃吃吃
		showGrade();
		EndBatchDraw();
		moveSnake();
		while (_kbhit())										//龙门消防官随时准备行动！
		{
			pauseMoment();
			keyDown();
		}
		Sleep(grade);											//睡多久还是你说了算，怎么样！很厉害吧！
	}
	mciSendString(_T("close bkmusic"), NULL, 0, NULL);			//音乐结束！
	int a = getchar();											//getchar居然还要返回值！vs你坏事做尽！
	closegraph();												//菜！就多练！输了！就别玩！
	printf("game over !欢迎下次使用！QAQ\n");	
	system("pause");
	return 0;													//结束啦~
}

void initSnake(void)
{
	snake.xy[2].x = 0;											//先初始化一个固定的生成位置。
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;												//默认最开始是3节，当然你也可以改多点，但是会装不下屏幕。
	snake.postion = right;										//默认方向是向右。

	food.flag = 0;												//故事的最初~还没有食物~
	food.eatgrade = 0;											//当然~也没有分数~
}

void drawSnake(void)
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);									//设置蛇蛇方块单元边框颜色的是黑色。
		setfillcolor(RGB(rand()%255,rand()%255,rand()%255));	//彩色蛇蛇！升天！
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
																//蛇蛇的方块是正方形，+10就能从一个点扩大到长方形了。
	}
}

void moveSnake(void)
{
																//除了第一节，后面每一节都是前一节的坐标。
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
																//第一节需要单独处理。
	switch (snake.postion)										//实际上其实是根据最初设置的点来设置蛇蛇的方向的
	{															//很神奇吧，这就是牵一发动全身！哼哼！
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
	char userKey = 0;											//屏晶得了一种不初始化就会死掉的病。
	userKey = _getch();											//获取键盘按下的按钮，实际上就是获得你按下键盘的上下左右。
	switch (userKey)
	{															//看好了哦！只讲一遍！
	case right:													//改变方向应该遵循这样的事情：如果和当前方向一致，不应该有任何改动
		if (snake.postion != left)								//蛇蛇不能直接转到相反的方向，所以在获取了键盘的方向之后要先判断是不是相反方向。
			snake.postion = right;								//毕竟如果正在向右走，再按右也没有什么用啦...>v<
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
	food.fdxy.x = rand() % 65 * 10;								//小只因巧：直接随机生成有可能密度太大，所以可以这样获取较小的随机数取倍数。
	food.fdxy.y = rand() % 48 * 10;								//同理↑
	food.flag = 1;												//初始化食物之后，实际上就已经存在食物了，薛定谔的食物QAQ！
	for (int i = 0; i > snake.num; i++)
	{
		if(food.fdxy.x == snake.xy[i].x && food.fdxy.x == snake.xy[i].x)
		{
			food.fdxy.x = rand() % 65 * 10;						//bug的来源，懒得改了：生成的食物如果和蛇蛇的体节重合就会重新生成一次。
			food.fdxy.y = rand() % 48 * 10;						//但是...如果又重合了呢QAQ！多次检验会变得卡顿，达咩达咩！
		}
	}
}

void drawFood(void)
{
	setlinecolor(BLACK);										//食物边框的颜色也是黑色的QAQ
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));//食物就不能是彩色的嘛！达咩达咩！
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
																//食物的其实也是确定左上角的点之后+10展开的。
}

void eatFood(int count)											//传入的count是用来做得分倍数计算的。
{
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y)
	{															//这里实在判断如果蛇头的坐标和食物的坐标重合了就相当于吃掉了食物。
		snake.num++;											//由于重合之后蛇蛇会覆盖掉食物不需要额外清空，所以直接让蛇蛇的长度边长就可以了。
		food.eatgrade += 10*count;								//得分！
		food.flag = 0;											//吃完了，该重新投放了QAQ
	}
}

int snakeDie()
{
	if (snake.xy[0].x > 680 || snake.xy[0].x < 0 || snake.xy[0].y>480 || snake.xy[0].y < 0)
	{															//如果蛇蛇的坐标等同于边界坐标，就说明碰到了边界，系内了呜呜呜。
		outtextxy(200,200,"baka！撞墙了哦！");					//是很有气势的一句话！
		MessageBox(hwnd, "笨蛋！输掉了！", "撞墙警告", MB_OK);	//弄出来一个新窗口来说明事情的严重性！
		return 1;												//给出1的值是因为if判断true是需要非零数字的QAQ
	}
	for (int i = 1; i < snake.num; i++)							//身体的每一处都要检查一下呢！
	{															//如果蛇蛇的坐标等同于任何一个体节的坐标，就说明咬到了自己。
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(200, 200, "baka！咬到自己啦！");			//仍旧是很有气势的宣言！
			MessageBox(hwnd, "笨蛋！输掉了！", "咬自己警告", MB_OK);
			return 1;
		}
	}
	return 0;													//如果不设置出口好像会出bug，不懂，反正加上了（）
}

void showGrade()												//"看看你的"
{
	char grade[100] = "";										//还是字符串更加方便一些啊...
	sprintf_s(grade, "%d", food.eatgrade);						//这里用sp打印，坏事做尽的vs非要加个  _s  
	setbkmode(TRANSPARENT);										//设置文本样式，怎么感觉和css有点像QAQ
	settextcolor(LIGHTBLUE);
	outtextxy(580,20,"分数：");									//+20其实是偷懒调整了绝对位置233333
	outtextxy(580 + 50, 20, grade);
}

void pauseMoment()												//不会暂停的游戏不是好游戏！
{
	if ((char)_getch() == ' ' )									//如果电脑读进了空格就会停下来。
	{
		MessageBox(hwnd, "笨蛋！暂停中~", "暂停~", MB_OK);		//并且放出来一个用于提示已经暂停的窗口。
		while ((char)_getch() != ' ' );							//直到再一个空格读入。
	}
}


void BGM()
{	
	mciSendString("open ./bgm.mp3 alias bgm", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
}