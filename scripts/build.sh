#!/bin/bash
cd "$( dirname "${BASH_SOURCE[0]}" )/.."
DIR=`pwd`
cd ~/Projects/Particle/firmware-repo/firmware/user
PLATFORM_ID=6 APPDIR=$DIR/src make
