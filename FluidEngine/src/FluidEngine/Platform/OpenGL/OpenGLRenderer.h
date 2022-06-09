#ifndef OPENGL_RENDERER_H_
#define OPENGL_RENDERER_H_

#include "FluidEngine/Renderer/RendererAPI.h"

namespace fe {
	class OpenGLRenderer : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
	};
}

#endif // !OPENGL_RENDERER_H_