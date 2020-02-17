#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define mf 500 //maximo fisico
#define max_ape 100
#define max_nac 8
#define max_fec 11
#define dat_ape 0
#define dat_fec 2
#define min_mes 5
#define max_mes 7
#define min_dia 8
#define max_dia 10

typedef enum {false, true} bool;

typedef enum {argentina=1, uruguaya, chilena, peruana, boliviana, paraguaya, brasilera} pais;

typedef enum {apellido, nombre, fecha, sexo, nacionalidad} dato;

typedef bool vecpaises[max_nac];

typedef char paises[15];

typedef paises vecnaciones[max_nac];

typedef struct {
	
	char ape[max_ape];
	char nom[max_ape];
	char fecha[max_fec];
	char sexo;
	vecpaises nacionalidades;
} templeado;

typedef templeado vecempleados[mf];

int pasar_texto_a_entero(char texto[], int min, int max){
	
	char texto_carac[2];
	int i, j=0;
	int texto_int;
	
	for (i=min; i<max; i++){
		
		texto_carac[j]=texto[i];
		
		j++;
	}
	
	texto_int=atoi(texto_carac);
	
	return texto_int;
}

bool validar_numero(int num, int max, int min){
	
	bool aux;
	
	if ((num<min) || (num>max)){
		
		aux=false;
	}else{
		
		aux=true;
	}
	
	return aux;
}

void validar_fecha(templeado emp){
	
	int anio, mes, dia;
	bool fec_val=false;
	
	while (fec_val==false){
		
		anio=atoi(emp.fecha);
	    mes=pasar_texto_a_entero(emp.fecha, min_mes, max_mes);
	    dia=pasar_texto_a_entero(emp.fecha, min_dia, max_dia);
	    
	    if ((anio>=1949) && (anio<=2003)){
	    	
	    	switch (mes){
	    		
	    		case 1:
		        case 3:
		        case 5:
		        case 7:
		        case 8:
		        case 10:
		        case 12:
		        	
		        	fec_val=validar_numero(dia, 31, 1);
		        	break;
		        case 4:
		        case 6:
		        case 9:
		        case 11:
		        	
		        	fec_val=validar_numero(dia, 30, 1);
		        	break;
		        case 2:
		        	
		        	if ((((anio%4)==0) && ((anio%100)!=0)) || ((anio%400)==0)){
		        		
		        		fec_val=validar_numero(dia, 29, 1);
					}else{
						
						fec_val=validar_numero(dia, 28, 1);
					}
					break;
				default:
					
					break;
		    }
		}
		
		if (fec_val==false){
			
			printf("Error: verifique los datos e ingrese nuevamente la fecha de nacimiento (aaaa-mm-dd): ");
			fflush(stdin);
			fgets(emp.fecha, max_fec, stdin);
		}
	}
}

void validar_sexo(templeado emp){
	
	while ((emp.sexo!='M') && (emp.sexo!='m') && (emp.sexo!='F') && (emp.sexo!='f')){
		
		printf("Error: verifique los datos e ingrese nuevamente el sexo (M/F): ");
		fflush(stdin);
		scanf("%c", &emp.sexo);
	}
}

void obtener_nacionalidades(vecpaises nac){
	
	int opc,i;
	bool nac_valid=true;
	
	for (i=0; i<max_nac; i++){
		
		nac[i]=false;
	}
	
	printf ("|-Nacionalidades: ");
	printf ("\n1. Argentina");
	printf ("\n2. Uruguaya");
	printf ("\n3. Chilena");
	printf ("\n4. Peruana");
	printf ("\n5. Boliviana");
	printf ("\n6. Paraguaya");
	printf ("\n7. Brasilera\n");
	
	i=0;
	
	do{
		
		if (i!=7){
		
		    printf ("|-Elija las nacionalidades o 0 para salir: ");
	        fflush (stdin);
	        scanf ("%d", &opc);
	    
	        if (i==0){
	    	
	    	    nac_valid=validar_numero(opc, 7, 1);
	    	
	    	    if (nac_valid==false){
	    		
	    		    printf("Error: debe ingresar al menos una nacionalidad valida.\n");
			    }else{
				
				    nac[opc]=true;
					i++;
			    }
		    }else{
			
			    nac_valid=validar_numero(opc, 7, 0);
			
			    if (nac_valid==true){
				
				    if (opc!=0){
					
					    nac[opc]=true;
				        i++;
				    }
			    }else{
				
				    printf("Error: recuerde seleccionar segun las opciones indicadas.\n");
			    }
		    }
		}else{
			
			i++;
		}
	} while (((i<max_nac) && (opc!=0)) || ((i<max_nac) && (nac_valid==false)));
}

