#include<stdio.h>
#include<string.h>

#define max_fecha 9

typedef struct {
	
	char fecha[max_fecha];
	int num_cliente;
	int num_sucursal;
	int articulo;
	int cantidad;
	float importe;
} t_vts_arg;

void cargar_datos(FILE *arch){
	
	t_vts_arg vts;
	int i=0;
	
	printf("A continuacion, le voy a solicitar que cargue los datos de las ventas de las sucursales argentinas durante el 2018:\n\n");
	
	do{
		
		printf("Ingrese el numero de sucursal (para finalizar ingrese 0): ");
		fflush(stdin);
		scanf("%d", &vts.num_sucursal);
		
		if ((vts.num_sucursal!=0) && (i<8000)){
			
			printf("Ingrese la fecha de venta (formato AAAAMMDD): ");
			fflush(stdin);
			fgets(vts.fecha, max_fecha, stdin);
			
			printf("Ingrese el numero de cliente: ");
			fflush(stdin);
			scanf("%d", &vts.num_cliente);
			
			printf("Ingrese el codigo del articulo: ");
			fflush(stdin);
			scanf("%d", &vts.articulo);
			
			printf("Ingrese la cantidad de articulos vendidos: ");
			fflush(stdin);
			scanf("%d", &vts.cantidad);
			
			printf("Ingrese el importe de la venta: ");
			fflush(stdin);
			scanf("%f", &vts.importe);
			
			fwrite(&vts, sizeof(vts), 1, arch);
			i++;
			printf("\n");
		}
	} while ((vts.num_sucursal!=0) && (i<8000));
}

void mostrar_datos(FILE *arch){
	
	t_vts_arg arg;
	
	rewind(arch);
	
	fread(&arg, sizeof(arg), 1, arch);
	
	printf("\n-Ventas de sucursales argentinas durante el 2018:\n");
	
	while (!feof(arch)){
		
		printf("\nNum Sucursal: %d\nFecha: %s\nNum Cliente: %d\nArticulo: %d\nCantidad: %d\nImporte: $%.2f\n", 
		arg.num_sucursal, arg.fecha, arg.num_cliente, arg.articulo, arg.cantidad, arg.importe);
		
		fread(&arg, sizeof(arg), 1, arch);
	}
}

int main(){
	
	FILE *VentasArg2018;
	VentasArg2018=fopen("VentasArg2018.dat", "wb+");
	
	if (VentasArg2018==NULL){
		
		printf("\nNo se pudo abrir el archivo\n");
	} else{
		
		cargar_datos(VentasArg2018);
		mostrar_datos(VentasArg2018);
		
		fclose(VentasArg2018);
	}
	
	return 0;
}
