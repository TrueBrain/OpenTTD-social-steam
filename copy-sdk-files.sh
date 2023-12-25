#!/bin/sh

set -e

if [ ! -e "sdk" ]; then
    echo "ERROR - Please download and extract the SteamWorks SDK to the root of this repository."
    echo ""
    echo "The SDK can be found here: https://partner.steamgames.com/downloads/list"
    exit 1
fi

rm -rf src/steam
cp -R sdk/public/steam src/

rm -rf lib
cp -R sdk/redistributable_bin lib

mkdir lib/win32
mv lib/steam_api.* lib/win32/

echo "OK - SDK files copied; you can now safely remove the 'sdk' folder."
