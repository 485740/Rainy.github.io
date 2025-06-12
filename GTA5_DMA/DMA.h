#pragma once

class DMA
{
public: /* �ӿڱ��� */
	static inline VMM_HANDLE vmh = 0;
	static inline DWORD PID = 0;

	static inline uintptr_t BaseAddress = 0;
	static inline uintptr_t LocalPlayerAddress = 0;      // ������ҵ�ַ
	static inline uintptr_t NavigationAddress = 0;        // ������ַ
	static inline uintptr_t PlayerInfoAddress = 0;        // �����Ϣ��ַ
	static inline uintptr_t VehicleAddress = 0;           // �ؾߵ�ַ
	static inline uintptr_t VehicleNavigationAddress = 0; // �ؾߵ�����ַ
	static inline uintptr_t WeaponInventoryAddress = 0;  // ��������ַ
	static inline uintptr_t WeaponManagerAddress = 0;     // ������������ַ
	static inline uintptr_t WeaponInfoAddress = 0;        // ������Ϣ��ַ

	static inline Vec3 LocalPlayerLocation = { 0,0,0 };   // �����������

public: /* DMA�ӿں��� */
	static bool Initialize();               // ��ʼ��
	static bool DMAThreadEntry();           // DMA�߳����
	static bool UpdatePlayerCurrentLocation();  // ������ҵ�ǰλ��
	static bool UpdateVehicleInformation();     // �����ؾ���Ϣ

public: /* ȫ�ֲ��� */
	static uintptr_t GetGlobalAddress(DWORD Index);  // ��ȡȫ�ֵ�ַ

	template <typename T>
	static bool GetGlobalValue(DWORD Index, T& Out)  // ��ȡȫ��ֵ
	{
		uintptr_t GlobalAddress = GetGlobalAddress(Index);
		if (!GlobalAddress) return 0;

		T ReturnValue = 0;
		DWORD BytesRead = 0x0;

		VMMDLL_MemReadEx(vmh, PID, GlobalAddress, (BYTE*)&ReturnValue, sizeof(T), &BytesRead, VMMDLL_FLAG_NOCACHE);

		if (BytesRead != sizeof(T))
			return 0;

		Out = ReturnValue;
		return 1;
	}

	template <typename T>
	static bool SetGlobalValue(DWORD Index, T In)  // ����ȫ��ֵ
	{
		uintptr_t GlobalAddress = GetGlobalAddress(Index);
		if (!GlobalAddress) return 0;

		VMMDLL_MemWrite(vmh, PID, GlobalAddress, (BYTE*)&In, sizeof(T));
		return 1;
	}

private: /* ˽�к��� */
	static bool UpdateEssentials();  // ���»�����Ϣ
	static bool Close();             // �رսӿ�
};