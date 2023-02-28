#pragma once
#include "SceneDefines.h"
#include "Drawgon/GUI/GUI_GeneralDefines.h"

#include "Drawgon/Scene/SceneData.h"
#include "Drawgon/Scene/SceneCamera.h"

#include <Tigraf/Tigraf.h>

using namespace Tigraf;

namespace Drawgon
{
	enum class SceneMode : uint16_t
	{
		Edit = 0,
		Play = 1,
		Pause = 2,
	};

	class Scene
	{
		DRAWGON_DECLARE_ON_GUI_RENDER
		DRAWGON_SCENE_CAMERA

		friend class AppLayer;

	public:

		Scene();
		Scene(const std::filesystem::path& filepath);
		Scene(const std::filesystem::path& fileDir, const char* filename);

		~Scene() {}

		void onUpdate(const TimeStep& ts);
		void onDraw();
		bool onEvent(Event& e);

		void onPlay();
		void onPause();
		void onStop();

		Ref<Texture2D> getColors() { return m_SceneFramebuffer->getColorTexture(0); }			//TODO: Maybe make it default to 0 implicitly
		Ref<Texture2D> getDepth() { return m_SceneFramebuffer->getDepthStencilTexture(); }

		/**
			Sets index of an cubemap texture which will be used
			@param skyboxIndex is the index which will shader sample cubemap from. Default range is [0-19]
		*/
		void setSkyboxIndex(uint16_t skyboxIndex);
		const int getSkyboxIndex() { return m_SceneData.m_PerFrameData.SkyboxIndex; }

	protected:

		Ref<Framebuffer> m_SceneFramebuffer = nullptr;

		SceneData m_SceneData{};
		SceneMode m_SceneMode = DRAWGON_DEFAULT_SCENE_MODE;

		Ref<Mesh> m_SceneSkybox = nullptr;
		Ref<Mesh> m_SceneGrid = nullptr;

	private:

	};
}