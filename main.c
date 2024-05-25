#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//============= ESTRUCTURA ================

//Definí el estado del puzzle como su configuración numérica y
//La dirección de su casilla vacía, representada por un 0. 
//También tiene la lista de acciones, que representa la secuencia de configuraciónes de las transiciones para llegar a
//La solución.
typedef struct
{
   int puzzle[3][3];
   int x_empty;
   int y_empty;
   List * actions; 
   //list tiene size :) con eso limitamos la altura pa que no se    //caiga esto :(
}State;

//====== FUNCIONES EXTRA: MENU ========

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
//Las copié del ejemplo 

//========= FUNCIONES DEL PROGRAMA =========
//Crea un estado nuevo, pero se usa poco. Generalmente los copio.
State* createState(){
  State* n = (State*) malloc(sizeof(State));
  return n;
}

//Crea una copia del estado, utilizando como parámetro el estado a copiar.
//Es útil para obtener los nodos adjacentes en lista, y aparte cuando se
//Copia el estado, se copia también su lista de acciones, permitiendo
//Que se guarde la secuencia que hacen. Así puedo "conectar" los "nodos".
State* copy_s(State* n){
    State *nw = (State*) malloc(sizeof(State));
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
      {
         nw->puzzle[i][j] = n->puzzle[i][j];
      }

   nw->x_empty = n->x_empty;
   nw->y_empty = n->y_empty;
   nw->actions = createList();
   List * aux = first(n->actions);
   while(aux != NULL)
   {
      pushBack(nw->actions, aux);
      aux = next(n->actions);
   }
   return nw;
}

//Lee un archivo de texto que contiene un puzzle 8
//EJEMPLO SE ENCUENTRA EN PUZZLE.TXT
//Puede estar el puzzle en cualquier configuración mientras
//Tenga números no repetidos del 1 al 8 y un 0 que significa que
//Esa casilla está vacía:
State* read_file (char* file_name){
   //reutilizé la función de lectura del sudokulab (flojera)
   State* n =  createState();
   FILE* file = fopen (file_name, "r");
   int i , j;
   for(i=0;i<3;i++)
   {
    for(j=0;j<3;j++)
    {
      if(!fscanf (file, "%d", &n->puzzle[i][j]))
         printf("failed to read data!");
      if (n->puzzle[i][j] == 0)
      {
         //Entonces es la casilla vacía. Llenamos los campos del struct
         //State que la representan.
         n->x_empty = i;
         n->y_empty = j;
      }
    }
   }
  fclose (file);
  return n;
}

//Imprime el nodo (que en este caso representa un estado)
void print_node(State* n)
{
   int i, j;
   for(i = 0; i < 3; i++)
   {
      for(j = 0; j < 3; j++)
      {
         if (n->puzzle[i][j] == 0)
         {
            printf("x ");
         }
         else
         {
            printf("%d ", n->puzzle[i][j]);
         }
      }
      printf("\n");
   }
   printf("\n");
}

//Esta función nos dice si un movimiento que queremos hacer con la 
//Casilla vacía es válido dentro de los límites del puzzle.
//Por ejemplo, no podemos mover la casilla vacía hacia arriba si es
//La primera de la primera fila. Se le pasa como parámetro la config que
//Se le quiere hacer a un estado para pasar a otro.
int is_valid(State *n, int config)
{
   int x_empty = n->x_empty;
   int y_empty = n->y_empty;

   int nw_x;
   int nw_y;
   
   if (config == 1)
   {
      //OPCION ARRIBA
      nw_x = x_empty;
      nw_y = y_empty - 1;
   }
   else if (config == 2)
   {
      //OPCION ABAJO
      nw_x = x_empty;
      nw_y = y_empty + 1;
   }
   else if (config == 3)
   {
      //OPCION IZQUIERDA
      nw_x = x_empty - 1;
      nw_y = y_empty;
   }
   else
   {
      //OPCION DERECHA
      nw_x = x_empty + 1;
      nw_y = y_empty;
   }
   //Se retorna la condición de verdad acerca de si el movimiento
   //Pertenece dentro de los límites de la matriz 3x3
   return (nw_x >= 0 && nw_x < 3 && nw_y >= 0 && nw_y < 3);
}

