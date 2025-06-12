#include "pch.h"
#include "Dev.h"

bool Dev::Render()
{
    ImGui::Begin("开发者调试");  // 更符合功能定位的窗口标题

    // 全局变量索引输入（添加单位说明）
    ImGui::InputInt("全局变量索引", &Dev::DesiredGlobalIndex);

    // 获取浮点数值按钮（添加操作提示）
    if (ImGui::Button("读取浮点数值"))
    {
        float Output = 0.0f;
        DMA::GetGlobalValue<float>(static_cast<DWORD>(DesiredGlobalIndex), Output);
        std::println("全局变量({0:d}) = {1:f}", DesiredGlobalIndex, Output);
    }

    // 获取DWORD值按钮（保持专业术语）
    if (ImGui::Button("读取整型数值"))
    {
        DWORD Output = 0;
        DMA::GetGlobalValue<DWORD>(static_cast<DWORD>(DesiredGlobalIndex), Output);
        std::println("全局变量({0:d}) = {1:d}", DesiredGlobalIndex, Output);
    }

    ImGui::End();

    return true;
}