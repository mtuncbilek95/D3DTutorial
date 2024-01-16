#include "Mesh.h"

#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Command/CommandList.h>

#include <Runtime/Graphics/GraphicsManager.h>

void Mesh::AllocateVertex()
{
	GraphicsBufferDesc desc;
	desc.ResourceUsage = ResourceUsage::DEFAULT;
	desc.Usage = BufferUsage::VERTEX_BUFFER;
	desc.CPUAccess = BufferCPUAccess::NONE;
	desc.SizeInBytes = sizeof(XMFLOAT3) * mPositions.size();
	desc.StructureByteStride = sizeof(XMFLOAT3);
	desc.MiscFlags = 0;
	desc.InitialData = mPositions.data();

	if(mPositions.size() != 0)
		mPositionBuffer = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(desc);
}

void Mesh::AllocateIndex()
{
}
