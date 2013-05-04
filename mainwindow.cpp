#include "mainwindow.h"

QBrush redBrush(Qt::red);
QBrush blueBrush(Qt::blue);
QBrush blkBrush(Qt::black);
QBrush greenBrush(Qt::green);
QBrush whiteBrush(Qt::white);
	
MainWindow::MainWindow()  {
	//Biggest layout that will include every other layout and widget	
	layout = new QGridLayout;
	//We need a scene and a view to do graphics in QT
	scene = new QGraphicsScene();
	view = new QGraphicsView( scene );
	scoreNum = 0;	
	mainTimer = NULL;
	dragon = NULL;
	gameLevel = 0;

	//This sets the size of the window and gives it a title.
	view->setFixedSize( WINDOW_MAX_X*2.5, WINDOW_MAX_Y*2.5 );
	
	backGround = new QPixmap("./pics/back_ground.jpg");
	
	pixmapItem = scene->addPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	//view->setScene(scene);

	// topLayout for text input board	
	topLayout = createTopLayout();
	rightLayout = createRightLayout();

	errMsg = new QTextEdit;
	errMsg->setMinimumHeight(30);
	errMsg->setReadOnly(true);	

	// placing layouts and widgets in the main layout by using gridlayout
	layout->addLayout(topLayout,1,0);
	layout->addLayout(rightLayout,1,1,3,1);
	layout->addWidget(view,2,0);
	layout->addWidget(errMsg,3,0);

	// window that will get layout that has every thing
	window = new QWidget;
	window->setWindowTitle("Dragon Flight");

	// setting layout in the main window
	// window > layout(Gridlayout) = other layouts + widgets
	window->setLayout(layout);		

	// connecting buttons
	connect(reStart, SIGNAL(clicked()), this, SLOT(startGame()));

	connect(pause_resumeGame, SIGNAL(clicked()), this, SLOT(PRGame()));
	// connecting quit button to terminate the program
	connect(exitGame, SIGNAL(clicked()), qApp, SLOT(quit()));	

	//setFocusPolicy(Qt::StrongFocus);

	scoreFile.setFileName("score.txt");
	if(!scoreFile.open(QIODevice::ReadWrite | QIODevice::Text))
		std::cout << "Error occurs during reading score file" << std::endl;

	scoreDisplay();

}

QHBoxLayout *MainWindow::createTopLayout()
{
	QHBoxLayout *topLayout = new QHBoxLayout;

	usrName = new QLineEdit;
	score = new QLCDNumber(10);
	// label for the box

	usrName->setMaxLength(4);
	usrName->setFixedSize(230,30);
	score->setFixedSize(230,40);
		
	usrNameLabel = new QLabel(tr("User Name"));
	//usrNameLabel->setMaximumWidth(150);
	scoreLabel = new QLabel(tr("Score"));
	scoreLabel->setMaximumWidth(200);

	topLayout->addWidget(usrNameLabel);
	topLayout->addWidget(usrName);
	topLayout->addWidget(scoreLabel);
	topLayout->addWidget(score);	

	return topLayout;
}
 
QVBoxLayout *MainWindow::createRightLayout() 
{	
	// top layout for three inputs, size, moves and seed value.
	QVBoxLayout *rightLayout = new QVBoxLayout;
	
	reStart = new QPushButton("Start");
	pause_resumeGame = new QPushButton("Pause/Resume");
	exitGame = new QPushButton("Quit");	
	//QLabel *blank = new QLabel(tr(" "));
	scoreListLabel = new QLabel(tr("High scores"));
	scoreList = new QTableView;
	instruction1 = new QLabel;
	instruction2 = new QLabel;
	QgameLevel = new QLCDNumber(2);
	gameLevelLabel = new QLabel(tr("	Game Level"));


	reStart->setMaximumWidth(150);
	pause_resumeGame->setMaximumWidth(150);
	exitGame->setMaximumWidth(150);
	scoreList->setMaximumWidth(150);
	scoreList->setMaximumHeight(276);
	/*scoreList->resizeRowsToContents(); // Adjust the row height
	scoreList->resizeColumnsToContents();
	scoreList->setColumnWidth(0,60);
	scoreList->setColumnWidth(1,60);*/
	scoreList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scoreList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scoreList->setDisabled(1);
//	scoreList->verticalHeader()->hide();
	
	instruction2->setText(tr("Arrow key: moving\nSpace: cast magic\n\nRed potion: +1 heart\nWhite potion: magic\nLeft shift key: pause"));

	instruction2->setFixedSize(150,100);

	QgameLevel->setFixedSize(150,100);
	

	rightLayout->addWidget(reStart);
	rightLayout->addWidget(pause_resumeGame);
	rightLayout->addWidget(exitGame);
	rightLayout->addWidget(scoreListLabel);
	rightLayout->addWidget(scoreList);
//	rightLayout->addWidget(instruction1);
	rightLayout->addWidget(instruction2);	
	//for(int i=0;i<14;i++)
	//	rightLayout->addWidget(blank);
	rightLayout->addWidget(QgameLevel);
	rightLayout->addWidget(gameLevelLabel);
	
	return rightLayout;
}

