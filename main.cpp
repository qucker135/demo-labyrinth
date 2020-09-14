#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <math.h>

using namespace std;

enum WALL{BOTTOM,TOP,LEFT,RIGHT};
string* gen_labyrinth(const unsigned height,const unsigned width,const WALL w1,const int wh1,const WALL w2,const int wh2){
	if(height<1 || width<1 || (w1==w2 && wh1==wh2)){
		return NULL;
	}
	string* wsk = new string [2*height+1];
	for(int i=0;i<=2*height;i++){
		wsk[i]="";
		for(int j=0;j<=2*width;j++){
			if(i==0||i==2*height||j==0||j==2*width) wsk[i] = wsk[i] + "#";
			else wsk[i] = wsk[i] + " ";
		}	
	}
	switch(w1){
			case BOTTOM:
				wsk[2*height][2*wh1+1] = ' ';
			break;
			case TOP:
				wsk[0][2*wh1+1] = ' ';	
			break;
			case LEFT:
				wsk[2*wh1+1][0] = ' ';
			break;
			case RIGHT:
				wsk[2*wh1+1][2*width] = ' ';
			break;
	}
	switch(w2){
			case BOTTOM:
				wsk[2*height][2*wh2+1] = ' ';
			break;
			case TOP:
				wsk[0][2*wh2+1] = ' ';	
			break;
			case LEFT:
				wsk[2*wh2+1][0] = ' ';
			break;
			case RIGHT:
				wsk[2*wh2+1][2*width] = ' ';
			break;
	}
	int vert = 2*height + 2*width;
	while(vert<(height+1)*(width+1)){
		int w=0;
		const int random = rand()%vert;
		for(int i=0;i<=2*height;i=i+2){
			for(int j=0;j<=2*width;j=j+2){
				if(wsk[i][j]=='#' && w<random) w++;
				else if(wsk[i][j]=='#' && w==random){
					w++;
					const int direction = rand()%4;
					switch(direction){
						case 0://UP
							if(i>1 && wsk[i-2][j]!='#'){
								wsk[i-1][j] = '#';
								wsk[i-2][j] = '#';
								vert++;
							}
						break;
						case 1://RIGHT
							if(j<2*width-1 && wsk[i][j+2]!='#'){
								wsk[i][j+1] = '#';
								wsk[i][j+2] = '#';
								vert++;
							}
						break;
						case 2://DOWN
							if(i<2*height-1 && wsk[i+2][j]!='#'){
								wsk[i+1][j] = '#';
								wsk[i+2][j] = '#';
								vert++;
							}
						break;
						case 3://LEFT
							if(j>1 && wsk[i][j-2]!='#'){
								wsk[i][j-1] = '#';
								wsk[i][j-2] = '#';
								vert++;
							}
						break;
					}
				}
			}
		}
	}
		
	return wsk;

}

string* board;

int main(){
	initscr();
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);

	//board = new string[11];
	
	/*
	board[0]  = "###########";
	board[1]  = "#         #";
	board[2]  = "# ##### ###";
	board[3]  = "# #   # # #";
	board[4]  = "# ### # # #";
	board[5]  = "    #   #  ";
	board[6]  = "# ### ### #";
	board[7]  = "# #   # # #";
	board[8]  = "### ### # #";
	board[9]  = "#         #";
	board[10] = "###########";
	*/

	srand(time(NULL));
	
	//sample values
	//by default, h(eight) and w(idth) are terminal-scaled
	//to disable it, comment section "terminal-scaled values"
	int h = 17;
	int w = 23;
	int r = h+(h%2==0),c=0;
	//DISCLAIMER
	/*
		h and w parameters explain number of faces in proper dimension, however due to the need of representation of walls generated table will have actual height of 2*h+1 and width of 2*w+1.
	*/
		
	const int range = 10;

	while(true){
		//terminal-scaled values
		{
		getmaxyx(stdscr,h,w);
		h=h/2-1;
		w=w/2-1;
		r=h+(h%2==0),c=0;//current position
		}

		board = gen_labyrinth(h,w,LEFT,h/2,RIGHT,h/2);

		int s=0;
		while(s!=410){ //rescale window
			for(int i=0;i<2*h+1;i++){
				for(int j=0;j<2*w+1;j++){
					if(r==i&&c==j) attron(A_REVERSE);
					
					//V1-VISIBLE
					printw("%c",board[i][j]);
					
					//V2-INVISIBLE
					
					/*{
					if(abs(i-r)<range && abs(j-c)<range)
						printw("%c",board[i][j]);
					else printw(" ");
					}*/
					
					if(r==i&&c==j) attroff(A_REVERSE);
					
				}
				printw("\n");
			}
			refresh();
			s = getch();
			
			if(s==258 && r<2*h && board[r+1][c]!='#') r++; //ARROW KEYS
			if(s==259 && r>0  && board[r-1][c]!='#') r--;  //
			if(s==260 && c>0  && board[r][c-1]!='#') c--;  //
			if(s==261 && c<2*w && board[r][c+1]!='#') c++; //
			if(s==110 || s==78) {move(0,0); break;}        //n or N for new labyrinth
			
			move(0,0);
		}
			
		delete[] board;

	}
	
	endwin();
	return 0;
}
