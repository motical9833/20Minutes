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

		//���� źȯ
		void TakeAim(); //T1 źȯ�ӵ� 30% ��ź ���� -15%
		void Penteration();//T2 //źȯ �ӵ� 15% ����+1
		void Smiper(); //T2 //źȯ�ӵ� 25% �Ѿ� ���ݷ� 15%
		void Assassin(); //T3 //ź�� 10% ü�� 20%�̸� �� �ڵ����

		//������ ��ȭ
		void PowerShot(); //T1 źȯ ���ݷ� 35%, �˹� 20%
		void Splinter(); //T2 ���� ����Ҷ� �Ѿ� ���� 3����Ѹ��� ���� �Ѿ���(������ 10%)
		void BigShot(); //T2 źȯ ���ݷ� 45%, źȯ ũ��+40%,����ӵ� -5%
		void ReaperRounds(); //T3 źȯ ���ݷ�15% ���� +1 //���� ���̸� ����+1

		// ���� ���
		void RapidFire(); //T1 ����ӵ� 25%
		void LightBullets(); //T2 ����ӵ� 15% �ִ�źâ +1 ź�� 15%
		void RubberBullets(); //T3 ƨ��+1,����ӵ� +10% źȯ ������-10%
		void Siege(); //T3 �������� ��ݽ� 33%�� źȯ�Һ�X

		//��Ƽ��
		void DoubleShot(); //T1 �߻��+1 ��ź����+15%, źȯ������-10%
		void FanFire(); //T2 ������ źȯ�� �߻��Ҷ� 15%�� ���ظ� �ִ� źȯ ������� 10�� �߻�
		void SplitFire(); //T2 �������� �ѹ��� ź�� �߰� �߻�
		void Fusillade(); //T3 �߻�� +1 ��ź ���� 15%, ź ������ -25% �⺻ �߻�ü�� �ι踦 �ι��

		//���� ��ȭ
		void QuickHands(); //T1 ������ �ӵ� +20, ���� �ӵ� 5%
		void ArmedAndReady(); //T2 �������ӵ� 10%, �ִ�ź�� +2
		void FreshClip(); //T2 ������ �ӵ� 5%, ������ �� 1�ʵ��� �Ѿ� ���ط� 50%
		void KillClip(); //T3 óġ�� ������ �ӵ� 5%���� ������ �� �ʱ�ȭ


		std::array<std::array<bool, 4>, 5> GetUpgradeBool() { return bupgrade; }

	private:
		PlayScene* pscene;
		std::array<std::array<bool, 4>, 5> bupgrade;
	};
}