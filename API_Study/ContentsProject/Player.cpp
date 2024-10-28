#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"

APlayer::APlayer()
{
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	SetActorLocation({100, 100});
	SetActorScale({ 100, 100 });
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	// �̺�Ʈ ������� ó��
	// ���ڸ� ȣ���Ҷ� �־��ְڴٴ� �������ִ°� placeholders::
	// � �������� ¥�Ŀ� ���� ��ŸŸ���� �ʿ��Ҽ��� �ְ�
	// �ʿ� �������� �ִ�.

	// 
	//UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&APlayer::LeftMove, this));
	//UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&APlayer::RightMove, this));
	//UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&APlayer::DownMove, this));
	//UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&APlayer::UpMove, this));

	UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::LEFT));
	UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::RIGHT));
	UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::DOWN));
	UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&APlayer::MoveFunction, this, FVector2D::UP));
	
	// �⺻ũ�Ⱑ �������� �����Ƿ� 
	// �⺻ ũ�� �� �⺻ �������� ��������� �մϴ�.

	// Ű�� �����.
	// 1�� ���̽�
	// EngineInput::CreateKey("PlayerMove", 'A');
	// EngineInput::CreateKey("PlayerMove", 'A', APlayer::PlayerLeftMove);
	// 2��
	// EngineInput::BindAction('A', APlayer::PlayerLeftMove);


}

// class LeftPlayer
// class RightPlayer
// �����ϱ�
void APlayer::MoveFunction(FVector2D _Dir/*, AMonster* Monster*/)
{
	// ���͸� ã�ƿ��� �Լ��� �����Ұ��̴�.
	// ���� ��ü�� �����ϱ� ������.
	// ã�ƿ��� �Լ��� �����մϴ�.

	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);
}

//void APlayer::LeftMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::LEFT * DeltaTime * Speed);
//}

//void APlayer::RightMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::RIGHT * DeltaTime * Speed);
//}

//void APlayer::UpMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::UP * DeltaTime * Speed);
//}

//void APlayer::DownMove()
//{
//	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
//
//	AddActorLocation(FVector2D::DOWN * DeltaTime * Speed);
//}

void APlayer::Tick(float _DeltaTime)
{
	//if (UEngineInput::GetInst().IsDown('A'))
	//{
	//	int a = 0;
	//}

	// EngineInput::GetFree(EngineKey::HOME)
	// if (true == EngineInput::GetFree('A'))

	//// �ȴ����� ������ 
	//if (true == EngineInput::GetFree("PlayerMove"))

	//// Ű�� ������
	//if (true == EngineInput::GetUp("PlayerMove"))

	//// ��� ������ ����
	//if (true == EngineInput::GetPress("PlayerMove"))

	//// ���� ó�� �ѹ� ��������
	//if (true == EngineInput::GetDown("PlayerMove"))

	// Time::DeltaTime;

	// �����е��� ��ǻ�Ͱ� 1�������̰�
	// �������� ��ǻ�Ͱ� 2��������

	// ���ӽ����ϰ� ��������?

	//         ������  ����ǻ�ʹ�
	// 0.5��             0.5        =+> 0.5         // 0.0, 0.0, => 0.5, 0.0
	// 1.0��    1.0f     0.5        =+> 1.0         // 0.5, 0.0, => 1.0, 0.0
	// 1.5��             0.5        =+> 1.5 - 1.0
	// 2.0��    1.0f     0.5        =+> 1.0         // 1.0, 0.0, => 2.0, 0.0

	// ��Ÿ��


	// �������� 
	// 0.0, 0.0, => 1.0, 0.0

	// ���� ������� �Ѵ�.
	// ���ɷȾ�
	// ��ǻ���� ���ɰ� ������� => ���� ���� ������ �����ֱ� ���ؼ� �Դϴ�. 

	// �⺻������ � ����� ���鶧��
	
	// ���� ���� ������ �ϰ� �ִٸ� ������ ������ �����ϴ� ����� ����Ѵ�.
	// �����Ҽ� �ִ� �ɷ��� �ִٰ� �ص� ������ ����� ����ؾ� �Ѵ�.
	// 1. ������ ���� ����ϰ� �ִ�.
	// 2. �׸��� ������ ������ �Ǹ� ���� ����� �׳� ��������. 
	// <= ���� ���� �ö󰡸� ���� ���� ���� �������� �ִ�. 5.4
	//    ������ ��ĥ�� ���ϴ� ��.

	// ���� ���� ������ �Ѵٸ�
	// 1. OS�� std�ĸ� ������ �մϴ�.
	// 2. OS �⺻������ �ϵ��� ���õȰ� ��κ� Window
	//    CPU�� ���� ��ǥ������ ���� �����带 ��ﶧ �����ϰ� �˴ϴ�.
	// 3. std�� ���� ������ ���鿡�� �����ϴ� �������� std�� �������� ���ɼ��� ����.
	//    �迭 => �迭�� ������ => std::vector

	// �׷��� �װ� �����鿡�� ��ǥ���� ��� ���� 
	// EngineWindow�� �츮������ ��ǥ���� ���� Ŭ�����Դϴ�.
	// WindowAPI�� ����� ����� �׳� �����ϴ� ���� ����.

	// �����찡 �����ϴ� �⺻ �Է��Լ��Դϴ�.
	// �Է¹��۴� �����찡 �˾Ƽ� ó�����ֱ� ������
	// �Է��� �������� 0�� �ƴ� ���� �����ϴ� �Լ��Դϴ�.

	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	//}

	// ���콺 ���� ��ư�Դϴ�.
	// ���� �Ѽ����� üũ�Ҽ� �ִ� ����� �ʿ��ϴ�.
	if (3.0f < UEngineInput::GetInst().IsPreeTime(VK_LBUTTON))
	{
		// �ֿܼ��� ���� ������� API�ͼ��� ��������.
		ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
		Ptr->SetActorLocation(GetActorLocation());
	}

}