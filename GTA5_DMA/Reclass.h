#pragma once
#include <cstdint>
// Created with ReClass.NET 1.2 by KN4CK3R

class World
{
public:
	char pad_0000[8]; //0x0000 // 填充字节（通常用于对齐或保留空间）
	class PED* pPlayer; //0x0008 // 指向玩家角色的指针
}; //Size: 0x0010
static_assert(sizeof(World) == 0x10);

class PED
{
public:
	char pad_0000[44]; //0x0000 // 填充字节
	int8_t InvisibilityFlag; //0x002C // 隐身状态标志（0=可见，非0=隐身）
	char pad_002D[3]; //0x002D // 填充字节
	class CNavigation* pCNavigation; //0x0030 // 导航组件指针（包含位置/方向数据）
	char pad_0038[336]; //0x0038 // 填充字节
	uint32_t GodFlags; //0x0188 // 无敌模式标志位（位掩码控制不同伤害免疫）
	char pad_018C[244]; //0x018C // 填充字节
	float CurrentHealth; //0x0280 // 当前生命值
	float MaxHealth; //0x0284 // 最大生命值上限
	char pad_0288[2696]; //0x0288 // 填充字节
	class CVehicle* pCVehicle; //0x0D10 // 当前载具对象指针（不在载具时为null）
	char pad_0D18[282]; //0x0D18 // 填充字节
	uint8_t InVehicleBits; //0x0E32 // 载具状态标记位（是否在载具中/乘客/驾驶位等）
	char pad_0E33[629]; //0x0E33 // 填充字节
	class PlayerInfo* pPlayerInfo; //0x10A8 // 玩家数据指针（速度/通缉等级等）
	class WeaponInventory* pCWeaponInventory; //0x10B0 // 武器库存指针（弹药数据）
	class CPEdWeaponManager* pCPedWeaponManager; //0x10B8 // 武器管理器指针（当前武器信息）
	char pad_10C0[72]; //0x10C0 // 填充字节
	class PED* pSelf2; //0x1108 // 自身对象指针（备份指针）
	char pad_1110[16]; //0x1110 // 填充字节
	class PED* pSelf; //0x1120 // 自身对象指针
	char pad_1128[2048]; //0x1128 // 填充字节
}; //Size: 0x1928
static_assert(sizeof(PED) == 0x1928);

class PlayerInfo
{
public:
	char pad_0000[184]; //0x0000 // 填充字节
	int32_t N00000406; //0x00B8 // 未知功能字段
	int32_t N00000409; //0x00BC // 未知功能字段
	char pad_00C0[292]; //0x00C0 // 填充字节
	float WalkSpeed; //0x01E4 // 行走速度倍数（修改可改变移动速度）
	char pad_01E8[1792]; //0x01E8 // 填充字节
	int32_t WantedLevel; //0x08E8 // 通缉等级（0-5星）
	char pad_08EC[1124]; //0x08EC // 填充字节
	float RunSpeed; //0x0D50 // 奔跑速度倍数
	char pad_0D54[916]; //0x0D54 // 填充字节
}; //Size: 0x10E8
static_assert(sizeof(PlayerInfo) == 0x10E8);

class WeaponInventory
{
public:
	char pad_0000[120];     // 0x0000 // 填充字节
	uint8_t AmmoModifier;   // 0x0078 // 弹药倍率修改器（影响弹药获取量）
	char pad_0079[3];       // 0x0079 // 填充字节
	int32_t AmmoInClip;     // 0x007C // 当前弹夹内弹药数量
	int32_t AmmoInReserve;  // 0x0080 // 后备弹药总量
}; //Size: 0x0084
static_assert(sizeof(WeaponInventory) == 0x84);

class CPEdWeaponManager
{
public:
	char pad_0000[32]; //0x0000 // 填充字节
	class WeaponInfo* pCWeaponInfo; //0x0020 // 当前手持武器数据指针
}; //Size: 0x0028
static_assert(sizeof(CPEdWeaponManager) == 0x28);

