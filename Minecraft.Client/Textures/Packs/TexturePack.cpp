#include "../../Platform/stdafx.h"
#include "TexturePack.h"

std::wstring TexturePack::getPath(bool bTitleUpdateTexture /*= false*/)
{
	std::wstring wDrive;
	#ifdef _XBOX
	if(bTitleUpdateTexture)
	{
		// Make the content package point to to the UPDATE: drive is needed
		#ifdef _TU_BUILD
		wDrive=L"UPDATE:\\";
		#else

		wDrive=L"GAME:\\res\\TitleUpdate\\";
		#endif
	}
	else
	{
		wDrive=L"GAME:\\";
	}
	#else

	#ifdef __PS3__

	// 4J-PB - we need to check for a BD patch - this is going to be an issue for full DLC texture packs (Halloween)

	char *pchUsrDir=getUsrDirPath();

	std::wstring wstr (pchUsrDir, pchUsrDir+strlen(pchUsrDir));

	if(bTitleUpdateTexture)
	{
		// Make the content package point to to the UPDATE: drive is needed
		wDrive= wstr + L"\\Common\\res\\TitleUpdate\\";
	}
	else
	{
		wDrive= wstr + L"/Common/";
	}


	#elif __PSVITA__
	char *pchUsrDir="";//getUsrDirPath();
	std::wstring wstr (pchUsrDir, pchUsrDir+strlen(pchUsrDir));

	if(bTitleUpdateTexture)
	{
		wDrive= wstr + L"\\Common\\res\\TitleUpdate\\";
	}
	else
	{
		wDrive= wstr + L"/Common/";
	}
	#else
	// same thing as consolesapp
	std::wstring assetsBase;
	#if defined(__linux__) || defined(__unix__)
	{
		char buf[PATH_MAX];
		ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
		if (len != -1) {
			buf[len] = '\0';
			std::string exePath(buf);
			size_t pos = exePath.find_last_of('/');
			std::string exeDir = (pos == std::string::npos) ? exePath : exePath.substr(0, pos);
			std::wstring candidate = convStringToWstring(exeDir) + L"/../../Minecraft.Assets/";
			File candidateFile(candidate);
			if (candidateFile.exists()) assetsBase = candidate;
		}

		if (assetsBase.empty()) {
			// Try searching from CWD
			File cwdCandidate(L"Minecraft.Assets/");
			if (cwdCandidate.exists()) assetsBase = L"Minecraft.Assets/";
		}
	}
	#endif

	if (!assetsBase.empty()) {
		if (bTitleUpdateTexture) wDrive = assetsBase + L"Common/res/TitleUpdate/";
		else wDrive = assetsBase + L"Common/";
	} else {
		if(bTitleUpdateTexture)
		{
			// Make the content package point to to the UPDATE: drive is needed
			wDrive=L"Common\\res\\TitleUpdate\\";
		}
		else
		{
			wDrive=L"Common/";
		}
	}
	#endif
	#endif

	return wDrive;
}
