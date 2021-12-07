#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H


// ACTIONS
//
#define ACT_ENABLE_POWER						1		// Включить питание блока
#define ACT_DISABLE_POWER						2		// Выключить питание блока
#define ACT_CLR_FAULT							3		// Очистка ошибки
#define ACT_CLR_WARNING							4		// Очистка предупреждения
//
#define ACT_DBG_INT_PS_CONTROL					50		// Отладочный режим - управление внутренним БП
#define ACT_DBG_INT_PS_DISCHARGE				51		// Отладочный режим - разряд внутреннего БП
#define ACT_DBG_PROTECTION_RESET				52		// Отладочный режим - сброс защиты по перенапряжению на управляющем выходе
#define ACT_DBG_OUTPUT_LOCK_CONTROL				53		// Отладочный режим - управление блокировкой выхода
#define ACT_DBG_SYNC							54		// Отладочный режим - формирование импульса синхронизации
#define ACT_DBG_GENERATE_PULSE					55		// Отладочный режим - формирование импульса
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
#define REG_V_INT_PS_OFFSET						0		// Смещение оцифрованных значений напряжения внутреннего источника
#define REG_V_INT_PS_K							1		// Коэффициент пересчета АЦП в напряжение, мВ
#define REG_SW_PULSE_WIDTH						2		// Длительность импульса в режиме программного запуска, мкс
#define REG_INTPS_STAB_COUNTER_VALUE			3		// Макс. значение счетчика при задании напряжения внутреннего источника
#define REG_ERR_FOR_FORCED_DISCHARGE			4		// Ошибка, при которой включается форсированный разряд внутреннего источника (% * 10)
#define REG_INTPS_ALLOWED_ERROR					5		// Минимально допустимая ошибка задания напряжения внутреннего источника (% * 10)
#define REG_V_INTPS_DEF							6		// Напряжение внутреннего источника по умолчанию в рабочем режиме (В * 10)
//
#define REG_CTRL1_MAX_WIDTH						10		// Максимальная длительность импульса CTRL1 при 50А/мкс
#define REG_CTRL2_MAX_WIDTH						11		// Максимальная длительность импульса CTRL2
//
#define REG_CTRL1_OFFSET						12		// Смещение грубой подстройки тока при скрости спада 50.0 А/мкс
#define REG_CTRL1_K								13		// Коэффициент грубой подстройки тока при скрости спада 50.0 А/мкс
#define REG_CTRL2_OFFSET						14		// Смещение грубой подстройки тока
#define REG_CTRL2_K								15		// Коэффициент грубой подстройки тока
//
#define REG_I_TO_DAC_OFFSET						20		// Смещение преобразования ток->ЦАП
#define REG_I_TO_DAC_K							21		// Коэффициент преобразования ток->ЦАП
#define REG_I_TO_DAC_P0							22		// Регистр тонкой подстройки Р0
#define REG_I_TO_DAC_P1							23		// Регистр тонкой подстройки Р1
#define REG_I_TO_DAC_P2							24		// Регистр тонкой подстройки Р2
//
#define REG_CURRENT_SETPOINT					128		// Амплитуда задаваемого тока, А
#define REG_V_INTPS_SETPOINT					129		// Принудительная установка напряжения внутреннего источника, В * 10

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
#define REG_INT_PS_VOLTAGE						200		// Напряжение источника формирователя, (в В х10)
// -----------------------------
#define REG_FWINFO_SLAVE_NID					256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID					257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN						260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN					261	// Begining of the information string record


// FAULT & DISABLE
//
#define DF_NONE									0
#define DF_PROTECTION							1		// Защита от перенапряжения в цепи управления

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
