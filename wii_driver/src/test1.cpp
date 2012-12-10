#include "ros/ros.h"
#include "std_msgs/String.h"
#include "/home/nirmiti/ros/wiiuse/src/wiiuse.h"
#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */


void handle_event(struct wiimote_t* wm) {
//printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

/* if a button is pressed, report it */
/*if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) prin;
if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) printf("B pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) printf("UP pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) printf("DOWN pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT)) printf("LEFT pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT)) printf("RIGHT pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) printf("MINUS pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) printf("PLUS pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) printf("ONE pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) printf("TWO pressed\n");
if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME)) printf("HOME pressed\n");
*/
/*
* Pressing minus will tell the wiimote we are no longer interested in movement.
* This is useful because it saves battery power.
*/
if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS))
wiiuse_motion_sensing(wm, 0);

/*
* Pressing plus will tell the wiimote we are interested in movement.
*/
if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS))
wiiuse_motion_sensing(wm, 1);

/*
* Pressing B will toggle the rumble
*
* if B is pressed but is not held, toggle the rumble
*/
if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B))
wiiuse_toggle_rumble(wm);

if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP))
wiiuse_set_ir(wm, 1);
if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN))
wiiuse_set_ir(wm, 0);

    /*
* Motion+ support
*/
    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_ONE))
    {
        if(WIIUSE_USING_EXP(wm))
            wiiuse_set_motion_plus(wm, 2); // nunchuck pass-through
        else
            wiiuse_set_motion_plus(wm, 1); // standalone
    }

    if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO))
    {
        wiiuse_set_motion_plus(wm, 0); // off
    }

/* if the accelerometer is turned on then print angles */
if (WIIUSE_USING_ACC(wm)) {
ROS_INFO("wiimote roll = %f [%f]\n", wm->orient.roll, wm->orient.a_roll);
ROS_INFO("wiimote pitch = %f [%f]\n", wm->orient.pitch, wm->orient.a_pitch);
ROS_INFO("wiimote yaw = %f\n", wm->orient.yaw);
}

