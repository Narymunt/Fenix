#define MyAppName "Gems Of Atlantis"
#define MyAppVerName "Gems Of Atlantis E429"
#define MyAppPublisher "SHODAN9"
#define MyAppURL "http://shodan9.com"
#define MyAppExeName "Game.exe"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
ChangesAssociations=yes
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
UninstallDisplayIcon={app}\Game.ico
LicenseFile=c:\iProducts\Gems Of Atlantis\windows\licence.txt
SetupIconFile=c:\iProducts\Gems Of Atlantis\windows\Game.ico
Compression=lzma/max
SolidCompression=yes
WizardImageFile=c:\iProjects\GemsOfAtlantis\windows installer\lewo.bmp
WizardSmallImageFile=c:\iProjects\GemsOfAtlantis\windows installer\up.bmp
  
[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: c:\iProducts\Gems Of Atlantis\windows\*; DestDir: {app}; Flags: recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent

