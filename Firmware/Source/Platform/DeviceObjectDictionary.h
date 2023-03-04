﻿#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER						1		// Включить питание блока
#define ACT_DISABLE_POWER						2		// Выключить питание блока
#define ACT_CLR_FAULT							3		// Очистка ошибки
#define ACT_CLR_WARNING							4		// Очистка предупреждения
//
#define ACT_DBG_FAN								50		// Отладочный режим - вентилятор
#define ACT_DBG_LAMP							51		// Отладочный режим - внешний индикатор
#define ACT_DBG_RELAY_MECH						52		// Отладочный режим - механическое реле
#define ACT_DBG_RELAY_SOLID						53		// Отладочный режим - твердотельное реле
#define ACT_DBG_INT_PS_CONTROL					54		// Отладочный режим - управление внутренним БП
#define ACT_DBG_INT_PS_DISCHARGE				55		// Отладочный режим - разряд внутреннего БП
#define ACT_DBG_PROTECTION_RESET				56		// Отладочный режим - сброс защиты по перенапряжению на управляющем выходе
#define ACT_DBG_OUTPUT_LOCK_CONTROL				57		// Отладочный режим - управление блокировкой выхода
#define ACT_DBG_SYNC							58		// Отладочный режим - формирование импульса синхронизации
#define ACT_DBG_EXT_REG_WRITE_DATA				59		// Отладочный режим - запись данных во внешний регистр
#define ACT_DBG_GENERATE_PULSE					60		// Отладочный режим - формирование импульса
#define ACT_DBG_CURRENT_READY_OUTPUT			61		// Отладочный режим - формирования сигнала CurrentReady
#define ACT_DBG_SET_COMPENSATION				62		// Отладочный режим - установка напряжения компенсации
//
#define ACT_CONFIG_UNIT							100		// Конфигурация блока
#define ACT_SOFTWARE_START						101		// Программный запуск
//
#define ACT_SAVE_TO_ROM							200		// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM					201		// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT					202		// Сброс DataTable в состояние по умолчанию
//
#define ACT_BOOT_LOADER_REQUEST					320		// Перезапуск процессора с целью перепрограммирования


