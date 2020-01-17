#!/bin/bash

if [[ "$1" == "" ]] ; then
    >&2 echo "You must specify a file name to write the mp4 to"
fi

ffmpeg -f rawvideo -pixel_format rgb32 -video_size 512x512 -framerate 25 -i pipe: -y -crf 12 -pix_fmt yuv420p $1