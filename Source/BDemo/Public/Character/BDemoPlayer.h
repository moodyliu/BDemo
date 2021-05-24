// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Attackable/WeaponBase.h"
#include "BDemoPlayer.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class BDEMO_API ABDemoPlayer : public ACharacterBase
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	float CapsuleHalfHeight;
	float ActorZScale;

	float IKLeftFootOffset;
	float IKRightFootOffset;
	float IKHipsOffset;
	float IKLeftHandAlpha;
	float TargetHandAlpha;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FVector RebirthLocationOffset;

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	void Melee();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	float IKFootTrace(FName SocketName,float TraceDistance, FRotator& Rotator);

	void IKFootTick(float DeltaTime);

	void IKHandTick(float DeltaTime);

	void LoadData(class UPlayerDataAsset* PlayerDataAsset);

public:
	ABDemoPlayer();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	bool IsUsingSkill();

	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type Reason) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(TSubclassOf<AWeaponBase> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void SetHandIKState(bool IsEnable);

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

#pragma region IHealth function Override
	virtual void OnReceiveDamage_Implementation(int DamageValue) override;
	virtual void OnReceiveRecover_Implementation(int RecoverValue) override;
	virtual void OnRebirth_Implementation() override;
	virtual void OnDead_Implementation() override;
	virtual void UpdateHp_Implementation() override;
#pragma endregion

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float FootTraceDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKInterpSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKHandInterpSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IKFootOffset;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Attack)
	class AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere)
	class UPlayerDataAsset* InitDataAsset;
};
