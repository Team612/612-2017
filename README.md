# FRC(++) Build tools

This repository contains the raw make files and scripts for building and deploying code for FRC C++ teams. Will automatically download and compile with the latest version of WPILib

Simply move these files into your repository and place your code in a directory named src/.

Status: needs testing!

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

## User guide

### Commands

    make - build code
    make update - manually update WPILib
    make clean - clean output files
    make deploy - deploy to robot
    
### How to deploy

1. Replace team number in TEAM_NAME file with your team number

2. Connect to robot

3. Perform `make clean`, `make`, and `make deploy`

## Dependencies

General:

  * CMake
  
  * JRE (used only to unzip a jar file) 

Windows:
  
  * Git bash for Windows (or another program that can run sh files) 
  
Linux: 
  N/A