//Se encarga de transicionar de un estado al otro, usando la config para 
//Hacerlo. Como ya se utilizó is valid, se asegura de que está en los
//Límites de la matriz 3x3. Cuando se identifica el movimiento que se
//Quiere hacer.
State * transicion(State* n, int config)
{
   //Arriba = 1; Abajo = 2; Izquierda = 3; Derecha = 4; :)
   
   //No es necesario buscar la casilla vacía ya que ya la tenemos:
   int x = n->x_empty;   
   int y = n->y_empty;
   int * config_ptr = (int *)malloc(sizeof(int));
   *config_ptr = config;
   
   if (config == 1)
   {
      //OPCION ARRIBA
      //Ddebemos cambiar el nodo del lugar establecido "arriba" al lugar        //Del nodo vacío. Cuando lo hagamos, debemos retornar el nodo, y          //Cambiar sus X e Y respectivos para que no se piense que la              //Casilla vacía quedó igual.
      
      //Vamos a copiar el espacio vacio a la posicion que se pide, por
      //Lo que debemos guardar el número que había en la casilla
      //A la que se va a pegar, ya que debemos pegarlo de nuevo
      //En la casilla vacía. (También se puede hacer al revés):
      
      int aux_arriba = n->puzzle[x][y - 1];
      n->puzzle[x][y - 1] = n->puzzle[x][y];
      n->puzzle[x][y] = aux_arriba;
      
      //Actualizamos el vacío, aquí solo es necesario modificar y:
      n->y_empty = y - 1;
      pushBack(n->actions, config_ptr); //La lista de acciones marca el 
      //Camino!! Sirve para limitar la altura del grafo, e imprimir 
      //Posteriormente ese camino solución. (Si se encuentra)
      return n;
   }
   else if (config == 2)
   {
      //OPCION ABAJO
      //De aquí en adelante se copian los pasos de la opción 1

      int aux_abajo = n->puzzle[x][y + 1];
      n->puzzle[x][y + 1] = n->puzzle[x][y];
      n->puzzle[x][y] = aux_abajo;

      //Actualizamos el vacío, aquí solo es necesario modificar y:
      n->y_empty = y + 1;
      pushBack(n->actions, config_ptr);
      return n;
   }
   else if (config == 3)
   {
      //OPCION IZQUIERDA
      int aux_izquierda = n->puzzle[x - 1][y];
      n->puzzle[x - 1][y] = n->puzzle[x][y];
      n->puzzle[x][y] = aux_izquierda;

      //Actualizamos el vacío, aquí solo es necesario modificar x:
      n->x_empty = x - 1;
      pushBack(n->actions, config_ptr);
      return n;
   }
   else
   {
      //OPCION DERECHA
      int aux_derecha = n->puzzle[x + 1][y];
      n->puzzle[x + 1][y] = n->puzzle[x][y];
      n->puzzle[x][y] = aux_derecha;

      //Actualizamos el vacío, aquí solo es necesario modificar x:
      n->x_empty = x + 1;
      pushBack(n->actions, config_ptr);
      return n;
   }
   //No debería pasar nunca porque pasó por is valid pero por si a caso.
   return NULL;
}


List* get_adj_nodes(State * n)
{
   List* list = createList();
   //Usamos los valores de k como configuraciones:
   for(int k = 1; k <= 4; k++)
   {
      State* cpy = copy_s(n);
      if (is_valid(cpy, k))
      {   
         State *nw = transicion(cpy, k); //la transición
         pushBack(list, nw);
      }
   }
   return list;
}

