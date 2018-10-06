#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

int count = 0;
void sighandler(int signo)
{
	time_t t;

	time(&t);
	printf("signal %d occurred %d time at %s\n",signo, ++count, ctime(&t));
}
	
int main(void)
{
	struct itimerval it;
	struct sigaction act, oact;

	// Initialize the signal handler for SIGPROF, SIGVTALRM, SIGALRM
	act.sa_handler = sighandler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGPROF, &act, &oact);	
	//sigaction(SIGALRM, &act, &oact);	
	//sigaction(SIGVTALRM, &act, &oact);	
	
	// Start itimer
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 500000;
	it.it_value.tv_sec = 3;
	it.it_value.tv_usec = 100000;
	setitimer(ITIMER_PROF, &it, NULL);
	//setitimer(ITIMER_REAL, &it, NULL);
	//setitimer(ITIMER_VIRTUAL, &it, NULL);
	
	for ( ; ; ) ;
}
