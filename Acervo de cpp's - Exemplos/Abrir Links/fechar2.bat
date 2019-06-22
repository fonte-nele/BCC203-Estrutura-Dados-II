echo off
title Abrir e Fechar Chrome Infinitamente
goto main

:main
cls
echo AGUARDANDO 20 SEGUNDOS PARA FECHAR O PROGRAMA...
choice -c r -t 20 -d r >nul
taskkill -f -im chrome.exe
goto main