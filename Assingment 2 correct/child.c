#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

int	 shouldRun	= 1;
int	 haveFoundPin	= 0;

void	 clearShouldRun	(int	sigNum
	 		)
{
  shouldRun	= 0;
}


int	main	(int argc, char* argv[])
{

  //  I.  Application validity check:
  if  (argc < 2)
  {
    fprintf(stderr,"Child: \"My mother did not give me a name! :(\"\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Eat them look for the pin!
  //  II.A.  :
  const char*	nameCPtr	= argv[1];

  //  II.B.  Set up signal handler to listen to when should stop:
  struct sigaction	act;

  memset(&act,'\0',sizeof(struct sigaction));
  act.sa_handler = clearShouldRun;
  sigaction(SIGTERM,&act,NULL);

  //  II.B.  Look for the pin:
  int  numAttempts = 0;

  srand(getpid());

  while  ( shouldRun && !haveFoundPin )
  {
    sleep(1);

    numAttempts++;

    switch  (rand() % 4)
    {
    case 0 :
      printf("%s %d: \"It's just grass, not pin yet.\"\n",
	     nameCPtr,getpid()
	    );
      break;

    case 1 :
      printf("%s %d: \"It smells nice, but no pin yet.\"\n",
	     nameCPtr,getpid()
	    );
      break;

    case 2 :
      printf("%s %d: \"Mom, have you thought of using a magnet?\"\n",
	     nameCPtr,getpid()
	    );
      break;

    case 3 :
      printf("%s %d: \"Ouch!  I got pricked by a "
	     ". . . Hey, look at what I found!\"\n",
	     nameCPtr,getpid()
	    );
      haveFoundPin = 1;
      kill(getppid(),SIGUSR1);
      break;
    }

  }

  while  (shouldRun)
    sleep(1);

  if  (haveFoundPin)
  {
    printf("%s %d: \"Yay!  I win!  $20 is all mine!\"\n",nameCPtr,getpid());
  }
  else
  {
    if  (numAttempts <= 2)
      printf
	("%s %d: \"That wasn't fair!  I was just getting started!\"\n",
	 nameCPtr,getpid()
	);
    else
    if  (numAttempts <= 4)
      printf("%s %d: \"Man!  Now my hands are itchy.\"\n",nameCPtr,getpid());
    else
      printf
	("%s %d: \"Achoo!  I'm itchy and my allergies are acting up.\"\n",
	 nameCPtr,getpid()
	);
  }

  return(EXIT_SUCCESS);
}
