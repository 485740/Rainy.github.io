#pragma once

#include "Offsets.h"    // 确保 Vec3、VMMDLL_SCATTER_HANDLE、CNavigation、PED 等类型已定义
#include <cstdint>

// 传送模块状态
enum class TeleportState : uint8_t
{
    Idle,
    Preparing,
    InProgress
};

class Teleport
{
public:
    // ImGui 界面渲染，每帧由主线程调用
    static bool Render();

    // DMA 线程每帧回调，每帧由 DMA 调用
    static bool OnDMAFrame();

    // 主开关：启用/关闭整个传送功能
    static inline bool bEnable = false;
    // 单次传送请求标志
    static inline bool bRequestedTeleport = false;
    // 自动传送到导航点开关
    static inline bool bAutoTeleport = false;

private:
    // 缓存的起始位置（用于判断传送成功）
    static inline Vec3 StartingLocation = { 0.0f, 0.0f, 0.0f };
    // 本次要传送到的目标位置
    static inline Vec3 DesiredLocation = { 0.0f, 0.0f, 0.0f };

    // 传送状态机
    static inline TeleportState State = TeleportState::Idle;
    // 已尝试写入次数
    static inline int Attempts = 0;
    // VMMDLL 散射写句柄
    static inline VMMDLL_SCATTER_HANDLE ScatterHandle = nullptr;

    //
    // —— 核心流程函数 —— 
    //

    // 从 Idle/Preparing 状态启动传送（准备散射写）
    static void StartTeleport();
    // 在 InProgress 状态下，每帧推进一次散射写
    static void StepTeleport();

    //
    // —— 原有辅助函数 —— 
    //

    // 读取并缓存玩家当前坐标到 StartingLocation
    static bool UpdatePlayerStartingLocation();
    // 立即做一次完整写入（保留备用）
    static void OverwriteLocation(const Vec3& dest);
    // 准备玩家坐标写入
    static void PreparePlayerWrites(VMMDLL_SCATTER_HANDLE vmsh);
    // 准备载具坐标写入（如果在载具中）
    static void PrepareVehicleWrites(VMMDLL_SCATTER_HANDLE vmsh);
    // 获取并返回当前导航点坐标（无点返回 0,0,0）
    static Vec3 GetWaypointCoords();

};