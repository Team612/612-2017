# FRC(++) Build tools

This repository contains the raw make files and scripts for building and deploying code for FRC C++ teams. Will automatically download and compile with the latest version of WPILib

Simply move these files into your repository and place your code in a directory named src/.

Status: Operational! (Report bugs as Issues)

## Start Here!

### Instructions for creating a new robotics project

1. Fork this repository

2. Replace the code in the src folder with your code.

3. Push to your own repository.

### Instructions for adding FRC(++) Build Tools to an existing robotics project

1. On your local git client, perform `git remote add build https://github.com/Team612/FRCpp_Build_Tools.git`

2. Perform `git pull build master`

3. Merge this repository with your current one.

4. Push the merged changes

## Dependencies

General:

  * CMake
  
  * FRC Toolchain

Windows:
  
  * Cygwin - cmake, make, unzip, wget, openssh

## User guide

### Linux

How to build code:

1. Open a terminal and `cd` into your code base

1. Make sure the code you want to compile is in src/ and `.build.sh` and `Makefile` are in the directory above src/

1. Type `make`into the terminal

How to deploy code:

**FIRST TIME ONLY**

1. Type `ssh-keygen -t rsa` into the terminal

1. Enter file in which to save the key (/home/demo/.ssh/id_rsa): `roborio`

1. Enter passphrase (empty for no passphrase): [leave blank]

1. After the output, connect to the robot and type `lvuser@roborio-[TEAM]-frc.local`. Be sure to replace [TEAM] with your number

1. Write your team number in the TEAM_NAME file. Make sure it is only one line and contains no extra spaces.

After this is done, simply type `make deploy`to deploy

### Windows

How to build code:

1. Open Cygwin and type `cd c:/`

1. Use `ls` to list your directory and `cd` to find the directory your code base is in

1. Make sure the code you want to compile is in src/ and `.build.sh` and `Makefile` are in the directory above src/

1. Type `make`into Cygwin

How to deploy code:

**FIRST TIME ONLY**

1. Type `ssh-keygen -t rsa` into the terminal

1. Enter file in which to save the key (/home/demo/.ssh/id_rsa): `roborio`

1. Enter passphrase (empty for no passphrase): [leave blank]

1. After the output, connect to the robot and type `lvuser@roborio-[TEAM]-frc.local`. Be sure to replace [TEAM] with your number.

1. Write your team number in the TEAM_NAME file. Make sure it is only one line and contains no extra spaces.

After this is done, simply type `make deploy`to deploy

### Commands

    make - build code
    make update - manually update WPILib
    make clean - clean output files
    make deploy - deploy to robot
