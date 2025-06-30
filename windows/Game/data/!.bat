@echo [#] Generowanie zasobów...
fenix_file.exe
@echo [#] Game.dat
move data.bin ..\Game.dat
@echo [#] Game.map
move data.map ..\Game.map
del data.h
@echo [#] KONIEC