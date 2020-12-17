## Background
The default map constructor sets maplayout is 32_32 inside the background.cpp engine. New constructor with maplayout parameter is added.
* For 64x64 map layout a 512x512.png is doable, but ~2 rows should be left to hinder bg index overlapping.

##Grit
* Set grit map & palette to u16 bit size.
* For tiles u32 bit size is possible.

###Commands cmd
####sprites
> grit pic1.png pic2.png kul.png -ftc -pS -gB8 -O shared.c

####background 
* met mLf ipv mLs werkt niet
> grit splashimage.png -gt -gB8 -mRtpf -mLs -ftc 

##GBA-TileEditor
With this program we can chose the map layout size and insert a tileset to design a costume scene/map
