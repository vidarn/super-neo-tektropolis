#ifndef CHUNK_DTJJKSZ
#define CHUNK_DTJJKSZ
#include <boost/random/mersenne_twister.hpp>
#include "actor.hpp"

class Level;

class Chunk 
{
	public:
		Chunk(int x, int y, Level *level, boost::random::mt19937 *rng, const std::string &type);
		~Chunk();
		void generate();
		bool actorInside(Actor *actor);
		bool actorCloseEnough(Actor *actor, int *x, int *y);
		int m_x, m_y;
		int m_iX, m_iY;
		int m_w, m_h;
		bool m_useless;
		const std::string &m_type;
	private:
		Level *m_level;
		boost::random::mt19937 *m_rng;
};

#endif /* end of include guard: CHUNK_DTJJKSZ */
