#pragma once
#include "DMA.h"
#include <map>
#include <string>

// 冲击类型枚举
enum eImpactType {
    IT_BULLET = 3,
    IT_EXPLOSION = 5
};

// 爆炸类型枚举
enum eImpactExplosion {
    IE_PETROL_PUMP = 9
};

class WeaponInspector
{
public:
    static bool Render();
    static bool OnDMAFrame();
    static bool UpdateEssentials();

    static inline bool bEnable = true;
    static inline bool bNoReload = false;
    static inline bool bLockAmmoCount = false;
    static inline int LockedAmmoCount = -1;

    static inline bool bNoSpread = true;       // 子弹无扩散
    static inline bool bNoRecoil = true;       // 零后坐力
    static inline uintptr_t LastWeaponInfoAddress = 0;


private:
    static bool UpdateCurrentWeapon();
    static bool UpdateWeaponInventory();
    static bool UpdateWeaponInfo();
    static bool EnableNoReload();
    static bool DisableNoReload();

    static void LogError(const std::string& context, const std::string& message);

    static inline uintptr_t WeaponInvAddress = 0x0;
    static inline WeaponInfo WepInfo{};
    static inline WeaponInventory WepInv{};
    static inline WeaponInfo DesiredWepInfo{};

    static inline DWORD BytesRead = 0x0;
    static inline bool bPrevNoReload = false;
    static inline bool bWeaponModified = false;

    template<typename T>
    static bool WriteField(uintptr_t base, size_t offset, const T& value)
    {
        return VMMDLL_MemWrite(DMA::vmh, DMA::PID, base + offset, (BYTE*)&value, sizeof(T));
    }

};
