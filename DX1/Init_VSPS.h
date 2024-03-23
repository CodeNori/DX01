
ID3D11VertexShader* g_pVertexShader = nullptr;//���ؽ����̴�
ID3D11InputLayout* g_pVertexLayout = nullptr;//���ؽ����̾ƿ�
ID3D11PixelShader* g_pPixelShader = nullptr;//�ȼ� ���̴�

ID3D11VertexShader* g_pGridVertexShader = nullptr;//�׸��� ���ؽ����̴�
ID3D11InputLayout* g_pGridVertexLayout = nullptr;//�׸��� ���ؽ����̾ƿ�
ID3D11PixelShader* g_pGridPixelShader = nullptr;//�׸��� �ȼ� ���̴�

HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);



HRESULT Init_GridVertexShader()
{
	HRESULT hr;

	// Compile the vertex shader
	//���̴��� ���α׷� �����Ҷ����� ������ �����ʰ� �ؿ� �Լ� ȣ�⶧ ������
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"Line.fx", "VS", "vs_4_0", &pVSBlob);//������ pVSBlob�� ���ؽ����̴������� �Է¼��� Shader02.fx �� ���⼭�� ��������
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The Line.fx file cannot be compiled.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pGridVertexShader);//������ 
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pGridVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT Init_GridPixelShader()
{
	HRESULT hr;

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Line.fx", "PS", "ps_4_0", &pPSBlob);//������ pVSBlob�� �ȼ����̴������� �Է�
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The Line.fx file cannot be compiled.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pGridPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	return S_OK;

}

void Render_GridShader()
{
	// Set the input layout
	pd3dContext->IASetInputLayout(g_pGridVertexLayout);         //�׸��� ���̾ƿ� ��ǲ
	pd3dContext->VSSetShader(g_pGridVertexShader, nullptr, 0);  //�׸��� ���ؽ� ���̴� 
	pd3dContext->PSSetShader(g_pGridPixelShader, nullptr, 0);   //�׸��� ���ؽ� ���̴�
}