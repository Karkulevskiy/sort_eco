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
#include "CEcoLab1EnumConnectionPoints.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoLab1Events.h"
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
    else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer))
    {
        *ppv = &pCMe->m_pVTblICPC;
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

/*
 *
 * <сводка>
 *   Функция MyFunction
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */

/*
 *
 * <сводка>
 *   Функция Fire_HipHipHooray
 * </сводка>
 *
 * <описание>
 *   Функция вызова обратного интерфейса
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_Fire_HipHipHooray(/* in */ struct IEcoLab1 *me, /* in */ char_t *Name)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    int16_t result = 0;
    uint32_t count = 0;
    uint32_t index = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0)
    {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0)
    {
        result = ((IEcoConnectionPoint *)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint *)pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0))
        {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0)
            {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **)&pIEvents);
                if ((result == 0) && (pIEvents != 0))
                {
                    result = pIEvents->pVTbl->HipHipHooray(pIEvents, Name);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Fire_GetMinMaxInArray(/* in */ struct IEcoLab1 *me, int32_t *array, int32_t length, int32_t *min, int32_t *max)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    int16_t result = 0;
    uint32_t count = 0;
    uint32_t index = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0)
    {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0)
    {
        result = ((IEcoConnectionPoint *)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint *)pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0))
        {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0)
            {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **)&pIEvents);
                if ((result == 0) && (pIEvents != 0))
                {
                    result = pIEvents->pVTbl->GetMinMaxInArray(pIEvents, array, length, min, max);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Fire_InitZeros(/* in */ struct IEcoLab1 *me, uint32_t *array, uint32_t length)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    int16_t result = 0;
    uint32_t count = 0;
    uint32_t index = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0)
    {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0)
    {
        result = ((IEcoConnectionPoint *)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint *)pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0))
        {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0)
            {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **)&pIEvents);
                if ((result == 0) && (pIEvents != 0))
                {
                    result = pIEvents->pVTbl->InitZeros(pIEvents, array, length);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

int16_t ECOCALLMETHOD CEcoLab1_Fire_LocalCountSort(/* in */ struct IEcoLab1 *me, uint32_t *countedArray, int32_t *outputArray, uint32_t range, int32_t min)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    int16_t result = 0;
    uint32_t count = 0;
    uint32_t index = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0)
    {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0)
    {
        result = ((IEcoConnectionPoint *)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint *)pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0))
        {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0)
            {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **)&pIEvents);
                if ((result == 0) && (pIEvents != 0))
                {
                    result = pIEvents->pVTbl->LocalCountSort(pIEvents, countedArray, outputArray, range, min);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoConnectionPointContainer
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_QueryInterface(/* in */ struct IEcoConnectionPointContainer *me, /* in */ const UGUID *riid, /* out */ void **ppv)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoUnknown *));

    if (me == 0 || ppv == 0)
    {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1))
    {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1 *)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer))
    {
        *ppv = &pCMe->m_pVTblICPC;
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
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoConnectionPointContainer
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_AddRef(/* in */ struct IEcoConnectionPointContainer *me)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoUnknown *));

    if (me == 0)
    {
        return -1;
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
 *   Функция Release для интерфейса IEcoConnectionPointContainer
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_Release(/* in */ struct IEcoConnectionPointContainer *me)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoUnknown *));

    if (me == 0)
    {
        return -1;
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

/*
 *
 * <сводка>
 *   Функция EnumConnectionPoints
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_EnumConnectionPoints(/* in */ struct IEcoConnectionPointContainer *me, /* out */ struct IEcoEnumConnectionPoints **ppEnum)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoUnknown *));
    int16_t result = 0;

    if (me == 0 || ppEnum == 0)
    {
        return -1;
    }

    result = createCEcoLab1EnumConnectionPoints((IEcoUnknown *)pCMe->m_pISys, &pCMe->m_pISinkCP->m_pVTblICP, ppEnum);

    return result;
}

