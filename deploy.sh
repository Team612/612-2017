#!/bin/bash
#!/usr/bin/expect -f

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "deploy.sh: Attempting to build without veryfying WPILib"
echo "deploy.sh: REMINDER: Always run 'make' before running 'make deploy'!"

if [ ! -d "wpilib/" ] && [ ! -d "$HOME/wpilib/" ]; then
  echo "deploy.sh: WPILib not in usual places"
  echo "deploy.sh: Exiting..."
  exit
fi

# run cmake to generate Makefile contents
cd ${DIR}/.build
rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile

echo "deploy.sh: Generating Makefiles..."
cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=./arm.cmake robot.cmake .. > /dev/null

# run make for the Makefile now
source make.settings > /dev/null 2>&1
make VERBOSE=1 -j $PARALLELBUILD

# Delete cmake files to keep Eclipse working
echo "deploy.sh: Deleting CMakeFiles and prepping binary..."
rm -rf CMakeFiles/
rm -rf ./FRCUserProgram
mv ./FRC* ./FRCUserProgram

echo "deploy.sh: Beginning deploy process..."
echo "Enter team name: "
read team

ping -c 4 "roboRIO-${team}-FRC.local" ; mDNS=$?
if [ $mDNS -ne 0 ]; then
  echo "roboRIO not found on mDNS, falling back to static USB..."
  ping -c 4 "172.22.11.2" ; static=$?
  if [ $static -ne 0 ] ; then
    echo "Failed to connect via static USB, falling back to static ethernet..."
    ping -c 4 "$(cat ../rio_ip.txt)" ; ethernet=$?
    if [ $ethernet -ne 0 ] ; then
      echo "Connection to roboRIO failed on all points!"
    else
      scp "FRCUserProgram" "lvuser@$(cat ../rio_ip.txt):~/FRCUserProgram"
      expect "assword:"
      send "\r"
      interact
    fi
  else
    scp "FRCUserProgram" "lvuser@172.22.11.2:~/FRCUserProgram"
    expect "assword:"
    send "\r"
    interact
  fi
else
  scp "FRCUserProgram" "lvuser@roboRIO-${team}-FRC.local:~/FRCUserProgram"
  expect "assword:"
  send "\r"
  interact
fi
echo "deploy.sh: Exiting..."
