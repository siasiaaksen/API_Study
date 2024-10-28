#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void APlayGameMode::BeginPlay()
{
	// 언리얼에서 게임 모드는 
	// 게임 규칙을 정하고 게임에 대한 규칙및 규격을 준비하라고 언리얼이 준비한
	// 가장 먼저 만들어진다는 점 그 자체가 중요하다.
	// 레벨 자체를 준비시킬수 있는 액터이다.
	
	// 내가 만든 컨텐츠용 게임모드
	// => 레벨이 만들어지면 무조건 만들어져야 한다.
	// 레벨마다 만들어줘야 할것이다.

	// 레벨마다 만들어진 게임모드에서
	// BeginPlay를 할때 => 그 레벨이 시작되면 존재해야 하는 엑터
	// 플레이어는 말그대로 주요 조작 액터라고 생각하고 있기 때문에.
	// 레벨이 만들어지면 만들어져야할 액터들을 만드는 용도를 적합하지 않아.

	// GameMode =>를 상속받는 내가 만든 게임모드들은
	// 게임을 시작할대 필요한 것들을 준비하라고 만들어준 가장 먼저 만들어지기
	// <= 왠만하면 초반에 다 만들어 놓자.




	APlayMap* PMAP0 = GetWorld()->SpawnActor<APlayMap>();
	APlayMap* PMAP1 = GetWorld()->SpawnActor<APlayMap>();
	PMAP1->SetActorLocation({700, 200});
	APlayMap* PMAP2 = GetWorld()->SpawnActor<APlayMap>();
	PMAP2->SetActorLocation({ 500, 1000 });
	APlayMap* PMAP3 = GetWorld()->SpawnActor<APlayMap>();
	PMAP3->SetActorLocation({ 900, 600 });
}
