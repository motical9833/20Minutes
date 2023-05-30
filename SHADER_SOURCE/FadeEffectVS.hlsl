#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
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

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;
    
    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);
    
    Out.Pos = ProjPosition;
    Out.Color = In.Color;
    Out.alpha = In.alpha;
    Out.value = In.value;
    
    return Out;
}