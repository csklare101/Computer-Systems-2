#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

const char*	FEMALE_NAME_ARRAY[]
				= {"Anna",
				   "Betty",
				   "Catherine",
				   "Dorothy"
				  };

const char*	MALE_NAME_ARRAY[]
				= {"Earl",
				   "Fred",
				   "Gerald",
				   "Hal"
				  };

int		haveFoundPin	= 0;

const int	NUM_CHILDREN	= 2;

void	 contestOver	(int	sigNum
	 		)
{
  printf("Mother: \"Thank you for finding my pin, here is $20.\"\n");
  haveFoundPin	  = 1;
}


int	main	(int	argc,
		 char*	argv[]
		)
{
  //  I.  Application validity check:

  //  II.  Ask children to look for pin:
  //  II.A.  :
  srand(getpid());

  //  II.B.  Install handler to listen for winner:
  struct sigaction	act;

  memset(&act,'\0',sizeof(struct sigaction));
  act.sa_handler = contestOver;
  sigaction(SIGUSR1,&act,NULL);


  //  II.B.  Start contest:
  printf("Mother: \"I will give $20 to whomever finds my "
	 "decorative pin in the pile of grass.  Go!\"\n");

  int i;
  pid_t	childIdArray[NUM_CHILDREN];

  for  (i = 0;  i < NUM_CHILDREN;  i++)
  {
    childIdArray[i] = fork();

    if  (childIdArray[i] < 0)
    {
      fprintf(stderr,"Your system is too busy to look for the pin!\n");
      exit(EXIT_FAILURE);
    }
    else
    if  (childIdArray[i] == 0)
    {
      const char**	nameArray;
      const char*	nameCPtr;

      nameArray	= (i == 0) ? FEMALE_NAME_ARRAY : MALE_NAME_ARRAY;
      nameCPtr	= nameArray[ rand() %
			     (sizeof(FEMALE_NAME_ARRAY) / sizeof(const char*))
			   ];

      execl("./child","child",nameCPtr,NULL);
      fprintf(stderr,"Hey!?!  Where are my children?!\n");
      exit(EXIT_FAILURE);
    }

  }

  while  (!haveFoundPin)
    sleep(1);

  for  (i = 0;  i < NUM_CHILDREN;  i++)
  {
    kill(childIdArray[i],SIGTERM);
    wait(NULL);
  }

  return(EXIT_SUCCESS);
}
