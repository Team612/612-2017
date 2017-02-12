ssh "lvuser@$1" "killall -9 FRCUserProgram && rm ~/FRCUserProgram && exit"

scp ".build/FRCUserProgram" "lvuser@$1:~/FRCUserProgram"
