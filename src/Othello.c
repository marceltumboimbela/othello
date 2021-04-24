#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <time.h>


typedef struct{
        int x;
        int y;
}point;

int board[10][10];
int end = 0;
point move[64];
int turn;

void print_board(){
	int i,j;
	int w = 0,b = 0;
	printf(" |1|2|3|4|5|6|7|8|\n------------------\n");
	for(i = 1;i<9;i++){
		printf("%d|",i);
		for(j = 1;j<9;j++){
			switch(board[j][i]){
				case 0 : printf(" |");break;
				case 1 : printf("W|");w++;break;
				case 2 : printf("B|");b++;break;
			}
		}
		printf("\n------------------\n");
	}
	printf("White : %d\tBlack : %d\n",w,b);
	if(end){
		printf("permainan berakhir\n");
		if(w == b)printf("seri");
		else if(w > b)printf("White menang\n");
		else if(w < b)printf("Black menang");
	}
}

void start_board(){
     int i,j;
     for(i = 0;i<10;i++){
           for(j = 0;j<10;j++){
                 board[i][j] = 0;
           }
     }
     board[4][4] = 1;
     board[5][5] = 1;
     board[4][5] = 2;
     board[5][4] = 2;
}

void Taruh(point LP,int player){
	int x,y;
	
	x = LP.x;y = LP.y;
	x++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			while(board[x][y] != player){
				board[x++][y] = player;
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x++;y++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x++;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y+1;
			while(board[x][y] != player){
				board[x++][y++] = player;
			}
		}
	}
	
	x = LP.x;y = LP.y;
	y++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y+1;
			while(board[x][y] != player){
				board[x][y++] = player;
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x--;y++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x--;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y+1;
			while(board[x][y] != player){
				board[x--][y++] = player;
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			while(board[x][y] != player){
				board[x--][y] = player;
			}
		}
	}

	x = LP.x;y = LP.y;
	x--;y--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x--;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y-1;
			while(board[x][y] != player){
				board[x--][y--] = player;
			}
		}
	}
	
	x = LP.x;y = LP.y;
	y--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y-1;
			while(board[x][y] != player){
				board[x][y--] = player;
			}
		}
	}
	
	x = LP.x;y = LP.y;
	x++;y--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x++;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y-1;
			while(board[x][y] != player){
				board[x++][y--] = player;
			}
		}
	}
	board[LP.x][LP.y] = player;
}

void changeplayer(int *player){
	if(*player == 1)*player = 2;
    else *player = 1;
}

void undomove(){
     int i;
     int pl = 2;
	 turn -= 2;
     start_board();
     for(i = 1;i < turn;i++){
        Taruh(move[i],pl);
        changeplayer(&pl);

     }
}

void PlayerPlay(point *LP){
     scanf("%d",&LP->x);
     while((LP->x) == 0){
          undomove();
          print_board();
          scanf("%d",&LP->x);          
     }
     scanf("%d",&LP->y);
}

int Layak(point LP,int player){
    if(LP.x < 1 || LP.x > 8 || LP.y < 1 || LP.y > 8 || board[LP.x][LP.y] != 0){
            return 0;
    }else{
         int x,y;
         
         x = LP.x;y = LP.y;
         x++;
         while(board[x][y] != 0 && board[x][y] != player){
                 x++;
                 if(board[x][y] == player)return 1;
         }

         
         x = LP.x;y = LP.y;
         x++;y++;
         while(board[x][y] != 0 && board[x][y] != player){
                 x++;y++;
                 if(board[x][y] == player)return 1;
         }
         
         x = LP.x;y = LP.y;
         y++;
         while(board[x][y] != 0 && board[x][y] != player){
                 y++;
                 if(board[x][y] == player)return 1;
         }
         
         x = LP.x;y = LP.y;
         x--;y++;
         while(board[x][y] != 0 && board[x][y] != player){
                 x--;y++;
                 if(board[x][y] == player)return 1;
         }
         
         x = LP.x;y = LP.y;
         x--;
         while(board[x][y] != 0 && board[x][y] != player){
                 x--;
                 if(board[x][y] == player)return 1;
         }
         
         x = LP.x;y = LP.y;
         x--;y--;
         while(board[x][y] != 0 && board[x][y] != player){
                 x--;y--;
                 if(board[x][y] == player)return 1;
         }
         
         x = LP.x;y = LP.y;
         y--;
         while(board[x][y] != 0 && board[x][y] != player){
                 y--;
                 if(board[x][y] == player)return 1;
         }

         x = LP.x;y = LP.y;
         x++;y--;
         while(board[x][y] != 0 && board[x][y] != player){
                 x++;y--;
                 if(board[x][y] == player)return 1;
         }
         return 0;
    }
}

