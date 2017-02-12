#!bin/bash

printf ".get_ctre: CTRE not found. Downloading..."
wget -r -nd --progress=bar http://www.ctr-electronics.com//downloads/lib/CTRE_FRCLibs_NON-WINDOWS.zip
unzip -q CTRE_FRCLibs_NON-WINDOWS.zip -d ctre_full
printf ".get_ctre.sh: Cleaning up...\n"
cp -r ctre_full/cpp CTRE
rm -rf ctre_full
rm CTRE_FRCLibs_NON-WINDOWS.zip
