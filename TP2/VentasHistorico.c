#include<stdio.h>

typedef struct {
	
	int anio;
	int mes;
	int num_sucursal;
	float importe;
} t_vts_his;

void cargar_datos (FILE *arch){
	
	t_vts_his vts;
	
	printf("A continuacion, le voy a solicitar que cargue los datos de las ventas de los ultimos 20 anios:\n\n");
	
	do{
		
		printf("Ingrese el numero de sucursal (para finalizar ingrese 0): ");
		fflush(stdin);
		scanf("%d", &vts.num_sucursal);
		
		if (vts.num_sucursal!=0){
			
			printf("Ingrese el anio de venta: ");
			fflush(stdin);
			scanf("%d", &vts.anio);
			
			printf("Ingrese el mes de venta: ");
			fflush(stdin);
			scanf("%d", &vts.mes);
			
			printf("Ingrese el importe vendido: ");
			fflush(stdin);
			scanf("%f", &vts.importe);
			
			fwrite(&vts, sizeof(vts), 1, arch);
			printf("\n");
		}
	} while (vts.num_sucursal!=0);
}

void mostrar_datos(FILE *arch){
	
	t_vts_his his;
	
	rewind(arch);
	
	fread(&his, sizeof(his), 1, arch);
	
	printf("\n-Ventas historicas:\n\n");
	
	while (!feof(arch)){
		
		printf("Num de sucursal: %d\nAnio: %d\nMes: %d\nImporte: $%.2f\n\n", his.num_sucursal, his.anio, his.mes, his.importe);
		
		fread(&his, sizeof(his), 1, arch);
	}
}

int main(){
	
	FILE *VentasHistorico;
	VentasHistorico=fopen("VentasHistorico.dat", "wb+");
	
	if (VentasHistorico==NULL){
		
		printf("\nNo se pudo crear el archivo\n");
	}else{
		
		cargar_datos(VentasHistorico);
		mostrar_datos(VentasHistorico);
		
		fclose(VentasHistorico);
	}
	
	return 0;
}