class WeaponInfo
{
public:
	char pad_0000[16]; //0x0000 // 填充字节
	uint32_t m_name; //0x0010 // 武器名称哈希值
	uint32_t m_model; //0x0014 // 武器模型哈希值
	uint32_t m_audio; //0x0018 // 武器音效哈希值
	uint32_t m_slot; //0x001C // 武器槽位编号
	int32_t ImpactType; //0x0020 // 命中效果类型
	int32_t ImpactExplosion; //0x0024 // 命中爆炸效果标识
	char pad_0028[72]; //0x0028 // 填充字节
	uint32_t clip_size; //0x0070 // 弹夹容量（基础值）
	float Spread;         // 0x0074 子弹扩散
	char pad_0078[56];
	float WeaponDamage; //0x00B0 // 武器伤害值
	char pad_00B4[92]; //0x00B4 // 填充字节
	float WeaponPenetration; //0x0110 // 穿透力（穿墙/载具能力）
	char pad_0114[32]; //0x0114 // 填充字节
	float ReloadMultiplier; //0x0134 // 换弹速度倍率（1.0=正常）
	char pad_0138[4]; //0x0138 // 填充字节
	float WeaponFireRate; //0x013C // 射速（每秒发射数）
	char pad_0140[272]; //0x0140 // 填充字节
	int32_t N000007DD; //0x0250 // 未知功能字段
	char pad_0254[8]; //0x0254 // 填充字节
	int32_t N0000082F; //0x025C // 未知功能字段
	char pad_0260[20]; //0x0260 // 填充字节
	int32_t N00000835; //0x0274 // 未知功能字段
	char pad_0278[16]; //0x0278 // 填充字节
	float N000007E4; //0x0288 // 未知浮点字段
	float WeaponRange; //0x028C // 武器有效射程（米）
	char pad_0290[8]; //0x0290 // 填充字节
	float N000007E6; //0x0298 // 未知浮点字段
	float N0000083F; //0x029C // 未知浮点字段
	char pad_02A0[84]; //0x02A0 // 填充字节
	float RecoilAmplitude; //0x02F4 // 后坐力强度（数值越大后坐越大）
}; //Size: 0x02F8
static_assert(sizeof(WeaponInfo) == 0x2F8);

class CNavigation
{
public:
	char pad_0000[80]; //0x0000 // 填充字节
	Vec3 Position; //0x0050 // 实体坐标位置（x,y,z）
	char pad_005C[44]; //0x005C // 填充字节
	float CameraZ; //0x0088 // 摄像机Z轴旋转角（弧度）
	char pad_008C[4]; //0x008C // 填充字节
	float CameraX; //0x0090 // 摄像机X轴旋转角（弧度）
	float CameraY; //0x0094 // 摄像机Y轴旋转角（弧度）
}; //Size: 0x0098
static_assert(sizeof(CNavigation) == 0x98);

class BlipArray
{
public:
	class Blip* pBlips[2000]; //0x0000 // 小地图标记指针数组
}; //Size: 0x3E80
static_assert(sizeof(BlipArray) == 0x3E80);

class Blip
{
public:
	char pad_0000[16]; //0x0000 // 填充字节
	Vec3 Position; //0x0010 // 标记点世界坐标
	char pad_001C[36]; //0x001C // 填充字节
	int32_t ID; //0x0040 // 标记点类型ID（警车/任务点等）
}; //Size: 0x0044
static_assert(sizeof(Blip) == 0x44);

class N0000078D
{
public:
	class N000007DA* N0000078E; //0x0000 // 未知嵌套对象指针
	char pad_0008[120]; //0x0008 // 填充字节
}; //Size: 0x0080
static_assert(sizeof(N0000078D) == 0x80);

class N000007DA
{
public:
	char pad_0000[2192]; //0x0000 // 填充字节
}; //Size: 0x0890
static_assert(sizeof(N000007DA) == 0x890);

class CVehicle
{
public:
	char pad_0000[32]; //0x0000 // 填充字节
	class CModelInfo* pCModelInfo; //0x0020 // 载具模型信息指针
	char pad_0028[8]; //0x0028 // 填充字节
	class CNavigation* pCNavigation; //0x0030 // 导航组件指针（位置/方向）
	char pad_0038[336]; //0x0038 // 填充字节
	uint32_t GodBits; //0x0188 // 载具无敌标记位（防爆炸/碰撞等）
	char pad_018C[244]; //0x018C // 填充字节
	float Health; //0x0280 // 载具当前耐久度（0=销毁）
	char pad_0284[1756]; //0x0284 // 填充字节
	class CHandlingData* pCHandlingData; //0x0960 // 载具物理操控数据指针
	char pad_0968[800]; //0x0968 // 填充字节
}; //Size: 0x0C88
static_assert(sizeof(CVehicle) == 0xC88);

class CHandlingData
{
public:
	char pad_0000[12]; //0x0000 // 填充字节
	float Mass; //0x000C // 载具质量（kg）
	char pad_0010[60]; //0x0010 // 填充字节
	float Acceleration; //0x004C // 引擎加速度（影响提速能力）
	char pad_0050[744]; //0x0050 // 填充字节
	float Thrust; //0x0338 // 特殊推力（飞行/船只推进强度）
	char pad_033C[1356]; //0x033C // 填充字节
}; //Size: 0x0888
static_assert(sizeof(CHandlingData) == 0x888);

class CModelInfo
{
public:
	char pad_0000[392]; //0x0000 // 填充字节
}; //Size: 0x0188
static_assert(sizeof(CModelInfo) == 0x188);