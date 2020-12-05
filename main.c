
#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>



void *functionA();
void *functionB();
void *universalthread(void *ptr);
 
struct thread_args
{
    char *filename;
    int loc;
    int sleep_ms;
    int looptime;
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

    fuel_consumption.loc = 1;    //10ms  @1
    engine_speed.loc = 13;         //500ms @13
    engine_cool_press.loc = 18 ;    //2s    @18
    current_gear.loc = 34;         //100ms @34

    fuel_consumption.sleep_ms = 10;    //10ms  @1
    engine_speed.sleep_ms = 500;         //500ms @13
    engine_cool_press.sleep_ms = 2,000 ;    //2s    @18
    current_gear.sleep_ms = 100;         //100ms @34

    fuel_consumption.sleep_ms = 100;    //10ms  @1
    engine_speed.sleep_ms = 2;         //500ms @13
    engine_cool_press.sleep_ms = 0 ;    //2s    @18
    current_gear.sleep_ms = 10;         //100ms @34    


 
	printf("We are now creating four threads...\n");
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &fuel_consumption);
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &engine_speed);
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &engine_cool_press);
	pthread_create(NULL,NULL, (void *) &universalthread, (void *) &current_gear);
	printf("Threads created.\n");

	printf("Main thread now waiting for first thread to finish\n");
	
	printf("Main thread now waiting for termination through user.\n");
	printf("Other threads keep running in the background until\n");
	printf("they finish or are terminated together with the main thread.\n");

 	pause();

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
	FILE* stream = fopen("public/coen320/dataset.csv", "r");
    char line[2048];
    char* value;
    int num = args->loc;
    while (fgets(line, 2048, stream))
    {
        int count = args->looptime;
        char* tmp = strdup(line);    
        const char* tok;
        value = getfield(line, args->filename)
    	printf("%s: %s\n",args->filename, value);
        sleep(args->sleep_ms);
        count--;
        
        while (count>0)
        {
            printf("%s: %s\n",args->filename, value);
            sleep(args->sleep_ms);
            count--;
        }
        

        // NOTE strtok clobbers tmp
        free(tmp);
    }
	
	return(NULL);
}
//192.168.141.3
