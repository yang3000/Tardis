#pragma once

#include <string>

#define TARDIS_EXPORT __declspec(dllexport)

typedef void(*Callback)(const char* info);

namespace TARDIS
{
	class IHonorCustomization
	{
	public:
		virtual void SetupCallback(Callback cb, bool debug = false) = 0;

		virtual bool EnumDonglePorts() = 0;
		virtual bool InitializeConnection(const char* mac, long idx = 0) = 0;
		virtual bool DestroyConnection(long idx = 0) = 0;

		virtual bool Query(const unsigned char* req, int req_len, unsigned char* res = nullptr, int res_len = 0, byte state = 0x00) = 0;

		virtual bool SelfCheck() = 0;

		virtual bool CheckRTFlag() = 0;

		virtual bool WriteMMI3Flag(const byte flag) = 0;
		virtual bool CheckMMI3Flag(const byte flag) = 0;


		virtual bool WriteUTFlag(const byte flag) = 0;
		virtual bool CheckUTFlag(const byte flag) = 0;

		virtual bool WriteCWFlag(const byte flag) = 0;
		virtual bool CheckCWFlag(const byte flag) = 0;

		virtual bool WriteMCFlag(const byte flag) = 0;
		virtual bool CheckMCFlag(const byte flag) = 0;

		virtual bool NVBackup() = 0;
		virtual bool TriggerUpgrade() = 0;

		virtual bool WriteSN(const char* sn) = 0;
		virtual bool CheckSN(const char* sn) = 0;
		virtual bool ReadSN(char* sn, size_t len) = 0;

		virtual bool WriteImei(const char* imei) = 0;
		virtual bool CheckImei(const char* imei) = 0;

		virtual bool ReadBsn(char* bsn, size_t len) = 0;
		virtual bool ReadBtMac(char* bt, size_t len) = 0;
		virtual bool CheckBTMAC(const char* bt) = 0;

		virtual bool ReadESimId(char* eSimId, size_t len) = 0;
		virtual bool CheckESimState(byte state) = 0;
		virtual bool CheckNV() = 0;

		virtual bool WriteSKU(const char* sku) = 0;
		virtual bool CheckSKU(const char* sku) = 0;

		virtual bool ReadBatteryLevel(int& power) = 0;
		virtual bool CheckSWVersion(const char* ver) = 0;
		virtual bool CheckFlashVersion(const char* ver) = 0;
		virtual bool CheckModemVersion(const char* ver) = 0;
		virtual bool CheckPower() = 0;

		virtual ~IHonorCustomization() {};
	};

}