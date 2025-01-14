#include "yaPaintShader.h"



namespace ya::graphics
{
	PaintShader::PaintShader()
		:ComputeShader()
		,mTarget(nullptr)
	{

	}
	PaintShader::~PaintShader()
	{

	}
	void PaintShader::Binds()
	{
		mTarget->BindUnorderdAccessView(0);

		mGroupX = mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupY = mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}
	void PaintShader::Clear()
	{
		mTarget->ClearUnorderdAccessView(0);
	}
}