void cargar_empleados(vecempleados vec, int *ml){
	
	int i=0;
	
	do{
		
		printf("Ingrese el/los apellido/s del empleado (para finalizar ingrese ""f""): ");
		fflush(stdin);
		fgets(vec[i].ape, max_ape, stdin);
		
		if ((strcmp(vec[i].ape, "f\n")!=0) && (strcmp(vec[i].ape, "F\n")!=0)){
			
			printf("Ingrese el/los nombre/s: ");
			fflush(stdin);
			fgets(vec[i].nom, max_ape, stdin);
			
			printf("Ingrese la fecha de nacimiento (aaaa-mm-dd): ");
			fflush(stdin);
			fgets(vec[i].fecha, max_fec, stdin);
			validar_fecha(vec[i]);
			
			printf("Ingrese el sexo (M/F): ");
			fflush(stdin);
			scanf("%c", &vec[i].sexo);
			validar_sexo(vec[i]);
			
			obtener_nacionalidades(vec[i].nacionalidades);
			i++;
			
			printf("\n");
		}
	} while ((i<mf) && (strcmp(vec[i].ape, "f\n")!=0) && (strcmp(vec[i].ape, "F\n")!=0));
	
	*ml=i-1; //ultima posicion con dato cargado.
}

void elegir_opcion(int *opcion){
	
	int aux_opc;
	bool opc_val=false;
	printf ("\n\t\t\t|----MENU----|\n");
	
	printf ("1. Mostrar nacidos antes del 2000 ordenado por nacimiento.\n");
	printf ("2. Buscar y mostrar datos de apellido de mujer ingresado por usuario, nacidas en verano.\n");
	printf ("3. Mostrar Uruguayos y Argentinos con mas de 1 nacionalidad.\n");
	printf ("4. Mostrar porcentaje de empleados Argentinos.\n");
	printf ("0. salir.\n");
	
	while (opc_val==false){
		
		printf ("\n|-seleccione la opcion a realizar o 0 para salir: ");
		fflush(stdin);
		scanf("%d", &aux_opc);
		opc_val=validar_numero(aux_opc, 4, 0);
		
		if (opc_val==false){
			
			printf("Error: verifique la opcion ingresada.\n");
		}
	}
	
	*opcion=aux_opc;
}

void burbujeo_optimizado(vecempleados vec, int ml, dato dat){
	
	int i=0, j;
	templeado aux_emp;
	bool cont_ciclo=true;
	
	while ((i<ml) && (cont_ciclo==true)) {
		
		cont_ciclo=false;
		
		for (j=0; j<(ml-i); j++) {
			
			if (((dat==fecha) && (strcmp(vec[j].fecha, vec[j+1].fecha)>0)) ||
			   ((dat==apellido) && (strcmp(vec[j].ape, vec[j+1].ape)>0))){
				
				aux_emp=vec[j];
				
				vec[j]=vec[j+1];
				
				vec[j+1]=aux_emp;
				
				cont_ciclo=true;
			}
		}
	    
	    i++;
	}
}

void cargar_nacidos_antes_2000(vecempleados vec, vecempleados aux, int ml, int *max){
	
	int i, j=0;
	
	for (i=0; i<=ml; i++){
		
		if (strcmp(vec[i].fecha, "2000-01-01")<0){
			
			aux[j]=vec[i];
			j++;
		}
	}
	
	*max=j-1;
}

void mostrar_vector(vecempleados vec, int pos_max){
	
	int i, j;
	vecnaciones nac={";", "argentina", "uruguaya", "chilena", "peruana", "boliviana", "paraguaya", "brasilera"};
	
	printf("\n");
	
	if (pos_max>=0){
		
		for (i=0; i<=pos_max; i++){
			
			printf("Apellido/s del empleado: %s", vec[i].ape);
			
			printf("Nombre/s: %s", vec[i].nom);
			
			printf("Fecha de nacimiento: %s\n", vec[i].fecha);
		    
		    printf("Sexo: %c\n", vec[i].sexo);
		    
		    printf("Nacionalidad/es: ");
		    
		    for (j=1; j<max_nac; j++){
		    	
		    	if (vec[i].nacionalidades[j]==true){
		    		
		    		printf("%s ", nac[j]);
				}
	        }
	        
	        printf("\n\n");
	    }
	}else{
		
		printf("No hay datos con las caracteristicas solicitadas.\n");
	}
}

bool validar_verano(char fecha[]){
	
	int mes=pasar_texto_a_entero(fecha, min_mes, max_mes);
	int dia=pasar_texto_a_entero(fecha, min_dia, max_dia);
	bool aux;
	
	switch (mes){
	
	    case 1:
	    case 2:
	    	
	    	aux=true;
	    	break;
	    	
	    case 12:
	    	
	    	if (dia>20){
	    		
	    		aux=true;
			}
			break;
			
		case 3:
			
			if (dia<21){
				
				aux=true;
			}
			break;
		
		default:
			
			aux=false;
			break;
	}
	
	return aux;
}

