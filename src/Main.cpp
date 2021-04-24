#include "DarkGDK.h"
using namespace std;

typedef struct{
	int x;
	int y;
}Point;

int x_origin = 24+200;//menyimpan posisi awal window x
int y_origin = 20+50; //menyimpan posisi awal window y
int board[10][10];//menyimpan state board
Point move[61];//menyimpan langkah2 yang telah dijalankan sebelumnya
//int boardmove[10][10][61];
int turn;//menyimpan nilai giliran saat ini
int color[3];//menyimpan nilai warna player


//konversi koordinat x dari board ke sprite
int convert1x(int x){
	return (x-1)*41+x_origin;
}

//konversi koordinat y dari board ke sprite
int convert1y(int y){
	return (y-1)*41+y_origin;
}

//konversi koordinat x dari sprite ke board
int convert2x(int x){
	return ((x-x_origin)/41)+1;
}

//konversi koordinat y dari sprite ke board
int convert2y(int y){
	return ((y-y_origin)/41)+1;
}

//mengembalikan id sprite yang berada pada posisi x,y sprite
int returnid(int x, int y){
	int i;
	for (i=1;i<61;i++){
		if(!dbSpriteExist(i) || !dbSpriteVisible(i))break;
		if(dbSpriteX(i) == x && dbSpriteY(i) == y)
			return i;
	}
	if(dbSpriteX(61) == x && dbSpriteY(61) == y)return 61;
	if(dbSpriteX(62) == x && dbSpriteY(62) == y)return 62;
	if(dbSpriteX(63) == x && dbSpriteY(63) == y)return 63;
	if(dbSpriteX(64) == x && dbSpriteY(64) == y)return 64;
}

//mengembalikan board ke state awal
void start_board(){
     int i,j;
     for(i = 0;i<10;i++){
           for(j = 0;j<10;j++){
                 board[i][j] = 0;
           }
     }
	 for(i = 1;i<=60;i++){
		 dbHideSprite(i);
	}

     board[4][4] = color[1];
     board[5][5] = color[1];
     board[4][5] = color[2];
     board[5][4] = color[2];

	 dbSprite(61,convert1x(4),convert1y(4),color[1]);
	 dbSprite(62,convert1x(5),convert1y(5),color[1]);

	 dbSprite(63,convert1x(4),convert1y(5),color[2]);
	 dbSprite(64,convert1x(5),convert1y(4),color[2]);

}

int count(int player){
int count = 0;
int i,j;
	for(i = 1;i<9;i++){
           for(j = 1;j<9;j++){
		   if (board[i][j] == color[player]) count++;
           }
     }
	return count;
}

void updatescore(){
		int c; 
		c = count(1);
		dbSprite(120,55,225,(30+(c-(c%10))/10));
		dbSprite(121,95,225,(30+(c%10)));
		c = count(2);
		dbSprite(122,55,300,(30+(c-(c%10))/10));
		dbSprite(123,95,300,(30+(c%10)));
}

//menaruh piece 'player' ke dalam posisi LP dan membalikkan sesuai dengan aturan othello
void Taruh(Point LP,int player){
	
	int x,y;
	
	x = LP.x;y = LP.y;
	
	x++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage (returnid(convert1x(x),convert1y(y)),color[player]);
				board[x++][y] = color[player];
			}
		}
	}
	
	x = LP.x;y = LP.y;
	
	x++;y++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x++;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y+1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x++][y++] = color[player];
			}
		}
	}
	
	x = LP.x;y = LP.y;
	y++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y+1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x][y++] = color[player];
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x--;y++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x--;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y+1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x--][y++] = color[player];
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x--][y] = color[player];
			}
		}
	}

	x = LP.x;y = LP.y;
	x--;y--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x--;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y-1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x--][y--] = color[player];
			}
		}
	}
	
	x = LP.x;y = LP.y;
	y--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y-1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x][y--] = color[player];
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x++;y--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x++;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y-1;
			while(board[x][y] != color[player]){
				dbSetSpriteImage(returnid(convert1x(x),convert1y(y)),color[player]);
				board[x++][y--] = color[player];
			}
		}
	}

	x = LP.x;y = LP.y;
	dbShowSprite(turn);
	dbSprite(turn,convert1x(x),convert1y(y),color[player]);
	board[LP.x][LP.y] = color[player];
}

//Mengganti giliran pemain dan menunjukkannya pada layar
void changeplayer(int *player){
	if(*player == 1)*player = 2;
    else *player = 1;
	dbSetSpriteImage(69,color[*player]);
}

//melakukan pembatalan gerakan, giliran mundur 2x
void changestate(int t){
     int i;
     int pl = 2;
     start_board();
	 turn = 1;
     for(i = 1;i < t;i++){
		Taruh(move[i],pl);
        changeplayer(&pl);
		turn++;
     }
}

