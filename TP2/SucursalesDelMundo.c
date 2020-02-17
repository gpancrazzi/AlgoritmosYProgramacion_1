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

void cargar_datos(FILE *Mun){
	
	t_suc suc;
	
	printf("A continuacion, le voy a solicitar que cargue los datos de las sucursales mundiales:\n\n");
	
	do{
		
		printf("Ingrese el numero de sucursal (para finalizar ingrese 0): ");
		scanf("%d", &suc.num_sucursal);
		
		if (suc.num_sucursal!=0){
			
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
		
		    fwrite(&suc, sizeof(suc), 1, Mun);
		    printf("\n");
		}
	} while (suc.num_sucursal!=0);
}

void mostrar_datos(FILE *Mun){
	
	t_suc suc;
	
	rewind(Mun);
	
	fread(&suc, sizeof(suc), 1, Mun);
	
	printf("\n-Sucursales del mundo:\n");
	
	while (!feof(Mun)){
		
		printf("\nNumero: %d\nNombre: %sPais: %sDireccion: %sTelefono: %s", suc.num_sucursal, suc.nombre, suc.pais, suc.direccion, suc.telefono);
		
		fread(&suc, sizeof(suc), 1, Mun);
	}
}

int main(){
	
	FILE *SucMundo;
	SucMundo=fopen("SucMundo.dat", "wb+");
	
	if (SucMundo==NULL){
		
		printf("\nNo se pudo abrir el archivo\n");
	}else{
		
		cargar_datos(SucMundo);
		mostrar_datos(SucMundo);
		
		fclose(SucMundo);
	}
	
	return 0;
}
