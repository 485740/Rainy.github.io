#pragma once
#include <cstdint>
// Created with ReClass.NET 1.2 by KN4CK3R

class World
{
public:
	char pad_0000[8]; //0x0000 // ����ֽڣ�ͨ�����ڶ�������ռ䣩
	class PED* pPlayer; //0x0008 // ָ����ҽ�ɫ��ָ��
}; //Size: 0x0010
static_assert(sizeof(World) == 0x10);

class PED
{
public:
	char pad_0000[44]; //0x0000 // ����ֽ�
	int8_t InvisibilityFlag; //0x002C // ����״̬��־��0=�ɼ�����0=����
	char pad_002D[3]; //0x002D // ����ֽ�
	class CNavigation* pCNavigation; //0x0030 // �������ָ�루����λ��/�������ݣ�
	char pad_0038[336]; //0x0038 // ����ֽ�
	uint32_t GodFlags; //0x0188 // �޵�ģʽ��־λ��λ������Ʋ�ͬ�˺����ߣ�
	char pad_018C[244]; //0x018C // ����ֽ�
	float CurrentHealth; //0x0280 // ��ǰ����ֵ
	float MaxHealth; //0x0284 // �������ֵ����
	char pad_0288[2696]; //0x0288 // ����ֽ�
	class CVehicle* pCVehicle; //0x0D10 // ��ǰ�ؾ߶���ָ�루�����ؾ�ʱΪnull��
	char pad_0D18[282]; //0x0D18 // ����ֽ�
	uint8_t InVehicleBits; //0x0E32 // �ؾ�״̬���λ���Ƿ����ؾ���/�˿�/��ʻλ�ȣ�
	char pad_0E33[629]; //0x0E33 // ����ֽ�
	class PlayerInfo* pPlayerInfo; //0x10A8 // �������ָ�루�ٶ�/ͨ���ȼ��ȣ�
	class WeaponInventory* pCWeaponInventory; //0x10B0 // �������ָ�루��ҩ���ݣ�
	class CPEdWeaponManager* pCPedWeaponManager; //0x10B8 // ����������ָ�루��ǰ������Ϣ��
	char pad_10C0[72]; //0x10C0 // ����ֽ�
	class PED* pSelf2; //0x1108 // �������ָ�루����ָ�룩
	char pad_1110[16]; //0x1110 // ����ֽ�
	class PED* pSelf; //0x1120 // �������ָ��
	char pad_1128[2048]; //0x1128 // ����ֽ�
}; //Size: 0x1928
static_assert(sizeof(PED) == 0x1928);

class PlayerInfo
{
public:
	char pad_0000[184]; //0x0000 // ����ֽ�
	int32_t N00000406; //0x00B8 // δ֪�����ֶ�
	int32_t N00000409; //0x00BC // δ֪�����ֶ�
	char pad_00C0[292]; //0x00C0 // ����ֽ�
	float WalkSpeed; //0x01E4 // �����ٶȱ������޸Ŀɸı��ƶ��ٶȣ�
	char pad_01E8[1792]; //0x01E8 // ����ֽ�
	int32_t WantedLevel; //0x08E8 // ͨ���ȼ���0-5�ǣ�
	char pad_08EC[1124]; //0x08EC // ����ֽ�
	float RunSpeed; //0x0D50 // �����ٶȱ���
	char pad_0D54[916]; //0x0D54 // ����ֽ�
}; //Size: 0x10E8
static_assert(sizeof(PlayerInfo) == 0x10E8);

class WeaponInventory
{
public:
	char pad_0000[120];     // 0x0000 // ����ֽ�
	uint8_t AmmoModifier;   // 0x0078 // ��ҩ�����޸�����Ӱ�쵯ҩ��ȡ����
	char pad_0079[3];       // 0x0079 // ����ֽ�
	int32_t AmmoInClip;     // 0x007C // ��ǰ�����ڵ�ҩ����
	int32_t AmmoInReserve;  // 0x0080 // �󱸵�ҩ����
}; //Size: 0x0084
static_assert(sizeof(WeaponInventory) == 0x84);

class CPEdWeaponManager
{
public:
	char pad_0000[32]; //0x0000 // ����ֽ�
	class WeaponInfo* pCWeaponInfo; //0x0020 // ��ǰ�ֳ���������ָ��
}; //Size: 0x0028
static_assert(sizeof(CPEdWeaponManager) == 0x28);

