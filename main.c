#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>


#define ONE_THOUSAND	1000
#define ONE_MILLION		1000000
/* offset and period are in microsends. */
#define OFFSET 1000000
#define PERIOD 1000000

sigset_t sigst;

double currentTime = 0.0;

void *universalthread(void *ptr);

struct thread_args
{
    char *filename;
    int loc;
    int sleep_ms;
    int looptime;
};

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


void *universalThread(void *ptr)
{
	struct thread_args *args = (struct thread_args *)ptr;
	//int executionTimer = 0;

	FILE* stream = fopen("/home/dataset.csv", "r");
    char line[2048];
    fgets(line, 2048, stream);
    char* value;
	printf("Here: %s\n", args->filename);

    int num = args->loc;
    //printf("Num: %d\n", num);
    while (1)
    {
    	fgets(line, 2048, stream);

        int count = args->looptime;
        char* tmp = strdup(line);
        //printf("Count: %d\n", count);

        if(tmp == NULL)
        	break;

        value = getfield(tmp, num);
        printf("%s: %s\n",args->filename, value);
        usleep(args->sleep_ms*1000);
        count--;

        while (count>0)
        {
            printf("%s: %s\n",args->filename, value);
            usleep(args->sleep_ms*1000);
            count--;
        }
        // NOTE strtok clobbers tmp
        free(tmp);
    }


	return(NULL);
}

int main (int argc, char *argv[]) {
	//int res;

	//set and activate a timer
	/*res = start_periodic_timer(OFFSET, PERIOD);
	if (res < 0 ){
		perror("Start periodic timer");
		return -1;
	}*/

	struct thread_args* fuel_consumption;
	struct thread_args* engine_speed;
	struct thread_args* engine_coolant_temp;
	struct thread_args* current_gear;
	struct thread_args* transmission_oil_temperature;
	struct thread_args* vehicle_speed;
	struct thread_args* acceleration_speed_longitudinal;
	struct thread_args* indication_of_brake_switch;

    pthread_t	fuel_thread_id;
    pthread_t	espeed_thread_id;
    pthread_t	cool_thread_id;
    pthread_t	gear_thread_id;
    pthread_t   oiltmp_thread_id;
    pthread_t   vspeed_thread_id;
    pthread_t   accSpeed_thread_id;
    pthread_t   brake_thread_id;


	fuel_consumption = (struct thread_args *) malloc(sizeof(struct thread_args));
    fuel_consumption->filename = "fuel_consumption";
    fuel_consumption->loc = 1;
    fuel_consumption->sleep_ms = 10;
    fuel_consumption->looptime = 100;

    engine_speed = (struct thread_args *) malloc(sizeof(struct thread_args));
	engine_speed->filename = "engine_speed";    //10ms  @1
	engine_speed->loc = 13;    //10ms  @1
	engine_speed->sleep_ms = 500;    //10ms  @1
	engine_speed->looptime = 2;    //10ms  @1

	engine_coolant_temp = (struct thread_args *) malloc(sizeof(struct thread_args));
	engine_coolant_temp->filename = "engine_coolant_temp";    //10ms  @1
	engine_coolant_temp->loc = 18;    //10ms  @1
	engine_coolant_temp->sleep_ms = 2,000;    //10ms  @1
	engine_coolant_temp->looptime = 0;    //10ms  @1

	current_gear = (struct thread_args *) malloc(sizeof(struct thread_args));
	current_gear->filename = "current_gear";    //10ms  @1
	current_gear->loc = 34;    //10ms  @1
	current_gear->sleep_ms = 100;    //10ms  @1
	current_gear->looptime = 10;    //10ms  @1

	transmission_oil_temperature = (struct thread_args *) malloc(sizeof(struct thread_args));
	transmission_oil_temperature->filename = "transmission_oil_temperature";    //10ms  @1
	transmission_oil_temperature->loc = 35;    //10ms  @1
	transmission_oil_temperature->sleep_ms = 5000;    //10ms  @1
	transmission_oil_temperature->looptime = 0;    //10ms  @1

	vehicle_speed = (struct thread_args *) malloc(sizeof(struct thread_args));
	vehicle_speed->filename = "vehicle_speed";    //10ms  @1
	vehicle_speed->loc = 44;    //10ms  @1
	vehicle_speed->sleep_ms = 100;    //10ms  @1
	vehicle_speed->looptime = 10;    //10ms  @1

	acceleration_speed_longitudinal = (struct thread_args *) malloc(sizeof(struct thread_args));
	acceleration_speed_longitudinal->filename = "acceleration_speed_longitudinal";    //10ms  @1
	acceleration_speed_longitudinal->loc = 45;    //10ms  @1
	acceleration_speed_longitudinal->sleep_ms = 150;    //10ms  @1
	acceleration_speed_longitudinal->looptime = 7;    //10ms  @1

	indication_of_brake_switch = (struct thread_args *) malloc(sizeof(struct thread_args));
	indication_of_brake_switch->filename = "indication_of_brake_switch";    //10ms  @1
	indication_of_brake_switch->loc = 46;    //10ms  @1
	indication_of_brake_switch->sleep_ms = 100;    //10ms  @1
	indication_of_brake_switch->looptime = 10;    //10ms  @1

    //Timer
	//pthread_create(NULL, NULL, (void *) &task_body, NULL);

	//Producers
	printf("We are now creating the producers...\n");
	pthread_create(&fuel_thread_id, NULL, (void *) &universalThread, fuel_consumption);
	pthread_create(&espeed_thread_id, NULL, (void *) &universalThread, engine_speed);
	pthread_create(&cool_thread_id, NULL, (void *) &universalThread, engine_coolant_temp);
	pthread_create(&gear_thread_id, NULL, (void *) &universalThread, current_gear);
	pthread_create(&oiltmp_thread_id, NULL, (void *) &universalThread, transmission_oil_temperature);
	pthread_create(&vspeed_thread_id, NULL, (void *) &universalThread, vehicle_speed);
	pthread_create(&accSpeed_thread_id, NULL, (void *) &universalThread, acceleration_speed_longitudinal);
	pthread_create(&brake_thread_id, NULL, (void *) &universalThread, indication_of_brake_switch);

    pthread_join(fuel_thread_id, NULL);
    pthread_join(espeed_thread_id, NULL);
    pthread_join(cool_thread_id, NULL);
    pthread_join(gear_thread_id, NULL);
    pthread_join(oiltmp_thread_id, NULL);
    pthread_join(vspeed_thread_id, NULL);
    pthread_join(accSpeed_thread_id, NULL);
    pthread_join(brake_thread_id, NULL);

    printf("Ending...\n");

	pause();

	return 0;
}

//192.168.141.3
