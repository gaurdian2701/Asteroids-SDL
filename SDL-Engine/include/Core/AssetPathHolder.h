#pragma once
#include <filesystem>
#include <iostream>
#include <string>

#include "PrintDebug.h"

namespace Core
{
	const inline std::string ROOT_PATH = "../../";

	class AssetPathHolder
	{
	private:
		AssetPathHolder() = default;
		~AssetPathHolder() = default;

	public:
		static AssetPathHolder& GetInstance()
		{
			static AssetPathHolder* instance = new AssetPathHolder();
			return *instance;
		}

		void UpdateAssetFolderPath(const std::string someAssetFolderPath)
		{
			m_assetFolderPath = ROOT_PATH + someAssetFolderPath;
		}

		std::string GetAssetPath(const std::string someAssetFilePath)
		{
			std::filesystem::path fullPath = std::filesystem::absolute(m_assetFolderPath + someAssetFilePath);
			PrintDebug(reinterpret_cast<char const *>(fullPath.c_str()), "\n");
			return fullPath.string();
		}

	private:
		std::string m_assetFolderPath = "";
	};
}