//Mengecek kelayakan peletakkan piece 'player' di posisi LP
//Mengembalian 0 jika tidak layak dan 1 jika layak
int Layak(Point LP,int player){
    if(LP.x < 1 || LP.x > 8 || LP.y < 1 || LP.y > 8 || board[LP.x][LP.y] != 0){
            return 0;
    }else{
         int x,y;
         
         x = LP.x;y = LP.y;
         x++;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 x++;
                 if(board[x][y] == color[player])return 1;
         }

         
         x = LP.x;y = LP.y;
         x++;y++;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 x++;y++;
                 if(board[x][y] == color[player])return 1;
         }
         
         x = LP.x;y = LP.y;
         y++;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 y++;
                 if(board[x][y] == color[player])return 1;
         }
         
         x = LP.x;y = LP.y;
         x--;y++;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 x--;y++;
                 if(board[x][y] == color[player])return 1;
         }
         
         x = LP.x;y = LP.y;
         x--;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 x--;
                 if(board[x][y] == color[player])return 1;
         }
         
         x = LP.x;y = LP.y;
         x--;y--;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 x--;y--;
                 if(board[x][y] == color[player])return 1;
         }
         
         x = LP.x;y = LP.y;
         y--;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 y--;
                 if(board[x][y] == color[player])return 1;
         }

         x = LP.x;y = LP.y;
         x++;y--;
         while(board[x][y] != 0 && board[x][y] != color[player]){
                 x++;y--;
                 if(board[x][y] == color[player])return 1;
         }
         return 0;
    }
}

//Mengkalkulasi penaruhan piece 'player' ke posisi LP
//mengembalikan jumlah piece yang akan didapatkan player
int Kalkulasi(Point LP,int player){
	int flip = 0;
	int x,y;
	
	/*kanan*/
	x = LP.x;y = LP.y;
	x++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			while(board[x][y] != color[player]){
				flip++;
				x++;
			}
		}
	}

	
	/*bawah*/
	x = LP.x;y = LP.y;
	y++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y+1;
			while(board[x][y] != color[player]){
				flip++;
				y++;
			}
		}
	}	

	/*kiri*/
	x = LP.x;y = LP.y;
	x--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			while(board[x][y] != color[player]){
				flip++;
				x--;
			}
		}
	}
	
	/*atas*/
	x = LP.x;y = LP.y;
	y--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y-1;
			while(board[x][y] != color[player]){
				flip++;
				y--;
			}
		}
	}
		
	/*kanan bawah*/
	x = LP.x;y = LP.y;
	x++;y++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x++;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y+1;
			while(board[x][y] != color[player]){
				flip++;
				x++;y++;
			}
		}
	}

	/*kiri bawah*/
	x = LP.x;y = LP.y;
	x--;y++;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x--;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y+1;
			while(board[x][y] != color[player]){
				flip++;
				x--;y++;
			}
		}
	}

	/*kiri atas*/
	x = LP.x;y = LP.y;
	x--;y--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x--;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y-1;
			while(board[x][y] != color[player]){
				flip++;
				x--;y--;
			}
		}
	}

	/*kanan atas*/
	x = LP.x;y = LP.y;
	x++;y--;
	if(board[x][y] != 0){
		while(board[x][y] != color[player]){
			x++;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y-1;
			while(board[x][y] != color[player]){
				flip++;
				x++;y--;
			}
		}
	}
	return flip;
}

//Menyelesaikan giliran player
void endturn(int *player,int *state){\
	int i,j;
	int cek = 0;
	Point P;
	changeplayer(player);
	turn++;
	for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(board[j][i] == 0 && Layak(P,*player))cek = 1;
			if(cek)break;
		}
		if(cek)break;
	}
	if(!cek){
		changeplayer(player);
		turn++;
		for(i = 1;i < 9;i++){
			for(j = 1;j < 9;j++){
				P.x = j;P.y = i;
				if(board[j][i] == 0 && Layak(P,*player))cek = 1;
				if(cek)break;
			}
			if(cek)break;
		}
	}
	if(!cek){
		*state = 3;
		updatescore();
		if(count(1) > count(2)){dbSprite ( 150, 0, 0, 60 );dbStretchSprite(150,45,45);dbSetSpriteAlpha(150,200);}
		else {dbSprite(150,0,0,61);dbStretchSprite(150,45,45);dbSetSpriteAlpha(150,200);}
	}
}


Point StupidTurnAI(int player){
	int i,j,cek;
	Point P;
	cek = 0;        
	for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player))cek = 1;
			if(cek)break;
		}
		if(cek)break;
	}
	return P;
}