// REGISTERS
//
#define REG_V_BAT_OFFSET						0		// Смещение оцифрованных значений напряжения батареи
#define REG_V_BAT_K								1		// Коэффициент пересчета АЦП в напряжение, мВ (x10000)
#define REG_V_INT_PS_OFFSET						2		// Смещение оцифрованных значений напряжения внутреннего источника
#define REG_V_INT_PS_K							3		// Коэффициент пересчета АЦП в напряжение, мВ (x10000)
#define REG_I_DUT_OFFSET						4		// Смещение оцифрованных значений тока
#define REG_I_DUT_K								5		// Коэффициент пересчета АЦП в ток, А
#define REG_I_DUT_P0							6		// Смещение тонкой подстройки Р0
#define REG_I_DUT_P1							7		// Коэффициент тонкой подстройки Р1
#define REG_I_DUT_P2							8		// Коэффициент тонкой подстройки Р2
// 9
#define REG_INTPS_STAB_COUNTER_VALUE			10		// Макс. значение счетчика при задании напряжения внутреннего источника
#define REG_ERR_FOR_FORCED_DISCHARGE			11		// Ошибка, при которой включается форсированный разряд внутреннего источника (% * 10)
#define REG_INTPS_ALLOWED_ERROR					12		// Минимально допустимая ошибка задания напряжения внутреннего источника (% * 10)
#define REG_BATTERY_FULL_CHRAGE_TIMEOUT			13		// Таймаут полного заряда батареи,мс
#define REG_BATTERY_RECHRAGE_TIMEOUT			14		// Таймаут дозаряда батареи,мс
#define REG_BAT_VOLTAGE_THRESHOLD				15		// Минимальный порог заряда батареи, В *10
#define REG_MAXIMUM_UNIT_CURRENT				16		// Максимальное значение тока с блока
#define REG_CONFIG_RDY_STATE_TIMEOUT			17		// Таймаут нахождения блока в состоянии ConfigReady
// 18
#define REG_FAN_CTRL							19		// Разрешение работы вентиляторов
#define REG_FAN_OPERATE_PERIOD					20		// Период работы вентилятора, с
#define REG_FAN_OPERATE_TIME					21		// Длительность работы вентилятора, с
#define REG_ERROR_COUNTER_MAX					22		// Максимальное значение счетчика при определении выхода тока на задание
#define REG_ALLOWED_ERROR						23		// Допустимая ошибка определения выхода тока на задание (% * 10)
// 24
#define REG_CTRL1_MAX_WIDTH_R0					25		// Максимальная длительность импульса CTRL1 (скорость 0)
#define REG_CTRL1_MAX_WIDTH_R1					26		// Максимальная длительность импульса CTRL1 (скорость 1)
#define REG_CTRL1_MAX_WIDTH_R2					27		// Максимальная длительность импульса CTRL1 (скорость 2)
#define REG_CTRL1_MAX_WIDTH_R3					28		// Максимальная длительность импульса CTRL1 (скорость 3)
#define REG_CTRL1_MAX_WIDTH_R4					29		// Максимальная длительность импульса CTRL1 (скорость 4)
#define REG_CTRL1_MAX_WIDTH_R5					30		// Максимальная длительность импульса CTRL1 (скорость 5)
#define REG_CTRL1_MAX_WIDTH_R6					31		// Максимальная длительность импульса CTRL1 (скорость 6)
#define REG_CTRL1_MAX_WIDTH_R7					32		// Максимальная длительность импульса CTRL1 (скорость 7)
#define REG_CTRL1_MAX_WIDTH_R8					33		// Максимальная длительность импульса CTRL1 (скорость 8)
#define REG_CTRL1_MAX_WIDTH_R9					34		// Максимальная длительность импульса CTRL1 (скорость 9)
#define REG_CTRL1_MAX_WIDTH_R10					35		// Максимальная длительность импульса CTRL1 (скорость 10)
#define REG_CTRL2_MAX_WIDTH						36		// Максимальная длительность импульса CTRL2
//
#define REG_TQ_TIMEOUT							37		// Таймаут между измерениями Tq (мс)
#define REG_PULSE_DELAY_TQ						38		// Задержка (мс) между импульсами тока при макс. амплитуде минус UNIT_PULSE_DELAY_MIN (Global.h)
// 39
#define REG_I_TO_V_K_2							40		// (100000*к)/А^3 коэффицент преобразования тока в напряжение внутреннего источника  (для всех скоростей)
#define REG_I_TO_V_INTPS_R0_OFFSET				41		// Смещение преобразования тока в напряжение внутреннего источника (скорость 0)
#define REG_I_TO_V_INTPS_R0_K					42		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 0)
#define REG_I_TO_V_INTPS_R1_OFFSET				43		// Смещение преобразования тока в напряжение внутреннего источника (скорость 1)
#define REG_I_TO_V_INTPS_R1_K					44		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 1)
#define REG_I_TO_V_INTPS_R2_OFFSET				45		// Смещение преобразования тока в напряжение внутреннего источника (скорость 2)
#define REG_I_TO_V_INTPS_R2_K					46		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 2)
#define REG_I_TO_V_INTPS_R3_OFFSET				47		// Смещение преобразования тока в напряжение внутреннего источника (скорость 3)
#define REG_I_TO_V_INTPS_R3_K					48		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 3)
#define REG_I_TO_V_INTPS_R4_OFFSET				49		// Смещение преобразования тока в напряжение внутреннего источника при (скорость 4)
#define REG_I_TO_V_INTPS_R4_K					50		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 4)
#define REG_I_TO_V_INTPS_R5_OFFSET				51		// Смещение преобразования тока в напряжение внутреннего источника (скорость 5)
#define REG_I_TO_V_INTPS_R5_K					52		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 5)
#define REG_I_TO_V_INTPS_R6_OFFSET				53		// Смещение преобразования тока в напряжение внутреннего источника (скорость 6)
#define REG_I_TO_V_INTPS_R6_K					54		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 6)
#define REG_I_TO_V_INTPS_R7_OFFSET				55		// Смещение преобразования тока в напряжение внутреннего источника (скорость 7)
#define REG_I_TO_V_INTPS_R7_K					56		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 7)
#define REG_I_TO_V_INTPS_R8_OFFSET				57		// Смещение преобразования тока в напряжение внутреннего источника (скорость 8)
#define REG_I_TO_V_INTPS_R8_K					58		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 8)
#define REG_I_TO_V_INTPS_R9_OFFSET				59		// Смещение преобразования тока в напряжение внутреннего источника (скорость 9)
#define REG_I_TO_V_INTPS_R9_K					60		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 9)
#define REG_I_TO_V_INTPS_R10_OFFSET				61		// Смещение преобразования тока в напряжение внутреннего источника (скорость 10)
#define REG_I_TO_V_INTPS_R10_K					62		// Коэффициент преобразования тока в напряжение внутреннего источника (скорость 10)
//
#define REG_CTRL1_R0_OFFSET						63		// Смещение грубой подстройки тока при скрости спада (скорость 0)
#define REG_CTRL1_R0_K							64		// Коэффициент грубой подстройки тока при скрости спада (скорость 0)
#define REG_CTRL1_R1_OFFSET						65		// Смещение грубой подстройки тока при скрости спада (скорость 1)
#define REG_CTRL1_R1_K							66		// Коэффициент грубой подстройки тока при скрости спада (скорость 1)
#define REG_CTRL1_R2_OFFSET						67		// Смещение грубой подстройки тока при скрости спада (скорость 2)
#define REG_CTRL1_R2_K							68		// Коэффициент грубой подстройки тока при скрости спада (скорость 2)
#define REG_CTRL1_R3_OFFSET						69		// Смещение грубой подстройки тока при скрости спада (скорость 3)
#define REG_CTRL1_R3_K							70		// Коэффициент грубой подстройки тока при скрости спада (скорость 3)
#define REG_CTRL1_R4_OFFSET						71		// Смещение грубой подстройки тока при скрости спада (скорость 4)
#define REG_CTRL1_R4_K							72		// Коэффициент грубой подстройки тока при скрости спада (скорость 4)
#define REG_CTRL1_R5_OFFSET						73		// Смещение грубой подстройки тока при скрости спада (скорость 5)
#define REG_CTRL1_R5_K							74		// Коэффициент грубой подстройки тока при скрости спада (скорость 5)
#define REG_CTRL1_R6_OFFSET						75		// Смещение грубой подстройки тока при скрости спада (скорость 6)
#define REG_CTRL1_R6_K							76		// Коэффициент грубой подстройки тока при скрости спада (скорость 6)
#define REG_CTRL1_R7_OFFSET						77		// Смещение грубой подстройки тока при скрости спада (скорость 7)
#define REG_CTRL1_R7_K							78		// Коэффициент грубой подстройки тока при скрости спада (скорость 7)
#define REG_CTRL1_R8_OFFSET						79		// Смещение грубой подстройки тока при скрости спада (скорость 8)
#define REG_CTRL1_R8_K							80		// Коэффициент грубой подстройки тока при скрости спада (скорость 8)
#define REG_CTRL1_R9_OFFSET						81		// Смещение грубой подстройки тока при скрости спада (скорость 9)
#define REG_CTRL1_R9_K							82		// Коэффициент грубой подстройки тока при скрости спада (скорость 9)
#define REG_CTRL1_R10_OFFSET					83		// Смещение грубой подстройки тока при скрости спада (скорость 10)
#define REG_CTRL1_R10_K							84		// Коэффициент грубой подстройки тока при скрости спада (скорость 10)
#define REG_CTRL2_OFFSET						85		// Смещение грубой подстройки тока
#define REG_CTRL2_K								86		// Коэффициент грубой подстройки тока
//
#define REG_CTRL1_R0_P2							87		// Коэффициент Р2 для скорости (скорость 0)
#define REG_CTRL1_R0_P1							88		// Коэффициент Р1 для скорости (скорость 0)
#define REG_CTRL1_R0_P0							89		// Коэффициент Р0 для скорости (скорость 0)
#define REG_CTRL1_R1_P2							90		// Коэффициент Р2 для скорости (скорость 1)
#define REG_CTRL1_R1_P1							91		// Коэффициент Р1 для скорости (скорость 1)
#define REG_CTRL1_R1_P0							92		// Коэффициент Р0 для скорости (скорость 1)
#define REG_CTRL1_R2_P2							93		// Коэффициент Р2 для скорости (скорость 2)
#define REG_CTRL1_R2_P1							94		// Коэффициент Р1 для скорости (скорость 2)
#define REG_CTRL1_R2_P0							95		// Коэффициент Р0 для скорости (скорость 2)
#define REG_CTRL1_R3_P2							96		// Коэффициент Р2 для скорости (скорость 3)
#define REG_CTRL1_R3_P1							97		// Коэффициент Р1 для скорости (скорость 3)
#define REG_CTRL1_R3_P0							98		// Коэффициент Р0 для скорости (скорость 3)
#define REG_CTRL1_R4_P2							99		// Коэффициент Р2 для скорости (скорость 4)
#define REG_CTRL1_R4_P1							100		// Коэффициент Р1 для скорости (скорость 4)
#define REG_CTRL1_R4_P0							101		// Коэффициент Р0 для скорости (скорость 4)
#define REG_CTRL1_R5_P2							102		// Коэффициент Р2 для скорости (скорость 5)
#define REG_CTRL1_R5_P1							103		// Коэффициент Р1 для скорости (скорость 5)
#define REG_CTRL1_R5_P0							104		// Коэффициент Р0 для скорости (скорость 5)
#define REG_CTRL1_R6_P2							105		// Коэффициент Р2 для скорости (скорость 6)
#define REG_CTRL1_R6_P1							106		// Коэффициент Р1 для скорости (скорость 6)
#define REG_CTRL1_R6_P0							107		// Коэффициент Р0 для скорости (скорость 6)
#define REG_CTRL1_R7_P2							108		// Коэффициент Р2 для скорости (скорость 7)
#define REG_CTRL1_R7_P1							109		// Коэффициент Р1 для скорости (скорость 7)
#define REG_CTRL1_R7_P0							110		// Коэффициент Р0 для скорости (скорость 7)
#define REG_CTRL1_R8_P2							111		// Коэффициент Р2 для скорости (скорость 8)
#define REG_CTRL1_R8_P1							112		// Коэффициент Р1 для скорости (скорость 8)
#define REG_CTRL1_R8_P0							113		// Коэффициент Р0 для скорости (скорость 8)
#define REG_CTRL1_R9_P2							114		// Коэффициент Р2 для скорости (скорость 9)
#define REG_CTRL1_R9_P1							115		// Коэффициент Р1 для скорости (скорость 9)
#define REG_CTRL1_R9_P0							116		// Коэффициент Р0 для скорости (скорость 9)
#define REG_CTRL1_R10_P2						117		// Коэффициент Р2 для скорости (скорость 10)
#define REG_CTRL1_R10_P1						118		// Коэффициент Р1 для скорости (скорость 10)
#define REG_CTRL1_R10_P0						119		// Коэффициент Р0 для скорости (скорость 10)
//
#define REG_I_TO_DAC_OFFSET						120		// Смещение преобразования ток->ЦАП
#define REG_I_TO_DAC_K							121		// Коэффициент преобразования ток->ЦАП
#define REG_I_TO_DAC_P0							122		// Регистр тонкой подстройки Р0
#define REG_I_TO_DAC_P1							123		// Регистр тонкой подстройки Р1
#define REG_I_TO_DAC_P2							124		// Регистр тонкой подстройки Р2
//


