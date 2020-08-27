# 加密库使用手册

---

本加密库支持在线授权的加密，文件加密和硬件加密。

SDK加密代码段：
{
#ifdef SEETA_AUTO_ENCRYPT
#include "SeetaLANLock.h"
#include "hidden/SeetaLockFunction.h"
#include "hidden/SeetaLockVerifyLAN.h"
#endif
	
	
#ifdef SEETA_AUTO_ENCRYPT
	SeetaLock_VerifyLAN verify(1001);
	if (!SeetaLockSafe_call(&verify))
	{
		orz::Log(orz::FATAL) << "Lock module hijacked" << orz::crash;
	}

	if (verify.out.errcode != 0)
	{
		SeetaLock_ErrorMessage error_message(verify.out.errcode);
		SeetaLockSafe_call(&error_message);
		orz::Log(orz::FATAL) << "SeetaLANLock failed(" << verify.out.errcode << "): " << error_message.out.message << orz::crash;
	}
#endif
}