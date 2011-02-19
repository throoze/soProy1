#include"pReinas.h"

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
	int k;
	for(k = 0 ; k < 8  ; k++) {
	  if(k == 7) {
	    printf("(%d)\n",x[k]);
	  }
	  else {
	    printf("(%d) ",x[k]);
	  }
	}
	
	FILE *archivo;
	char *nombre = malloc(sizeof(char*));
	char *resultado = malloc(15);
	sprintf(nombre,"salida%d%d",ri,rj);
	sprintf(resultado,"%d %d %d %d %d %d %d %d",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
	archivo = fopen(nombre, "w");
	if(archivo == NULL) {
	  perror("error creando el archivo");
	  exit(0);
	}
	fprintf(archivo, "%s", resultado);
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
  
  printf("reina en la posicion (%d,%d)\n",ri,rj);
  //fflush(stdout);
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

  try(0);
   
  return 1;
}



    
