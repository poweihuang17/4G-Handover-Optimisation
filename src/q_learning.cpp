#include "actions.h"
#include "prop.h"
#include "event_definitions.h"
#include <random>
#include <fstream>

q_learning::q_learning(scheduler* gs, int TTT, int hys) : event_handler(gs) {
	int startState = (TTT*21)+hys;
	if(function == 1) { //for creating policy
		int qDrop = 0;
		int qPing = 0;
		std::ifstream qd ("qDrop.txt");
		std::ifstream qp ("qPing.txt");

		if(qd.is_open() && qp.is_open()) {
			for(int i=0; i<NUMSTATES; i++) {
				for(int j=0; j<NUMSTATES; j++) {
					qd>>qDrop;
					qp>>qPing;
					Qdrop[i][j] = qDrop; //read Q in
					Qping[i][j] = qPing;
				}
			}
		}

    	qd.close();
    	qp.close();

		current_state = startState;
		action = 0;
		next_state = 0;
		firstPass = true;

		send_delay(new event(LEARN),60);
	} else if(function == 2) { //for using policy
		std::ifstream pDrop ("policyDrop.txt");
		std::ifstream pPing ("policyPing.txt");

		if(pDrop.is_open() && pPing.is_open()) {
			for(int i=0; i<NUMSTATES; i++) {
				pDrop >> policy_drop[i];
				pPing >> policy_ping[i];
			}
		}

		pDrop.close();
		pPing.close();

		current_state = startState;
	}
}

q_learning::~q_learning() {
	globalScheduler->remove_from(this);
	globalScheduler->remove_to(this);
}

void q_learning::handler(const event* received)
{

	switch(received->label) {
		case LEARN:
			printf("HERE\n");
			learn();
			break;
		case POLICYDROP:
			//change state depending on policy
			changeState(0);
			break;
		case POLICYPING:
			changeState(1);
			break;
		// case DROP:
		// 	learn(0);
		// 	break;
		// case PING:
		// 	learn(1);
		// 	break;
		default:
			// program should not reach here
			break;
	} // end switch statement
	
}

void q_learning::learn() {
	if(!firstPass) {
		double Q = 0;
		double value = 0;

		Q = getPingQ(current_state,action);
		value = Q + ALPHA * (getRewardDrop() + GAMMA * maxQ(current_state,0) - Q);
    	updateQ(current_state, action, value, 0);

		Q = getPingQ(current_state,action);
		value = Q + ALPHA * (getRewardPing() + GAMMA * maxQ(current_state,1) - Q);
    	updateQ(current_state, action, value, 1);

    	current_state = next_state;
	} else {
		firstPass = false;
	}

	do {
		action = *(actions[current_state]+rand()%LENGTH); //choose next state
		printf("Action: %d\n", action);
	} while(action == -1);
	next_state = action;

	printf("Next State: %d\n", next_state);

	//change TTT and hys
	changeTTThys();

	send_delay(new event(LEARN),60);
}

double q_learning::maxQ(int state, int type) {
	int* nextstates = actions[state];
	double maxq = -999999;
	double q = 0.0;
	for(int i=0; i<LENGTH; i++) {
		if(*(nextstates+i) != -1) {
			if(type == 0) {
            	q = Qdrop[state][*(nextstates+i)];
        	} else {
        		q = Qping[state][*(nextstates+i)];
        	}
            if (q > maxq)
                maxq = q;
		}
	}
	return maxq;
}

double q_learning::getDropQ(int state, int action) {
	return Qdrop[state][action];
}

double q_learning::getPingQ(int state, int action) {
	return Qping[state][action];
}

void q_learning::updateQ(int state, int action, double q, int type) {
	if(type == 0) {
		Qdrop[state][action] = q;
	} else {
		Qping[state][action] = q;
	}
}

double q_learning::getRewardDrop() {
	double reward = 0.0;
	reward = -rewardDrop;
	rewardDrop = 0;
	rewardHandover = 0;
	return reward;
}

double q_learning::getRewardPing() {
	double reward = 0.0;
	reward = -rewardPing;
	rewardHandover = 0;
	rewardPing = 0;
	return reward;
}

