#include<stdio.h>//printf
#include<windows.h>//manipular pantalla
#include<conio.h>//obtener datos teclado
#include<list>
#include <iostream>
using namespace std;
//POSICION TECLAS CODIGO ASCII
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESPACIO 255
int main();
void PintaGameOver();
//libreria borlan recreada a partir de windows.h
//manipular pantalla cmd
void gotoxy(int x, int y){
	HANDLE IdConsole;
	IdConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwpos;
	dwpos.X = x;
	dwpos.Y = y;
	
	SetConsoleCursorPosition(IdConsole, dwpos);
}

//funcion parpadeo cursor
void OcultarCursor(){
	HANDLE IdConsole;
	IdConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 2;
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(IdConsole,&cursor);	
}

void Limites(){
	//horizontales
	for(int i=2 ; i<78; i++){
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,33); printf("%c",205);
	}
	//verticales
	for(int i=4 ; i<33; i++){
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	
	//esquinas
	gotoxy(2,3); printf("%c",201);
	gotoxy(2,33); printf("%c",200);
	gotoxy(77,3); printf("%c",187);
	gotoxy(77,33); printf("%c",188);
}
//
 void juego(int puntos){
	char cont;
		do{
		system("CLS");
		Limites();
		PintaGameOver();
		gotoxy(15,1); cout<<"..:: Desarrollado::..";
		gotoxy(10,2); cout<<"..:: Universidad De Cundinamarca, Sede Chia, Noviembre 2016 ::..";
		gotoxy(45,10); cout<<"Total Puntos: "<<puntos;
		gotoxy(45,15); cout<<"¿Desea volver a jugar?";
		gotoxy(45,16); cout<<"Presione <S> para continuar";
		gotoxy(45,17); cout<<"Presione <N> para salir \n";
		cont=getch();
		}while( cont!='s' && cont!='n' && cont!='N' && cont!='S' );
		if (cont=='n' || cont=='N'){
			system("CLS");
			exit(0);
			
		}else{
			system("CLS");
			main();
			
		}
	}
//POO
class NAVE{
	int x,y;
	int corazones;
	int vidas;
	public:
		NAVE(int _x,int _y,int _corazones,int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
		int X(){return x;}
		int Y(){return y;}
		int VIDAS(){return vidas;}
		int cor(){corazones--;}
		void pintar();
		void borrar();
		void mover();
		void Pintar_Salud();
		void morir();
};

void NAVE::pintar(){
	gotoxy(x,y);printf("  %c",30);
	gotoxy(x,y+1);printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2);printf("%c%c %c%c",30,190,190,30);	
}

void NAVE::borrar(){
	gotoxy(x,y);printf("     ");
	gotoxy(x,y+1);printf("     ");
	gotoxy(x,y+2);printf("     ");
}

void NAVE::mover(){
	//detectar tecla presionada
		if(kbhit()){
			//guardar letra presionada
			char tecla = getch();
			borrar();
			if(tecla == IZQUIERDA && x > 3) x--;
			if(tecla == DERECHA && x+5 < 77) x++;
			if(tecla == ARRIBA && y > 4) y--;
			if(tecla == ABAJO && y+3 < 33) y++;
			if(tecla =='e')corazones--;
			pintar();
			Pintar_Salud();
		}
}

void NAVE::Pintar_Salud(){
	gotoxy(50,2);printf("Vidas: %d",vidas);
	gotoxy(64,2);printf("Salud:");
	gotoxy(70,2);printf("      ");
	for(int i= 0; i< corazones; i++){
		gotoxy(70+i,2);printf("%c",3);
	}
}

void NAVE::morir(){
	if(corazones == 0){
		borrar();
		gotoxy(x,y); printf("   **   ");
		gotoxy(x,y+1); printf("  ****  ");
		gotoxy(x,y+2); printf("   **   ");
		Sleep(200);
		borrar();
		gotoxy(x,y); printf(" * ** * ");
		gotoxy(x,y+1); printf("* **** *");
		gotoxy(x,y+2); printf(" * ** * ");
		Sleep(200);
		borrar();
		vidas--;
		corazones=3;
		Pintar_Salud();
		gotoxy(x,y);printf("          ");
		gotoxy(x,y+1);printf("         ");
		gotoxy(x,y+2);printf("         ");
		pintar();
		Limites();
	}
}
class asteroide{
	int x,y;
	public:
		asteroide(int _x,int _y):x(_x),y(_y){}
		int X(){
			return x;
		}
		int Y(){
			return y;
		}
		void pintarast();
		void moverast();
		void choque(NAVE &N);
		void borrar();
};
void asteroide::borrar(){
	gotoxy(x,y);printf("          ");
	gotoxy(x,y+1);printf("         ");
	gotoxy(x,y+2);printf("         ");
}
void asteroide::pintarast(){
	gotoxy(x,y); printf("%c",184);
	
}

