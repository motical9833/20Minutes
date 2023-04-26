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


		std::array<std::array<bool, 4>, 5> GetUpgradeBool() { return bupgrade; }

	private:
		PlayScene* pscene;
		std::array<std::array<bool, 4>, 5> bupgrade;
	};
}