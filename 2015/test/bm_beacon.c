#pragma config(UserModel, "../pragmas/baemax.h")

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FOUR_WHEEL_DRIVE
#define DEAD_RECKON_GYRO

#include "../../lib/sensors/drivers/hitechnic-sensormux.h"

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "../../lib/sensors/drivers/hitechnic-sensormux.h"
#include "../../lib/sensors/drivers/hitechnic-protoboard.h"
#include "../../lib/sensors/drivers/hitechnic-irseeker-v2.h"
#include "../../lib/sensors/drivers/hitechnic-gyro.h"

const tMUXSensor HTGYRO  = msensor_S4_3;
const tMUXSensor irr_left = msensor_S4_1;
const tMUXSensor irr_right = msensor_S4_2;

bool beacon_done;
int distance_monitor_distance;

#include "../library/baemax_defs.h"
#include "../../lib/baemax_drivetrain_defs.h"
#include "../../lib/drivetrain_square.h"
#include "../../lib/limit_switch.h"
#include "../../lib/dead_reckon.h"
#include "../../lib/data_log.h"
#include "../../lib/ir_utils.h"
#include "../../lib/us_utils.h"
#include "../../lib/button_utils.h"
#include "../../lib/us_cascade_utils.c"
#include "../library/auto_utils.h"

const tMUXSensor HTPB = msensor_S4_4;

task main()
{
    int i;
    int segment;

    i = 20;
    disableDiagnosticsDisplay();

    eraseDisplay();
    servo[rightEye] = i;

    wait1Msec(500);

    while (i < 255) {
        servo[rightEye] = i;
        wait1Msec(100);
        segment = HTIRS2readACDir(irr_right);
        nxtDisplayCenteredBigTextLine(4, "%d %d", segment, i);
        if (segment == 6) {
            break;
        }
        i++;
    }

    while(true) {
        segment = HTIRS2readACDir(irr_right);
        nxtDisplayCenteredBigTextLine(2, "%d %d", segment, i);
    }
}