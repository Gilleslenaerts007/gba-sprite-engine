# Ash on the hunt for bandits
'Ash on the hunt for bandits', is a GBA game based on a mix of Pokemon & shooting bandits. The bandits
are invading Ash's town and he is trying to rescue his town by killing as much bandits as possible !
Ash starts with 5 lives and after 10 kills, the enemy spawn pool increases, making it more difficult ! 

How long can you defend Ash's town... ?!

##Folder structure
- Inside 'src', most of the game code can be found.
- 'img', contains the images used for background & sprite creations.
- in 'pikseldata', the converted arrays from using Grit are stored.
##Code overview
The game contains 2 scenes, a start screen and an actual game screen. The menu screen is based of 1 background
and some text together with the sprites used in the game scene. The game scene is called 'scene_Chapter1.cpp", contains
the game logical functions and controls the flow of the bandit waves.

The player, bandits and bullets are the three main classes. The player class contains its lives, position,
current model, time between shots, kill count and his movement flags. It also updates his paremeters and 
movement based on the users input. The enemy class, bandits, has much a like variables and functions. The 
bullets are used for the vector inside the game screen.
###Sprites
Used sprites consists of 2 sided bullets, enemies and a player model. This data can be found in pikseldata & img folders. 

### Background
The default map constructor from fork repository sets the maplayout to 32_32 inside the background.cpp engine. A new constructor added with a maplayout parameter for 500x500 map usage.
* For 64x64 map layout a 512x512.png is doable, but ~2 rows is left to hinder bg index overlapping.

### Bugs
Really weird array glitch in where array position 0 of the pixeltiles of 7 sprites in a spritesheet file can not be accesed. This is fixed with
adding another sprite to the sheet so the sprite in position 0 of the array is moved to position 1, position 1 to 2,.... Still position 0 for animatetoframe(0)
does not work with this. -> solution is to add another same sprite in the sheet.

## OTHER
### GBA-TileEditor
Is a program where the map layout size can be chosen and a custom tileset can be imported.
This is an ideal program for creating a fully customized map/scene.
### Grit
* Set grit map & palette to u16 bit size.
* For tiles u32 bit size is possible.
#### Grit commands cmd
for background tile/map/pallete creation:
> grit game_bg.png  -gt -gB8 -mRtpf -mLs -ftc -s name
> grit menu_bg.png  -gt -gB8 -mRtpf -mLs -ftc -s name

for sprites tile/map/pallete creation:
> grit EnemyFull.png CharFull.png BulletHori.png BulletVerti.png -ftc -pS -gB8 -O shared.c 

###FUTURE WORK
Schema