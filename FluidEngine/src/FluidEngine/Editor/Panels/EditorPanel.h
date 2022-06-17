#ifndef PANEL_H_
#define PANEL_H_

#include "pch.h"
#include "imgui.h"
#include "FluidEngine/Scene/Scene.h"
#include "FluidEngine/Scene/Entity.h"

namespace fe {

	class EditorPanel : public RefCounted {
	public:
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void SetSceneContext(Ref<Scene> context) = 0;
		virtual void SetSelectionContext(Entity selectionContext) = 0;
	protected:
		std::string m_Name;
		Ref<Scene> m_SceneContext;
		Entity m_SelectionContext;

		bool m_Focused = false;
		bool m_Hovered = false;

		friend class PanelManager;
	};
}

#endif // !PANEL_H_