/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab2Sink.h"
#include "IEcoConnectionPointContainer.h"
#include "stdio.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2Sink_QueryInterface(/* in */ struct IEcoLab2Events *me, /* in */ const UGUID *riid, /* out */ void **ppv)
{
    if (IsEqualUGUID(riid, &IID_IEcoLab2Events))
    {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown))
    {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab2Sink_AddRef(/* in */ struct IEcoLab2Events *me)
{
    CEcoLab2Sink *pCMe = (CEcoLab2Sink *)me;

    if (me == 0)
    {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab2Sink_Release(/* in */ struct IEcoLab2Events *me)
{
    CEcoLab2Sink *pCMe = (CEcoLab2Sink *)me;

    if (me == 0)
    {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0)
    {
        deleteCEcoLab2Sink((IEcoLab2Events *)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция HipHipHooray
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2Sink_Advise(/* in */ struct CEcoLab2Sink *me, /* in */ IEcoLab1 *pIEcoLab1)
{
    IEcoConnectionPointContainer *pCPC = 0;
    IEcoConnectionPoint *pCP = 0;
    int16_t result = 0;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void **)&pCPC);

    if (result == 0 && pCPC != 0)
    {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab2Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0)
        {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown *)me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2Sink_Unadvise(/* in */ struct CEcoLab2Sink *me, /* in */ IEcoLab1 *pIEcoLab1)
{
    IEcoConnectionPointContainer *pCPC = 0;
    IEcoConnectionPoint *pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie)
    {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void **)&pCPC);
        if (result == 0)
        {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab2Events, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0)
            {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

int16_t ECOCALLMETHOD CEcoLab2Sink_Greeting(/* in */ struct IEcoLab2Events *me)
{
    CEcoLab2Sink *pCMe = (CEcoLab2Sink *)me;

    if (me == 0)
    {
        return -1;
    }

    printf("Hello from another sinker\n");

    return 0;
}

int16_t ECOCALLMETHOD CEcoLab2Sink_CountElements(/* in */ struct IEcoLab2Events *me, uint32_t *countedArray, int32_t *inputArray, uint32_t length, int32_t min)
{
    int32_t i;
    CEcoLab2Sink *pCMe = (CEcoLab2Sink *)me;

    if (me == 0)
    {
        return -1;
    }

    for (i = 0; i < length; i++)
    {
        countedArray[inputArray[i] - min]++;
    }

    return 0;
}

IEcoLab2VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C792VTblEvents = {
    CEcoLab2Sink_QueryInterface,
    CEcoLab2Sink_AddRef,
    CEcoLab2Sink_Release,
    CEcoLab2Sink_Greeting,
    CEcoLab2Sink_CountElements,
};

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
int16_t ECOCALLMETHOD createCEcoLab2Sink(/* in */ IEcoMemoryAllocator1 *pIMem, /* out */ IEcoLab2Events **ppIEcoLab2Events)
{
    int16_t result = -1;
    CEcoLab2Sink *pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab2Events == 0 || pIMem == 0)
    {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab2Sink *)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2Sink));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab2Events = &g_x2D2E3B9214F248A6A09ECB494B59C792VTblEvents;

    *ppIEcoLab2Events = (IEcoLab2Events *)pCMe;

    return 0;
};

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
void ECOCALLMETHOD deleteCEcoLab2Sink(IEcoLab2Events *pIEcoLab2Events)
{
    CEcoLab2Sink *pCMe = (CEcoLab2Sink *)pIEcoLab2Events;
    IEcoMemoryAllocator1 *pIMem = 0;

    if (pIEcoLab2Events != 0)
    {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
