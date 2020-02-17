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

void actualizar_por_mezcla(FILE *Arg, FILE *Mun, FILE *Act){
	
	t_suc arg, mun;
	
	rewind(Arg);
	rewind(Mun);
	
	fread(&arg, sizeof(arg), 1, Arg);
	fread(&mun, sizeof(mun), 1, Mun);
	
	while ((!feof(Arg)) && (!feof(Mun))){
		
		if (arg.num_sucursal<mun.num_sucursal){
			
			fwrite(&arg, sizeof(arg), 1, Act);
			fread(&arg, sizeof(arg), 1, Arg);
		}else{
			
			fwrite(&mun, sizeof(mun), 1, Act);
			fread(&mun, sizeof(mun), 1, Mun);
		}
	}
	
	while (!feof(Arg)){
		
		fwrite(&arg, sizeof(arg), 1, Act);
		fread(&arg, sizeof(arg), 1, Arg);
	}
	
	while (!feof(Mun)){
		
		fwrite(&mun, sizeof(mun), 1, Act);
		fread(&mun, sizeof(mun), 1, Mun);
	}
}

void mostrar_datos(FILE *arch){
	
	t_suc suc;
	
	rewind(arch);
	
	fread(&suc, sizeof(suc), 1, arch);
	
	printf("-Sucursales Mundiales:\n\n");
	
	while (!feof(arch)){
		
		printf("Num sucursal: %d\nPais: %sNombre: %sDireccion: %sTelefono: %s\n", suc.num_sucursal, suc.pais, suc.nombre, suc.direccion, suc.telefono);
		
		fread(&suc, sizeof(suc), 1, arch);
	}
}

int main(){
	
	FILE *SucursalesArg;
	FILE *SucMundo;
	FILE *SucMundoAct;
	
	SucursalesArg=fopen("SucursalesArg.dat", "rb");
	SucMundo=fopen("SucMundo.dat", "rb");
	SucMundoAct=fopen("SucMundoAct.dat", "wb+");
	
	if ((SucursalesArg==NULL) || (SucMundo==NULL) || (SucMundoAct==NULL)){
		
		printf("\nNo se pudo crear el archivo.\n");
	}else{
		
		actualizar_por_mezcla(SucursalesArg, SucMundo, SucMundoAct);
		mostrar_datos(SucMundoAct);
		
		fclose(SucMundoAct);
		fclose(SucursalesArg);
		fclose(SucMundo);
	}
	
	return 0;
}
