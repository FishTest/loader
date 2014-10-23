/*
 * run.c:
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
//WiringPI GPIO1=Rpi Pin12 ada  btn1 4(23)
#define	BUTTON 4

void setup (void)
{
  if (geteuid () != 0)
  {
    fprintf (stderr, "\nAlert: Need to be root to run (sudo?)\n") ;
    exit (0) ;
  }
  if (wiringPiSetup () == -1)
    exit (1) ;
  printf ("\n--Setup GPIO Mode... ") ; 
  fflush (stdout) ;
  pullUpDnControl (BUTTON,PUD_UP);
  printf ("--OK\n") ;
}
void waitButton (void)
{
  //printf ("--Waiting for button ... \n") ; 
  fflush (stdout) ;
  while (digitalRead (BUTTON) == LOW){
  printf("1");
	delay (200) ;
	
	}
  //printf ("\n--Starting X-Pi\n") ;
  //printf ("--Run ls /home/pi -l \n") ;
  //system ("cd //home//pi//xpi// && sudo python tools.py");
  //system ("sudo python //home//pi//xpi//tools.py");
}
int main (void)
{
  setup () ;
  while (1)
    waitButton ();
  return 1;
}
