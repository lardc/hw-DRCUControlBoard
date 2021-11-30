// Header
#include "Diagnostic.h"

// Includes
#include "DebugActions.h"
#include "DeviceObjectDictionary.h"

// Functions
bool DIAG_HandleDiagnosticAction(Int16U ActionID, Int16U *pUserError)
{
	switch (ActionID)
	{
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

		case ACT_DBG_GENERATE_PULSE:
			DBGACT_GeneratePulse();
			break;

		default:
			return false;
	}

	return true;
}
