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



int start_periodic_timer(uint64_t offset, int period) {
	struct itimerspec timer_spec;
	struct sigevent sigev;
	timer_t timer;
	const int signal = SIGALRM;
	int res;

	/* set timer parameters */
	timer_spec.it_value.tv_sec = offset / ONE_MILLION;
	timer_spec.it_value.tv_nsec = (offset % ONE_MILLION) * ONE_THOUSAND;
	timer_spec.it_interval.tv_sec = period / ONE_MILLION;
	timer_spec.it_interval.tv_nsec = (period % ONE_MILLION) * ONE_THOUSAND;

	sigemptyset(&sigst); // initialize a signal set
	sigaddset(&sigst, signal); // add SIGALRM to the signal set
	sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal

	/* set the signal event a timer expiration */
	memset(&sigev, 0, sizeof(struct sigevent));
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = signal;

	/* create timer */
	res = timer_create(CLOCK_MONOTONIC, &sigev, &timer);

	if (res < 0) {
		perror("Timer Create");
		exit(-1);
	}

	/* activate the timer */
	return timer_settime(timer, 0, &timer_spec, NULL);
}

static void task_body(void) {

	static int cycles = 0;

	while (1){

	int dummy;
	/* suspend calling process until a signal is pending */
	sigwait(&sigst, &dummy);


	static uint64_t start;
	uint64_t current;
	struct timespec tv;

	if (start == 0) {
		clock_gettime(CLOCK_MONOTONIC, &tv);
		start = tv.tv_sec * ONE_THOUSAND + tv.tv_nsec / ONE_MILLION;
	}

	clock_gettime(CLOCK_MONOTONIC, &tv);
	current = tv.tv_sec * ONE_THOUSAND + tv.tv_nsec / ONE_MILLION;

//	if (cycles > 0) {
//		fprintf(stderr, "Ave interval between instances: %f milliseconds\n",
//			(double)(current-start));
//	}

	currentTime = (double)(current-start);
	printf("%f\n", currentTime);
	cycles++;

	}
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


void *universalThread(void *ptr)
{
	struct thread_args *args = ptr;
	double executionTimer = 0;

	FILE* stream = fopen("/home/dataset.csv", "r");
    char line[2048];
    char* value;

    while (1){

		fgets(line, 2048, stream);

		while (executionTimer < 1000) {

			char* tmp = strdup(line);
			free(tmp);
			printf("%s", args->filename);
			value = getfield(tmp, args->loc);
			printf(": %s\n", value);
			executionTimer += args->sleep_ms;
			usleep(args->sleep_ms*1000);

	}

	executionTimer -= 1000;

  }


	return(NULL);
}

int main (int argc, char *argv[]) {
	int res;

	//set and activate a timer
	res = start_periodic_timer(OFFSET, PERIOD);
	if (res < 0 ){
		perror("Start periodic timer");
		return -1;
	}

	struct thread_args* fuel_consumption;
	struct thread_args* engine_speed;
	struct thread_args* engine_coolant_temp;
	struct thread_args* current_gear;
	struct thread_args* transmission_oil_temperature;
	struct thread_args* vehicle_speed;
	struct thread_args* acceleration_speed_longitudinal;
	struct thread_args* indication_of_brake_switch;

	fuel_consumption = malloc(sizeof(struct thread_args));
    fuel_consumption->filename = "fuel_consumption";
    fuel_consumption->loc = 1;
    fuel_consumption->sleep_ms = 10;
    fuel_consumption->looptime = 100;

    engine_speed = malloc(sizeof(struct thread_args));
	engine_speed->filename = "engine_speed";    //10ms  @1
	engine_speed->loc = 13;    //10ms  @1
	engine_speed->sleep_ms = 500;    //10ms  @1
	engine_speed->looptime = 2;    //10ms  @1

	engine_coolant_temp = malloc(sizeof(struct thread_args));
	engine_coolant_temp->filename = "engine_coolant_temp";    //10ms  @1
	engine_coolant_temp->loc = 18;    //10ms  @1
	engine_coolant_temp->sleep_ms = 2,000;    //10ms  @1
	engine_coolant_temp->looptime = 0;    //10ms  @1

	current_gear = malloc(sizeof(struct thread_args));
	current_gear->filename = "current_gear";    //10ms  @1
	current_gear->loc = 34;    //10ms  @1
	current_gear->sleep_ms = 100;    //10ms  @1
	current_gear->looptime = 10;    //10ms  @1

	transmission_oil_temperature = malloc(sizeof(struct thread_args));
	transmission_oil_temperature->filename = "transmission_oil_temperature";    //10ms  @1
	transmission_oil_temperature->loc = 35;    //10ms  @1
	transmission_oil_temperature->sleep_ms = 5000;    //10ms  @1
	transmission_oil_temperature->looptime = 0;    //10ms  @1

	vehicle_speed = malloc(sizeof(struct thread_args));
	vehicle_speed->filename = "vehicle_speed";    //10ms  @1
	vehicle_speed->loc = 44;    //10ms  @1
	vehicle_speed->sleep_ms = 100;    //10ms  @1
	vehicle_speed->looptime = 10;    //10ms  @1

	acceleration_speed_longitudinal = malloc(sizeof(struct thread_args));
	acceleration_speed_longitudinal->filename = "acceleration_speed_longitudinal";    //10ms  @1
	acceleration_speed_longitudinal->loc = 45;    //10ms  @1
	acceleration_speed_longitudinal->sleep_ms = 150;    //10ms  @1
	acceleration_speed_longitudinal->looptime = 7;    //10ms  @1

	indication_of_brake_switch = malloc(sizeof(struct thread_args));
	indication_of_brake_switch->filename = "indication_of_brake_switch";    //10ms  @1
	indication_of_brake_switch->loc = 46;    //10ms  @1
	indication_of_brake_switch->sleep_ms = 100;    //10ms  @1
	indication_of_brake_switch->looptime = 10;    //10ms  @1

    //Timer
	pthread_create(NULL, NULL, (void *) &task_body, NULL);

	//Producers
	//pthread_create(NULL, NULL, (void *) &universalThread, fuel_consumption);
	//pthread_create(NULL, NULL, (void *) &universalThread, engine_speed);
	//pthread_create(NULL, NULL, (void *) &universalThread, engine_coolant_temp);
	//pthread_create(NULL, NULL, (void *) &universalThread, current_gear);
	//pthread_create(NULL, NULL, (void *) &universalThread, transmission_oil_temperature);
	//pthread_create(NULL, NULL, (void *) &universalThread, vehicle_speed);
	//pthread_create(NULL, NULL, (void *) &universalThread, acceleration_speed_longitudinal);
	//pthread_create(NULL, NULL, (void *) &universalThread, indication_of_brake_switch);

	pause();

	return 0;
}
