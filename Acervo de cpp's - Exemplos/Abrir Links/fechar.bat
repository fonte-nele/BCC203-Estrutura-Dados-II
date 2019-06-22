echo off
title Abrir e Fechar Firefox Infinitamente
goto main

:main
cls
echo INICIANDO O PROGRAMA...
cd C:\Program Files (x86)\Google\Chrome\Application
start chrome.exe
cls
echo AGUARDANDO 20 SEGUNDOS PARA FECHAR O PROGRAMA...
choice -c r -t 20 -d r >nul
taskkill -f -im chrome.exe
goto main