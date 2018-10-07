#include <malloc.h>
#include <ucontext.h>
#include <stdio.h>
#include <sys/time.h>
#define MAXTHREADS	20
#define THREAD_STACKSIZE	32767

unsigned int whichqs = 0;
thread_t ** qs, ** tqs;

typedef struct thread_t {
	int thr_id;
	int thr_usrpri;
	int thr_cpupri;
	int thr_pri;
	int thr_nice;
	
	int thr_totalcpu;
	ucontext_t thr_context;
	void * thr_stack;
	int thr_stacksize;
	struct thread_t *thr_next;
	struct thread_t *thr_prev;
} thread_t;

typedef struct mutex_t {
	int val;
	thread_t *owner;
	thread_t *wait_q;
} mutex_t;

typedef struct condition_t {
	thread_t *wait_q;
} condition_t;

thread_t thread_table[MAXTHREADS];

int ticks = 0;
int timeq = 0;
thread_t * ready_q = NULL, * current_thread = NULL;
void timertick_handler(int alrm);
void schedule(void);

thread_t * thread_create(void (* thr_func)(void *), void *arg)
{
	int i;
	thread_t *thr;
	static int thrno = 1;
	struct itimerval t1;

	// Allocate thread structure.
	for (i=0; i<MAXTHREADS; i++)
		if (thread_table[i].thr_id == 0) // Unused
			break;

	if (i >= MAXTHREADS) return NULL;

	thr = &thread_table[i];	
         // Get the current execution context
         getcontext(&(thr->thr_context));

         // Modify the context to a new stack
         thr->thr_context.uc_link = 0;
         thr->thr_stack = thr->thr_context.uc_stack.ss_sp = malloc( THREAD_STACKSIZE );
         thr->thr_context.uc_stack.ss_size = THREAD_STACKSIZE;
         thr->thr_context.uc_stack.ss_flags = 0;        
         if ( thr->thr_context.uc_stack.ss_sp == 0 )
         {
                 perror( "malloc: Could not allocate stack" );
                 exit( 1 );
         }

         // Create the new context
         printf( "Creating child fiber\n" );
         makecontext( &thr->thr_context, thr_func, 1 , arg);

	// Initialize other fields of the thread structure
	thr->thr_id = thrno++;
	thr->thr_usrpri = 20;
	thr->thr_cpupri = 0;
	thr->thr_totalcpu = 0;
	thr->thr_stacksize = THREAD_STACKSIZE;
	// TO BE DONE :: Block the signals during adding to the ready_q;
	if (ready_q == NULL)
	{

		// Create the main thread also
		for (i=0; i<MAXTHREADS; i++)
			if (thread_table[i].thr_id == 0)
			{
				current_thread = &thread_table[i];
				current_thread->thr_id = thrno++;
				current_thread->thr_usrpri = 20;
				current_thread->thr_cpupri = 0;
				current_thread->thr_totalcpu = 0;
				current_thread->thr_next = NULL;
				current_thread->thr_prev = NULL;
				ready_q = current_thread;
				
				break;
			}
		// First thread so activate the timer tick
		signal(SIGPROF, timertick_handler);
		t1.it_interval.tv_usec = 50000;
		t1.it_interval.tv_sec = 0;
		t1.it_value.tv_usec = 0;
		t1.it_value.tv_sec = 2;
		setitimer(ITIMER_PROF, &t1, NULL);
	}

		
	// Add this to ready q
	thr->thr_next = ready_q;
	thr->thr_prev = NULL;
	ready_q->thr_prev = thr;
	ready_q = thr;
	return thr;
}

void thread_exit(void)
{
	// Remove this thread from the ready_q
	// TO BE DONE :: Block the signals during adding to the ready_q;

	if (current_thread->thr_next != NULL)
		(current_thread->thr_next)->thr_prev = current_thread->thr_prev;
	if (current_thread->thr_prev != NULL)
		(current_thread->thr_prev)->thr_next = current_thread->thr_next;
	
	if (current_thread == ready_q)
		ready_q = current_thread->thr_next;
	free(current_thread->thr_stack);
	current_thread->thr_id = 0; // Free the slot

	current_thread = NULL;
	schedule();
	// DO NOT ENABLE SIGNALS HERE
}

