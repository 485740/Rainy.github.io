#pragma once
#include <cstdint>

namespace Offsets
{
    // 基础指针偏移
    static const uintptr_t WorldPtr = 0x43C03F8;         // 世界管理器指针
    static const uintptr_t GlobalPtr = 0x3FB2EF8;        // 全局指针
    static const uintptr_t BlipPtr = 0x3E63AF0;          // 小地图标记指针

    // 世界和实体相关
    static const uintptr_t ReplayInterface = 0x1F58B58;  // 实体管理器偏移 (示例值，需验证)
    static const uintptr_t ViewMatrixPtr = 0x20019E0;    // 视图矩阵指针偏移

    // PED结构内部偏移
    namespace Ped {
        static const uintptr_t InvisibilityFlag = 0x002C;  // 隐身标志
        static const uintptr_t CNavigationPtr = 0x0030;    // 导航组件指针
        static const uintptr_t GodFlags = 0x0188;          // 无敌标记
        static const uintptr_t CurrentHealth = 0x0280;     // 当前生命值
        static const uintptr_t MaxHealth = 0x0284;         // 最大生命值
        static const uintptr_t CVehiclePtr = 0x0D10;       // 载具指针
        static const uintptr_t InVehicleBits = 0x0E32;     // 载具状态位
        static const uintptr_t PlayerInfoPtr = 0x10A8;     // 玩家信息指针
        static const uintptr_t WeaponInventoryPtr = 0x10B0; // 武器库存指针
        static const uintptr_t WeaponManagerPtr = 0x10B8;  // 武器管理器指针
    }

    // CNavigation结构内部偏移
    namespace Navigation {
        static const uintptr_t Position = 0x0050;         // 位置坐标
        static const uintptr_t CameraZ = 0x0088;          // 摄像机Z轴旋转
        static const uintptr_t CameraX = 0x0090;          // 摄像机X轴旋转
        static const uintptr_t CameraY = 0x0094;          // 摄像机Y轴旋转
    }

    // 骨骼系统关键偏移
    namespace Bones {
        static const uintptr_t MatrixPtr = 0x60;          // 骨骼变换矩阵指针 (PED内偏移)
        static const uintptr_t ArrayBase = 0x410;         // 骨骼数组基址 (PED内偏移)
        static const uintptr_t BoneSize = 0x10;           // 单个骨骼数据大小
    }

    // 视图矩阵偏移
    namespace ViewMatrix {
        static const uintptr_t CameraStruct = 0x24C;      // 视图矩阵在相机结构中的偏移
    }

    // 实体列表相关
    namespace EntityList {
        static const uintptr_t PedInterface = 0x18;       // 实体接口偏移 (ReplayInterface内)
        static const uintptr_t PedListBase = 0x100;       // 实体列表基址 (PedInterface内)
    }

    // 玩家信息结构
    namespace PlayerInfo {
        static const uintptr_t WalkSpeed = 0x01E4;        // 行走速度
        static const uintptr_t WantedLevel = 0x08E8;      // 通缉等级
        static const uintptr_t RunSpeed = 0x0D50;         // 奔跑速度
    }

    // 武器系统
    namespace Weapon {
        static const uintptr_t AmmoModifier = 0x0078;          // 弹药倍率 (WeaponInventory内)
        static const uintptr_t AmmoInClip = 0x007C;            // 弹夹弹药 (WeaponInventory内)
        static const uintptr_t AmmoInReserve = 0x0080;         // 后备弹药 (WeaponInventory内)
        static const uintptr_t WeaponInfoPtr = 0x0020;         // 武器信息指针 (WeaponManager内)
        static const uintptr_t WeaponDamage = 0x00B0;          // 武器伤害 (WeaponInfo内)
        static const uintptr_t WeaponFireRate = 0x013C;        // 射速 (WeaponInfo内)
        static const uintptr_t WeaponRange = 0x028C;           // 射程 (WeaponInfo内)
        static const uintptr_t RecoilAmplitude = 0x02F4;       // 后坐力 (WeaponInfo内)
    }

    // 载具系统
    namespace Vehicle {
        static const uintptr_t ModelInfoPtr = 0x0020;          // 模型信息指针 (CVehicle内)
        static const uintptr_t GodBits = 0x0188;               // 无敌标记 (CVehicle内)
        static const uintptr_t Health = 0x0280;                // 耐久度 (CVehicle内)
        static const uintptr_t HandlingDataPtr = 0x0960;       // 物理数据指针 (CVehicle内)

        // 物理数据处理
        namespace Handling {
            static const uintptr_t Mass = 0x000C;              // 质量
            static const uintptr_t Acceleration = 0x004C;      // 加速度
            static const uintptr_t Thrust = 0x0338;            // 推力
        }
    }
}