//Comprueba si el estado en que nos encontramos es el final/solución.
int is_final(State* n)
{
   int i, k;
   //Lista auxiliar: comprueba que los números estén en orden y el último    //Sea el 0 (vacío). También se puede hacer con una matriz.
   int lista[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
   int index = 0;
   for (i = 0; i < 3; i++)
   {
      for(k = 0; k < 3; k++)
      {
         if (n->puzzle[i][k] != lista[index])
         {
            return 0;
         }
         index++;
      }
   }
   return 1;
}

 //Realiza una búsqueda en profundidad para encontrar la solución al 
//Puzzle 8. Explora todos los caminos posibles desde el estado inicial, profundizando en rama de movimientos antes de retroceder, hasta encontrar el estado final que resuelve el puzzle o alcanzar una profundidad máxima de 15 movimientos (ahí paso a la siguiente rama).
State* DFS(State* initial, int* cont)
{
   Stack *stack = createStack();

   push(stack, initial);
   while (top(stack) != NULL)
   {
      //saco/elimino.
      State *aux_stack = top(stack);
      pop(stack);
      if (get_size(aux_stack->actions) >= 13)
      {
         //Si se pasa de 13 movimientos, me cambio de rama.
         continue;
      }
      if (is_final(aux_stack))
      {
         free(stack);
         return aux_stack;
      }
      //No es el estado final así que hay que obtener los vecinos:
      List *list_vecinos = get_adj_nodes(aux_stack);
      State *list_index = first(list_vecinos);
      while (list_index != NULL)
      {
         push(stack, list_index); //se ponen en el stack cada uno de los elementos de la lista que son los vecinos :D
         list_index = next(list_vecinos); //avanzo
      }
      clean(list_vecinos); 
      free(list_vecinos);
      //liberé memoria porque pasé a la otra rama.
      *cont = *cont + 1;
   }
   free(stack);
   return NULL;
}

//Realiza una búsqueda en anchura para encontrar la solución al puzzle 8. //Para eso, explora todos los caminos posibles desde el estado inicial 
//Nivel por nivel; primero revisa todos los estados alcanzables en un 
//Solo movimiento, (1, 2, 3, 4), luego todos los estados alcanzables en 
//Dos movimientos (se comienzan a combinar), y así sucesivamente, hasta 
//Encontrar el estado final que resuelve el puzzle.
State * BFS(State *initial, int *cont)
{
   Queue *cola = queue_create();

   queue_insert(cola, initial);
   while (queue_front(cola) != NULL)
   {
      //saco/elimino.
      State *aux_queue = queue_front(cola);
      queue_remove(cola);
      /*if (get_size(aux_queue->actions) >= 15)
      {
         continue;
      }*/ //Funciona igual
      if (is_final(aux_queue))
      {
         free(cola);
         return aux_queue;
      }
      //No es el estado final así que hay que obtener los vecinos:
      List *list_vecinos = get_adj_nodes(aux_queue);
      State *list_index = first(list_vecinos);
      while (list_index != NULL)
      {
         queue_insert(cola, list_index); //se ponen en el stack cada uno de los elementos de la lista que son los vecinos :D
         list_index = next(list_vecinos); //avanzo
      }
      clean(list_vecinos);
      free(list_vecinos);
      //liberé memoria porque me cambié de rama.
      *cont = *cont + 1;
   }
   free(cola);
   return NULL;
}

//Tenemos que imprimir los estados en orden que fueron las 
//Configuraciones que permitieron llegar al estado final. Para eso hay 
//Que transformar el nodo inicial en el nodo n, pero con la lista de 
//Acciones tenemos todos sus pasos. Solo debemos pasarlos por transicion //De nuevo:
void imprimir_todas_transiciones(State * ini, State *fn)
{
   List * list = fn->actions; 
   int * aux = first(list);
   //Imprimimos el inicial
   printf("\nEstado Inicial :\n");
   print_node(ini);

   //Ahora empezamos a transicionar en orden.
   State *trans_state = copy_s(ini);
   int cont = 2;
   while(aux != NULL)
   {
      printf("Estado n° %d del puzzle:\n", cont);
      State * nw = transicion(trans_state, *aux);
      print_node(nw);
      trans_state = nw; //Ahora hacemos la transición al nuevo estado.
      aux = next(list);
      cont++;
   }
   free(list);
   free(trans_state);
}

int main()
{
   printf("\n***** Bienvenid@ ******\n\n");
   printf("*~ Se leerá el puzzle 8 del archivo puzzle.txt. \n");
   printf("*~ Asegúrate que el puzzle que quieres resolver esté ahí. \n\n");
   
   //Se lee el archivo, se puede modificar al puzzle 8 que se desee.
   State* initial= read_file("puzzle.txt");
   initial->actions = createList();

   //====================================
   int cont = 0;
   int cont_2 = 0;
   State * fn;
   State * fn_2;
   //=======Cosas de búsquedas===========
   char opcion;

   do {
      printf("Resolvamos el puzzle 8 que cargaste:\n\n");
      puts("========================================");
      puts("     Escoge método de búsqueda");
      puts("========================================");
      
      puts("1) Búsqueda en Profundidad");
      puts("2) Buscar en Anchura");
      puts("3) Buscar Mejor Primero");
      puts("4) Salir");
      
      printf("Ingresa tu opción del menú: ");
      scanf(" %c", &opcion);
      
      switch (opcion) 
      {
         //DFS
         case '1':
            printf("\n==========================\n");
            printf(" Búsqueda en Profundidad:\n");
            printf("==========================\n");
            fn = DFS(initial, &cont);
            imprimir_todas_transiciones(initial, fn);
            printf("Número de iteraciones para llegar a la solución: %d \n\n", cont);
            cont = 0; //Si no las almacena para siempre y las suma 
            //Cada vez que se haga el dfs :/
            break;
         //BFS
         case '2':
            printf("\n==========================\n");
            printf(" Búsqueda en Anchura:\n");
            printf("==========================\n");
            fn_2 = BFS(initial, &cont_2);
            imprimir_todas_transiciones(initial, fn_2);
            printf("Número de iteraciones para llegar a la solución: %d \n\n", cont_2);
            cont_2 = 0;
            break;
         case '3':
            printf("\nAún no se implementa esta funcionalidad :(\n");
            //best_first(estado_inicial);
            break;
         case '4':
            printf("\nSaliendo del programa...\n");
            break;
         default:
            printf("\nOpción inválida. Vuelve a intentarlo!\n");
            break;
      }
      presioneTeclaParaContinuar();
      limpiarPantalla();
      
   } while (opcion != '4');
   return 0;
}