#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    
    float2 WorldPos : POSITION;
};

float4 main(VSOut In) : SV_Target
{
    float alpha = fadeDeltaTime;
    
    if (alpha >= 1.f)
    {
        alpha = 1.f;
    }
    else if (alpha <= 0.f)
    {
        alpha = 0.f;
    }
    
    float4 Out = float4(0.f, 0.f, 0.f, alpha);
    
    return Out;
}