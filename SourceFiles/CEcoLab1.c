/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID *riid, /* out */ void **ppv)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0)
    {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1))
    {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1 *)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown))
    {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1 *)pCMe);
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
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;

    /* Проверка указателя */
    if (me == 0)
    {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;

    /* Проверка указателя */
    if (me == 0)
    {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0)
    {
        deleteCEcoLab1((IEcoLab1 *)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
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
void *ECOCALLMETHOD CEcoLab1_Alloc(/* in */ IEcoLab1Ptr_t me, /* in */ uint64_t addrVirtual, /* in */ uint32_t size)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    Block *best_block = NULL;
    Block *current = pCMe->first_block;
    uint8_t *next = 0;
    size_t max_free_size = 0;
    size_t remaining = 0;

    if (size == 0)
        return NULL;

    // Проходим по всем блокам
    while ((uint8_t *)current < pCMe->memory_pool + POOL_SIZE)
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
        next = (uint8_t *)current + sizeof(Block) + current->size;
        if (next >= pCMe->memory_pool + POOL_SIZE)
            break;
        current = (Block *)next;
    }

    if (best_block == NULL)
    {
        return NULL; // Нет подходящего блока
    }

    // Разделяем блок, если остаток достаточно велик для нового блока
    remaining = best_block->size - size;
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
void ECOCALLMETHOD CEcoLab1_Free(/* in */ IEcoLab1Ptr_t me, /* in */ void *ptr)
{
    Block *b = 0;
    if (ptr == NULL)
        return;
    b = data_to_block(ptr);
    b->free = 1;
}
/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    IEcoInterfaceBus1 *pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0)
    {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1 *)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0)
    {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1 *)pIUnkSystem;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_Alloc,
    CEcoLab1_Free};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown *pIUnkSystem, /* in */ IEcoUnknown *pIUnkOuter, /* out */ IEcoLab1 **ppIEcoLab1)
{
    int16_t result = -1;
    IEcoSystem1 *pISys = 0;
    IEcoInterfaceBus1 *pIBus = 0;
    IEcoInterfaceBus1MemExt *pIMemExt = 0;
    IEcoMemoryAllocator1 *pIMem = 0;
    CEcoLab1 *pCMe = 0;
    UGUID *rcid = (UGUID *)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0)
    {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0)
    {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void **)&pIMemExt);
    if (result == 0 && pIMemExt != 0)
    {
        rcid = (UGUID *)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void **)&pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0)
    {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1 *)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    pCMe->first_block = (Block *)pCMe->memory_pool;
    pCMe->first_block->size = POOL_SIZE - sizeof(Block);
    pCMe->first_block->free = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1 *)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1 *pIEcoLab1)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)pIEcoLab1;
    IEcoMemoryAllocator1 *pIMem = 0;

    if (pIEcoLab1 != 0)
    {
        pIMem = pCMe->m_pIMem;
        if (pCMe->m_pISys != 0)
        {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
