#include<stdio.h>
#include<limits.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sys/time.h>
#include <math.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

typedef unsigned char tipo_dato;
typedef unsigned int natural;
typedef long long entero_largo;
typedef unsigned long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

#define MAX_NUMEROS 200000
#define MAX_VALOR 200
#define MAX_INDEX MAX_VALOR+1
#define TAM_MAX_LINEA (MAX_NUMEROS*4)
#define FRAUDUCACA_MAX_NUMEROS_POR_HEAP (MAX_NUMEROS>>1)+1
#define FRAUDUCACA_MAX_NUMEROS_REDONDEADO (1<<(CACA_X_MAX_PROFUNDIDAD-2))
#define FRAUDUCACA_MAX_NODOS (1 << CACA_X_MAX_PROFUNDIDAD)
#define FRAUDUCACA_VALOR_INVALIDO -1
#define FRAUDUCACA_MAX_VALORES_INT ((unsigned int)((unsigned int)INT_MAX-(INT_MIN)))

#define FRAUDUCACA_BUF_STATICO (char[10000] ) { '\0' }

//#define FRAUDUCACA_VALIDAR_ARBOLINES
//#define FRAUDUCACA_DUMPEAR

#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
//#define CACA_COMUN_LOG
#endif

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#if 1
#define CACA_LOG_MAX_TAM_CADENA 20000
#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2
/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){printf("fuck\n");sleep(10);}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifndef ONLINE_JUDGE
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

void caca_comun_timestamp(char *stime) {
	time_t ltime;
	struct tm result;
	long ms;
	struct timespec spec;
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

	caca_comun_current_utc_time(&spec);
#ifndef ONLINE_JUDGE
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
			"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
			+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = { '\0' };
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = { '\0' };
	char cadena_timestamp[100] = { '\0' };

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
}

static char *caca_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

static char *caca_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

static inline bool caca_comun_checa_bit(bitch_vector *bits,
		unsigned long posicion) {
	bool res = falso;
	int idx_arreglo = 0;
	int idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	res = !!(bits[idx_arreglo]
			& (bitch_vector) ((bitch_vector) 1 << idx_registro));

	return res;
}

static inline void caca_comun_asigna_bit(bitch_vector *bits,
		unsigned long posicion) {
	int idx_arreglo = 0;
	int idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	bits[idx_arreglo] |= (bitch_vector) ((bitch_vector) 1 << idx_registro);

}

static inline void caca_comun_limpia_bit(bitch_vector *bits,
		unsigned long posicion) {
	int idx_arreglo = 0;
	int idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	bits[idx_arreglo] &= (bitch_vector) ~((bitch_vector) 1 << idx_registro);

}

#endif

/*Declaring heap globally so that we do not need to pass it as an argument every time*/

/* Heap used here is Min Heap */

#if 1

typedef struct heap_shit {
	bool min;
	natural heap_size;
	tipo_dato heap[FRAUDUCACA_MAX_NUMEROS_POR_HEAP];
	natural indices_valores[MAX_INDEX][MAX_NUMEROS];
	natural num_indices_valores[MAX_INDEX];
	natural mapeo_idx_heap_a_pos_ocurrencia[MAX_NUMEROS];
} heap_shit;

/*Initialize Heap*/
void heap_shit_init(heap_shit *heap, bool es_min) {
	heap->heap_size = 0;
	heap->min = es_min;
	heap->heap[0] = FRAUDUCACA_VALOR_INVALIDO;
	memset(heap->mapeo_idx_heap_a_pos_ocurrencia,FRAUDUCACA_VALOR_INVALIDO,sizeof(heap->mapeo_idx_heap_a_pos_ocurrencia));
}

void heap_shit_fini(heap_shit *heap_ctx) {
	memset(heap_ctx->mapeo_idx_heap_a_pos_ocurrencia,FRAUDUCACA_VALOR_INVALIDO,sizeof(heap_ctx->mapeo_idx_heap_a_pos_ocurrencia));
}