/*
* If IR tracking is enabled then print the coordinates
* on the virtual screen that the wiimote is pointing to.
*
* Also make sure that we see at least 1 dot.
*/
if (WIIUSE_USING_IR(wm)) {
int i = 0;

/* go through each of the 4 possible IR sources */
for (; i < 4; ++i) {
/* check if the source is visible */
if (wm->ir.dot[i].visible)
ROS_INFO("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
}

ROS_INF0("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
ROS_INFO("IR z distance: %f\n", wm->ir.z);
}

/* show events specific to supported expansions */
if (wm->exp.type == EXP_NUNCHUK || wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
/* nunchuk */
struct nunchuk_t* nc = (nunchuk_t*)&wm->exp.nunchuk;

if (IS_PRESSED(nc, NUNCHUK_BUTTON_C)) ROS_INFO("Nunchuk: C pressed\n");
if (IS_PRESSED(nc, NUNCHUK_BUTTON_Z)) ROS_INFO("Nunchuk: Z pressed\n");

ROS_INFO("nunchuk roll = %f\n", nc->orient.roll);
ROS_INFO("nunchuk pitch = %f\n", nc->orient.pitch);
ROS_INFO("nunchuk yaw = %f\n", nc->orient.yaw);

ROS_INFO("nunchuk joystick angle: %f\n", nc->js.ang);
ROS_INFO("nunchuk joystick magnitude: %f\n", nc->js.mag);
} else if (wm->exp.type == EXP_CLASSIC) {
/* classic controller */
struct classic_ctrl_t* cc = (classic_ctrl_t*)&wm->exp.classic;
/*
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZL)) printf("Classic: ZL pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_B)) printf("Classic: B pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_Y)) printf("Classic: Y pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_A)) printf("Classic: A pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_X)) printf("Classic: X pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZR)) printf("Classic: ZR pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_LEFT)) printf("Classic: LEFT pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_UP)) printf("Classic: UP pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_RIGHT)) printf("Classic: RIGHT pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_DOWN)) printf("Classic: DOWN pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_L)) printf("Classic: FULL L pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_MINUS)) printf("Classic: MINUS pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_HOME)) printf("Classic: HOME pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_PLUS)) printf("Classic: PLUS pressed\n");
if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_R)) printf("Classic: FULL R pressed\n");
*/
ROS_INFO("classic L button pressed: %f\n", cc->l_shoulder);
ROS_INFO("classic R button pressed: %f\n", cc->r_shoulder);
ROS_INFO("classic left joystick angle: %f\n", cc->ljs.ang);
ROS_INFO("classic left joystick magnitude: %f\n", cc->ljs.mag);
ROS_INFO("classic right joystick angle: %f\n", cc->rjs.ang);
ROS_INFO("classic right joystick magnitude: %f\n", cc->rjs.mag);
} else if (wm->exp.type == EXP_GUITAR_HERO_3) {
/* guitar hero 3 guitar */
struct guitar_hero_3_t* gh3 = (guitar_hero_3_t*)&wm->exp.gh3;
/*
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_UP)) printf("Guitar: Strum Up pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_DOWN)) printf("Guitar: Strum Down pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_YELLOW)) printf("Guitar: Yellow pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_GREEN)) printf("Guitar: Green pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_BLUE)) printf("Guitar: Blue pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_RED)) printf("Guitar: Red pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_ORANGE)) printf("Guitar: Orange pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_PLUS)) printf("Guitar: Plus pressed\n");
if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_MINUS)) printf("Guitar: Minus pressed\n");
*/
ROS_INFO("Guitar whammy bar: %f\n", gh3->whammy_bar);
ROS_INFO("Guitar joystick angle: %f\n", gh3->js.ang);
ROS_INFO("Guitar joystick magnitude: %f\n", gh3->js.mag);
} else if (wm->exp.type == EXP_WII_BOARD) {
/* wii balance board */
struct wii_board_t* wb = (wii_board_t*)&wm->exp.wb;
float total = wb->tl + wb->tr + wb->bl + wb->br;
float x = ((wb->tr + wb->br) / total) * 2 - 1;
float y = ((wb->tl + wb->tr) / total) * 2 - 1;
ROS_INFO("Weight: %f kg @ (%f, %f)\n", total, x, y);
/* printf("Interpolated weight: TL:%f TR:%f BL:%f BR:%f\n", wb->tl, wb->tr, wb->bl, wb->br); */
/* printf("Raw: TL:%d TR:%d BL:%d BR:%d\n", wb->rtl, wb->rtr, wb->rbl, wb->rbr); */
}

    if(wm->exp.type == EXP_MOTION_PLUS ||
                wm->exp.type == EXP_MOTION_PLUS_NUNCHUK)
        {
            printf("Motion+ angular rates (deg/sec): pitch:%03.2f roll:%03.2f yaw:%03.2f\n",
                   wm->exp.mp.angle_rate_gyro.pitch,
                   wm->exp.mp.angle_rate_gyro.roll,
                   wm->exp.mp.angle_rate_gyro.yaw);
        }
    }

/**
* @brief Callback that handles a read event.
*
* @param wm Pointer to a wiimote_t structure.
* @param data Pointer to the filled data block.
* @param len Length in bytes of the data block.
*
* This function is called automatically by the wiiuse library when
* the wiimote has returned the full data requested by a previous
* call to wiiuse_read_data().
*
* You can read data on the wiimote, such as Mii data, if
* you know the offset address and the length.
*
* The \a data pointer was specified on the call to wiiuse_read_data().
* At the time of this function being called, it is not safe to deallocate
* this buffer.
*/
void handle_read(struct wiimote_t* wm, byte* data, unsigned short len) {
int i = 0;

ROS_INFO("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
ROS_INFO("finished read of size %i\n", len);
for (; i < len; ++i) {
if (!(i%16))
ROS_INFO("\n");
ROS_INFO("%x ", data[i]);
}
ROS_INFO("\n\n");
}


/**
* @brief Callback that handles a controller status event.
*
* @param wm Pointer to a wiimote_t structure.
* @param attachment Is there an attachment? (1 for yes, 0 for no)
* @param speaker Is the speaker enabled? (1 for yes, 0 for no)
* @param ir Is the IR support enabled? (1 for yes, 0 for no)
* @param led What LEDs are lit.
* @param battery_level Battery level, between 0.0 (0%) and 1.0 (100%).
*
* This occurs when either the controller status changed
* or the controller status was requested explicitly by
* wiiuse_status().
*
* One reason the status can change is if the nunchuk was
* inserted or removed from the expansion port.
*/
void handle_ctrl_status(struct wiimote_t* wm) {
ROS_INFO("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

ROS_INFO("attachment: %i\n", wm->exp.type);
ROS_INFO("speaker: %i\n", WIIUSE_USING_SPEAKER(wm));
ROS_INFO("ir: %i\n", WIIUSE_USING_IR(wm));
ROS_INFO("leds: %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
ROS_INFO("battery: %f %%\n", wm->battery_level);
}


/**
* @brief Callback that handles a disconnection event.
*
* @param wm Pointer to a wiimote_t structure.
*
* This can happen if the POWER button is pressed, or
* if the connection is interrupted.
*/
void handle_disconnect(wiimote* wm) {
ROS_INFO("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}


void test(struct wiimote_t* wm, byte* data, unsigned short len) {
ROS_INFO("test: %i [%x %x %x %x]\n", len, data[0], data[1], data[2], data[3]);
}


int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can 
   * perform any ROS arguments and name remapping that were provided at
   * the command line. For programmatic remappings you can use a
   * different version of init() which takes remappings directly, but
   * for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any
   * other part of the ROS system.
   */
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the
   * ROS system. The first NodeHandle constructed will fully initialize
   * this node, and the last NodeHandle destructed will close down
   * the node.
   */
  ros::NodeHandle n;
  wiimote** wiimotes;
  int found, connected;
  wiimotes = wiiuse_init(MAX_WIIMOTES);
 
found = wiiuse_find(wiimotes,1, 5);
if (!found) {
ROS_INFO("no wiimote found");
return 0;
}

connected = wiiuse_connect(wiimotes,1);
if (connected)
ROS_INFO("Connected to %i wiimotes (of %i found).\n", connected, found);
else {
ROS_INFO("Failed to connect to any wiimote.\n");
return 0;
}



  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

 	if(wiiuse_poll(wiimotes,1)) 
	{
		int i = 0;
		for (; i < 1; ++i) 
		{
			switch (wiimotes[i]->event) {
				case WIIUSE_EVENT:
				/* a generic event occurred */
				handle_event(wiimotes[i]);
				break;

			case WIIUSE_STATUS:
			/* a status event occurred */
			handle_ctrl_status(wiimotes[i]);
			break;

			case WIIUSE_DISCONNECT:
			case WIIUSE_UNEXPECTED_DISCONNECT:
			/* the wiimote disconnected */
			handle_disconnect(wiimotes[i]);
			break;

			case WIIUSE_READ_DATA:
/*
* Data we requested to read was returned.
* Take a look at wiimotes[i]->read_req
* for the data.
*/
			break;

			case WIIUSE_NUNCHUK_INSERTED:
/*
* a nunchuk was inserted
* This is a good place to set any nunchuk specific
* threshold values. By default they are the same
* as the wiimote.
*/
/* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
/* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
			//printf("Nunchuk inserted.\n");
			break;

			case WIIUSE_CLASSIC_CTRL_INSERTED:
			//printf("Classic controller inserted.\n");
			break;

			case WIIUSE_WII_BOARD_CTRL_INSERTED:
			//printf("Balance board controller inserted.\n");
			break;

			case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
/* some expansion was inserted */
			handle_ctrl_status(wiimotes[i]);
			//printf("Guitar Hero 3 controller inserted.\n");
			break;

         		case WIIUSE_MOTION_PLUS_ACTIVATED:
			//printf("Motion+ was activated\n");
             		break;

			case WIIUSE_NUNCHUK_REMOVED:
			case WIIUSE_CLASSIC_CTRL_REMOVED:
			case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
			case WIIUSE_WII_BOARD_CTRL_REMOVED:
                    	case WIIUSE_MOTION_PLUS_REMOVED:
/* some expansion was removed */
			handle_ctrl_status(wiimotes[i]);
			//printf("An expansion was removed.\n");
			break;

			default:
			break;
			}
		}
	}
}

/*
* Disconnect the wiimotes
*/
wiiuse_cleanup(wiimotes, MAX_WIIMOTES);	
			


    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();



    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
 
   chatter_pub.publish(msg);


    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