class WeaponInfo
{
public:
	char pad_0000[16]; //0x0000 // ����ֽ�
	uint32_t m_name; //0x0010 // �������ƹ�ϣֵ
	uint32_t m_model; //0x0014 // ����ģ�͹�ϣֵ
	uint32_t m_audio; //0x0018 // ������Ч��ϣֵ
	uint32_t m_slot; //0x001C // ������λ���
	int32_t ImpactType; //0x0020 // ����Ч������
	int32_t ImpactExplosion; //0x0024 // ���б�ըЧ����ʶ
	char pad_0028[72]; //0x0028 // ����ֽ�
	uint32_t clip_size; //0x0070 // ��������������ֵ��
	float Spread;         // 0x0074 �ӵ���ɢ
	char pad_0078[56];
	float WeaponDamage; //0x00B0 // �����˺�ֵ
	char pad_00B4[92]; //0x00B4 // ����ֽ�
	float WeaponPenetration; //0x0110 // ��͸������ǽ/�ؾ�������
	char pad_0114[32]; //0x0114 // ����ֽ�
	float ReloadMultiplier; //0x0134 // �����ٶȱ��ʣ�1.0=������
	char pad_0138[4]; //0x0138 // ����ֽ�
	float WeaponFireRate; //0x013C // ���٣�ÿ�뷢������
	char pad_0140[272]; //0x0140 // ����ֽ�
	int32_t N000007DD; //0x0250 // δ֪�����ֶ�
	char pad_0254[8]; //0x0254 // ����ֽ�
	int32_t N0000082F; //0x025C // δ֪�����ֶ�
	char pad_0260[20]; //0x0260 // ����ֽ�
	int32_t N00000835; //0x0274 // δ֪�����ֶ�
	char pad_0278[16]; //0x0278 // ����ֽ�
	float N000007E4; //0x0288 // δ֪�����ֶ�
	float WeaponRange; //0x028C // ������Ч��̣��ף�
	char pad_0290[8]; //0x0290 // ����ֽ�
	float N000007E6; //0x0298 // δ֪�����ֶ�
	float N0000083F; //0x029C // δ֪�����ֶ�
	char pad_02A0[84]; //0x02A0 // ����ֽ�
	float RecoilAmplitude; //0x02F4 // ������ǿ�ȣ���ֵԽ�����Խ��
}; //Size: 0x02F8
static_assert(sizeof(WeaponInfo) == 0x2F8);

class CNavigation
{
public:
	char pad_0000[80]; //0x0000 // ����ֽ�
	Vec3 Position; //0x0050 // ʵ������λ�ã�x,y,z��
	char pad_005C[44]; //0x005C // ����ֽ�
	float CameraZ; //0x0088 // �����Z����ת�ǣ����ȣ�
	char pad_008C[4]; //0x008C // ����ֽ�
	float CameraX; //0x0090 // �����X����ת�ǣ����ȣ�
	float CameraY; //0x0094 // �����Y����ת�ǣ����ȣ�
}; //Size: 0x0098
static_assert(sizeof(CNavigation) == 0x98);

class BlipArray
{
public:
	class Blip* pBlips[2000]; //0x0000 // С��ͼ���ָ������
}; //Size: 0x3E80
static_assert(sizeof(BlipArray) == 0x3E80);

class Blip
{
public:
	char pad_0000[16]; //0x0000 // ����ֽ�
	Vec3 Position; //0x0010 // ��ǵ���������
	char pad_001C[36]; //0x001C // ����ֽ�
	int32_t ID; //0x0040 // ��ǵ�����ID������/�����ȣ�
}; //Size: 0x0044
static_assert(sizeof(Blip) == 0x44);

class N0000078D
{
public:
	class N000007DA* N0000078E; //0x0000 // δ֪Ƕ�׶���ָ��
	char pad_0008[120]; //0x0008 // ����ֽ�
}; //Size: 0x0080
static_assert(sizeof(N0000078D) == 0x80);

class N000007DA
{
public:
	char pad_0000[2192]; //0x0000 // ����ֽ�
}; //Size: 0x0890
static_assert(sizeof(N000007DA) == 0x890);

class CVehicle
{
public:
	char pad_0000[32]; //0x0000 // ����ֽ�
	class CModelInfo* pCModelInfo; //0x0020 // �ؾ�ģ����Ϣָ��
	char pad_0028[8]; //0x0028 // ����ֽ�
	class CNavigation* pCNavigation; //0x0030 // �������ָ�루λ��/����
	char pad_0038[336]; //0x0038 // ����ֽ�
	uint32_t GodBits; //0x0188 // �ؾ��޵б��λ������ը/��ײ�ȣ�
	char pad_018C[244]; //0x018C // ����ֽ�
	float Health; //0x0280 // �ؾߵ�ǰ�;öȣ�0=���٣�
	char pad_0284[1756]; //0x0284 // ����ֽ�
	class CHandlingData* pCHandlingData; //0x0960 // �ؾ�����ٿ�����ָ��
	char pad_0968[800]; //0x0968 // ����ֽ�
}; //Size: 0x0C88
static_assert(sizeof(CVehicle) == 0xC88);

class CHandlingData
{
public:
	char pad_0000[12]; //0x0000 // ����ֽ�
	float Mass; //0x000C // �ؾ�������kg��
	char pad_0010[60]; //0x0010 // ����ֽ�
	float Acceleration; //0x004C // ������ٶȣ�Ӱ������������
	char pad_0050[744]; //0x0050 // ����ֽ�
	float Thrust; //0x0338 // ��������������/��ֻ�ƽ�ǿ�ȣ�
	char pad_033C[1356]; //0x033C // ����ֽ�
}; //Size: 0x0888
static_assert(sizeof(CHandlingData) == 0x888);

class CModelInfo
{
public:
	char pad_0000[392]; //0x0000 // ����ֽ�
}; //Size: 0x0188
static_assert(sizeof(CModelInfo) == 0x188);