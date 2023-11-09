#include <iostream>
#include <conio.h>    
#include <string.h>


//line code 223 MOVIENDO FICHAS
using namespace std;

//Funcion Para Inicializar  Y mostrar el Tablero.
void InicializarTablero(char tablero[8][8]){
	//El tablero inicia con piezas vacias.
	for(int fila = 0; fila < 8; fila++){
		for(int columna = 0; columna < 8; columna++){
			tablero[fila][columna] = ' ';
		}
	}
	
	//Aqui colocamos las piezas en su posicion inicial
	
	tablero[0][0] = 'T'; //TORRE NEGRA
	tablero[0][7] = 'T'; //TORRE NEGRA
	tablero[0][1] = 'C'; //Caballo izquierdo negro
	tablero[0][2] = 'A'; //alfil izquierdo negro
	tablero[0][3] = 'Q'; // q = queen = reyna NEGRA
	tablero[0][4] = 'R'; // REY negro.
	tablero[0][5] = 'A'; //Alfil derecho negro
	tablero[0][6] = 'C'; // Caballo Derecho Negro.
	tablero[7][0] = 't'; //torre blanca
	tablero[7][7] = 't'; //torre blanca
	tablero[7][1] = 'c'; //caballito izquierdo blanco
	tablero[7][2] = 'a'; //alfil izquierdo blanco
	tablero[7][3] = 'q'; // q = queen = reyna blanca
	tablero[7][4] = 'r'; // rey blanco
	tablero[7][5] = 'a'; //alfil derecho blanco
	tablero[7][6] = 'c'; // Caballo derecho blanco
	
	//Peones Negros.
	tablero[1][0] = 'P'; // Peon negro
	tablero[1][1] = 'P'; // Peon negro
	tablero[1][2] = 'P'; // Peon negro
	tablero[1][3] = 'P'; // Peon negro
	tablero[1][4] = 'P'; // Peon negro
	tablero[1][5] = 'P'; // Peon negro
	tablero[1][6] = 'P'; // Peon negro
	tablero[1][7] = 'P'; // Peon negro
	
	// Peones Blancos.
	tablero[6][0] = 'p'; //peon blanco
	tablero[6][1] = 'p'; //peon blanco
	tablero[6][2] = 'p'; //peon blanco
	tablero[6][3] = 'p'; //peon blanco   
	tablero[6][4] = 'p'; //peon blanco
	tablero[6][5] = 'p'; //peon blanco
	tablero[6][6] = 'p'; //peon blanco
    tablero[6][7] = 'p'; //peon blanco
	
	//iremos agregando las demas piezas aqui.
	
	
	/*
	   swith (p)
	   
	    case 'p' :
	         if
	         
	         
	         
	         
	*/
}

//funcion para mostrar el tablero actual 
void MostrarTablero(char tablero[8][8]) {
    cout << "  a b c d e f g h" << endl;
    cout << "\n";
    for (int fila = 0; fila < 8; fila++) {
        cout << 8 - fila << " ";
        for (int columna = 0; columna < 8; columna++) {
            cout << tablero[fila][columna] << " ";
        }
        cout << 8 - fila << endl;
    }
    cout << "\n";
    cout << "  a b c d e f g h";
   
}

bool MoverPeon(char tablero[8][8], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    int direccion = (tablero[fila_origen][columna_origen] == 'P') ? 1 : -1; // Peón blanco o negro
    int fila_dif = fila_destino - fila_origen;
    int columna_dif = abs(columna_destino - columna_origen);

    if (fila_dif == direccion) {
        if (columna_dif == 0 && tablero[fila_destino][columna_destino] == ' ') {
            return true; // Avance de una casilla si está vacía
        } else if (columna_dif == 1 && tablero[fila_destino][columna_destino] != ' ') {
            return true; // Captura en diagonal
        }
    } else if (fila_dif == 2 * direccion && columna_dif == 0 && fila_origen == (direccion == 1 ? 1 : 6) &&
               tablero[fila_destino][columna_destino] == ' ' &&
               tablero[fila_destino - direccion][columna_destino] == ' ') {
        return true; // Doble avance inicial
    }

    return false; // Movimiento no válido
}

bool MoverTorre(char tablero[8][8], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    if (fila_origen == fila_destino) {
        int direccion = (columna_destino > columna_origen) ? 1 : -1;
        for (int col = columna_origen + direccion; col != columna_destino; col += direccion) {
            if (tablero[fila_origen][col] != ' ') {
                return false; // Obstrucción en el camino
            }
        }
        return true;
    } else if (columna_origen == columna_destino) {
        int direccion = (fila_destino > fila_origen) ? 1 : -1;
        for (int row = fila_origen + direccion; row != fila_destino; row += direccion) {
            if (tablero[row][columna_origen] != ' ') {
                return false; // Obstrucción en el camino
            }
        }
        return true;
    }

    return false; // Movimiento no válido
}

