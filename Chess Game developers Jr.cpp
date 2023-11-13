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
	
 // Peones Negros.
    for (int i = 0; i < 8; i++) {
        tablero[1][i] = 'P'; // aqui podemos automatizar el rellenado de los peones negros
    }

    // Peones Blancos.
    for (int i = 0; i < 8; i++) {
        tablero[6][i] = 'p'; // aqui podemos automatizar el rellenado de los peones blancos
    }
	
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

// Validar si el usuario se ajusta a los parametros del juego, es decir que no pueda colocar mas de dos palabras
bool EsFormatoCorrecto(const string& entrada) {
    if (entrada.length() != 2) {
    	cout << "Formato incorrecto. Debe tener dos caracteres." << endl;
        return false;  // Si tiene mas de dos palabras
    }

    char columna = entrada[0];
    char fila = entrada[1];

    if (!isalpha(columna) || !isdigit(fila)) {
        return false;  // Valida si tiene una letra y un numero
    }

    // Aqui garantizamos que tenga no sea una letra invalida o un numero mayor a lo permitido en el tablero
    if (columna < 'a' || columna > 'h' || fila < '1' || fila > '8') {
    	cout << "Formato incorrecto. Utilice una letra entre 'a' y 'h' para la columna y un numero entre '1' y '8' para la fila." << endl;
        return false;
    }

    return true;
}

bool MoverFicha(char tablero[8][8], string origen, string destino, char turno ) {
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
    
	// Verifica que la ficha pertenezca al jugador que tiene el turno
    if ((turno == 'b' && isupper(ficha)) || (turno == 'n' && islower(ficha))) {
        return false;
    }

    // Verifica que la ficha de destino no sea del mismo jugador
    if ((isupper(ficha) && isupper(tablero[fila_destino][columna_destino])) ||
        (islower(ficha) && islower(tablero[fila_destino][columna_destino]))) {
        return false;
    }
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
            MoverReina(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
       		if(MoverReina){
       			tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
       			tablero[fila_origen][columna_origen] =' ';
       		return true;
			   }
			return false;
		case 'R':
        case 'r':
            MoverRey(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
        	if(MoverRey){
        		tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_destino];
        		tablero[fila_origen][columna_origen] =' ';
        	return true;
			}
		default:
            return false; // Ficha inválida
    }
}



int main(){
	  cout << "****CHESS GAME******"  << endl; 
	  cout << "\n";
	char tablero[8][8];
    InicializarTablero(tablero);
    MostrarTablero(tablero);

    // Aquí puedes agregar la lógica para que los jugadores realicen movimientos
	
	string origen, destino;
	
	 char turno = 'b';

    while (true) {
        cout << "\nTurno de las fichas " << turno << endl;

        do {
            cout << " Ingrese el origen (por ejemplo, e2): ";
            cin >> origen;
        } while (!EsFormatoCorrecto(origen));

        do {
            cout << " Ingrese el destino (por ejemplo, e4): ";
            cin >> destino;
        } while (!EsFormatoCorrecto(destino));

        if (MoverFicha(tablero, origen, destino, turno)) {
            MostrarTablero(tablero);
            // Aqui cambiamos elturno para el siguiente jugador
            turno = (turno == 'b') ? 'n' : 'b';
        } else {
            cout << "Movimiento invalido. Intentelo de nuevo." << endl;
        }
    }
   /* while (true) {
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
    } modificando el original */ 
	
	
	getch();
	return 0;
}