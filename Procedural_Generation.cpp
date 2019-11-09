//Procedural Generation Project C++ Class
//Rishabh Pandey (UIUC-Junior)

#include "Procedural_Generation.h"
#include "Engine/World.h"

// Sets default values
AProcedural_Generation::AProcedural_Generation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	x = 0.0f;
	y = 0.0f;
	lowerBound = -4000.0f;
	upperBound = 4000.0f; 
	minDistance = 40.0f;
	iterations = 100;
	lastXVals.SetNum(iterations);
	lastYVals.SetNum(iterations);
}

// Called when the game starts or when spawned
void AProcedural_Generation::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < iterations; i++) {
		x = generateX(x); //Generating X Values for Mesh Placement
		y = generateY(y); //Generating Y Values for Mesh Placement
		lastXVals[i] = x; 
		lastYVals[i] = y;
		const UWorld* world = GetWorld(); //Checking if the World exists

		if (world) {
			FActorSpawnParameters params;
			params.Owner = this;
			params.Instigator = Instigator;

			FVector location;
			//setting location of mesh (z subject to choice)
			location.Set(x, y, 150.0f);
			//Spawning Mesh in World
			AActor* actor = GetWorld()->SpawnActor<AProceduralMesh>(t1, location, FRotator::ZeroRotator, params);

		}
	}
}

// Called every frame
void AProcedural_Generation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AProcedural_Generation::generateX(float lastX) {
	//Random Value Between Lower and Upper
	float val = FMath::RandRange(lowerBound, upperBound);
	val += lastX;
	if (val < lowerBound || val > upperBound) {
		//Regenerate if out of bounds
		val = generateX(lastX);
	}
	if (isUsed(lastXVals, val)) {
		//Regenerate if a mesh already exists there
		val = generateX(lastX);
	}

	return val;
}

float AProcedural_Generation::generateY(float lastY) {
	//Random Value Between Lower and Upper
	float val = FMath::RandRange(lowerBound, upperBound);
	val += lastY;
	if (val < lowerBound || val > upperBound) {
		//Regenerate if out of bounds
		val = generateX(lastY);
	}
	if (isUsed(lastYVals, val)) {
		//Regenerate if a mesh already exists there
		val = generateX(lastY);
	}

	return val;
}

bool AProcedural_Generation::isUsed(TArray<float> &lastArray, float checkNumber) {
	//Checking if a certain coordinate is already in use by another mesh.
	for (int i = 0; i < lastArray.Num(); i++) {
		if (distance(lastArray[i], checkNumber) < minDistance) {
			return true;
		}
	}
	return false;
}

float AProcedural_Generation::distance(float first, float second) {
	//Distance between meshes.
	float val = first - second;
	if (val < 0) {
		val *= -1;
	}
	return val;
}


