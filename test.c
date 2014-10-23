/*树莓派开机通过GPIO按钮选择执行程序，Version0.7
作者：FishX @ bbs.ickey.cn
欢迎转载，转载请注明出处*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <curses.h>
#include <menu.h>
#define BTN_UP 4
#define BTN_DOWN 3
#define BTN_ENTER 2
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*菜单项及其描述*/
char *choices[] = {"Network Toolbox","Camera","Shutdown","Back to console"};
char *choice_descp[] = {"","","",""};

/*初始化GPIO按钮*/
void gpiosetup (){
	if (geteuid() != 0){
		fprintf(stderr, "\nAlert: Need to be root to run (sudo?)\n") ;
		exit (0);
	}
	if (wiringPiSetup() == -1)
		exit (1) ;
	printf ("\n--Setup GPIO Buttons... ") ; 
	fflush (stdout) ;
	//BTN_UP 4 AdaPanel 23,BTN_DOWN 3 AdaPanel 22,BTN_ENTER AdaPanel 21 or 27
	//把GPIO设置为上拉模式
	pullUpDnControl (BTN_UP,PUD_UP);
	pullUpDnControl (BTN_DOWN,PUD_UP);
	pullUpDnControl (BTN_ENTER,PUD_UP);
	printf ("--OK\n");
}

void waitbutton(){




}

/*主程序入口*/
void main(){
	//初始化GPIO按钮
	//gpiosetup();
	printf ("--OK\n");
	//初始化屏幕及菜单项
	//GPIO控制选择部分
	while(1){
		waitbutton();
		fflush (stdout) ;
		if (digitalRead (BTN_UP) == HIGH){
			//delay (100);
			printf("up\n");
		}
			// }

		// if (digitalRead (BTN_DOWN) == HIGH){delay (100) ;printf("down");
			// }

		// if (digitalRead (BTN_ENTER) == HIGH){delay (100) ;printf("enter");
		// }
	}
	// return 1;

}