void thread_yield(void)
{
	schedule();
}

void enqueue_thread(thread_t *t, thread_t *qs[])
{
	int id;
	thread_t *t1, *t2;

	// Find the queue id
	id = t->thr_pri / 4;
	
	// Inser at proper position within the selected queue based priority
	// and modify whichqs
	if (qs[id] == NULL)
	{
		qs[id] = t;
		t->thr_prev = t->thr_next = NULL;
		whichqs = whichqs | (1 << id);
	}
	else
	{
		t1 = qs[id];
		// Insert at the beginning?
		if (t1->thr_pri > t->thr_pri)
		{
			t->thr_next = t1;
			t->thr_prev = NULL;
			t1->thr_prev = t;
			qs[id] = t;
		}
		else
		{
			while (t1->thr_next != NULL && (t1->thr_next)->thr_pri <= t->thr_pri)
				t1 = t1->thr_next;
			t->thr_next = t1->thr_next;
			t->thr_prev = t1;
			t1->thr_next = t;
			if (t->thr_next != NULL)
				(t->thr_next)->thr_prev = t;
		}	
	}
}

void dequeue_thread(int qid, thread_t *t, thread_t *qs[])
{
	if (t->prev != NULL) (t->thr_prev)->thr_next = t->thr_next;	
	else qs[id] = t->thr_next;

	if (t->thr_next != NULL) (t->thr_next)->thr_prev = t->thr_prev;

	// Check if queue is empty?
	if (qs[id] == NULL)
		whichqs = whichqs & (~(1 << id));
}

void recompute_priority(void)
{
	int i;
	thread_t *t1, *t2;

	// For all the queues qs[], select one thread at a time,
	// compute its pririty, insert it into tqs[] queue

	for (i=0; i<32; i++)
	{
		while (qs[i] != NULL)
		{
			t1 = qs[i];
			dequeue_thread(i, t1, qs);
			t1->thr_cpupri /= 2;	
			t1->thr_pri = USER_PRI + (t1-> thr_cpupri / 4) + (2 * t1->thr_nice);
			enqueue_thread(t1, tqs);
		}
	}
	for (i=0; i<32; i++)
		qs[i] = tqs[i];
}

void schedule()
{
	int id;
	thread_t *t, *t1;
	ucontext_t dummy;

	// Select the first thread in first non-empty queue
	// dequeue it and context switch
	for (id=0; id < 32; i++)
		if (whichqs & (1 << id))
			break;

	// Check if non-empty queue is found?
	if (id < 32)
	{
		t = qs[id];
		dequeue_thread(id, t, qs);

		// If current thread is active then enqueue it.
		if (current_thread != NULL)
		{
			enqueue_thread(current_thread, qs);
			t1 = current_thread;
			current_thread = t;
			swap_context(&t1->thr_context, &t->thr_context);
		}
		else 
		{
			current_thread = t;
			swap_context(&dummy, &t->thr_context);
		}
	}
	else
	{
		// Deadlock situtation is not addressed.
		// Assuming that at least one runnable thread must be available.
		if (current_thread != NULL) return;
		else exit(0);
	}
}
/*
void schedule(void)
{
	thread_t *t1, *t2;
	thread_t * newthr = NULL;
	int newpri = 127;
	struct itimerval tm;
	ucontext_t dummy;
	sigset_t sigt;

	t1 = ready_q;

	// Select the thread with higest priority
	while (t1 != NULL)
	{
		if (newpri > t1->thr_usrpri + t1->thr_cpupri)
		{
			newpri = t1->thr_usrpri + t1->thr_cpupri;
			newthr = t1;
		}

		t1 = t1->thr_next;
	}

	if (newthr == NULL)
	{
		if (current_thread == NULL)
		{
			// No more threads? (stop itimer)
			tm.it_interval.tv_usec = 0;
			tm.it_interval.tv_sec = 0;
			tm.it_value.tv_usec = 0; // ZERO Disable
			tm.it_value.tv_sec = 0;
			setitimer(ITIMER_PROF, &tm, NULL);
		}
		return;
	}
	else
	{
		// TO DO :: Reenabling of signals must be done.
		// Switch to new thread
		if (current_thread != NULL)
		{
			t2 = current_thread;
			current_thread = newthr;
			timeq = 0;
			sigemptyset(&sigt);
			sigaddset(&sigt, SIGPROF);
			sigprocmask(SIG_UNBLOCK, &sigt, NULL);
			swapcontext(&(t2->thr_context), &(current_thread->thr_context));
		}
		else 
		{
			// No current thread? might be terminated
			current_thread = newthr;
			timeq = 0;
			sigemptyset(&sigt);
			sigaddset(&sigt, SIGPROF);
			sigprocmask(SIG_UNBLOCK, &sigt, NULL);
			swapcontext(&(dummy), &(current_thread->thr_context));
		}
	}
}
*/

