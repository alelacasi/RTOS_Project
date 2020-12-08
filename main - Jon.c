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

void *producer(void *ptr);
void *consumer();

int value1, value2, value3, value4, value5, value6, value7, value8;

struct thread_args{
    char *filename;
    int loc;
    int period;
    int *value;
};

const char* getfield(char* line, int num){
	const char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")){
        if (!--num)
            return tok;
    }
    return NULL;
}


void *producer(void *ptr){

	struct thread_args *args = (struct thread_args *)ptr;

	FILE* stream = fopen("/home/cardata.csv", "r");
    char line[2048];
    fgets(line, 2048, stream);
    char* value;
    int *stored = args->value;
    int num = args->loc;
    int count = 0;

    while (1){

    	//Read a new line, set value to that field
    	fgets(line, 2048, stream);
        char* tmp = strdup(line);

        //If you reach the end of the document, break
        if(tmp == NULL)
        	break;

    	//Fetch value
    	value = getfield(tmp, num);

        while (count<=1000){

        	//Store value in global variable
            *stored = atoi(value);

            //Sleep for period (2ms offset due to scheduler discrepancy
            usleep(args->period*1000 - 2);
            count += args->period;
        }

        free(tmp);

        //Each row accounts for 1000ms
        count -= 1000;

    }

	return(NULL);
}

void *consumer()
{

	while(1) {
		printf("--------------Displaying Sensor Data--------------\n");
		printf("Fuel Consumption			: %i\n", value1);
		printf("Engine Speed				: %i\n", value2);
		printf("Engine Coolant Temperature		: %i\n", value3);
		printf("Engine Gear				: %i\n", value4);
		printf("Transmission Oil Temperature		: %i\n", value5);
		printf("Vehicle Speed				: %i\n", value6);
		printf("Acceleration Speed Longitudinal Temp	: %i\n", value7);
		printf("Indication Of Brake Switch		: %i\n", value8);
		printf("--------------------------------------------------\n");
		delay(25);
	}

	return(NULL);
}

int main (int argc, char *argv[]) {

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
    pthread_t   consumer_thread_id;

	fuel_consumption = (struct thread_args *) malloc(sizeof(struct thread_args));
    fuel_consumption->filename = "fuel_consumption";
    fuel_consumption->loc = 1;
    fuel_consumption->period = 10;
    fuel_consumption->value = &value1;

    engine_speed = (struct thread_args *) malloc(sizeof(struct thread_args));
	engine_speed->filename = "engine_speed";
	engine_speed->loc = 13;
	engine_speed->period = 500;
	engine_speed->value = &value2;

	engine_coolant_temp = (struct thread_args *) malloc(sizeof(struct thread_args));
	engine_coolant_temp->filename = "engine_coolant_temp";
	engine_coolant_temp->loc = 18;
	engine_coolant_temp->period = 2000;
	engine_coolant_temp->value = &value3;

	current_gear = (struct thread_args *) malloc(sizeof(struct thread_args));
	current_gear->filename = "current_gear";
	current_gear->loc = 34;
	current_gear->period = 100;
	current_gear->value = &value4;

	transmission_oil_temperature = (struct thread_args *) malloc(sizeof(struct thread_args));
	transmission_oil_temperature->filename = "transmission_oil_temperature";
	transmission_oil_temperature->loc = 35;
	transmission_oil_temperature->period = 5000;
	transmission_oil_temperature->value = &value5;

	vehicle_speed = (struct thread_args *) malloc(sizeof(struct thread_args));
	vehicle_speed->filename = "vehicle_speed";
	vehicle_speed->loc = 44;
	vehicle_speed->period = 100;
	vehicle_speed->value = &value6;

	acceleration_speed_longitudinal = (struct thread_args *) malloc(sizeof(struct thread_args));
	acceleration_speed_longitudinal->filename = "acceleration_speed_longitudinal";
	acceleration_speed_longitudinal->loc = 45;
	acceleration_speed_longitudinal->period = 150;
	acceleration_speed_longitudinal->value = &value7;

	indication_of_brake_switch = (struct thread_args *) malloc(sizeof(struct thread_args));
	indication_of_brake_switch->filename = "indication_of_brake_switch";
	indication_of_brake_switch->loc = 46;
	indication_of_brake_switch->period = 100;
	indication_of_brake_switch->value = &value8;

	//Producers
	printf("Producers Creation...\n");
	pthread_create(&fuel_thread_id, NULL, (void *) &producer, fuel_consumption);
	pthread_create(&espeed_thread_id, NULL, (void *) &producer, engine_speed);
	pthread_create(&cool_thread_id, NULL, (void *) &producer, engine_coolant_temp);
	pthread_create(&gear_thread_id, NULL, (void *) &producer, current_gear);
	pthread_create(&oiltmp_thread_id, NULL, (void *) &producer, transmission_oil_temperature);
	pthread_create(&vspeed_thread_id, NULL, (void *) &producer, vehicle_speed);
	pthread_create(&accSpeed_thread_id, NULL, (void *) &producer, acceleration_speed_longitudinal);
	pthread_create(&brake_thread_id, NULL, (void *) &producer, indication_of_brake_switch);

	//Producers
	printf("Consumer Creation...\n");
	pthread_create(&consumer_thread_id, NULL, &consumer, NULL);

    pthread_join(fuel_thread_id, NULL);
    pthread_join(espeed_thread_id, NULL);
    pthread_join(cool_thread_id, NULL);
    pthread_join(gear_thread_id, NULL);
    pthread_join(oiltmp_thread_id, NULL);
    pthread_join(vspeed_thread_id, NULL);
    pthread_join(accSpeed_thread_id, NULL);
    pthread_join(brake_thread_id, NULL);
    pthread_join(consumer_thread_id, NULL);

    printf("Program Ending...\n");

	pause();

	return 0;
}