/*Insert an element into the heap */
void heap_shit_insert(heap_shit *heap_ctx, tipo_dato element) {
	natural heap_size = ++heap_ctx->heap_size;
	tipo_dato *heap = NULL;
	natural *mapeo_inv=heap_ctx->mapeo_idx_heap_a_pos_ocurrencia;

	heap = heap_ctx->heap;

	heap[heap_size] = element; /*Insert in the last place*/
	/*Adjust its position*/
	natural now = heap_size;
	while (((heap_ctx->min &&  (heap[now / 2]==(tipo_dato)FRAUDUCACA_VALOR_INVALIDO?-1:(int)heap[now / 2]) > (int) element)
			|| (!heap_ctx->min && (natural) heap[now / 2] < (natural) element))) {
//printf("caca now %u de heap %u elem %u\n",now,heap[now],element);
		natural idx_pos = 0;
		idx_pos = mapeo_inv[now/2];
		assert_timeout(idx_pos!=FRAUDUCACA_VALOR_INVALIDO);

		heap_ctx->indices_valores[heap[now / 2]][idx_pos] = now;
		
		mapeo_inv[now/2]=FRAUDUCACA_VALOR_INVALIDO;

		mapeo_inv[now]=idx_pos;

		heap[now] = heap[now / 2];
		now /= 2;
	}
//printf("raise now %u con heap %u y elem %u res %u\n",now,heap[now / 2],element, (unsigned int)heap[now / 2]>(unsigned int)element);	

	mapeo_inv[now]=heap_ctx->num_indices_valores[element];

	heap[now] = element;
	heap_ctx->indices_valores[element][heap_ctx->num_indices_valores[element]++] =
			now;

//tablin_idx_pos_en_heap
}

tipo_dato heap_shit_delete(heap_shit *heap_ctx, natural idx_a_borrar) {
	natural heap_size = heap_ctx->heap_size;
	natural idx_pos = 0;
	natural idx_pos_las_elem_ocur = FRAUDUCACA_VALOR_INVALIDO;
	natural child, now;
	tipo_dato minElement, lastElement;
	tipo_dato *heap;
	natural *mapeo_inv=heap_ctx->mapeo_idx_heap_a_pos_ocurrencia;

	heap = heap_ctx->heap;

	assert_timeout(heap_size>=idx_a_borrar);
	if (heap_size > idx_a_borrar) {
		idx_pos_las_elem_ocur=mapeo_inv[heap_size];
		assert_timeout(idx_pos_las_elem_ocur!=FRAUDUCACA_VALOR_INVALIDO);
		mapeo_inv[heap_size]=FRAUDUCACA_VALOR_INVALIDO;
		caca_log_debug("el mapeo inverso del ultimo elemento %u es %u",
				heap_size, idx_pos_las_elem_ocur);
	}

	/* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased.
	 Now heap[1] has to be filled. We put the last element in its place and see if it fits.
	 If it does not fit, take minimum element among both its children and replaces parent with it.
	 Again See if the last element fits in that place.*/
	minElement = heap[idx_a_borrar];
	lastElement = heap[heap_size--];

	idx_pos=mapeo_inv[idx_a_borrar];
	assert_timeout(idx_pos!=FRAUDUCACA_VALOR_INVALIDO);
	
	mapeo_inv[idx_a_borrar]=FRAUDUCACA_VALOR_INVALIDO;

	caca_log_debug("el mapeo inverso del tope que se elimina %u es %u", idx_a_borrar,
			idx_pos);
	if (heap_ctx->num_indices_valores[minElement] > 1
			&& idx_pos != (heap_ctx->num_indices_valores[minElement] - 1)) {
		natural idx_ocurrencia_ultimo =
				heap_ctx->indices_valores[minElement][--heap_ctx->num_indices_valores[minElement]];
		heap_ctx->indices_valores[minElement][idx_pos] = idx_ocurrencia_ultimo;
		if (minElement == lastElement
				&& idx_ocurrencia_ultimo == heap_size + 1) {
			caca_log_debug(
					"como solo ay un numero en el heap la ultima ocurrencia es la que se actualizara el idx de la ocurrencia a actualizar se modifica de %u a %u",
					idx_pos_las_elem_ocur, idx_pos);
			heap_ctx->indices_valores[minElement][idx_pos] =
					FRAUDUCACA_VALOR_INVALIDO;
			idx_pos_las_elem_ocur = idx_pos;
		} else {
			mapeo_inv[idx_ocurrencia_ultimo]=idx_pos;
		}
		heap_ctx->indices_valores[minElement][heap_ctx->num_indices_valores[minElement]
				+ 1] = 0;

	} else {
		heap_ctx->indices_valores[minElement][--heap_ctx->num_indices_valores[minElement]] =
				0;
	}

	now = idx_a_borrar;
	if(((heap_ctx->min 
	     &&  (heap[now>>1]==(tipo_dato)FRAUDUCACA_VALOR_INVALIDO?-1:(int)heap[now>>1]) > (int) lastElement)
	   || (!heap_ctx->min && (natural) heap[now>>1] < (natural) lastElement))) {
		while (((heap_ctx->min &&  (heap[now / 2]==(tipo_dato)FRAUDUCACA_VALOR_INVALIDO?-1:(int)heap[now / 2]) > (int) lastElement)
				|| (!heap_ctx->min && (natural) heap[now / 2] < (natural) lastElement))) {
	//printf("caca now %u de heap %u elem %u\n",now,heap[now],element);
			natural idx_pos = 0;
			idx_pos = mapeo_inv[now/2];
			assert_timeout(idx_pos!=FRAUDUCACA_VALOR_INVALIDO);

			heap_ctx->indices_valores[heap[now / 2]][idx_pos] = now;
			
			mapeo_inv[now/2]=FRAUDUCACA_VALOR_INVALIDO;

			mapeo_inv[now]=idx_pos;

			heap[now] = heap[now / 2];
			now /= 2;
		}
	}
	else
	{

		/* now refers to the index at which we are now */
		for (now = idx_a_borrar; now * 2 <= heap_size; now = child) {
			/* child is the index of the element which is minimum among both the children */
			/* Indexes of children are i*2 and i*2 + 1*/
			child = now * 2;
			/*child!=heap_size beacuse heap[heap_size+1] does not exist, which means it has only one
			 child */
			if (child != heap_size
					&& ((heap_ctx->min && heap[child + 1] < heap[child])
							|| (!heap_ctx->min && heap[child + 1] > heap[child]))) {
				child++;
			}
			/* To check if the last element fits ot not it suffices to check if the last element
			 is less than the minimum element among both the children*/
	//printf("last %u heap %u\n",lastElement,heap[child]);
			if ((heap_ctx->min && lastElement > heap[child])
					|| (!heap_ctx->min && lastElement < heap[child])) {
				idx_pos=mapeo_inv[child];
				assert_timeout(idx_pos!=FRAUDUCACA_VALOR_INVALIDO);

				heap_ctx->indices_valores[heap[child]][idx_pos] = now;

				mapeo_inv[child]=FRAUDUCACA_VALOR_INVALIDO;

				mapeo_inv[now]=idx_pos;

				heap[now] = heap[child];
			} else /* It fits there */
			{
				break;
			}
		}
	}

	if (idx_pos_las_elem_ocur != FRAUDUCACA_VALOR_INVALIDO) {
		mapeo_inv[now]=idx_pos_las_elem_ocur;
		heap_ctx->indices_valores[lastElement][idx_pos_las_elem_ocur] = now;
	}
	heap[now] = lastElement;
	heap_ctx->heap_size = heap_size;
	return minElement;
}

