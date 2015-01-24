#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QLCDNumber>
#include <QPixmap>
#include <QTextEdit>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QString>

#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

#include "obstacle.h"
#include "dragon.h"

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

using namespace std;

struct QScore
{
	QString ID;
	double score;
};

class MainWindow : public QWidget {
    Q_OBJECT
    
public:
	/**  Default constructor  \n
	 *	QWidget, which is window, will be the biggest screen that will save layouts and scene. \n
	 *  layouts will have every button, textbox, LCD for score and level etc.
	 */
	explicit MainWindow();
	/**  Default destructor */
	~MainWindow();

	/** Create the top layout that will be contained in Gridlayout 
	 * 	@return QHBoxLayout that has username box and score LCD
	 */
	QHBoxLayout *createTopLayout();
	
	/** Create the right layout that will be contained in Gridlayout 
	 * 	@return QVBoxLayout that has start, pause, quit buttons and game level LCD
	 */
	QVBoxLayout *createRightLayout();

	/** Stop all timers */
	void allTimerStop();

	/** Delete all timers and save NULL as an address*/
	void allTimerDelete();

	/** Will display the window*/
	void show();
	
	/** Creat potions depending on the type number that will be generated randomly
	 *	@param type type of potion, either red or white
	 */
	void obs_potions(int type);

	/** Will display high scores in the right box*/
	void scoreDisplay();

	/** Will export scores in the box to score.txt file*/
	void exportScore();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
	QPixmap *backGround;
	QGraphicsPixmapItem* pixmapItem;

    QWidget *window;

	// layouts
	QGridLayout *layout; // main layout    
    QHBoxLayout *topLayout; // top input text board layout
    QVBoxLayout *rightLayout; // top input text board layout
    
	// buttons
	QPushButton *reStart;	
	QPushButton *pause_resumeGame;	
	QPushButton *exitGame;	
	
	// text boxes
	QLCDNumber *score;
	QLCDNumber *QgameLevel;
	int gameLevel;
	double scoreNum; // for score
	QTextEdit *errMsg; // get error message
	QLabel *instruction1;
	QLabel *instruction2;
	QLineEdit *usrName;

	// labels for layouts
	QLabel *scoreLabel;
	QLabel *usrNameLabel;
	QLabel *gameLevelLabel;
	QLabel *scoreListLabel;
	
	// vector for saving obstacles
	QVector<Obstacle*> obstacles;
	QVector<QLabel*> Qhearts;
	int num_hearts;
	QVector<QLabel*> magic_potions;
	Dragon *dragon;

	QTimer *mainTimer; // main timer
	QTimer *timer1; // for rock
	QTimer *timer2; // for arrow
	QTimer *timer3; // for fireball
	//QTimer *timer4; // for red potion
	//QTimer *timer5; // for white potion


	QStandardItemModel *model; // for saving solList
	QTableView *scoreList; // QTableView for score display
	//ifstream in_score; // output file 
	QFile scoreFile; // output file 
	//ofstream out_score; // output file 
	QVector<QScore> QScores; // save scores from score.txt file
		 
protected:

public slots:
	/** Start the game by starting timers and creating a dragon etc */
	void startGame();
	/** Pause or resume the game by stoping or starting timers */
	void PRGame();
	/** Count score everytime the main timer times out */
	void cntScore();
	/** Creat rock obstacle everytime timer1 times out */
	void obs_rock();
	/** Creat arrow obstacle everytime timer2 times out */
	void obs_arrow();
	/** Creat fireball obstacle everytime timer3 times out */
	void obs_fireball();
	/** Cast magic if a dragon has white potion left */
	void useMagic();
};

#endif // MAINWINDOW_H
