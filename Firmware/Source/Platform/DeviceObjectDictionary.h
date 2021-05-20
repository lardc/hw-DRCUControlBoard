#ifndef __DEV_OBJ_DIC_H
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
#define REG_V_BAT_K								1		// Коэффициент пересчета АЦП в напряжение, мВ
#define REG_V_INT_PS_OFFSET						2		// Смещение оцифрованных значений напряжения внутреннего источника
#define REG_V_INT_PS_K							3		// Коэффициент пересчета АЦП в напряжение, мВ
//
#define REG_I_DUT_OFFSET						10		// Смещение оцифрованных значений тока
#define REG_I_DUT_K								11		// Коэффициент пересчета АЦП в ток, А
#define REG_I_DUT_P0							12		// Смещение тонкой подстройки Р0
#define REG_I_DUT_P1							13		// Коэффициент тонкой подстройки Р1
#define REG_I_DUT_P2							14		// Коэффициент тонкой подстройки Р2
#define REG_I_TO_DAC_OFFSET						15		// Смещение преобразования ток->ЦАП
#define REG_I_TO_DAC_K							16		// Коэффициент преобразования ток->ЦАП
#define REG_I_TO_DAC_P0							17		// Регистр тонкой подстройки Р0
#define REG_I_TO_DAC_P1							18		// Регистр тонкой подстройки Р1
#define REG_I_TO_DAC_P2							19		// Регистр тонкой подстройки Р2
//
#define REG_INTPS_STAB_COUNTER_VALUE			20		// Макс. значение счетчика при задании напряжения внутреннего источника
#define REG_ERR_FOR_FORCED_DISCHARGE			21		// Ошибка, при которой включается форсированный разряд внутреннего источника (% * 10)
#define REG_INTPS_ALLOWED_ERROR					22		// Минимально допустимая ошибка задания напряжения внутреннего источника (% * 10)
#define REG_BATTERY_FULL_CHRAGE_TIMEOUT			23		// Таймаут полного заряда батареи,мс
#define REG_BATTERY_RECHRAGE_TIMEOUT			24		// Таймаут дозаряда батареи,мс
#define REG_BAT_VOLTAGE_THRESHOLD				25		// Минимальный порог заряда батареи, В *10
#define REG_MAXIMUM_UNIT_CURRENT				26		// Максимальное значение тока с блока
#define REG_CONFIG_RDY_STATE_TIMEOUT			27		// Таймаут нахождения блока в состоянии ConfigReady
#define REG_ERROR_COUNTER_MAX					28		// Максимальное значение счетчика при определении выхода тока на задание
#define REG_ALLOWED_ERROR						29		// Допустимая ошибка определения выхода тока на задание (% * 10)
#define REG_AFTER_PULSE_PAUSE					30		// Пауза после импульса, мс
#define REG_FAN_CTRL							31		// Разрешение работы вентиляторов
#define REG_FAN_OPERATE_PERIOD					32		// Период работы вентилятора, с
#define REG_FAN_OPERATE_TIME					33		// Длительность работы вентилятора, с
//
#define REG_CTRL1_MAX_WIDTH_050					40		// Максимальная длительность импульса CTRL1 при 0.5А/мкс
#define REG_CTRL1_MAX_WIDTH_075					41		// Максимальная длительность импульса CTRL1 при 0.75А/мкс
#define REG_CTRL1_MAX_WIDTH_100					42		// Максимальная длительность импульса CTRL1 при 1А/мкс
#define REG_CTRL1_MAX_WIDTH_250					43		// Максимальная длительность импульса CTRL1 при 2.5А/мкс
#define REG_CTRL1_MAX_WIDTH_500					44		// Максимальная длительность импульса CTRL1 при 5А/мкс
#define REG_CTRL1_MAX_WIDTH_750					45		// Максимальная длительность импульса CTRL1 при 7.5А/мкс
#define REG_CTRL1_MAX_WIDTH_1000				46		// Максимальная длительность импульса CTRL1 при 10А/мкс
#define REG_CTRL1_MAX_WIDTH_1500				47		// Максимальная длительность импульса CTRL1 при 15А/мкс
#define REG_CTRL1_MAX_WIDTH_2500				48		// Максимальная длительность импульса CTRL1 при 25А/мкс
#define REG_CTRL1_MAX_WIDTH_3000				49		// Максимальная длительность импульса CTRL1 при 30А/мкс
#define REG_CTRL1_MAX_WIDTH_5000				50		// Максимальная длительность импульса CTRL1 при 50А/мкс
#define REG_CTRL2_MAX_WIDTH						51		// Максимальная длительность импульса CTRL2
//
#define REG_INTPS_VOLTAGE_050					52		// Напряжение внутреннего источника для скорости 0.50 А/мкс
#define REG_INTPS_VOLTAGE_075					53		// Напряжение внутреннего источника для скорости 0.75 А/мкс
#define REG_INTPS_VOLTAGE_100					54		// Напряжение внутреннего источника для скорости 1.00 А/мкс
#define REG_INTPS_VOLTAGE_250					55		// Напряжение внутреннего источника для скорости 2.50 А/мкс
#define REG_INTPS_VOLTAGE_500					56		// Напряжение внутреннего источника для скорости 5.00 А/мкс
#define REG_INTPS_VOLTAGE_750					57		// Напряжение внутреннего источника для скорости 7.50 А/мкс
#define REG_INTPS_VOLTAGE_1000					58		// Напряжение внутреннего источника для скорости 10.0 А/мкс
#define REG_INTPS_VOLTAGE_1500					59		// Напряжение внутреннего источника для скорости 15.0 А/мкс
#define REG_INTPS_VOLTAGE_2500					60		// Напряжение внутреннего источника для скорости 25.0 А/мкс
#define REG_INTPS_VOLTAGE_3000					61		// Напряжение внутреннего источника для скорости 30.0 А/мкс
#define REG_INTPS_VOLTAGE_5000					62		// Напряжение внутреннего источника для скорости 50.0 А/мкс
//
#define REG_CTRL1_050_OFFSET					63		// Смещение грубой подстройки тока при скрости спада 0.50 А/мкс
#define REG_CTRL1_050_K							64		// Коэффициент грубой подстройки тока при скрости спада 0.50 А/мкс
#define REG_CTRL1_075_OFFSET					65		// Смещение грубой подстройки тока при скрости спада 0.75 А/мкс
#define REG_CTRL1_075_K							66		// Коэффициент грубой подстройки тока при скрости спада 0.75 А/мкс
#define REG_CTRL1_100_OFFSET					67		// Смещение грубой подстройки тока при скрости спада 1.00 А/мкс
#define REG_CTRL1_100_K							68		// Коэффициент грубой подстройки тока при скрости спада 1.00 А/мкс
#define REG_CTRL1_250_OFFSET					69		// Смещение грубой подстройки тока при скрости спада 2.50 А/мкс
#define REG_CTRL1_250_K							70		// Коэффициент грубой подстройки тока при скрости спада 2.50 А/мкс
#define REG_CTRL1_500_OFFSET					71		// Смещение грубой подстройки тока при скрости спада 5.00 А/мкс
#define REG_CTRL1_500_K							72		// Коэффициент грубой подстройки тока при скрости спада 5.00 А/мкс
#define REG_CTRL1_750_OFFSET					73		// Смещение грубой подстройки тока при скрости спада 7.50 А/мкс
#define REG_CTRL1_750_K							74		// Коэффициент грубой подстройки тока при скрости спада 7.50 А/мкс
#define REG_CTRL1_1000_OFFSET					75		// Смещение грубой подстройки тока при скрости спада 10.0 А/мкс
#define REG_CTRL1_1000_K						76		// Коэффициент грубой подстройки тока при скрости спада 10.0 А/мкс
#define REG_CTRL1_1500_OFFSET					77		// Смещение грубой подстройки тока при скрости спада 15.0 А/мкс
#define REG_CTRL1_1500_K						78		// Коэффициент грубой подстройки тока при скрости спада 15.0 А/мкс
#define REG_CTRL1_2500_OFFSET					79		// Смещение грубой подстройки тока при скрости спада 25.0 А/мкс
#define REG_CTRL1_2500_K						80		// Коэффициент грубой подстройки тока при скрости спада 25.0 А/мкс
#define REG_CTRL1_3000_OFFSET					81		// Смещение грубой подстройки тока при скрости спада 30.0 А/мкс
#define REG_CTRL1_3000_K						82		// Коэффициент грубой подстройки тока при скрости спада 30.0 А/мкс
#define REG_CTRL1_5000_OFFSET					83		// Смещение грубой подстройки тока при скрости спада 50.0 А/мкс
#define REG_CTRL1_5000_K						84		// Коэффициент грубой подстройки тока при скрости спада 50.0 А/мкс
#define REG_CTRL2_OFFSET						85		// Смещение грубой подстройки тока
#define REG_CTRL2_K								86		// Коэффициент грубой подстройки тока
//
#define REG_I_RATE_COMPENS_050					87		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 0.50 A/us
#define REG_I_RATE_COMPENS_075					88		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 0.75 A/us
#define REG_I_RATE_COMPENS_100					89		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 1.00 A/us
#define REG_I_RATE_COMPENS_250					90		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 2.50 A/us
#define REG_I_RATE_COMPENS_500					91		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 5.00 A/us
#define REG_I_RATE_COMPENS_750					92		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 7.50 A/us
#define REG_I_RATE_COMPENS_1000					93		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 10.0 A/us
#define REG_I_RATE_COMPENS_1500					94		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 15.0 A/us
#define REG_I_RATE_COMPENS_2500					95		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 25.0 A/us
#define REG_I_RATE_COMPENS_3000					96		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 30.0 A/us
#define REG_I_RATE_COMPENS_5000					97		// Коэффициент компенсации зависимости dI/dt от амплитуды тока задания при 50.0 A/us

#define REG_CURRENT_SETPOINT					128		// Амплитуда задаваемого тока, А
#define REG_CURRENT_RATE						129		// Скорость измерения тока, А/мкс

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
#define REG_CURRENT								201		// Измеренное значение амплитуды тока (в мА)
#define REG_INT_PS_VOLTAGE						202
// -----------------------------
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record


// ENDPOINTS
//
#define EP_DUT_I								1		// Оцифрованные данные тока DUT (в мА)


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// Ошибка заряда батареи
#define DF_PROTECTION							2		// Защита от перенапряжения в цепи управления

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
