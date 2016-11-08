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
typedef unsigned int khint32_t;

typedef unsigned long long khint64_t;
typedef khint32_t khint_t;
typedef khint_t khiter_t;
static const double __ac_HASH_UPPER = 0.77;
static inline khint_t __ac_X31_hash_string(const char *s) {
	khint_t h = (khint_t) *s;
	if (h)
		for (++s; *s; ++s)
			h = (h << 5) - h + (khint_t) *s;
	return h;
}
static inline khint_t __ac_Wang_hash(khint_t key) {
	key += ~(key << 15);
	key ^= (key >> 10);
	key += (key << 3);
	key ^= (key >> 6);
	key += ~(key << 11);
	key ^= (key >> 16);
	return key;
}
typedef const char *kh_cstr_t;
typedef struct kh_caca_s {
	khint_t n_buckets, size, n_occupied, upper_bound;
	khint32_t *flags;
	khint32_t *keys;
	int *vals;
} kh_caca_t;

#define kh_key(h, x) ((h)->keys[x])
#define kh_val(h, x) ((h)->vals[x])
#define kh_value(h, x) ((h)->vals[x])
#define kh_begin(h) (khint_t)(0)
#define kh_end(h) ((h)->n_buckets)
#define kh_size(h) ((h)->size)
#define kh_exist(h, x) (!__ac_iseither((h)->flags, (x)))

#define __ac_isempty(flag, i) ((flag[i>>4]>>((i&0xfU)<<1))&2)
#define __ac_isdel(flag, i) ((flag[i>>4]>>((i&0xfU)<<1))&1)
#define __ac_iseither(flag, i) ((flag[i>>4]>>((i&0xfU)<<1))&3)
#define __ac_set_isdel_false(flag, i) (flag[i>>4]&=~(1ul<<((i&0xfU)<<1)))
#define __ac_set_isempty_false(flag, i) (flag[i>>4]&=~(2ul<<((i&0xfU)<<1)))
#define __ac_set_isboth_false(flag, i) (flag[i>>4]&=~(3ul<<((i&0xfU)<<1)))
#define __ac_set_isdel_true(flag, i) (flag[i>>4]|=1ul<<((i&0xfU)<<1))
#define __ac_fsize(m) ((m) < 16? 1 : (m)>>4)

