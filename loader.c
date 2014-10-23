/*树莓派开机通过GPIO按钮选择执行程序，Version1.0
作者：FishX @ bbs.ickey.cn @weibo.com 鱼叉wb
欢迎转载，转载请注明出处*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <curses.h>
#include <menu.h>
#define BTN_UP 4
#define BTN_DOWN 3
#define BTN_OK 2
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*菜单项及其描述*/
char *choices[] = {"1.Network Toolbox","2.Camera","3.MPC","4.HD Music Player","5.Back to console","6.Shutdown"};
char *choice_descp[] = {"","","","","",""};

/*初始化GPIO按钮*/
void gpiosetup (void){
	if (geteuid() != 0){
		fprintf(stderr, "\nAlert: Need to be root to run (sudo?)\n") ;
		exit (0);
	}
	if (wiringPiSetup() == -1)
		exit (1) ;
	fflush (stdout) ;
	//BTN_UP 4 AdaPanel 23,BTN_DOWN 3 AdaPanel 22,BTN_ENTER AdaPanel 21 or 27
	//把GPIO设置为上拉模式
	pullUpDnControl (BTN_UP,PUD_UP);
	pullUpDnControl (BTN_DOWN,PUD_UP);
	pullUpDnControl (BTN_OK,PUD_UP);
}

/*主程序入口*/
void main(){
	//初始化GPIO按钮
	gpiosetup();
	//构建菜单
	ITEM **my_items;
	int c;
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
		my_items[i] = new_item(choices[i],choice_descp[i]);
	my_items[n_choices] = (ITEM *)NULL;
	my_menu = new_menu((ITEM **)my_items);
	post_menu(my_menu);
	refresh();
	//开始检测按键
	int ret = 0;
	while(ret==0){
		refresh();
		if (digitalRead (BTN_UP) == LOW){
			menu_driver(my_menu, REQ_UP_ITEM);
			delay(200);
			continue;
		}
		if (digitalRead (BTN_DOWN) == LOW){
			menu_driver(my_menu, REQ_DOWN_ITEM);
			delay(200);
			continue;
		}
		if (digitalRead (BTN_OK) == LOW){
			switch(item_index(current_item(my_menu)))
				{	
					case 0://执行第一个程序
						def_prog_mode();
						endwin();
						system ("cd //home//pi//xpi// && sudo python tools.py");
						reset_prog_mode();
						refresh();
						break;
					case 1://执行第二个程序
						def_prog_mode();
						endwin();
						system ("cd //home//pi//ada// && sudo python cam.py");
						reset_prog_mode();
						refresh();
						break;
					case 2://MPC
						def_prog_mode();
						endwin();
						system ("cd //home//pi//impc// && sudo python radioplayer.py");
						reset_prog_mode();
						refresh();
						break;
					case 3://HD Music Player
						def_prog_mode();
						endwin();
						system ("cd //home//pi//pplayer && sudo python player.py");
						reset_prog_mode();
						refresh();
						break;
					case 4://back to console
						ret = 1;
						break;
					case 5://关机
						free_item(my_items[0]);
						free_item(my_items[1]);
						free_menu(my_menu);
						endwin();
						refresh();
						system ("sudo shutdown -h now");
						break;
				}
			delay(200);
			continue;
		}
		mvprintw(LINES-1,0,"[%s]                 ", item_name(current_item(my_menu)));
	}
	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(my_menu);
	endwin();
	fflush (stdout) ;
}
