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
	tiempo = clock() - tiempo;
	int k;
	if (imprime){
	  fflush(stdout);
	  printf("   Resultado del proceso %d:\n",ri+(rj*8));
	  printf("      Solucion: ");
	  for(k = 0 ; k < 8  ; k++) {
	    if(k == 7) {
	      printf("(%d,%d)\n",k,x[k]);
	    }
	    else {
	      printf("(%d,%d) ",k,x[k]);
	    }
	  }
	  fflush(stdout);
	  printf("          Tiempo: %.2Lf mseg.\n",(double)tiempo);
	  printf("          Tablero inicial: (%d,%d)\n\n", ri, rj);
	  fflush(stdout);
	}
	
	FILE *archivo;
	char *nombre = malloc(sizeof(char*));
	char *resultado = malloc(20);
	sprintf(nombre,"./salidas/salida%d%d",rj,ri);
	archivo = fopen(nombre, "w");
	sprintf(resultado,"%d %d %d %d %d %d %d %d",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
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
  rj = atoi(argv[2]);
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

  tiempo = clock();
  try(0);
   
  return 1;
}



    
