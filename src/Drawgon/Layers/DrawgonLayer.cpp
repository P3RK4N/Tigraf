#include "DrawgonLayer.h"


namespace Drawgon
{
	struct PerFrameData
	{
		glm::mat4 CameraViewProjection{};
		glm::vec3 CameraWorldPosition{};
		float TotalTime;
		float FrameTime;
		uint32_t SkyboxSlot;
	} frameData{};

	struct PerModelData
	{
		glm::mat4 M{};
		glm::mat4 MVP{};
	} modelData{};

	void DrawgonLayer::init()
	{
		DRAWGON_ON_GUI_INIT();

		//FRAMEBUFFER FRAME
		glm::mat4 transform =  glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));
		m_FramebufferFrameMesh = MeshPrimitives::Plane(transform);
		m_FramebufferFrameMesh->setShader(Shader::create("shaders\\FramebufferShader.glsl"));


		//TEXTURES
		m_CubemapTexture = TextureCube::create("textures\\cubemaps\\skybox\\skybox", "jpg");
		SetTextureHandle(m_CubemapTexture, TextureCubeSlot::TEXTURE_CUBE_0);

		m_CurrentScene = createRef<Scene>();
		SetTextureHandle(m_CurrentScene->getColors(), Texture2DSlot::TEXTURE_2D_0);
	}

	void DrawgonLayer::onUpdate(const TimeStep& ts)
	{
		m_CurrentScene->onUpdate(ts);
	}

	void DrawgonLayer::onDraw()
	{
		DRAWGON_ON_GUI_RENDER(this);

		m_CurrentScene->onDraw();
		//m_FramebufferFrameMesh->drawTrianglesIndexed();
	}

	void DrawgonLayer::shutdown()
	{
		DRAWGON_ON_GUI_SHUTDOWN();
	}

	bool DrawgonLayer::onEvent(Event& event)
	{
		if(m_CurrentScene->onEvent(event)) return true;

		return false;
	}

	static bool showDemo = true;

#ifndef DRAWGON_EXPORT

	ImGuiID DrawgonLayer::s_DockspaceID = 0;

	void DrawgonLayer::onGuiRender()
	{
		DRAWGON_GUI_RENDER_BEGIN();

		ImGui::BeginMainMenuBar();
		{
			if(ImGui::BeginMenu("Application"))
			{
				if(ImGui::MenuItem("Exit"))
				{
					Application::s_Instance->exit();
				}

				ImGui::EndMenu();
			}

			if(ImGui::BeginMenu("View"))
			{
				DRAWGON_WINDOW_CHECKBOX(m_CurrentScene, "Scene");
				DRAWGON_WINDOW_CHECKBOX(m_Console, "Console");

				ImGui::EndMenu();
			}
		}
		ImGui::EndMainMenuBar();

		ImGui::ShowDemoWindow(&showDemo);

		DRAWGON_ON_GUI_RENDER(m_CurrentScene);
		DRAWGON_ON_GUI_RENDER(m_Console);

		DRAWGON_GUI_RENDER_END();
	}

#endif

}