#include <stdio.h>
#include <stdlib.h>

const int NUMOFTRAITS = 55;

// Real Filepath /public/coen320/Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv
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


int main (int argc, char *argv[]) {

    char*  fuel_consumption;    //10ms  @1
    char* engine_speed;         //500ms @13
    char* engine_cool_press;    //2s    @18
    char* current_gear;         //100ms @34
    char* transm_oil_temp;      //5s    @35
    char* vehicle_speed;        //100ms @44
    char* accel_speed_longi;    //150ms @45
    char* indic_break_switch;   //100ms @46


	
    FILE* stream = fopen("Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv", "r");

    char line[2048];
    int count = 0;
    while (fgets(line, 2048, stream))
    {
        char* tmp = strdup(line);
        fuel_consumption = getfield(tmp,1);
        printf("Fuel_consumption: %s\n", fuel_consumption);
        sleep(1);

        if(count==3){
            break;
        }
        count++;
        // NOTE strtok clobbers tmp
        free(tmp);
    }
    count = 0;
        while (fgets(line, 2048, stream))
    {
        char* tmp = strdup(line);
        engine_speed = getfield(tmp,13);
        printf("Engine Speed: %s\n", engine_speed);
        sleep(1);

        if(count==3){
            break;
        }
        count++;
        // NOTE strtok clobbers tmp
        free(tmp);
    }


	return 0;
}