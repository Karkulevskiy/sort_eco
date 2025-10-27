# Лабораторная работа 2
Реализована схема с агрегацией/включением

Были добавлены компонены IEcoCalculatorY, IEcoCalculatorX. \
Для включения был добавлен IEcoCalculatorY в тип CEcoLab1. \
Была использована как таблица с IEcoCalculatorYVTbl, так и функции, например: CEcoLab1_Multiplication, чтобы показать различные способы для включения и композиции компонента.

Для агрегации был использван IEcoUnknown для IEcoCalculatorX. \
Были изменены init*, QueryInterface* функции для CEcoLab1, позволяющее использовать функции IEcoCalculatorX \

В Unit тесте были показаны свойсва интерфейсов, с использованием функций
