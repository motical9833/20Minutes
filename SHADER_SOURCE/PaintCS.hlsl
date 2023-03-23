
RWTexture2D<float4> tex : register(u0);

// SV_GropID : �����忡 ���� �׷��� ��ǥ z��
// SV_GropThreadID : �׷� ���� ������ ��ǥ
// SV_GropIndex : �׷쳻�� �������� �ε��� ��ǥ(1����)
// SV_DispatchThreadID : ��ü �������� �������� ȣ��� ��ǥ


[numthreads(32, 32, 1)] // �׷�� ������ ����(��ü �ִ� 1024���� ��������)
void main( uint3 DTid : SV_DispatchThreadID )
{
    if(1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }
    
    tex[DTid.xy] = float4(1.0f, 0.0f, 0.0f, 1.0f);
}