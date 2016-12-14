# FRC(++) Build tools

This repository contains the raw make files and scripts for building and deploying code for FRC C++ teams. Will automatically download and compile with the latest version of WPILib

Simply move these files into your repository and place your code in a directory named src/.

Status: needs testing!

To build:

* `make`

To deploy:

* write the ip of your roboRIO in `rio_ip.txt`.

* `make deploy` (always `make` before `make deploy`-ing)

## Dependencies

General: 
  CMake

Windows:
  N/A
  
Linux: 
  N/A
