#ifndef MESH_CONVERTERS_H
#define MESH_CONVERTERS_H

// std includes
#include <vector>

namespace mirage
{

	class WavefrontFile;
	class MeshBase;
	class MeshRenderer;

	// ---------------------------------------------------------------------------
	// -- Convert wavefront .obj mesh to list of MeshBase
	// ---------------------------------------------------------------------------
	std::vector<MeshBase *> convert_wavefront_to_basemesh(WavefrontFile * const wfFile);

	// ---------------------------------------------------------------------------
	// -- Convert wavefront .obj mesh to lists of MeshBase & MeshRenderer
	// ---------------------------------------------------------------------------
	void convert_wavefront_to_all(
		WavefrontFile * const wfFile,
		std::vector<MeshBase *> & out_base,
		std::vector<MeshRenderer *> & out_renderer
	);

}

#endif // MESH_CONVERTERS_H