#!/usr/bin/env python3

from shutil import copytree, copy
from sys import argv
from pathlib import Path

project_source_root = Path(argv[1])
build_root_dir = Path(argv[2])
client_build_dir = Path(argv[3])
media_archive = Path(argv[4])
output_stamp = Path(argv[5])

# At runtime, the client expects a `Common/` folder from the Minecraft.Assets source and a compiled
# media archive (LinuxMedia.arc) inside of said folder at its current working directory to launch.
#
# `meson install` also handles this, but installs it to system folders, which can be annoying for
# testing. Since we want a way to run it straight from `/build` when debugging, we do this instead.

# copy `Minecraft.Assets/Common` into the build directory for the client.
copytree(
    project_source_root / "Minecraft.Assets" / "Common",
    client_build_dir / "Common"
)

# copy the media archive to `Common/Media` inside the folder we just copied.
copy(media_archive, client_build_dir / "Common" / "Media")

# modify the stamp so this only happens when client or media_archive targets are changed
Path(output_stamp).touch()