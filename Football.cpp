/*

 //################################################################################################\\
||          ______                                                                                  ||
||         /      |   _     _                                                                       ||
||        |  ,----' _| |_ _| |_                                                                     ||
||        |  |     |_   _|_   _|                                                                    ||
||        |  `----.  |_|   |_|                                                                      ||
||         \______|                                                                                 ||
||         _______   ______     ______   .___________..______        ___       __       __          ||
||        |   ____| /  __  \   /  __  \  |           ||   _  \      /   \     |  |     |  |         ||
||        |  |__   |  |  |  | |  |  |  | `---|  |----`|  |_)  |    /  ^  \    |  |     |  |         ||
||        |   __|  |  |  |  | |  |  |  |     |  |     |   _  <    /  /_\  \   |  |     |  |         ||
||        |  |     |  `--'  | |  `--'  |     |  |     |  |_)  |  /  _____  \  |  `----.|  `----.    ||
||        |__|      \______/   \______/      |__|     |______/  /__/     \__\ |_______||_______|    ||
||                                                                                                  ||
||        .______   .______        ______          __   _______   ______ .___________.              ||
||        |   _  \  |   _  \      /  __  \        |  | |   ____| /      ||           |              ||
||        |  |_)  | |  |_)  |    |  |  |  |       |  | |  |__   |  ,----'`---|  |----`              ||
||        |   ___/  |      /     |  |  |  | .--.  |  | |   __|  |  |         |  |                   ||
||        |  |      |  |\  \----.|  `--'  | |  `--'  | |  |____ |  `----.    |  |                   ||
||        | _|      | _| `._____| \______/   \______/  |_______| \______|    |__|                   ||
||                                                                                                  ||
||                 {{ Coded by Dylan Taylor, Blair Stephen, and Connor Dickey }}                    ||
||                                                                                                  ||
 \\################################################################################################//

*/

/* Scoring:
	Touchdown - 6 Points
    Field Goal - 3 Points
    Extra Points - 1 Point
*/

// Directives
#include <iostream> //iostream.h was replaced with iostream somewhere between Visual Studio 6 and Visual Studio 2008.
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include<windows.h>
using namespace std;
enum Colors {blue=1, green, cyan, red, purple, yellow, gray, dgray, hblue, hgreen, hcyan, hred, hpurple, hyellow, hwhite, white };

