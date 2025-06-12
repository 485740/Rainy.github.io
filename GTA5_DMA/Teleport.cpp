// Teleport.cpp
#include "pch.h"
#include "Teleport.h"
#include "Offsets.h"

// —— 启动传送 ——
// 从 Preparing 转到 InProgress
void Teleport::StartTeleport()
{
    if (!UpdatePlayerStartingLocation())
    {
        puts("Teleport: 无法读取起始位置，取消传送。");
        State = TeleportState::Idle;
        bRequestedTeleport = false;
        return;
    }

    ScatterHandle = VMMDLL_Scatter_Initialize(DMA::vmh, DMA::PID, VMMDLL_FLAG_NOCACHE);
    PreparePlayerWrites(ScatterHandle);
    PrepareVehicleWrites(ScatterHandle);

    Attempts = 0;
    State = TeleportState::InProgress;
    bRequestedTeleport = false;
}

// —— 分帧执行写入 ——
// 在 InProgress 状态下，每帧调用一次
void Teleport::StepTeleport()
{
    if (!ScatterHandle)
    {
        State = TeleportState::Idle;
        return;
    }

    VMMDLL_Scatter_Execute(ScatterHandle);
    ++Attempts;

    if (DMA::UpdatePlayerCurrentLocation())
    {
        float distToDest = DMA::LocalPlayerLocation.Distance(DesiredLocation);
        float distFromStart = DMA::LocalPlayerLocation.Distance(StartingLocation);

        if (distToDest < 1.0f && distFromStart > 100.0f)
        {
            puts("Teleport: 成功传送。");
            VMMDLL_Scatter_CloseHandle(ScatterHandle);
            ScatterHandle = nullptr;
            State = TeleportState::Idle;
            return;
        }
    }

    if (Attempts >= 200)
    {
        puts("Teleport: 传送失败，超出尝试次数。");
        VMMDLL_Scatter_CloseHandle(ScatterHandle);
        ScatterHandle = nullptr;
        State = TeleportState::Idle;
    }
}

// —— DMA 帧回调 ——
// 驱动整个状态机，无阻塞
bool Teleport::OnDMAFrame()
{
    if (!bEnable)
        return true;

    // —— 快捷键 F4 触发传送到导航点 —— 
    // 使用边缘检测，防止一按就触发多次
    static bool f4PrevDown = false;
    bool f4Down = (GetAsyncKeyState(VK_F4) & 0x8000) != 0;
    if (f4Down && !f4PrevDown)
    {
        Vec3 wp = GetWaypointCoords();
        if (wp.x != 0.0f || wp.y != 0.0f || wp.z != 0.0f)
        {
            DesiredLocation = wp;
            bRequestedTeleport = true;
        }
    }
    f4PrevDown = f4Down;

    // —— 自动传送逻辑 —— 
    if (State == TeleportState::Idle && bAutoTeleport)
    {
        Vec3 wp = GetWaypointCoords();
        if (wp.x != 0.0f || wp.y != 0.0f || wp.z != 0.0f)
        {
            DesiredLocation = wp;
            bRequestedTeleport = true;
        }
    }

    // —— 状态机推进 —— 
    if ((State == TeleportState::Idle || State == TeleportState::Preparing) && bRequestedTeleport)
    {
        State = TeleportState::Preparing;
        StartTeleport();
    }
    else if (State == TeleportState::InProgress)
    {
        StepTeleport();
    }

    return true;
}

// —— ImGui 渲染 ——
bool Teleport::Render()
{
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::Begin("传送功能");

    ImGui::Text("%.2f, %.2f, %.2f",
        DMA::LocalPlayerLocation.x,
        DMA::LocalPlayerLocation.y,
        DMA::LocalPlayerLocation.z);

    ImGui::InputFloat("X坐标", &DesiredLocation.x);
    ImGui::InputFloat("Y坐标", &DesiredLocation.y);
    ImGui::InputFloat("Z坐标", &DesiredLocation.z);

    if (ImGui::Button("传送到导航点"))
    {
        Vec3 wp = GetWaypointCoords();
        if (wp.x != 0.0f || wp.y != 0.0f || wp.z != 0.0f)
        {
            DesiredLocation = wp;
            bRequestedTeleport = true;
        }
    }

    ImGui::End();
    ImGui::PopFont();
    return true;
}

// —— 辅助函数 ——
// 保留原有逻辑，仅修正签名和内存清零

