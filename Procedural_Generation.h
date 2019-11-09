//Procedural Generation Project .h File
//Rishabh Pandey (UIUC-Junior)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMesh.h"
#include "Procedural_Generation.generated.h"

UCLASS()
class PROCEDURALPROJECT_API AProcedural_Generation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcedural_Generation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh1") //Adding a Mesh to Procedural Generation
	TSubclassOf<AProceduralMesh> t1; 
	
	/*
	UPROPERTY(EditDefaultsOnly, Category = "Mesh2")
	TSubclassOf<AProceduralMesh> t2;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh3")
	TSubclassOf<AProceduralMesh> t3;
	*/


private:
	float generateX(float lastX); //Generating X Values
	float generateY(float lastY); //Generating Y Values
	bool isUsed(TArray<float> &lastArray, float checkNumber); //Checking if those values have already been generated
	float distance(float first, float second); //Distance between two meshes

private:
	TArray<float> lastXVals; //Array of XVals
	TArray<float> lastYVals; //Array of YVals
	float x; //Current X Val
	float y; //Current Y Val
	int iterations;
	float lowerBound; //Landscape Lowerbound
	float upperBound; //Landscape Upperbound
	float minDistance; //Minimum Distance Between Meshes
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