// Function Prototypes 
int rand(int, int); // This is VERY useful. Generates random numbers. Syntax is min, max.
void splash(); //Moved to a function to keep this clutter out of the main function.
void doplay(bool); //The boolean is false 99% of the time. It is only true if you are recursively calling it for a 2-point conversion. This saves a LOT of coding.
void fieldgoal();
void turnover();
void displayinfo();
void nodownsleft();
void victory();
void gameisover(int);
void setcolor(int);
void cls();
void drawbox(int);
void congrats();
void fullscreen();
//Adds points to the team specified and determines if the game is over yet
void points(int, int); //Parameters: Team to Recieve Points, Type of Score (1: TD, 2: FG, 3: EP)
void drawfield(); //Draws the football field to the screen using a bitmap image.
//Global Variables, accessible across all methods (for a good reason)
HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
bool gameover = false; //The game is not over yet...
bool chosen = false;
bool fd1 = false;
bool fd2 = false;
bool turnsover = false;
//Start both teams off as not having posession.
int team = 0; // Current Team in Posession of the ball. 
int yards = 25;
int downs = 4; //Downs remaining for the team with posession.
int t1ts = 0; //Total Number of turns by Team 1
int t2ts = 0; //Total Number of turns by Team 2
int t1s = 0; //Team 1's score
int t2s = 0; //Team 2's score
int downnum = 0;//This is the number of the down. It will be calculated based on downs remaining.
int nfd = 10; //Next First Down
int main( int argc, char* argv[] ) {
	fullscreen(); //It's obvious what this does based on the name.
	//Team 1 - Red (1); Team 2 - Green (3)
	srand((unsigned int)time(0)); //Set up random numbers.... This is a replacement for "srand(time(NULL));" for Visual Studio 2008.
	char choice[9999]; //Play or field goal. While 2 would've made sense here, this fixes a bug. Also, this number is OVER 9000!!!
	splash(); //Displays our super awesome splash screen! :D
	cout<<endl<<"    "; //Goes to next line and prints 3 spaces
	system("pause"); //Wait for user to press a key
	system("cls"); //When they press a key, clear the screen.
	setcolor(7);
	while (gameover == false) {
        if (team == 0) { //This will be set back to 0 when going into a second overtime.
			cout<<"Flipping a coin to determine which team will have posession... ";
			team = rand(1,2);
			if (team == 1) {
				t1ts = t1ts + 1;
			} else if (team == 2) {
				t2ts = t2ts + 1;
			}
			if (team == 1) {
				setcolor(1);
			} else if (team == 2) {
				setcolor(3);
			}
			cout<<"Team "<<team<<"!"<<endl;
			setcolor(7);
			displayinfo();
        }

        while ((team == 1) && (gameover == false)) {
            chosen = false;
            while (chosen == false) {
				cout<<endl<<"   [P]lay or [F]ield Goal? "; //Gets first letter typed. Ignores end line characters.
				cin.getline(choice, 9999, '\n');
				if ((_stricmp(choice, "P")) == 0) {    //If they chose to do a play
                    chosen = true;
                    //cout<<"Play (Team 1)"<<endl;
					cout<<"-------------------------------------------------------------------------------"<<endl;
                    doplay(false);
                } else if ((_stricmp(choice, "F")) == 0) { //If they chose to go for field goal/extra point
                    chosen = true;
                    //cout<<"Field Goal (Team 1)"<<endl;
					cout<<"-------------------------------------------------------------------------------"<<endl;
                    fieldgoal();
                } else {
					cin.clear(); //JUST in case they enter more than 9999 characters, this will clear the input buffer.
					//I have no idea why this is needed, but it was mentioned on cprogramming.com -- and it might just work.
					cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
                    cout<<"Invalid choice, please choose only 'P' or 'F'."<<endl;
					cout<<"-------------------------------------------------------------------------------"<<endl;
                }
            }//A choice was made.
        }
		while ((team == 2) && (gameover == false)) {
            chosen = false;
            while (chosen == false) {
				cout<<endl<<"   [P]lay or [F]ield Goal? "; //Gets first letter typed. Ignores end line characters.
				cin.getline(choice, 9999, '\n');
				if ((_stricmp(choice, "P")) == 0) {    //If they chose to do a play
                    chosen = true;
                    //cout<<"Play (Team 2)"<<endl;
					cout<<"-------------------------------------------------------------------------------"<<endl;
                    doplay(false);
                } else if ((_stricmp(choice, "F")) == 0) { //If they chose to go for field goal/extra point
                    chosen = true;
                    //cout<<"Field Goal (Team 2)"<<endl;
					cout<<"-------------------------------------------------------------------------------"<<endl;
                    fieldgoal();
                } else {
					cin.clear(); //JUST in case they enter more than 9999 characters, this will clear the input buffer.
					//I have no idea why this is needed, but it was mentioned on cprogramming.com -- and it might just work.
					cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
                    cout<<"Invalid choice, please choose only 'P' or 'F'."<<endl;
					cout<<"-------------------------------------------------------------------------------"<<endl;
                }
            }//A choice was made.
        }
    }

//Before Each Play, Offense Enteres "P" for running/passing play, or "F" for field goal/extra point.
return 0;
}//Ends Main Method

int rand (int min, int max) { //Random Number Generator
    int r = (rand() % max + min);
    return r;
}

