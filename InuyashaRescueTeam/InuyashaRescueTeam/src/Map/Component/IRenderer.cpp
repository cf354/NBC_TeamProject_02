#include "Map/Component/IRenderer.h"

void IRenderer::SetSortOrder(int sortOrder)
{
	this->sortOrder = sortOrder;
}

int IRenderer::GetSortOrder() const
{
	return sortOrder;
}
