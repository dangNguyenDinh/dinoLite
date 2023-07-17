#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<iomanip>
#include<unistd.h> // add when using dev c 5.11
using namespace std;

void TextColor(int x)//X là mã màu
{
     HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
void gotoxy(int x,int y){  
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(console, a);
}

void drawGround(char bg[30][60]){	//ve tat ca nhung gi co tren man hinh. Day la ham tao nen phan hien thi
	gotoxy(0,0);
	for(int i = 0;i < 30;i++){
		for(int j = 0;j < 60;j++){
			cout<<bg[i][j];
		}
		cout<<"\n";
	}
}
bool enemiesControl(){		//ham random ti le 1/5
	int a = rand()%8;
	if(a==0) return true;
	return false;
	
}
void drawCactus(int ct,char bg[30][60]){   //them cactus vao mang, de them no vao man hinh
	bg[28][ct]='*';
	bg[27][ct]='*';
}
void drawInvisibleCactus(int ct,char bg[30][60]){	//xoa cactus trong mang, de xoa no tren man hinh
	bg[28][ct]=' ';
	bg[27][ct]=' ';
}
void drawEnemies(char bg[30][60],int &enemies){	
	gotoxy(0,0);
	for(int i = 0;i < 60;i++){		//phan nay de lam cho cactus di lui ve ben trai.
		if(bg[28][i] == '*' && i!=1){
			drawInvisibleCactus(i,bg);
			drawCactus(i-1,bg);
		}else if(bg[28][i] == '*' && i==1){
			drawInvisibleCactus(i,bg);
		}
	}
	//kiem tra diem da dat duoc	
	if(bg[28][19] == '*'){
			enemies++;
			cout<<"\a";
	}
}
void drawPrototypeEnemies(char bg[30][60],int sec,int &oldSec){
	//day la phan dieu khien. cactus se xuat hien theo ti le 1/5 va thoa man dk cac cactus cach nhau it nhat 10 spaces.
	if(enemiesControl() == true && sec - oldSec >= 10){
		drawCactus(58,bg);
		oldSec = sec;	// quy tac o day: thoi gian xuat hien cactus phai cach nhau it nhat la 10 sec. phan if se ktra neu nho hon 10 sec thi khong hoat dong. 
	}
	
}
void drawDino(int dn,char bg[30][60]){
	bg[dn][20]='[';
	bg[dn-1][20]='[';
	bg[dn][21]=']';
	bg[dn-1][21]=']';
}
void drawInvisibleDino(int dn,char bg[30][60]){
	bg[dn][20]=' ';
	bg[dn-1][20]=' ';
	bg[dn][21]=' ';
	bg[dn-1][21]=' ';
}
void dinoJump(int &dn,char bg[30][60]){
	for(int i=0;i<30;i++){
		if(bg[i][20] == '[' && i > 1){
			drawInvisibleDino(dn--,bg);
			drawDino(dn,bg);
		}
	}
}
void dinoFall(int &dn,char bg[30][60]){
	for(int i=29;i>=0;i--){
		if(bg[i][20] == '[' && i < 30){
			drawInvisibleDino(dn++,bg);
			drawDino(dn,bg);
		}
	}
}

int main(){
	char isPlayAgain;	//de quyet dinh co choi lai khong
	//khoi tao tu dau
	cout<<"0000    0   00   0    0000\n0   0   0   0  0 0   0    0\n0   0   0   0   00   0    0\n0000    0   0    0    0000";
		cout<<"\n\n\n";
		cout<<setfill('-')<<setw(40)<<"PRESS SPACE BAR TO PLAY..."<<setw(30)<<"\n"<<setfill(' ');
		getch();
	do{
		system("cls"); //TextColor(7);
		//khoi tao nhung thu can thiet
		int enemies1 = 0;	//tao phan tinh diem
		char isJump;		//kiem tra nut bam cua ban phim
		int dn = 28;		//vi tri dau tien cua dino
		int sec = 0;		//tinh thoi gian (thuc ra la so lan nhay man hinh)
		int oldSec = sec;	//kiem tra lan cuoi xuat cactus, cai nay lam cho xuong rong xuat hien khong qua day dac
		srand(time(NULL));	//random
		char bg1[30][60];	//khoi tao mang de ve man hinh
		
		for(int i = 0;i < 30;i++){	//ve lai man hinh trong thoi diem ban dau
			for(int j = 0;j < 60; j++){
				if(i==0||i==29){
					bg1[i][j]='=';
				}else if((j==0&&i!=0&&i!=29)||(j==59&&i!=0&&i!=29)){
					bg1[i][j]='|';
				}else{
					bg1[i][j]=' ';
				}
			}
		}
		int jumpCount = 0; int jumpCount2;	//phuc vu cho viec nhay len va roi xuong
		bool isJumpControl = false;	//bien boolean xem có nhảy hay ko
		//khoi tao man hinh chinh
		
		//vòng lặp chính
		while(1){
			sec ++;
			gotoxy(0,0);
			drawPrototypeEnemies(bg1,sec,oldSec);
			drawDino(dn,bg1);
			sleep(0);
			if(kbhit()){
				isJump = getch();
				if(isJump == 32){
					isJumpControl = true;
				}
			}
			if(isJumpControl == true){
				if(jumpCount < 5){
					dinoJump(dn,bg1);
					jumpCount++;
					if(jumpCount == 5){
						jumpCount2 = 5;
					}
				}else if(jumpCount2 >= 0){
					dinoFall(dn,bg1);
					jumpCount2--;
					if(jumpCount2 == 0){
						jumpCount = 0;
						isJumpControl = false;
					}
				}	
			}
			drawEnemies(bg1,enemies1);
			drawGround(bg1);
			if(bg1[dn][21] == '*'||bg1[dn][20] == '*'||bg1[dn-1][21] == '*'||bg1[dn-1][20] == '*'){
				gotoxy(20,20);
				cout<<"GAME OVER";
				gotoxy(20,21);
				cout<<"+)press SPACE to try again";
				gotoxy(20,22);
				cout<<"+)press ESC to quit the game";
				isPlayAgain = getch();
				break;
			}
			
			//chuyen mau console
			gotoxy(0,31);
			cout<<"TIME:"<<sec<<setw(30)<<"POINT:"<< enemies1;	
			
//			if(sec % 150 == 0){
//				TextColor(rand()% 12);
//			}
			if(isPlayAgain == 27){
				return 0; 
			}
	    }
	}while(isPlayAgain == 32);
	
}


