void doplay(bool twopoint) { //Gains of yards are done with subtraction because they are getting closer to the field goal (which is 0).
	//If two point is true, we are recursively calling this function for only two points if they get a touchdown.
	system("cls");
	turnsover = true;
	bool attemptconv = false; //attempting a conversion
	int awarded;
	if (twopoint == false) {
		awarded = 6; //Six points awarded for a successful touchdown but no conversion.
	} else if (twopoint == true) {
		awarded = 2; //Two points awarded for a successful conversion.
		turnsover = false;
	}
    int play = (rand(1,12));
	//int play = 1;
	int result; //Used for checking if extra point attempt is good.
	if (twopoint != true) { //Otherwise we will get an infinite loop
		bool chosen = false;
	}
	char choice[2] = " "; //Two point conversion or Field Goal -- set to a blank space
    if (play == 1) {
        //Touchdown, add 6 to team with possesion.
        cout<<"Your offense made a successful pass to your open receiver, who ran it into "<<endl;
        cout<<"the endzone for a ";
		if (twopoint == true) {
			cout<<"2 point conversion!";
		} else {
				cout<<"touchdown!";
		}
		cout<<endl;
		//DO NOT BE AN IDIOT AND RE-ADD THE POINTS FUNCTION HERE. YARDS = 0 WILL HAVE THE TOUCHDOWN CALCULATED LATER.
		//THIS IS LIKE THE THIRD TIME WE HAD TO FIX THIS! 
		yards = 0;
        downs = 2; //Automatically subtracts one later. This fixes a bug...
    } else if (play == 2) {
        //Turnover.
        cout<<"Your running back began to run it down the field, when he was hit hard by  "<<endl;
        cout<<"the opponent defensive lineman, causing your running back to fumble. "<<endl;
        cout<<"The opponent line man recovered the ball."<<endl;
		turnsover = true;
        turnover(); //Switch posession
		downs = 5; //Will go back down to 4 automatically.
    } else if (play == 3) {
        //Gain of 15
        cout<<"Your quarterback saw your wide reciever wide open and passed it to him. "<<endl;
		if (twopoint == false) {
			cout<<"He caught it and ran for a gain of 15 yards!"<<endl;
		} else {
			cout<<"He caught it and ran it into the endzone for a successful two point conversion!"<<endl;
		}
        yards = yards - 15;
    } else if (play == 4) {
        //Loss of 10
        cout<<"Your quarterback ran backwards because the pocket was collapsing, and was"<<endl;
        cout<<"sacked by the defense for a loss of 10 yards."<<endl;
        yards = yards + 10;
    } else if (play == 5) {
        //Gain of 4
        cout<<"Your running back had the ball handed off to him,"<<endl;
        cout<<"and ran the ball for a gain of 4 yards."<<endl;
        yards = yards - 4;
    } else if (play == 6) {
        //No Gain
        cout<<"Your running back was pitched the ball, and ran it to the line of scrimmage"<<endl;
        cout<<"where he was tackled. You gained no yardage."<<endl;
    } else if (play == 7) {
        //Gain of 1
        cout<<"Your running back was handed the ball, where he ran for a gain of 1 yard."<<endl;
        yards = yards - 1;
    } else if (play == 8) {
        //Loss of 2
        cout<<"Your quarterback was pressured and sacked for a loss of 2 yards. "<<endl;
        yards = yards + 2;
    } else if (play == 9) {
        //Gain of 6
        cout<<"Your quarterback made a short pass ";
		if (twopoint == false) {
			cout<<"for a gain of 6 yards."<<endl;
		} else {
			cout<<"into the endzone for a successful two point conversion!"<<endl;
		}
        yards = yards - 6;
    } else if (play == 10) {
        //Loss of 4
        cout<<"Your quarter back didn't see the opponent coming on his left, which caused him "<<endl;
        cout<<"to be sacked for a loss of 4 yards."<<endl;
        yards = yards + 4;
    } else if (play == 11) {
        //Gain of 8
        cout<<"Your running back got past the defensive line and made a run "<<endl;
		if (twopoint == false) {
			cout<<"for a gain of 8 yards."<<endl;
		} else {
			cout<<"into the endzone for a successful two point conversion!"<<endl;
		}
        yards = yards - 8;
	//It IS POSSIBLE for the defense to get a touchdown during a 2-point conversion. They get only 2 points. We looked this up in the official rules. SRSLY.
    } else if (play == 12) {
        //Interception, Defensive Touchdown
        //Give 6 points to defense, then it will go for extra point attempt, and return to offense.
        cout<<"Your quarterback threw the ball to your wide reciever."<<endl;
        cout<<"The ball hit your reciever's helmet deflecting the ball high into the air."<<endl;
        cout<<"The opponent defensive back intercepted the ball and ran for a touchdown!"<<endl;
        downs = 5; // Will automatically subtract by 1 later.
		if (team == 1) {
			points(2,awarded);
		} else if (team == 2) {
			points(1,awarded);
		}
		yards = 25; // Yards go back to 25. Team is not changed because it would go back to the original team anyways.
		nfd = 10;
		//If it's team 1's turn, team 2 had less turns OR the same amount of turns, and they have more points
		if ((team == 1) && (t2ts <= t1ts) && (t2s > t1s) && (gameover != true)) {
				gameisover(2); //Team 2 wins. Game is OVER.
		}
		//If it's team 2's turn, team 1 had less turns OR the same amount of turns, and they have more points
		if ((team == 2) && (t1ts <= t2ts) && (t1s > t2s) && (gameover != true)) {
				gameisover(1); //Team 1 wins. Game is OVER.
		}
    }
	if (fd1 == false) {
		//abs is absolute value
		nfd = abs(15 - yards);
	}
	downs = downs - 1;
	if (fd1 == false && yards <= 15 && yards > 5) //If this is the first time they got a first down and they got past/on the 15 yard line
	{
	cout<<"-------------------------------------------------------------------------------"<<endl;
	congrats();
	cout<<" Your team just earned a First Down!"<<endl;
	downs = 4;
	nfd = yards - 10;
	fd1 = true;
	}
	if (fd2 == false && yards <= nfd && yards > 0 && fd1 == true) // the first fd1 == false makes sure that it doesn't print first down twice.
	{
	cout<<"-------------------------------------------------------------------------------"<<endl;
	congrats();
	cout<<" Your team just earned a First Down!"<<endl;
		downs = 4;
		fd2 = true;
	}
	if (yards <= 0) {
		yards = 0; //Fixes a bug.
		if (twopoint == false) {
			turnsover = false; //This fixes a MAJOR BUG.
		}
		points(team, awarded); //Touchdown!
		if (twopoint == true) {
			turnover();
		} else if (twopoint == false) { //So they can't go for ANOTHER field goal or 2-point conversion after the first one.
			chosen = false;
			while (chosen == false) {
				cout<<"-------------------------------------------------------------------------------"<<endl;
				if (team == 1) {
					setcolor(1);
				} else if (team == 2) {
					setcolor(3);
				}
				cout<<endl<<"   Team "<<team;
				setcolor(7);
				cout<<" just scored a touchdown! [E]xtra Point or 2-Point [C]onversion? ";
				cin.getline(choice, 9999, '\n');
				if ((_stricmp(choice, "E")) == 0) {    //If they chose to go for a field goal
					result = rand(1,10); //Random integer 1 to 10
					system("cls");
					cout<<"Team "<<team<<" is attempting to kick a successful field goal from the "<<(yards + 10)<<" yard line..."<<endl;
					cout<<"The kicker kicks it aaaaaaaaaaaand... it's";
					if (result != 1 && result != 10) {
						cout<<" GOOD!!!!! Team "<<team<<" earned 3 points!"<<endl;
						points(team, 1); //It's good.
					} else {
						cout<<" no good! No points were awarded."<<endl;
						downs = 4;
					}
					turnover(); //Give posession to the other team...
					chosen = true; //A choice was made. Needed to get out of the loop.
					turnsover = true;
				} else if ((_stricmp(choice, "C")) == 0) { // If they go for 2-Point Conversion
					downs = 2; //Give them one more play... a down is automatically subtracted...
					yards = 2;
					doplay(true); //This tells the function that it is being called recursively and they points for a touchdown by the offense is only 2.
					turnsover = true;
					chosen = true;
					attemptconv = true;	
				} else {
					cout<<"Invalid choice, please choose only 'E' or 'C'."<<endl;
				}
			}
		}
	}
    if (downs < 1) {
        downs = 4;
        nodownsleft();
	}
	//If we remove && attemptconv == true it will display twice, but the second one will be correct.
	if (gameover == false && twopoint == false) {
		displayinfo();
	}
	return;
}

