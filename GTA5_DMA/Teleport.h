#pragma once

#include "Offsets.h"    // ȷ�� Vec3��VMMDLL_SCATTER_HANDLE��CNavigation��PED �������Ѷ���
#include <cstdint>

// ����ģ��״̬
enum class TeleportState : uint8_t
{
    Idle,
    Preparing,
    InProgress
};

class Teleport
{
public:
    // ImGui ������Ⱦ��ÿ֡�����̵߳���
    static bool Render();

    // DMA �߳�ÿ֡�ص���ÿ֡�� DMA ����
    static bool OnDMAFrame();

    // �����أ�����/�ر��������͹���
    static inline bool bEnable = false;
    // ���δ��������־
    static inline bool bRequestedTeleport = false;
    // �Զ����͵������㿪��
    static inline bool bAutoTeleport = false;

private:
    // �������ʼλ�ã������жϴ��ͳɹ���
    static inline Vec3 StartingLocation = { 0.0f, 0.0f, 0.0f };
    // ����Ҫ���͵���Ŀ��λ��
    static inline Vec3 DesiredLocation = { 0.0f, 0.0f, 0.0f };

    // ����״̬��
    static inline TeleportState State = TeleportState::Idle;
    // �ѳ���д�����
    static inline int Attempts = 0;
    // VMMDLL ɢ��д���
    static inline VMMDLL_SCATTER_HANDLE ScatterHandle = nullptr;

    //
    // ���� �������̺��� ���� 
    //

    // �� Idle/Preparing ״̬�������ͣ�׼��ɢ��д��
    static void StartTeleport();
    // �� InProgress ״̬�£�ÿ֡�ƽ�һ��ɢ��д
    static void StepTeleport();

    //
    // ���� ԭ�и������� ���� 
    //

    // ��ȡ��������ҵ�ǰ���굽 StartingLocation
    static bool UpdatePlayerStartingLocation();
    // ������һ������д�루�������ã�
    static void OverwriteLocation(const Vec3& dest);
    // ׼���������д��
    static void PreparePlayerWrites(VMMDLL_SCATTER_HANDLE vmsh);
    // ׼���ؾ�����д�루������ؾ��У�
    static void PrepareVehicleWrites(VMMDLL_SCATTER_HANDLE vmsh);
    // ��ȡ�����ص�ǰ���������꣨�޵㷵�� 0,0,0��
    static Vec3 GetWaypointCoords();

};