void q_learning::changeTTThys() {
	if(next_state >= 0 && next_state < 21) {
		TTT = TTTArray[0];
		hys = hysArray[next_state-0];
	} else if(next_state >= 21 && next_state < 42) {
		TTT = TTTArray[1];
		hys = hysArray[next_state-21];
	} else if(next_state >= 42 && next_state < 63) {
		TTT = TTTArray[2];
		hys = hysArray[next_state-42];
	} else if(next_state >= 63 && next_state < 84) {
		TTT = TTTArray[3];
		hys = hysArray[next_state-63];
	} else if(next_state >= 84 && next_state < 105) {
		TTT = TTTArray[4];
		hys = hysArray[next_state-84];
	} else if(next_state >= 105 && next_state < 126) {
		TTT = TTTArray[5];
		hys = hysArray[next_state-105];
	} else if(next_state >= 126 && next_state < 147) {
		TTT = TTTArray[6];
		hys = hysArray[next_state-126];
	} else if(next_state >= 147 && next_state < 168) {
		TTT = TTTArray[7];
		hys = hysArray[next_state-147];
	} else if(next_state >= 168 && next_state < 189) {
		TTT = TTTArray[8];
		hys = hysArray[next_state-168];
	} else if(next_state >= 189 && next_state < 210) {
		TTT = TTTArray[9];
		hys = hysArray[next_state-189];
	} else if(next_state >= 210 && next_state < 231) {
		TTT = TTTArray[10];
		hys = hysArray[next_state-210];
	} else if(next_state >= 231 && next_state < 252) {
		TTT = TTTArray[11];
		hys = hysArray[next_state-231];
	} else if(next_state >= 252 && next_state < 273) {
		TTT = TTTArray[12];
		hys = hysArray[next_state-252];
	} else if(next_state >= 273 && next_state < 294) {
		TTT = TTTArray[13];
		hys = hysArray[next_state-273];
	} else if(next_state >= 294 && next_state < 315) {
		TTT = TTTArray[14];
		hys = hysArray[next_state-294];
	} else if(next_state >= 315 && next_state < 336) {
		TTT = TTTArray[15];
		hys = hysArray[next_state-315];
	}
	printf("New: TTT: %f hys: %f\n", TTT,hys);
}

void q_learning::changeState(int type) {
	if(type == 0) {
		next_state = policy_drop[current_state];
	} else {
		next_state = policy_ping[current_state];
	}
	changeTTThys();
	current_state = next_state;
}

void q_learning::print() {
	// for(int i=0; i<NUMSTATES; i++) {
	// 	for(int j=0; j<NUMSTATES; j++) {
	// 		printf("%f ", Q[i][j]);
	// 	}
	// 	printf("\n");
	// }
	printPolicy();

	//print Q to file
	std::ofstream qd ("qDrop.txt");
	std::ofstream qp ("qPing.txt");
	if (qd.is_open() && qp.is_open()) {
		for(int i=0; i<NUMSTATES; i++) {
			for(int j=0; j<NUMSTATES; j++) {
    			qd << Qdrop[i][j] << "\n";
    			qp << Qping[i][j] << "\n";
  			}
  		}
  	}

  	qd.close();
  	qp.close();
}

int q_learning::policy(int current, int type) {
    double maxValue = -99999;
    int maxNext = -1; // For testing cause not all Q's have values yet
    for (int i = 0; i < LENGTH; i++) {
        int nextState = *(actions[current]+i);

        if(nextState != -1) {
        	double value = 0;
        	if(type == 0) {
          		value = getDropQ(current,nextState);
          	} else {
          		value = getPingQ(current,nextState);
          	}
 
           	if (value > maxValue) {
               	maxValue = value;
           	    maxNext = nextState;
           	}
       	}
    }
    return maxNext;
}

void q_learning::printPolicy() {
	std::ofstream pDrop ("policyDrop.txt");
	std::ofstream pPing ("policyPing.txt");

	if(pDrop.is_open()) {
    	for (int i=0; i < NUMSTATES; i++) {
    	    int current = i;
    	    int next =  policy(current,0);
    	    pDrop << next << "\n";
    	    printf("From %d Next %d\n",current,next);
    	}    
    } 

    if(pPing.is_open()) {
    	for (int i=0; i < NUMSTATES; i++) {
    	    int current = i;
    	    int next =  policy(current,1);
    	    pPing << next << "\n";
    	    printf("From %d Next %d\n",current,next);
    	}    
    } 
    pDrop.close();
    pPing.close();      
}