void timertick_handler(int alrm)
{
	thread_t *t1;

	ticks ++;
	current_thread->thr_totalcpu += 10; // One timer tick = 10 Units
	current_thread->thr_cpupri += 10; // One timer tick
	timeq += 10;
	if (ticks % 25 == 0)
	{
		// recalculate priorities of the other threads 
		recompute_priority();
	}
	if (timeq >= 50)
	{
		// Time quantum expired?
		schedule();
	}
}

void mutex_init(mutex_t *mut, int val)
{
	mut->val = val;
	mut->owner = NULL;
	mut->wait_q = NULL;
}

int mutex_lock(mutex_t *mut)
{
	sigset_t sigt;
	thread_t *t1;

	// Block timer
	sigemptyset(&sigt);
	sigaddset(&sigt, SIGPROF);
	sigprocmask(SIG_BLOCK, &sigt, NULL);

	mut->val--;
	if (mut->val < 0)
	{
		// Sleep, remove from ready_q
		if (current_thread->thr_prev != NULL)
			(current_thread->thr_prev)->thr_next = current_thread->thr_next;
		if (current_thread->thr_next != NULL)
			(current_thread->thr_next)->thr_prev = current_thread->thr_prev;

		if (current_thread->thr_prev == NULL)
			ready_q = current_thread->thr_next;
		// Add this to the waiting q
		if (mut->wait_q == NULL)
		{
			current_thread->thr_prev = NULL;
			current_thread->thr_next = NULL;
			mut->wait_q = current_thread;
		}
		else
		{
			t1 = mut->wait_q;
			while (t1->thr_next != NULL)
				t1 = t1->thr_next;
			t1->thr_next = current_thread;
			current_thread->thr_next = NULL;
			current_thread->thr_prev = t1;
		}
			
		// Call scheduler
		schedule();
	}	

	// Lock it
	mut->owner = current_thread;
	// Enable timer
	sigprocmask(SIG_UNBLOCK, &sigt, NULL);
	return 0;	
}

int mutex_trylock(mutex_t *mut)
{
	sigset_t sigt;

	// Block timer
	sigemptyset(&sigt);
	sigaddset(&sigt, SIGPROF);
	sigprocmask(SIG_BLOCK, &sigt, NULL);

	if (mut->val <= 0)
	{
		sigprocmask(SIG_UNBLOCK, &sigt, NULL);
		return -1;	
	}	

	// Lock it
	mut->val--;
	mut->owner = current_thread;
	// Enable timer
	sigprocmask(SIG_UNBLOCK, &sigt, NULL);
	return 0;	
}

