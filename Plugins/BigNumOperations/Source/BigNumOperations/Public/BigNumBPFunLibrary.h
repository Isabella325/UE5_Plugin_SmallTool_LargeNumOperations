// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BigNumBPFunLibrary.generated.h"


using namespace std;

/**
 * 
 */
UCLASS()
class BIGNUMOPERATIONS_API UBigNumBPFunLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "BigNumFunLib")
		static FString BigNumFun_Add(FString numA, FString numB);
	UFUNCTION(BlueprintCallable, Category = "BigNumFunLib")
		static FString BigNumFun_Minus(FString numA, FString numB);
	UFUNCTION(BlueprintCallable, Category = "BigNumFunLib")
		static FString BigNumFun_Divide(FString num, int divisor, int digit);
	UFUNCTION(BlueprintCallable, Category = "BigNumFunLib")
		static FString BigNumFun_multiply(FString numA, FString numB);
	UFUNCTION(BlueprintCallable, Category = "BigNumFunLib")
		static int BigNumFun_Judge(FString numA, FString numB);
	

	static string s_divide(string num, int divisor, int digit);
	static int s_judge(string a, string b);
	static string s_minus(string a, string b);
	static string s_dezero(string a);
	static string s_add(string a, string b);
	static string s_multiply(string a,string b);
	static long double s_stringToDouble(string a);
	static void s_DoubleToStr(long double a, int digit, string& outR);
};
