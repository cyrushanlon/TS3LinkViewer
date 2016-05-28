#Teamspeak 3 Link Viewer
Used to view links sent through Teamspeak 3 chat on a secondary screen through the use of hotkeys while on the desktop or in a fullscreen application.

Due to TS3s limited selection of Qt DLLs I was unable to fully incorporate the functionality I wanted into the plugin DLL. Through the use of an external exe launched from the TS3 plugin everything that was required is included.

#Current Features
* Can display any valid URL sent to your client through TS3.
* Can hold links so that you don't miss out on anything while you are busy.
* Automatic mode: displays the webpages as the links come
* Hotkey for opening the top link.
* Hotkey for closing the current page.
* Hotkey for toggling automatic mode.
* Configurable Hotkeys and modes.

##Todo
* General Polish.
* Error checking on the settings window.
* Seriously reduce the number of DLLS required

##Possible Features
* A popup mode that allows users with only 1 monitor to view the links.
* No fixed window so no extra room is taken up when no link is loaded.
* Link List as a separate window for use with either of the above.
* Remember screen position for all of the above.
* Remove the need for the exe (could be tough(?))

##Build / Install
Using Qt Creator and Qt 5.6 (MSVC-2015-dynamic) on Windows I was able to build both the program and the TS3 plugin DLL. I have not yet tested this on either Linux or Mac but I suspect that it should just work. 
* Place the compiled DLL into the Teamspeak 3 plugins folder.
* Place the exe inside a folder called "autolink_plugin" inside the plugins folder alongside the following Qt DLLS
  * Qt5Core.dll
  * Qt5Gui.dll
  * Qt5Network.dll
  * Qt5Qml.dll
  * Qt5Quick.dll
  * Qt5WebChannel.dll
  * Qt5WebEngineCore.dll
  * Qt5WebEngineWidgets.dll
  * Qt5Widgets.dll
* Enable the plugin in Teamspeak 3 through Settings > Plugins and ticking "TS3 Auto Link Viewer"

##Notes
* Included in the project is QHotKey as found here: https://github.com/Skycoder42/QHotkey
* Currently does not support flash in the viewing panel.
