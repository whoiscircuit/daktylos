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
  File "nssm.exe"

  ; Write uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;--------------------------------
; Define constants
;--------------------------------
!define SERVICE_NAME "HidrosisService"
!define DISPLAY_NAME "Hidrosis Service"

;--------------------------------
Section "Install Service with NSSM"

  ; Install the service
  ExecWait '"$INSTDIR\nssm.exe" install "${SERVICE_NAME}" "$INSTDIR\hidrosis.exe"'

  ; Set display name
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" DisplayName "${DISPLAY_NAME}"'

  ; Set working directory
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" AppDirectory "$INSTDIR"'

  ; Optional: redirect logs
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" AppStdout "$INSTDIR\hidrosis-stdout.log"'
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" AppStderr "$INSTDIR\hidrosis-stderr.log"'
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" AppTimestampLog 1'

  ; Set automatic startup
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" Start SERVICE_AUTO_START'

  ; Set to run as LocalSystem
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" ObjectName LocalSystem'

  ; Optionally allow interaction with desktop (legacy)
  ; Only meaningful on older Windows versions
  ExecWait '"$INSTDIR\nssm.exe" set "${SERVICE_NAME}" Type SERVICE_INTERACTIVE_PROCESS'

  ; Start the service
  ExecWait '"$INSTDIR\nssm.exe" start "${SERVICE_NAME}"'

SectionEnd

;--------------------------------
Section "Uninstall"

  ; Stop and remove the service
  ExecWait '"$INSTDIR\nssm.exe" stop "${SERVICE_NAME}"'
  ExecWait '"$INSTDIR\nssm.exe" remove "${SERVICE_NAME}" confirm'

  ; Delete installed files
  Delete "$INSTDIR\hidrosis.exe"
  Delete "$INSTDIR\nssm.exe"
  Delete "$INSTDIR\hidrosis-stdout.log"
  Delete "$INSTDIR\hidrosis-stderr.log"
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR"

SectionEnd