void cargar_coincidencia(vecempleados vec, vecempleados aux, int pos_central, int *pos, int *cant){
	
	bool es_verano=validar_verano(vec[pos_central].fecha);
	
	if (((vec[pos_central].sexo=='f') || (vec[pos_central].sexo=='F')) && (es_verano==true)){
		
		aux[*pos]=vec[pos_central];
		*pos=*pos+1;
		*cant=*cant+1;
	}
}

void busqueda_lineal(vecempleados vec, vecempleados aux, char ape_aux[], int ml, int pos_central, int *cant){
	
	int aux_cant=-1;
	int i=0, j=pos_central-1;
	
	while ((pos_central<=ml) && (strcmp(ape_aux, vec[pos_central].ape)==0)){
		
		cargar_coincidencia(vec, aux, pos_central, &i, &aux_cant);
		
		pos_central++;
	}
	
	while ((j>=0) && (strcmp(ape_aux, vec[j].ape)==0)){
		
		cargar_coincidencia(vec, aux, j, &i, &aux_cant);
		
		j--;
	}
	
	*cant=aux_cant; //ultima posicion con valor cargado.
}

void busqueda_binaria(vecempleados vec, vecempleados aux, int ml, int *max){
	
	int pos_central;
	int cant=-1;
	int lim_inf=0, lim_sup=ml;
	bool encontrado=false;
	char ape_aux[max_ape];
	
	printf("\nIngrese un apellido para buscar coincidencias: ");
	fflush(stdin);
	fgets(ape_aux, max_ape, stdin);
	
	while ((encontrado==false) && (lim_inf<=lim_sup)){
		
		pos_central=(lim_inf+lim_sup)/2;
		
		if (strcmp(vec[pos_central].ape, ape_aux)==0){
			
			encontrado=true;
			busqueda_lineal(vec, aux, ape_aux, ml, pos_central, &cant);
		}else{
			
			if (strcmp(vec[pos_central].ape, ape_aux)>0){
				
				lim_sup=pos_central-1;
			}else{
				
				lim_inf=pos_central+1;
			}
		}
	}
	
	*max=cant;
}

void cargar_dos_nacionalidades(vecempleados vec, vecempleados aux, int ml, int *max){
	
	int i, j, k=0, cant=-1;
	bool dos_nac;
	
	for (i=0; i<=ml; i++){
		
		dos_nac=false;
		
		if ((vec[i].nacionalidades[argentina]==true) || (vec[i].nacionalidades[uruguaya]==true)){
			
			if (vec[i].nacionalidades[argentina]==true){
				
				j=uruguaya;
			}else{
				
				j=chilena;
			}
			
			while ((j<max_nac) && (dos_nac==false)){
					
				if (vec[i].nacionalidades[j]==true){
						
					dos_nac=true;
					aux[k]=vec[i];
					k++;
					cant++;
				}
					
				j++;
			}
		}
	}
	
	*max=cant;
}

void calcular_porcentaje_arg(vecempleados vec, int ml){
	
	int cant_arg=0;
	int i;
	int total=ml+1;
	float porcentaje;
	
	for (i=0; i<=ml; i++){
		
		if (vec[i].nacionalidades[argentina]==true){
			
			cant_arg++;
		}
	}
	
	porcentaje=(((float)cant_arg)/((float)total))*100;
	
	printf("\nHay un %.2f%% de argentinos sobre el total de empleados.\n", porcentaje);
}

void opciones_a_ejecutar(vecempleados vec, int ml, int opc){
	
	vecempleados aux;
	int max;
	
	switch (opc){
		
		case 1:
			
			cargar_nacidos_antes_2000(vec, aux, ml, &max);
			burbujeo_optimizado(aux, max, dat_fec);
			mostrar_vector(aux, max);
			break;
		
		case 2:
			
			burbujeo_optimizado(vec, ml, dat_ape);
			busqueda_binaria(vec, aux, ml, &max);
			mostrar_vector(aux, max);
			break;
			
		case 3:
			
			cargar_dos_nacionalidades(vec, aux, ml, &max);
			mostrar_vector(aux, max);
			break;
			
		case 4:
			
			calcular_porcentaje_arg(vec, ml);
			break;
			
		default:
			
			printf ("\n\t\tAdios!!...\n");
			break;
	}
}

int main(){
	
	vecempleados emp;
	int ml, opc;
	
	cargar_empleados(emp, &ml);
	
	do{
		
		elegir_opcion(&opc);
		opciones_a_ejecutar(emp, ml, opc);
	} while (opc!=0);
	
	return 0;
}