bool MoverAlfil(char tablero[8][8], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    int fila_dif = abs(fila_destino - fila_origen);
    int columna_dif = abs(columna_destino - columna_origen);

    if (fila_dif == columna_dif) {
        int fila_direccion = (fila_destino > fila_origen) ? 1 : -1;
        int columna_direccion = (columna_destino > columna_origen) ? 1 : -1;
        int fila = fila_origen + fila_direccion;
        int columna = columna_origen + columna_direccion;

        while (fila != fila_destino && columna != columna_destino) {
            if (tablero[fila][columna] != ' ') {
                return false; // Obstrucción en el camino
            }
            fila += fila_direccion;
            columna += columna_direccion;
        }

        return true;
    }

    return false; // Movimiento no válido
}

bool MoverCaballo(char tablero[8][8], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    int fila_dif = abs(fila_destino - fila_origen);
    int columna_dif = abs(columna_destino - columna_origen);

    return (fila_dif == 2 && columna_dif == 1) || (fila_dif == 1 && columna_dif == 2);
}

bool MoverReina(char tablero[8][8], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    return MoverTorre(tablero, fila_origen, columna_origen, fila_destino, columna_destino) ||
           MoverAlfil(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
}

bool MoverRey(char tablero[8][8], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    int fila_dif = abs(fila_destino - fila_origen);
    int columna_dif = abs(columna_destino - columna_origen);

    return (fila_dif <= 1 && columna_dif <= 1);
}

bool MoverFicha(char tablero[8][8], string origen, string destino) {
    // Convierte las coordenadas de texto a índices de matriz
    int fila_origen = 8 - (origen[1] - '0');  // 6
    int columna_origen = origen[0] - 'a';
    int fila_destino = 8 - (destino[1] - '0');
    int columna_destino = destino[0] - 'a';

    // Verifica si la casilla de origen contiene una ficha y si el destino está dentro del tablero
    if (fila_origen < 0 || fila_origen >= 8 || columna_origen < 0 || columna_origen >= 8 ||
        fila_destino < 0 || fila_destino >= 8 || columna_destino < 0 || columna_destino >= 8 ||
        tablero[fila_origen][columna_origen] == ' ') {
        return false;
    }

    // Obtén el tipo de ficha
    char ficha = tablero[fila_origen][columna_origen];

    // Llama a la función específica para el tipo de ficha,C
    switch(ficha) {
        case 'P':
        case 'p':
             MoverPeon(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
            if	(MoverPeon){
             tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
              tablero[fila_origen][columna_origen] = ' ';
        return true;
			}
			return false;
        case 'T':
        case 't':
             MoverTorre(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
             if (MoverTorre){
              tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
              tablero[fila_origen][columna_origen] = ' ';
              return true;
			 }
			 return false;
        case 'A':
        case 'a':
             MoverAlfil(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
             if (MoverAlfil){
             	tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                tablero[fila_origen][columna_origen] = ' ';
              return true;
			 }
			 return false;
        case 'C':
        case 'c':
             MoverCaballo(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
             if(MoverCaballo){
             	tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
                tablero[fila_origen][columna_origen] = ' ';
              return true;	
			 }
			 return false;
        case 'Q':
        case 'q':
            return MoverReina(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
        case 'R':
        case 'r':
            return MoverRey(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
        default:
            return false; // Ficha inválida
    }
}



int main(){
	  cout << "****CHESS GAME******"  << endl; 
	  cout << "\n";
	  cout << "pronam";
	char tablero[8][8];
    InicializarTablero(tablero);
    MostrarTablero(tablero);

    // Aquí puedes agregar la lógica para que los jugadores realicen movimientos
	
	string origen, destino;

    while (true) {
    	cout << "\n";
        cout << " Ingrese el origen (por ejemplo, e2): ";
        cin >> origen;
        cout << " Ingrese el destino (por ejemplo, e4): ";
        cin >> destino;

        if (MoverFicha(tablero, origen, destino)) {
            MostrarTablero(tablero);
              // Aquí puedes agregar código para verificar condiciones de fin de juego (por ejemplo, checkmate)
        } else {
            cout << "Movimiento inválido. Inténtelo de nuevo." << endl;
        }
    }
	
	
	getch();
	return 0;
}