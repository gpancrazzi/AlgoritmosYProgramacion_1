#include<stdio.h>
#include<string.h>

#define max_nom 30
#define max 50
#define max_tel 20

typedef struct {
	
	int num_sucursal;
	char nombre[max_nom];
	char pais[max];
	char direccion[max];
	char telefono[max_tel];
} t_suc;

void cargar_datos (FILE *arch){
	
	t_suc suc;
	int i=0;
	
	printf("A continuacion, le voy a solicitar que cargue los datos de las sucursales argentinas:\n\n");
	
	do{
		
		printf("Ingrese el numero de sucursal (para finalizar ingrese 0): ");
		fflush(stdin);
		scanf("%d", &suc.num_sucursal);
		
		if ((suc.num_sucursal!=0) && (i<80)){
			
			printf("Ingrese el nombre de la sucursal: ");
		    fflush(stdin);
		    fgets(suc.nombre, max_nom, stdin);
		
		    printf("Ingrese el pais: ");
		    fflush(stdin);
		    fgets(suc.pais, max, stdin);
		
		    printf("Ingrese la direccion: ");
		    fflush(stdin);
		    fgets(suc.direccion, max, stdin);
		
		    printf("Ingrese el telefono: ");
		    fflush(stdin);
		    fgets(suc.telefono, max_tel, stdin);
		
		    fwrite(&suc, sizeof(suc), 1, arch);
		    i++;
		    printf("\n");
		}
	} while ((suc.num_sucursal!=0) && (i<80));
}

void mostrar_datos(FILE *arch){
	
	t_suc suc;
	
	rewind(arch);
	
	fread(&suc, sizeof(suc), 1, arch);
	
	printf("\n-Sucursales argentinas:\n");
	
	while (!feof(arch)){
		
		printf("\nNumero: %d\nNombre: %sDireccion: %sTelefono: %s", suc.num_sucursal, suc.nombre, suc.direccion, suc.telefono);
		
		fread(&suc, sizeof(suc), 1, arch);
	}
}

int main(){
	
	FILE *SucursalesArg;
	SucursalesArg=fopen("SucursalesArg.dat", "wb+");
	
	if (SucursalesArg==NULL){
		
		printf("\nNo se pudo crear el archivo.\n");
	}else{
		
		cargar_datos(SucursalesArg);
		mostrar_datos(SucursalesArg);
		fclose(SucursalesArg);
	}
	
	return 0;
}