void heap_shit_borrar_directo(heap_shit *heap_ctx, tipo_dato num_a_borrar) {
	natural heap_size = heap_ctx->heap_size;
	natural (*indices_valores)[MAX_NUMEROS]=heap_ctx->indices_valores;
	natural *num_indices_valores=heap_ctx->num_indices_valores;
	assert_timeout(heap_size);

	natural num_ocurrencias=num_indices_valores[num_a_borrar];
	assert_timeout(num_ocurrencias);
	natural idx_a_borrar=indices_valores[num_a_borrar][--num_ocurrencias];
	assert_timeout(idx_a_borrar!=FRAUDUCACA_VALOR_INVALIDO);

	heap_shit_delete(heap_ctx, idx_a_borrar);
}

void heap_shit_dumpear(heap_shit *heap_ctx) {
	natural heap_size = heap_ctx->heap_size;
	natural *mapeo_inv=heap_ctx->mapeo_idx_heap_a_pos_ocurrencia;
	for (int i = 0; i <= heap_size; i++) {
		caca_log_debug("mierda %u es %u", i, heap_ctx->heap[i]);
	}
	caca_log_debug("los mapeos inversos:");
	for (int i=0;i<MAX_NUMEROS;i++){
		caca_log_debug("la llave %u mapea a %u", i, mapeo_inv[i]);
	}
	caca_log_debug("las ocurrencias de cada pendejo:");
	for (int i = 0; i < MAX_INDEX; i++) {
		if (heap_ctx->num_indices_valores[i]) {
			caca_log_debug("el num %u tiene las ocurrencias %s", i,
					caca_arreglo_a_cadena_natural(heap_ctx->indices_valores[i],heap_ctx->num_indices_valores[i],FRAUDUCACA_BUF_STATICO));
		}
	}
}