//Melakukan pergerakan AI dengan algoritma greedy
//Mengembalikan posisi dengan piece maksimum
Point GreedyBySUM(int player){
	int i,j,k;
	Point P,Pmax;
	int max = 0;
	for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			k = Kalkulasi(P,player);
    			if(k > max){
    				max = k;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
	return Pmax;
}

Point GreedyByX(int player){
     int i,j,k;
	 Point P,Pmax;
	 int max = 5;
     for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			if(j == 1 || j == 8)k = 1;
    			else if(j == 2 || j == 7)k = 4;
				else if(j == 3 || j == 6)k = 2;
				else if(j == 4 || j == 5)k = 3;
    			if(k < max){
    				max = k;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
	return Pmax;
} 


Point GreedyByY(int player){
     int i,j,k;
	 Point P,Pmax;
	 int max = 5;
     for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			if(i == 1 || i == 8)k = 1;
    			else if(i == 2 || i == 7)k = 4;
				else if(i == 3 || i == 6)k = 2;
				else if(i == 4 || i == 5)k = 3;
    			if(k < max){
    				max = k;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
	return Pmax;
} 

Point GreedyCombo(int player){
     int i,j,a,b,ka,kb;
	 Point P,Pmax;
	 int maxa = 10;
	 int maxb = 0;
     for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			if(j == 1 || j == 8)a = 1;
    			else if(j == 2 || j == 7)a = 4;
				else if(j == 3 || j == 6)a = 2;
				else if(j == 4 || j == 5)a = 3;
    			
				if(i == 1 || i == 8)b = 1;
    			else if(i == 2 || i == 7)b = 4;
				else if(i == 3 || i == 6)b = 2;
				else if(i == 4 || i == 5)b = 3;

    			ka = a+b;
    			kb = Kalkulasi(P,player);
    			if(ka <= maxa){
					if(ka != maxa || kb > maxb){
						maxa = ka;
						maxb = kb;
						Pmax.x = P.x;
						Pmax.y = P.y;
					}
    			}
            }
		}
	}
	return Pmax;
} 



/*void backtrack(){
}

void re_start(){
}*/

