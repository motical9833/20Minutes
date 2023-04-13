#include "Light.hlsli"
#include "Particle.hlsli"

cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Animation : register(b3)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer NumberOfLight : register(b4)
{
    uint numberOfLight;
}

cbuffer ParticleSystem : register(b5)
{
    float4 particleColor;
    uint elementCount;
    float deltaTime;
}

cbuffer Fade : register(b6)
{
    float4 fCameraPosition;
    float2 fCameraScale;
    float2 fResolution;
    float fadeDeltaTime;
    float3 padding;
}


SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

StructuredBuffer<LightAttribute> lightAttributes : register(t13);
StructuredBuffer<Particle> particleBuffer : register(t15);

Texture2D defaultTexture : register(t0);
//Texture2D defaultTexture2 : register(t1);
//Texture2D defaultTexture3 : register(t2);

//atlasSize Texture
Texture2D atlasTexture : register(t12);

void CalculateLight(in out LightColor pLightColor, float3 position, int idx)
{
    if(0 == lightAttributes[idx].type)
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
    else if (1 == lightAttributes[idx].type) //Point Light
    {
        float length = distance(lightAttributes[idx].position.xy,position.xy);
        
        if(length < lightAttributes[idx].radius)
        {
            float ratio = 1.0f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio; // * cos(time); //빛의 크기가 커졌다가 작아졌다가 반복 (횃불)
        }
    }
    else
    {
        
    }
}