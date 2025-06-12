#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "pch.h"
#include "MyMenu.h"
#include "Features.h"
#include "GodMode.h"
#include "WeaponInspector.h"
#include "Dev.h"



// 初始化ImGui中文字体
void InitializeImGui()
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 16.0f, nullptr,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
}

bool MyMenu::Render()
{
    static bool firstRunInit = true;
    if (firstRunInit)
    {
        WeaponInspector::bNoReload = true;         // 启动时默认开启“无限弹药”
        GodMode::bPlayerGodMode = true;            // 启动时默认开启“玩家无敌”
        firstRunInit = false;
    }
    ImGui::Begin("Grand Theft Auto V Enhanced", nullptr, ImGuiWindowFlags_NoCollapse);

    // ==================== 功能设置 ====================

    ImGui::BeginTable("FeatureSettings", 2, ImGuiTableFlags_SizingFixedFit);
    {

        ImGui::TableNextColumn();
        ImGui::Checkbox("武器功能", &WeaponInspector::bEnable);

        ImGui::TableNextColumn();
        static bool firstRun = true;
        if (firstRun) {
            Teleport::bEnable = true;
            firstRun = false;
        }
        ImGui::Checkbox("传送功能", &Teleport::bEnable);
        
        
        ImGui::TableNextColumn();
        ImGui::Checkbox("无限弹药", &WeaponInspector::bNoReload);
        ImGui::TableNextColumn();
        ImGui::Checkbox("子弹扩散", &WeaponInspector::bNoSpread);
        ImGui::TableNextColumn();
        ImGui::Checkbox("无后坐力", &WeaponInspector::bNoRecoil);
        ImGui::TableNextColumn();
        ImGui::Checkbox("玩家无敌", &GodMode::bPlayerGodMode);
        ImGui::TableNextColumn();
        ImGui::Checkbox("载具无敌", &GodMode::bVehicleGodMode);
        ImGui::TableNextColumn();
        ImGui::Checkbox("永不通鸡", &NoWanted::bEnable);
        ImGui::TableNextColumn();
        ImGui::Checkbox("自动传送", &Teleport::bAutoTeleport);


    }
    ImGui::EndTable();

    ImGui::End();
    return true;
}