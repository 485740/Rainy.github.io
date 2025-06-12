#include "pch.h"
#include "WeaponInspector.h"

static inline uintptr_t LastWeaponInfoAddress = 0;


static const std::map<int, const char*> IMPACT_TYPE_NAMES = {
    {IT_BULLET, "子弹射击"},
    {IT_EXPLOSION, "爆炸伤害"}
};

static const std::map<int, const char*> EXPLOSION_TYPE_NAMES = {
    {IE_PETROL_PUMP, "爆炸子弹"},
};

bool WeaponInspector::Render()
{
    ImGui::Begin("武器功能", &bEnable);

    ImGui::Text("当前伤害: %.2f", WepInfo.WeaponDamage);
    ImGui::Text("当前射程: %.2f", WepInfo.WeaponRange);

    auto impactIt = IMPACT_TYPE_NAMES.find(WepInfo.ImpactType);
    ImGui::Text("子弹类型: %s", impactIt != IMPACT_TYPE_NAMES.end() ? impactIt->second : "未知");

    auto explosionIt = EXPLOSION_TYPE_NAMES.find(WepInfo.ImpactExplosion);
    ImGui::Text("爆炸类型: %s", explosionIt != EXPLOSION_TYPE_NAMES.end() ? explosionIt->second : "未知");

    ImGui::Separator();

    if (ImGui::Button("伤害 200")) {
        DesiredWepInfo.WeaponDamage = 200.0f;
        bWeaponModified = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("伤害9999")) {
        DesiredWepInfo.WeaponDamage = 9999.0f;
        bWeaponModified = true;
    }

    if (ImGui::Button("射程修改")) {
        DesiredWepInfo.WeaponRange = 1500.0f;
        bWeaponModified = true;
    }

    ImGui::Separator();

    if (ImGui::Button("普通子弹")) {
        DesiredWepInfo.ImpactType = IT_BULLET;
        bWeaponModified = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("爆炸子弹")) {
        DesiredWepInfo.ImpactType = IT_EXPLOSION;
        DesiredWepInfo.ImpactExplosion = IE_PETROL_PUMP;
        bWeaponModified = true;
    }

    ImGui::End();
    return true;
}

bool WeaponInspector::OnDMAFrame()
{
    DesiredWepInfo.RecoilAmplitude = bNoRecoil ? 0.0f : 0.01f;
    DesiredWepInfo.Spread = bNoSpread ? 0.0f : 0.01f;

    if (!UpdateEssentials()) {
        LogError(__FUNCTION__, "更新失败");
        return false;
    }

    if (DMA::WeaponInfoAddress) {
        WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, Spread), DesiredWepInfo.Spread);
        WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, RecoilAmplitude), DesiredWepInfo.RecoilAmplitude);
    }

    if (bNoReload != bPrevNoReload) {
        bNoReload ? EnableNoReload() : DisableNoReload();
    }
    else if (bNoReload && !(std::bitset<8>(WepInv.AmmoModifier).test(1))) {
        EnableNoReload();
    }

    if (bLockAmmoCount && LockedAmmoCount >= 0) {
        uintptr_t addr = WeaponInvAddress + offsetof(WeaponInventory, AmmoInClip);
        VMMDLL_MemWrite(DMA::vmh, DMA::PID, addr, (BYTE*)&LockedAmmoCount, sizeof(int));
    }

    // 只在标记后更新一次
    if (bWeaponModified && DMA::WeaponInfoAddress) {
        WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, WeaponDamage), DesiredWepInfo.WeaponDamage);
        WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, WeaponRange), DesiredWepInfo.WeaponRange);
        WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, ImpactType), DesiredWepInfo.ImpactType);
        WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, ImpactExplosion), DesiredWepInfo.ImpactExplosion);
        bWeaponModified = false;
    }

    return true;
}

bool WeaponInspector::UpdateEssentials()
{
    return UpdateWeaponInfo() && UpdateWeaponInventory();
}

bool WeaponInspector::UpdateCurrentWeapon()
{
    if (!DMA::WeaponInfoAddress) {
        LogError(__FUNCTION__, "在载具中，无法更新武器信息");
        return false;
    }

    WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, WeaponDamage), DesiredWepInfo.WeaponDamage);
    WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, WeaponRange), DesiredWepInfo.WeaponRange);
    WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, RecoilAmplitude), DesiredWepInfo.RecoilAmplitude);
    WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, Spread), DesiredWepInfo.Spread);
    WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, ImpactType), DesiredWepInfo.ImpactType);
    WriteField(DMA::WeaponInfoAddress, offsetof(WeaponInfo, ImpactExplosion), DesiredWepInfo.ImpactExplosion);
    return true;
}

bool WeaponInspector::UpdateWeaponInventory()
{
    uintptr_t ptr = DMA::LocalPlayerAddress + offsetof(PED, pCWeaponInventory);
    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, ptr, (BYTE*)&WeaponInvAddress, sizeof(uintptr_t), &BytesRead, VMMDLL_FLAG_NOCACHE);
    if (BytesRead != sizeof(uintptr_t)) return false;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, WeaponInvAddress, (BYTE*)&WepInv, sizeof(WepInv), &BytesRead, VMMDLL_FLAG_NOCACHE);
    return BytesRead == sizeof(WepInv);
}

bool WeaponInspector::UpdateWeaponInfo()
{
    if (!DMA::WeaponInfoAddress) {
        ZeroMemory(&WepInfo, sizeof(WepInfo));
        return true;
    }

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID, DMA::WeaponInfoAddress, (BYTE*)&WepInfo, sizeof(WepInfo), &BytesRead, VMMDLL_FLAG_NOCACHE);
    if (BytesRead != sizeof(WepInfo)) return false;

    // 检测武器切换：同步 DesiredWepInfo，避免连带写入其他字段
    if (DMA::WeaponInfoAddress != LastWeaponInfoAddress) {
        DesiredWepInfo = WepInfo;
        LastWeaponInfoAddress = DMA::WeaponInfoAddress;
    }

    return true;
}


bool WeaponInspector::EnableNoReload()
{
    std::bitset<8> Bits(WepInv.AmmoModifier);
    Bits.set(1);
    uint8_t NewBits = Bits.to_ulong();
    uintptr_t addr = WeaponInvAddress + offsetof(WeaponInventory, AmmoModifier);
    VMMDLL_MemWrite(DMA::vmh, DMA::PID, addr, (BYTE*)&NewBits, sizeof(uint8_t));
    bPrevNoReload = true;
    return true;
}

bool WeaponInspector::DisableNoReload()
{
    std::bitset<8> Bits(WepInv.AmmoModifier);
    Bits.reset(1);
    uint8_t NewBits = Bits.to_ulong();
    uintptr_t addr = WeaponInvAddress + offsetof(WeaponInventory, AmmoModifier);
    VMMDLL_MemWrite(DMA::vmh, DMA::PID, addr, (BYTE*)&NewBits, sizeof(uint8_t));
    bPrevNoReload = false;
    return true;
}

void WeaponInspector::LogError(const std::string& context, const std::string& message)
{
    std::fprintf(stderr, "[WeaponInspector::%s] 错误: %s\n", context.c_str(), message.c_str());
}
