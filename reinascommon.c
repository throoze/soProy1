void procesarNJobs(char *argv, int *nJobs, char *usage){
  *nJobs = atoi(argv);
  if (*nJobs <= 0) {
    int opt;
    printf("Debe haber al menos un trabajador!");
    printf(usage);
    do {
      printf("\nQue desea hacer???\n");
      printf("\t1) Introducir un nuevo numero de trabajadores.\n");
      printf("\t2) Usar el valor por defecto (8 trabajadores).\n");
      printf("\t3) Abandonar el programa.\n");
      printf("\n\tIntroduzca el numero de opción:\n\t\t>> ");
      scanf("%d",&opt);
    } while (1 > opt || opt >= 4);
    switch (opt)
      {
      case 1:
	do {
	  printf("Por favor intruduzca un numero válido de trabajadores:\n\t>> ");
	  scanf("%d",nJobs);
	} while (*nJobs < 1);
	break;
      case 2:
	*nJobs = 8;
	break;
      case 3:
	printf("Saliendo del programa...\n");
	exit(0);
      }
  }
}

void procesarFlagPrint(char *argv, int *flagPrint, char *usage){
  *flagPrint = atoi(argv);
  if (*flagPrint < 0 || 1 < *flagPrint) {
    int opt;
    printf("Los posibles valores para la opción de impresión son cero(0) o uno (1)!\n");
    printf(usage);
    do {
      printf("\nQue desea hacer???\n");
      printf("\t1) Volver a introducir la opción de impresión.\n");
      printf("\t2) Usar el valor por defecto (0, no imprimir).\n");
      printf("\t3) Abandonar el programa.\n");
      printf("\n\tIntroduzca el numero de opción:\n\t\t>> ");
      scanf("%d",&opt);
    } while (1 > opt || opt >= 4);
    switch (opt)
      {
      case 1:
	do {
	  printf("Por favor intruduzca un valor válido de opción de impresión:\n\t>> ");
	  scanf("%d",flagPrint);
	} while (*flagPrint != 0 || *flagPrint != 1);
	break;
      case 2:
	*flagPrint = 0;
	break;
      case 3:
	printf("Saliendo del programa...\n");
	exit(0);
      }
  }
}

void procesarArgumentos(int argc, char **argv, int *nJobs, int *flagPrint, char *usage) {
  if (argc != 1) {
    switch (argc)
      {
      case 3:
	if (strcmp(argv[1],"-n") == 0){
	  procesarNJobs(argv[2],nJobs,usage);
	} else if (strcmp(argv[1],"-i") == 0) {
	  procesarFlagPrint(argv[2],flagPrint,usage);
	} else {
	  printf(usage);
	  exit(1);
	}
	break;
      case 5:
	if (strcmp(argv[1],"-n") == 0){
	  if (strcmp(argv[3],"-i") == 0) {
	    procesarNJobs(argv[2],nJobs,usage);
	    procesarFlagPrint(argv[4],flagPrint,usage);
	  } else {
	    printf(usage);
	    exit(1);
	  }
	} else if (strcmp(argv[1],"-i") == 0) {
	  if (strcmp(argv[3],"-n") == 0) {
	    procesarNJobs(argv[4],nJobs,usage);
	    procesarFlagPrint(argv[2],flagPrint,usage);
	  } else {
	    printf(usage);
	    exit(1);
	  }
	} else {
	  printf(usage);
	  exit(1);
	}
	break;
      default:
	printf(usage);
	exit(1);
      }
  }
}
