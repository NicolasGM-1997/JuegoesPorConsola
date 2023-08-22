#include <windows.h>
#include <iostream>
#include <conio.h>

#define IZQUIERDA 75
#define DERECHA   77
#define ARRIBA    72
#define ABAJO     80

char avion_l1[] = {' ',' ',' ','^',' ',' ',' ',0};
char avion_l2[] = {' ',' ','/','|','\\',' ',' ',0};
char avion_l3[] = {' ','/','-','-','-','\\',' ',0};

char explosion_l1[] = {' ',' ',' ','*',' ',' ',' ',0};
char explosion_l2[] = {' ',' ','*','*','*',' ',' ',0};
char explosion_l3[] = {' ',' ',' ','*',' ',' ',' ',0};

char explosion_r1[] = {'*',' ','*','*','*',' ','*',0};
char explosion_r2[] = {' ','*',' ',' ',' ','*',' ',0};
char explosion_r3[] = {'*',' ','*','*','*',' ','*',0};

char borrar[] = {' ',' ',' ',' ',' ',' ',' ',0};

// datos del juego
int Num_vidas = 3;
int corazones = 3;
int ix = 50;
int iy = 25;

// disparo de la nave
int bala1=0,bala2=1,ib=0;
bool disparar = false;

// asteriodes
int asteroidesX[10] = { 6,10,15,27,38,47,66,71,84,91 };
int asteroidesY[10] = { 4,10,15,7,5,7,8,9,10,6 };

// datos del puntaje
int experiencia = 0, puntaje = 0, nivel = 1, velocidad = 100;
bool condicion = false;