void asteroide::moverast(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y > 32){
		x = rand()%71 +6;
		y=4;
	}
	pintarast();
}

void asteroide::choque(NAVE &N){
	if( x >= N.X() && x < N.X()+5 && y >= N.Y() && y<= N.Y()+2){
		Sleep(200);
		N.cor();
		borrar();
		Limites();
		N.pintar();
		N.Pintar_Salud();
		x = rand()%71 +6;
		y=4;
	}
}
class enemigo{
	int x,y,vida,salud,puntos;
	bool bandera;
		public:
		enemigo( bool _bandera,int _x,int _y,int _vida,int _salud): x(_x),y(_y),vida(_vida),bandera(_bandera),salud(_salud){}
		int X(){return x;}
		int Y(){return y;}
		void impacto(){vida--  ;}
		bool Bandera(){return bandera;}
		int vidae(){return vida;}
		int morir(){return salud;}
		void pts(int puntos){}
		int puntaje(){
		return puntos;}
		void pintarenemy();
		void borrarenemy();
		void moverenemy();
		void Pinta_vidaenemy();
		void morirenemy();
		
			
};
void enemigo::pintarenemy(){
	gotoxy(x,y-2);printf(" %c%c%c%c%c%c%c",100,47,77,95,77,92,98);
	gotoxy(x,y-1);printf("%c%c%c%c%c%c%c%c%c",126,124,92,207,207,207,47,124,126);
	gotoxy(x,y);printf("%c       %c",31,31);
}
void enemigo::borrarenemy(){
	gotoxy(x,y-2);printf("        ");
	gotoxy(x,y-1);printf("         ");
	gotoxy(x,y);printf("         ");
}
void enemigo::moverenemy(){	
	borrarenemy();
	if(bandera==false){
	x++;
		if(x>67){
		bandera=!bandera;
		}
	}else{
		x--;
		if(x<5){
			bandera=!bandera;	
		}
	}
	pintarenemy();
}
void enemigo::Pinta_vidaenemy(){
	gotoxy(20,2);printf("Enemigo: %d",vida);

	//gotoxy(1,1);cout<<puntaje();
	gotoxy(35,2);printf("          ");
	for(int i= 0; i< salud; i++){
		gotoxy(35+i,2);printf("%c",178);
	}
	
}
void enemigo::morirenemy(){
	if(vida == 0){
		salud--;
		vida=30;
		Pinta_vidaenemy();	
	}
}

class Disparo{
	int x,y;
	public: 
	Disparo(int _x, int _y):x(_x),y(_y){}
	int X(){return x;}
	int Y(){return y;}
	void mover();
	bool fuera();
	void disp(enemigo &E);
};

void Disparo::disp(enemigo &E){
		//gotoxy(5,1);printf("X:%d Y:%d ",E.X(),E.Y());
		int cont=3;
		int ex=E.X();
		int din=ex+9;
		for(ex;ex<din;ex++){
			if(x==ex && y== E.Y()+1){
				E.impacto();
				E.morirenemy();
				E.Pinta_vidaenemy();		
			}
			if(E.morir()==0){
				
			//GameOver=true;
			juego(E.puntaje());
		}
		gotoxy(1,1);cout<<E.puntaje();
		}
	//}
}
void Disparo::mover(){
	gotoxy(x,y); printf(" ");
	if(y>4) y--;
	gotoxy(x,y); printf("|");
}

bool Disparo::fuera(){
	if(y==4){
		return true;
	}else{
		return false;	
	}
	
}


int main(){
	system("color 70");
	OcultarCursor();
	Limites();
	NAVE N(38,30,3,3);
	enemigo E(false,4,6,30,10);
	E.pintarenemy();
	N.pintar();
	N.Pintar_Salud();
	E.Pinta_vidaenemy();
	gotoxy(15,1); cout<<"..:: *NAVES* ::..";
	//creando asteroides
	list<asteroide*>A;
	list<asteroide*>::iterator itA;
	for(int i=0;i<5;i++){
		A.push_back(new asteroide(rand()%75+3,rand()%5+4));
	}
	list<Disparo*> D;
	list<Disparo*>::iterator it;
	
	
	bool GameOver = false;
	int puntos = 0;
	while(!GameOver){
		E.moverenemy();
		
		gotoxy(4,2);printf("Puntos: %d",puntos);
		if(kbhit()){
			char tecla= getch();
			if(tecla == ' '){
				D.push_back(new Disparo(N.X()+0,N.Y()+1));
				D.push_back(new Disparo(N.X()+2,N.Y()-1));
				D.push_back(new Disparo(N.X()+4,N.Y()+1));
			}
		}
		
		for(it =  D.begin();it != D.end(); it++){
			(*it)->mover();
			(*it)->disp(E);
			if((*it)->fuera()){
				gotoxy((*it)->X(),(*it)->Y());printf(" ");
				//eliminar elemento en la lista
				delete(*it);
				//reorganizar enlaces de la lista
				it= D.erase(it);
			}
		}
		//asteroides en pantalla
		for(itA=A.begin();itA!=A.end();itA++){
			(*itA)->moverast();
			(*itA)->choque(N);
		}
		//colision asteroides 
		for(itA=A.begin();itA!=A.end();itA++){
			//colision balas
			for(it =  D.begin();it != D.end(); it++){
				if((*itA)->X() == (*it)->X() &&( (*itA)->Y()+1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() )) {
					gotoxy((*it)->X(),(*it)->Y()); printf(" ");
					delete(*it);
					it = D.erase(it);
					A.push_back(new asteroide(rand()%74+3, 4));
					gotoxy((*itA)->X(),(*itA)->Y()); printf(" ");
					delete(*itA);
					itA= A.erase(itA);
					puntos +=5;	 
					E.pts(puntos);
				}
			}
		}
		
		
		if(N.VIDAS()==0){
			GameOver=true;
			juego(puntos);
		}
		
		
		N.morir();
		N.mover();
		
			//iteraciones ms no recargar pc
		Sleep(50);
		
		
	}
	
	//system("PAUSE");
	
	
	return 0;
}

