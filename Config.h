#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

namespace gm
{
	const int ChunkHeight = 24; // number of tiles in a chunk
	const int ChunkWidth = 16;	// number of tiles in a chunk
	const int MapWidth = 32;	// map size
	const int MapHeight = 24;

	const int MaxTextureSize = 490;	// texture size
	const int TileSize = 70;		// tile size

	const float MaxXVelocity = 1024; // 1024 px/s
	const float AccelerationX = 3072; // player will gain 3072px/s in velocity after one second (meaning it will reach its max velocity after 1/3 of a second)
	const float SlowdownX = 0.99f*4; // lose 396% of its speed each second (meaning we will lose all speed in ~0.25s)

	const float MaxYVelocity = 1792; // 1792 px/s - we have this so player doesnt fall through the tiles
	const float Gravity = 5376; // player will fall and gain 5376px/s in velocity after one second (meaning it will reach its max velocity after 1/3 of a second)
	const float JumpVelocity = 1623; // h = v0^2/(2g), so for a jump height of 245px (3.5 blocks) we get v0 = 1623px/s 

	const float PhysicsStep = 1 / 60.f; // seconds per tick
}

#endif