void turnover() { //Gives posession to the defense
    if (team == 1) {
		t2ts = t2ts + 1;
        team = 2;
    } else if (team == 2) {
		t1ts = t1ts + 1;
        team = 1;
    }
	fd1 = false;
	fd2 = false;
	yards = 25; //Put yards back to 25
	nfd = 10;
    return;
}

void fieldgoal() {
	system("cls");
	turnsover = true;
    int result = rand(1,10);
    int tyards = 0;
    tyards = yards + 10; //Go 10 yards AWAY from opponents goal post.
    cout<<"Team "<<team<<" is attempting to kick a successful field goal from the "<<tyards<<" yard line..."<<endl;
	cout<<"The kicker kicks it aaaaaaaaaaaand... it's";
	//Behold... the if statement of all if statements. One if statement to rule them all. (LOTR reference)
	if (((tyards >=10 && tyards <= 15) && (result != 1 && result != 10)) || ((result != 1 && result != 2 && result != 10) && (tyards >=16 && tyards <= 20)) || ((tyards >=21 && tyards <= 30) && (result != 1 && result != 2 && result != 9 && result != 10)) || ((tyards >=31 && tyards <= 40) && (result != 1 && result != 2 && result != 3 && result != 9 && result != 10)) || ((tyards > 40) && (result != 1 && result != 2 && result != 3 && result != 4 && result != 8 && result != 9 && result != 10))) {
		cout<<" GOOD!!!!! Team "<<team<<" earned 3 points!"<<endl;
		points(team, 3); //It's good.
		downs = 4;
    } else {
		cout<<" no good! No points were awarded."<<endl;
		downs = 4;
	}
	//Check if the game is over.
	victory();
	turnover();
	if (gameover == false) {
		displayinfo();
	}
	return;
}