static inline __attribute__ ((__unused__)) kh_caca_t *kh_init_caca(void) {
	return (kh_caca_t*) calloc(1, sizeof(kh_caca_t));
}
static inline __attribute__ ((__unused__)) void kh_destroy_caca(kh_caca_t *h) {
	if (h) {
		free((void *) h->keys);
		free(h->flags);
		free((void *) h->vals);
		free(h);
	}
}
static inline __attribute__ ((__unused__)) void kh_clear_caca(kh_caca_t *h) {
	if (h && h->flags) {
		__builtin___memset_chk(h->flags, 0xaa,
				((h->n_buckets) < 16 ? 1 : (h->n_buckets) >> 4)
						* sizeof(khint32_t),
				__builtin_object_size(h->flags, 0));
		h->size = h->n_occupied = 0;
	}
}
static inline __attribute__ ((__unused__)) khint_t kh_get_caca(
		const kh_caca_t *h, khint32_t key) {
	if (h->n_buckets) {
		khint_t k, i, last, mask, step = 0;
		mask = h->n_buckets - 1;
		k = (khint32_t) (key);
		i = k & mask;
		last = i;
		while (!((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 2)
				&& (((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 1)
						|| !((h->keys[i]) == (key)))) {
			i = (i + (++step)) & mask;
			if (i == last)
				return h->n_buckets;
		}
		return ((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 3) ? h->n_buckets : i;
	} else
		return 0;
}
static inline __attribute__ ((__unused__)) int kh_resize_caca(kh_caca_t *h,
		khint_t new_n_buckets) {
	khint32_t *new_flags = 0;
	khint_t j = 1;
	{
		(--(new_n_buckets), (new_n_buckets) |= (new_n_buckets) >> 1, (new_n_buckets) |=
				(new_n_buckets) >> 2, (new_n_buckets) |= (new_n_buckets) >> 4, (new_n_buckets) |=
				(new_n_buckets) >> 8, (new_n_buckets) |= (new_n_buckets) >> 16, ++(new_n_buckets));
		if (new_n_buckets < 4)
			new_n_buckets = 4;
		if (h->size >= (khint_t) (new_n_buckets * __ac_HASH_UPPER + 0.5))
			j = 0;
		else {
			new_flags = (khint32_t*) malloc(
					((new_n_buckets) < 16 ? 1 : (new_n_buckets) >> 4)
							* sizeof(khint32_t));
			if (!new_flags)
				return -1;
			__builtin___memset_chk(new_flags, 0xaa,
					((new_n_buckets) < 16 ? 1 : (new_n_buckets) >> 4)
							* sizeof(khint32_t),
					__builtin_object_size(new_flags, 0));
			if (h->n_buckets < new_n_buckets) {
				khint32_t *new_keys = (khint32_t*) realloc((void *) h->keys,
						new_n_buckets * sizeof(khint32_t));
				if (!new_keys) {
					free(new_flags);
					return -1;
				}
				h->keys = new_keys;
				if (1) {
					int *new_vals = (int*) realloc((void *) h->vals,
							new_n_buckets * sizeof(int));
					if (!new_vals) {
						free(new_flags);
						return -1;
					}
					h->vals = new_vals;
				}
			}
		}
	}
	if (j) {
		for (j = 0; j != h->n_buckets; ++j) {
			if (((h->flags[j >> 4] >> ((j & 0xfU) << 1)) & 3) == 0) {
				khint32_t key = h->keys[j];
				int val;
				khint_t new_mask;
				new_mask = new_n_buckets - 1;
				if (1)
					val = h->vals[j];
				(h->flags[j >> 4] |= 1ul << ((j & 0xfU) << 1));
				while (1) {
					khint_t k, i, step = 0;
					k = (khint32_t) (key);
					i = k & new_mask;
					while (!((new_flags[i >> 4] >> ((i & 0xfU) << 1)) & 2))
						i = (i + (++step)) & new_mask;
					(new_flags[i >> 4] &= ~(2ul << ((i & 0xfU) << 1)));
					if (i < h->n_buckets
							&& ((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 3)
									== 0) {
						{
							khint32_t tmp = h->keys[i];
							h->keys[i] = key;
							key = tmp;
						}
						if (1) {
							int tmp = h->vals[i];
							h->vals[i] = val;
							val = tmp;
						}
						(h->flags[i >> 4] |= 1ul << ((i & 0xfU) << 1));
					} else {
						h->keys[i] = key;
						if (1)
							h->vals[i] = val;
						break;
					}
				}
			}
		}
		if (h->n_buckets > new_n_buckets) {
			h->keys = (khint32_t*) realloc((void *) h->keys,
					new_n_buckets * sizeof(khint32_t));
			if (1)
				h->vals = (int*) realloc((void *) h->vals,
						new_n_buckets * sizeof(int));
		}
		free(h->flags);
		h->flags = new_flags;
		h->n_buckets = new_n_buckets;
		h->n_occupied = h->size;
		h->upper_bound = (khint_t) (h->n_buckets * __ac_HASH_UPPER + 0.5);
	}
	return 0;
}
static inline __attribute__ ((__unused__)) khint_t kh_put_caca(kh_caca_t *h,
		khint32_t key, int *ret) {
	khint_t x;
	if (h->n_occupied >= h->upper_bound) {
		if (h->n_buckets > (h->size << 1)) {
			if (kh_resize_caca(h, h->n_buckets - 1) < 0) {
				*ret = -1;
				return h->n_buckets;
			}
		} else if (kh_resize_caca(h, h->n_buckets + 1) < 0) {
			*ret = -1;
			return h->n_buckets;
		}
	}
	{
		khint_t k, i, site, last, mask = h->n_buckets - 1, step = 0;
		x = site = h->n_buckets;
		k = (khint32_t) (key);
		i = k & mask;
		if (((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 2))
			x = i;
		else {
			last = i;
			while (!((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 2)
					&& (((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 1)
							|| !((h->keys[i]) == (key)))) {
				if (((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 1))
					site = i;
				i = (i + (++step)) & mask;
				if (i == last) {
					x = site;
					break;
				}
			}
			if (x == h->n_buckets) {
				if (((h->flags[i >> 4] >> ((i & 0xfU) << 1)) & 2)
						&& site != h->n_buckets)
					x = site;
				else
					x = i;
			}
		}
	}
	if (((h->flags[x >> 4] >> ((x & 0xfU) << 1)) & 2)) {
		h->keys[x] = key;
		(h->flags[x >> 4] &= ~(3ul << ((x & 0xfU) << 1)));
		++h->size;
		++h->n_occupied;
		*ret = 1;
	} else if (((h->flags[x >> 4] >> ((x & 0xfU) << 1)) & 1)) {
		h->keys[x] = key;
		(h->flags[x >> 4] &= ~(3ul << ((x & 0xfU) << 1)));
		++h->size;
		*ret = 2;
	} else
		*ret = 0;
	return x;
}
static inline __attribute__ ((__unused__)) void kh_del_caca(kh_caca_t *h,
		khint_t x) {
	if (x != h->n_buckets && !((h->flags[x >> 4] >> ((x & 0xfU) << 1)) & 3)) {
		(h->flags[x >> 4] |= 1ul << ((x & 0xfU) << 1));
		--h->size;
	}
}
#endif

#if 1

typedef struct heap_shit {
	bool min;
	natural heap_size;
	tipo_dato heap[FRAUDUCACA_MAX_NUMEROS_POR_HEAP];
	natural indices_valores[MAX_VALOR][MAX_VALOR];
	natural num_indices_valores[MAX_VALOR];
	kh_caca_t *tablin_idx_pos_en_heap;
} heap_shit;

/*Initialize Heap*/
void heap_shit_init(heap_shit *heap, bool es_min) {
	heap->heap_size = 0;
	heap->min=es_min;
	heap->heap[0] = FRAUDUCACA_VALOR_INVALIDO;
	heap->tablin_idx_pos_en_heap=kh_init_caca()
}

/*Insert an element into the heap */
void heap_shit_insert(heap_shit *heap_ctx, tipo_dato element) {
	natural heap_size = ++heap_ctx->heap_size;
	int ret = 0;
	khiter_t iter=0;
	tipo_dato *heap=NULL;

	heap = heap_ctx->heap;

	heap[heap_size] = element; /*Insert in the last place*/
	/*Adjust its position*/
	natural now = heap_size;
	while (((heap_ctx->min && (int)heap[now / 2] > (int)element) || (!heap_ctx->min && (natural)heap[now / 2] < (natural)element))) {
//printf("caca now %u de heap %u elem %u\n",now,heap[now],element);
		natural idx_pos=0;
		iter=kh_get_caca(heap_ctx->tablin_idx_pos_en_heap, heap+now/2);
		idx_pos=kh_val(heap_ctx->tablin_idx_pos_en_heap,iter);

		heap[now] = heap[now / 2];
		heap_ctx->indices_valores[heap[now]][idx_pos]=now;
		now /= 2;
	}
//printf("raise now %u con heap %u y elem %u res %u\n",now,heap[now / 2],element, (unsigned int)heap[now / 2]>(unsigned int)element);	

	iter= kh_put_caca(heap_ctx->tablin_idx_pos_en_heap, heap+now, &ret);
	kh_value(heap_ctx->tablin_idx_pos_en_heap, iter)= heap_ctx->num_indices_valores[element];
	heap[now] = element;
	heap_ctx->indices_valores[element][heap_ctx->num_indices_valores[element]++]=now;
	
//tablin_idx_pos_en_heap
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
		if (child != heap_size && ((heap_ctx->min && heap[child + 1] < heap[child]) || (!heap_ctx->min && heap[child + 1] > heap[child]))) {
			child++;
		}
		/* To check if the last element fits ot not it suffices to check if the last element
		 is less than the minimum element among both the children*/
//printf("last %u heap %u\n",lastElement,heap[child]);
		if ((heap_ctx->min && lastElement > heap[child]) || (!heap_ctx->min && lastElement < heap[child])) {
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
	bool es_min=verdadero;
	heap_shit *heap_ctx = &(heap_shit ) { 0 };
	tipo_dato *caca_prueba=NULL;
	int number_of_elements;
//	scanf("%d", &number_of_elements);
	int iter, element;
	heap_shit_init(heap_ctx,es_min);
	if(!es_min)
	{
		caca_prueba = (tipo_dato []){ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	}
	else
	{
		caca_prueba = (tipo_dato[]){ 10,9,8,7,6,5,4,3,2,0};
	}
	number_of_elements = 10;
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
