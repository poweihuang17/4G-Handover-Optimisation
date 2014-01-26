// #include "handover_management.h"
// #include <stdio.h>
// #include <math.h>
// #include "mobile.h"
// #include "basestation.h"
// #include "event_definitions.h"
#include "globals.h"

// basestation* bStations[9];
// mobile* mobiles[1];	

/* Constructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 **************************** 
 * Description: Basic class constructor that create an instance of handover_management
 */
handover_management::handover_management(scheduler* gs) : event_handler(gs) {
	bStations[0] = new basestation(gs,0,0,0,1500,60);
	bStations[1] = new basestation(gs,1,750,0,1500,60);
	bStations[2] = new basestation(gs,2,1500,0,1500,60);
	bStations[3] = new basestation(gs,3,0,750,1500,60);
	bStations[4] = new basestation(gs,4,750,750,1500,60);
	bStations[5] = new basestation(gs,5,1500,750,1500,60);
	bStations[6] = new basestation(gs,6,0,1500,1500,60);
	bStations[7] = new basestation(gs,7,750,1500,1500,60);
	bStations[8] = new basestation(gs,8,1500,1500,1500,60);
	prop[0] = 0.0;
	prop[1] = 0.0;
	prop[2] = 0.0;
	prop[3] = 0.0;
	prop[4] = 0.0;
	prop[5] = 0.0;
	prop[6] = 0.0;
	prop[7] = 0.0;
	prop[8] = 0.0;
	mobiles[0] = new mobile(gs,1,750,750,4,1);
	threshold = -125.0;
	handoverTime = 0.25;

	send_delay(new event(MOVE,mobiles[0]),0.0);
}
/* Method
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in:
 * const event* received
 ****************************
 * Description: Class hanlder that takes in a event and does the
 * required action depending on the event that was received.
 */
handover_management::~handover_management() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}
/* Destructor
 ****************************
 * Return Type: N/A 
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Class destrcutor that removes an instance of this class
 * from the schedular and any messages still waiting to be passed.
 */
void handover_management::handler(const event* received)
{
	switch(received->label) {
		case PROP:
			propSendPacket* recPacket;
			recPacket = reinterpret_cast<propSendPacket*> (received->getAttachment());
    		prop[recPacket->id] = -(recPacket->prop);
    		printf("id:%d Rx:%f dB\n",recPacket->id,prop[recPacket->id]);
   			delete recPacket;
   			break;
   		case POLL:
   			propRequestPacket* sendPacket0;
   			propRequestPacket* sendPacket1;
   			propRequestPacket* sendPacket2;
   			propRequestPacket* sendPacket3;
   			propRequestPacket* sendPacket4;
			propRequestPacket* sendPacket5;
   			propRequestPacket* sendPacket6;
   			propRequestPacket* sendPacket7;
   			propRequestPacket* sendPacket8;
   			double dist;
   			double height;
   			height = mobiles[0]->getHeight();

   			dist = sqrt(pow((bStations[0]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[0]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket0 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[1]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[1]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket1 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[2]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[2]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket2 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[3]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[3]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket3 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[4]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[4]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket4 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[5]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[5]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket5 = new propRequestPacket(dist,height);
			dist = sqrt(pow((bStations[6]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[6]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket6 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[7]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[7]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket7 = new propRequestPacket(dist,height);
   			dist = sqrt(pow((bStations[8]->getX()-mobiles[0]->getX()),2.0) + pow((bStations[8]->getY()-mobiles[0]->getY()),2.0));
   			sendPacket8 = new propRequestPacket(dist,height);

   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket0),bStations[0]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket1),bStations[1]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket2),bStations[2]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket3),bStations[3]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket4),bStations[4]),1.0);
			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket5),bStations[5]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket6),bStations[6]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket7),bStations[7]),1.0);
   			send_delay(new event(PROP,reinterpret_cast<payloadType<class T>*>(sendPacket8),bStations[8]),1.0);
		case PRINT:
			//send_now(new event(PRINT,mobiles[0]));
			//mobiles[0]->print();
			break;
		default:
			// program should not reach here
			break;
	} // end switch statement
}

/* Method
 ****************************
 * Return Type: int
 ****************************
 * Parameters Passed in: int connected
 ****************************
 * Description: Method that analysis the values it has and based on those values makes
 * 				a decision on what basestation the mobile should be connected to and
 *				if the basestation is different then the mobile is connected to the new
 *				"best" basestation.
 */
void handover_management::makeDecision() {
	// double bestProp = 50000.0;
	// double dist = 0.0;
	// double prop = 0.0;
	// double h = mobiles[0]->getHeight();
	// int connected = mobiles[0]->getConnectedTo();
	// int bestID = mobiles[0]->getConnectedTo();
	// for(int i=0; i<(sizeof(bStations)/sizeof(*bStations)); i++) {
	// 	dist = sqrt((abs((bStations[i]->getX()-mobiles[0]->getX()))^2) + (abs((bStations[i]->getY()-mobiles[0]->getY()))^2));
	// 	printf("%d: dist: %f\n",i,dist);
	// 	prop = bStations[i]->getProp(dist,h);
	// 	printf("prop: %f\n",prop);
	// 	if(prop < bestProp) {
	// 		bestProp = prop;
	// 		bestID = bStations[i]->getID();
	// 	}
	// }
	// printf("bestProp: %f\n",bestProp);
	// printf("bestID: %d\n",bestID);
	// if(connected != bestID) {
 //    	mobiles[0]->switchBasestation(bestID);
	// }
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: N/A
 ****************************
 * Description: Method that prints out all the information about
 * the mobiles and basestaions being used in the simulation.
 */
void handover_management::output() {
	mobiles[0]->print();
	for(int i=0; i<9; i++) {
		bStations[i]->print();
	}
}
/* Method
 ****************************
 * Return Type: void
 ****************************
 * Parameters Passed in: int index
 ****************************
 * Description: Method that calls the move method for a specified mobile.
 */
void handover_management::moveMobile(int index) {
	send_now(new event(MOVE, mobiles[0]));
}

// basestation* getBasestation(int id) {
// 	return bStations[id];
// }

// mobile* getMobile(int id) {
// 	return mobiles[id];
// }
