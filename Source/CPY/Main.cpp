// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include <fstream> // For file operations
#include <windows.h>


// Sets default values
AMain::AMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMain::RunPythonScript()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Define the full path to python executable and script
    std::wstring pythonPath = L"C:\\Users\\pc\\AppData\\Local\\Programs\\Python\\Python311\\python.exe"; // Update with your python executable path
    std::wstring scriptPath = L"C:\\UnrealProjects\\CPY\\Source\\CPY\\helper.py";

    // Combine python executable and script path
    std::wstring command = pythonPath + L" " + scriptPath;

    // Start the child process
    if (!CreateProcess(
        NULL,                // No module name (use command line)
        &command[0],         // Command line
        NULL,                // Process handle not inheritable
        NULL,                // Thread handle not inheritable
        FALSE,               // Set handle inheritance to FALSE
        0,                   // No creation flags
        NULL,                // Use parent's environment block
        NULL,                // Use parent's starting directory
        &si,                 // Pointer to STARTUPINFO structure
        &pi))                // Pointer to PROCESS_INFORMATION structure
    {
        // If process creation failed, show error
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to run Python script.");
        return;
    }

    // Wait for the process to complete
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void AMain::SendPatientInformation(int32 age, int32 sex, int32 cp, int32 trestbps, int32 chol, int32 fbs, int32 restecg, int32 thalach, int32 exang, float oldpeak, int32 slope, int32 ca, int32 thal)
{
    // Define the full path to save the file
    FString FilePath = TEXT("C:/UnrealProjects/CPY/Source/CPY/fromc++.txt");

    // Convert integers to FString
    FString AgeStr = FString::Printf(TEXT("%d"), age);
    FString SexStr = FString::Printf(TEXT("%d"), sex);
    FString CpStr = FString::Printf(TEXT("%d"), cp);
    FString TrestbpsStr = FString::Printf(TEXT("%d"), trestbps);
    FString CholStr = FString::Printf(TEXT("%d"), chol);
    FString FbsStr = FString::Printf(TEXT("%d"), fbs);
    FString RestecgStr = FString::Printf(TEXT("%d"), restecg);
    FString ThalachStr = FString::Printf(TEXT("%d"), thalach);
    FString ExangStr = FString::Printf(TEXT("%d"), exang);
    FString OldpeakStr = FString::Printf(TEXT("%.2f"), oldpeak);
    FString SlopeStr = FString::Printf(TEXT("%d"), slope);
    FString CaStr = FString::Printf(TEXT("%d"), ca);
    FString ThalStr = FString::Printf(TEXT("%d"), thal);


    // Create the output string
    FString Result = FString::Printf(TEXT("age,sex,cp,trestbps,chol,fbs,restecg,thalach,exang,oldpeak,slope,ca,thal\n%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
        *AgeStr, *SexStr, *CpStr, *TrestbpsStr, *CholStr, *FbsStr, *RestecgStr,
        *ThalachStr, *ExangStr, *OldpeakStr, *SlopeStr, *CaStr, *ThalStr);

    // Save result to a file
    std::ofstream OutFile(TCHAR_TO_UTF8(*FilePath));
    if (OutFile.is_open())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Saving data to fromc++.txt.");
        OutFile << TCHAR_TO_UTF8(*Result);
        OutFile.close();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to open file fromc++.txt.");
    }

    // Run Python script
    RunPythonScript();
}


void AMain::FinalResultFromPython()
{
    FString FilePath = TEXT("C:/UnrealProjects/CPY/Source/CPY/frompython.txt");
    FString FilePath2 = TEXT("C:/UnrealProjects/CPY/Source/CPY/modelaccuracy.txt");

    // Read the content from the file
    if (FFileHelper::LoadFileToString(FileContent, *FilePath) && FFileHelper::LoadFileToString(FileContent2, *FilePath2))
    {
        // Print the result on screen
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FileContent);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FileContent2);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed to Load File To String.");
    }
}
