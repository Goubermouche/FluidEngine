#ifndef RENDERER_H_
#define RENDERER_H_

#include "Renderer/VertexArray.h"
#include "Renderer/Material.h"
#include "Renderer/Camera.h"
#include "Renderer/Buffers/FrameBuffer.h"

namespace fe {
	struct PointVertex {
		glm::vec3 position;
		glm::vec4 color;
		float radius;
	};

	struct LineVertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	struct QuadVertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	struct CubeVertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	/// <summary>
	/// Batch renderer data
	/// </summary>
	struct RendererData {
		static const uint32_t maxQuads = 20000;
		static const uint32_t maxVertices = maxQuads * 4;
		static const uint32_t maxIndices = maxQuads * 24;

		float lineWidth = 1;

		// Points
		Ref<VertexArray> pointVertexArray;
		Ref<VertexBuffer> pointVertexBuffer;
		Ref<Material> pointMaterial;

		uint32_t pointVertexCount = 0;
		PointVertex* pointVertexBufferBase = nullptr;
		PointVertex* pointVertexBufferPtr = nullptr;

		// Lines
		Ref<VertexArray> lineVertexArray;
		Ref<VertexBuffer> lineVertexBuffer;
		Ref<Material> lineMaterial;

		uint32_t lineVertexCount = 0;
		LineVertex* lineVertexBufferBase = nullptr;
		LineVertex* lineVertexBufferPtr = nullptr;

		// Quads
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Material> quadMaterial;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPtr = nullptr;
		glm::vec4 quadVertexPositions[4];

		// Cubes
		Ref<VertexArray> cubeVertexArray;
		Ref<VertexBuffer> cubeVertexBuffer;
		Ref<Material> cubeMaterial;

		uint32_t cubeIndexCount = 0;
		CubeVertex* cubeVertexBufferBase = nullptr;
		CubeVertex* cubeVertexBufferPtr = nullptr;
		glm::vec4 cubeVertexPositions[8];
	};

	class Camera;

	/// <summary>
	/// Base renderer class. Enables us to interact with the current renderer API. 
	/// </summary>
	class Renderer
	{
	public:
		static void Init();

		/// <summary>
		/// Starts a new render 'context' using the specified camera. All objects drawn in this context will use the specified camera for projection and view matrices. Additionally, the batch renderer is readied.
		/// </summary>
		/// <param name="camera"></param>
		static void BeginScene(Ref<Camera> camera);

		/// <summary>
		/// Ends the current render context.Submits the last batch to the render API.
		/// </summary>
		static void EndScene();

		/// <summary>
		/// Clears the viewport with the previously specified clear color. 
		/// </summary>
		static void Clear();

		/// <summary>
		/// Draws a point using the batch renderer.
		/// </summary>
		/// <param name="p">Point location.</param>
		/// <param name="color">Point color.</param>
		/// <param name="radius">Point radius.</param>
		static void DrawPoint(const glm::vec3& p, const glm::vec4 color, float radius = 1.0f);
		static void DrawPoints(const Ref<VertexArray> vertexArray, size_t vertexCount, Ref<Material> material);

		/// <summary>
		/// Draws a line using the batch renderer.
		/// </summary>
		/// <param name="p0">First point of the line.</param>
		/// <param name="p1">Second point of the line.</param>
		/// <param name="color">Color to drwa the line in.</param>
		static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color);
		static void DrawLines(const Ref<VertexArray> vertexArray, size_t vertexCount, Ref<Material> material);
		static void DrawLinesIndexed(const Ref<VertexArray> vertexArray, size_t vertexCount, Ref<Material> material);

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

		static void DrawBox(const glm::mat4& transform, const glm::vec4& color);

		static void DrawTriangles(const Ref<VertexArray> vertexArray, size_t vertexCount, Ref<Material> material);
		static void DrawTrianglesIndexed(const Ref<VertexArray> vertexArray, size_t count, Ref<Material> material);

		/// <summary>
		/// Sets the viewports position and size.
		/// </summary>
		/// <param name="x">Position on the X axis.</param>
		/// <param name="y">Position on the Y axis.</param>
		/// <param name="width">Viewport width.</param>
		/// <param name="height">Viewport height.</param>
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		/// <summary>
		/// Sets the new clear color that will be used by the Clear function until a new clear color is set.
		/// </summary>
		/// <param name="color">Clear color.</param>
		static void SetClearColor(const glm::vec4& color);

		/// <summary>
		/// Sets the line width that will be used by the batch renderer until a new line width is set. Can only be used once per context.
		/// </summary>
		/// <param name="width">Line width.</param>
		static void SetLineWidth(float width);

		/// <summary>
		/// Gets the line width currently used by the batch renderer.
		/// </summary>
		/// <returns>Currently used line width.</returns>
		static float GetLineWidth();
	private:
		// Batching
		static void StartBatch();
		static void NextBatch();
		static void Flush();
	public:
		static ShaderLibrary shaderLibrary;
	private:
		/// <summary>
		/// Buffer of render data for the current batch.
		/// </summary>
		static RendererData s_Data;

		/// <summary>
		/// Camera that is currently used by the renderer, set by calling the BeginScene function
		/// </summary>
		static Ref<Camera> s_Camera;
	};
}

#endif // !RENDERER_H_