
ID3D11VertexShader* g_pVertexShader = nullptr;//���ؽ����̴�
ID3D11InputLayout* g_pVertexLayout = nullptr;//���ؽ����̾ƿ�
ID3D11PixelShader* g_pPixelShader = nullptr;//�ȼ� ���̴�

ID3D11VertexShader* g_pGridVertexShader = nullptr;//�׸��� ���ؽ����̴�
ID3D11InputLayout* g_pGridVertexLayout = nullptr;//�׸��� ���ؽ����̾ƿ�
ID3D11PixelShader* g_pGridPixelShader = nullptr;//�׸��� �ȼ� ���̴�

HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);






