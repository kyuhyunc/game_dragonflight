
#include "mainwindow.h"
	
	/** @mainpage CSCI 102 Homework #5
	 *  @section purpose Purpose/Overview
	 *	  PA5 make my own game with using qt - GUI implementation assignment
	 */

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	
	MainWindow w;

	w.show();	

	return a.exec();
}
 