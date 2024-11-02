#ifndef INCLUDED_GNUSTARTUPASMGENERATOR_H
#define INCLUDED_GNUSTARTUPASMGENERATOR_H

/* -------------------------------------------------------------------------------------------------------------- */
/*  */


typedef struct NVIC_VectorItem_S{
    struct NVIC_VectorItem_S * prev;
    struct NVIC_VectorItem_S * next;
    char IRQHandler[256];
    char Comment[256];
}NVIC_VectorItem_T;

#define NEXT(N) (N)->next
#define PREV(N) (N)->prev
#define PREV_NEXT(N) NEXT(PREV(N))
#define NEXT_PREV(N) PREV(NEXT(N))

/* Lp -- N -- L -- Ln */
#define INSERT_BEFORE(L, N) \
do{                         \
    PREV_NEXT(L) = (N);     \
    PREV(N) = PREV(L);      \
    NEXT(N) = (L);          \
    PREV(L) = (N);          \
}while(0)

/* Np -- N -- Nn */
#define REMOVE_ITEM(N) \
do{                    \
    PREV_NEXT(N) = NEXT(N); \
    NEXT_PREV(N) = PREV(N); \
    PREV(N) = NEXT(N) = (N);\
}while(0)

/* -------------------------------------------------------------------------------------------------------------- */
/*  */

int NVIC_Vector_AddItem(NVIC_VectorItem_T* table, const char* IRQHandler, const char* Comment);

void NVIC_Vector_Release(NVIC_VectorItem_T* table);

int GNUStartupASMGenerator_Generate(NVIC_VectorItem_T* vectors
        , const char* cpu_type, const char* fpu, const char* file);


#endif /* INCLUDED_GNUSTARTUPASMGENERATOR_H */
