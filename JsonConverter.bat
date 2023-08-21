@echo off
taskkill /IM JsonConverter.exe /t /f
start /d "../release" /b JsonConverter.exe "./ExcelFiles" "./JsonFiles"