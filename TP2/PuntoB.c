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

void corte_control(FILE *arg, FILE *tot){
	
	char prov_ant[max], loc_ant[max];
	int suma_prov, suma_loc;
	t_cli cli;
	char aux[max];
	
	rewind(arg);
	
	fread(&cli, sizeof(cli), 1, arg);
	fprintf(tot,"-Clientes totales por localidad y por provincia:\n\n");
	
	while (!feof(arg)){
		
		suma_prov=0;
		strcpy(prov_ant, cli.provincia);
		
		while ((!feof(arg)) && (strcmp(prov_ant, cli.provincia)==0)){
			
			suma_loc=0;
		    strcpy(loc_ant, cli.localidad);
			
			while ((!feof(arg)) && (strcmp(prov_ant, cli.provincia)==0) && (strcmp(loc_ant, cli.localidad)==0)){
				
				suma_loc++;
				suma_prov++;
				fread(&cli, sizeof(cli), 1, arg);
			}
			
			sprintf(aux, "%d", suma_loc);
			fprintf(tot, "Provincia: %sLocalidad: %sTotal: %s\n", prov_ant, loc_ant, aux);
	    }
	    
	   sprintf(aux, "%d", suma_prov);
	   fprintf(tot, "\nProvincia: %sTotal: %s\n\n", prov_ant, aux);
	}
}

void mostrar_datos(FILE *TotCli){
	
	char texto[max];
	
	rewind(TotCli);
	
	fgets(texto, max, TotCli);
	
	while (!feof(TotCli)){
		
		printf("%s", texto);
		
		fgets(texto, max, TotCli);
	}
}

int main(){
	
	FILE *ClientesArg;
	FILE *Tot_Cli;
	
	ClientesArg=fopen("ClientesArg.dat", "rb");
	Tot_Cli=fopen("Tot_Cli.txt", "wt+");
	
	if ((ClientesArg==NULL) || (Tot_Cli==NULL)){
		
		printf("\nNo se pudo crear el archivo.\n");
	}else{
		
		corte_control(ClientesArg, Tot_Cli);
		mostrar_datos(Tot_Cli);
		
		fclose(Tot_Cli);
		fclose(ClientesArg);
	}
	
	return 0;
}
