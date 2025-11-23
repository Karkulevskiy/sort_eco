/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLAB2EVENTS_H__
#define __I_ECOLAB2EVENTS_H__

#include "IEcoBase1.h"

#ifndef __IID_IEcoLab2Events
static const UGUID IID_IEcoLab2Events = {0x01, 0x10, 0xB6, 0xD3, 0x86, 0x61, 0x68, 0x27, 0x46, 0xD9, 0x91, 0x35, 0xFD, 0x4B, 0x20, 0x4A, 0x68, 0xD8};
#endif /* __IID_IEcoLab2Events */

/* Обратный интерфейс */
typedef struct IEcoLab2VTblEvents
{

    /* IEcoUnknown */
    int16_t(ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoLab2Events *me, /* in */ const UGUID *riid, /* out */ void **ppv);
    uint32_t(ECOCALLMETHOD *AddRef)(/* in */ struct IEcoLab2Events *me);
    uint32_t(ECOCALLMETHOD *Release)(/* in */ struct IEcoLab2Events *me);

    int16_t(ECOCALLMETHOD *Greeting)(/* in */ struct IEcoLab2Events *me);
    int16_t(ECOCALLMETHOD *CountElements)(/* in */ struct IEcoLab2Events *me, uint32_t *countedArray, int32_t *inputArray, uint32_t length, int32_t min);
} IEcoLab2VTblEvents, *IEcoLab2VTblEventsPtr;

interface IEcoLab2Events
{
    struct IEcoLab2VTblEvents *pVTbl;
}
IEcoLab2Events;

#endif /* __I_ECOLAB2EVENTS_H__ */