void PintaGameOver(){
	gotoxy(4,4); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,5); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,223,223,223,219,219,197,219,219,219,223,223,223,219,219,219,197,219,219,219,223,219,220,219,223,219,219,219,197,219,219,223,223,223);
	gotoxy(4,6); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,197,197,197,197,219,219,197,219,219,197,197,197,197,197,219,219,197,219,219,197,197,197,219,197,197,197,219,219,197,219,219,197,197,197);
	gotoxy(4,7); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,197,197,197,220,220,220,197,219,219,220,220,220,220,220,219,219,197,219,219,197,197,197,223,197,197,197,219,219,197,219,219,223,223,223);
	gotoxy(4,8); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,197,197,197,197,219,219,197,219,219,197,197,197,197,197,219,219,197,219,219,197,197,197,197,197,197,197,219,219,197,219,219,197,197,197);
	gotoxy(4,9); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,220,220,220,219,219,197,219,219,197,197,197,197,197,219,219,197,219,219,197,197,197,197,197,197,197,219,219,197,219,219,220,220,220);
	gotoxy(4,10); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,11); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,223,223,223,219,219,219,197,223,219,219,219,197,197,219,219,223,197,219,219,223,223,223,197,219,219,223,223,223,223,219,219,220,197);
	gotoxy(4,12); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,197,197,197,197,197,219,219,197,197,197,219,219,197,197,219,219,197,197,219,219,197,197,197,197,219,219,197,197,197,197,197,219,219,197);
	gotoxy(4,13); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,197,197,197,197,197,219,219,197,197,197,219,219,197,197,219,219,197,197,219,219,223,223,223,197,219,219,220,220,220,220,220,223,223,197);
	gotoxy(4,14); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,197,197,197,197,197,219,219,197,197,197,219,219,197,197,219,223,197,197,219,219,197,197,197,197,219,219,197,197,197,197,197,219,219,197);
	gotoxy(4,15); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,220,220,220,219,219,219,197,197,197,45,223,219,223,197,197,45,197,219,219,220,220,220,197,219,219,197,197,197,197,197,219,219,220);
	gotoxy(4,16); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,17); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,219,219,197,197,197,197,197,197,197,197,197,197,197,197,197,197,197,219,219,197,197,197,197,197,197,197,197,197);
	gotoxy(4,18); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,219,219,219,219,220,197,197,197,220,220,220,220,220,220,220,197,197,197,220,219,219,219,219,197,197,197,197,197,197,197);
	gotoxy(4,19); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,223,223,219,220,219,219,219,219,219,219,219,219,219,220,219,223,223,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,20); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,219,219,219,219,219,219,219,219,219,219,219,219,219,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,21); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,219,219,223,223,223,219,219,219,223,223,223,219,219,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,22); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,219,219,197,197,197,219,219,219,197,197,197,219,219,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,23); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,219,219,219,219,219,223,220,223,219,219,219,219,219,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,24); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,197,197,219,219,219,219,219,219,219,219,219,219,219,197,197,197,197,197,197,197,197,197,197,197,197,197);
	gotoxy(4,25); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,220,220,220,219,219,197,197,219,223,219,223,219,197,197,219,219,220,220,220,197,197,197,197,197,197,197,197,197);
	gotoxy(4,26); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,223,223,219,219,197,197,197,197,197,197,197,197,197,197,197,219,219,223,223,197,197,197,197,197,197,197,197,197);
	gotoxy(4,27); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",197,197,197,197,197,197,197,197,197,197,223,223,197,197,197,197,197,197,197,197,197,197,197,223,223,197,197,197,197,197,197,197,197,197,197,197);
	//http://www.network-science.de/ascii/
	


}
