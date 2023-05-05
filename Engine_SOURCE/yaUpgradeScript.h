#pragma once
#include "yaScript.h"
#include <array>
namespace ya
{
	class PlayScene;
	class UpgradeScript :public Script
	{
	public:
		UpgradeScript();
		~UpgradeScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//빠른 탄환
		void TakeAim(); //T1 탄환속도 30% 산탄 범위 -15%
		void Penteration();//T2 //탄환 속도 15% 관통+1
		void Smiper(); //T2 //탄환속도 25% 총알 공격력 15%
		void Assassin(); //T3 //탄속 10% 체력 20%미만 적 자동사살

		//데미지 강화
		void PowerShot(); //T1 탄환 공격력 35%, 넉백 20%
		void Splinter(); //T2 적이 사망할때 총알 파편 3발흩뿌리기 기존 총알의(데미지 10%)
		void BigShot(); //T2 탄환 공격력 45%, 탄환 크기+40%,연사속도 -5%
		void ReaperRounds(); //T3 탄환 공격력15% 관통 +1 //적을 죽이면 관통+1

		// 빠른 사격
		void RapidFire(); //T1 연사속도 25%
		void LightBullets(); //T2 연사속도 15% 최대탄창 +1 탄속 15%
		void RubberBullets(); //T3 튕김+1,연사속도 +10% 탄환 데미지-10%
		void Siege(); //T3 정지상태 사격시 33%로 탄환소비X

		//멀티샷
		void DoubleShot(); //T1 발사수+1 산탄범위+15%, 탄환데미지-10%
		void FanFire(); //T2 마지막 탄환을 발사할때 15%의 피해를 주는 탄환 사방으로 10발 발사
		void SplitFire(); //T2 뒤쪽으로 한발의 탄을 추가 발사
		void Fusillade(); //T3 발사수 +1 산탄 범위 15%, 탄 데미지 -25% 기본 발사체를 두배를 두배로

		//장전 강화
		void QuickHands(); //T1 재장전 속도 +20, 연사 속도 5%
		void ArmedAndReady(); //T2 재장전속도 10%, 최대탄장 +2
		void FreshClip(); //T2 재장전 속도 5%, 재장전 후 1초동안 총알 피해량 50%
		void KillClip(); //T3 처치당 재장전 속도 5%증가 재장전 후 초기화
		
		//전기술사
		void ElectroMage(); //(T1) : 탄환을 2회 발사할 때마다 22의 피해를 주는 번개를 소환한다. 커서가 위치하는 적을 타격한다.
		void ElectroBug(); //(T2) : 매 초마다 근접한 두명의 적에게 번개를 떨어뜨리는 번개 벌레를 소환한다.
		void Energized(); //(T2) : 적에게 번개가 칠 때마다 20% 확률로 탄환을 3개 충전한다.
		void ElectroMastery(); //(T3) : 모든 번개 피해가 12 증가하고, 범위 효과가 75% 늘어난다.

		//얼음마법
		void FrostMage(); //(T1) : 탄환이 35% 확률로 3초간 적을 빙결시킨다. 보스는 0.3초간 빙결된다.
		void Frostbite(); //(T2) : 적이 빙결될 때마다 최대 체력의 15%만큼 피해를 입는다. 보스는 1%만큼 피해를 입는다.
		void IceShard(); //(T2) : 탄창의 마지막 탄을 발사했을 때 적을 얼리는 3개의 얼음 조각을 발사한다.
		void Shatter(); //(T3) : 빙결된 적이 죽으면 폭발하여 주변에 최대 체력의 10%에 해당하는 피해를 준다.

		//화염마법
		void PyroMage(); //(T1) : 탄환이 50% 확률로 발화 효과를 입혀, 초당 3의 피해를 준다.
		void FireStarter(); //(T2) : 탄환을 5회 발사할 때마다 화염구를 발사한다. 화염구는 40의 피해를 주고 적을 불태워 초당 3의 피해를 준다.
		void IntenseBurn(); //(T2) : 발화 피해량 +35%
		void SoothingWarmth(); //(T3) : 적에게 발화 효과를 입힐 때마다, 0.05% (2000 분의 1) 확률로 체력을 1 얻는다.

		//사술
		void DarkArts(); //(T1) : 탄환이 25% 확률로 저주 효과를 걸고, 탄환 데미지의 2배의 데미지를 입힙니다.
		void Doom(); //(T2) : 저주가 발동되기까지 시간을 1초 늘립니다. 대신 저주가 탄환 데미지의 100%를 추가로 입힙니다.
		void Wither(); //(T2) : 저주에 걸린적은 30% 추가 피해를 입습니다.
		void Ritual(); //(T3) : 저주로 죽인 적 10마리 마다 탄환 데미지를 1% 증가시킵니다.

		//성도
		void HolyAttack(); //(T1) : 마지막 탄을 발사했을 때, 근처의 적을 강타하여 20의 데미지를 줍니다.
		void HolyMight(); //(T2) : 강타가 현재 체력당 10의 추가데미지를 줍니다.
		void Justice(); //(T2) : 강타로 죽인 적 500마리마다 최대체력이 1 증가합니다. 이 방식으로 얻는 최대 체력은 최대 3입니다.
		void Angelic(); //(T3) : 강타로 죽인 적 500마리마다 체력 1을 회복합니다.