void MainWindow::startGame()
{	
	if(usrName->text() == "")
		errMsg->setPlainText("Should enter user name");
	else if(mainTimer == NULL){
		errMsg->setPlainText("Game starts");
		usrName->setDisabled(1);
		//std::cout << "Start Game" << std::endl;
		scoreNum = 0;
		gameLevel = 0;
		num_hearts = 2;

		QgameLevel->display(gameLevel);
		score->display(scoreNum);
		
		// resetting hearts
		while(Qhearts.size()){
			delete Qhearts.last();
			Qhearts.pop_back();
		}

		// reseting magic potions
		while(magic_potions.size()){
			delete magic_potions.last();
			magic_potions.pop_back();
		}

		if(mainTimer != NULL){

		}

		//std::cout << "obstacles number: " << obstacles.size() << std::endl;
		int size = obstacles.size();
		for(int i=0;i<size;i++){
			//std::cout << "i: " << i << std::endl;
			delete obstacles[i];	
			//obstacles.remove(i);	
		}

		obstacles.clear();
		//std::cout << "obstacles number: " << obstacles.size() << std::endl;

		if(dragon != NULL)	delete dragon;

		double dragonSize = 80;
		/*QPixmap *d = new QPixmap("./pics/dragon.png");
		QPixmap d_ = d->scaled(dragonSize,dragonSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);*/
		QPixmap d_("./pics/dragon.png");

		QLabel *qtemp = new QLabel;
		qtemp->move(WINDOW_MAX_X,WINDOW_MAX_Y);
		qtemp->setFixedSize(dragonSize,dragonSize);
	//	qtemp->setPixmap(d_);
		qtemp->setPixmap(d_.scaled(dragonSize,dragonSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		dragon = new Dragon(qtemp,(double)WINDOW_MAX_X,(double)WINDOW_MAX_Y,dragonSize,dragonSize);

		scene->addWidget(qtemp);

		QPixmap heart_("./pics/heart.png");
		int heartSize = 25;
		for(int i=0;i<num_hearts;i++){
			QLabel *heart = new QLabel;
			heart->move(10+30*i,10);
			heart->setFixedSize(heartSize,heartSize);
			heart->setPixmap(heart_.scaled(heartSize,heartSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
			Qhearts.push_back(heart);
			heart->setAttribute(Qt::WA_TranslucentBackground);

			scene->addWidget(heart);
		}

		mainTimer = new QTimer(this);
		// setting a timer
		timer1 = new QTimer(this);
		timer2 = new QTimer(this);
		timer3 = new QTimer(this);
		//timer4 = new QTimer(this);
		//timer5 = new QTimer(this);

		mainTimer->setInterval(15);
		timer1->setInterval(600);
		timer2->setInterval(2000);
		timer3->setInterval(3000);

		mainTimer->start();

		// mainTimer
		connect(mainTimer, SIGNAL(timeout()), this, SLOT(cntScore()));

		// rock
		connect(timer1, SIGNAL(timeout()), this, SLOT(obs_rock()));
		connect(timer2, SIGNAL(timeout()), this, SLOT(obs_arrow()));
		connect(timer3, SIGNAL(timeout()), this, SLOT(obs_fireball()));

		// connect dragon
		connect(dragon, SIGNAL(myPressSignal()), this, SLOT(useMagic()));
		connect(dragon, SIGNAL(myPressSignal2()), this, SLOT(PRGame()));
		
		//dragon->setFocus();
		//scene->setFocus();
		
	}
	else{
		//dragon->keyReset();
		errMsg->setPlainText("Game is already running. Cannot restart the game");
	}
	view->setFocus();
}

void MainWindow::show() 
{
	window->show();
}

void MainWindow::PRGame()
{
	if(dragon != NULL && num_hearts != 0){
		//std::cout << "Pause or Resume Game" << std::endl;
		if (timer1->isActive() == true){
			disconnect(dragon, SIGNAL(myPressSignal()), this, SLOT(useMagic()));
			errMsg->setPlainText("Pause");
			dragon->keyReset();
			mainTimer->stop();
			timer1->stop(); 
			timer2->stop();
			timer3->stop();
			//timer4->stop();
			//timer5->stop();
			view->setFocus();
		}
		else{
			connect(dragon, SIGNAL(myPressSignal()), this, SLOT(useMagic()));
			//connect(dragon, SIGNAL(myPressSignal2()), this, SLOT(PRGame()));
			errMsg->setPlainText("Resume");
			//dragon->setFocus();
			dragon->keyReset();
			mainTimer->start();
			timer1->start(); 
			timer2->start(); 
			timer3->start(); 
			//timer4->start(); 
			//timer5->start();
			view->setFocus();
		}
	}
	else
		errMsg->setPlainText("Game is not even started");
}
void MainWindow::cntScore()
{
	scoreNum ++;
	score->display(scoreNum);
	//dragon->setFocus();
	dragon->move(WINDOW_MAX_X,WINDOW_MAX_Y);

	// as scoreNum goes higer set interval again

	// after 2sec, start rock
	if(scoreNum == 100){
		timer1->start();
		errMsg->setPlainText("Lv1: Rocks");
		gameLevel = 1;
	}
	// after 15sec, start arrow
	if(scoreNum == 500){
		timer2->start();
		errMsg->setPlainText("Lv2: Fast arrow");
		gameLevel = 2;

		backGround->load("./pics/back_ground2.jpg");
		pixmapItem->setPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}
	// after 30sec, start fireball
	if(scoreNum == 1000){
		timer3->start();
		errMsg->setPlainText("Lv3: Big firball");
		gameLevel = 3;

		backGround->load("./pics/back_ground3.jpg");
		pixmapItem->setPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}
	if(scoreNum == 1500){
		timer1->setInterval(500);
		timer2->setInterval(1800);
		timer3->setInterval(2800);
		errMsg->setPlainText("Lv4: More obstacles are coming");
		gameLevel = 4;

		backGround->load("./pics/back_ground4.jpg");
		pixmapItem->setPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}
	if(scoreNum == 2000){	
		timer1->setInterval(400);
		timer2->setInterval(1500);
		timer3->setInterval(2500);
		errMsg->setPlainText("Lv5: More obstacles are coming and faster");
		gameLevel = 5;

		backGround->load("./pics/back_ground5.jpg");
		pixmapItem->setPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}
	if(scoreNum == 2500){	
		timer1->setInterval(300);
		timer2->setInterval(1300);
		timer3->setInterval(2300);
		errMsg->setPlainText("Lv6: Hell");
		gameLevel = 6;

		backGround->load("./pics/back_ground6.jpg");
		pixmapItem->setPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}

	QgameLevel->display(gameLevel);

	srand(scoreNum);
	int potionNumber = rand() % 10;

	// potions
	if((int)scoreNum % 1000 == 0)	obs_potions(potionNumber);
	
	// move every obstacles in the vector
	int size = obstacles.size();
	//std::cout << "obstacles size: " << obstacles.size() << std::endl;
	for(int i=0;i<size;i++){
	//for(int i=0;i<obstacles.size();i++){
		int flag = obstacles[i]->move(WINDOW_MAX_X, WINDOW_MAX_Y);
		if(flag == 0){ // when obstacles go to the end of the screen
			//std::cout << "before " << std::endl;
			delete obstacles[i];
			obstacles[i] = NULL;
			//std::cout << "after1 " << std::endl;
			//obstacles.remove(i);
			//std::cout << "after2 " << std::endl;
		}
		else if(flag == 1){ // when one of the obstacles hit the dragon
			errMsg->setPlainText("Ouch!!!");
			//std::cout << "hithithit!!" << std::endl;
			// 1. delete obstacle
			delete obstacles[i];
			obstacles[i] = NULL;
			//obstacles.remove(i);
			
			// 2. life --;
			delete Qhearts.last();
			//Qhearts.last()->setPixmap(NULL);
			Qhearts.pop_back();

			num_hearts = Qhearts.size();

			//std::cout << "hearts: " << num_hearts << std::endl;
			if(num_hearts == 0){
				errMsg->setPlainText("Game Over");
				allTimerStop();
				allTimerDelete();

				usrName->setDisabled(0);

				exportScore();
				scoreDisplay();
			}
		}
		else if(flag == 2){ // red_potion
			if(num_hearts < 5){
				errMsg->setPlainText("+1 heart");
				QPixmap heart_("./pics/heart.png");
				int heartSize = 25;
				QLabel *heart = new QLabel;
				heart->move(10+30*num_hearts,10);
				heart->setFixedSize(heartSize,heartSize);
				heart->setPixmap(heart_.scaled(heartSize,heartSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
				heart->setAttribute(Qt::WA_TranslucentBackground);
				
				Qhearts.push_back(heart);
				num_hearts = Qhearts.size();

				scene->addWidget(heart);
			}
			else
				errMsg->setPlainText("Life is alreay the maxmimum: (5)");
			
			delete obstacles[i];	
			obstacles[i] = NULL;				
			//obstacles.remove(i);
		}
		else if(flag == 3){ // magic_potion
			if(magic_potions.size() < 3){
				errMsg->setPlainText("+1 magic potion");
				QPixmap potion_("./pics/white_potion.png");
				int potionSize = 35;
				QLabel *potion = new QLabel;
				potion->move(5+30*(magic_potions.size()),10+potionSize);
				potion->setFixedSize(potionSize,potionSize);
				potion->setPixmap(potion_.scaled(potionSize,potionSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
				potion->setAttribute(Qt::WA_TranslucentBackground);

				magic_potions.push_back(potion);

				scene->addWidget(potion);
			}
			else
				errMsg->setPlainText("Magic potion is alreay the maximum: (3)");
			delete obstacles[i];	
			obstacles[i] = NULL;				
			//obstacles.remove(i);
	
		}
	}

	vector<int> temp;

	for(int i=0;i<obstacles.size();i++){
		if(obstacles[i] == NULL)
			temp.push_back(i);
	}

	int sizet = temp.size();
	for(int i=0;i<sizet;i++){
		obstacles.remove(temp.back());
		temp.pop_back();
	}

}

void MainWindow::useMagic()
{
	if(magic_potions.size() > 0){
		errMsg->setPlainText("Cast the magic! Will eliminate every obstacle");
		int size = obstacles.size();
		for(int i=0;i<size;i++){
			//std::cout << "i: " << i << std::endl;
			delete obstacles[i];	
			//obstacles.remove(i);	
		}
		obstacles.clear();

		delete magic_potions.last();
		magic_potions.pop_back();
	}
	else if(magic_potions.size() == 0)
		errMsg->setPlainText("There is no magic potion");
}

void MainWindow::obs_potions(int type)
{
	QPixmap red_potion_("./pics/red_potion.png");
	QPixmap white_potion_("./pics/white_potion.png");
	QLabel *potion = new QLabel;
	Obstacle *item;

	int RpotionSize = 77;
	int WpotionSize = 78;
	int vx = 0;
	int vy = 2;
	int temp;

	srand(scoreNum);
	do{
		temp = rand() % 600;
		if(temp < 600 && temp > 100)	break;
	}while(1);

	if(type == 2 || type == 5 || type == 8){ // magic potion
		potion->move(temp, 0);
		potion->setFixedSize(WpotionSize,WpotionSize);
		potion->setPixmap(white_potion_.scaled(WpotionSize,WpotionSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(potion,temp,0,WpotionSize,WpotionSize,vx,vy,dragon);
	}
	else{ // red_potion
		potion->move(temp, 0);
		potion->setFixedSize(RpotionSize,RpotionSize);
		potion->setPixmap(red_potion_.scaled(RpotionSize,RpotionSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(potion,temp,0,RpotionSize,RpotionSize,vx,vy,dragon);
	}
	
	scene->addWidget(potion);

	obstacles.push_back(item);			
}

void MainWindow::obs_rock()
{
	//std::cout << "rock" << std::endl;
	//QPixmap *rock = new QPixmap("./pics/obstacle1_rock.png");
	QPixmap rock_("./pics/obstacle1_rock.png");

	srand(scoreNum);
	int size = 40;
	int vx = 1+rand()%1;
	int vy = 1+rand()%1;

	if(gameLevel == 6){
		vx+=2; vy+=2;
	}
	else if(gameLevel == 5){
		vx++; vy++;
	}

	int temp;
	int direction = rand() % 4;
	int direction2 = rand() % 2;

	do{
		temp = rand() % 622 - size;
		if(temp < 622-size && temp > 0)	break;
	}while(1);

	QLabel *qtemp;
	Obstacle *item;

	//QPixmap rock_ = rock->scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

	if(direction == 0){
		if(direction2 == 0) vx = -vx;
		//std::cout << "rock1" << std::endl;
		qtemp = new QLabel;
		qtemp->move(temp, 0);
		qtemp->setFixedSize(size,size);
		qtemp->setPixmap(rock_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		//qtemp->setPixmap(rock_);
		item = new Obstacle(qtemp,temp,0,size,size,vx,vy,dragon);
	}
	else if(direction == 1){
		if(direction2 == 0) vy = -vy;
		//std::cout << "rock2" << std::endl;
		qtemp = new QLabel;
		qtemp->move(0,temp);
		qtemp->setFixedSize(size,size);
		qtemp->setPixmap(rock_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		//qtemp->setPixmap(rock_);
		item = new Obstacle(qtemp,0,temp,size,size,vx,vy,dragon);
	}
	else if(direction == 2){
		vy = -vy;
		if(direction2 == 0) vx = -vx;
		//std::cout << "rock3" << std::endl;
		qtemp = new QLabel;
		qtemp->move(temp,WINDOW_MAX_X*2.49-size);
		qtemp->setFixedSize(size,size);
		qtemp->setPixmap(rock_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		//qtemp->setPixmap(rock_);
		item = new Obstacle(qtemp,temp,WINDOW_MAX_X*2.49-size,size,size,vx,vy,dragon);
	}
	else{
		vx = -vx;
		if(direction2 == 0) vy = -vy;
		//std::cout << "rock4" << std::endl;
		qtemp = new QLabel;
		qtemp->move(WINDOW_MAX_X*2.49-size,temp);
		qtemp->setFixedSize(size,size);
		qtemp->setPixmap(rock_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		//qtemp->setPixmap(rock_);
		item = new Obstacle(qtemp,WINDOW_MAX_X*2.49-size,temp,size,size,vx,vy,dragon);
	}
	
	//scene->addPixmap(*(qtemp->pixmap()));
	scene->addWidget(qtemp);

	obstacles.push_back(item);
	//std::cout << "size of obstacle(vector): " << obstacles.size() << std::endl;
}

void MainWindow::obs_arrow()
{
	//std::cout << "obs_arrow" << std::endl;

	srand(scoreNum+1);
	int width = 80;
	int height = 30;
	int vx = 2+rand()%3;
	int vy = 2+rand()%3;

	if(gameLevel == 6){
		vx+=2; vy+=2;
	}
	else if(gameLevel == 5){
		vx++; vy++;
	}
	
	int temp;
	int direction = rand() % 4;
	int direction2 = rand() % 2;

	do{
		temp = rand() % 622 - width;
		//if(temp < 622-width && temp > 0)	break;
		if(temp < 550 && temp > 100)	break;
	}while(1);

	QLabel *qtemp;
	Obstacle *item;
	//QPixmap *arrow;
	QPixmap arrow_; 
		
	if(direction == 0){
		//arrow = new QPixmap("./pics/obstacle2_arrow_0.png");
		arrow_.load("./pics/obstacle2_arrow_0.png");
		//arrow_ = arrow->scaled(height,width,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	}
	else if(direction == 1){
		//arrow = new QPixmap("./pics/obstacle2_arrow_1.png");
		arrow_.load("./pics/obstacle2_arrow_1.png");
		//arrow_ = arrow->scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	}
	else if(direction == 2){
		//arrow = new QPixmap("./pics/obstacle2_arrow_2.png");
		arrow_.load("./pics/obstacle2_arrow_2.png");		
		//arrow_ = arrow->scaled(height,width,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	}
	else if(direction == 3){
		//arrow = new QPixmap("./pics/obstacle2_arrow_3.png");
		arrow_.load("./pics/obstacle2_arrow_3.png");		
		//arrow_ = arrow->scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	}

	if(direction == 0){ // from north
		if(direction2 == 0) vx = -vx;
		//std::cout << "rock1" << std::endl;
		qtemp = new QLabel;
		qtemp->move(temp, 0);
		qtemp->setFixedSize(height,width);
		//qtemp->setPixmap(*rock);
		//qtemp->setPixmap(arrow_);
		qtemp->setPixmap(arrow_.scaled(height,width,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,temp,0,height,width,vx,vy,dragon);
	}
	else if(direction == 1){ // from west
		if(direction2 == 0) vy = -vy;
		//std::cout << "rock2" << std::endl;
		qtemp = new QLabel;
		qtemp->move(0,temp);
		qtemp->setFixedSize(width,height);
		//qtemp->setPixmap(arrow_);
		qtemp->setPixmap(arrow_.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,0,temp,width,height,vx,vy,dragon);
	}
	else if(direction == 2){ // from souht
		vy = -vy;
		if(direction2 == 0) vx = -vx;
		//std::cout << "rock3" << std::endl;
		qtemp = new QLabel;
		qtemp->move(temp,WINDOW_MAX_X*2.49-width);
		qtemp->setFixedSize(height,width);
		//qtemp->setPixmap(arrow_);
		qtemp->setPixmap(arrow_.scaled(height,width,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,temp,WINDOW_MAX_X*2.49-width,height,width,vx,vy,dragon);
	}
	else{ // from east
		vx = -vx;
		if(direction2 == 0) vy = -vy;
		//std::cout << "rock4" << std::endl;
		qtemp = new QLabel;
		qtemp->move(WINDOW_MAX_X*2.49-width,temp);
		qtemp->setFixedSize(width,height);
		//qtemp->setPixmap(arrow_);
		qtemp->setPixmap(arrow_.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,WINDOW_MAX_X*2.49-width,temp,width,height,vx,vy,dragon);
	}
	
	//scene->addPixmap(*(qtemp->pixmap()));
	scene->addWidget(qtemp);

	obstacles.push_back(item);
}

void MainWindow::obs_fireball()
{	
	//std::cout << "fireball" << std::endl;
	//QPixmap *fireball = new QPixmap("./pics/obstacle3_fireball.png");

	srand(scoreNum+2);
	int size = 110;
	int vx = 2+rand()%2;
	int vy = 2+rand()%2;
	
	if(gameLevel == 6){
		vx+=2; vy+=2;
	}
	else if(gameLevel == 5){
		vx++; vy++;
	}

	int temp;
	int direction = rand() % 4;
	int direction2 = rand() % 2;

	do{
		temp = rand() % 622 - size;
		//if(temp < 622-size && temp > 0)	break;
		if(temp < 450 && temp > 200)	break;
	}while(1);

	QLabel *qtemp;
	Obstacle *item;
	
	QPixmap fireball_("./pics/obstacle3_fireball.png");
		//= fireball->scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

	if(direction == 0){
		if(direction2 == 0) vx = -vx;
		//std::cout << "rock1" << std::endl;
		qtemp = new QLabel;
		qtemp->move(temp, 0);
		qtemp->setFixedSize(size,size);
		qtemp->setPixmap(fireball_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,temp,0,size,size,vx,vy,dragon);
	}
	else if(direction == 1){
		if(direction2 == 0) vy = -vy;
		//std::cout << "rock2" << std::endl;
		qtemp = new QLabel;
		qtemp->move(0,temp);
		qtemp->setFixedSize(size,size);
		//qtemp->setPixmap(fireball_);
		qtemp->setPixmap(fireball_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,0,temp,size,size,vx,vy,dragon);
	}
	else if(direction == 2){
		vy = -vy;
		if(direction2 == 0) vx = -vx;
		//std::cout << "rock3" << std::endl;
		qtemp = new QLabel;
		qtemp->move(temp,WINDOW_MAX_X*2.49-size);
		qtemp->setFixedSize(size,size);
		//qtemp->setPixmap(fireball_);
		qtemp->setPixmap(fireball_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,temp,WINDOW_MAX_X*2.49-size,size,size,vx,vy,dragon);
	}
	else{
		vx = -vx;
		if(direction2 == 0) vy = -vy;
		//std::cout << "rock4" << std::endl;
		qtemp = new QLabel;
		qtemp->move(WINDOW_MAX_X*2.49-size,temp);
		qtemp->setFixedSize(size,size);
		//qtemp->setPixmap(fireball_);
		qtemp->setPixmap(fireball_.scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		item = new Obstacle(qtemp,WINDOW_MAX_X*2.49-size,temp,size,size,vx,vy,dragon);
	}
	
	//scene->addPixmap(*(qtemp->pixmap()));
	scene->addWidget(qtemp);

	obstacles.push_back(item);
	//std::cout << "size of obstacle(vector): " << obstacles.size() << std::endl;
}

	

void MainWindow::scoreDisplay()
{
	QTextStream in(&scoreFile);

	while(!in.atEnd()){
		QString chunk1;
		QString ID;
		QString chunk2;
		double score;

		in >> chunk1; // ID:
		in >> ID; // actual ID
		in >> chunk2; // Score:
		in >> score; // actual Score

		QScore tempScore;
		
		tempScore.ID = ID;
		tempScore.score = score;

		string ID_ = ID.toUtf8().constData();
		string chunk1_ = chunk1.toUtf8().constData();
		string chunk2_ = chunk2.toUtf8().constData();
		
		//std::cout << chunk1_ << ID_ << " " << chunk2_ << score << std::endl;
	
		QScores.push_back(tempScore);
		in.readLine();
	}

	int score_size = QScores.size();

	// order: high to low
	for(int i=0;i<score_size-1;i++)
	{
		QScore max = QScores[i];
		int idx = i;
		for(int j=i+1;j<score_size;j++){
			if(max.score < QScores[j].score){
				max = QScores[j];
				idx = j;
			}
		}
		QScore temp = QScores[i];
		QScores[i] = QScores[idx];
		QScores[idx] = temp;
	}

	
	//QStandardItemModel for saving solution
	model = new QStandardItemModel(score_size,1,this);

	for(int i=0;i<score_size;i++){
		QString temp;

		temp.setNum(QScores[i].score);
		
		QStandardItem* ID = new QStandardItem(QScores[i].ID);
		QStandardItem* Score = new QStandardItem(temp);

		model->setItem(i,0,ID);
		model->setItem(i,1,Score);
	}
	scoreList->setModel(model);

	scoreList->resizeRowsToContents(); // Adjust the row height
	scoreList->resizeColumnsToContents();
	scoreList->setColumnWidth(0,45);
	scoreList->setColumnWidth(1,87);
}

void MainWindow::exportScore()
{
	QString tname = usrName->text();
	//string name = tname.toUtf8().constData();
	double tscore = score->value();
	
	QScore temp;
	temp.ID = tname;
	temp.score = tscore;

	QScores.push_back(temp);

	int score_size = QScores.size();
	
	// order: high to low
	for(int i=0;i<score_size-1;i++)
	{
		QScore max = QScores[i];
		int idx = i;
		for(int j=i+1;j<score_size;j++){
			if(max.score < QScores[j].score){
				max = QScores[j];
				idx = j;
			}
		}
		QScore temp = QScores[i];
		QScores[i] = QScores[idx];
		QScores[idx] = temp;
	}

	// if size is larger than 10, discard the lowest one, which is the last one.
	while(QScores.size() > 10){
		QScores.pop_back();
	}
	
	scoreFile.remove();

	scoreFile.setFileName("score.txt");
	if(!scoreFile.open(QIODevice::ReadWrite | QIODevice::Text))
		std::cout << "Error occurs during writing score file" << std::endl;
	
	QTextStream out(&scoreFile);

	score_size = QScores.size();
	
	for(int i=0;i<score_size;i++){
		if(i == score_size-1)
			out << "ID: " << QScores[i].ID << " Score: " << QScores[i].score;
		else
			out << "ID: " << QScores[i].ID << " Score: " << QScores[i].score << "\n";
	}
}

void MainWindow::allTimerStop()
{
	mainTimer->stop();
	timer1->stop(); 
	timer2->stop();
	timer3->stop();
	//timer4->stop();
	//timer5->stop();
}

void MainWindow::allTimerDelete()
{
	delete mainTimer;
	delete timer1;
	delete timer2;
	delete timer3;

	mainTimer = NULL;
}

MainWindow::~MainWindow()
{/*
	if(mainTimer->isActive() == false){
		mainTimer->stop();
		timer1->stop();
		timer2->stop();
		timer3->stop();
		timer4->stop();
		timer5->stop();
	}

	// buttons
	delete pause_resumeGame;	
	delete exitGame;	

	// text boxes
	delete score;
	
	// labels for topLayout 
	delete scoreLabel;

	delete topLayout; // top input te
	delete layout; // main layout    
    delete scene;
    delete view;
    delete window;
*/}

