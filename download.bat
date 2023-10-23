@echo off
curl -o main.zip https://github.com/TerryMazzoni/RTypeMirror/archive/refs/heads/main.zip
tar -xf main.zip
del main.zip
cd RTypeMirror-main
install.bat