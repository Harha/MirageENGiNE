#ifndef MODEL_BASIC_H
#define MODEL_BASIC_H

#include "game/gcomponent.h"

// std includes
#include <string>
#include <vector>

// mirage includes
#include "core/transform.h"

namespace mirage
{

	class GraphicsEngine;
	class GameObject;
	class MeshBase;
	class MeshRenderer;

	class ModelBasic : public GameComponent
	{
	public:
		ModelBasic(
			const std::string & filePath,
			const std::string & identifier = "model_basic"
		);
		~ModelBasic();

		virtual void update(float dt) override;
		virtual void render(GraphicsEngine * const gfxEngine) override;
		virtual void setParent(GameObject * const parent) override;
		const std::string & getFilePath() const;
		const std::vector<MeshBase *> & getMeshBases() const;
		const std::vector<MeshRenderer *> & getMeshRenderers() const;
	private:
		std::string m_filePath;
		std::vector<MeshBase *> m_meshBases;
		std::vector<MeshRenderer *> m_meshRenderers;
	};

}

#endif // MODEL_BASIC_H