#define REG_CURRENT_SETPOINT					128		// Амплитуда задаваемого тока, А
#define REG_CURRENT_RATE						129		// Скорость измерения тока, А/мкс
#define REG_V_INTPS_SETPOINT					130		// Принудительная установка напряжения внутреннего источника, В * 10
#define REG_PULSE_WIDTH							131		// Длительность импульса тока, мс  * 10
//
#define REG_CALIBRATION_PROCESS					140		// Флаг процесса калибровки

#define REG_DBG									150		// Отладочный регистр 1
#define REG_DBG2								151		// Отладочный регистр 2
// -----------------------------------------------

#define REG_DEV_STATE							192		// Статус работы блока
#define REG_FAULT_REASON						193		// Ошибка работы блока
#define REG_DISABLE_REASON						194		// Причина отключения блока
#define REG_WARNING								195		// Предупреждение
#define REG_PROBLEM								196		// Регистр Problem
#define REG_DEV_SUBSTATE						197		// Подстатус работы блока
//
#define REG_BAT_VOLTAGE							200		// Напряжение на конденсаторной батарее 1 (в В х10)
#define REG_INT_PS_VOLTAGE						201		// Напряжение источника формирователя, (в В х10)
#define REG_CURRENT								202		// Измеренное значение амплитуды тока (в А*10)
// -----------------------------
#define REG_FWINFO_SLAVE_NID					256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID					257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN						260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN					261	// Begining of the information string record


// ENDPOINTS
//
#define EP_DUT_I								1		// Оцифрованные данные тока DUT (в мА)


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// Ошибка заряда батареи
#define DF_PROTECTION							2		// Защита от перенапряжения в цепи управления
#define DF_SYNC									3		// Длительность импульса синхронизации превышена

// WARNINGS
//
#define WARNING_NONE							0
#define WARNING_CURRENT_NOT_READY				1		// Ток не вышел на заданный уровень

// User Errors
// 
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1		// Устройство защищено от записи
#define ERR_OPERATION_BLOCKED					2		// Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY					3		// Устройство не готово для смены состояния
#define ERR_WRONG_PWD							4		// Неправильный ключ


#endif // __DEV_OBJ_DIC_H
