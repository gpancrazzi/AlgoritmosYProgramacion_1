#include<stdio.h>
#include<string.h>

#define max 50
#define max_nom 30

typedef struct {
	
	int num_cliente;
	char nombre[max_nom];
	char provincia[max];
	char localidad[max];
	char direccion[max];
} t_cli;

void cargar_datos(FILE *arch){
	
	t_cli cli;
	long i=0;
	
	printf("A continuacion, le voy a solicitar que cargue los datos de los clientes argentinos:\n\n");
	
	do{
		
		printf("Ingrese el numero de cliente (para finalizar ingrese 0): ");
		fflush(stdin);
		scanf("%d", &cli.num_cliente);
		
		if ((cli.num_cliente!=0) && (i<90000)){
			
			printf("Ingrese el nombre: ");
			fflush(stdin);
			fgets(cli.nombre, max_nom, stdin);
			
			printf("Ingrese la provincia: ");
			fflush(stdin);
			fgets(cli.provincia, max, stdin);
			
			printf("Ingrese la localidad: ");
			fflush(stdin);
			fgets(cli.localidad, max, stdin);
			
			printf("Ingrese la direccion: ");
			fflush(stdin);
			fgets(cli.direccion, max, stdin);
			
			fwrite(&cli, sizeof(cli), 1, arch);
			i++;
			printf("\n");
		}
	} while ((cli.num_cliente!=0) && (i<90000));
}

void mostrar_datos(FILE *arch){
	
	t_cli cli;
	
	rewind(arch);
	
	fread(&cli, sizeof(cli), 1, arch);
	
	printf("\n-Clientes argentinos:\n");
	
	while (!feof(arch)){
		
		printf("\nNumero de cliente: %d\nNombre: %sProvincia: %sLocalidad: %sDireccion: %s", 
		cli.num_cliente, cli.nombre, cli.provincia, cli.localidad, cli.direccion);
		
		fread(&cli, sizeof(cli), 1, arch);
	}
}

int main(){
	
	FILE *ClientesArg;
	ClientesArg=fopen("ClientesArg.dat", "wb+");
	
	if (ClientesArg==NULL){
		
		printf("\nNo se pudo crear el archivo.\n");
	} else{
		
		cargar_datos(ClientesArg);
		mostrar_datos(ClientesArg);
		
		fclose(ClientesArg);
	}
	
	return 0;
}