void displayinfo() {
	cout<<"There are "<<nfd<<" more yards until your next first down."<<endl;
	if (downs == 4)
		downnum = 1;
	else if (downs == 3)
		downnum = 2;
	else if (downs == 2)
		downnum = 3;
	else if (downs == 1)
		downnum = 4;
	setcolor(7);
	cout<<endl<<" "<<'\xDB'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDB'<<endl<<" "<<'\xDB';
	cout<<"  Current Offense: ";
    if (team == 1) {
		setcolor(1);
        cout<<"Team 1"<<" "<<"[";
		if (t1s < 10) {
			cout<<"0";
		}
		cout<<t1s<<" Points]  ";
    } else if (team == 2) {
		setcolor(3);
        cout<<"Team 2"<<" "<<"[";
		if (t2s < 10) {
			cout<<"0";
		}
		cout<<t2s<<" Points]  ";
    }
	setcolor(7);
    cout<<"Current Defense: ";
    if (team == 1) {
		setcolor(3);
        cout<<"Team 2"<<" "<<"[";
		if (t2s < 10) {
			cout<<"0";
		}
		cout<<t2s<<" Points]";
    } else if (team == 2) {
		setcolor(1);
        cout<<"Team 1"<<" "<<"[";
		if (t1s < 10) {
			cout<<"0";
		}
		cout<<t1s<<" Points]";
    }
	setcolor(7);
	cout<<"  "<<'\xDB'<<endl<<" "<<'\xDB';
	cout<<"  Current Position (In Yards): ";
	setcolor(2);
	if (yards < 10) {
		cout<<"0";
	}
	cout<<yards<<"      ";
	setcolor(7);
    cout<<"Current Down: ";
	setcolor(4);
	cout<<downnum<<"                      ";
	setcolor(7);
	cout<<'\xDB'<<endl;
	cout<<" "<<'\xDB'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDB'<<endl;       
	//Turn Count. Mostly For Internal Development Use.
	cout<<"T1: "<<t1ts<<" T2: "<<t2ts<<endl;
	return;
}

void nodownsleft() {
    cout<<"-------------------------------------------------------------------------------"<<endl;
    if (team == 1) {
		setcolor(1);
	} else if (team == 2) {
		setcolor(3);
	}
	cout<<"Team "<<team;
	setcolor(7);
	cout<<" just ran out of downs. ";
	turnover(); //Switch teams
	if (team == 1) {
		setcolor(1);
	} else if (team == 2) {
		setcolor(3);
	}
	cout<<"Team "<<team;
	setcolor(7);
	cout<<" is now in posession of the ball."<<endl;
    //cout<<"-------------------------------------------------------------------------------"<<endl;
    return;
}

void points(int reciever, int pts){
    //First Determine number of points to give...
	//If the team to recieve the points is set to anything other than 1 or 2 (this program uses 0) no points will be added.
	//The only thing that will happed is a field goal is scored
	//Add points to current team
    if (reciever == 1) {
        t1s = t1s + pts;
    } else if (reciever == 2) {
        t2s = t2s + pts;
    }
	if (pts != 6) { // If it's not a touchdown, set the yards back to 25.
		yards = 25;
		nfd = 10;
	}
    //Now determine if it's a victory...
	if (turnsover == true) {
		victory();
	}
	return;
}