void heap_shit_valida_referencias_inversas(heap_shit *heap_ctx) {
	natural num_elems = 0;
	natural num_elems_mapeo = 0;
	natural heap_size = heap_ctx->heap_size;
	tipo_dato *heap = heap_ctx->heap;
	natural (*indices_valores)[MAX_NUMEROS] = heap_ctx->indices_valores;
	natural *num_indices_valores = heap_ctx->num_indices_valores;
	natural *mapeo_inv=heap_ctx->mapeo_idx_heap_a_pos_ocurrencia;
	bitch_vector valores_ya_validados[(MAX_NUMEROS / 64) + 1] = { 0 };
	for (int i = 1; i < heap_size + 1; i++) {
		tipo_dato num_act = heap[i];
		natural *indices_valores_act = indices_valores[num_act];
		natural num_indices_valores_act = num_indices_valores[num_act];
		if (num_indices_valores_act
				&& !caca_comun_checa_bit(valores_ya_validados, num_act)) {
			for (int j = 0; j < num_indices_valores_act; j++) {
				tipo_dato num_act_ocu = 0;
				natural indice_valor_act = 0;
				natural indice_pos_ocurrencia_en_mapa = 0;

				indice_valor_act = indices_valores_act[j];
				num_act_ocu = heap[indice_valor_act];
				assert_timeout(num_act_ocu == num_act);

				indice_pos_ocurrencia_en_mapa =mapeo_inv[indice_valor_act];
				assert_timeout(indice_pos_ocurrencia_en_mapa!=FRAUDUCACA_VALOR_INVALIDO);

				assert_timeout(j == indice_pos_ocurrencia_en_mapa);

				num_elems++;
			}
			caca_comun_asigna_bit(valores_ya_validados, num_act);
		}
	}
	assert_timeout(heap_size == num_elems);
	for (int i=0;i<MAX_NUMEROS;i++){
			natural idx_en_heap = 0;
			natural idx_en_pos_ocurrencias = 0;
			natural num_indices_valores_act = 0;
			tipo_dato num_act = 0;

			idx_en_heap = i;
			idx_en_pos_ocurrencias = mapeo_inv[i];
			if(idx_en_pos_ocurrencias!=FRAUDUCACA_VALOR_INVALIDO)
			{
 				num_act = heap[idx_en_heap];

				num_indices_valores_act = num_indices_valores[num_act];
				assert_timeout(idx_en_pos_ocurrencias < num_indices_valores_act);

				num_elems_mapeo++;
			}
	}

	assert_timeout(heap_size == num_elems_mapeo);
}

void heap_shit_valida_invariante(heap_shit *heap_ctx, natural idx_heap) {
	natural heap_size = heap_ctx->heap_size;
	tipo_dato *heap = heap_ctx->heap;
	if (idx_heap < heap_size) {
		tipo_dato num_act = heap[idx_heap];
		natural idx_heap_hijo_izq = (idx_heap << 1);
		if (idx_heap_hijo_izq < heap_size) {
			tipo_dato num_act_hijo_izq = heap[idx_heap_hijo_izq];
			if (heap_ctx->min) {
				assert_timeout(num_act <= num_act_hijo_izq);
			} else {
				assert_timeout(num_act >= num_act_hijo_izq);
			}
		}
		if (idx_heap_hijo_izq + 1 < heap_size) {
			tipo_dato num_act_hijo_der = heap[idx_heap_hijo_izq + 1];
			if (heap_ctx->min) {
				assert_timeout(num_act <= num_act_hijo_der);
			} else {
				assert_timeout(num_act >= num_act_hijo_der);
			}
		}
		heap_shit_valida_invariante(heap_ctx, idx_heap_hijo_izq);
		heap_shit_valida_invariante(heap_ctx, idx_heap_hijo_izq + 1);
	}
}

void heap_shit_valida_mierda(heap_shit *heap_ctx) {
	heap_shit_valida_referencias_inversas(heap_ctx);
	heap_shit_valida_invariante(heap_ctx, 1);
}

