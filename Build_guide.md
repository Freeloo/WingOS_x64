## Before :
you can't build wingOS on windows or in WSL 


# Build guide :
how to build this os ?

## Set up :
you have to install these packages : 

```build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo gparted lib-fuse fuse```

before making the toolchain

## Making the toolchain :

then run the file make\_cross\_compiler.sh

## Making echfs-utils :
run 
``` make setup_echfs_utils ```
then run in the echfs folder
``` sudo make install ```
now you have echfs-utils ! 

## Making wingOS :

you have to run make to build wingOS
there are some option : 



- make clean

to clean



- make format 

to run clang format



- make super

to clean, rebuild and run everything



- make app

to make wingOS app



- make runvbox

for running virtual box (you have to create a virtual machine named : wingOS64



- make run

for running qemu



- make boch

for running boch



- make disk 

for making the disk


