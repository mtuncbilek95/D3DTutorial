#include <Runtime/Application/Application.h>

#include <Runtime/Graphics/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/Application/ApplicationManager.h>
#include <Runtime/Graphics/Command/CommandList.h>

#include <Runtime/World/ObjectPipeline.h>

#include <Runtime/World/Helmet.h>
#include <Runtime/World/Lantern.h>

std::vector<std::shared_ptr<GameObject>> objects;

int main()
{
	auto app = ApplicationManager::GetInstance().GetApplication();
	auto camera = CameraManager::GetInstance().GetCamera();

	auto pipelineObject = std::make_shared<ObjectPipeline>();

	auto helmet = std::make_shared<Helmet>();
	objects.push_back(helmet);
	auto lantern = std::make_shared<Lantern>();
	objects.push_back(lantern);

	while (app->IsRunning())
	{
		app->Run();
		camera->UpdateViewMatrix();
		camera->HandleInputs(WindowManager::GetInstance().GetWindow()->GetWindowHandle());

		app->GetCommandList()->BindPipeline(pipelineObject->GetPipeline());

		for (auto& object : objects)
		{
			object->Update();

			app->GetCommandList()->BindVertexBuffer({ object->GetMesh()->GetPositionBuffer(), object->GetMesh()->GetTexCoordBuffer(), object->GetMesh()->GetNormalBuffer()});
			app->GetCommandList()->BindIndexBuffer({ object->GetMesh()->GetIndexBuffer() });


			app->GetCommandList()->UpdateDynamicBuffer(object->GetModelCB(), &object->GetModelMatrix(), sizeof(CBData));
			app->GetCommandList()->BindResources({ object->GetBaseColor()->GetTextureView(), object->GetEmmisive()->GetTextureView(), object->GetNormal()->GetTextureView()}, {pipelineObject->GetSampler()}, {}, ShaderStage::PixelShader);
			app->GetCommandList()->BindResources({}, {}, { object->GetModelCB() }, ShaderStage::VertexShader);

			app->GetCommandList()->DrawIndexed((uint32)object->GetMesh()->GetIndices().size(), 0, 0);
		}

		GraphicsManager::GetInstance().GetMainDevice()->ExecuteCommandLists({ app->GetCommandList() });
		GraphicsManager::GetInstance().GetMainDevice()->Present();
	}

	return 0;
}
