/*
Nom: Marc Fernández García.
S'ha d'optimitzar aquest codi tot el que pugueu.
Fer un document PDF on s'explica detalladament com estava el codi i quina millora heu fet.
Podeu modificar el codi tot el que vulgueu, però ha de mantenir les mateixes funcionalitats, no pot tenir noves ni tenir menys, el programa ha de fer el mateix.
*/

#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>

using namespace std;

struct carta{
	int numero;
	string palo;
};

// FUNCIONES
void PasadoDeNumero(int Puntos, bool Repetir);
void cartas(carta mano[52], carta manoMaquina[52], int contadorAs, int puntos, int num_cartas_mano);
void cartas2(carta mano[52], int contadorAs, int puntos, int num_cartas_mano);
void cartas3(carta manoMaquina[52], int puntosMaquina, int carta_mano_maquina, int puntos, int repetir, carta baraja[52]);
void cartas5(carta baraja[52]);


int main(){

	struct carta baraja[52];
  time_t t;
  srand((unsigned) time(&t));
	int numeros[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

	const string palos[4] = { "Corazones", "Diamantes", "Picas", "Treboles" };
	
	int contador = 0; 

	for ( int i = 0; i < 13; i++){
		for ( int j = 0; j < 4; j++){
			baraja[contador].numero = numeros[i];
			baraja[contador].palo = palos[j];
			contador++;
		}
	}

  int opcion;
  bool repetir = true;  
  struct carta mano[52], manoMaquina[52];
  int num_cartas_mano, carta_mano_maquina, puntos, contadorAs, puntosMaquina, turno = 0;
 
  //Repartir cartas
  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
    mano[contadorBaraja] = baraja[rand()%52];
  }

  do {
        cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << endl;
        cout << "\033[1;32m 1. Robar carta \033[0m" << endl;
        cout << "\033[1;32m 2. Mostrar mano \033[0m" << endl;
        cout << "\033[1;32m 3. Plantarse \033[0m" << endl;
        cout << "\033[1;32m 4. Ver baraja \033[0m" << endl;
        cout << "\033[1;32m 0. SALIR \033[0m" << endl;
        
        if (turno == 0)
        {
          
          cartas(mano, manoMaquina, contadorAs, puntos, num_cartas_mano);
          
          PasadoDeNumero(puntos, repetir);
        } 
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        turno++;

        switch (opcion) {
            case 1:
                system("clear");
                mano[num_cartas_mano+1] = baraja[rand()%52];                
                cout << "\033[1;32mTu carta es: \033[0m" << endl;
                
                cartas(mano, manoMaquina, contadorAs, puntos, num_cartas_mano);

                PasadoDeNumero(puntos, repetir);
                
            case 2:
                system("clear");               
                cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
                puntos = 0;
                contadorAs = 0;

                cartas2(mano, contadorAs, puntos, num_cartas_mano);

                cout << "\033[1;32mTienes " << puntos <<" puntos \033[0m" << endl;
                break;
                
            case 3:
            	system("clear");               
              
              cartas3(manoMaquina, puntosMaquina, carta_mano_maquina, puntos, repetir, baraja);
    
            case 4:
              
              cartas5(baraja);
              break;

            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir);

		return 0;
}

//FUNCIONES SOLUCION.

void PasadoDeNumero(int puntos, bool repetir){

  if (puntos > 21){
    cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << endl;
    cout << "\033[1;31mHas perdido\033[0m" << endl;
    repetir = false;
  } else if (puntos == 21){ 
    cout << "\033[1;33mFELICIDADES tienes " << puntos <<  " puntos!(Blackjack)\033[0m" << endl;
    repetir = false;
  } else {
    cout << "\033[1;32mTienes " << puntos <<" puntos \033[0m" << endl;
  }
};

void cartas(carta mano[52], carta manoMaquina[52], int contadorAs, int puntos, int num_cartas_mano){

  for (int contadorMano = 0; contadorMano < 52; contadorMano++)
  {
    if (mano[contadorMano].palo != "")
    {
              if (mano[contadorMano].numero == 1)
              {
                cout << "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
                contadorAs++;
                if (contadorAs >= 1 && puntos + 11 > 21)
                {
                  puntos = puntos + 1;
                }
                else
                {
                  puntos = puntos + 11;
                }
                num_cartas_mano++;
              }
              else if (mano[contadorMano].numero == 11)
              {
                cout << "\033[1;33m Sota de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + 10;
                num_cartas_mano++;
              }
              else if (mano[contadorMano].numero == 12)
              {
                cout << "\033[1;33m Caballo de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + 10;
                num_cartas_mano++;
              }
              else if (mano[contadorMano].numero == 13)
              {
                cout << "\033[1;33m Rey de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + 10;
                num_cartas_mano++;
              }
              else
              {
                cout << "\033[1;33m " << mano[contadorMano].numero << " de " << mano[contadorMano].palo << "\033[0m" << endl;
                puntos = puntos + mano[contadorMano].numero;
                num_cartas_mano++;
              }
    }
  }
};

void cartas2(carta mano[52], int contadorAs, int puntos, int num_cartas_mano){

  for (int contadorMano = 0; contadorMano < 52; contadorMano++){
                  if (mano[contadorMano].palo != ""){
                    if( mano[contadorMano].numero == 1){
                      cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
                      contadorAs++;
                      if (contadorAs >= 1 && puntos+11 > 21){
                        puntos = puntos + 1;
                      } else {
                        puntos = puntos + 11;
                      }
                      num_cartas_mano++;
                    } else if (mano[contadorMano].numero == 11){
                      cout <<  "\033[1;33m Sota de " << mano[contadorMano].palo << "\033[0m" << endl;
                      puntos = puntos + 10;
                      num_cartas_mano++;
                    } else if (mano[contadorMano].numero == 12){
                      cout <<  "\033[1;33m Caballo de " << mano[contadorMano].palo << "\033[0m" << endl;
                      puntos = puntos + 10;
                      num_cartas_mano++;
                    } else if (mano[contadorMano].numero == 13){
                      cout <<  "\033[1;33m Rey de " << mano[contadorMano].palo << "\033[0m" << endl;
                      puntos = puntos + 10;
                      num_cartas_mano++;
                    } else {
                      cout << "\033[1;33m " << mano[contadorMano].numero << " de " << mano[contadorMano].palo << "\033[0m" << endl;
                      puntos = puntos + mano[contadorMano].numero;
                      num_cartas_mano++;
                    }
                  }
                }
};

void cartas3(carta manoMaquina[52], int puntosMaquina, int carta_mano_maquina, int puntos, int repetir, carta baraja[52]){
  
                  if( manoMaquina[carta_mano_maquina].numero == 1){
                    cout <<  "\033[1;33m A de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else if (manoMaquina[carta_mano_maquina].numero == 11){
                    cout <<  "\033[1;33m Sota de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else if (manoMaquina[carta_mano_maquina].numero == 12){
                    cout <<  "\033[1;33m Caballo de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else if (manoMaquina[carta_mano_maquina].numero == 13){
                    cout <<  "\033[1;33m Rey de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  } else {
                    cout << "\033[1;33m " << manoMaquina[carta_mano_maquina].numero << " de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
                  }
                  puntosMaquina = puntosMaquina + manoMaquina[carta_mano_maquina].numero;
                  cout << "\033[1;37m Puntos maquina: " << puntosMaquina << endl;
                  carta_mano_maquina++;
                
                if (puntosMaquina > 21){
                  cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
                  cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
                } else if (puntosMaquina == puntos){
                  cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
                  cout << "\033[1;33mEmpate\033[0m" << endl;
                } else {
                  cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
                  cout << "\033[1;31mHas perdido...\033[0m" << endl;
                }
                cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << endl;
                repetir = false;            

};

void cartas5(carta baraja[52]){

  for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++){
                if( baraja[contadorBaraja].numero == 1){
                  cout <<  "A de " << baraja[contadorBaraja].palo << endl;
                } else if (baraja[contadorBaraja].numero == 11){
                  cout <<  "Sota de " << baraja[contadorBaraja].palo << endl;
                } else if (baraja[contadorBaraja].numero == 12){
                  cout <<  "Caballo de " << baraja[contadorBaraja].palo << endl;
                } else if (baraja[contadorBaraja].numero == 13){
                  cout <<  "Rey de " << baraja[contadorBaraja].palo << endl;
                } else {
                  cout << baraja[contadorBaraja].numero << " de " << baraja[contadorBaraja].palo << endl;
                }
              }


};