/*
 *
 * <сводка>
 *   Функция FindConnectionPoint
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoConnectionPointContainer_FindConnectionPoint(/* in */ struct IEcoConnectionPointContainer *me, /* in */ const UGUID *riid, /* out */ struct IEcoConnectionPoint **ppCP)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)((uint64_t)me - sizeof(struct IEcoUnknown *));
    int16_t result = 0;

    if (me == 0 || ppCP == 0)
    {
        return -1;
    }

    if (!IsEqualUGUID(riid, &IID_IEcoLab1Events))
    {
        *ppCP = 0;
        /* CONNECT_E_NOCONNECTION */
        return -1;
    }

    if (pCMe->m_pISinkCP == 0)
    {
        /* E_FAIL */
        return -1;
    }

    pCMe->m_pISinkCP->m_pVTblICP->AddRef(&pCMe->m_pISinkCP->m_pVTblICP);
    *ppCP = &pCMe->m_pISinkCP->m_pVTblICP;

    return 0;
}

static int16_t ECOCALLMETHOD CEcoLab1_PseudoGenerator(
    /* in */ IEcoLab1Ptr_t me,
    /* in */ uint32_t length,
    /* in */ uint32_t seed,
    /* out */ int32_t **generatedArray)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    int32_t *outputArray;
    int32_t i;
    if (me == 0 || length == 0)
    {
        return ERR_ECO_POINTER;
    }
    outputArray = (uint32_t *)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, length * sizeof(uint32_t));
    if (outputArray == 0)
    {
        return ERR_ECO_OUTOFMEMORY;
    }
    for (i = 0; i < length; i++)
    {
        outputArray[i] = ((i + 1) * seed * 42 + 228) % 1007;
    }

    *generatedArray = outputArray;

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoLab1_CountSort(
    /* in */ IEcoLab1 *me,
    /* in */ int32_t *inputArray,
    /* in */ uint32_t length,
    /* out */ int32_t **sortedArray)
{
    CEcoLab1 *pCMe = (CEcoLab1 *)me;
    int32_t min;
    int32_t max;
    uint32_t range;
    uint32_t *countedArray;
    int32_t *outputArray;
    int32_t i;
    int32_t j;
    uint32_t outputIndex;

    if (me == 0 || inputArray == 0 || sortedArray == 0 || length == 0)
    {
        return ERR_ECO_POINTER;
    }

    CEcoLab1_Fire_GetMinMaxInArray(me, inputArray, length, &min, &max);

    range = max - min + 1;

    // Создать массив подсчётов
    countedArray = (uint32_t *)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, range * sizeof(uint32_t));
    if (countedArray == 0)
    {
        return ERR_ECO_OUTOFMEMORY;
    }

    CEcoLab1_Fire_InitZeros(me, countedArray, range);

    // Считаем кол-во элементов
    for (i = 0; i < length; i++)
    {
        countedArray[inputArray[i] - min]++;
    }
    // Создать результирующий массив
    outputArray = (int32_t *)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, length * sizeof(int32_t));
    if (outputArray == 0)
    {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, countedArray);
        return ERR_ECO_OUTOFMEMORY; // TODO подумать над ошибкой
    }

    // Заполняем результирующий массив
    CEcoLab1_Fire_LocalCountSort(me, countedArray, outputArray, range, min);

    // Чистим память от массива подсчётов
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, countedArray);

    *sortedArray = outputArray;

    /* Обратный вызов */
    CEcoLab1_Fire_HipHipHooray(me, pCMe->m_Name);

    return ERR_ECO_SUCCESES;
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

    /* Создание точки подключения */
    result = createCEcoLab1ConnectionPoint((IEcoUnknown *)pCMe->m_pISys, &pCMe->m_pVTblICPC, &IID_IEcoLab1Events, (IEcoConnectionPoint **)&((pCMe)->m_pISinkCP));
    if (result == 0 && pCMe->m_pISinkCP != 0)
    {
        result = 0;
    }

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_CountSort,
    CEcoLab1_PseudoGenerator};

/* Create Virtual Table IEcoConnectionPointContainer */
IEcoConnectionPointContainerVTbl g_x0000000500000000C000000000000046VTblCPC = {
    CEcoLab1_IEcoConnectionPointContainer_QueryInterface,
    CEcoLab1_IEcoConnectionPointContainer_AddRef,
    CEcoLab1_IEcoConnectionPointContainer_Release,
    CEcoLab1_IEcoConnectionPointContainer_EnumConnectionPoints,
    CEcoLab1_IEcoConnectionPointContainer_FindConnectionPoint};

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

    pCMe->m_Name = 0;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Создание таблицы функций интерфейса IEcoConnectionPointContainer */
    pCMe->m_pVTblICPC = &g_x0000000500000000C000000000000046VTblCPC;

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
        if (pCMe->m_Name != 0)
        {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pISys != 0)
        {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