int mutex_unlock(mutex_t *mut)
{
	sigset_t sigt;
	thread_t *t1;

	if (mut->owner != current_thread) return -1; // Error
	// Block timer
	sigemptyset(&sigt);
	sigaddset(&sigt, SIGPROF);
	sigprocmask(SIG_BLOCK, &sigt, NULL);
	
	mut->val++;
	if (mut->val <= 0)
	{
		// wakeup the first waiting thread.
		t1 = mut->wait_q;
		mut->wait_q = t1->thr_next;
		// Add t1 to ready q
		t1->thr_next = ready_q;
		t1->thr_prev = NULL;
		ready_q->thr_prev = t1;
		ready_q = t1;
	}	

	// Enable timer
	sigprocmask(SIG_UNBLOCK, &sigt, NULL);
	return 0;	
}

void condition_init(condition_t *cond)
{
	cond->wait_q = NULL;
}

void condition_wait(condition_t *cond, mutex_t *mut)
{
	sigset_t sigt;
	thread_t *t1;

	// Block timer
	sigemptyset(&sigt);
	sigaddset(&sigt, SIGPROF);
	sigprocmask(SIG_BLOCK, &sigt, NULL);

	// Sleep, remove from ready_q
	if (current_thread->thr_prev != NULL)
		(current_thread->thr_prev)->thr_next = current_thread->thr_next;
	if (current_thread->thr_next != NULL)
		(current_thread->thr_next)->thr_prev = current_thread->thr_prev;

	if (current_thread->thr_prev == NULL)
		ready_q = current_thread->thr_next;
	// Add this to the waiting q
	if (cond->wait_q == NULL)
	{
		current_thread->thr_prev = NULL;
		current_thread->thr_next = NULL;
		cond->wait_q = current_thread;
	}
	else
	{
		t1 = cond->wait_q;
		while (t1->thr_next != NULL)
			t1 = t1->thr_next;
		t1->thr_next = current_thread;
		current_thread->thr_next = NULL;
		current_thread->thr_prev = t1;
	}
			
	// Call scheduler
	schedule();
	sigprocmask(SIG_UNBLOCK, &sigt, NULL);
}

int condition_signal(condition_t *cond)
{
	sigset_t sigt;
	thread_t *t1;

	// Block timer
	sigemptyset(&sigt);
	sigaddset(&sigt, SIGPROF);
	sigprocmask(SIG_BLOCK, &sigt, NULL);
	
	// wakeup the first waiting thread.
	t1 = cond->wait_q;
	cond->wait_q = t1->thr_next;
	// Add t1 to ready q
	t1->thr_next = ready_q;
	t1->thr_prev = NULL;
	ready_q->thr_prev = t1;
	ready_q = t1;

	// Enable timer
	sigprocmask(SIG_UNBLOCK, &sigt, NULL);
	return 0;	
}

int condition_broadcast(condition_t *cond)
{
	sigset_t sigt;
	thread_t *t1, *t2;

	// Block timer
	sigemptyset(&sigt);
	sigaddset(&sigt, SIGPROF);
	sigprocmask(SIG_BLOCK, &sigt, NULL);
	
	// wakeup all waiting threads.
	t1 = cond->wait_q;
	cond->wait_q = NULL;
	while (t1 != NULL)
	{
		t2 = t1->thr_next;

		// Add t1 to ready q
		t1->thr_next = ready_q;
		t1->thr_prev = NULL;
		ready_q->thr_prev = t1;
		ready_q = t1;

		t1 = t2;
	}

	// Enable timer
	sigprocmask(SIG_UNBLOCK, &sigt, NULL);
	return 0;	
}



// The child thread will execute this function
void threadFunction(void *arg)
{
	int i, thrno;
	thrno = *(int *)arg;
	for ( ; ; )
	{
		printf("This is child thread : %d\n", thrno);
		for (i=0; i<0x100000; i++) ;
	}
}

int main()
{
	thread_t *t1, *t2;
	int t1no=1, t2no=2, j;
	t1 = thread_create(threadFunction, (void *)&t1no);
	t2 = thread_create(threadFunction, (void *)&t2no);

	for ( ; ; )
	{
		printf("This is main thread\n");
		for (j=0; j<0x200000; j++) ;
	}
}

