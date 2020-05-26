// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include "CACommentatorTypes.generated.h"


/** Priorities (in order) for the commentator system */
UENUM()
enum class ECACommentatorPriority
{
	Off,
	IdleChatter,
	WeakAttack,
	StrongAttack,
};