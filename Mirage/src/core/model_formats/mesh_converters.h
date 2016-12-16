#ifndef MESH_CONVERTERS_H
#define MESH_CONVERTERS_H

// std includes
#include <vector>

namespace mirage
{

	class WavefrontFile;
	class MeshBase;

	std::vector<MeshBase *> convertWavefrontToMeshBase(WavefrontFile * const wfFile);

}

#endif // MESH_CONVERTERS_H