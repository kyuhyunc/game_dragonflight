#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QLabel>
#include "dragon.h"

/**
  This class maintains the location, size, and speed of one obstacle.
 */
class Obstacle : public QLabel{
public:
	/**  Default constructor		 
	 *  @param nObstacle QLabel that has pixmap data of obstacle
	 *  @param nx left top location of the tile(x-location)
	 *  @param ny left top location of the tile(y-location)
	 *  @param w width of the tile
	 *  @param h height of the tile
 	 *  @param vx x speed
	 *  @param vy y speed
 	 *  @param d copy of dragon in order to check if an obstacle hits a dragon
	 */
	Obstacle(QLabel *nObstacle, double nx, double ny, double w, double h, int vx, int vy, Dragon *d);
	/**  Default destructor */
	~Obstacle();
	
	/** Set x-location 
 	 *	@param nx x location of left top of the tile
	 */
    void setX( int nx );

	/** Set y-location 
 		 *	@param ny y location of left top of the tile
     */
    void setY( int ny );

	/** Set x-velocity
 	 *	@param vx new x velocity
	 */
    void setVelocityX( int vx );
    
	/** Set y-velocity
 	 *	@param vy new y velocity
	 */
	void setVelocityY( int vy );
    
	/** Get x-location 
     * @return x-location 
     */
	int getX();

	/** Get y-location 
     * @return y-location
     */    
	int getY();
    
	/** Get x-velocity
     * @return x-velocity
     */
	int getVelocityX();

	/** Get y-velocity
     * @return y-velocity
     */    
    int getVelocityY();

	/** Move the tile in proper direction
	 *	@param windowMaxX width of window
	 *	@param windowMaxY height of window
	 *	@return return the result of move about its status\n
	 *			(return 0: obstacle meets wall
	 *			return 1: obstacle hit a dragon
	 *			return 2: red potion hit a dragon
	 *			return 3: white potion hit a dragon)
	 */
    int move(int windowMaxX, int windowMaxY );

	/** hitCheck function which will be called everytime moving is done
	 *	it will compare with the dragon's location and an obstacle's location
	 *	@return return the result of move about its status \n
	 *			(return 0: no hit
	 *			return 1: obstacle hit a dragon
	 *			return 2: red potion hit a dragon
	 *			return 3: white potion hit a dragon)
	 */
	int hitCheck();

private:
    int x;
    int y;
    int width;
    int height;
    int velocityX;
    int velocityY;
	QLabel *obstacle;
	Dragon *dragon;
};

#endif // OBSTACLE_H
