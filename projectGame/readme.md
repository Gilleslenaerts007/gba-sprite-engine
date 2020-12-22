## Global info

## Bugs
Really weird array glitch in where array position 0 of the pixeltiles of 7 sprites in a spritesheet file can not be accesed. This is fixed with
adding another sprite to the sheet so the sprite in position 0 of the array is moved to position 1, position 1 to 2,.... Still position 0 for animatetoframe(0)
does not work with this.
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