		//Aero Magic
		void AeroMagic(); //(T1) : 마지막 탄을 발사했을 때, 돌풍을 추가로 발사합니다. 돌풍은 0.5초마다 10의 데미지를 입힙니다.
		void WindBorne(); //(T2) : 이동속도 +15%, 이동속도 보너스만큼 돌풍의 데미지가 증가합니다.
		void EyeoftheStorm(); //(T2) : 근처의 적에게 돌풍의 2배의 데미지를 입힙니다. 돌풍의 데미지가 5증가합니다.
		void AeroMastery(); //(T3) : 돌풍의 데미지가 15증가합니다.

		//HP강화
		void Vitality(); //(T1) : 최대 체력 +1
		void AngerPoint(); //(T2) : 피격시 15초 동안 총알 공격력 및 탄속 +50%
		void Giant(); //(T2) : 최대 체력 +2, 플레이어 크기 +50%, 이동 속도 -16%
		void Regeneration(); //(T3) : 90초마다 체력 1 회복

		//실드강화
		void HolyShield(); //(T1) : 공격을 1회 막아주는 신성한 보호막을 생성한다. 소모된 보호막은 2분마다 재생된다.
		void DivineBlessing(); //(T2) : 신성한 보호막이 활성화된 동안, 재장전 속도와 이동 속도를 25% 증가시킨다.
		void DivineWrath(); //(T2) : 신성한 보호막이 활성화 된 동안 매 초 22의 피해를 주는 번개를 가까이 있는 적에게 떨어뜨린다.
		void StalwartShield(); //(T3) : 보호막 재생성 시간이 1분이 된다.

		//XP획득
		void Magnetism(); //(T1) : 경험치 획득 범위 +30%
		void Recharge(); //(T2) : 경험치 획득 범위 +20%, 경험치 획득 시 10% 확률로 탄환 1개 충전
		void WatchLearn(); //(T2) : 경험치 획득 범위 +15%, 시야 +25%	
		void Excitement(); //(T3) : 경험치 획득 범위 +20%, 경험치 획득 시 1초 동안 연사 속도 +35%

		//이동속도 강화
		void Haste(); //(T1) : 이동속도 +20%, 연사 속도 +5%
		void BlazingSpeed(); //(T2) : 이동속도 +10%, 이동하는 동안 주변의 적에게 발화 효과를 가한다. 이 효과는 빨리 움직일수록 자주 발동된다.
		void RunGun(); //(T2) : 사격 중 이동 속도를 100% 증가시킨다.
		void IntheWind(); //(T3) : 10초마다 이동속도 및 총알 공격력 +10%(최대 40%), 이 효과는 피격시 초기화된다.

		//시너지
		void Glare(); //(T1) : 시야 +25%, 시야 내의 적에게 2초마다 25 피해를 준다.
		void IntenseGlare(); //(T2) : 시야 +25%. 섬광으로 주는 피해량이 2배로 증가한다.
		void SightMagic(); //(T2) : 시야 +15%. 섬광 피해가 총알이 명중했을 때의 효과를 적용한다.
		void Saccade(); //(T3) : 시야 +15%. 섬광이 발생하는 빈도가 두배가 된다.


		//Dodge
		void Evasive(); //(T1) : 회피율 +20%
		void Nimble(); //(T2) : 회피율 +10%, 이동속도 +10%
		void Tiny(); //(T2) : 회피율 +5%, 캐릭터크기 -25%
		void Reflex(); //(T3) : 이동속도 +15%, 이동속도 보너스만큼 회피율이 증가합니다.

		//드래곤
		void DragonEgg(); //1분 후에 용으로 부화하는 알을 얻는다. 부화한 용은 커서 방향으로 피해와 발화 상태를 주는 탄을 세 갈래로 발사한다. (기본 관통 1회, 기본 피해량 20)
		void AgedDragon(); //(T2) : 용의 피해량이 60초마다 8 상승한다. 이 효과는 아직 부화하지 않았어도 적용된다.
		void TrainedDragon(); //(T2) : 용의 공격 속도가 60초마다 10% 상승한다. 이 효과는 아직 부화하지 않았어도 적용된다.
		void DragonBond(); //(T3) : 투사체가 용의 공격력 10%에 해당하는 추가 피해를 입힌다.드래곤 특성을 얼마나 빨리 먹느냐로 갈린다.일반 모드에선 이론상 최대 17.2까지 받을 수 있다.

		//유령
		void GhostFriend(); //(T1) : 22의 피해를 주는 탄을 발사하는 유령을 소환한다.
		void EnergeticFriends(); //(T2) : 소환수 공격 속도 +50%
		void InSync(); //(T2) : 소환수 공격력 +15%, 소환수 공격 속도 +15%, 커서 방향으로 공격한다.
		void VengefulGhost(); //(T3) : 소환수 공격력 +15%, 유령의 탄을 2개 더 추가한다.

		//매직랜즈
		void MagicLens(); //(T1) : 통과한 탄의 피해량과 크기를 30% 증가시키는 렌즈를 소환한다. 이 효과는 소환 공격력에 비례한다. 유령 친구의 탄이나 Hina의 분신 등에도 적용되며 한 탄에 여러번 적용시킬 수 있다.
		void IgnitingLens(); //(T2) : 렌즈를 통과한 탄환이 발화 효과를 입힌다. 이 발화 피해량은 탄환 피해량과 비례하기 때문에, 실질적으로 DPS를 몇배 끌어올린다.
		void Refraction(); //(T2) : 렌즈를 통과한 탄환이 바운스+2를 얻는다.
		void FocalPoint(); //(T3) : 렌즈의 모든 효과가 2배가 되지만, 렌즈의 크기가 절반으로 작아진다.

		std::array<std::array<bool, 4>, 10> GetUpgradeBool() { return bupgrade; }

	private:
		PlayScene* pscene;
		std::array<std::array<bool, 4>, 10> bupgrade;
	};
}