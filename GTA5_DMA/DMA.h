#pragma once

class DMA
{
public: /* 接口变量 */
	static inline VMM_HANDLE vmh = 0;
	static inline DWORD PID = 0;

	static inline uintptr_t BaseAddress = 0;
	static inline uintptr_t LocalPlayerAddress = 0;      // 本地玩家地址
	static inline uintptr_t NavigationAddress = 0;        // 导航地址
	static inline uintptr_t PlayerInfoAddress = 0;        // 玩家信息地址
	static inline uintptr_t VehicleAddress = 0;           // 载具地址
	static inline uintptr_t VehicleNavigationAddress = 0; // 载具导航地址
	static inline uintptr_t WeaponInventoryAddress = 0;  // 武器库存地址
	static inline uintptr_t WeaponManagerAddress = 0;     // 武器管理器地址
	static inline uintptr_t WeaponInfoAddress = 0;        // 武器信息地址

	static inline Vec3 LocalPlayerLocation = { 0,0,0 };   // 本地玩家坐标

public: /* DMA接口函数 */
	static bool Initialize();               // 初始化
	static bool DMAThreadEntry();           // DMA线程入口
	static bool UpdatePlayerCurrentLocation();  // 更新玩家当前位置
	static bool UpdateVehicleInformation();     // 更新载具信息

public: /* 全局操作 */
	static uintptr_t GetGlobalAddress(DWORD Index);  // 获取全局地址

	template <typename T>
	static bool GetGlobalValue(DWORD Index, T& Out)  // 获取全局值
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
	static bool SetGlobalValue(DWORD Index, T In)  // 设置全局值
	{
		uintptr_t GlobalAddress = GetGlobalAddress(Index);
		if (!GlobalAddress) return 0;

		VMMDLL_MemWrite(vmh, PID, GlobalAddress, (BYTE*)&In, sizeof(T));
		return 1;
	}

private: /* 私有函数 */
	static bool UpdateEssentials();  // 更新基础信息
	static bool Close();             // 关闭接口
};