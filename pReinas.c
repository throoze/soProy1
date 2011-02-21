#include "pReinas.h"

void try(int i){
  int j;
  if(i == ri && i != 7) i++;
  for (j = 0; j < 8; j++){

    if ((a[j] && b[i+j] && c[i-j+7]) || (i == 7 && ri == i)){
      if (ri != i){      
	x[i]=j;
	a[j]=FALSE;
	b[i+j]=FALSE;
	c[i-j+7]=FALSE;
      }
      if (i < 7) try(i+1);
      else{
	gettimeofday(&end, NULL);
	tiempo = ((end.tv_sec * 1000000 + end.tv_usec)
		      - (start.tv_sec * 1000000 + start.tv_usec));
	int k;
	if (imprime){
	  char *resultado = malloc(200);
	  sprintf(resultado, "   Resultado del hijo %d:\n      Solucion: ",ri+(8*rjreal) + 1);
	  for(k = 0 ; k < 8  ; k++) {
	    if(k == 7) {
	      sprintf(resultado, "%s(%d,%d)\n",resultado,k,x[k]);
	    }
	    else {
	      sprintf(resultado, "%s(%d,%d) ",resultado,k,x[k]);
	    }
	  }
	  sprintf(resultado, "%s          Tiempo (milisegundos): %d \n",resultado, tiempo);
	  sprintf(resultado, "%s          Tablero inicial: (%d,%d)\n\n",resultado,  ri, rj);
	  printf(resultado);
	  
	}
	
	FILE *archivo;
	char *nombre = malloc(sizeof(char*));
	char *resultado = malloc(20);
	sprintf(nombre,"./salidas/salida%d",ri+(rjreal*8) + 1);
	archivo = fopen(nombre, "w");
	sprintf(resultado,"%d %d %d %d %d %d %d %d %d",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],tiempo);
	if(archivo == NULL) {
	  perror("error creando el archivo");
	  exit(0);
	}
	fprintf(archivo, "%s %f", resultado, (double)tiempo);
	fclose(archivo);
	free(resultado);
	  
	exit(0);
      }	
      a[j]=TRUE;
      b[i+j]=TRUE;
      c[i-j+7]=TRUE;	
    }      
  }
}

int main( int argc, const char* argv[] ){
  ri = atoi(argv[1]);
  rj = atoi(argv[2])%8;
  rjreal = atoi(argv[2]);
  imprime = atoi(argv[3]);

  
  int i;
  for(i = 0; i < 8; i++){ 
    a[i] = TRUE;
  }
  for(i = 0; i < 15; i++){ 
    b[i] = TRUE;
  } 
  for(i = 0; i < 15; i++){ 
    c[i] = TRUE;
  }
  
  x[ri] = rj;
  a[rj] = FALSE;
  b[ri + rj] = FALSE;
  c[ri - rj + 7] = FALSE;

gettimeofday(&start, NULL);
  try(0);
   
  return 1;
}



    
