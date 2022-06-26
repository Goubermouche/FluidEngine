#ifndef OPENGL_VERTEX_ARRAY_H_
#define OPENGL_VERTEX_ARRAY_H_

#include "FluidEngine/Renderer/VertexArray.h"

namespace fe::opengl {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const {
			return m_VertexBuffers;
		}

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const {
			return m_IndexBuffer;
		}

		virtual uint32_t GetRendererID() override;

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

#endif // !OPENGL_VERTEX_ARRAY_H_