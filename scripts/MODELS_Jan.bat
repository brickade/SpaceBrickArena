::  ----------------------------------------------------------
set DRIVE_PATH="C:\Users\jan.oldsen\Google Drive\Brickade\ART\Bricks\Models\FINAL"
set LOCAL_PATH="C:\Users\jan.oldsen\Documents\SpaceBrickArena\bin\data\models"
::  ----------------------------------------------------------

@echo off
rmdir /S /Q %LOCAL_PATH%
mkdir %LOCAL_PATH%
cd %DRIVE_PATH%
for /f "tokens=*" %%a in ('dir *.obj /b /s /a-d') do @copy "%%a" %LOCAL_PATH%
::pause