#endif
int main() {
	bool es_min = verdadero;
	heap_shit *heap_ctx = calloc(1, sizeof(heap_shit));
	tipo_dato cacasos_prueba[][10] = { 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
	{ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, 
	{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 0 }, 
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, { 10, 9, 8, 7, 6, 5, 4, 2, 1 }, { 1,
			1, 1, 1, 1, 2, 2, 2, 2, 2 }, { 2, 2, 2, 2, 2, 1, 1, 1, 1, 1 }, { 1,
			1, 1, 2, 2, 2, 2, 3, 3, 3 } };
	int number_of_elements;
	natural num_cacasos = 0;
//	scanf("%d", &number_of_elements);
	int iter, element;
	number_of_elements = 10;
	printf("nume elems %u\n", number_of_elements);
	num_cacasos = sizeof(cacasos_prueba) / 10;
	for (int i = 0; i < num_cacasos; i++) {
		tipo_dato *cacaso_act = cacasos_prueba[i];
		printf("mpezo caso %u\n", i);
		for (bool j = falso; j <= verdadero; j++) {
			caca_log_debug("cacaso %s",
					caca_arreglo_a_cadena(cacaso_act,10,FRAUDUCACA_BUF_STATICO));
			heap_shit_init(heap_ctx, j);
			for (iter = 0; iter < number_of_elements; iter++) {
//		scanf("%d", &element);
				element = cacaso_act[iter];
				heap_shit_insert(heap_ctx, element);
				caca_log_debug("dumpeando cabron ins caso %u min %u iter %u", i,
						j, iter);
#ifdef FRAUDUCACA_DUMPEAR
				heap_shit_dumpear(heap_ctx);
#endif
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
				heap_shit_valida_mierda(heap_ctx);
#endif
			}
			for (iter = 0; iter < number_of_elements; iter++) {
				printf("%d ", heap_shit_delete(heap_ctx,1));
				caca_log_debug("dumpeando cabron del caso %u min %u iter %u", i,
						j, iter);
#ifdef FRAUDUCACA_DUMPEAR
				heap_shit_dumpear(heap_ctx);
#endif
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
				heap_shit_valida_mierda(heap_ctx);
#endif
			}
			printf("\n");
			for (iter = 0; iter < number_of_elements; iter++) {
//		scanf("%d", &element);
				element = cacaso_act[iter];
				heap_shit_insert(heap_ctx, element);
				caca_log_debug("dumpeando cabron mezcla caso %u min %u iter %u",
						i, j, iter);
#ifdef FRAUDUCACA_DUMPEAR
				heap_shit_dumpear(heap_ctx);
#endif
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
				heap_shit_valida_mierda(heap_ctx);
#endif
				if (iter % 2) {
					heap_shit_delete(heap_ctx,1);
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
					heap_shit_valida_mierda(heap_ctx);
#endif
				}
			}

			for (iter = 0; iter < MAX_NUMEROS - heap_ctx->heap_size; iter++) {
//		scanf("%d", &element);
				element = iter % 201;
				heap_shit_insert(heap_ctx, element);
				caca_log_debug(
						"dumpeando cabron ins grande caso %u min %u iter %u", i,
						j, iter);
#ifdef FRAUDUCACA_DUMPEAR
				heap_shit_dumpear(heap_ctx);
#endif
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
				heap_shit_valida_mierda(heap_ctx);
#endif
				if(heap_ctx->heap_size && !(iter%101))
				{
					heap_shit_borrar_directo(heap_ctx,heap_ctx->heap[2]);
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
					heap_shit_valida_mierda(heap_ctx);
#endif
				}
				if(heap_ctx->heap_size && !(iter%1003))
				{
					heap_shit_borrar_directo(heap_ctx,heap_ctx->heap[heap_ctx->heap_size-2]);
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
					heap_shit_valida_mierda(heap_ctx);
#endif
				}

				if(heap_ctx->heap_size && !(iter%1017))
				{
					heap_shit_borrar_directo(heap_ctx,heap_ctx->heap[heap_ctx->heap_size>>1]);
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
					heap_shit_valida_mierda(heap_ctx);
#endif
				}
				if (iter % 4) {
					heap_shit_delete(heap_ctx,1);
#ifdef FRAUDUCACA_VALIDAR_ARBOLINES
					heap_shit_valida_mierda(heap_ctx);
#endif
				}
				if(!(iter%10000))
				{
					printf("en iter %u\n",iter);
				}
			}
			heap_shit_fini(heap_ctx);
			memset(heap_ctx, 0, sizeof(*heap_ctx));
		}
		printf("termino caso %u\n", i);
	}
	free(heap_ctx);
	return 0;
}
