# OpenTTD Social Presence Plugin for Steam

This plugin allows OpenTTD to announce what the player is doing on Steam.

## Supported OpenTTD

- OpenTTD 14+

## Supported Platforms

- Windows (32bit, 64bit)
- Linux (x86_64)
- MacOS (i386, x86_64, arm64)

## Preparation

- Download the latest SteamWorks SDK from [here](https://partner.steamgames.com/downloads/list).
  You do need an account for this.
- Unpack the zip-file in the root folder.
- Run `./copy-sdk-files.sh`.

In case you can't execute `copy-sdk-files.sh`, you have to do some actions manually:

- Copy the `public/steam` folder into `src/` (so there now is a `src/steam` folder with include-files).
- Copy the `redistributable_bin` folder to `lib` (so there are now folders like `linux32` in `lib/`).
- Make a folder `lib/win32`, and move `lib/steam_api.*` to `lib/win32/`.

## Building

This is a default CMake Project.

```bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/install ..
make
```

On MacOS, you need to add `-DCMAKE_OSX_ARCHITECTURES=[arm64|x86_64|i386]` to the `cmake` line, to select which of the targets you want to build for.

## Installation

```bash
make install
```

This creates a `lib` folder in the `install` folder of your build-dir.

In your OpenTTD folder, for example in your Documents folder, there should be a `social_presence` folder (if not, start OpenTTD once to create that folder).
Copy the content of the `lib` folder into `social_presence/steam`.

Now start OpenTTD to try out the plugin.
Start OpenTTD with `-dmisc=1` to get a bit more information about what plugins it sees and how they are loading.

## Updating the Steamworks SDK

- Download the SDK from [here](https://partner.steamgames.com/downloads/list).
- Upload the SDK to the Cloudflare R2 bucket "Steamworks SDK".
- On GitHub, under "Secrets and variables" -> "Actions" -> "Variables", update the version to the new version.

And now the CI / Release will use the new SDK.

The reason this is needed, is because Steam puts the download behind authorization, which is very difficult to do from a GitHub Workflows.
The SDK is also not available via `steamcmd` (which would have been a fine solution).
So all we have left is uploading the SDK ourselves to a place where we can reach from a GitHub Workflows.
