#pragma once

class GodMode {
public:
    static inline bool bPlayerGodMode = false;  // 现在这个既是开关也是状态维持
    static inline bool bVehicleGodMode = false; // 同上

    static inline DWORD BytesRead = 0x0;

public:
    static bool OnDMAFrame();

    static bool PlayerSet(bool GodMode);
    static bool VehicleSet(bool GodMode);

    static bool IsPlayerGodModeEnabled();
    static bool IsVehicleGodModeEnabled(); // 新增载具无敌状态检查
};