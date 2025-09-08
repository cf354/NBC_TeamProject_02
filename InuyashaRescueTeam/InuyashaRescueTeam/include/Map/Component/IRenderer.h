#pragma once
#include "IComponent.h"

#define RENDER_ALPHA '?'			// 랜더링 할 때 투명 처리 할 문자

class IRenderer : public IComponent
{
public:
	virtual void Render() = 0;
	void SetSortOrder(int sortOrder);

	int GetSortOrder() const;

	/// <summary>
	/// 높을 수록 늦게 렌더링
	/// </summary>
	int sortOrder = 0;
};

