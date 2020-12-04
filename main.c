/*  T H R E A D  C R E A T I O N  */

/* Project Name: "example_threads" */

/* What are threads under QNX?
 * Under QNX Neutrino, there are processes and threads. It's
 * not a process that actually runs, it's (at least) one thread
 * that runs inside.
 * Threads are the ones being scheduled, they are consuming
 * CPU time when they run.
 * Per default, a process has one thread, the main thread.
 * To create this main thread, you don't need to do anything,
 * it is created automatically for you.
 * You can create further threads within your process, for 
 * example to parallelize tasks. A process has its own virtual
 * address space. All threads share the memory of the process.
 * In this example program, we will create some additional
 * threads using the appropriate functions.
 */
 
/* In a second thread related example,
 * "example_sched.c", we will play with priorities
 * and scheduling algorithms.
 */
 
/* More information:
 * See "Processes and Threads" in the Programmer's Guide,
 * chapter "Programming Overview". 
 * You will find it in the Help Viewer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>



void *functionA();
void *functionB();
void *universalthread(void *ptr);


/* At this point our process goes live and has one thread, the
 * main thread. All setup for this was done by the OS.
 */
 
struct thread_args
{
    char *filename;
    int loc;
};

	struct thread_args fuel_consumption;
	struct thread_args engine_speed;
	struct thread_args engine_cool_press;
	struct thread_args current_gear;
	//struct thread_args transm_oil_temp;
	//struct thread_args
	//struct thread_args
	//struct thread_args

int main ()
{
    fuel_consumption.filename = "fuel_consumption";    //10ms  @1
    engine_speed.filename = "engine_speed";         //500ms @13
    engine_cool_press.filename = "engine_cool_press" ;    //2s    @18
    current_gear.filename = "current_gear";         //100ms @34
    //transm_oil_temp;      //5s    @35
    //vehicle_speed;        //100ms @44
    //accel_speed_longi;    //150ms @45
    //indic_break_switch;   //100ms @46
 
	printf("We are now creating four threads...\n");
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &fuel_consumption);
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &engine_speed);
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &engine_cool_press);
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &current_gear);
	printf("Threads created.\n");
	
	
/* Now, what shall we do in the main thread? In fact you can do
 * anything you want. It can do further work, or it can wait
 * for another thread to complete (thread exits its function).
 * Let's wait for a thread to complete! For this we need its
 * thread ID and the function pthread_join().
 */

	printf("Main thread now waiting for first thread to finish\n");

/* When we created the first thread, we stored the thread ID
 * in "our_thread_id". We use it now. The function pthread_join()
 * will not return until the corresponding thread completes.
 */
	//pthread_join(our_thread_id, NULL);	
//	/printf("Thread %d completed its function!\n",our_thread_id); 


/* Now let's have the main thread wait for cancellation through
 * user (Ctrl+C). The other threads will run until they are
 * completed. If you press Ctrl+C before they are completed,
 * they are terminated along with the main thread. If you wait
 * a while, the threads will finish on their own. Type "pidin"
 * on a different console or look in the System Information
 * Perspective - the finished threads will be labelled 'dead'.	
 */
	
	printf("Main thread now waiting for termination through user.\n");
	printf("Other threads keep running in the background until\n");
	printf("they finish or are terminated together with the main thread.\n");

/* Hitting Ctrl+C sends a SIGTERM signal to the process. If the
 * process receives this signal, it is killed along with all of
 * its threads. We now use the pause() function to wait for
 * the signal.
 */
 	pause();

/* Hitting Ctrl+C will end the whole program, thus any lines
 * after the pause() and the } will not be executed.
 * If you want the main thread exit after the others threads
 * finished, use pthread_join() as shown above.
 * Have fun while exploring!
 */
 
	return EXIT_SUCCESS;
}


void *functionA()
{
	
	
	
	printf("functionA active\n");
	sleep(5);
	printf ("functionA is finished.\n");
	return(NULL);
}

void *functionB()
{

	printf("functionB is working...\n");
	sleep (7);
	printf("functionB done.\n");
	return(NULL);
}	

const char* getfield(char* line, int num)
{
	const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void *universalthread(void *ptr)
{
	struct thread_args *args = ptr;
	FILE* stream = fopen("/public/coen320/Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv", "r");
    char line[2048];
    char* value;
    int num = args->loc;
    int count = 0;
    while (fgets(line, 2048, stream))
    {
        char* tmp = strdup(line);    
        const char* tok;
    	for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
    	{
		    if (!--num)
		        value = tok;
		}
    	printf("%s: %s\n",args->filename, value);
        sleep(2);

        if(count==3){
            break;
        }
        count++;
        // NOTE strtok clobbers tmp
        free(tmp);
    }
	
	return(NULL);
}
