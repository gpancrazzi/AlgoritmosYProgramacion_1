#include<stdio.h>
#include<string.h>

#define max_fecha 9
#define max_mes 13

typedef struct {
	
	int anio;
	int mes;
	int num_sucursal;
	float importe;
} t_vts_his;

typedef struct {
	
	char fecha[max_fecha];
	int num_cliente;
	int num_sucursal;
	int articulo;
	int cantidad;
	float importe;
} t_vts_arg;

typedef t_vts_his vec_his[max_mes]; //vector de registros de ventas con 12 posiciones (una para cada mes del año).

int calcular_mes(t_vts_arg arg){
	
	int i, j=0;
	int mes;
	char aux_mes[3];
	
	for (i=4; i<6; i++){
		
		aux_mes[j]=arg.fecha[i];
		j++;
	}
	
	mes=atoi(aux_mes);
	
	return mes;
}

void cargar_vector(vec_his vec, t_vts_arg arg){    //Modulo para inicializar el vector de registros de ventas. 
	
	int i;
	
	for (i=1; i<max_mes; i++){
		
		vec[i].anio=2018; //corresponde a las ventas del archivo de ventas de Argentina durante el 2018.
		vec[i].mes=i;
		vec[i].num_sucursal=arg.num_sucursal; //el numero de sucursal se corresponde con el que se pasa desde el modulo "actualizar_por_mezcla".
		vec[i].importe=0; //se inicializa en 0 el importe de ventas.
	}
}

void escribir_en_archivo(FILE *Act, vec_his vec){
	
	int i;
	
	for (i=1; i<max_mes; i++){
		
		if (vec[i].importe!=0){ //si el importe es mayor a 0, en ese mes, quiere decir que hubo ventas, por lo tanto, se escriben en el archivo actualizado.
			
			fwrite(&vec[i], sizeof(vec[i]), 1, Act); 
		}
	}
}

void actualizar_por_mezcla(FILE *His, FILE *Arg, FILE *Act){
	
	t_vts_his his;
	t_vts_arg arg;
	vec_his vec;
	int mes;
	
	rewind(His);
	rewind(Arg);
	
	fread(&his, sizeof(his), 1, His);
	fread(&arg, sizeof(arg), 1, Arg);
	
	while ((!feof(His)) && (!feof(Arg))){
		
		if (his.num_sucursal==arg.num_sucursal){
			
			if (his.anio<2018){
				
				fwrite(&his, sizeof(his), 1, Act);
				fread(&his, sizeof(his), 1, His);
			}else{
				
				cargar_vector(vec, arg);
				
				while ((!feof(Arg)) && (vec[1].num_sucursal==arg.num_sucursal)){ //se recorre el archivo de ventas arg hasta que cambie el num de suc o sea eof.
					
					mes=calcular_mes(arg); //se calcula el mes de la venta.
					vec[mes].importe=vec[mes].importe+arg.importe; //se suma el importe de la venta en la posicion del vector correspondiente al mes.
					fread(&arg, sizeof(arg), 1, Arg);
				}
				
				escribir_en_archivo(Act, vec); //se escribe en el archivo actualizado los registros contenidos en el vector.
			}
		}else{
			
			if (his.num_sucursal<arg.num_sucursal){
				
				fwrite(&his, sizeof(his), 1, Act);
				fread(&his, sizeof(his), 1, His);
			}else{
				
				cargar_vector(vec, arg);
				
				while ((!feof(Arg)) && (vec[1].num_sucursal==arg.num_sucursal)){
					
					mes=calcular_mes(arg);
					vec[mes].importe=vec[mes].importe+arg.importe;
					fread(&arg, sizeof(arg), 1, Arg);
				}
				
			    escribir_en_archivo(Act, vec);
			}
		}
	}
	
	while (!feof(His)){
		
		fwrite(&his, sizeof(his), 1, Act);
		fread(&his, sizeof(his), 1, His);
	}
	
	while (!feof(Arg)){
		
		cargar_vector(vec, arg);
				
		while ((!feof(Arg)) && (vec[1].num_sucursal==arg.num_sucursal)){
					
			mes=calcular_mes(arg);
			vec[mes].importe=vec[mes].importe+arg.importe;
			fread(&arg, sizeof(arg), 1, Arg);
		}
				
		escribir_en_archivo(Act, vec);
	}
}

void mostrar_datos(FILE *Act){
	
	t_vts_his reg;
	
	rewind(Act);
	
	fread(&reg, sizeof(reg), 1, Act);
	
	printf("Num Suc/ Anio/ \tMes/ \tImporte\n");
	
	while (!feof(Act)){
		
		printf("\n%d \t %d \t%d \t$%.2f", reg.num_sucursal, reg.anio, reg.mes, reg.importe);
		
		fread(&reg, sizeof(reg), 1, Act);
	}
}

int main(){
	
	FILE *VentasHistorico;
	FILE *VentasArg2018;
	FILE *VentasAct;
	
	VentasHistorico=fopen("VentasHistorico.dat", "rb");
	VentasArg2018=fopen("VentasArg2018.dat", "rb");
	VentasAct=fopen("VentasAct.dat", "wb+");
	
	if ((VentasHistorico==NULL) || (VentasArg2018==NULL) || (VentasAct==NULL)){
		
		printf("\nNo se pudo abrir el archivo.\n");
	}else{
		
		actualizar_por_mezcla(VentasHistorico, VentasArg2018, VentasAct);
		mostrar_datos(VentasAct);
		
		fclose(VentasAct);
		fclose(VentasHistorico);
		fclose(VentasArg2018);
	}
	
	return 0;
}
