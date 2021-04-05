// Header
#include "Diagnostic.h"

// Includes
#include "DebugActions.h"
#include "DeviceObjectDictionary.h"

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{
		case ACT_DBG_FAN:
			DBGACT_Fan();
		break;

		case ACT_DBG_LAMP:
			DBGACT_Lamp();
		break;

		case ACT_DBG_RELAY_MECH:
			DBGACT_RelayMech();
		break;

		case ACT_DBG_RELAY_SOLID:
			DBGACT_RelaySolid();
		break;

		case ACT_DBG_INT_PS_CONTROL:
			DBGACT_InternalPowerSupplyControl();
		break;

		case ACT_DBG_INT_PS_DISCHARGE:
			DBGACT_InternalPowerSupplyDischarge();
		break;

		case ACT_DBG_PROTECTION_RESET:
			DBGACT_ProtectionReset();
		break;

		case ACT_DBG_OUTPUT_LOCK_CONTROL:
			DBGACT_OutputLockControl();
		break;

		case ACT_DBG_SYNC:
			DBGACT_Sync();
		break;

		default:
			return false;
	}

	return true;
}