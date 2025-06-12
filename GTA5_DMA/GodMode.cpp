#include "pch.h"
#include "GodMode.h"

bool GodMode::OnDMAFrame()
{
    // 玩家无敌状态维持
    if (bPlayerGodMode && !IsPlayerGodModeEnabled())
    {
        PlayerSet(true);
    }
    else if (!bPlayerGodMode && IsPlayerGodModeEnabled())
    {
        PlayerSet(false);
    }

    // 载具无敌状态维持
    if (bVehicleGodMode && !IsVehicleGodModeEnabled())
    {
        VehicleSet(true);
    }
    else if (!bVehicleGodMode && IsVehicleGodModeEnabled())
    {
        VehicleSet(false);
    }

    return true;
}

bool GodMode::PlayerSet(bool GodMode)
{
    uintptr_t GodBitsAddress = DMA::LocalPlayerAddress + offsetof(PED, GodFlags);
    uint32_t OriginalBits = 0x0;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, GodBitsAddress, (BYTE*)&OriginalBits, sizeof(uint32_t), &BytesRead, VMMDLL_FLAG_NOCACHE);

    if (BytesRead != sizeof(uint32_t))
    {
        std::println("{} failed!", __FUNCTION__);
        return false;
    }

    std::bitset<16> GodBits(OriginalBits);

    if (GodMode)
    {
        GodBits.set(4);
        GodBits.set(8);
    }
    else
    {
        GodBits.reset(4);
        GodBits.reset(8);
    }

    uint32_t Bits = GodBits.to_ulong();
    VMMDLL_MemWrite(DMA::vmh, DMA::PID, GodBitsAddress, (BYTE*)&Bits, sizeof(uint32_t));

    return true;
}

bool GodMode::IsPlayerGodModeEnabled()
{
    uintptr_t GodBitsAddress = DMA::LocalPlayerAddress + offsetof(PED, GodFlags);
    uint32_t CurrentBits = 0x0;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, GodBitsAddress, (BYTE*)&CurrentBits, sizeof(uint32_t), &BytesRead, VMMDLL_FLAG_NOCACHE);

    if (BytesRead != sizeof(uint32_t))
        return false;

    std::bitset<16> GodBits(CurrentBits);
    return GodBits.test(4) && GodBits.test(8);
}

bool GodMode::IsVehicleGodModeEnabled()
{
    uintptr_t GodBitsAddress = DMA::VehicleAddress + offsetof(CVehicle, GodBits);
    uint32_t CurrentBits = 0x0;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, GodBitsAddress, (BYTE*)&CurrentBits, sizeof(uint32_t), &BytesRead, VMMDLL_FLAG_NOCACHE);

    if (BytesRead != sizeof(uint32_t))
        return false;

    std::bitset<16> GodBits(CurrentBits);
    return GodBits.test(4) && GodBits.test(8);
}

bool GodMode::VehicleSet(bool GodMode)
{
    uintptr_t GodBitsAddress = DMA::VehicleAddress + offsetof(CVehicle, GodBits);
    uint32_t OriginalBits = 0x0;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, GodBitsAddress, (BYTE*)&OriginalBits, sizeof(uint32_t), &BytesRead, VMMDLL_FLAG_NOCACHE);

    if (BytesRead != sizeof(uint32_t))
    {
        std::println("{} failed!", __FUNCTION__);
        return false;
    }

    std::bitset<16> GodBits(OriginalBits);

    if (GodMode)
    {
        GodBits.set(4);
        GodBits.set(8);
    }
    else
    {
        GodBits.reset(4);
        GodBits.reset(8);
    }

    uint32_t Bits = GodBits.to_ulong();
    VMMDLL_MemWrite(DMA::vmh, DMA::PID, GodBitsAddress, (BYTE*)&Bits, sizeof(uint32_t));

    return true;
}