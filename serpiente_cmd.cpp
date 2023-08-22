#include <windows.h>
#include <iostream>
#include <conio.h>

#define IZQUIERDA 75
#define DERECHA   77
#define ARRIBA    72
#define ABAJO     80

char SIZQ[] = {'<',0};
char SDER[] = {'>',0};
char SARB[] = {'A',0};
char SABJ[] = {'V',0};

// objeto - serpiente
class escamas{
	private:
		int posX, posY;
		char dir[1];
	public:
		int getPosX(){return posX;}
		int getPosY(){return posY;}
		char* getDir(){return dir;}
		void setPosX(int x){posX = x;}
		void setPosY(int y){posY = y;}
		void setDir(char c){dir[0] = c;}
		~escamas(){}
};

escamas serpiente[500];

// datos del juego
int Num_vidas = 3;
int larga_i = 5, larga_f = 5;
int sx = 47, sxi = 47;
int sy = 14, syi = 14;

// asteriodes
int comidaX[5] = {11,51,75,85,37};
int comidaY[5] = {20,11,6,15,22}; 

// datos del puntaje
int direccion = 1, experiencia = 0, puntaje = 0, nivel = 1, velocidad = 150;
bool condicion = false;

// pocision en la ventana
void gotoxy(int x,int y){
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void vidas(int v){
	gotoxy(2,1);
	printf("VIDAS %d",v);
}

// pintar contorno
void contorno(){
	for(int i=0;i<=100;i++){
		gotoxy(2+i,3); printf("-");
		gotoxy(2+i,28); printf("-");
	}
	for(int i=0;i<=23;i++){
		gotoxy(2,3+i+1); printf("|");
		gotoxy(102,3+i+1); printf("|");
	}
}

void serpiente_inicial(int x, int y){
	for(int i=0;i>larga_i;i-=2){
		serpiente[i].setPosX(x+i);
		serpiente[i].setPosY(y);
		serpiente[i].setDir(SIZQ[0]);
		gotoxy(serpiente[i].getPosX(),serpiente[i].getPosY());
	}
}

// borrar mapa al estrellarse
void borrar_mapa(){
	for(int i=3;i<28;i++){
		for(int j=1;j<104;j++){
			gotoxy(j,i); printf(" ");
		}
	}
	for(int i=0;i<larga_f;i++){
		serpiente[i].setPosX(0);
		serpiente[i].setPosY(0);
		serpiente[i].setDir(' ');
	}
	contorno();
	Sleep(50);
	sx = sxi; sy = syi;
	direccion = 1;
	printf("\a");
}

int numero_impar(int x){
	if(x<=101){
		if(x%2==0){
			return x+1;
		} else {
			return x;
		}
	}
}

char* direccion_S(int dir){
	switch(dir){
		case 1:
			return SIZQ;
			break;
		case 2:
			return SARB;
			break;
		case 3:
			return SDER;
			break;
		case 4:
			return SABJ;
			break;
	}
}

void movimiento_serpiente(){
	for(int i=0;i<larga_f-1;i++){
		gotoxy(serpiente[0].getPosX(),serpiente[0].getPosY()); printf(" ");
		serpiente[i].setPosX(serpiente[i+1].getPosX());
		serpiente[i].setPosY(serpiente[i+1].getPosY());
		gotoxy(serpiente[i].getPosX(),serpiente[i].getPosY());
	}
}

// logica del juego
void jugar(){
	// indicamos la cola de la serpiente
	gotoxy(serpiente[0].getPosX(),serpiente[0].getPosY()); printf("+");
	
	// imprimimos la comida
	gotoxy(comidaX[0],comidaY[0]); printf("%c",157);
	gotoxy(comidaX[1],comidaY[1]); printf("%c",157);
	gotoxy(comidaX[2],comidaY[2]); printf("%c",157);
	gotoxy(comidaX[3],comidaY[3]); printf("%c",157);
	gotoxy(comidaX[4],comidaY[4]); printf("%c",157);
	Sleep(velocidad);
	
	// movimiento de la serpiente
	if(kbhit()){
		unsigned char tecla = getch();
		switch(tecla){
			case IZQUIERDA:
				if(direccion==2 || direccion==4){
					direccion = 1;
				}
				break;
			case DERECHA:				
				if(direccion==2 || direccion==4){
					direccion = 3;	
				}
				break;
			case ARRIBA:
				if(direccion==1 || direccion==3){
					direccion = 2;	
				}
				break;
			case ABAJO:
				if(direccion==1 || direccion==3){
					direccion = 4;	
				}	
				break;
		}
	}
	
	// Aumento de tamaño
	if(condicion){
		larga_f++;
		condicion = false;
	} else {
		movimiento_serpiente();
	}

	// colision con las paredes
	if(sx<=2 || sx>=102 || sy<=3 || sy>=28) {
		Num_vidas--;
		borrar_mapa();
		serpiente_inicial(sx,sy);
		vidas(Num_vidas);
	}
	
	// colision con el cuerpo
	for(int i=2;i<larga_f;i++){
		if(sx==serpiente[i-2].getPosX() && sy==serpiente[i-2].getPosY()){
			Num_vidas--;
			borrar_mapa();
			serpiente_inicial(sx,sy);
			vidas(Num_vidas);
		}
	}
	
	// comer la comida
	for(int i=0; i<sizeof(comidaX);i++){
		if(comidaX[i]==sx && comidaY[i]==sy){
			condicion = true;
			gotoxy(sx,sy); puts(direccion_S(direccion));
			puntaje+=10;
			experiencia+=10;
			gotoxy(60,1); printf("PUNTAJE TOTAL %i",puntaje);
			comidaX[i] = (rand()%97)+4;
			comidaX[i] = numero_impar(comidaX[i]);
			comidaY[i] = (rand()%24)+4;
		}	
	}
	
	// movimiento constante
	switch(direccion){
		case 1:
			sx-=2;
			serpiente[larga_f-1].setPosX(sx);
			serpiente[larga_f-1].setPosY(sy);
			gotoxy(serpiente[larga_f-1].getPosX(),serpiente[larga_f-1].getPosY()); printf(SIZQ);
			break;
		case 2:
			sy--;
			serpiente[larga_f-1].setPosX(sx);
			serpiente[larga_f-1].setPosY(sy);
			gotoxy(serpiente[larga_f-1].getPosX(),serpiente[larga_f-1].getPosY()); printf(SARB);
			break;
		case 3:
			sx+=2;
			serpiente[larga_f-1].setPosX(sx);
			serpiente[larga_f-1].setPosY(sy);
			gotoxy(serpiente[larga_f-1].getPosX(),serpiente[larga_f-1].getPosY()); printf(SDER);
			break;
		case 4:
			sy++;
			serpiente[larga_f-1].setPosX(sx);
			serpiente[larga_f-1].setPosY(sy);
			gotoxy(serpiente[larga_f-1].getPosX(),serpiente[larga_f-1].getPosY()); printf(SABJ);
			break;
	}
	
	// subir nivel
	if(experiencia==100){
		nivel++;
		gotoxy(30,1); printf("NIVEL %i",nivel);
		if(velocidad>40){
			velocidad-=25;
		} else if(velocidad<=30){
			velocidad = 10;
		}
		gotoxy(90,1); printf("VELOCIDAD    ");
		gotoxy(90,1); printf("VELOCIDAD %i",velocidad);
		experiencia = 0;
	}
}

int main(){
	vidas(Num_vidas);
	gotoxy(30,1); printf("NIVEL %i",nivel);
	gotoxy(60,1); printf("PUNTAJE TOTAL %i",puntaje);
	gotoxy(90,1); printf("VELOCIDAD %i",velocidad);
	contorno();
	serpiente_inicial(sx,sy);
	getch();
	while(Num_vidas>0 && nivel<=10){
		jugar();
	}
	if(Num_vidas==0){
		borrar_mapa();
		gotoxy(45,12); printf("FIN DEL JUEGO");
	}
	Sleep(250);
	getch();
}