bool Teleport::UpdatePlayerStartingLocation()
{
    puts(__FUNCTION__);

    uintptr_t addr = DMA::NavigationAddress + offsetof(CNavigation, Position);
    DWORD read = 0;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID,
        addr,
        reinterpret_cast<BYTE*>(&StartingLocation),
        sizeof(Vec3),
        &read,
        VMMDLL_FLAG_NOCACHE);

    if (read != sizeof(Vec3))
    {
        memset(&StartingLocation, 0, sizeof(Vec3));
        return false;
    }
    return true;
}

// 签名已匹配 Teleport.h
void Teleport::OverwriteLocation(const Vec3& dest)
{
    UpdatePlayerStartingLocation();

    BYTE bits = 0;
    uintptr_t vb = DMA::LocalPlayerAddress + offsetof(PED, InVehicleBits);
    VMMDLL_MemRead(DMA::vmh, DMA::PID, vb, &bits, sizeof(bits));

    VMMDLL_SCATTER_HANDLE vmsh =
        VMMDLL_Scatter_Initialize(DMA::vmh, DMA::PID, VMMDLL_FLAG_NOCACHE);

    // 抛弃 const，将 dest 转为可写指针
    BYTE* pData = reinterpret_cast<BYTE*>(const_cast<Vec3*>(&dest));

    VMMDLL_Scatter_PrepareWrite(vmsh,
        DMA::NavigationAddress + offsetof(CNavigation, Position),
        pData,
        sizeof(Vec3));

    if (bits & 0x1)
    {
        VMMDLL_Scatter_PrepareWrite(vmsh,
            DMA::VehicleNavigationAddress + offsetof(CNavigation, Position),
            pData,
            sizeof(Vec3));
    }

    VMMDLL_Scatter_Execute(vmsh);
    VMMDLL_Scatter_CloseHandle(vmsh);
}

void Teleport::PreparePlayerWrites(VMMDLL_SCATTER_HANDLE vmsh)
{
    VMMDLL_Scatter_PrepareWrite(vmsh,
        DMA::NavigationAddress + offsetof(CNavigation, Position),
        reinterpret_cast<BYTE*>(&DesiredLocation),
        sizeof(Vec3));
}

void Teleport::PrepareVehicleWrites(VMMDLL_SCATTER_HANDLE vmsh)
{
    VMMDLL_Scatter_PrepareWrite(vmsh,
        DMA::VehicleNavigationAddress + offsetof(CNavigation, Position),
        reinterpret_cast<BYTE*>(&DesiredLocation),
        sizeof(Vec3));
}

#define BLIP_NUM 1000

Vec3 Teleport::GetWaypointCoords()
{
    std::println("正在获取导航点坐标...");

    Vec3 WaypointCoordinates{ 0.0f, 0.0f, 0.0f };
    uintptr_t base = DMA::BaseAddress + Offsets::BlipPtr;
    uintptr_t BlipAddresses[BLIP_NUM]{};
    DWORD read = 0;

    VMMDLL_MemReadEx(DMA::vmh, DMA::PID,
        base,
        reinterpret_cast<BYTE*>(&BlipAddresses),
        sizeof(BlipAddresses),
        &read,
        VMMDLL_FLAG_NOCACHE);

    if (read != sizeof(BlipAddresses))
    {
        puts("读取 Blip 列表失败.");
        return WaypointCoordinates;
    }

    auto pBlips = std::make_unique<Blip[]>(BLIP_NUM);
    memset(pBlips.get(), 0, sizeof(Blip) * BLIP_NUM);

    VMMDLL_SCATTER_HANDLE vmsh =
        VMMDLL_Scatter_Initialize(DMA::vmh, DMA::PID, VMMDLL_FLAG_NOCACHE);

    for (int i = 0; i < BLIP_NUM; ++i)
    {
        if (!BlipAddresses[i]) continue;
        VMMDLL_Scatter_PrepareEx(vmsh,
            BlipAddresses[i],
            sizeof(Blip),
            reinterpret_cast<BYTE*>(&pBlips[i]),
            &read);
    }
    VMMDLL_Scatter_Execute(vmsh);
    VMMDLL_Scatter_CloseHandle(vmsh);

    for (int i = 0; i < BLIP_NUM; ++i)
    {
        if (pBlips[i].ID == 8)
        {
            WaypointCoordinates = pBlips[i].Position;
            if (WaypointCoordinates.z == 20.0f)
                WaypointCoordinates.z = -255.0f;
            else
                WaypointCoordinates.z += 2.0f;
            break;
        }
    }

    return WaypointCoordinates;
}