#pragma once
#include <cstdint>

namespace Offsets
{
    // ����ָ��ƫ��
    static const uintptr_t WorldPtr = 0x43C03F8;         // ���������ָ��
    static const uintptr_t GlobalPtr = 0x3FB2EF8;        // ȫ��ָ��
    static const uintptr_t BlipPtr = 0x3E63AF0;          // С��ͼ���ָ��

    // �����ʵ�����
    static const uintptr_t ReplayInterface = 0x1F58B58;  // ʵ�������ƫ�� (ʾ��ֵ������֤)
    static const uintptr_t ViewMatrixPtr = 0x20019E0;    // ��ͼ����ָ��ƫ��

    // PED�ṹ�ڲ�ƫ��
    namespace Ped {
        static const uintptr_t InvisibilityFlag = 0x002C;  // �����־
        static const uintptr_t CNavigationPtr = 0x0030;    // �������ָ��
        static const uintptr_t GodFlags = 0x0188;          // �޵б��
        static const uintptr_t CurrentHealth = 0x0280;     // ��ǰ����ֵ
        static const uintptr_t MaxHealth = 0x0284;         // �������ֵ
        static const uintptr_t CVehiclePtr = 0x0D10;       // �ؾ�ָ��
        static const uintptr_t InVehicleBits = 0x0E32;     // �ؾ�״̬λ
        static const uintptr_t PlayerInfoPtr = 0x10A8;     // �����Ϣָ��
        static const uintptr_t WeaponInventoryPtr = 0x10B0; // �������ָ��
        static const uintptr_t WeaponManagerPtr = 0x10B8;  // ����������ָ��
    }

    // CNavigation�ṹ�ڲ�ƫ��
    namespace Navigation {
        static const uintptr_t Position = 0x0050;         // λ������
        static const uintptr_t CameraZ = 0x0088;          // �����Z����ת
        static const uintptr_t CameraX = 0x0090;          // �����X����ת
        static const uintptr_t CameraY = 0x0094;          // �����Y����ת
    }

    // ����ϵͳ�ؼ�ƫ��
    namespace Bones {
        static const uintptr_t MatrixPtr = 0x60;          // �����任����ָ�� (PED��ƫ��)
        static const uintptr_t ArrayBase = 0x410;         // ���������ַ (PED��ƫ��)
        static const uintptr_t BoneSize = 0x10;           // �����������ݴ�С
    }

    // ��ͼ����ƫ��
    namespace ViewMatrix {
        static const uintptr_t CameraStruct = 0x24C;      // ��ͼ����������ṹ�е�ƫ��
    }

    // ʵ���б����
    namespace EntityList {
        static const uintptr_t PedInterface = 0x18;       // ʵ��ӿ�ƫ�� (ReplayInterface��)
        static const uintptr_t PedListBase = 0x100;       // ʵ���б��ַ (PedInterface��)
    }

    // �����Ϣ�ṹ
    namespace PlayerInfo {
        static const uintptr_t WalkSpeed = 0x01E4;        // �����ٶ�
        static const uintptr_t WantedLevel = 0x08E8;      // ͨ���ȼ�
        static const uintptr_t RunSpeed = 0x0D50;         // �����ٶ�
    }

    // ����ϵͳ
    namespace Weapon {
        static const uintptr_t AmmoModifier = 0x0078;          // ��ҩ���� (WeaponInventory��)
        static const uintptr_t AmmoInClip = 0x007C;            // ���е�ҩ (WeaponInventory��)
        static const uintptr_t AmmoInReserve = 0x0080;         // �󱸵�ҩ (WeaponInventory��)
        static const uintptr_t WeaponInfoPtr = 0x0020;         // ������Ϣָ�� (WeaponManager��)
        static const uintptr_t WeaponDamage = 0x00B0;          // �����˺� (WeaponInfo��)
        static const uintptr_t WeaponFireRate = 0x013C;        // ���� (WeaponInfo��)
        static const uintptr_t WeaponRange = 0x028C;           // ��� (WeaponInfo��)
        static const uintptr_t RecoilAmplitude = 0x02F4;       // ������ (WeaponInfo��)
    }

    // �ؾ�ϵͳ
    namespace Vehicle {
        static const uintptr_t ModelInfoPtr = 0x0020;          // ģ����Ϣָ�� (CVehicle��)
        static const uintptr_t GodBits = 0x0188;               // �޵б�� (CVehicle��)
        static const uintptr_t Health = 0x0280;                // �;ö� (CVehicle��)
        static const uintptr_t HandlingDataPtr = 0x0960;       // ��������ָ�� (CVehicle��)

        // �������ݴ���
        namespace Handling {
            static const uintptr_t Mass = 0x000C;              // ����
            static const uintptr_t Acceleration = 0x004C;      // ���ٶ�
            static const uintptr_t Thrust = 0x0338;            // ����
        }
    }
}