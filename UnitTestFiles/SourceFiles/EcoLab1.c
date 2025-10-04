/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include <time.h>

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */

int16_t EcoMain(IEcoUnknown *pIUnk)
{
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1 *pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1 *pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1 *pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1 *pIEcoLab1 = 0;
    int32_t *sorted_arr;
    int32_t *generated_arr;
    uint32_t length;
    uint32_t seed;
    int32_t i;
    clock_t start, end;
    double cpu_time_used;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0)
    {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0)
        {
            /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0)
    {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown *)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0)
    {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void **)&pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0)
    {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void **)&pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0)
    {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    // Test & Cmp time for CountSort
    for (i = 1; i <= 10; i++)
    {
        length = 1000000 * i;
        seed = i;
        result = pIEcoLab1->pVTbl->PseudoGenerator(pIEcoLab1, length, seed, &generated_arr);
        if (result != ERR_ECO_SUCCESES)
        {
            pIMem->pVTbl->Free(pIMem, generated_arr);
            goto Release;
        }

        start = clock();
        result = pIEcoLab1->pVTbl->CountSort(pIEcoLab1, generated_arr, length, &sorted_arr);
        end = clock();
        if (result != ERR_ECO_SUCCESES)
        {
            pIMem->pVTbl->Free(pIMem, sorted_arr);
            goto Release;
        }
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("CountSort (length = %u) time: %f seconds\n", length, cpu_time_used);
    }

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0)
    {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0)
    {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0)
    {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0)
    {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}