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

#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorE.h"
#include "IdEcoCalculatorC.h"

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
    IEcoCalculatorX *pIX = 0;
    IEcoCalculatorY *pIY = 0;
    IEcoLab1 *pIEcoLab1_testing = 0;
    IEcoCalculatorX *pIX_testing = 0;
    IEcoCalculatorY *pIY_testing = 0;
    int operation_result;

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
    if (result != 0 || pIMem == 0)
        goto Release;

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void **)&pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0)
        goto Release;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void **)&pIX_testing);
    if (result != 0)
        printf("IEcoCalculatorX from IEcoLab1: FAILED\n");
    else
    {
        printf("IEcoCalculatorX from IEcoLab1: OK\n");
        pIX_testing->pVTbl->Release(pIX_testing);
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void **)&pIY_testing);
    if (result != 0)
        printf("IEcoCalculatorY from IEcoLab1: FAILED\n");
    else
    {
        printf("IEcoCalculatorY from IEcoLab1: OK\n");
        pIY_testing->pVTbl->Release(pIY_testing);
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void **)&pIEcoLab1_testing);
    if (result != 0)
        printf("IEcoCalculatorY from IEcoLab1: FAILED\n");
    else
    {
        printf("IEcoCalculatorY from IEcoLab1: OK\n");
        pIEcoLab1_testing->pVTbl->Release(pIEcoLab1_testing);
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void **)&pIX);
    if (result != 0 || pIX == 0)
        goto Release;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void **)&pIY);
    if (result != 0 || pIY == 0)
        goto Release;

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void **)&pIY_testing);
    if (result != 0)
        printf("IEcoCalculatorY from IEcoCalculatorX: FAILED\n");
    else
    {
        printf("IEcoCalculatorY from IEcoCalculatorX: OK\n");
        pIY_testing->pVTbl->Release(pIY_testing);
    }

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void **)&pIEcoLab1_testing);
    if (result != 0)
        printf("IEcoLab1 from IEcoCalculatorX: FAILED\n");
    else
    {
        printf("IEcoLab1 from IEcoCalculatorX: OK\n");
        pIEcoLab1_testing->pVTbl->Release(pIEcoLab1_testing);
    }

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, (void **)&pIX_testing);
    if (result != 0)
        printf("IEcoCalculatorX from IEcoCalculatorX: FAILED\n");
    else
    {
        printf("IEcoCalculatorX from IEcoCalculatorX: OK\n");
        pIX_testing->pVTbl->Release(pIX_testing);
    }

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void **)&pIX_testing);
    if (result != 0)
        printf("IEcoCalculatorX from IEcoCalculatorY: FAILED\n");
    else
    {
        printf("IEcoCalculatorX from IEcoCalculatorY: OK\n");
        pIX_testing->pVTbl->Release(pIX_testing);
    }

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void **)&pIEcoLab1_testing);
    if (result != 0)
        printf("IEcoLab1 from IEcoCalculatorY: FAILED\n");
    else
    {
        printf("IEcoLab1 from IEcoCalculatorY: OK\n");
        pIEcoLab1_testing->pVTbl->Release(pIEcoLab1_testing);
    }

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorY, (void **)&pIY_testing);
    if (result != 0)
        printf("IEcoCalculatorY from IEcoCalculatorY: FAILED\n");
    else
    {
        printf("IEcoCalculatorY from IEcoCalculatorY: OK\n");
        pIY_testing->pVTbl->Release(pIY_testing);
    }

    operation_result = pIX->pVTbl->Addition(pIX, 1, 1);
    printf("Addition: %s\n", operation_result == 2 ? "OK" : "FAILED");

    operation_result = pIX->pVTbl->Subtraction(pIX, 2, 1);
    printf("Subtraction: %s\n", operation_result == 1 ? "OK" : "FAILED");

    operation_result = pIY->pVTbl->Multiplication(pIY, 2, 2);
    printf("Multiplication: %s\n", operation_result == 4 ? "OK" : "FAILED");

    operation_result = pIY->pVTbl->Division(pIY, 4, 2);
    printf("Division: %s\n", operation_result == 2 ? "OK" : "FAILED");

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