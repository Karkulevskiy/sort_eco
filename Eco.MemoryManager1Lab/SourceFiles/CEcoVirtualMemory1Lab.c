/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoVirtualMemory1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов IEcoVirtualMemory1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "CEcoMemoryManager1Lab.h"

extern CEcoMemoryManager1Lab_623E1838 g_xCEcoMemoryManager1Lab_623E1838;

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoVirtualMemory1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_QueryInterface(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ const UGUID *riid, /* out */ voidptr_t *ppv)
{
    CEcoMemoryManager1Lab_623E1838 *pCMe = (CEcoMemoryManager1Lab_623E1838 *)((uint64_t)me - sizeof(voidptr_t) * 2);

    if (me == 0 || ppv == 0)
    {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoMemoryManager1))
    {
        *ppv = &pCMe->m_pVTblIMgr;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1 *)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoMemoryAllocator1))
    {
        *ppv = &pCMe->m_pVTblIMem;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1 *)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoVirtualMemory1))
    {
        *ppv = &pCMe->m_pVTblIVirtual;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1 *)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown))
    {
        *ppv = &pCMe->m_pVTblIMgr;
        pCMe->m_pVTblIMgr->AddRef((IEcoMemoryManager1 *)pCMe);
    }
    else
    {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoVirtualMemory1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_AddRef(/* in */ IEcoVirtualMemory1Ptr_t me)
{
    CEcoMemoryManager1Lab_623E1838 *pCMe = (CEcoMemoryManager1Lab_623E1838 *)((uint64_t)me - sizeof(voidptr_t) * 2);

    if (me == 0)
    {
        return -1;
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoVirtualMemory1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Release(/* in */ IEcoVirtualMemory1Ptr_t me)
{
    CEcoMemoryManager1Lab_623E1838 *pCMe = (CEcoMemoryManager1Lab_623E1838 *)((uint64_t)me - sizeof(voidptr_t) * 2);

    if (me == 0)
    {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0)
    {
        deleteCEcoMemoryManager1Lab_623E1838((IEcoMemoryManager1 *)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Init(/* in */ IEcoVirtualMemory1Ptr_t me)
{
    // CEcoMemoryManager1Lab_623E1838 *pCMe = (CEcoMemoryManager1Lab_623E1838 *)((uint64_t)me - sizeof(voidptr_t) * 2);
    if (first_block != NULL)
        return; // Уже инициализирован

    // Весь пул начинается с одного свободного блока
    first_block = (Block *)memory_pool;
    first_block->size = POOL_SIZE - sizeof(Block);
    first_block->free = 1;
    return 0;
}

// Вспомогательная функция: возвращает указатель на данные блока
static void *block_data(Block *b)
{
    return (void *)((uint8_t *)b + sizeof(Block));
}

// Вспомогательная функция: возвращает блок по указателю на данные
static Block *data_to_block(void *ptr)
{
    return (Block *)((uint8_t *)ptr - sizeof(Block));
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция возвращает адрес страницы
 * </описание>
 *
 */
voidptr_t ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Alloc(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ uint64_t addrVirtual, /* in */ uint32_t size)
{
    // CEcoMemoryManager1Lab_623E1838 *pCMe = (CEcoMemoryManager1Lab_623E1838 *)((uint64_t)me - sizeof(voidptr_t) * 2);
    if (size == 0)
        return NULL;

    Block *best_block = NULL;
    Block *current = first_block;
    size_t max_free_size = 0;

    // Проходим по всем блокам
    while ((uint8_t *)current < memory_pool + POOL_SIZE)
    {
        if (current->free && current->size >= size)
        {
            if (current->size > max_free_size)
            {
                max_free_size = current->size;
                best_block = current;
            }
        }

        // Переход к следующему блоку
        uint8_t *next = (uint8_t *)current + sizeof(Block) + current->size;
        if (next >= memory_pool + POOL_SIZE)
            break;
        current = (Block *)next;
    }

    if (best_block == NULL)
    {
        return NULL; // Нет подходящего блока
    }

    // Разделяем блок, если остаток достаточно велик для нового блока
    size_t remaining = best_block->size - size;
    if (remaining >= sizeof(Block) + 1)
    { // +1 чтобы был хотя бы 1 байт данных
        Block *new_block = (Block *)((uint8_t *)best_block + sizeof(Block) + size);
        new_block->size = remaining - sizeof(Block);
        new_block->free = 1;

        best_block->size = size;
    }

    best_block->free = 0;
    return block_data(best_block);
}

/*
 *
 * <сводка>
 *   Функция Free
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoVirtualMemory1Lab_623E1838_Free(/* in */ IEcoVirtualMemory1Ptr_t me, /* in */ voidptr_t ptr)
{
    if (ptr == NULL)
        return;
    Block *b = data_to_block(ptr);
    b->free = 1;
    // CEcoMemoryManager1Lab_623E1838 *pCMe = (CEcoMemoryManager1Lab_623E1838 *)((uint64_t)me - sizeof(voidptr_t) * 2);
}
