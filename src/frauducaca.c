#include<stdio.h>
#include<limits.h>

#define MAX_NUMEROS 200000
#define MAX_VALOR 200
#define TAM_MAX_LINEA (MAX_NUMEROS*4)
#define FRAUDUCACA_MAX_NUMEROS_POR_HEAP (MAX_NUMEROS>>1)+1
#define FRAUDUCACA_MAX_NUMEROS_REDONDEADO (1<<(CACA_X_MAX_PROFUNDIDAD-2))
#define FRAUDUCACA_MAX_NODOS (1 << CACA_X_MAX_PROFUNDIDAD)
#define FRAUDUCACA_VALOR_INVALIDO -1
#define FRAUDUCACA_MAX_VALORES_INT ((unsigned int)((unsigned int)INT_MAX-(INT_MIN)))

#define FRAUDUCACA_BUF_STATICO_DUMP_ARBOL (char[1000] ) { '\0' }

//#define FRAUDUCACA_VALIDAR_ARBOLINES

/*
 #define caca_log_debug printf
 */
#define caca_log_debug(formato, args...) 0
#define assert_timeout(condition) assert(condition);
/*
 #define assert_timeout(condition) 0
 #define assert_timeout(condition) if(!(condition)){printf("fuck\n");sleep(10);assert(condition);}
 */

typedef char tipo_dato;
typedef unsigned int natural;
typedef long long entero_largo;
typedef unsigned long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

#define max(x,y) ((x) < (y) ? (y) : (x))
#define min(x,y) ((x) < (y) ? (x) : (y))

/*Declaring heap globally so that we do not need to pass it as an argument every time*/

/* Heap used here is Min Heap */

#if 1

typedef struct heap_shit {
	bool min;
	natural heap_size;
	tipo_dato heap[FRAUDUCACA_MAX_NUMEROS_POR_HEAP];
} heap_shit;

/*Initialize Heap*/
void heap_shit_init(heap_shit *heap) {
	heap->heap_size = 0;
	heap->heap[0] = FRAUDUCACA_VALOR_INVALIDO;
}
/*Insert an element into the heap */
void heap_shit_insert(heap_shit *heap_ctx, tipo_dato element) {
	natural heap_size = ++heap_ctx->heap_size;
	tipo_dato *heap;

	heap = heap_ctx->heap;

	heap[heap_size] = element; /*Insert in the last place*/
	/*Adjust its position*/
	natural now = heap_size;
	while (heap[now / 2] > element) {
		heap[now] = heap[now / 2];
		now /= 2;
	}
	heap[now] = element;
}
tipo_dato heap_shit_delete(heap_shit *heap_ctx) {
	natural heap_size = heap_ctx->heap_size;
	natural child, now;
	tipo_dato minElement, lastElement;
	tipo_dato *heap;
	heap = heap_ctx->heap;
	/* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased.
	 Now heap[1] has to be filled. We put the last element in its place and see if it fits.
	 If it does not fit, take minimum element among both its children and replaces parent with it.
	 Again See if the last element fits in that place.*/
	minElement = heap[1];
	lastElement = heap[heap_size--];
	/* now refers to the index at which we are now */
	for (now = 1; now * 2 <= heap_size; now = child) {
		/* child is the index of the element which is minimum among both the children */
		/* Indexes of children are i*2 and i*2 + 1*/
		child = now * 2;
		/*child!=heap_size beacuse heap[heap_size+1] does not exist, which means it has only one
		 child */
		if (child != heap_size && heap[child + 1] < heap[child]) {
			child++;
		}
		/* To check if the last element fits ot not it suffices to check if the last element
		 is less than the minimum element among both the children*/
		if (lastElement > heap[child]) {
			heap[now] = heap[child];
		} else /* It fits there */
		{
			break;
		}
	}
	heap[now] = lastElement;
	heap_ctx->heap_size = heap_size;
	return minElement;
}

void heap_shit_dumpear(heap_shit *heap_ctx) {
	natural heap_size = heap_ctx->heap_size;
	for (int i = 0; i <= heap_size; i++) {
		printf("mierda %u es %u\n", i, heap_ctx->heap[i]);
	}
}

#endif
int main() {
	heap_shit *heap_ctx = &(heap_shit ) { 0 };
	int number_of_elements;
//	scanf("%d", &number_of_elements);
	int iter, element;
	heap_shit_init(heap_ctx);
	tipo_dato caca_prueba[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	number_of_elements = sizeof(caca_prueba);
	printf("nume elems %u\n", number_of_elements);
	for (iter = 0; iter < number_of_elements; iter++) {
//		scanf("%d", &element);
		element = caca_prueba[iter];
		heap_shit_insert(heap_ctx, element);
//		printf("dumpeando cabron ins\n");
//		heap_shit_dumpear(heap_ctx);
	}
	for (iter = 0; iter < number_of_elements; iter++) {
		printf("%d ", heap_shit_delete(heap_ctx));
//		printf("dumpeando cabron del\n");
//		heap_shit_dumpear(heap_ctx);
	}
	printf("\n");
	return 0;
}