void DarkGDK ( void )
{	
	int img[3];//menyimpan id image yang dipakai untuk player 1 dan player 2
	int user1 = 0; // user1 bermain menjadi nilai, 0 = tidak bermain
	int user2 = 0; // user2 bermain menjadi nilai, 0 = tidak bermain
	int ai1 = 1; // ai1 bermain menjadi nilai, 0 = tidak bermain
	int ai2 = 2; // ai2 bermain menjadi nilai, 0 = tidak bermain
	int aimode1 = 0; //0 = Greedy by SUM, 1 = Greedy by X, 2 = Greedy by Y, 3 = Greedy Kombinasi
	int aimode2 = 0;
	int state = 0; //State Permainan, 0 = main menu,1 = menu pilihan,2 = permainan,3 = permainan selesai
	int delay = 1000;

	dbSetImageColorKey ( 255, 0, 255 );
	int mouse_state = 0;
	int key_state = 0;
	int x;
	int y;
	int tawal,t;
    Point LP;/*Last Play*/
    int player = 2; //yang jalan pertama
	int posisix;
	int posisiy;
	
	//gambar background
	dbLoadImage ( "background1.bmp", 80 );
	dbLoadImage ( "background2.bmp", 81 );
	dbLoadImage ( "baru.png", 82 );
	
	//gambar blank
	dbLoadImage ( "blank.png", 99 );
	
	//gambar pilihan pada menu
	dbLoadImage ( "chose_black.png", 41 );
	dbLoadImage ( "chose_blue.png", 43 );
	dbLoadImage ( "chose_green.png", 42 );
	dbLoadImage ( "chose_red.png", 44 );
	dbLoadImage ( "chose_white.png", 40 );
	dbLoadImage ( "apakek2.png", 45 );
	dbLoadImage ( "human.png", 46 );
	dbLoadImage ( "by_many.png", 47 );
	dbLoadImage ( "by_x.png", 48 );
	dbLoadImage ( "by_smua.png", 49 );
	dbLoadImage ( "vs.png", 50 );
	dbLoadImage ( "by_y.png", 51 );
	
	//gambar angka
	dbLoadImage ( "0.png", 30 );
	dbLoadImage ( "1.png", 31 );
	dbLoadImage ( "2.png", 32 );
	dbLoadImage ( "3.png", 33 );
	dbLoadImage ( "4.png", 34 );
	dbLoadImage ( "5.png", 35 );
	dbLoadImage ( "6.png", 36 );
	dbLoadImage ( "7.png", 37 );
	dbLoadImage ( "8.png", 38 );
	dbLoadImage ( "9.png", 39 );

	//gambar pada menu permainan
	dbLoadImage ( "blackboard.png", 10 );
	dbLoadImage ( "apakek.png",11);
	dbLoadImage ( "side_panel.png", 98 );
	
	//gambar bola
	dbLoadImage ( "bola putih.png", 1 );//bola ijo = p1
	dbLoadImage ( "bola item.png", 2);//bola xxx = p2
	dbLoadImage ( "bola ijo.png", 3);
	dbLoadImage ( "bola biru.png", 4);
	dbLoadImage ( "bola merah.png", 5);
	
	//gambar kemenangan
	dbLoadImage ( "wins_P1.png", 60);
	dbLoadImage ( "wins_P2.png", 61);
	
	//gambar kecepatan
	dbLoadImage ( "fastest.png", 62);
	dbLoadImage ( "faster.png", 63);
	dbLoadImage ( "normal.png", 64);
	
	//gambar maju-mundur
	dbLoadImage ( "maju.png", 65);
	dbLoadImage ( "mundur.png", 66);
	
	dbLoadImage ( "main_menu.jpg",6);//menu utama
	dbLoadImage ( "menu pilihan.png",7);//menu pilihan
	
	dbLoadImage ( "star_but.png",8);
	dbLoadImage ( "quit_but.png",9);
	dbSyncOn   ( );
	dbSyncRate ( 60 );
	dbDisableEscapeKey ( );
	dbRandomize ( dbTimer ( ) );
	dbSetWindowTitle ( "oThelo - oTak hebat othello" );
	
	state = 0;
	dbSprite ( 73, 0, 0, 6 );
	dbSprite ( 74, 100, 350, 8);
	dbSprite ( 75, 400, 350, 9);
	dbStretchSprite(73,45,45);
	dbSizeSprite(74,150,100);
	dbSizeSprite(75,150,75);

	int r;
	r = rand();
	r = r % 3;

	
	

	while ( LoopGDK ( ) ){
		
		if(state == 0){
			if ((dbMouseX() >= dbSpriteX(74)) && (dbMouseX() <= dbSpriteX(74)+dbSpriteWidth(74)) && (dbMouseY() >= dbSpriteY(74)) && (dbMouseY() <= dbSpriteY(74)+dbSpriteHeight(74))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					
					dbDeleteSprite(74);
					dbDeleteSprite(75);

					dbSprite ( 73, 0, 0, 7 );
					dbStretchSprite(73,90,77);

					//gambar human-computer P1
					dbSprite ( 130, 30, 100, 46 );
					dbStretchSprite(130,40,40);
					dbSprite ( 131, 30, 150, 47 );
					dbStretchSprite(131,40,40);
					dbSprite ( 135, 30, 200, 48 );
					dbStretchSprite(135,40,40);
					dbSprite ( 136, 80, 100, 51 );
					dbStretchSprite(136,40,40);
					dbSprite ( 137, 80, 150, 49 );
					dbStretchSprite(137,40,40);

					//gambar bola2 yang bisa diklik P1
					dbSprite ( 100, 30, 320, 40 );
					dbStretchSprite(100,40,40);
					dbSprite ( 101, 70, 320, 41 );
					dbStretchSprite(101,40,40);
					dbSprite ( 102, 110, 320, 42 );
					dbStretchSprite(102,40,40);
					dbSprite ( 103, 150, 320, 43 );
					dbStretchSprite(103,40,40);
					dbSprite ( 104, 190, 320, 44 );
					dbStretchSprite(104,40,40);
					
					//gambar tombol start
					dbSprite ( 199, 250, 160, 50 );
					dbStretchSprite(199,30,30);
					
					//gambar human-computer P2
					dbSprite ( 132, 420, 230, 46 );
					dbStretchSprite(132,40,40);
					dbSprite ( 134, 420, 280, 47 );
					dbStretchSprite(134,40,40);
					dbSprite ( 138, 420, 330, 48 );
					dbStretchSprite(138,40,40);
					dbSprite ( 139, 470, 280, 49 );
					dbStretchSprite(139,40,40);
					dbSprite ( 140, 470, 230, 51 );
					dbStretchSprite(140,40,40);
					
					//gambar bola2 yang bisa diklik P2
					dbSprite ( 105, 420, 440, 40 );
					dbStretchSprite(105,40,40);
					dbSprite ( 106, 460, 440, 41 );
					dbStretchSprite(106,40,40);
					dbSprite ( 107, 500, 440, 42 );
					dbStretchSprite(107,40,40);
					dbSprite ( 108, 540, 440, 43 );
					dbStretchSprite(108,40,40);
					dbSprite ( 109, 580, 440, 44 );
					dbStretchSprite(109,40,40);
					
					//selektor bola P1
					dbSprite ( 110, 27, 317, 45 );
					dbStretchSprite(110,85,85);
					
					//selektor greedy P1
					dbSprite ( 112, 26, 96, 45 );
					dbStretchSprite(112,120,120);

					//selektor bola P2
					dbSprite ( 113, 457, 437, 45 );
					dbStretchSprite(113,85,85);
					
					//selektor greedy P2
					dbSprite ( 111, 416, 226, 45 );
					dbStretchSprite(111,120,120);
					
					state = 1;
					mouse_state = 1;
				}
			}
			if ((dbMouseX() >= dbSpriteX(75)) && (dbMouseX() <= dbSpriteX(75)+dbSpriteWidth(75)) && (dbMouseY() >= dbSpriteY(75)) && (dbMouseY() <= dbSpriteY(75)+dbSpriteHeight(75))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					return;
					state = 1;
					mouse_state = 1;
				}
			}
			if(dbMouseClick()==0){
				mouse_state=0;
			}
		}
		if(state == 1){
			if ((dbMouseX() >= dbSpriteX(199)) && (dbMouseX() <= dbSpriteX(199)+dbSpriteWidth(199)) && (dbMouseY() >= dbSpriteY(199)) && (dbMouseY() <= dbSpriteY(199)+dbSpriteHeight(199))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					user1 = 0;
					user2 = 0;
					ai1 = 0;
					ai2 = 0;
				
					int a = (((dbSpriteY(112) - 96)/50) + 1);
					int b = (((dbSpriteX(112) - 26)/50) + 1);
					if(a == 1 && b == 1){
						user1 = (((dbSpriteX(110) - 27)/40) + 1);
						color[1] = user1;
					}
					else if(a == 2 && b == 1){
						ai1 = (((dbSpriteX(110) - 27)/40) + 1);
						aimode1 = 0;
						color[1] = ai1;
					}
					else if(a == 3 && b == 1){
						ai1 = (((dbSpriteX(110) - 27)/40) + 1);
						aimode1 = 1;
						color[1] = ai1;
					}
					else if(a == 1 && b == 2){
						ai1 = (((dbSpriteX(110) - 27)/40) + 1);
						aimode1 = 2;
						color[1] = ai1;
					}
					else if(a == 2 && b == 2){
						ai1 = (((dbSpriteX(110) - 27)/40) + 1);
						aimode1 = 3;
						color[1] = ai1;
					}
					
					a = (((dbSpriteY(111) - 226)/50) + 1);
					b = (((dbSpriteX(111) - 416)/50) + 1);
					if(a == 1 && b == 1) {
						user2 = (((dbSpriteX(113) - 417)/40) + 1);
						color[2] = user2;
					}
					else if(a == 2 && b == 1){
						ai2 = (((dbSpriteX(113) - 417)/40) + 1);
						aimode2 = 0;
						color[2] = ai2;
					}
					else if(a == 3 && b == 1){
						ai2 = (((dbSpriteX(113) - 417)/40) + 1);
						aimode2 = 1;
						color[2] = ai2;
					}
					else if(a == 1 && b == 2){
						ai2 = (((dbSpriteX(113) - 417)/40) + 1);
						aimode2 = 2;
						color[2] = ai2;
					}
					else if(a == 2 && b == 2){
						ai2 = (((dbSpriteX(113) - 417)/40) + 1);
						aimode2 = 3;
						color[2] = ai2;
					}
					if(color[1] != color[2]){
						r = rand();
						r = r % 3;
						if (r == 0){dbSprite ( 70, 0, 0, 80 );dbStretchSprite(70,100,100);}
						if (r == 1){dbSprite ( 70, 0, 0, 81 );dbStretchSprite(70,100,100);}
						if (r == 2){dbSprite ( 70, 0, 0, 82 );dbStretchSprite(70,50,50);}
						
						dbDeleteSprite(73);
						dbDeleteSprite(130);
						dbDeleteSprite(131);
						dbDeleteSprite(100);
						dbDeleteSprite(101);
						dbDeleteSprite(102);
						dbDeleteSprite(103);
						dbDeleteSprite(104);
						dbDeleteSprite(105);
						dbDeleteSprite(106);
						dbDeleteSprite(107);
						dbDeleteSprite(108);
						dbDeleteSprite(109);
						dbDeleteSprite(110);
						dbDeleteSprite(111);
						dbDeleteSprite(112);
						dbDeleteSprite(113);
						dbDeleteSprite(130);
						dbDeleteSprite(131);
						dbDeleteSprite(132);
						dbDeleteSprite(133);
						dbDeleteSprite(134);
						dbDeleteSprite(135);
						dbDeleteSprite(136);
						dbDeleteSprite(137);
						dbDeleteSprite(138);
						dbDeleteSprite(139);
						dbDeleteSprite(140);
						dbDeleteSprite(199);
						

						dbSprite ( 71, 200, 50,10);
						dbSprite ( 250, 0, 0,98);
						dbStretchSprite ( 250, 40, 40);
						dbSprite ( 151, 190, 455,62);
						dbStretchSprite(151,30,30);
						dbSprite ( 152, 150, 455,63);
						dbStretchSprite(152,30,30);
						dbSprite ( 153, 130, 455,64);
						dbStretchSprite(153,30,30);
						
						//sprite mundur
						dbSprite ( 154, 40, 415,66);
						dbStretchSprite(154,40,40);
						//sprite maju
						dbSprite ( 155, 120, 415,65);
						dbStretchSprite(155,40,40);
						
						dbSprite ( 69, 75, 375, color[2]);
						turn = 1;
						start_board();
						
						state = 2;
					}
				}
			}
			if ((dbMouseX() >= dbSpriteX(100)) && (dbMouseX() <= dbSpriteX(100)+dbSpriteWidth(100)) && (dbMouseY() >= dbSpriteY(100)) && (dbMouseY() <= dbSpriteY(100)+dbSpriteHeight(100))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 110, 27, 317, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(101)) && (dbMouseX() <= dbSpriteX(101)+dbSpriteWidth(101)) && (dbMouseY() >= dbSpriteY(101)) && (dbMouseY() <= dbSpriteY(101)+dbSpriteHeight(101))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 110, 27+40, 317, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(102)) && (dbMouseX() <= dbSpriteX(102)+dbSpriteWidth(102)) && (dbMouseY() >= dbSpriteY(102)) && (dbMouseY() <= dbSpriteY(102)+dbSpriteHeight(102))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 110, 27+80, 317, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(103)) && (dbMouseX() <= dbSpriteX(103)+dbSpriteWidth(103)) && (dbMouseY() >= dbSpriteY(103)) && (dbMouseY() <= dbSpriteY(103)+dbSpriteHeight(103))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 110, 27+120, 317, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(104)) && (dbMouseX() <= dbSpriteX(104)+dbSpriteWidth(104)) && (dbMouseY() >= dbSpriteY(104)) && (dbMouseY() <= dbSpriteY(104)+dbSpriteHeight(104))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 110, 27+160, 317, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(130)) && (dbMouseX() <= dbSpriteX(130)+dbSpriteWidth(130)) && (dbMouseY() >= dbSpriteY(130)) && (dbMouseY() <= dbSpriteY(130)+dbSpriteHeight(130))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 112, 26, 96, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(131)) && (dbMouseX() <= dbSpriteX(131)+dbSpriteWidth(131)) && (dbMouseY() >= dbSpriteY(131)) && (dbMouseY() <= dbSpriteY(131)+dbSpriteHeight(131))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 112, 26, 96+50, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(135)) && (dbMouseX() <= dbSpriteX(135)+dbSpriteWidth(135)) && (dbMouseY() >= dbSpriteY(135)) && (dbMouseY() <= dbSpriteY(135)+dbSpriteHeight(135))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 112, 26, 96+100, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(136)) && (dbMouseX() <= dbSpriteX(136)+dbSpriteWidth(136)) && (dbMouseY() >= dbSpriteY(136)) && (dbMouseY() <= dbSpriteY(136)+dbSpriteHeight(136))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 112, 26+50, 96, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(137)) && (dbMouseX() <= dbSpriteX(137)+dbSpriteWidth(137)) && (dbMouseY() >= dbSpriteY(137)) && (dbMouseY() <= dbSpriteY(137)+dbSpriteHeight(137))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 112, 26+50, 96+50, 45 );
				}
			}
			
			if ((dbMouseX() >= dbSpriteX(105)) && (dbMouseX() <= dbSpriteX(105)+dbSpriteWidth(105)) && (dbMouseY() >= dbSpriteY(105)) && (dbMouseY() <= dbSpriteY(105)+dbSpriteHeight(105))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 113, 417, 437, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(106)) && (dbMouseX() <= dbSpriteX(106)+dbSpriteWidth(106)) && (dbMouseY() >= dbSpriteY(106)) && (dbMouseY() <= dbSpriteY(106)+dbSpriteHeight(106))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 113, 417+40, 437, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(107)) && (dbMouseX() <= dbSpriteX(107)+dbSpriteWidth(107)) && (dbMouseY() >= dbSpriteY(107)) && (dbMouseY() <= dbSpriteY(107)+dbSpriteHeight(107))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 113, 417+80, 437, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(108)) && (dbMouseX() <= dbSpriteX(108)+dbSpriteWidth(108)) && (dbMouseY() >= dbSpriteY(108)) && (dbMouseY() <= dbSpriteY(108)+dbSpriteHeight(108))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 113, 417+120, 437, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(109)) && (dbMouseX() <= dbSpriteX(109)+dbSpriteWidth(109)) && (dbMouseY() >= dbSpriteY(109)) && (dbMouseY() <= dbSpriteY(109)+dbSpriteHeight(109))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 113, 417+160, 437, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(132)) && (dbMouseX() <= dbSpriteX(132)+dbSpriteWidth(132)) && (dbMouseY() >= dbSpriteY(132)) && (dbMouseY() <= dbSpriteY(132)+dbSpriteHeight(132))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 111, 416, 226, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(134)) && (dbMouseX() <= dbSpriteX(134)+dbSpriteWidth(134)) && (dbMouseY() >= dbSpriteY(134)) && (dbMouseY() <= dbSpriteY(134)+dbSpriteHeight(134))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 111, 416, 226+50, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(138)) && (dbMouseX() <= dbSpriteX(138)+dbSpriteWidth(138)) && (dbMouseY() >= dbSpriteY(138)) && (dbMouseY() <= dbSpriteY(138)+dbSpriteHeight(138))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 111, 416, 226+100, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(139)) && (dbMouseX() <= dbSpriteX(139)+dbSpriteWidth(139)) && (dbMouseY() >= dbSpriteY(139)) && (dbMouseY() <= dbSpriteY(139)+dbSpriteHeight(139))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 111, 416+50, 226+50, 45 );
				}
			}
			if ((dbMouseX() >= dbSpriteX(140)) && (dbMouseX() <= dbSpriteX(140)+dbSpriteWidth(140)) && (dbMouseY() >= dbSpriteY(140)) && (dbMouseY() <= dbSpriteY(140)+dbSpriteHeight(140))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					dbSprite ( 111, 416+50, 226, 45 );
				}
			}
			if(dbMouseClick()==0){
				mouse_state=0;
			}
		}
		if(state == 2){
			updatescore();
				
				//mundur
				if ((dbMouseX() >= dbSpriteX(154)) && (dbMouseX() <= dbSpriteX(154)+dbSpriteWidth(154)) && (dbMouseY() >= dbSpriteY(154)) && (dbMouseY() <= dbSpriteY(154)+dbSpriteHeight(154))){  
					if(dbMouseClick()==1 && mouse_state == 0){
							tawal = turn;
							t = turn-1;
							changestate(t);
							state = 4;
							mouse_state = 1;
					}
				}
				
				//cepat					
				if ((dbMouseX() >= dbSpriteX(151)) && (dbMouseX() <= dbSpriteX(151)+dbSpriteWidth(151)) && (dbMouseY() >= dbSpriteY(151)) && (dbMouseY() <= dbSpriteY(151)+dbSpriteHeight(151))){  
					if(dbMouseClick()==1 && mouse_state == 0){
						mouse_state = 1;
						delay = 100;
					}
				}
					//sedang
				if ((dbMouseX() >= dbSpriteX(152)) && (dbMouseX() <= dbSpriteX(152)+dbSpriteWidth(152)) && (dbMouseY() >= dbSpriteY(152)) && (dbMouseY() <= dbSpriteY(152)+dbSpriteHeight(152))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					mouse_state = 1;
					delay = 500;
				}
				}
					//lambat
				if ((dbMouseX() >= dbSpriteX(153)) && (dbMouseX() <= dbSpriteX(153)+dbSpriteWidth(153)) && (dbMouseY() >= dbSpriteY(153)) && (dbMouseY() <= dbSpriteY(153)+dbSpriteHeight(153))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					mouse_state = 1;
					delay = 1000;
				}
				}
				if(dbMouseClick()==0){
				mouse_state=0;
			}
			if(color[player] == user1 || color[player] == user2){
				
				posisix = dbMouseX();
				posisiy = dbMouseY();
		
				LP.x = convert2x(posisix);
				LP.y = convert2y(posisiy);

				if(Layak(LP,player)){
					dbShowSprite(72);
					dbSprite(72,convert1x(LP.x),convert1y(LP.y),11);
				}
				if(dbMouseClick()==1 && mouse_state == 0){
					mouse_state=1;
						if(Layak(LP,player)){
							Taruh(LP,player);
							move[turn] = LP;
							endturn(&player,&state);
							dbHideSprite(72);
						}
				}
				if(dbMouseClick()==0){
					mouse_state=0;
				}
			}else{
				if(color[player] == ai1){
					dbSleep(delay);
					if(aimode1 == 0)LP = GreedyBySUM(player);
					else if(aimode1 == 1)LP = GreedyByX(player);
					else if(aimode1 == 2)LP = GreedyByY(player);
					else if(aimode1 == 3)LP = GreedyCombo(player);
					Taruh(LP,player);
					move[turn] = LP;
					endturn(&player,&state);
				}
				if(color[player] == ai2){
					dbSleep(delay);
					if(aimode2 == 0)LP = GreedyBySUM(player);
					else if(aimode2 == 1)LP = GreedyByX(player);
					else if(aimode2 == 2)LP = GreedyByY(player);
					else if(aimode2 == 3)LP = GreedyCombo(player);
					Taruh(LP,player);
					move[turn] = LP;
					endturn(&player,&state);
				}
			}
			if ( dbEscapeKey ( ) && key_state == 0){
				changestate(turn-2);
				key_state = 1;
				//break;
			}
			if ( !dbEscapeKey())key_state = 0;
		}
		
		if(state == 3){
			if(dbMouseClick() == 0){
				mouse_state = 0;
			}
			if(dbMouseClick() == 1 && mouse_state == 0){
				//dbDeleteSprite(73);
				dbSprite ( 73, 0, 0, 7 );
				dbStretchSprite(73,90,77);

				//gambar human-computer P1
					dbSprite ( 130, 30, 100, 46 );
					dbStretchSprite(130,40,40);
					dbSprite ( 131, 30, 150, 47 );
					dbStretchSprite(131,40,40);
					dbSprite ( 135, 30, 200, 48 );
					dbStretchSprite(135,40,40);
					dbSprite ( 136, 80, 100, 51 );
					dbStretchSprite(136,40,40);
					dbSprite ( 137, 80, 150, 49 );
					dbStretchSprite(137,40,40);

					//gambar bola2 yang bisa diklik P1
					dbSprite ( 100, 30, 320, 40 );
					dbStretchSprite(100,40,40);
					dbSprite ( 101, 70, 320, 41 );
					dbStretchSprite(101,40,40);
					dbSprite ( 102, 110, 320, 42 );
					dbStretchSprite(102,40,40);
					dbSprite ( 103, 150, 320, 43 );
					dbStretchSprite(103,40,40);
					dbSprite ( 104, 190, 320, 44 );
					dbStretchSprite(104,40,40);
					
					//gambar tombol start
					dbSprite ( 199, 250, 160, 50 );
					dbStretchSprite(199,30,30);
					
					//gambar human-computer P2
					dbSprite ( 132, 420, 230, 46 );
					dbStretchSprite(132,40,40);
					dbSprite ( 134, 420, 280, 47 );
					dbStretchSprite(134,40,40);
					dbSprite ( 138, 420, 330, 48 );
					dbStretchSprite(138,40,40);
					dbSprite ( 139, 470, 280, 49 );
					dbStretchSprite(139,40,40);
					dbSprite ( 140, 470, 230, 51 );
					dbStretchSprite(140,40,40);
				
				//gambar bola2 yang bisa diklik P2
				dbSprite ( 105, 420, 440, 40 );
				dbStretchSprite(105,40,40);
				dbSprite ( 106, 460, 440, 41 );
				dbStretchSprite(106,40,40);
				dbSprite ( 107, 500, 440, 42 );
				dbStretchSprite(107,40,40);
				dbSprite ( 108, 540, 440, 43 );
				dbStretchSprite(108,40,40);
				dbSprite ( 109, 580, 440, 44 );
				dbStretchSprite(109,40,40);
				
				//selektor bola P1
				dbSprite ( 110, 27, 317, 45 );
				dbStretchSprite(110,85,85);
				
				//selektor greedy P1
				dbSprite ( 112, 26, 96, 45 );
				dbStretchSprite(112,120,120);

				//selektor bola P2
				dbSprite ( 113, 457, 437, 45 );
				dbStretchSprite(113,85,85);
				
				//selektor greedy P2
				dbSprite ( 111, 416, 226, 45 );
				dbStretchSprite(111,120,120);

				dbDeleteSprite(150);
				state = 1;
			}
		}
		if(state == 4){
			if(dbMouseClick()==0)mouse_state = 0;
			if ((dbMouseX() >= dbSpriteX(154)) && (dbMouseX() <= dbSpriteX(154)+dbSpriteWidth(154)) && (dbMouseY() >= dbSpriteY(154)) && (dbMouseY() <= dbSpriteY(154)+dbSpriteHeight(154))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					changestate(--t);
					mouse_state = 1;
				}
			}				
			//maju
			if ((dbMouseX() >= dbSpriteX(155)) && (dbMouseX() <= dbSpriteX(155)+dbSpriteWidth(155)) && (dbMouseY() >= dbSpriteY(155)) && (dbMouseY() <= dbSpriteY(155)+dbSpriteHeight(155))){  
				if(dbMouseClick()==1 && mouse_state == 0){
					changestate(++t);
					if(t == tawal)state = 2;
					mouse_state = 1;
				}
			}
		}
		dbSync ( );
	}
	dbDeleteImage ( 1 );
	return;
}
