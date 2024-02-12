#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

enum menu
{
	MENU_ADD = 1,
	MENU_SUB = 2,
	MENU_MUL = 3,
	MENU_DIV = 4
};

int main(void)
{
	int (*add)(int, int);
	int (*sub)(int, int);
	int (*mul)(int, int);
	double (*div)(double, double);
	
	void *calc_add = NULL;
	void *calc_sub = NULL;
	void *calc_mul = NULL;
	void *calc_div = NULL;
	
	int menu_option;
	int arg1, arg2;
	
	char plugin[5];
	printf ("Which libraries do you want to use? (add, sub, mul, div)\n");
	
	while (1){
		printf ("(to stop print \"stop\")\n");
		fgets (plugin, 5, stdin);
		
		if (strcmp (plugin, "stop") == 0){
			break;
		}		
		else if (strcmp (plugin, "add") == 0){
			calc_add = dlopen ("./libadd.so", RTLD_LAZY);
		
			if (calc_add == NULL){
				printf ("No such library\n");	
				return 0;
			}
		
			add = dlsym (calc_add, "add");
		}		
		else if (strcmp (plugin, "sub") == 0){
			calc_sub = dlopen ("./libsub.so", RTLD_LAZY);
			
			if (calc_sub == NULL){
				printf ("No such library\n");	
				return 0;
			}
			
			sub = dlsym (calc_sub, "sub");
		}	
		else if (strcmp (plugin, "mul") == 0){
			calc_mul = dlopen ("./libmul.so", RTLD_LAZY);
		
			if (calc_mul == 0){
				printf ("No such library\n");	
				return 0;
			}
			
			mul = dlsym (calc_mul, "mul");
		}		
		else if (strcmp (plugin, "div") == 0){
			calc_div = dlopen ("./libdiv.so", RTLD_LAZY);
			
			if (calc_div == 0){
				printf ("No such library\n");	
				return 0;
			}
			
			div = dlsym (calc_div, "div");
		}		
		else{
			printf ("No such library\n");
		}	
	
	}
	
	while (1){	
		if (calc_add != NULL){
			printf ("\n1) Addition");
		}					
		if (calc_sub != NULL){
			printf ("\n2) Subtraction");
		}
		if (calc_mul != NULL){
			printf ("\n3) Multiplication");
		}	
		if (calc_div != NULL){
			printf ("\n4) Division");
		}
		
		printf ("\n5) Exit");
		printf ("\nSelect option: ");
		scanf("%d", &menu_option);
		
		if (menu_option == 5){
			if (calc_add != NULL){
				dlclose(calc_add);
			}			
			if (calc_sub != NULL){
				dlclose(calc_sub);
			}		
			if (calc_mul != NULL){
				dlclose(calc_mul);
			}					
			if (calc_div != NULL){
				dlclose(calc_div);
			}
			return 0;
		}
		else{	
			printf ("\narg1 = ");
			scanf ("%d", &arg1);
			printf ("arg2 = ");
			scanf ("%d", &arg2);
			
			switch (menu_option){
				case MENU_ADD:
					add (arg1, arg2);
					break;
				case MENU_SUB:
					sub (arg1, arg2);
					break;
				case MENU_MUL:
					mul (arg1, arg2);
					break;
				case MENU_DIV:
					div (arg1, arg2);
					break;
			}	
		}
	}
}	
