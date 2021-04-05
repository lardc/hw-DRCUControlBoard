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
//
#define REG_BATTERY_FULL_CHRAGE_TIMEOUT			20		// Таймаут полного заряда батареи,мс
#define REG_BATTERY_RECHRAGE_TIMEOUT			21		// Таймаут дозаряда батареи,мс
#define REG_BAT_VOLTAGE_THRESHOLD				22		// Минимальный порог заряда батареи, В *10
#define REG_CURRENT_BOARD_QUANTITY				23		// Количество силовых плат
// -----------------------------------------------

#define REG_CURRENT_SETPOINT					128		// Амплитуда задаваемого тока, А
#define REG_CURRENT_RATE						129		// Скорость измерения тока, А/мкс

#define REG_DBG									150		// Отладочный регистр
// -----------------------------------------------

#define REG_DEV_STATE							96		// Статус работы блока
#define REG_FAULT_REASON						97		// Ошибка работы блока
#define REG_DISABLE_REASON						98		// Причина отключения блока
#define REG_WARNING								99		// Предупреждение
#define REG_PROBLEM								100		// Регистр Problem
//
#define REG_BAT_VOLTAGE							103		// Напряжение на конденсаторной батарее 1 (в В х10)
//
#define REG_CURRENT								111		// Измеренное значение амплитуды тока (в мА)


// ENDPOINTS
//
#define EP_DUT_I								1		// Оцифрованные данные тока DUT (в мА)


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_BATTERY								1		// Ошибка заряда батареи

// WARNINGS
//
#define WARNING_NONE							0

// User Errors
// 
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1		// Устройство защищено от записи
#define ERR_OPERATION_BLOCKED					2		// Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY					3		// Устройство не готово для смены состояния
#define ERR_WRONG_PWD							4		// Неправильный ключ


#endif // __DEV_OBJ_DIC_H