void gotoxy(int x,int y){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void vidas(int vi){
	gotoxy(2,1);
	printf("VIDAS %d",vi);
}

void barra_salud(int n){
	gotoxy(100,1); printf(" ");
	gotoxy(101,1); printf(" ");
	gotoxy(102,1); printf(" ");
	
	for(int i=0; i<n; i++){
		gotoxy(100+i,1); printf("%c",3);
	}
}

void imprimir_avion(int x,int y){
	gotoxy(x,y); puts(avion_l1);
	gotoxy(x,y+1); puts(avion_l2);
	gotoxy(x,y+2); puts(avion_l3);
}

void borrar_avion(int x,int y){
	gotoxy(ix,iy); puts(borrar);
	gotoxy(ix,iy+1); puts(borrar);
	gotoxy(ix,iy+2); puts(borrar);
}

void explosion(){
	gotoxy(ix,iy); puts(explosion_l1);
	gotoxy(ix,iy+1); puts(explosion_l2);
	gotoxy(ix,iy+2); puts(explosion_l3);	
	Sleep(500);	
	gotoxy(ix,iy); puts(explosion_r1);
	gotoxy(ix,iy+1); puts(explosion_r2);
	gotoxy(ix,iy+2); puts(explosion_r3);
	Sleep(500);
	imprimir_avion(ix,iy);
}

// logica del juego
void jugar(){
	if(!disparar) ib = ix;
	// pocision inicial de asteroides
	gotoxy(asteroidesX[0],asteroidesY[0]); printf("%c",157);
	gotoxy(asteroidesX[1],asteroidesY[1]); printf("%c",157);
	gotoxy(asteroidesX[2],asteroidesY[2]); printf("%c",157);
	gotoxy(asteroidesX[3],asteroidesY[3]); printf("%c",157);
	gotoxy(asteroidesX[4],asteroidesY[4]); printf("%c",157);
	gotoxy(asteroidesX[5],asteroidesY[5]); printf("%c",157);
	gotoxy(asteroidesX[6],asteroidesY[6]); printf("%c",157);
	gotoxy(asteroidesX[7],asteroidesY[7]); printf("%c",157);
	gotoxy(asteroidesX[8],asteroidesY[8]); printf("%c",157);
	gotoxy(asteroidesX[9],asteroidesY[9]); printf("%c",157);

	gotoxy(ib+2,iy+bala2); printf("/");
	gotoxy(ib+3,iy+bala1); printf("^");
	gotoxy(ib+4,iy+bala2); printf("\\");
	
	Sleep(velocidad);
	
	// movimiento de los asteroides
	gotoxy(asteroidesX[0],asteroidesY[0]); printf(" ");
	gotoxy(asteroidesX[1],asteroidesY[1]); printf(" ");
	gotoxy(asteroidesX[2],asteroidesY[2]); printf(" ");
	gotoxy(asteroidesX[3],asteroidesY[3]); printf(" ");
	gotoxy(asteroidesX[4],asteroidesY[4]); printf(" ");
	gotoxy(asteroidesX[5],asteroidesY[5]); printf(" ");
	gotoxy(asteroidesX[6],asteroidesY[6]); printf(" ");
	gotoxy(asteroidesX[7],asteroidesY[7]); printf(" ");
	gotoxy(asteroidesX[8],asteroidesY[8]); printf(" ");
	gotoxy(asteroidesX[9],asteroidesY[9]); printf(" ");
	
	gotoxy(ib+2,iy+bala2); printf(" ");
	gotoxy(ib+3,iy+bala1); printf(" ");
	gotoxy(ib+4,iy+bala2); printf(" ");
	
	if(disparar==true){
		bala1--;
		bala2--;
	}
	
	if(iy+bala1 <= 5){
		bala1 = 0;
		bala2 = 1;
		disparar = false;
	}
	
	// colision de los asteroides
	if(asteroidesY[0]>25 || (asteroidesX[0]==ib+3 && iy+bala1<=asteroidesY[0]) ||
		(asteroidesX[0]==ib+2 && iy+bala2<=asteroidesY[0]) || (asteroidesX[0]==ib+4 && iy+bala2<=asteroidesY[0])){
		asteroidesY[0] = 4;
		asteroidesX[0] = (rand()%100)+6;
		if(asteroidesY[0] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[1]>25 || (asteroidesX[1]==ib+3 && iy+bala1<=asteroidesY[1]) ||
		(asteroidesX[1]==ib+2 && iy+bala2<=asteroidesY[1]) || (asteroidesX[1]==ib+4 && iy+bala2<=asteroidesY[1])){
		asteroidesY[1] = 4;
		asteroidesX[1] = (rand()%100)+6;
		if(asteroidesY[1] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[2]>25 || (asteroidesX[2]==ib+3 && iy+bala1<=asteroidesY[2]) ||
		(asteroidesX[2]==ib+2 && iy+bala2<=asteroidesY[2]) || (asteroidesX[2]==ib+4 && iy+bala2<=asteroidesY[2])){
		asteroidesY[2] = 4;
		asteroidesX[2] = (rand()%100)+6;
		if(asteroidesY[2] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[3]>25 || (asteroidesX[3]==ib+3 && iy+bala1<=asteroidesY[3])  ||
		(asteroidesX[3]==ib+2 && iy+bala2<=asteroidesY[3]) || (asteroidesX[3]==ib+4 && iy+bala2<=asteroidesY[3])){
		asteroidesY[3] = 4;
		asteroidesX[3] = (rand()%100)+6;
		if(asteroidesY[3] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[4]>25 || (asteroidesX[4]==ib+3 && iy+bala1<=asteroidesY[4]) ||
		(asteroidesX[4]==ib+2 && iy+bala2<=asteroidesY[4]) || (asteroidesX[4]==ib+4 && iy+bala2<=asteroidesY[4])){
		asteroidesY[4] = 4;
		asteroidesX[4] = (rand()%100)+6;
		if(asteroidesY[4] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[5]>25 || (asteroidesX[5]==ib+3 && iy+bala1<=asteroidesY[5]) ||
		(asteroidesX[5]==ib+2 && iy+bala2<=asteroidesY[5]) || (asteroidesX[5]==ib+4 && iy+bala2<=asteroidesY[5])){
		asteroidesY[5] = 4;
		asteroidesX[5] = (rand()%100)+6;
		if(asteroidesY[5] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[6]>25 || (asteroidesX[6]==ib+3 && iy+bala1<=asteroidesY[6])  ||
		(asteroidesX[6]==ib+2 && iy+bala2<=asteroidesY[6]) || (asteroidesX[6]==ib+4 && iy+bala2<=asteroidesY[6])){
		asteroidesY[6] = 4;
		asteroidesX[6] = (rand()%100)+6;
		if(asteroidesY[6] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[7]>25 || (asteroidesX[7]==ib+3 && iy+bala1<=asteroidesY[7]) ||
		(asteroidesX[7]==ib+2 && iy+bala2<=asteroidesY[7]) || (asteroidesX[7]==ib+4 && iy+bala2<=asteroidesY[7])){
		asteroidesY[7] = 4;
		asteroidesX[7] = (rand()%100)+6;
		if(asteroidesY[7] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[8]>25 || (asteroidesX[8]==ib+3 && iy+bala1<=asteroidesY[8])  ||
		(asteroidesX[8]==ib+2 && iy+bala2<=asteroidesY[8]) || (asteroidesX[8]==ib+4 && iy+bala2<=asteroidesY[8])){
		asteroidesY[8] = 4;
		asteroidesX[8] = (rand()%100)+6;
		if(asteroidesY[8] == 4){
			condicion = false;
		}
	}
	if(asteroidesY[9]>25 || (asteroidesX[9]==ib+3 && iy+bala1<=asteroidesY[9]) ||
		(asteroidesX[9]==ib+2 && iy+bala2<=asteroidesY[9]) || (asteroidesX[9]==ib+4 && iy+bala2<=asteroidesY[9])){
		asteroidesY[9] = 4;
		asteroidesX[9] = (rand()%100)+6;
		if(asteroidesY[9] == 4){
			condicion = false;
		}
	}
	
	// movimiento del avion
	if(kbhit()){
		unsigned char tecla = getch();
		switch(tecla){
			case IZQUIERDA:
				if(ix>4){
					borrar_avion(ix,iy);					
					ix-=3;					
					imprimir_avion(ix,iy);
				}
				break;
			case DERECHA:
				if(ix<96){
					borrar_avion(ix,iy);					
					ix+=3;					
					imprimir_avion(ix,iy);
				}
				break;
			case ARRIBA:
				if(iy>20){
					borrar_avion(ix,iy);
					iy-=1;
					imprimir_avion(ix,iy);
				}
				break;
			case ABAJO:
				if(iy<25){
					borrar_avion(ix,iy);
					iy+=1;
					imprimir_avion(ix,iy);
				}
				break;
			case ' ':
				disparar = true;
				break;
		}
	}
	// Golpes de los asteroides
	if((asteroidesX[0]>ix && asteroidesX[0]<ix+6 && asteroidesY[0]==iy-1) ||
		(asteroidesX[1]>ix && asteroidesX[1]<ix+6 && asteroidesY[1]==iy-1) ||
		(asteroidesX[2]>ix && asteroidesX[2]<ix+6 && asteroidesY[2]==iy-1) ||
		(asteroidesX[3]>ix && asteroidesX[3]<ix+6 && asteroidesY[3]==iy-1) ||
		(asteroidesX[4]>ix && asteroidesX[4]<ix+6 && asteroidesY[4]==iy-1) ||
		(asteroidesX[5]>ix && asteroidesX[5]<ix+6 && asteroidesY[5]==iy-1) ||
		(asteroidesX[6]>ix && asteroidesX[6]<ix+6 && asteroidesY[6]==iy-1) ||
		(asteroidesX[7]>ix && asteroidesX[7]<ix+6 && asteroidesY[7]==iy-1) ||
		(asteroidesX[8]>ix && asteroidesX[8]<ix+6 && asteroidesY[8]==iy-1) ||
		(asteroidesX[9]>ix && asteroidesX[9]<ix+6 && asteroidesY[9]==iy-1)) {
			corazones--;
			barra_salud(corazones);
			printf("\a");
		}
	imprimir_avion(ix,iy);
	
	if(!corazones){
		Num_vidas--;
		vidas(Num_vidas);
		explosion();
		corazones = 3;
		barra_salud(corazones);
	}
	
	// cambio de nivel
	if(!condicion){
		experiencia++;
		puntaje++;
		gotoxy(45,1); printf("PUNTAJE TOTAL %i",puntaje);
		condicion = true;
	}
	
	if(experiencia==25){
		nivel++;
		if(nivel<=25){
			gotoxy(25,1); printf("NIVEL %i",nivel);
		} else {
			gotoxy(25,1); printf("NIVEL MAXIMO");
		}
		borrar_avion(ix,iy);
		if(velocidad>=10){
			velocidad-=7;
		} else if(velocidad<10){
			velocidad = 5;
		}
		gotoxy(75,1); printf("VELOCIDAD    ");
		gotoxy(75,1); printf("VELOCIDAD %i",velocidad);
		imprimir_avion(ix,iy);
		experiencia = 0;
	}
	
	asteroidesY[0]++;asteroidesY[1]++;asteroidesY[2]++;asteroidesY[3]++;asteroidesY[4]++;
	asteroidesY[5]++;asteroidesY[6]++;asteroidesY[7]++;asteroidesY[8]++;asteroidesY[9]++;
}

int main(){
	vidas(Num_vidas);
	barra_salud(corazones);
	
	gotoxy(25,1); printf("NIVEL %i",nivel);
	gotoxy(45,1); printf("PUNTAJE TOTAL %i",puntaje);
	gotoxy(75,1); printf("VELOCIDAD %i",velocidad);
	
	imprimir_avion(ix,iy);
	
	while(Num_vidas>0 && nivel<=25){
		jugar();
	}
	
	if(nivel>25 || Num_vidas==0){
		borrar_avion(ix,iy);
		gotoxy(50,11); printf("FIN DEL JUEGO");
	}
	
	Sleep(2500);
	getch();
}