void victory() { //Checks if a team has won yet...
	//The reason gameover needs to be checked is because victory method is called multiple times even after the game is over.
	if ((t1s != t2s) && (gameover != true)) { //If the scores are NOT the same and the game is not already over
		if ((t1ts == t2ts) && (t1ts >= 1) && (t2ts >= 1)) { //And if they both had the same number of turns and they both had at least one turn
			//Whatever team has the highest score wins!
			if (t1s > t2s) { //If team 1's score is more than team 2's score...
				gameisover(1); //Team 2 just lost the game! And so did you!
			} else if (t2s > t1s) { //Otherwise, if team 2's score is more than team 1's score
				gameisover(2); //Team 1 just lost the game!
			}
		}
	}
	return;
}

void gameisover(int team) { //End of game message.
	gameover = true;
	//cls();
	displayinfo();
	cout<<endl<<"   ";
	congrats();
	if (team == 1) {
		setcolor(1);
	} else if (team == 2) {
		setcolor(3);
	}
	cout<<" Team "<<team;
	setcolor(7);
	cout<<" just won the game!"<<endl; //And you just lost the game. :P
	cout<<endl<<"      In the end, ";
	setcolor(1);
	cout<<"Team 1 ";
	setcolor(7);
	cout<<"had ";
	setcolor(1);
	cout<<t1s;
	setcolor(7);
	cout<<" points, and ";
	setcolor(3);
	cout<<"Team 2 ";
	setcolor(7);
	cout<<"had ";
	setcolor(3);
	cout<<t2s;
	setcolor(7);
	cout<<" points!"<<endl;
	cout<<endl<<"         To leave fullscreen mode, press Alt+Enter.";
	//Bottome bar
	//cout<<" "<<'\xDB'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDB'<<endl;
	while (gameover == true) { //Fixes a bug that causes the program to exit when the game is over	
		//do nothing at all.
	}
	return;
}

void setcolor(int c) {
	if (c == 0) {
		SetConsoleTextAttribute( handle, hwhite);
	} else if (c == 1) {
		SetConsoleTextAttribute( handle, hred);
	} else if (c == 2) {
		SetConsoleTextAttribute(handle, hyellow);
	} else if (c == 3) {
		SetConsoleTextAttribute(handle, hgreen);
	} else if (c == 4) {
		SetConsoleTextAttribute(handle, hcyan);
	} else if (c == 5) {
		SetConsoleTextAttribute(handle, hblue);
	} else if (c == 6) {
		SetConsoleTextAttribute(handle, hpurple);
	} else if (c == 7) {
		SetConsoleTextAttribute(handle, gray);
	}
}
void cls() {
	system("cls");
	displayinfo();
}

void drawbox(int x) {
	//1 is the top of the box, 2 is the bottom.
	if (x == 1) {
		cout<<endl;
	}
}

