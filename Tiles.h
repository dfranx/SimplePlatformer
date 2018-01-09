#ifndef __GAME_TILES_H__
#define __GAME_TILES_H__

namespace gm
{
	enum Tiles // 'important' tiles
	{
		EMPTY_FG = 0,	// empty block
		BONUS = 7,		// block that can be hit from below
		BONUS_USED = 8, // block that was hit from below
		COIN = 10,		// coin that can be picked up
		EMPTY_DEC = 11,	// empty decoration
		SPIKES = 17		// spikes can kill player
	};
}

#endif