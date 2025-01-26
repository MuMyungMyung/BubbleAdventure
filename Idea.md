# BubbleAdventure

## Context

BubbleAdventure is a RPG with a bubble themed gameplay.

The main character dives into a world where everything is dirty and needs to be cleaned.
The main character main weapon is soap, which creates bubbles on hit. His special attack is bubble cannon, which shoots bubbles 5 grids away.
He can dash using his soapy dash move.

The main character has stats :
- Attack Power (Increasing the damage output)
- Health (Increasing the health of the player)
- Experience (To gain levels and stat points)
- Sanity (To make the game more realistic)

There will be items, such as a recovery potion that grants health points, meds that grants sanity points.
Items will be picked up automatically.

The game is set in a village. Enemies will spawn by waves. There will be 5 waves.
The enemies attacks are throwing dirt, which stuns the player for 0.1 seconds.

On launch, there will be a splash screen with an animation. A menu, with play, settings and quit.
Settings will contain volume and resolution.

## Technical Requirements

The game will be coded in C++ with SDL3 for graphics and audio.

The game engine will need :
- ECS (or other software design)
- Particle system
- Audio system
- Stat system
- Hitbox system
- Weapon system
- Item system
- Rendering system
- Animation system
- json configuration of entities (if implemented, a save system)

The game ui will be :
- Hotbar for weapon and item slot
- Health, Experience, Sanity displayed
- A stat window
- a pause menu