void splash() {
	//This entire splash screen was MANUALLY created with ASCII art. It was such a pain to make this. :(
	/*Displays the splash screen. This code is unfortunately not meant to be easily editable...
	This is approximately what it should look like without character escapes or colors:
cout<<"______________________________________________________________________________"<<endl;
cout<<"_                                                                            _"<<endl;
cout<<"_                     __    __          __  __          __                   _"<<endl;
cout<<"_                     __    __          __  __          __                   _"<<endl;
cout<<"_                     __    __   ____   __  __   ____   __                   _"<<endl;
cout<<"_                     __    __  __  __  __  __  __  __  __                   _"<<endl;
cout<<"_                     ________  ______  __  __  __  __  __                   _"<<endl;
cout<<"_                     __    __  __      __  __  __  __  __                   _"<<endl;
cout<<"_                     __    __  __      __  __  __  __                       _"<<endl;
cout<<"_                     __    __  __  __  __  __  __  __  __                   _"<<endl;
cout<<"_                     __    __   ____   __  __   ____   __                   _"<<endl;
cout<<"_                                                                            _"<<endl;
cout<<"_ Welcome to C++ Football, by Dylan Taylor, Blair Stephen, and Connor Dickey _"<<endl;
cout<<"______________________________________________________________________________"<<endl;  
*/
setcolor(0);
cout<<endl<<" "<<'\xDB'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDF'<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
setcolor(1);
//H
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
setcolor(3);
//L1
cout<<"          "<<'\xDB'<<'\xDB';
setcolor(4);
//L2
cout<<"  "<<'\xDB'<<'\xDB';
setcolor(6);
//!
cout<<"          "<<'\xDB'<<'\xDB'<<"                   ";
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
setcolor(1);
//H
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
setcolor(3);
//L1
cout<<"          "<<'\xDB'<<'\xDB';
setcolor(4);
//L2
cout<<"  "<<'\xDB'<<'\xDB';
setcolor(6);
//!
cout<<"          "<<'\xDB'<<'\xDB'<<"                   ";
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//LINE THREE
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"   "<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB';
setcolor(3);
//L1
cout<<"   "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"   "<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB';
//!
setcolor(6);
cout<<"   "<<'\xDB'<<'\xDB'<<"                   ";
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//LINE 4
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB';
//L1
setcolor(3);
cout<<"  "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB';
//!
setcolor(6);
cout<<"  "<<'\xDB'<<'\xDB'<<"                   ";
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"  "<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB';
//L1
setcolor(3);
cout<<"  "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB';
//!
setcolor(6);
cout<<"  "<<'\xDB'<<'\xDB'<<"                   ";
//LINE 6
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"  "<<'\xDB'<<'\xDB';
//L1
setcolor(3);
cout<<"      "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB';
//!
setcolor(6);
cout<<"  "<<'\xDB'<<'\xDB'<<"                   ";
//LINE 7
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"  "<<'\xDB'<<'\xDB';
//L1
setcolor(3);
cout<<"      "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB'<<"                       ";
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB';
//L1
setcolor(3);
cout<<"  "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"  "<<'\xDB'<<'\xDB'<<"  "<<'\xDB'<<'\xDB';
//!
setcolor(6);
cout<<"  "<<'\xDB'<<'\xDB'<<"                   ";
setcolor(0);
cout<<'\xDB'<<endl<<" "<<'\xDB'<<"                     ";
//H
setcolor(1);
cout<<'\xDB'<<'\xDB'<<"    "<<'\xDB'<<'\xDB';
//E
setcolor(2);
cout<<"   "<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB';
setcolor(3);
//L1
cout<<"   "<<'\xDB'<<'\xDB';
//L2
setcolor(4);
cout<<"  "<<'\xDB'<<'\xDB';
//O
setcolor(5);
cout<<"   "<<'\xDB'<<'\xDB'<<'\xDB'<<'\xDB';
//!
setcolor(6);
cout<<"   "<<'\xDB'<<'\xDB'<<"                   ";
setcolor(0);
cout<<'\xDB'<<endl;
cout<<" "<<'\xDB'<<"                                                                            "<<'\xDB'<<endl;
cout<<" "<<'\xDB'<<" Welcome to C++ Football, by Dylan Taylor, Blair Stephen, and Connor Dickey "<<'\xDB'<<endl;
cout<<" "<<'\xDB'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDC'<<'\xDB'<<endl;       
}

void congrats() {
	setcolor(1);
	cout<<"C";
	setcolor(2);
	cout<<"o";
	setcolor(3);
	cout<<"n";
	setcolor(4);
	cout<<"g";
	setcolor(5);
	cout<<"r";
	setcolor(6);
	cout<<"a";
	setcolor(1);
	cout<<"t";
	setcolor(2);
	cout<<"u";
	setcolor(3);
	cout<<"l";
	setcolor(4);
	cout<<"a";
	setcolor(5);
	cout<<"t";
	setcolor(6);
	cout<<"i";
	setcolor(1);
	cout<<"o";
	setcolor(2);
	cout<<"n";
	setcolor(3);
	cout<<"s";
	setcolor(4);
	cout<<"!";
	setcolor(7);
}

void fullscreen() {
  typedef BOOL (WINAPI *PROCSETCONSOLEDISPLAYMODE)(HANDLE,DWORD,LPDWORD);
  typedef BOOL (WINAPI *PROCGETCONSOLEDISPLAYMODE)(LPDWORD);
  PROCSETCONSOLEDISPLAYMODE SetConsoleDisplayMode;
  PROCGETCONSOLEDISPLAYMODE GetConsoleDisplayMode;
  HMODULE hKernel32 = GetModuleHandle("kernel32");
  SetConsoleDisplayMode = (PROCSETCONSOLEDISPLAYMODE )
  GetProcAddress(hKernel32,"SetConsoleDisplayMode");
  GetConsoleDisplayMode = (PROCGETCONSOLEDISPLAYMODE)
  GetProcAddress(hKernel32,"GetConsoleDisplayMode");
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwOldMode;
  SetConsoleDisplayMode(hOut,1,&dwOldMode);
  system("cls");
}