int Kalkulasi(point LP,int player){
	int flip = 0;
	int x,y;
	
	/*kanan*/
	x = LP.x;y = LP.y;
	x++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			while(board[x][y] != player){
				flip++;
				x++;
			}
		}
	}

	
	/*bawah*/
	x = LP.x;y = LP.y;
	y++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y+1;
			while(board[x][y] != player){
				flip++;
				y++;
			}
		}
	}	

	/*kiri*/
	x = LP.x;y = LP.y;
	x--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			while(board[x][y] != player){
				flip++;
				x--;
			}
		}
	}
	
	/*atas*/
	x = LP.x;y = LP.y;
	y--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			y = LP.y-1;
			while(board[x][y] != player){
				flip++;
				y--;
			}
		}
	}
		
	/*kanan bawah*/
	x = LP.x;y = LP.y;
	x++;y++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x++;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y+1;
			while(board[x][y] != player){
				flip++;
				x++;y++;
			}
		}
	}

	/*kiri bawah*/
	x = LP.x;y = LP.y;
	x--;y++;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x--;y++;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y+1;
			while(board[x][y] != player){
				flip++;
				x--;y++;
			}
		}
	}

	/*kiri atas*/
	x = LP.x;y = LP.y;
	x--;y--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x--;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x-1;
			y = LP.y-1;
			while(board[x][y] != player){
				flip++;
				x--;y--;
			}
		}
	}

	/*kanan atas*/
	x = LP.x;y = LP.y;
	x++;y--;
	if(board[x][y] != 0){
		while(board[x][y] != player){
			x++;y--;
			if(board[x][y] == 0)break;
		}
		if(board[x][y] != 0){
			x = LP.x+1;
			y = LP.y-1;
			while(board[x][y] != player){
				flip++;
				x++;y--;
			}
		}
	}
	return flip;
}

void endturn(int *player){/*nanti ganti jadi input himpunan kandidat*/
	int i,j;
	int cek = 0;
	point P;
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
		for(i = 1;i < 9;i++){
			for(j = 1;j < 9;j++){
				P.x = j;P.y = i;
				if(board[j][i] == 0 && Layak(P,*player))cek = 1;
				if(cek)break;
			}
			if(cek)break;
		}
	}
	if(!cek)end = 1;
}

point PlayerTurn(player){
    point LP;
    PlayerPlay(&LP);
    while(!Layak(LP,player)){
    	printf("Penempatan piece tidak layak\n");
        print_board();
        PlayerPlay(&LP);
    }
    return LP;
}

point StupidTurnAI(player){
	int i,j,cek;
	point P;
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

point GreedyBySUM(player){
	int i,j,k;
	point P,Pmax;
	int max = 0;
	for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			k = Kalkulasi(P,player);
    			printf("%d,%d jumlah = %d\n",j,i,k);
    			if(k > max){
    				max = k;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
    system("pause");	
	return Pmax;
}

point GreedyByX(player){
     int i,j,k;
	 point P,Pmax;
	 int max = 5;
     for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			if(j <= 4)k = j;
    			else k = 9-j;
    			printf("%d,%d posisi = %d\n",j,i,k);
    			if(k < max){
    				max = k;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
    system("pause");	
	return Pmax;
} 


point GreedyByY(player){
     int i,j,k;
	 point P,Pmax;
	 int max = 5;
     for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			if(i <= 4)k = i;
    			else k = 9-i;
    			printf("%d,%d posisi = %d\n",j,i,k);
    			if(k < max){
    				max = k;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
    system("pause");	
	return Pmax;
} 

point GreedyCombo(player){
     int i,j,a,b,ka,kb;
	 point P,Pmax;
	 int maxa = 10;
	 int maxb = 0;
     for(i = 1;i < 9;i++){
		for(j = 1;j < 9;j++){
			P.x = j;P.y = i;
			if(Layak(P,player)){
    			if(j <= 4)a = j;
    			else a = 9-j;
    			if(i <= 4)b = i;
    			else b = 9-i;
    			ka = a+b;
    			kb = Kalkulasi(P,player);
    			printf("%d,%d posisi = %d\n",j,i,kb);
    			if(ka <= maxa && kb > maxb){
    				maxa = ka;
                    maxb = kb;
    				Pmax.x = P.x;
    				Pmax.y = P.y;
    			}
            }
		}
	}
    system("pause");	
	return Pmax;
} 



int main(){
    turn = 1;
    start_board();
    point LP;/*Last Play*/
    int player = 2;
    print_board();
    endturn(&player);
    while(!end){

        if(player == 1)LP = GreedyBySUM(player);
        else LP = GreedyCombo(player);

        move[turn++] = LP;
        Taruh(LP,player);

        printf("\nOpponent Last Play: %c,%d\n\n",move[turn-1].x+64,move[turn-1].y);
        changeplayer(&player);
        endturn(&player);
        print_board();
    }
        system("pause");
}
