;--------------------------------
; Basic installer info
;--------------------------------
OutFile "Hidrosis-Installer.exe"
InstallDir "$PROGRAMFILES\Hidrosis"
RequestExecutionLevel admin  ; REQUIRED to create a service

Page directory
Page instfiles

;--------------------------------
Section "Install"
  SetOutPath "$INSTDIR"

  ; Copy main files
  File "..\..\build\app\Release\hidrosis.exe"

  ; Write uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;--------------------------------
; Define constants
;--------------------------------
!define SERVICE_NAME "HidrosisService"
!define DISPLAY_NAME "Hidrosis Service"

;--------------------------------
Section "Register Task for Current User"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "Hidrosis" '$INSTDIR\hidrosis.exe'
SectionEnd

;--------------------------------
Section "Uninstall"

  ; Delete installed files
  ExecWait 'taskkill /F /IM hidrosis.exe'
  Delete "$INSTDIR\hidrosis.exe"
  Delete "$INSTDIR\hidrosis-stdout.log"
  Delete "$INSTDIR\hidrosis-stderr.log"
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"
  DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "Hidrosis"

SectionEnd