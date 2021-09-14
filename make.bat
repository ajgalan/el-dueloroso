@set GBDK=d:\GBDev\gbdk

@if not exist build mkdir build
@if not exist obj mkdir obj
@if not exist obj\sprites mkdir obj\sprites
@if not exist obj\tiles mkdir obj\tiles
@if not exist obj\maps mkdir obj\maps
@if not exist obj\backgrounds mkdir obj\backgrounds
@if not exist obj\sound mkdir obj\sound

%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/main.o src/main.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/utils.o src/utils.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/levels.o src/levels.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/sound.o src/sound.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/title.o src/title.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/duel.o src/duel.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/shooting.o src/shooting.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/riding.o src/riding.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo0 -c -o obj/text.o src/text.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo1 -c -o obj/duel_banked.o src/duel_banked.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo1 -c -o obj/shooting_banked.o src/shooting_banked.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo1 -c -o obj/riding_banked.o src/riding_banked.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/sprites/ridingSprites.o src/sprites/ridingSprites.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/sprites/mainMenuSprites.o src/sprites/mainMenuSprites.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/sprites/shootingSprites.o src/sprites/shootingSprites.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/sprites/duelCharactersSprites.o src/sprites/duelCharactersSprites.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/tiles/numbers.o src/tiles/numbers.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/tiles/bigTextUITiles.o src/tiles/bigTextUITiles.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/tiles/iconsUI.o src/tiles/iconsUI.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/tiles/textTiles.o src/tiles/textTiles.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/tiles/borderTiles.o src/tiles/borderTiles.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/tiles/pausedUITiles.o src/tiles/pausedUITiles.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/maps/bigTextUIMaps.o src/maps/bigTextUIMaps.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/maps/pausedUIMap.o src/maps/pausedUIMap.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/maps/borderMaps.o src/maps/borderMaps.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/adrianjgLogo.o src/backgrounds/adrianjgLogo.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/duelBackground.o src/backgrounds/duelBackground.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/gbcompo2021.o src/backgrounds/gbcompo2021.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/ridingBackground.o src/backgrounds/ridingBackground.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/shootingBackground.o src/backgrounds/shootingBackground.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/titleBackground.o src/backgrounds/titleBackground.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/gameOverBackground.o src/backgrounds/gameOverBackground.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo2 -c -o obj/backgrounds/easterEgg.o src/backgrounds/easterEgg.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo3 -c -o obj/sound/shootingSong.o src/sound/shootingSong.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo3 -c -o obj/sound/winSong.o src/sound/winSong.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo3 -c -o obj/sound/loseSong.o src/sound/loseSong.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo3 -c -o obj/sound/ridingSong.o src/sound/ridingSong.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-bo3 -c -o obj/sound/titleSong.o src/sound/titleSong.c
%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -Wf-ba0 -c -o obj/saveData.o src/saveData.c

%GBDK%\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-j -DUSE_SFR_FOR_REG -Wm-yn"ELDUELOROSO" -Wm-yj -Wl-yt3 -Wl-yo4 -Wl-ya1 -o build/ElDueloroso.gb ^
obj/main.o obj/utils.o obj/sound.o obj/levels.o obj/title.o obj/duel.o obj/shooting.o obj/riding.o obj/text.o ^
obj/duel_banked.o obj/shooting_banked.o obj/riding_banked.o ^
obj/sprites/ridingSprites.o obj/sprites/mainMenuSprites.o obj/sprites/shootingSprites.o obj/sprites/duelCharactersSprites.o ^
obj/tiles/numbers.o obj/tiles/bigTextUITiles.o obj/tiles/iconsUI.o obj/tiles/textTiles.o obj/tiles/borderTiles.o obj/tiles/pausedUITiles.o ^
obj/maps/bigTextUIMaps.o obj/maps/pausedUIMap.o obj/maps/borderMaps.o ^
obj/backgrounds/adrianjgLogo.o obj/backgrounds/duelBackground.o obj/backgrounds/gbcompo2021.o obj/backgrounds/ridingBackground.o ^
obj/backgrounds/shootingBackground.o obj/backgrounds/titleBackground.o obj/backgrounds/gameOverBackground.o obj/backgrounds/easterEgg.o ^
libs/huGEDriver.obj.o obj/sound/titleSong.o obj/sound/shootingSong.o obj/sound/ridingSong.o obj/sound/winSong.o obj/sound/loseSong.o ^
obj/saveData.o

@echo.
@if exist build/ElDueloroso.gb echo Build finished! The game is on build/ElDueloroso.gb
@if not exist build/ElDueloroso.gb echo Build failed! Please make sure you have set the path to gbdk-4.0.4 on line 1
pause