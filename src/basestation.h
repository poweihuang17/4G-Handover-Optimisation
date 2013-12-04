/* Header that contains the class definition of the basestation class
 ********************************************************************
 * The basestation class is used to represent a basestaton that will
 * have other basestations near by and a mobile moving around them.
 */
#include <stdio.h>
#include <math.h>
class basestation {
private:
    /* Private Variables
     ****************************
     * int id: Unique interger values that indentifies this instance of the class.
     * int x_co: Integer value that denotes where of the x-axis this instance of
     *           the class is found. 
     * int y_co: Integer value that denotes where of the y-axis this instance of
     *           the class is found. 
     * double tx: Double value that denoted the signal strength being transmitted
     *            from this instance of the class.
     * double f:  Double value that denoted the frequency the transmitter transmits
     *            at in MHz.
	 * double hb: Double value that denoted the height of the base station.
     */
	int id;
    int x_co;
    int y_co;
    double f;
    double hb;
public:
    basestation();
    basestation(int idNum, int x, int y, double freq, double hBase);
    void print();
    int getID();
    int getX();
    int getY();
    double getProp(double d, double hm);
};