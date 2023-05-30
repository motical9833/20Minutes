#include "globals.hlsli"

struct VSIn
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float alpha : ALPHA;
    float value : VALUE;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float alpha : ALPHA;
    float value : VALUE;
};



float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(anisotropicSampler, 0);
    color.w = alpha;
    
    return color;
}